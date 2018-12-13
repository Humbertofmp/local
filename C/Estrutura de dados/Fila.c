#include <stdio.h>
#include <stdlib.h>

#define N 3 //tamanho da fila

struct fila{
int n;
int inicio;
int vet[N];
};

typedef struct fila Fila;

void menu();
Fila* cria();
void push(Fila* f, int x);
int pop(Fila* f);
void imprime(Fila* f);

int main()
{
int op=0, x, p;
Fila* fila;

fila=cria();


while(op!=4)
    {

    menu();
    scanf("%d",&op);
    fflush(stdin);
    system("cls");

    switch(op)
        {
        case 1:
                printf("\nDigite o elemento\n");
                scanf("%d", &x);
                push(fila, x);

            break;
        case 2:
                if (fila->n == 0)
                {
                    printf("\nFila vazia\n");
                }

                else
                {
                    p=pop(fila) ;
                    printf("\nElemento retirado: %d\n", p);
                }
            break;
        case 3:
                imprime(fila);

            break;
        case 4: /*sair*/ break;


        default:

                printf("opcao invalida");
            break;
        }
printf("\n");
system("pause") ;
    }

return 0;
}


void menu(){

system("cls");
printf("MENU:\n\n\
1- Inserir um elemento\n\
2- Remover um elemento\n\
3- Imprimir a fila\n\
4- Sair\n");
}

Fila* cria(){
Fila* f = (Fila*)malloc(sizeof(Fila)); if(!f){printf("\nfalta memoria\n"); exit(1);}
f->n=0;
f->inicio=0;
return f;
}

void push(Fila* f, int x){
int fim;
    if(f->n==N)
        {
        printf("Fila cheia");

        }

    else
        {
        fim=(f->inicio + f->n) %N;
        f->vet[fim] = x;
        f->n++;
        }
}

int pop(Fila* f){
int aux;

aux= f->vet[f->inicio];
f->inicio= ((f->inicio + 1)%N);
f->n --;
return aux;
}

void imprime(Fila*f ){
int i, aux;

    if(f->n==0)
    {printf("Fila vazia\n");}

    else
        {
        aux=f->inicio;

        for(i=0; i<f->n; i++)
            {

            printf("%d, ", f->vet[aux]);
            aux=((aux+1)%N);
            }
        }
}
