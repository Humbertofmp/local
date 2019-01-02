#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void primeira_passada(char *linha);
void segunda_passada(char *linha);
void terceira_passada(char *linha);
void criptografia(char* linha);

int main()
{
    char linha[1000];
    char texto[1000]={};

    int  j, N;

   while ((scanf("%d", &N)))
          {



    for(j=0; j<N; j++)
        {

            fflush(stdin);
            fgets(linha, 1000, stdin);

            criptografia(linha);
            strcat(texto, linha);

        }
        printf("\n%s", texto);
          }
    return 0;
}

void primeira_passada(char *linha){
    int i=0;
    while((linha[i]) != ('\0'))
        {
            if(isalpha(linha[i]))
            linha[i]= linha[i] + 3;
            i++;

        }
}

void segunda_passada(char *linha){
    strrev(linha);
}

void terceira_passada(char *linha){
    int metade, i;
    metade = (strlen(linha))/2;

    for(i= (metade) ;linha[i]!= '\0'; i++)
        {
            if((linha[i])!= (' '))
            linha[i]= linha[i] - 1;
        }
    linha[i+1]= '\0';
}

void criptografia(char* linha){

    primeira_passada(linha);

    segunda_passada(linha);

    terceira_passada(linha);

    }
