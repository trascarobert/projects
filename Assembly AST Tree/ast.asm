
section .data
    delim db " ", 0

section .bss
    root resd 1

section .text


extern check_atoi
extern print_tree_inorder
extern print_tree_preorder
extern evaluate_tree
extern malloc
extern strcpy
extern strtok
extern strlen

global create_tree
global iocla_atoi

iocla_atoi:
    enter   0, 0
    xor     eax, eax

    mov     edi, 0
    
    mov     esi, [ebp + 8]
    mov     edx, 0
    movzx   eax, byte[esi + edx]
    cmp     eax, 45
    mov     ebx, 1
    jnz     condition_while
    mov     ebx, -1
    mov     edx, 1
    jmp     condition_while

while:
    imul    edi, 10
    mov     esi, [ebp + 8]
    movzx   eax, byte[esi + edx]
    sub     eax, 48
    add     edi, eax
    inc     edx

condition_while:
    mov     esi, [ebp + 8]
    movzx   eax, byte[esi + edx]
    cmp     eax, 47
    jng     return_atoi
    cmp     eax, 57
    jng     while


return_atoi:
    mov     eax, ebx
    mov     ecx, edi
    mul     ecx
    xor     edi, edi
    xor     ebx, ebx
    xor     edx, edx
    leave
    ret

create_tree:
    enter   0, 0
    xor     eax, eax
    sub     esp, 20

    push    dword[ebp + 8]
    call    strlen
    add     esp, 4
    inc     eax
    push    eax
    call    malloc
    add     esp, 4
    mov     [ebp - 4], eax

    push    dword[ebp + 8]
    push    dword[ebp - 4]
    call    strcpy
    add     esp, 8

    push    delim
    push    dword[ebp - 4]
    call    strtok
    add     esp, 8
    mov     [ebp - 8], eax
    push    dword[ebp - 8]
    call    strlen
    add     esp, 4
    inc     eax
    mov     [ebp - 20], eax

    mov     edx, 12
    push    edx
    call    malloc
    add     esp, 4
    mov     [ebp - 12], eax

    push    dword[ebp + 8]
    call    strlen
    add     esp, 4
    inc     eax
    push    eax
    call    malloc
    add     esp, 4
    mov     [ebp - 16], eax

    mov     edx, [ebp + 8]
    add     edx, dword[ebp - 20]
    push    edx
    push    dword[ebp - 16]
    call    strcpy
    add     esp, 8
    push    dword[ebp - 16]
    push    dword[ebp + 8]
    call    strcpy
    add     esp, 8

    
    mov     eax, [ebp - 8]
    movzx   eax, byte[eax]
    cmp     eax, 42
    je      if_is_operator
    cmp     eax, 47
    je      if_is_operator
    cmp     eax, 43
    je      if_is_operator
    cmp     eax, 45
    jnz     if_is_operand
    mov     eax, [ebp - 8]
    inc     eax
    movzx   eax, byte[eax]
    cmp     eax, 0
    jnz     if_is_operand

if_is_operator:
    mov     edx, 1
    push    edx
    call    malloc
    add     esp, 4
    mov     edx, [ebp - 12]
    mov     [edx], eax

    push    dword[ebp - 8]
    push    dword[edx]
    call    strcpy
    add     esp, 8

    push    dword[ebp + 8]
    call    create_tree
    add     esp, 4
    mov     edx, [ebp - 12]
    mov     [edx + 4], eax

    push    dword[ebp + 8]
    call    create_tree
    add     esp, 4
    mov     edx, [ebp - 12]
    mov     [edx + 8], eax
	jmp     return_tree

if_is_operand:
    mov     edx, 1
    push    edx
    call    malloc
    add     esp, 4
    mov     edx, [ebp - 12]
    mov     [edx], eax

    push    dword[ebp - 8]
    push    dword[edx]
    call    strcpy
    add     esp, 8

    mov     edx, [ebp - 12]
    mov     dword[edx + 4], 0
    
    mov     edx, [ebp - 12]
    mov     dword[edx + 8], 0

return_tree:
    mov     eax, [ebp - 12]
    xor     edx, edx
    xor     ecx, ecx
    leave
    ret
