#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
#define MAX 1024
using namespace std;

struct node{
    char ch;
    struct node* next;
    struct node* last;
};
struct node *head,*t;

int main(int argc,char* argv[])
{
    char* fname = argv[1];
    FILE* in;
    in = fopen(fname,"r");

    char c=fgetc(in);
    while(c!=EOF)
    {
        if(head==NULL)
        {
            head=(struct node*)malloc(sizeof(node));
            head->ch=c;
            head->next=head->last=NULL;
            t=head;
        }
        else{
            struct node *p=(struct node*)malloc(sizeof(node));
            t->next=p;
            p->last=t;
            p->ch=c;
            p->next=NULL;
            t=p;
        }
        c=fgetc(in);
    }
    t=head;
    while(t!=NULL)
    {
        printf("%c\n",t->ch);
        t=t->next;
    }
    fclose(in);
	return 0;
}
