#include<stdio.h>
#include<string.h>
#include<stack>
#define MAX 1024
using namespace std;
char ch[6] = {'+', '*', 'i', '(', ')'};
char p[6][6];
stack<int> s1,s2;

int get(int c);
int r();

int main(int argc,char* argv[])
{
    char* fname = argv[1];
    char line[MAX];
    FILE* in;

    in = fopen(fname,"r");
    while(!s1.empty()) s1.pop();
    while(!s2.empty()) s2.pop();
    //>:1 =:0 <:-1
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++) p[i][j]=2;
    p[0][0]=p[0][4]=p[1][0]=p[1][1]=p[1][4]=p[2][0]=p[2][1]=p[2][4]=p[4][0]=p[4][1]=p[4][4]=1;
    p[3][4]=0;
    p[0][1]=p[0][2]=p[0][3]=p[1][2]=p[1][3]=p[3][0]=p[3][1]=p[3][2]=p[3][3]=-1;

    char c=fgetc(in);
    while(c!=EOF){
        if(get(c)==-1) break;
        if(s1.empty()) {s1.push(c); printf("I%c\n",c); c=fgetc(in);}
        else{
            int a=get(s1.top()),b=get(c);
            if(b==-1) {printf("E\n"); break;}
            if(p[a][b]==2) {printf("E\n"); break;}
            if(p[a][b]<=0) {s1.push(c); printf("I%c\n",c); c=fgetc(in);}
            else{
                int flag=r();
                if(flag==0) printf("R\n");
                else {printf("RE\n"); break;}
            }
        }
        while(get(c)==-1){
            int flag=r();
            if(flag==0) printf("R\n");
            else {printf("RE\n"); break;}
            if(s1.empty()) break;
        }
    }
    fclose(in);
	return 0;
}

int get(int c){
    if(c=='+') return 0;
    if(c=='*') return 1;
    if(c=='i') return 2;
    if(c=='(') return 3;
    if(c==')') return 4;
    return -1;
}
int r(){
    int a=s1.top();
    if(a=='(') return -1;
    if(a=='i'){
        s1.pop();
        s2.push('N');
        return 0;
    }
    if(a=='+'){
        if(s2.size()>=2){
            s1.pop();
            s2.pop();
            return 0;
        }
        else return -1;
    }
    if(a=='*'){
        if(s2.size()>=2){
            s1.pop();
            s2.pop();
            return 0;
        }
        else return -1;
    }
    if(a==')'){
        s1.pop();
        if(s1.empty() || s1.top()!='(') return -1;
        s1.pop();
        return 0;
    }
}
