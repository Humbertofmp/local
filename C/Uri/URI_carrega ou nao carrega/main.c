#include <stdio.h>
#include <stdlib.h>

int * bin(tam, num){
 int *vet, i, numero;


numero=num;
 vet= malloc(tam * sizeof(int));
 if(vet==NULL){printf("\n falta memoria"); exit(1);}

for(i=0; i<tam; i++){vet[i]=0;}
for(i=0; i<tam; i++){
vet[31-i]= numero%2;
numero=numero/2;
 //printf(" %d ", vet[i]);
}

return vet;
}


int main()
{
    int tam=32,i, num, num2,cont=0, potencia=0, base=0, decimal=0, j;
    int *vet, *vet2;
    int res[32];

    while(scanf("%d %d", &num, &num2)!= EOF){;

    vet=bin(tam,num);
    vet2=bin(tam,num2);

    for(i=0; i<tam; i++){
    printf("%d ", vet[i]);
    }
   printf("********\n\n");
    for(i=0; i<tam; i++){
    printf("%d ", vet2[i]);}

    for(i=0; i<tam; i++){
            if((vet[i]+ vet2[i]==0)||(vet[i]+ vet2[i]==2))
             res[i]= 0;

             else
                res[i]=1;
                }


  printf("********\n\n");
  for(i=0; i<tam; i++){
    printf("%d ", res[i]);}


i=0;
while(res[i]==0){
cont++;
i++;
}

//conversão:

potencia = tam-cont;
potencia--; //levar em conta que a primeira potencia é 0
cont--;
for(i=cont; i<32 ;i++){


//potencia
base=res[i] *2;
potencia--;
for(j=1; j<potencia; j++){
base= base*2;
printf("\n%d", base);
}
decimal=decimal + base;
}
decimal++;
printf("\n decimal %d", decimal);

    free(vet);
    free(vet2);
    }
    return 0;
}
