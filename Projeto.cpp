#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

#define SIZE_CAD 200


struct Cliente{
       char id[5], nome[30], cidade[20], UF[3], ident[25];  
       bool st;
};
struct Parcela{
       char idPar[10], idCli[5], venc[9], rec[9], val[9];
       int banco;
       float valor[9];
       bool st;
};
//*****************************VARIAVEIS GLOBAIS******************************//
char *result;
char linha[200][150];
char tmp[200], tmp2[30]; //tmp2 é só para eu não ter que apagar o lixo de memoria que esta em tmp
int qtLinhas, qtLinhasParc, ref;        
int tecla;

struct Cliente cadastro[SIZE_CAD];
struct Parcela registro[SIZE_CAD];
//*****************************XXXXXXXXXXXXXXXXX******************************//

//******************INICIALIZAÇÃO DOS PROCEDIMENTOE FUNÇÕES*******************//
/*Feito*/void leArquivo(char nomeArq[15]);
void apresenta();
void apresenta2();
/*Feito*/void salvaCliente ();
/*Feito*/void salvaParcela ();
/*Feito*/void divisao (int id);
/*Feito*/void divisaoCPF (int id);
/*Feito*/void selectionNome ();
/*Feito*/void selectionIdCliente ();
/*Feito*/void selectionNumeroPar ();
/*Feito*/void selectionVencPar ();
/*Feito*/int validaID (char comp[5]);
int menuMudarCli (int p);
void mudarCliente ();
void cadastrarCliente ();
/*Feito*/void maiusc (char palavra[30]);
void deletarCliente ();
int buscaBinaria (char pesquisa[5], int tipo);
/*Feito*/void addParcela ();
/*Feito*/bool validaDate (char data[11]);
//******************XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*******************//

//-----------------------------PROGRAMA PRINCIPAL-----------------------------//
int main (){
    setlocale(LC_ALL,"portuguese");

    leArquivo ("CLIENTES.txt"); //Tem que passar por parametro o nome do arquivo .txt desejado. 
    
    salvaCliente ();
    //apresenta();
    //system ("pause");
    
    
    //mudarCliente ();
    
    leArquivo ("PARCELAS.txt");
    salvaParcela();
    //apresenta2();
    //system ("pause");
    
    //selectionVencPar();
    //apresenta2();
    //system ("pause");
    
    
    //selectionNome();
    //apresenta();
    //system ("pause");

    //selectionIdCliente();
    //apresenta2();
    //system ("pause");
    
    //selectionNumeroPar();
    //apresenta2();
    //system ("pause");
    
     
     //mudarCliente ();
     cadastrarCliente ();
     
     /*deletarCliente ();
     apresenta();
     printf ("PROBLEMA EM APARECER SÓ OS REGISTROS true...QUANDO DELETA UM CLIENTE");
     */
     /*int j;
     selectionNumeroPar ();
     apresenta2();
     j = buscaBinaria();
     printf ("%d",j);*/
     
     
     //addParcela();
     
    system ("pause");
return 0;
}
//-----------------------------XXXXXXXXXXXXXXXXXX-----------------------------//

//---------------------------PROCEDIMENTOS E FUNÇÕES--------------------------//
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
    } 
}
//------------------------------------------------------------------------------
void apresenta(){
     system ("cls");
     for (int x=0;x<=qtLinhas;x++){
         //if (cadastro[x].st == true){
            printf("%4s  %20s  %22s  %2s  %30s\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident);
         //}
     }
     getch();
}
//------------------------------------------------------------------------------
void apresenta2(){
     system ("cls");
     printf ("  Parcela   id    Vencimento  Recebimento  Valor     BC\n");
     printf ("--------------------------------------------------------\n");
     for (int x=0;x<=qtLinhas;x++){
         printf("%9s  %5s  %9s  %9s  %9s  %.3d\n",registro[x].idPar, registro[x].idCli, registro[x].venc, registro[x].rec, registro[x].val, registro[x].banco);
         //Sleep (30);
     }
    getch();
    /*while total/25 > 0 ---> Para apresentar por página (uma ideia algo assim)*/
}
//------------------------------------------------------------------------------
void divisao (int id){
    bool flag = true;
    int j=0;

    while (flag){
          tmp[j] = linha[id][ref];
          j++;
          ref++;
          if (linha[id][ref] == '"'){
             tmp[j] = '\0';
             flag = not flag;
          }
    }
    ref = ref + 3;
}
//------------------------------------------------------------------------------
void divisaoCPF (int id){
     char letra[11] = {'k','C','P','F','R','G',' ','.', ':', '"', ','};
     int k;
     
     k = 0; //TENHO QUE TER ESSE K AQUI PARA NÃO APAGAR O J DO WHILE ABAIXO (a posição do vetor ident fica ERRADA)
     for (int p = 0; p < 11; p++){
         if (linha[id][ref+k] == letra[p]){
            k++;
         }
     }

     if (ref <= strlen (linha[id])){
        strcpy (tmp, "SEM IDENTIFICACAO.");
        tmp[18] = '\0';
     }
     
     if (k == 0 || k == 2){
        if (k == 2) ref = ref -1;
        divisao (id);
     }
     
     if (k == 2){
        strcpy (tmp, "N/D");
        tmp[3] = '\0';
     }   
}
//------------------------------------------------------------------------------
void salvaCliente (){
     
     for (int i=0; i <= qtLinhas; i++){
         ref = 1;
         
         divisao (i);
         strcpy (cadastro[i].id, tmp);
         
         divisao (i);
         strcpy (cadastro[i].nome, tmp);
         
         divisao (i);
         strcpy (cadastro[i].cidade, tmp);
         
         divisao (i);
         strcpy (cadastro[i].UF, tmp);
         
         divisao (i);
         divisao (i);
         divisao (i);
         
         divisaoCPF (i);
         strcpy (cadastro[i].ident, tmp);
         
         cadastro[i].st == true;
     }
}
//------------------------------------------------------------------------------
void salvaParcela (){
     int bc;
     for (int i=0; i <= qtLinhas; i++){
         ref = 1;
         
         divisao (i);
         strcpy (registro[i].idPar, tmp);
         
         divisao (i);
         strcpy (registro[i].idCli, tmp);
         
         divisao (i);
         strcpy (registro[i].venc, tmp);
         //***************************************
         divisaoCPF (i);
         strcpy (registro[i].rec, tmp);
         //***************************************    
         divisao (i);
         strcpy (registro[i].val, tmp);
         
         divisao (i);
         bc = strtol (tmp, NULL, 10); //FUNÇÃO PADRÃO QUE CONVERTE char p/ int
         registro[i].banco = bc;
     }
     qtLinhasParc = qtLinhas;
}
//------------------------------------------------------------------------------
void selectionNome (){ //Organiza por nome do cliente
     struct Cliente tmpCad;
     
     for (int i=0; i<=qtLinhas-1; i++){
         for (int j=i+1; j<=qtLinhas; j++){
             if (strcmp(cadastro[j].nome, cadastro[i].nome) < 0){
                tmpCad = cadastro[i];
                cadastro[i]=cadastro[j];
                cadastro[j]=tmpCad;
             }           
         }         
     }  
}
//------------------------------------------------------------------------------
void selectionIdCliente (){ //Organiza por id do cliente
     struct Cliente tmpCad;
     
     for (int i=0; i<=qtLinhas-1; i++){
         for (int j=i+1; j<=qtLinhas; j++){
             if (strcmp(cadastro[j].id, cadastro[i].id) < 0){
                tmpCad = cadastro[i];
                cadastro[i]=cadastro[j];
                cadastro[j]=tmpCad;
             }           
         }         
     }  
}
//------------------------------------------------------------------------------
void selectionNumeroPar (){ //Organiza por número da parcela
     struct Parcela tmpPar;
     
     for (int i=0; i<=qtLinhas-1; i++){
         for (int j=i+1; j<=qtLinhas; j++){
             if (strcmp(registro[j].idPar, registro[i].idPar) < 0){
                tmpPar = registro[i];
                registro[i]=registro[j];
                registro[j]=tmpPar;
             }           
         }         
     }  
}
//------------------------------------------------------------------------------
void selectionVencPar (){ //Organiza por vencimento da parcela
     struct Parcela tmpPar;
     
     for (int i=0; i<=qtLinhas-1; i++){
         for (int j=i+1; j<=qtLinhas; j++){
             if (strcmp(registro[j].venc, registro[i].venc) < 0){
                tmpPar = registro[i];
                registro[i]=registro[j];
                registro[j]=tmpPar;
             }           
         }         
     }  
}
//------------------------------------------------------------------------------
int menuMudarCli (int p) {
     int op;
     do {
        system ("cls");
        printf ("Alterar dados do Cliente: %s\n", cadastro[p].nome);
        printf ("1 - Alterar Nome\n");
        printf ("2 - Alterar Cidade\n");
        printf ("3 - Alterar UF\n");
        printf ("4 - Alterar RG/CPF/CNPJ\n");
        printf ("5 - Voltar\n");
        printf ("Escolha uma opção: ");
        scanf ("%d", &op);
     }while (op <=0 && op >=6);
     return op;
}
//------------------------------------------------------------------------------
void mudarCliente (){ //*****************************************************************PROBLEMA não está salvando dados
     int k, j = 0;
     char cod[5];
     
     printf ("Código do cliente a ser altualizado: ");
     gets (cod);
     k = validaID(cod);
     if (k != -1){
        do{
           j = menuMudarCli (k);
           //printf ("%d",j);
           //system ("pause");
           if (j == 1){
            system ("cls");
            printf ("Novo Nome: ");
            gets (cadastro[k].nome);
           }
           else if (j == 2){
            system ("cls");
            printf ("Nova Cidade: ");
            gets (cadastro[k].cidade);
           }
           else if (j == 3){
            system ("cls");
            printf ("Novo UF: ");
            gets (cadastro[k].UF);  
           }
           else if (j == 4){
            system ("cls");
            printf ("Novo identificador: ");
            gets (cadastro[k].ident); 
           }
        }while(j != 5);
             
     }
     else{
       printf ("Cliente não cadastrado!!!\n"); 
       printf ("Precione <ENTER> para continuar");  
       getch();
       //*******************************RETORNAR MENU?*********************COLOCAR AQUI UM CAMINHO PARA SEGUIR NO PROGRAMA
     }
}
//------------------------------------------------------------------------------
int validaID (char comp[5]){ //Busca exastiva (da para melhorar se sobrar tempo)
     
     for (int i = 0; i <= qtLinhas-1; i++){
         if (strcmp(comp, cadastro[i].id) == 0)
            return i;
     }
     return -1;
}
//------------------------------------------------------------------------------
void cadastrarCliente (){
     int k = -10;
     
     qtLinhas++;
     system ("cls");
     printf ("Cadastrar NOVO Cliente\n");
     while (k != -1){
           printf ("Código: ");
           gets (cadastro[qtLinhas].id);
           k = validaID (cadastro[qtLinhas].id);
           if (k != -1) printf ("Código já cadastrado!!!\n");
     }
     printf ("Nome: ");
     gets (cadastro[qtLinhas].nome);
     maiusc (cadastro[qtLinhas].nome); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhas].nome, tmp2);
    
     printf ("Nova Cidade: ");
     gets (cadastro[qtLinhas].cidade);
     maiusc (cadastro[qtLinhas].cidade); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhas].cidade, tmp2);
         
     printf ("UF: ");
     gets (cadastro[qtLinhas].UF);
     maiusc (cadastro[qtLinhas].UF); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhas].UF, tmp2);
         
     printf ("RG/CPF/CNPJ: ");
     gets (cadastro[qtLinhas].ident);
     maiusc (cadastro[qtLinhas].ident); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhas].ident, tmp2);
}
//------------------------------------------------------------------------------
void maiusc (char palavra[30]){
     for (int i = 0; i <= strlen(palavra); i++){
         tmp2[i] = toupper (palavra[i]); //tmp variavel global
     }
}
//------------------------------------------------------------------------------
void deletarCliente (){
     char cod[5];
     int k = -100;
     
     qtLinhas++; //Sem isso, não pega o último código do cliente
     printf ("Deletar Cliente\n");
     do{
     printf ("Código do Cliente: ");
     gets (cod);
     k = validaID (cod);
     if (k == -1) printf ("Cliente não cadastrado.\n");
     }while (k == -1);
     cadastro[k].st = false;
     qtLinhas--; //Para voltar ao normal
     
     printf ("%d",cadastro[k].st);
     system ("pause");
}
//------------------------------------------------------------------------------
int buscaBinaria (char pesquisa[5], int tipo){ //BUSCA PARA ACHAR O número da parcela
    int ini, fim, meio, p = 0;           
    
    if (tipo = 1) qtLinhasParc--;
    
    ini = 0;
    fim = qtLinhasParc;
    while (ini <= fim){
          meio = (ini+fim)/2;
          if (strcmp(registro[meio].idPar, pesquisa) == 0){
             p = meio;
             if (tipo = 1) qtLinhasParc++;
             return p;//retorna a posição da parcela
          }else{
              if (strcmp(pesquisa, registro[meio].idPar) < 0){ 
                 fim = meio - 1;           
              }
              else {
                   ini = meio + 1;
              }
          }                  
    }
    if (tipo = 1) qtLinhasParc++;
    return -1; // retorna -1 número da parcela não encontrado
}
//------------------------------------------------------------------------------**********************************
void addParcela (){
     int k = -1;
     bool flag;
     
     qtLinhasParc++;
     printf ("Adicionar Parcelas\n\n");
     while (k == -1){ //Validando ID CLIENTE
           printf ("Código do cliente: ");
           gets (registro[qtLinhasParc].idCli);
           selectionNumeroPar ();
           k = validaID(registro[qtLinhasParc].idCli);
           
           if (k == -1) printf ("Código não cadastrado.\n");
     }
     k = 0;
     while (k != -1){ //Validando CÓDIGO PARCELA
           printf ("Informe código da parcela(Ex: 1234/1): ");
           gets (registro[qtLinhasParc].idPar);
            
           k = buscaBinaria (registro[qtLinhasParc].idPar, 1); //Passando como parametro o '1' para descontar a qtLinhasParc, se não da ruim.
           
           if (k != -1) printf ("Número de parcela já cadastrado.\n");     
     }
     
     flag = false;
     while (not flag){
         printf ("Data do vencimento(Ex: 02/11/21): ");
         gets (registro[qtLinhasParc].venc);
         flag = validaDate (registro[qtLinhasParc].venc);
         if (not flag) printf ("Data Inválida.\n");
     }   
     
     do {
        printf ("Valor da Parcela (Ex: 150,00): ");
        gets (registro[qtLinhasParc].val);
        if (strtol(registro[qtLinhasParc].val, NULL, 10) <= 0) //Convertendo de CHAR para INT (Função 'strtol')
           printf ("Valor de parcela Inválido\n");
     } while (strtol(registro[qtLinhasParc].val, NULL, 10) <= 0);
     
     do{
        printf ("(0   - Carteira)\n(001 - Banco do Brasil)\n(104 - Caixa Econômica Federal)\n(237 - Bradesco)\n(260 - Nubank)\nCódigo Banco: ");                                                                                
        //gets (registro[qtLinhasParc].banco);
        scanf ("%d",&registro[qtLinhasParc].banco);
     }while (registro[qtLinhasParc].banco !=0 &&
      registro[qtLinhasParc].banco !=001 &&
      registro[qtLinhasParc].banco !=104 && 
      registro[qtLinhasParc].banco !=237 && 
      registro[qtLinhasParc].banco !=260);
      //ESSA MERDA FUNCIONA ASSIM SÓ SE A VARIAVEL FOR int (só Deus sabe o motivo)...  
}
//------------------------------------------------------------------------------
bool validaDate (char data[11]){
     char dia[3], mes[3], ano[5];
     int nDia, nMes, nAno;
     
     for (int i=0; i<= strlen(data); i++){  //    Ex: 17/01/1994
         if (data[i] != '/' || data[i] != '.' && i<=1){
            dia[i] = data[i];   
         }
         if (data[i] != '/' || data[i] != '.' && i>=3 && i<=4){
            mes[i-3] = data[i];   
         }
         if (data[i] != '/' || data[i] != '.' && i>=6 && i<=9){
            ano[i-6] = data[i];   
         }   
     }
     dia[2] = '\0';
     mes[2] = '\0';
     ano[4] = '\0';
     nDia = strtol (dia, NULL, 10); //FUNÇÃO PADRÃO QUE CONVERTE char p/ int
     nMes = strtol (mes, NULL, 10); //FUNÇÃO PADRÃO QUE CONVERTE char p/ int
     nAno = strtol (ano, NULL, 10); //FUNÇÃO PADRÃO QUE CONVERTE char p/ int
     //Ano bissexto
     if (nMes == 2){
        if (nAno % 4 != 0){ //Significa que o ano NÃO é bissexto
           if (nDia > 28){ 
              return false;
           }
        }
        if (nAno % 4 == 0){ //Significa que o ano é bissexto
           if (nDia > 29){ 
              return false;
           }
        }
     }
       
     if (nDia <=0 || nDia >= 32 || nMes <= 0 || nMes >=13 || nAno < 1900 || nAno >= 5000){ 
        return false;
     }else{
        return true;
     }        
}
//------------------------------------------------------------------------------
