#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define SIZE_CAD 200
/*
Ana e Tiago...Os dois procedimentos principais para coletar os dados do arquivo texto são
     void leArquivo(char nomeArq[15])  Esse le os dados do arquivo texto
     void coleta ()                    E esse organiza os dados em uma struct.
*/

struct Cliente{
       char id[5], nome[30], cidade[20], UF[3], ident[25];  
};

struct Cliente cadastro[SIZE_CAD];

char *result;
char linha[200][150]; //Tinha erro aqui, coloquei o vetor de char muito pequeno (100).
int qtLinhas;


void leArquivo(char nomeArq[15]);
void apresenta();
void apresenta2();
void coleta ();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main (){
    //setlocale(LC_ALL,"portuguese");

    leArquivo ("CLIENTES.txt"); //Tem que passar por parametro o nome do arquivo .txt desejado. 
    //apresenta();
    
    coleta ();
    apresenta2();

    system ("pause");
return 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*void apresenta()
{
      for (int x=0;x<=qtLinhas;x++)
	     printf("%s\n",linha[x]);   
    getch();
}*/

//Procedimento só para mostrar na tela os dados já colocados no vetor de forma adequada.
void apresenta2(){
     system ("cls");
      for (int x=0;x<=qtLinhas;x++)
	     printf("%s | %s | %s | %s | %s\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident);
	     //printf("%s \n",cadastro[x].id); 
         //printf("%s\n",cadastro[x].nome);  
    getch();
}
//------------------------------------------------------------------------------
//Esse primeiro procedimento é igual ao que o professor passou em sala
//Só mudei o nome de uma variavel para fazer mais sentido na minha cabeça.
//E coloquei uma passagem por parametro para ficar mais dinâmico 
void leArquivo(char nomeArq[15]){
    FILE *arq;
     
    arq = fopen(nomeArq, "r"); //leitura
    if (arq == NULL)  // Se houve erro na abertura
    
     printf("Problemas na abertura do arquivo\n");
    else   
    { 
      qtLinhas=0;
      while (!feof(arq))
      {
          result = fgets(linha[qtLinhas], 200, arq);  // o 'fgets' le ate 99 caracteres ou ate o '\n'
          if (linha[qtLinhas][strlen(linha[qtLinhas])-1]=='\n')
                linha[qtLinhas][strlen(linha[qtLinhas])-1]='\0'; //caso o ultimo caracter seja /n, sera substituido por /0 (fin de string)
    	  qtLinhas++;   
      }
      fclose(arq);	
      qtLinhas--;
      printf ("Falta coletar CPF/CNPJ/RG\n");
      printf ("Quantidade de linhas: %d\n\n\n",qtLinhas);
    } 
}
//------------------------------------------------------------------------------
//Iguinorem essa função.
//Tenho que tirar uma duvida com o Morena na Quarta-feira
//Sobre passagem de structs por referência
int divisao (struct Cliente *tmp, int i, int ref){

    bool flag = true;
    int j=0;   
    
    while (flag){
          tmp -> id[j] = linha[i][ref+j];
          j++;
          if (linha[i][ref+j] == '"'){
             tmp -> id[j] = '\0';
             flag = not flag;
             j--;
          }
    }
    return ref+j;
}
//------------------------------------------------------------------------------
//Esse é o procedimento que faz a magica
//Ele organiza em vetor de struct os cados que estão a matriz (vetor de caracter) => linha[qtLinhas][strlen(linha[qtLinhas])-1]
void coleta (){
     int j, ref, referencia;
     int contJ;
    
     for (int i = 0; i < SIZE_CAD; i++){       

         //Pega o código do cliente
         contJ = 0;
         ref = 1;
         j=0;
         bool flag = true;
         
         while (flag){
               cadastro[i].id[j] = linha[i][ref+j];
               j++;
               if (linha[i][ref+j] == '"'){
                  cadastro[i].id[j] = '\0';
                  flag = not flag;
                  
               }
         }
        
         
         //Pega o nome do cliente
         contJ = contJ + j; //Aqui nada mais é do que esta guardando o valor de j (GLOBAL - da linha i)
         ref = contJ + 4;
         j = 0;
         flag = true;
         while (flag){
               cadastro[i].nome[j] = linha[i][ref+j];
               j++;
               if (linha[i][ref+j] == '"'){
                  cadastro[i].nome[j] = '\0';
                  flag = not flag;
               }
         }
         
         //Pega a cidade do cliente
         contJ = contJ + j; //Aqui nada mais é do que esta guardando o valor de j (GLOBAL - da linha i)
         ref = contJ + 7;
         j = 0;
         flag = true;
         while (flag){
               cadastro[i].cidade[j] = linha[i][ref+j];
               j++;
               if (linha[i][ref+j] == '"'){
                  cadastro[i].cidade[j] = '\0';
                  flag = not flag;
               }
         }
         
         //Pega a UF do cliente
         contJ = contJ + j;
         ref = contJ+10;
         j = 0;
         flag = true;
         while (flag){
               cadastro[i].UF[j] = linha[i][ref+j];
               j++;
               if (linha[i][ref+j] == '"'){
                  cadastro[i].UF[j] = '\0';
                  flag = not flag;
               }
         }
         
         
         
         //DAQUI PARA BAIXO SÃO TENTATIVAS PARA PEGAR CPF/CNPJ/RG
         //NÃO ESTA PRONTA TEM ERROS NO CÓDIGO...
         
         
         //Tratamento para chegar no CPF/CNPJ/RG
         
         //ACHEI O ERRO DAQUI...
         contJ = contJ + j;
         //printf ("CONT %d\n",contJ);
         ref = contJ+13;
         //printf ("ref = cont = %d\n",ref);
         j = 0;
         int k = 0;
         while ( k < 6){
               //printf ("%c",linha[i][ref+j]);
               if (linha[i][ref+j] == '"'){
                  k++;
                  //printf ("%d\n",k);
                  
                  //printf ("Caract     %c\n",linha[i][ref+j]);
                  //printf ("Caract+1     %c\n",linha[i][ref+j+1]);
                 // system ("pause");
                                   //printf ("\nJ %d   i %d\n",j, i);
                                   //printf ("K          %d\n",k);
                                   //printf ("Caract     %c\n",linha[i][ref+j]);
                                   //printf ("ref+j      %d\n",ref+j);
                                   //system ("pause");
                  //printf ("DEPOIS %d\n",k);
                  //system ("pause");
               }
               j++;                    
         }
         
         //TEM QUE FAZER VARIOS TRATAMENTOS PARA CPF / RG /CNPJ -- Tem campo que esta em banco tmb
         
         contJ = contJ + j;
         ref = contJ+13;
         //printf ("ref=%d      i=%d  \n",ref,i);
         //system ("pause");
         j = 0;
         //*******************************************************************************************
         flag = true;
         char letra[8] = {'k','C','P','F','R','G',' ','.'};
         
    //Vai ficar mais lento o programa fazendo assim...mas é o que temos para hoje.
         k = 0; //TENHO QUE TER ESSE K AQUI PARA NÃO APAGAR O J DO WHILE ABAIXO (a posição do vetor ident fica ERRADA)
         for (int p = 0; p < 8; p++){
             if (linha[i][ref+k+j] == letra[p]){
                //printf ("%d   |\n",j);
                //printf ("%c   |\n",linha[i][ref+k+j]);
                //system ("pause");
                k++;
             }
         }
         if (linha[i][ref+k+j] == ' ' || linha[i][ref+k+j] == '"'){
            flag = not flag;
            strcpy (cadastro[i].ident, "SEM IDENTIFICACAO.");
            cadastro[i].ident[18] = '\0';
         }
//*************************************SÓ FALTA FAZER A TRATATIVA DO CPF / RG /CNPJ VAZIO*************************************************************************
/*
colocar flag = not flag
fazer um if
para pegar o espaço ou a " e gravar nesta posição da struct de vetor : "SEM IDENTIFICAÇÃO" com '\0' na ultima posição
*/
         
         while (flag){      
               //printf ("\n%d        ",ref+k+j);       
               cadastro[i].ident[j] = linha[i][ref+k+j];
               //printf ("%c",cadastro[i].ident[j]);
               //Sleep (10);
               //system ("pause");
               j++;
               if (linha[i][ref+k+j] == '"'){
                  cadastro[i].ident[j] = '\0';
                  flag = not flag;
               }
         
         }
      printf ("\n");  
    
     } 
}







