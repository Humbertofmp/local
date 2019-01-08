/* Verificar se uma cadeia é reconhecida por um AFND */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*formato do arquivo que gera o automato:
    %d%c inteiro para a quantidade de estados e quebra de linha
    %d%c consecutivos para destino e letra do alfabeto, com 0 e quebra de linha para gerar proximo estado

    considerar estados com valores negativos como estado-final
*/

typedef struct lista{
    int destino;
    char custo;
    struct lista *prox;
}Lista;


void inserir_grafo(Lista **g, int origem, int destino, char custo);
Lista* inserir_lista(Lista *l, int d, char c);
void imprime(Lista **g, int n);
void imprime_lista(Lista*l);
void imprimir_caminhos(int* vet, int estado_atual, int pos_cadeia, int fim, char* cadeia, Lista**g);

int main()
{
int n,x,i, fim;
char ch;
char cadeia[10]; //implementar malloc e perguntar tamanho da cadeia
int *vetor, *caminho;
Lista **grafo;
FILE *arquivo;

arquivo = fopen("automato.txt","r");
if(arquivo==NULL)
    {
    printf("Problemas na ABERTURA do arquivo\n");
    system("pause");
    exit(1);
    }

fscanf(arquivo, "%d", &n);
//gerar grafo
grafo=(Lista**) malloc((n+1)* sizeof(Lista*));
if(grafo==NULL){printf("FALTA MEMORIA"); exit(1);}

for(i=0;i<=n;i++)
    {
    grafo[i]=NULL;
    }

fscanf(arquivo, "%c", &ch);

if(ch!='\n')
	{
	printf("Erro no arquivo");
	exit(1);
	}


for(i=1; i<=n; i++)
	{
	while(1)
		{
		//ler linha inteira do grafo
		fscanf(arquivo, "%d", &x);
		fscanf(arquivo, "%c", &ch);
		if(x== 0)
            break;
		inserir_grafo(grafo, i, x, ch);
		//inserir aresta
		}

	}
fclose(arquivo);
imprime(grafo, n);

fflush(stdin);
printf("\n\nDigite a cadeia: ");
gets(cadeia);
fim=(strlen(cadeia))-1;
vetor= (int*) malloc(n*sizeof(int));
if(vetor==NULL){printf("Falta memoria"); exit(1);}

caminho= (int*) malloc((fim+1)*sizeof(int));
if(caminho==NULL){printf("Falta memoria"); exit(1);}
puts(cadeia);
vetor[0]=1;
imprimir_caminhos(vetor, 1, 0, fim, cadeia, grafo);


return 0;
}


void inserir_grafo(Lista **g, int origem, int destino, char custo){
g[origem]=inserir_lista(g[origem], destino, custo);
}

Lista* inserir_lista(Lista *l, int d, char c){
Lista* no=(Lista*)malloc(sizeof(Lista));
no->destino=d;
no->custo=c;
no->prox=l;
return no;
}

void imprime(Lista **g, int n){
int i;
for(i=1;i<=n;i++)
    {
    printf("\n%d", i);
    imprime_lista(g[i]);
    }
}

void imprime_lista(Lista*l){
if(l!=NULL)
    {
    printf("-> %d | %c\t", l->destino, l->custo);
    imprime_lista(l->prox);
    }
}

void imprimir_caminhos(int* vet, int estado_atual, int pos_cadeia, int fim, char* cadeia, Lista**g){
printf("\nTeste 1: fim= %d, estado_atual= %d, vet[estado atual -1]= %d, pos cadeia= %d, cadeia= %c\n", fim, estado_atual, vet[estado_atual-1], pos_cadeia, cadeia[pos_cadeia]);
int i; //teste
if((pos_cadeia -1) == fim)
    {

    if(vet[estado_atual-1] < 0)
        {
        printf("cadeia aceita");

        for(i=0;i<=fim+1; i++)
            {

            printf(" %d ", vet[i]);
           // caminho[i]=vet[i];
            }

printf("\nTeste 2: fim= %d, estado_atual= %d, pos cadeia= %d, cadeia= %c\n", fim, estado_atual, pos_cadeia, cadeia[pos_cadeia]);
        }
    }
else
    {
    Lista*l = g[vet[estado_atual-1]];  // cria lista (percorrer caminhos que estado atual podem levar)
    while(l!=NULL)
        {
        printf("teste cadeia &c", cadeia[pos_cadeia]);
        if(cadeia[pos_cadeia]==l->custo);
            { printf(" custo %c ",l->custo);
            vet[estado_atual]=l->destino;
            imprimir_caminhos(vet, estado_atual+1, pos_cadeia+1, fim, cadeia, g);

            }
        l=l->prox;
        }
    }
}
