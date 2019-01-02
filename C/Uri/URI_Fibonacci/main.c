#include <stdio.h>
#include <stdlib.h>

/*
fib(0) = 0
fib(1) = 1
fib(n) = fib(n-1) + fib(n-2);
*/
int fib(int n, int *p);

int main()
{
    int result=0, n=0, num_calls, *p;
    p=&num_calls;
    n=0;
    while/*(scanf("%d", &n))*/(n<40)
        {

        num_calls=0;


        result=fib(n, p);


        printf("fib(%d) = %d calls = %d\n", n, num_calls, result);
        n++;
        }
    return 0;
}

int fib(int n, int *p)
{
    if(n==0)
        {
        return 0;
        }
    int vet[40];
    int i;
    vet[0]=0;
    vet[1]=1;
    for(i=2;i<=n;i++)
        {
        *p=*p+2;
        vet[i]=vet[i-1] + vet[i-2];

        }
    return vet[n];
}
