#include <stdio.h>
#include <stdlib.h>

int main(){
char c;
int p=0;

while((scanf("%c", &c)) != (EOF))
    {
    if(c=='(')
        p=p+1;
    if(c==')')
        {
        p=p-1;
        if (p<0)
            {
            p=1111;
            }
        }
    if(c=='\n')
        {
        if(p==0)
            {
            printf("correct\n");
            }
        if(p!=0)
            {
            printf("incorrect\n");
            p=0;
            }
        }
    }

return 0;
}
