#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 15

typedef struct placa{
    char letras[3];
    int digitos;
} Placa;

typedef struct carro{
    int renavan;
    Placa pl;
    char modelo[50];
    int potencia;
}Carro;

typedef struct moto{
    Placa pl;
    int km;
    char cor[15];
}Moto;

typedef struct veiculo{
    char tipo[5];
    void* info;
    struct veiculo* prox;
}Veiculo;

void menu();
void inicializar(Veiculo* vet);
Veiculo* inserir_lista(Veiculo* l);
void imprimir(Veiculo* v);
Veiculo* remover(Veiculo* v, Placa p);
int vazia(Veiculo *l);
int contar_moto_cor(Veiculo* v, char* cor);
void carro_potente(Veiculo* v);
void destruir(Veiculo* v);

int main()
{
int sc=0, r;
char cor[12];
Placa aux;
Veiculo *lista=NULL;
inicializar(lista);

while(sc!=6)
    {
    system("cls");
    menu();
    fflush(stdin);
    scanf("%d", &sc);
    switch(sc)
        {
        case 1:
                lista=inserir_lista(lista);
                break;
        case 2:
                r=vazia(lista);
                if(r==0)
                    {
                    printf("\nDigite a placa do veiculo a ser removido(separar com espaco as letras dos numeros)");
                    fflush(stdin);
                    scanf("%s %d", aux.letras, &aux.digitos);
                    lista=remover(lista, aux);
                    }
                else
                    {
                    fflush(stdin);
                    getchar();
                    }
                break;
        case 3:
                r=vazia(lista);
                if(r==0)
                    {
                    imprimir(lista);
                    }
                fflush(stdin);
                getchar();

                break;
        case 4:
                printf("\nDigite a cor: ");
                fflush(stdin);
                gets(cor);
                r=contar_moto_cor(lista, cor);
                printf("\n%d moto[s] ", r);
                fflush(stdin);
                getchar();
                break;
        case 5:
                if(vazia(lista)==0)
                    {
                    carro_potente(lista);
                    }
                fflush(stdin);
                getchar();
                break;
        case 6:
                destruir(lista);
                break;
        }
    }
    return 0;
}

void menu(){
printf("Menu:\n\n\
1-Inserir um veiculo\n\
2-Remover um veiculo\n\
3-Imprimir lista\n\
4-Contar as motos de uma determinada cor\n\
5-Imprimir carro de  maior potencia\n\
6-Sair\n\n");
}

void inicializar(Veiculo* lista){
lista=(Veiculo*) malloc(sizeof(Veiculo));
if(lista==NULL){printf("FALTA MEMORIA"); exit(1);}
}

Veiculo* inserir_lista(Veiculo* l){
char t[5];
Veiculo *v;

v=(Veiculo*) malloc(sizeof(Veiculo));
if(v==NULL){printf("FALTA MEMORIA"); exit(1);}
v->prox=l;
printf("\n\nDigite carro ou moto: ");
fflush(stdin);
gets(t);

if(strcmp(t, "carro")==0)
    {
    //inserir um carro na lista
    Carro* c=(Carro*)malloc(sizeof(Carro));
    if(c==NULL){printf("FALTA MEMORIA"); exit(1);}
    printf("\nDigite o renavan: ");
    scanf("%d", &c->renavan);
    printf("\nDigite a placa (separar letras e digito com espaco): ");
    scanf("%s %d", c->pl.letras, &c->pl.digitos);
    printf("\nDigite o modelo: ");
    scanf("%s", c->modelo);
    printf("\nDigite a potencia: ");
    scanf("%d", &c->potencia);

    strcpy(v->tipo , t);
    v->info= (void*) c;
    }
else if(strcmp(t, "moto")==0)
    {
    //inserir uma moto na lista
    Moto* m=(Moto*)malloc(sizeof(Moto));
    if(m==NULL){printf("FALTA MEMORIA"); exit(1);}
    printf("\nDigite a placa (separar letras e digito com espaco): ");
    scanf("%s %d", m->pl.letras, &m->pl.digitos);
    printf("\nDigite a cor: ");
    scanf("%s", m->cor);
    printf("\nDigite a quilometragem: ");
    scanf("%d", &m->km);

    strcpy(v->tipo, t);
    v->info= (void*) m;
    }
return v;
}

void imprimir(Veiculo* v){
if(v!=NULL)
    {
    printf("\n");
    if(strcmp(v->tipo, "carro")==0)
        {
        printf("Carro");
        Carro* c= (Carro*)v->info;
        printf("\nrenavan %d\nplaca %s %d\nmodelo %s\npotencia %d\n", c->renavan, c->pl.letras, c->pl.digitos, c->modelo, c->potencia);
        }
    if(strcmp(v->tipo, "moto")==0)
        {
        printf("Moto");
        Moto* m=(Moto*) v->info;
        printf("\nplaca %s %d\nkm %d\ncor %s\n", m->pl.letras, m->pl.digitos, m->km, m->cor);
        }
    imprimir(v->prox);
    }
}

Veiculo* remover(Veiculo* v, Placa p)
{
if(v!=NULL)
    {
    if(strcmp(v->tipo, "carro")==0)
        {
        Carro *aux=(Carro*) v->info;
        if(p.digitos==aux->pl.digitos)
            {
            if(strcmp(p.letras, aux->pl.letras)==0)
                {
                Veiculo *temp= v->prox;
                v->info=NULL;
                free(v);
                return temp;
                }
            }
        }
    else if(strcmp(v->tipo, "moto")==0)
        {
        Moto *aux=(Moto*) v->info;
        if(p.digitos==aux->pl.digitos)
            {
            if(strcmp(p.letras, aux->pl.letras)==0)
                {
                Veiculo *temp= v->prox;
                v->info=NULL;
                free(v);
                return temp;
                }
            }
        }
    v->prox=remover(v->prox, p);
    }
return v;
}

int vazia(Veiculo *l){
if(l==NULL)
    {
    printf("\nLista vazia!\n");
    return 1;
    }
else
    return 0;
}

int contar_moto_cor(Veiculo* v, char* cor){
int cont=0;
Veiculo *aux;

aux=v;

while(aux!=NULL)
    {
    if(strcmp(aux->tipo, "moto")==0)
        {
        Moto* m= (Moto*)aux->info;
        if(strcmp(m->cor, cor)==0)
            {
            cont++;
            }
        }
    aux=aux->prox;
    }
return cont;
}

void carro_potente(Veiculo* v)
{
Veiculo *aux;
Carro *potente;

potente=(Carro*) malloc(sizeof(Carro));
if(potente==NULL){printf("FALTA MEMORIA"); exit(1);}

potente->potencia=0;

aux=v;

while(aux!=NULL)
    {
    if(strcmp(aux->tipo, "carro")==0)
        {
        Carro *c= (Carro*)aux->info;
        if(c->potencia > potente->potencia)
            {
            strcpy(potente->pl.letras, c->pl.letras);
            potente->pl.digitos=c->pl.digitos;
            potente->renavan= c->renavan;
            potente->potencia= c->potencia;
            strcpy(potente->modelo, c->modelo);
            }
        }
    aux=aux->prox;
    }
printf("\nplaca: %s %d", potente->pl.letras, potente->pl.digitos);
printf("\npotencia: %d", potente->potencia);
free(potente);
}

void destruir(Veiculo* v){
if(v!=NULL)
    {
    destruir(v->prox);
    free(v->info);
    free(v);
    }
}
