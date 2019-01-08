//Lz77
//Humberto F. M. Pastor
//Leandro Bucci
//Claudio Rodrigues Nunes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define TAMANHO_JANELA 4096
#define TAMANHO_BUFFER 256


//Variaveis globais
int final_janela=0, inicio_janela=0, cheia=0, fim_arquivo=0, fim_buffer=TAMANHO_BUFFER-1, M=TAMANHO_BUFFER, N=TAMANHO_JANELA;


void compara(int* janela, int* buffer, int *tamanho, int *posicao);
//compara o vetor buffer e janela e grava por referencia posição e tamanho da maior repetição do buffer na janela
void buffer_inicializa(int *buffer, FILE* arq);
void buffer_alimenta(int* buffer, int tamanho, FILE* arq);
//ler arquivo para o buffer
int* cria_janela(int tamanho);
void inseri_janela(int* janela, int* aux, int tam);
//função para ler do buffer e salvar na janela (vetor circular-fila)
void convStringByte(uint8_t *byte,char *str);
void convByteString(uint8_t byte,char *str);
void converte_arquivo();
//converte o arquivo original em um arquivo de 0s e 1s
void descomprimir(FILE* arq, FILE* saida);
//le o arquivo contendo as tuplas, salva em uma struct e gera o arquivo original formado por 0s e 1s. Em seguida converte para texto
void taxacomp(FILE* in, FILE* compac);

int main()
{
int opcao=0;
printf("1-Comprimir\n2-Descomprimir\n");
scanf("%d", &opcao);

if(opcao==1)////////////////////////////////COMPRIMIR////////////////////////////
    {
    int posicao=0, tamanho=0, i;
    char nome[50];
    int* janela, *buffer;

    converte_arquivo();
    printf("\nArquivo de 0s e 1s gerado com o nome: temp.txt\n");
    janela=cria_janela(N);
    buffer=(int*) malloc((M)*sizeof(int));

    //printf("Informe o nome do aquivo que sera analisado: ");
    //gets(nome);
    fflush(stdin);
    FILE *arq;
    arq = fopen("temp.txt","rb");
    if(arq==NULL)
        {
        printf("Problemas na ABERTURA do arquivo\n");
        system("pause");
        exit(1);
        }

   // printf("\n\ninforme o nome do arquivo que sera guardado a apuracao: ");
    //scanf("%50s",&nome);
    fflush(stdin);
    FILE *saida;
    saida = fopen("compactado.txt","wb");
    if(saida==NULL) printf("Não foi possivel criar o arquivo!!\n");

    buffer_inicializa(buffer, arq);
    printf("\nCompactando...\n");
    while(fim_buffer>1)
        {

        compara(janela, buffer, &tamanho, &posicao);
        inseri_janela(janela, buffer, tamanho);
        fprintf(saida, "(%d,%d,%d)",  posicao, tamanho,buffer[tamanho]);
        buffer_alimenta(buffer, tamanho, arq);

        posicao=0;
        tamanho=0;
        }
    taxacomp(arq,saida);
    fclose(arq);
    fclose(saida);
    free(janela);
    free(buffer);
    printf("\nFim");
    free(janela);
    free(buffer);
    }
else if(opcao==2)/////////////////////DESCOMPRIMIR/////////////////////////////////////////////////////
    {
    char nome[50];
    fflush(stdin);
    printf("\nInforme o arquivo a ser descompactado\n");
    gets(nome);

    FILE *arq;
    arq = fopen(nome,"r");
    if(arq==NULL)
        {
        printf("Problemas na ABERTURA do arquivo\n");
        system("pause");
        exit(1);
        }

    printf("\n\ninforme o nome do arquivo que sera guardado a apuracao: ");
    scanf("%50s",&nome);
    fflush(stdin);
    FILE *saida;
    saida = fopen("bin.txt","w");
    if(saida==NULL) printf("Não foi possivel criar o arquivo!!\n");
    descomprimir(arq, saida);
    fclose(saida);
    fclose(arq);
    
    }
 return 0;
}


void buffer_inicializa(int *buffer, FILE* arq){
int i=0; char c;

while(i<M)
    {
    if(fscanf(arq, "%c", &c)!=EOF)
        {
        buffer[i]=c - 48;
        i++;
        }
    else
        {
        buffer[i]=c;
        fim_buffer=i;
        }
    }
}

void buffer_alimenta(int* buffer, int tamanho, FILE* arq){
int i=0, j=tamanho+1;
char c;
//////////desloca os numeros do buffer que não passar para a janela a esquerda
for(i=0;i<M-j; i++)
    {
    buffer[i]=buffer[i+j];
    }
fim_buffer= M-j;

//completa o buffer com dados do arquivo
while((!feof(arq)) && (fim_buffer<M))
    {
    fscanf(arq, "%c", &c);
    buffer[fim_buffer]= c - 48;
    fim_buffer++;
    }
if(feof(arq))
    {
    fim_buffer--;
    M=fim_buffer;
    }
if(fim_buffer==M)
    {
    fim_buffer--;
    }
}

int* cria_janela(int tamanho){
int* janela, i;
janela=(int*)malloc (tamanho* sizeof(int));
if(janela==NULL){printf("Falta memoria!");exit(1);}
inicio_janela=0;
for(i=0;i<N;i++)
    {
    janela[i]=-1;
    }
return janela;
}

void inseri_janela(int* janela, int* aux, int tam){
int i=0;
// adiciona o buffer na janela, a partir do final

for(i=0;i<=tam;i++)
    {
    janela[final_janela]=aux[i];
    final_janela=((final_janela +1)%(TAMANHO_JANELA)); //incrementa final com circular (fila)
    cheia++;
    }
    if(cheia>TAMANHO_JANELA)
        inicio_janela=final_janela;
}

void compara(int* janela, int* buffer, int *tamanho, int *posicao){
int i=0, j=0, ponteiro_inicio=inicio_janela, pos=0, pos_maior=0, tam_aux=0, tam_maior=0, guardar;

for(i=0;i<TAMANHO_JANELA;i++)
	{
	j=0;
    guardar=ponteiro_inicio;
    if(janela[ponteiro_inicio]==buffer[j])
        {
        pos=ponteiro_inicio;
        tam_aux=0;
        while((janela[ponteiro_inicio]==buffer[j]) && (j < M-1) && ((i+j)<N))//i+j<N para não dar uma volta na lista
            {
            tam_aux=tam_aux+1;
            ponteiro_inicio= (ponteiro_inicio+1)%N; j++;
            }
        if(tam_aux>tam_maior)
            {
            tam_maior=tam_aux;
            tam_aux=0;
            pos_maior=pos;
            }
        if((tam_aux==tam_maior) && (tam_aux > 0))
            {
                pos_maior=pos;
                tam_aux=0;
            }

        }
    ponteiro_inicio=guardar;
    ponteiro_inicio=(ponteiro_inicio+1)%N;
	}
*tamanho=tam_maior;
*posicao=pos_maior;
}


void convByteString(uint8_t byte,char *str){
strcpy(str,"00000000\0");
int i=0;
while (byte>0)
    {
    if (byte>=128)
        str[i]='1';
    byte = byte<<1;
    i++;
    }
}

void convStringByte(uint8_t *byte,char *str){
int base=1,i;
*byte=0;
for (i=7;i>=0;i--)
    {
    if (str[i]=='1')
        *byte+=base;
    base*=2;
    }
}

void converte_arquivo(){
char nome[128];
char str[9];
FILE* in;
FILE* temp;
uint8_t byte;

printf("Nome do arquivo a ser compactado:\n");
fflush(stdin);
fgets(nome, 128, stdin);
nome[strlen(nome)-1] = '\0';
in = fopen(nome,"rb");
temp = fopen("temp.txt","w");

while(fread(&byte,1,1,in))
    {
    convByteString(byte,str);
    fprintf(temp,"%s",str);
    }

//system("CLS");
printf("Arquivo convertido com sucesso!\n");
fclose(temp);
fclose(in);
}


void descomprimir(FILE* arq, FILE* saida){

typedef struct tupla{
    int p;
	int t;
	int c;
}Tupla;
uint8_t byte;
int janela2[TAMANHO_JANELA];
char lixo[4]; char str[9];
Tupla tp;
int indice_janela=0;
int i;


while(((fscanf(arq, "%c%d%c%d%c%d%c", &lixo[0], &tp.p, &lixo[1], &tp.t, &lixo[2], &tp.c, &lixo[3]))!=EOF))
    {
    if(tp.t>0)
        {
        for(i=0; i<tp.t;i++)
            {
            janela2[indice_janela]=janela2[(tp.p+i)%TAMANHO_JANELA];
            fprintf(saida, "%d", janela2[indice_janela]);
            indice_janela= ((indice_janela +1 )%(TAMANHO_JANELA));
            }
        }

    janela2[indice_janela]= tp.c;
    fprintf(saida, "%d", janela2[indice_janela]);
    indice_janela= ((indice_janela +1 )%(TAMANHO_JANELA));
    }

fclose(saida);
fclose(arq);

FILE* temp;
FILE* out;
out = fopen("final.txt","w");
temp = fopen("bin.txt","r");
    while(fscanf(temp,"%8c",str)==1)
        {
        convStringByte(&byte,str);
        fwrite(&byte,1,1,out);
        }
}

void taxacomp(FILE* in, FILE* compac){
double x = ftell(in);

printf("Tamanho original: %.0f\n",x);  double y = ftell(compac);
printf("Tamanho do arquivo compactado: %.0f\n",y);  printf("Taxa de compressao: %.2f",x/y);
}
