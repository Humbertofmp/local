#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct arvore{
    int info;
    struct arvore* esq;
    struct arvore* dir;
}arvore;

void menu();
void menu2();
arvore* cria(arvore* a, FILE* arq);
void imprime_entre(arvore* a);
int altura(arvore*a);
void imprime_arquivo(arvore* a);
arvore* libera (arvore* a);
arvore* inserir(arvore* a, int x);
arvore* remover(arvore* a, int x);
int ordenada(arvore*a, int pai, char controle);
int maior(arvore*a, int aux); //aux para iniciar a função com algum valor que exista na arvore (raiz)
int menor(arvore*a, int aux);
void imprime_entre_xy(arvore* a, int x, int y);
void imprime_menores_ou_maiores(arvore* a, int x, int y);
arvore* balancear(arvore* a);
int balanceada(arvore*a);

int main()
{
    int x=0, sc=0, i, aux;
    arvore* arv=NULL;
    FILE* arquivo;
    char nome_arquivo[30];

    while(sc!= 13)
        {
        system("cls");
        menu();
        scanf("%d", &sc);
        switch(sc)
            {
            case 1:
                    system("cls");
                    printf("\n\nDigite o nome do arquivo\n\n");
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
                    aux=ordenada(arv, arv->info, 'n');
                        if(aux==1)
                            {
                            printf("\nArvore Ordenada ");
                            }
                        else
                            {
                            printf("\nArvore Nao Ordenada ");
                            }
                    aux=balanceada(arv);
                    if(aux==1)
                        {
                        printf("\nBalanceada");
                        fflush(stdin);
                        getchar();
                        }
                    else
                        {
                        printf("\n\nNao balanceada");
                        fflush(stdin);
                        getchar();
                        }
                    break;
            case 2:
                    menu2();
                    fflush(stdin);
                    scanf("%d", &sc);
                    switch(sc)
                        {

                        case 1:
                                printf("\n\n");
                                imprime_entre(arv);
                                fflush(stdin);
                                getchar();
                                break;
                        case 2:
                                imprime_arquivo(arv);
                                fflush(stdin);
                                getchar();
                                fclose(arquivo);
                                break;
                        }
                    x=0;
                    break;

            case 3:
                    printf("\n\n%d", altura(arv));
                    fflush(stdin);
                    getchar();
                    break;
            case 6:
                    if(arv==NULL)
                        {
                        printf("\n\nArvore vazia");
                        fflush(stdin);
                        getchar();
                        }
                    else
                        {
                        aux=ordenada(arv, arv->info, 'n');
                        if(aux==1)
                            {
                            printf("\nOrdenada ");
                            fflush(stdin);
                            getchar();
                            }
                        else
                            {
                            printf("\nNao Ordenada ");
                            fflush(stdin);
                            getchar();
                            }
                        }
                    break;
            case 7:
                    printf("\n\nDigite o elemento: ");
                    scanf("%d", &x);
                    inserir(arv, x);
                    if(!balanceada(arv))
                        {
                        printf("\nArvore desbalanceada ao inserir o elemento!\n");
                        balancear(arv);
                        fflush(stdin);
                        getchar();
                        printf("\n\nArvore balanceada agora!");
                        fflush(stdin);
                        getchar();
                        }
                    break;
            case 8:
                    printf("\n\nDigite o elemento: ");
                    scanf("%d", &x);
                    remover(arv, x);
                    if(!balanceada(arv))
                        {
                        printf("\nArvore desbalanceada ao remover o elemento!\n");
                        balancear(arv);
                        fflush(stdin);
                        getchar();
                        printf("\n\nArvore balanceada agora!");
                        fflush(stdin);
                        getchar();
                        }
                    break;
            case 9:
                    printf("Digite os valores x e y\n");
                    scanf("%d %d", &x, &i);
                    imprime_entre_xy(arv, x, i);
                    fflush(stdin);
                    getchar();
                    break;
            case 10:
                    printf("Digite os valores x e y\n");
                    scanf("%d %d", &x, &i);
                    imprime_menores_ou_maiores(arv, x, i);
                    fflush(stdin);
                    getchar();
                    break;
            case 11:
                    balancear(arv);
                    break;
            case 12:
                    aux= balanceada(arv);
                    if(aux==1)
                        {
                        printf("\nBalanceada");
                        fflush(stdin);
                        getchar();
                        }
                    else
                        {
                        printf("Nao balanceada");
                        fflush(stdin);
                        getchar();
                        }
                    break;
            case 13:
                    libera(arv);
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
5-Contar numero de ocorrencias de um determinado elemento\n\
6-Verificar se a arvore é ordenada\n\
7-Inserir elemento\n\
8-Remover elemento\n\
9-Imprime elemento maior que x e menor que y\n\
10-Imprime elemento menor que x ou maior que y\n\
11-Balancear\n\
12-Verificar se esta balanceada\n\
13-Sair\n\n");
}

void menu2(){
system("cls");
printf("1-Em ordem\n\
2-Notação de arquivo\n\n");
}

arvore* cria(arvore* a, FILE* arq){
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
    a= (arvore*) malloc(sizeof(arvore));
    if(a==NULL){printf("Falta memoria");exit(1);}
    a->info=x;
    a->esq= cria(a->esq, arq);
    a->dir= cria(a->dir, arq);
    }
fscanf(arq, "%c", &ch);
return a;
}

void imprime_entre(arvore* a){
if(a!=NULL)
    {
    imprime_entre(a->esq);
    printf("% d ", a->info);
    imprime_entre(a->dir);
    }
}

int altura(arvore*a){
if(a==NULL)
    {
    return 0;
    }
else
    {
    int he, hd;
    he= altura(a->esq);
    hd= altura(a->dir);
    if(he>hd)
        {
        return he+1;
        }
    else
        {
        return hd+1;
        }
    }
}

void imprime_arquivo(arvore* a){
if(a==NULL)
	{
	printf("(-1)");
	}
else
	{
	printf("(%d", a->info);
	imprime_arquivo(a->esq);
	imprime_arquivo(a->dir);
	printf(")");
	}
}

arvore* libera (arvore* a){
if (a!=NULL){
libera(a->esq);
libera(a->dir);
free(a);
}
return NULL;
}

arvore* inserir(arvore*a, int x){

if(a==NULL)
    {
    a= (arvore*) malloc(sizeof(arvore));
    if(a==NULL){printf("falta memoria"); exit(1);}
    a->info= x;
    a->esq=NULL;
    a->dir=NULL;
    }
else
    {
    if(x < a->info)
        {
        a->esq= inserir(a->esq, x);
        }
    else
        {
        a->dir=inserir(a->dir, x);
        }
    }
return a;
}

arvore* remover(arvore* a, int x){
if(a!=NULL)
    {
    if(a->info==x)
        {
        if((a->esq==NULL) && (a->dir==NULL))
            {
            free(a);
            return NULL;
            }
        else if((a->esq == NULL) || (a->dir == NULL))
                {
                arvore* aux;
                if(a->esq==NULL)
                    aux= a->dir;
                else
                    aux=a->esq;
                free(a);
                return aux;
                }
            else
                {
                arvore* m = a->esq;
                while(m->dir!=NULL)
                    {
                    m=m->dir;
                    }
                a->info= m->info;
                a->esq= remover(a->esq, m->info);
                return a;
                }
            }
            else if(x < a->info)
                {
                    a->esq=remover(a->esq, x);
                }
            else
                {
                a->dir=remover(a->dir, x);
                }
        }
return a;
}

int maior(arvore*a, int aux){
if(a!=NULL)
    {
    aux=maior(a->esq, aux);
    aux=maior(a->dir, aux);
    if(a->info > aux)
        {
        return a->info;
        }
    else
        {
        return aux;
        }
    }
return aux;
}

int menor(arvore*a, int aux){
if(a!=NULL)
    {
    aux=menor(a->esq, aux);
    aux=menor(a->dir, aux);
    if(a->info < aux)
        {
        return a->info;
        }
    else
        {
        return aux;
        }
    }
return aux;
}

int ordenada(arvore*a, int pai, char controle){ // na main: (arv, a->info(se existir), a->info)
int r=1;
if(a!=NULL)
   {
    if((maior(a->esq, a->info) > a->info) || (menor(a->dir, a->info) < a->info))
        {
        return 0;
        }
    else
        {
        r= r* ordenada(a->esq, a->info, 'e');
        if(controle=='e')
            {
            controle='n';
            if((a->info > pai))
                {
                return 0;
                }
            }
        else if(controle=='d')
            {
            controle='n';

             if((a->info < pai) || (a->info == pai))
                {
                return 0;
                }
            }
        r= r* ordenada(a->dir, a->info, 'd');
        }
    }
return r;
}

void imprime_entre_xy(arvore* a, int x, int y){
if(a!=NULL)
    {
    if(a->info < x)
        {
        imprime_entre_xy(a->dir, x, y);
        }
    else if(a->info > y)
        {
        imprime_entre_xy(a->esq, x, y);
        }
    else
        {
        imprime_entre_xy(a->esq, x, y);
        printf("%d ", a->info);
        imprime_entre_xy(a->dir, x, y);
        }
    }
}

void imprime_menores_ou_maiores(arvore* a, int x, int y)
{
if(a!=NULL)
   {
    imprime_menores_ou_maiores(a->esq, x, y);
    if((a->info < x ) || (a->info > y))
        {
        printf("%d ", a->info);
        }
    imprime_menores_ou_maiores(a->dir, x, y);
   }
}

arvore* balancear(arvore* a){
if(a!=NULL)
    {
    int he, hd;
    a->esq= balancear(a->esq);
    a->dir= balancear(a->dir);
    he= altura(a->esq);
    hd= altura(a->dir);
    if(hd - he > 1)
        {
        int x;
        arvore* aux= a->dir;
        while(aux->esq!=NULL)
            {
            aux=aux->esq;
            }
        x= a->info;
        a->info= aux->info;
        a->dir= remover(a->dir, aux->info);
        a->esq= inserir(a->esq, x);
        a=balancear(a);
        }
    else if(he - hd > 1)
        {
        int x;
        arvore* aux= a->esq;
        while(aux->dir!=NULL)
            {
            aux=aux->dir;
            }
        x= a->info;
        a->info= aux->info;
        a->esq= remover(a->esq, aux->info);
        a->dir= inserir(a->dir, x);
        a=balancear(a);
        }
    }
return a;
}

int balanceada(arvore*a){
int r=1, he, hd;
if(a!=NULL)
    {
    r=r* balanceada(a->esq);
    r=r* balanceada(a->dir);
    he= altura(a->esq);
    hd= altura(a->dir);
    if((he-hd > 1) || (he-hd < -1))
        return 0;
    }
return r;
}
