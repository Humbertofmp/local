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
void imprime_pre(arvore* a);
void imprime_entre(arvore* a);
void imprime_pos(arvore* a);
void imprime_nivel(arvore* a, int nivel, int cont);
int altura(arvore*a);
void imprime_arquivo(arvore* a);
//FUNÇÃO DESABILITADA void imprime_arquivo(arvore* a, FILE* arq);
int existe(arvore* a, int x);
int contar(arvore*a, int x, int cont);
arvore* libera (arvore* a);
void imprime_folhas(arvore*a);
int contar_no(arvore* a, int cont);
int nivel(arvore*a, int x, int n);
int contar_no_nivel(arvore* a, int n, int cont, int no);
int cheia(arvore* a);
arvore* inserir(arvore* a, int x);
arvore* remover(arvore* a, int x);
int ordenada(arvore*a, int pai, char controle);
int maior(arvore*a, int aux); //aux para iniciar a função com algum valor que exista na arvore (raiz)
int menor(arvore*a, int aux);
void imprime_entre_xy(arvore* a, int x, int y);
void imprime_menores_ou_maiores(arvore* a, int x, int y);
arvore* balancear(arvore* a);
int balanceada(arvore*a);
void prova1(arvore* a, int b);

int main()
{
    int x=0, sc=0, i, aux, controle_arquivo=0;
    arvore* arv=NULL;
    FILE* arquivo;
    char nome_arquivo[30];

    while(sc!= 17)
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
                    controle_arquivo=1;
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
                                imprime_pre(arv);
                                fflush(stdin);
                                getchar();
                                break;
                        case 2:
                                printf("\n\n");
                                imprime_entre(arv);
                                fflush(stdin);
                                getchar();
                                break;
                        case 3:
                                printf("\n\n");
                                imprime_pos(arv);
                                fflush(stdin);
                                getchar();
                                break;
                        case 4:
                                aux=altura(arv);
                                printf("\n\n");
                                for(i=0; i<=aux; i++)
                                    {
                                    imprime_nivel(arv, i, 0);
                                    printf("\n\n");
                                    }
                                fflush(stdin);
                                getchar();
                                break;
                        case 5:
                         /*      if(controle_arquivo==1)
                                    {
                                    system("cls");
                                    arquivo= fopen(nome_arquivo, "r");
                                    if(!arquivo)
                                        {
                                        printf("\n\nErro na abertura do arquivo");
                                        exit(1);
                                        }
                //////////////////  imprime_arquivo(arv, arquivo); *///////////////////////
                                    imprime_arquivo(arv);
                                    fflush(stdin);
                                    getchar();
                                    fclose(arquivo);
                /////////////////////////////////////////////
                /*
                                else
                                    {
                                    printf("\nNenhuma arvore foi criada");///////////////////
                                    fflush(stdin);
                                    getchar();
                                    } */
                                break;
                        }
                    x=0;
                    break;
            case 3:
                    x=-1;
                    system("cls");
                    printf("\n\nDigite o elemnto\n\n");
                    fflush(stdin);
                    scanf("%d", &x);
                    aux=existe(arv, x);
                    if(aux==0)
                        {
                        printf("\n\nElemento não existe");
                        }
                    else
                        {
                        printf("\n\nExiste");
                        }
                    fflush(stdin);
                    getchar();
                    break;
            case 4:
                    printf("\n\n%d", altura(arv));
                    fflush(stdin);
                    getchar();
                    break;
            case 5:
                    x=-1;
                    system("cls");
                    printf("\n\nDigite o elemento\n\n");
                    fflush(stdin);
                    scanf("%d", &x);
                    aux=contar(arv, x, 0);
                    printf("\n\nNumero de elementos x=%d: %d", x, aux);
                    fflush(stdin);
                    getchar();
                    break;
            case 6:
                    imprime_folhas(arv);
                    fflush(stdin);
                    getchar();
                    break;
            case 7:
                    aux=contar_no(arv,0);
                    printf("\n\n%d", aux);
                    fflush(stdin);
                    getchar();
                    break;
            case 8:
                    printf("\nDigite o elemento ");
                    scanf("%d", &x);
                    aux=nivel(arv, x, 1);
                    if(aux==0) //comando para continuar buscando por elementos repetidos. caso não encontre o retorno será = 0
                        {
                        printf("\n\nNenhuma ocorrencia encontrada");
                        }
                    else
                        {
                        printf("\n\nNivel %d", aux);
                        }
                    fflush(stdin);
                    getchar();
                    break;
            case 9:
                    aux=cheia(arv);
                    if(aux==1)
                        printf("\n\nCheia");
                    else
                        printf("\n\nNao cheia");

                    fflush(stdin);
                    getchar();
                    break;
            case 10:
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
            case 11:
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
            case 12:
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

            case 13:
                    printf("Digite os valores x e y\n");
                    scanf("%d %d", &x, &i);
                    imprime_entre_xy(arv, x, i);
                    fflush(stdin);
                    getchar();
                    break;
            case 14:
                    printf("Digite os valores x e y\n");
                    scanf("%d %d", &x, &i);
                    imprime_menores_ou_maiores(arv, x, i);
                    fflush(stdin);
                    getchar();
                    break;
            case 15:
                    balancear(arv);
                    break;
            case 16:
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
            case 17:
                    libera(arv);
                    break;
            case 18:
                    printf("\nDigite b: ");
                    fflush(stdin);
                    scanf("%d", &x);
                    prova1(arv, x);
                    fflush(stdin);
                    getchar();
                    break;
            }
        }
    return 0;
    }

void menu(){

printf("Menu:\n\n\
1-Ler arquivo\n\
2-Imprimir\n\
3-Verificar se um elemento existe\n\
4-Calcular altura\n\
5-Contar numero de ocorrencias de um determinado elemento\n\
6-Imprimir folhas\n\
7-Contar numero de nos internos\n\
8-Verificar o nivel de um no\n\
9-Verificar se a arvore e cheia\n\
10-Verificar se a arvore é ordenada\n\
11-Inserir elemento\n\
12-Remover elemento\n\
13-Imprime elemento maior que x e menor que y\n\
14-Imprime elemento menor que x ou maior que y\n\
15-Balancear\n\
16-Verificar se esta balanceada\n\
17-Sair\n\
18-Questao 1 da prova\n");

}

void menu2(){
system("cls");
printf("1-Pre ordem\n\
2-Em ordem\n\
3 Pos ordem\n\
4-Em largura\n\
5-Notação de arquivo\n\n");
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

void imprime_pre(arvore* a){
if(a!=NULL)
    {
    printf("% d ", a->info);
    imprime_pre(a->esq);
    imprime_pre(a->dir);
    }
}

void imprime_entre(arvore* a){
if(a!=NULL)
    {
    imprime_entre(a->esq);
    printf("% d ", a->info);
    imprime_entre(a->dir);
    }
}

void imprime_pos(arvore* a){
if(a!=NULL)
    {
    imprime_pos(a->esq);
    imprime_pos(a->dir);
    printf("% d ", a->info);
    }
}

void imprime_nivel(arvore* a, int nivel, int cont){
if(a!=NULL)
    {
    if( cont==nivel)
        {
        printf("%d ", a->info);
        }
    else
        {
        imprime_nivel(a->esq, nivel, cont+1);
        imprime_nivel(a->dir, nivel, cont+1);
        }
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

/* FUNÇÃO DESABILITADA
void imprime_arquivo(arvore* a, FILE* arq){
int x;
char ch;

fscanf(arq, "%c", &ch);
printf("%c", ch);
fscanf(arq, "%d", &x);
printf("%d", x);
if(x!=-1)
    {
    imprime_arquivo(a->esq, arq);
    imprime_arquivo(a->dir, arq);
    }
fscanf(arq, "%c", &ch);
printf("%c", ch);
}
*/
int existe(arvore* a, int x){
if(a==NULL)
    {
   return 0;
    }
else
    {
    if(a->info== x)
        {
        return 1;
        }
    else
        {
        if(x > a->info)
            {
            return existe(a->dir, x);
            }
        else
            {
            return existe(a->esq, x);
            }
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

int contar(arvore*a, int x, int cont){
if(a!=NULL)
    {
    cont=contar(a->esq, x, cont);
    cont=contar(a->dir, x, cont);
    if(a->info==x)
        {
        return cont + 1;
        }
    }
return cont;
}

arvore* libera (arvore* a){
if (a!=NULL){
libera(a->esq);
libera(a->dir);
free(a);
}
return NULL;
}

void imprime_folhas(arvore* a){
if(a!=NULL)
    {
    imprime_folhas(a->esq);
    imprime_folhas(a->dir);
    if((a->esq==NULL) && (a->dir==NULL))
        {
        printf("% d ", a->info);
        }
    }
}

int contar_no(arvore* a, int cont){
if(a!=NULL)
    {
    cont=contar_no(a->esq, cont);
    cont=contar_no(a->dir, cont);
    if((a->esq!=NULL) || (a->dir!=NULL))
        {
        return cont+1;
        }
    }
return cont;
}

int nivel(arvore*a, int x, int n){
int aux=0;
char c='s';
if(a!=NULL)
    {
    if(a->info==x)
        {
        printf("\n\nOcorrencia do elemento encontrada no nivel %d. \nContinuar procurando? s/n: ", n);
        fflush(stdin);
        scanf("%c", &c);
        if(c=='n' || c=='N')
            {
            return n;
            }
        }
        if(c=='s'|| c=='S')
        {
        aux=nivel(a->esq, x, n+1);
        if(aux>0)
            {
            return aux;
            }
        else
            {
            aux=nivel(a->dir, x, n+1);
            return aux;
            }
        }
    }
return aux;
}

int contar_no_nivel(arvore* a, int n, int cont, int no){
if(a!=NULL)
    {
    if(cont==n)
    {
    return no+1;
    }
    else
        {
        no=contar_no_nivel(a->esq, n, cont+1, no);
        no=contar_no_nivel(a->dir, n, cont+1, no);
        }
    }
return no;
}

int cheia(arvore*a){

int pot, nivel,h;
h=altura(a);
printf("\n----altura= %d", h);
pot=pow(2, h-1);
printf("\n----potencia(2^h-1)= %d", pot);
nivel=contar_no_nivel(a, h, 1, 0);
printf("\n----quantidade de nos no ultimo nivel= %d", nivel);
if(pot==nivel)
    {
    return 1;
    }
return 0;
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

void prova1(arvore* a, int b)
{
if(a!=NULL)
    {
    if(a->info >= b)
        {
        prova1(a->esq, b);
        }
    else
        {
        if((a->esq == NULL) && (a->dir ==NULL))
            {
            printf("%d ", a->info);
            }
        else
            {
            prova1(a->esq, b);
            prova1(a->dir, b);
            }
        }
    }
}
