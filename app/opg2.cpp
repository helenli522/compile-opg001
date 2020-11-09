#include<stdio.h>
#include<string.h>
#include<stack>
#define MAX 1024
using namespace std;
char ch[6] = {'+', '*', 'i', '(', ')','#'};
char p[6][6];
char line[MAX];
stack<int> s1,s2;

void init();
char find_lt();
int def(int c);
void analyse();

int main(int argc,char* argv[])
{
    int len = 0;
    char c;
    char* fname = argv[1];
    FILE* in;
    in = fopen(fname,"r");
    while((c=fgetc(in))!=EOF){
        if(c!='\r' && c!='\n') line[len++] = c;
    }
    line[len++] = '#'; //printf("%s\n",line);
    fclose(in);
    init();
    analyse();
	return 0;
}

void init()
{
    for(int i=0; i<6; i++) for(int j=0; j<6; j++) p[i][j]=2;
    p[0][0]=p[0][4]=p[0][5]=p[1][0]=p[1][1]=p[1][4]=p[1][5]=p[2][0]=p[2][1]=p[2][4]=p[2][5]=p[4][0]=p[4][1]=p[4][4]=p[4][5]=1;
    p[3][4]=p[5][5]=0;
    p[0][1]=p[0][2]=p[0][3]=p[1][2]=p[1][3]=p[3][0]=p[3][1]=p[3][2]=p[3][3]=p[5][0]=p[5][1]=p[5][2]=p[5][3]=-1;
}
char find_lt()
{
    char c,ans;
    c=s1.top();
    if(def(c)<6)
        return c;
    s1.pop();
    ans=s1.top();
    s1.push(c);
    return ans;
}
int def(int c)
{
    if(c=='+') return 0;
    if(c=='*') return 1;
    if(c=='i') return 2;
    if(c=='(') return 3;
    if(c==')') return 4;
    if(c=='#') return 5;
    return 6;
}
void analyse()
{
    s1.push('#');
    char rc,lc;
    int a,b,compare;
    for(int i=0;i<strlen(line);i++){
        rc=line[i]; //printf("rc:%c\n",rc);
        if(def(rc)<6){
            lc=find_lt(); //printf("lc:%c\n",lc);
            a=def(lc); //printf("a:%d\n",a);
            b=def(rc); //printf("b:%d\n",b);
            compare=p[a][b];
            if(compare==2){
                printf("E\n");
                return;
            }
            if(compare<=0&&rc!='#'){
                s1.push(rc);
                printf("I%c\n",rc);
            }
            else if(rc=='#'&&lc=='#'){
                return;
            }
            else{
                if(lc=='i'){ // ? lc or s1.top()
                    s1.pop();
                    s1.push('N');
                }
                else{
                    if(s1.size()>=4){
                        char t[4];
                        t[2]=s1.top(); s1.pop(); //printf("t[2]:%c\n",t[2]);
                        t[1]=s1.top(); s1.pop(); //printf("t[1]:%c\n",t[1]);
                        t[0]=s1.top(); s1.pop(); //printf("t[0]:%c\n",t[0]);
                        t[3]='\0';
                        if(strcmp("N+N",t)==0 || strcmp("N*N",t)==0 || strcmp("(N)",t)==0)
                            s1.push('N');
                        else{
                            printf("RE\n");
                            return;
                        }
                    }
                    else{
                        printf("RE\n");
                        return;
                    }
                }
                i--;
                printf("R\n");
            }
        }
        else{
            printf("E\n");
            return;
        }
    }
}
