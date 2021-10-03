#include <queue.h>
#include "skel.h"
#include "parser.h"


struct route_table_entry *get_best_route(struct route_table_entry *rtable,int rtable_size,__u32 dest_ip) {
    int i;
    uint32_t max;
    struct route_table_entry *x = NULL;
    for(i = 0 ; i < rtable_size ; i++) {
        if((rtable[i].mask & dest_ip) == rtable[i].prefix) {
            if (ntohl(rtable[i].mask) > max) {
                max = rtable[i].prefix;
                x = &rtable[i];
            }
        }
    }
    if(x == NULL)
        return NULL;
    return x;
}

struct arp_entry *get_arp_entry(struct arp_entry *arpTable,int arp_size,__u32 ip) {
    int i;
    for(i = 0 ; i < arp_size ; i++){
        if(arpTable[i].ip == ip) {
            return &(arpTable[i]);
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
	packet m;
	int rc;
	init(argc - 2, argv + 2);
    struct route_table_entry *rtable = malloc(sizeof(struct route_table_entry));
    struct arp_entry *arpTable = malloc(sizeof(struct arp_entry));
    int arp_size = 0;
    int route_size = 0;
    route_size = read_rtable(argv[1],&rtable);
    queue q;
    q = queue_create();

    while (1) {

		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
        struct ether_header *eth_hdr = (struct ether_header *)m.payload;
        struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));

        if(ntohs(eth_hdr->ether_type) == ETHERTYPE_ARP) {

            struct arp_header *arpHeader = parse_arp(m.payload);

            if(ntohs(arpHeader->op) == ARPOP_REQUEST) {
                struct ether_header *ethHeaderAux = malloc(sizeof(struct ether_header));
                uint8_t macInterface[6];
                get_interface_mac(m.interface,macInterface);
                ethHeaderAux->ether_type = htons(ETHERTYPE_ARP);
                memcpy(ethHeaderAux->ether_shost,macInterface,sizeof(uint8_t) * 6);
                memcpy(ethHeaderAux->ether_dhost,arpHeader->sha,sizeof(uint8_t) * 6);
                send_arp(arpHeader->spa, arpHeader->tpa,ethHeaderAux,m.interface, htons(ARPOP_REPLY));

            }else if(ntohs(arpHeader->op) == ARPOP_REPLY) {

                arpTable[arp_size].ip = arpHeader->spa;
                memcpy(arpTable[arp_size].mac,arpHeader->sha,sizeof(uint8_t) * 6);
                arp_size++;
                arpTable = realloc(arpTable,(arp_size + 1)*sizeof(struct arp_entry));

                while(!queue_empty(q)) {
                    packet *packetAux = malloc(sizeof(packet));
                    packetAux = (packet *)queue_deq(q);
                    struct ether_header *etherHeaderAux = (struct ether_header *)packetAux->payload;
                    struct iphdr *iphdr = (struct iphdr *)(packetAux->payload + sizeof(struct ether_header));
                    struct route_table_entry *search_in_Rtable = get_best_route(rtable,route_size,ntohl(iphdr->daddr));
                    if(search_in_Rtable == NULL)
                        continue;
                    struct arp_entry *search_in_Arp = get_arp_entry(arpTable,arp_size, htonl(search_in_Rtable->next_hop));
                    if(search_in_Arp == NULL)
                        break;
                    memcpy(etherHeaderAux->ether_dhost, search_in_Arp->mac, sizeof(uint8_t) * 6);
                    get_interface_mac(packetAux->interface, etherHeaderAux->ether_shost);
                    memcpy((*packetAux).payload, etherHeaderAux, sizeof(struct ether_header));
                    packetAux->len += sizeof(struct ether_header);
                    send_packet(search_in_Rtable->interface, packetAux);
                }
            }
		}else if(ntohs(eth_hdr->ether_type) == ETHERTYPE_IP){

            if(ip_checksum(ip_hdr,sizeof(struct iphdr)) != 0) {
                perror("Checksum Error");
                continue;
            }

            if(ip_hdr->ttl <= 1){
                send_icmp_error(ip_hdr->saddr,ip_hdr->daddr,eth_hdr->ether_dhost,eth_hdr->ether_shost,11,0,m.interface);
                continue;
            }

            struct route_table_entry *best_route = get_best_route(rtable,route_size,ntohl(ip_hdr->daddr));
            if(best_route == NULL) {
                send_icmp_error(ip_hdr->saddr,ip_hdr->daddr,eth_hdr->ether_dhost,eth_hdr->ether_shost,3,0,m.interface);
                continue;
            }
            struct icmphdr *icmp_hdr = parse_icmp(m.payload);
            struct in_addr verify;
            inet_aton(get_interface_ip(best_route->interface),&verify);

            if(ip_hdr->daddr == verify.s_addr) {
                if (icmp_hdr->type == 8 && icmp_hdr != NULL) {
                    send_icmp(ip_hdr->saddr, ip_hdr->daddr, eth_hdr->ether_dhost, eth_hdr->ether_shost, 0, 0,
                              m.interface,icmp_hdr->un.echo.id, icmp_hdr->un.echo.sequence);
                }
                continue;
            }

            ip_hdr->ttl = ip_hdr->ttl - 1;
            ip_hdr->check = 0;
            ip_hdr->check = ip_checksum(ip_hdr,sizeof(struct iphdr));

            struct arp_entry *dest_arp = get_arp_entry(arpTable,arp_size, htonl(best_route->next_hop));

            if(dest_arp == NULL) {
                struct ether_header *ethHeaderAux = malloc(sizeof(struct ether_header));
                uint8_t macInterface[6];
                get_interface_mac(best_route->interface, macInterface);
                memcpy(ethHeaderAux->ether_shost, macInterface, sizeof(uint8_t) * 6);
                ethHeaderAux->ether_type = htons(ETHERTYPE_ARP);
                struct in_addr inAddr;
                inet_aton(get_interface_ip(best_route->interface),&inAddr);
                uint8_t *macUnknown = (uint8_t *) malloc(sizeof(uint8_t) * 6);
                for (int j = 0; j < 6; j++) {
                    macUnknown[j] = 0xff;
                }
                memcpy(ethHeaderAux->ether_dhost, macUnknown, sizeof(uint8_t) * 6);
                packet *newPacket = malloc(sizeof(packet));
                memcpy(newPacket,&m,sizeof(packet));
                send_arp(htonl(best_route->next_hop), inAddr.s_addr, ethHeaderAux, best_route->interface, htons(ARPOP_REQUEST));
                queue_enq(q,newPacket);
            }else {
                memcpy(eth_hdr->ether_dhost, dest_arp->mac, sizeof(dest_arp->mac));
                get_interface_mac(best_route->interface,eth_hdr->ether_shost);
                send_packet(best_route->interface, &m);
            }
        }
    }
}