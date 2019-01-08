#include <stdio.h>
#include <stdlib.h>

typedef struct arvoregeral{
    int info;
    struct arvoregeral *filho;
    struct arvoregeral *irmao;
}ag;

ag* cria(ag* a, FILE* arq);
void menu();
void menu2();
void imprime_arquivo(ag* a);
void imprime_nivel(ag* a, int nivel, int cont);
void imprime_largura(ag* a);
ag* libera (ag* a);
int altura(ag* a);
int contar_folhas(ag* a);
void imprime_no_interno(ag* a);
int nivel_no(ag* a, int x, int cont);
int existe(ag* a, int x);
ag* insere(ag* a, int x, int y, int* s);
ag* remove_y(ag* a, int y);

int main()
{
   int sc=0, aux, x, y, sair=0;
    ag* arv=NULL;
    FILE* arquivo;
    char nome_arquivo[30];

    while(sc!= 8)
        {
        system("cls");
        menu();
        scanf("%d", &sc);
        switch(sc)
            {
            case 1:
                    system("cls");
                    printf("\nDigite o nome do arquivo\n\n");
                    fflush(stdin);
                    gets(nome_arquivo);
                    arquivo= fopen(nome_arquivo, "r");
                    if(!arquivo)
                        {
                        printf("\n\nErro na abertura do arquivo");
                        fflush(stdin);
                        getchar();
                        break;
                        }
                    arv= cria(arv, arquivo);
                    fclose(arquivo);

                    break;

            case 2:
                    menu2();
                    fflush(stdin);
                    scanf("%d", &sc);
                    switch(sc)
                        {
                        case 1:
                                printf("\n\n");
                                imprime_arquivo(arv);
                                fflush(stdin);
                                getchar();
                                break;
                        case 2:
                                imprime_largura(arv);
                                fflush(stdin);
                                getchar();
                                fclose(arquivo);
                                break;
                        }
                    break;
            case 3:
                    aux=altura(arv);
                    printf("\n%d ", aux);
                    fflush(stdin);
                    getchar();
                    break;

            case 4:
                    aux=contar_folhas(arv);
                    printf("\n%d ", aux);
                    fflush(stdin);
                    getchar();
                    break;

            case 5:
                    imprime_no_interno(arv);
                    fflush(stdin);
                    getchar();
                    break;

            case 6:
                    printf("\ndigite o no ");
                    fflush(stdin);
                    scanf("%d", &x);
                    aux=nivel_no(arv, x, 1);
                    printf("---%d--- ", aux);
                    fflush(stdin);
                    getchar();
                    break;
            case 7:
                    printf("\nDigite os elementos X e Y\n");
                    fflush(stdin);
                    scanf("%d %d", &x, &y);
                    if(existe(arv, y))
                        {
                        arv=insere(arv, x, y, &sair);
                        printf("\nElemento inserido");
                        fflush(stdin);
                        getchar();
                        }
                    else
                        {
                        printf("No y não existe na arvore");
                        }
                    sair=0;
                    break;

            case 8:
                    arv=libera(arv);

                    break;

            }
        }
    return 0;
}

void menu(){
printf("Menu:\n\n\
1-Ler arquivo\n\
2-Imprimir\n\
3-Calcular altura\n\
4-Contar numero de folhas\n\
5-imprimir nos internos\n\
6-imprimir nivel de um no\n\
7-Inserir no x como filho de y\n\
8-Sair\n\n");
}

void menu2(){
system("cls");
printf("1-Notação de arquivo\n\
2-Em largura\n\n");
}


ag* cria(ag* a, FILE* arq){
int x;
char ch;

fscanf(arq, "%c", &ch);
fscanf(arq, "%d", &x);
if(x==-1)
    {
    a=NULL;
    }
else
    {
    a= (ag*) malloc(sizeof(ag));
    if(a==NULL){printf("Falta memoria");exit(1);}
    a->info=x;
    a->filho= cria(a->filho, arq);
    a->irmao= cria(a->irmao, arq);
    }
fscanf(arq, "%c", &ch);
return a;
}


void imprime_arquivo(ag* a){
if(a==NULL)
	{
	printf("(-1)");
	}
else
	{
	printf("(%d", a->info);
	imprime_arquivo(a->filho);
	imprime_arquivo(a->irmao);
	printf(")");
	}
}

void imprime_nivel(ag* a, int nivel, int cont){
if(a!=NULL)
    {
        if(cont==nivel)
            {
            printf("%d ", a->info);
            imprime_nivel(a->irmao, nivel, cont);
            }
        else
            {
            imprime_nivel(a->filho, nivel, cont+1);
            imprime_nivel(a->irmao, nivel, cont);
            }
    }
}

void imprime_largura(ag* a){
int i, aux;
aux= altura(a);
for(i=0; i<=aux; i++)
    {
    imprime_nivel(a, i, 1);
    printf("\n");
    }
}

ag* libera (ag* a){
if (a!=NULL){
libera(a->filho);
libera(a->irmao);
free(a);
}
return NULL;
}

int altura(ag* a){
int hf=0, hi=0;
if(a==NULL)
    {
    return 0;
    }
else
    {
    hf=altura(a->filho)+1;
    hi=altura(a->irmao);

    if(hf>hi)
        {
        return hf;
        }
    else
        {
        return hi;
        }
    }
}

int contar_folhas(ag* a){
if(a==NULL)
    {
    return 0;
    }
else
    {
    if(a->filho == NULL)
        {
        return 1+ contar_folhas(a->irmao);
        }
    else
        {
        return contar_folhas(a->filho)+ contar_folhas(a->irmao);
        }
    }
}

void imprime_no_interno(ag* a){
if(a!=NULL)
    {
    if(a->filho!=NULL)
        {
        printf("%d ", a->info);
        }
    imprime_no_interno(a->filho);
    imprime_no_interno(a->irmao);
    }
}

int nivel_no(ag* a, int x, int cont){
int aux=0;
if(a!=NULL)
    {
    if(a->info == x)
        {
        return cont;
        }
    else
        {
        aux= nivel_no(a->irmao, x, cont);
        if(aux==0)
            {
            aux= nivel_no(a->filho, x, cont+1);
            }
        }
    }

return aux;
}

int existe(ag* a, int x){
if(a!=NULL)
    {
    if(a->info == x)
        {
        return 1;
        }
    else
        {
        return (existe(a->irmao, x) + existe(a->filho, x));
        }
    }
return 0;
}

ag* insere(ag* a, int x, int y, int* s){
if(a!=NULL)
    {
    if(a->info== y)
        {
        ag* aux;
        aux= (ag*) malloc(sizeof(ag));
        if(aux==NULL){printf("Falta memoria");exit(1);}
        aux->info = x;
        aux->irmao = a->filho;
        a->filho = aux;
        aux->filho=NULL;
        printf("------teste1-----");
        *s = 1;
        printf("------teste2-----");
        return a;
        }
    else
        {
        if(*s==0)
            { printf("------teste3-----");
            a->irmao=insere(a->irmao, x, y, s);
            }
        if(*s==0)
            {
                printf("------teste4-----");
            a->filho=insere(a->filho, x, y, s);
            }
        }
    }printf("------teste5-----");
return a;
}

ag* remove_y(ag* a, int y){
if(a!=NULL)
    {
    a->filho=remove_y(a->filho, y);
    a->irmao=remove_y(a->irmao, y);

    if((a->info==y) &&(a->filho==NULL))
        {
        ag* aux= a->irmao;
        free(a);
        return aux;
        }
    else if((a->info==y) && (a->filho!=NULL))
        {

        }
    }
}
