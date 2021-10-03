#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "list.h"

void pushDirectory(list **root, void *new_data)
{
list *new_node = (struct list *) malloc(sizeof(struct list));
list *mod;

new_node->data = (Directory *) new_data;
new_node->next = NULL;
	if (*root == NULL) {
		*root = new_node;
	} else {
		mod = (*root);
	while (mod->next)
		mod = mod->next;
	mod->next = new_node;
	}
list *temp = (*root);
list *nod = temp->next;
char *tmp;

	while (nod != NULL) {
		while (nod != temp) {
			if (strcmp
			(((Directory *) (nod->data))->name,
				((Directory *) (temp->data))->name) < 0) {
				tmp = ((Directory *) (temp->data))->name;
				((Directory *) (temp->data))->name =
					((Directory *) (nod->data))->name;
				((Directory *) (nod->data))->name = tmp;
			}
		temp = temp->next;
	}
	temp = (*root);
	nod = nod->next;
	}
}

void pushFile(list **root, void *new_data)
{
list *new_node = (struct list *) malloc(sizeof(struct list));
list *mod;

new_node->data = (File *) new_data;
new_node->next = NULL;
	if (*root == NULL) {
		*root = new_node;
	} else {
		mod = (*root);
		while (mod->next)
			mod = mod->next;
		mod->next = new_node;
	}
list *temp = (*root);
list *nod = temp->next;
char *tmp;

	while (nod != NULL) {
		while (nod != temp) {
			if (strcmp
			(((File *) (nod->data))->name,
				((File *) (temp->data))->name) < 0) {
				tmp = ((File *) (temp->data))->name;
				((File *) (temp->data))->name =
					((File *) (nod->data))->name;
				((File *) (nod->data))->name = tmp;
			}
		temp = temp->next;
		}
	temp = (*root);
	nod = nod->next;
	}
}

void lsDirectory(list *root)
{
list *curent = root;

	while (curent != NULL) {
		printf("%s ", ((Directory *) (curent->data))->name);
	curent = curent->next;
	}
}

void lsFile(list *root)
{
list *curent = root;

	while (curent != NULL) {
		printf("%s ", ((File *) (curent->data))->name);
		curent = curent->next;
	}
}

void createFS(Directory **root)
{
Directory *curent =
(Directory *) malloc(sizeof(Directory));

curent->parentDir = NULL;
curent->startDirectory = NULL;
curent->startFile = NULL;
curent->name = "/";
(*root) = curent;
}

void mkdir(Directory **root, char *directoryName, Directory **Parent)
{
Directory *head = (Directory *) malloc(sizeof(Directory));

head->name = strdup(directoryName);
head->parentDir = (*Parent);
head->startDirectory = NULL;
head->startFile = NULL;
(*root) = head;
pushDirectory(&((*Parent)->startDirectory), (void *) (*root));
}

void deleteFS(Directory **root)
{
(*root) = NULL;
free(*root);
}

void touch(File **root, char *fileName, char *fileContent,
Directory **Parent)
{
File *head = (File *) malloc(sizeof(File));

head->name = strdup(fileName);
	if (fileContent != NULL) {
		head->data = fileContent;
		head->size = strlen(fileContent);
	} else {
		head->data = NULL;
		head->size = 0;
	}
head->dir = (*Parent);
(*root) = head;
pushFile(&((*Parent)->startFile), (void *) (*root));

}

void cd(Directory **Parent, char *nameGo)
{
list *mod = (*Parent)->startDirectory;

int move;

move = 0;
	while (mod) {
		if (strcmp(((Directory *) mod->data)->name, nameGo) == 0) {
			(*Parent) = (Directory *) mod->data;
			move = 1;
			break;
		}
	mod = mod->next;
	}
	if (move == 0)
		printf("Cannot move to '%s': No such directory!\n", nameGo);
}

void pwd(Directory **root, Directory **radacina)
{
Directory *head = *root;

int i;
i = 0;
	while (head != *radacina && head != NULL) {
		head = head->parentDir;
		i++;
	}
	i--;
	while (i) {
		head = *root;
		for (int j = 0; j < i; j++)
			head = head->parentDir;
		printf("/%s", head->name);
		i--;
	}
printf("/%s", (*root)->name);
printf("\n");
}

void rm(list **root, char *deleteName)
{
list *mod = (*root);
list *prev;

prev = NULL;
int delete;

delete = 0;
	while (mod) {
		if (strcmp(((File *) mod->data)->name, deleteName) == 0) {
			if (prev == NULL) {
				(*root) = mod->next;
				free(mod);
				delete = 1;
			} else {
				prev->next = mod->next;
				delete = 1;
			}
		}
		prev = mod;
		mod = mod->next;
	}
	if (delete == 0)
		printf("Cannot remove '%s': No such file!\n", deleteName);
}

void rmdir(list **root, char *deleteName)
{
list *mod = (*root);
list *prev;

prev = NULL;
int delete;

delete = 0;
	while (mod) {
		if (strcmp(((Directory *) mod->data)->name, deleteName) == 0) {
			if (prev == NULL) {
				(*root) = mod->next;
				free(mod);
				delete = 1;
			} else {
				prev->next = mod->next;
				delete = 1;
			}
		}
		prev = mod;
		mod = mod->next;
	}
	if (delete == 0)
		printf("Cannot remove '%s': No such directory!\n", deleteName);
}
void printFiles(list *root, int spaces)
{
list *curent = root;

	while (curent != NULL) {
		for (int i = 0; i < spaces; i++)
			printf(" ");
		printf("%s\n", ((File *) (curent->data))->name);
		curent = curent->next;
	}
}
void tree(Directory *Parent, list *root, int spaces)
{
root = Parent->startDirectory;
	for (int j = 0; j < 2 * (spaces - 1); j++)
		printf(" ");
printf("%s\n", Parent->name);
printFiles(Parent->startFile, 2 * (spaces + 1));
	while (root) {
		tree(((Directory *) (root->data)), root, spaces + 2);
		root = root->next;
	}
}
int main(void)
{
Directory *MyDirectory;
Directory *newDirectory;
Directory *radacina;
File *MyFiles;

MyDirectory = NULL;
newDirectory = MyDirectory;
radacina = NULL;
MyFiles = NULL;
char buffer[128];

fgets(buffer, 128, stdin);
char *p = strtok(buffer, " ");

	while (strcmp(p, "delete") != 0) {
		if (strcmp(p, "create") == 0) {
			createFS(&radacina);
			MyDirectory = radacina;
		} else if (strcmp(buffer, "mkdir") == 0) {
			p = strtok(NULL, " ");
			mkdir(&newDirectory, p, &MyDirectory);
		} else if (strcmp(buffer, "touch") == 0) {
			char *content;

			p = strtok(NULL, " ");
			content = strtok(NULL, " ");
			touch(&MyFiles, p, content, &MyDirectory);
		} else if (strcmp(buffer, "pwd") == 0) {
			if (MyDirectory == radacina)
				printf("%s\n", radacina->name);
			else
				pwd(&MyDirectory, &radacina);
		} else if (strcmp(buffer, "cd") == 0) {
			p = strtok(NULL, " ");
				if (strcmp(p, "..") == 0)
					MyDirectory = MyDirectory->parentDir;
				else
					cd(&MyDirectory, p);
		} else if (strcmp(buffer, "rm") == 0) {
			p = strtok(NULL, " ");
			rm(&MyDirectory->startFile, p);
		} else if (strcmp(buffer, "rmdir") == 0) {
			p = strtok(NULL, " ");
			rmdir(&MyDirectory->startDirectory, p);
		} else if (strcmp(buffer, "tree") == 0) {
			tree(MyDirectory, MyDirectory->startDirectory, 1);
		} else if (strcmp(buffer, "ls") == 0) {
			lsFile(MyDirectory->startFile);
			lsDirectory(MyDirectory->startDirectory);
			printf("\n");
		}
		fgets(buffer, 128, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		p = strtok(buffer, " ");
	}
	if (strcmp(p, "delete") == 0)
		deleteFS(&MyDirectory);
return 0;
}
