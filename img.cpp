#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include<dirent.h>
struct LL
{
    char name[100];
    struct LL *next;
    struct LL *prev;
};

typedef struct LL node;
void push(node **head,char data[]);
void delete_file(node **head);
node *search_file(node *head);
void show(node *head);
void displayImg(node *head);
int is_jpeg(char *fn);
void fetch_file(char *path);
void image_opn(node **head);

int main()
{
    DIR *d;
    int n, i;
    char ch, path[1000];
    char filename[1000];
    node *head;
    head = NULL;
    struct dirent *dir;
    printf("Enter the path to the photo directory: \n");
    scanf("%[^\n]%*c",path);
	printf("\n");

	for(i=0;path[i]!='\0';i++)
		if(path[i] == '\\')
			path[i] = '/';
	if(path[i-1] != '/');
		strcat(path, "/");


    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            strcpy(filename,dir->d_name);
            printf("%s",filename);
            if(is_jpeg(filename))
            {
                printf("\n");
                printf("%s\n", dir->d_name);
                push(&head,filename);
            }
        }
        closedir(d);
    }



    for(i=0;i<100;i++)
    {
        printf("\nEnter\n1 to delete \n2 to search \n3 for slide show \n4 to enable gallery mode\n5 to exit\n");
        scanf("%d",&ch);
        if(ch==1)
            delete_file(&head);
        else if(ch==2)
        {
            node *t;
            t = search_file(head);
            if (t==NULL)
                printf("Does not exist\n");
            else
                printf("Exists\n");
        }
        else if(ch==3)
            show(head);
        else if (ch==4)
            image_opn(&head);
        else if (ch==5)
            break;
        else
            printf("Invalid Choice\n");
    }
}

void push(node **head, char data[])
{
    node *new_node;
    new_node = (node *)malloc(sizeof(node));
    strcpy(new_node->name,data);
    new_node->prev=NULL;
    new_node->next = (*head);
    if ((*head)!=NULL)
        new_node->next->prev = new_node;
    (*head)=new_node;
}

node *search_file(node *head)
{
    node *t;
    t=(head);
    char key[100]; printf("\nEnter the desired file name:\n");
    scanf("%s",key);
    while((t!=NULL)&&(strcmp(t->name,key)!=0))
        t=t->next;
    return t;
}

void delete_file(node **head)
{
    node *t;
    t= search_file(*(head));
    if(t==NULL)
        {
        printf("File does not exist\n");
        return;
        }
    if ((*head)==t)
    {
        (*head)=t->next;
    }
    if(t->next!=NULL)
        t->next->prev=t->prev;
    if (t->prev!=NULL)
        t->prev->next=t->next;
    free(t);

}

void show(node *head)
{
    node *t;
    t=head;
    if (t==NULL)
    {
        printf("No files to view\n");
        return;
    }
    while(t!=NULL)
    {
        printf("[%s]--->",t->name);
        displayImg(t);
        t = t->next;
    }
    printf("\n");
}

void displayImg(node *head)
{
    //Displays the image in a window
    initwindow(720, 640, head -> name);

    readimagefile((head -> name), 0, 0, 720, 640);

    Sleep(4000);
    closegraph();

    return;
}

int is_jpeg(char *fn)
{
	char check[5];
	int len = strlen(fn), i, j;
	if(len >= 4)
		for(i=len-4,j=0;i<len;i++)
			check[j++] = fn[i];
	if( strcmp(".jpg",check) )
		return 0;
	return 1;
}

void image_opn(node **head)
{
    node *t;
    t=(*head); int i;char ch;
    displayImg(t);
    for(i=0;i<100;i++)
    {
        printf("Enter N for next, P for Previous and X to exit\n");
        scanf("\n%c",&ch);

        if(ch=='N')
        {
            if (t->next==NULL)
                printf("No next photo available, end of files\n");
            else
                {
                    t=t->next;
                    displayImg(t);

        }
        }
        else if(ch=='P')
        {
            if (t->prev==NULL)
                printf("No previous file available\n");
            else
                {
                    t=t->prev;
                    displayImg(t);
                }
        }
        else if (ch=='X')
            break;
        else
            printf("Invalid input\n");
    }
}
