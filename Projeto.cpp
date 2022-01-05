#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

#define SIZE_CAD 200

/////////enter = getch(); comando para trocar UTILIZANDO A TABELA ASCII


//DUVIDA: Professor, ao deletar um registro, eu posso utilizar o ID que foi deletado em outro registro?
// E NA APRESENTAÇÃO DOS DADOS BANCARIOS TMB. SE FOR DELETADO TEM QUE APARECER NO RESUMO?

//Lembrete
//TESTAR: em validaID, colocar uma if para testar o campo cadastro[i].status se é verdadeiro ou falso
//        se for falso, retornar -1, indicando que o código não exixte (foi deletado)

struct Cliente{
       char id[5], nome[30], cidade[30], UF[3], ident[25];  
       bool status;
};
struct Parcela{
       char idPar[10], idCli[5], venc[9], rec[9], val[9], charBanco[5];
       int banco;
       float valor;
       bool st;
};
//*****************************VARIAVEIS GLOBAIS******************************//
char *result;
char linha[200][150];
char tmp[200], tmp2[30]; //tmp2 é só para eu não ter que apagar o lixo de memoria que esta em tmp
int qtLinhas, qtLinhasParc, qtLinhasCli, ref;        
int tecla;
bool flagCli, flagParc;
int enter, timerMenu;
char idBanco[15][5];
char nomeBanco [20][15];
int totalBanco;

struct Cliente cadastro[SIZE_CAD];
struct Parcela registro[SIZE_CAD];
//*****************************XXXXXXXXXXXXXXXXX******************************//

//******************INICIALIZAÇÃO DOS PROCEDIMENTOE FUNÇÕES*******************//
/*Feito*/void menuCliente ();
void mostrarCadastro (char descricao[50]); //FALRA LISTAR TODOS, SEM SELECIONAR CIDADE.
void menuParcela ();
void mostrarParcela (char opMenu[15]);
void deletarParcela ();

void menuPrincipal ();
/*Feito*/void leArquivo(char nomeArq[15]);
/*Feito*/void dadosImp (int tipo, bool flag);
/*Feito*/void apresenta(char legenda[50], char menu[50]);
/*Feito*/void apresenta2(char menu[50]);
/*Feito*/void salvaCliente ();
/*Feito*/void salvaParcela ();
/*Feito*/void divisao (int id);
/*Feito*/void divisaoCPF (int id);
/*Feito*/void selectionNome ();
/*Feito*/void selectionIdCliente ();
/*Feito*/void selectionNumeroPar ();
/*Feito*/void selectionVencPar ();
/*Feito*/int validaID (char comp[5]);
/*Feito*/int menuMudarCli (int p);
/*Feito*/void mudarCliente ();
/*Feito*/void cadastrarCliente ();
/*Feito*/void maiusc (char palavra[30]);
bool deletarCliente (char cod[5]);
void menuDeletarCliente ();
/*Feito*/int buscaBinaria (char pesquisa[5], int tipo);
int buscaBinariaIdCli (char pesquisa[5], int tipo);
/*Feito*/void addParcela ();
/*Feito*/void mudarParc ();
void menuMudarPar (int q, int c);
/*Feito*/int subMenuMudarPac (int p, int cliente);
/*Feito*/bool validaDate (char data[7]);

//void totalGeral ();
//void menuResumidoPag (float a, float r, float t);
void resumoBanco ();
void receitaBancoCliente (int tipo);
void menuReceita ();

void menuBusca ();

void personalizado ();
bool parcelaBanco (char cli[5], char bc[5]);
void clienteEUmbanco (char cli[5], char bc[5], int orde, int parc, bool flag);

void Bancos ();
int validaBanco (char bc[5]);

void resumoSintBanco ();
void consutaTodasParcela ();

int palavraIgual (char p1[30], char p2[30]);

/*Feito*/void creditos ();
//******************XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*******************//

//-----------------------------PROGRAMA PRINCIPAL-----------------------------//
int main (){
    setlocale(LC_ALL,"portuguese");
      
    flagCli = false; 
    flagParc = false;
    
    timerMenu = 300;
    totalBanco = 6;
    Bancos ();
    
    //menuPrincipal ();
    leArquivo ("CLIENTES.txt");
    salvaCliente ();
    leArquivo ("PARCELAS.txt");
    salvaParcela ();
    
    //menuPrincipal ();
    //resumoSintBanco ();
    
    consutaTodasParcela ();
    
    
    //selectionVencPar ();
    
     //menuDeletarCliente ();
     
     
    //personalizado ();
    
    //receitaBancoCliente (2);
    
    
    //totalGeral ();
    
    //contaBanco ();
    
    //receitaBancoCliente (1);
     
return 0;
}
//-----------------------------XXXXXXXXXXXXXXXXXX-----------------------------//

//---------------------------PROCEDIMENTOS E FUNÇÕES--------------------------//
void menuPrincipal (){
    int op=-1;
    
    system ("cls");
    printf ("Falta fazer a validação de deletar parcela...\n");
    
    //while (op < 48 || op > 53 || op == 27){
    do{
        system ("cls");
        printf ("Falta fazer a validação de deletar parcela...\n");
        printf ("MENU PRINCIPAL\n\n");
        printf ("  1  - Menu Cliente\n");
        printf ("  2  - Menu Parcelas\n");
        printf ("  3  - Menu Busca\n");
        printf ("  4  - Menu Receita\n");
        printf ("  0  - Créditos\n");
        printf (" ESC - Sair\n");
        printf (" Escolha uma opção: ");
        op = getch ();
        if (op-48>=0 && op-48<=9) printf ("%d",op-48);
        Sleep (timerMenu);  
    }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 48 && op != 27);
    
    switch (op){
           case 49: 
                menuCliente ();
                break;
           case 50: 
                menuParcela ();
                break;
           case 51:
                menuBusca ();
                break;
           case 52:
                menuReceita ();
                break;
           case '5':break;
           case 48:
                creditos ();
                printf ("<ENTER> para voltar MENU PRINCIPAL");
                do{ //VALIDA SE A PESSOA APERTOU ENTER
                    fflush (stdin);
                    enter = getch();
                }while (enter != 13);
                menuPrincipal ();
                break;
           case 27:
                break;
    }
}
//------------------------------------------------------------------------------
void menuCliente (){
     int op;
     
     do {
         fflush (stdin);
         system ("cls");
         printf ("MENU CLIENTE\n\n");
         printf ("  1  - Importar\n");
         printf ("  2  - Mostrar Cadastros\n");
         printf ("  3  - Adicionar\n");
         printf ("  4  - Alterar\n");
         printf ("  5  - Excluir\n");
         printf (" ESC - Menu Principal\n");
         printf (" Escolha um opção: ");
         op = getch ();
         if (op-48>=0 && op-48<=9) printf ("%d",op-48);  
         Sleep (timerMenu);  
    }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 53 && op != 27);
     
     switch (op){
            case 49:
                 if (flagCli){
                    system ("cls");
                    printf ("Dados dos Clientes já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    do{ //VALIDA SE A PESSOA APERTOU ENTER
                        fflush (stdin);
                        enter = getch();
                    }while (enter != 13);
                    menuCliente (); 
                 }
                 leArquivo ("CLIENTES.txt");
                 salvaCliente ();
                 apresenta ("AGUARDE, IMPORTANDO...","Obrigado por esperar! <ENTER> voltar ao MENU CLIENTE");
                 menuCliente ();
                 break;
            case 50:
                 dadosImp (1, flagCli);
                 mostrarCadastro ("<ENTER> para voltar ao MEU CLIENTE"); 
                 menuCliente ();
                 break;
            case 51:
                 dadosImp (1, flagCli);
                 cadastrarCliente ();
                 break;
            case 52:
                 dadosImp (1, flagCli);
                 mudarCliente ();
                 break;
            case 53:
                 dadosImp (1, flagCli);
                 menuDeletarCliente ();
                 break;
            case 27:
                 menuPrincipal ();
                 break;                
     }    
}
//------------------------------------------------------------------------------
void mostrarCadastro (char descricao[50]){
     char cidade[30], uf[3];
     int ord;
     int temp[qtLinhasCli];
     int linha = 0;
     int enter;
     
     system ("cls");
     printf ("Lista de Clientes Cadastrados\n\n");
     
     fflush (stdin);
     printf ("Cidade desejada (Enter para TODAS) : ");
     gets (cidade);
     maiusc (cidade); //PARA GRAVAR E PESQUISAR TUDO EM MAIUSCULO
     strcpy (cidade, tmp2);
     if (cidade[0] == '\0'){
        system ("cls");
        printf ("Lista de Clientes Cadastrados\n\n");
        printf ("Cidade desejada (Enter para TODAS) : %s\n","TODOS");
     }
     
     fflush (stdin);
     printf ("UF desejada (Enter para TODOS)     : ");
     gets (uf);
     maiusc (uf); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (uf, tmp2);
     if (uf[0] == '\0'){
        system ("cls");
        printf ("Lista de Clientes Cadastrados\n\n");
        printf ("Cidade desejada (Enter para TODAS) : %s\n", "TODOS");
        printf ("UF desejada (Enter para TODOS)     : %s\n",     "TODOS");
     }
     
     do{
        fflush (stdin);
        printf ("Ordenação (1 - Nome | 2 - ID)      :   ");
        scanf ("%d",&ord);
     }while (ord != 1 && ord != 2);
     
     if (ord == 1){
        selectionNome ();
     }else{
        selectionIdCliente ();
     }     
  
     system ("cls");
     for (int x=0; x<=qtLinhasCli; x++){
         if (((strcmp(cidade, cadastro[x].cidade)==0  ) || (cidade[0] == '\0'))  &&  ((strcmp(uf, cadastro[x].UF)==0) || (uf[0] == '\0' ))){ 
            if (linha == 0){
               printf (" ID          Cliente                  Cidade              UF     RG/CPF/CNPJ\n");
               printf ("------------------------------------------------------------------------------------\n");
            }
            if (cadastro[x].status == true){
               printf("%4s | %20s | %25s | %2s | %19s |\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident);
               Sleep (20);
               linha++;
            }
            if (linha == 25){
               linha = 0;
               fflush (stdin);
               printf ("------------------------------------------------------------------------------------\n");
               printf ("<Enter> para mostrar mais");
               do{ //VALIDA SE A PESSOA APERTOU ENTER
                   fflush (stdin);
                   enter = getch();
               }while (enter != 13);
               system ("cls");
            } 
         }
     }
     if (linha > 0){
        printf ("---------------------------------------------------------------------------------\n");
        printf (descricao); //descricao (é o que aparece na última linha da última tela)
        do{//VALIDA SE A PESSOA APERTOU ENTER
           fflush (stdin);
           enter = getch();
        }while (enter != 13); 
     }else{
        if (cidade[0] == '\0') strcpy(cidade,"Todas");
        printf ("---------------------------------------------------------------------\n");
        printf (" Nenhum cliente encontrado:  Cidade:%20s  |  UF: %2s\n",cidade, uf);
        printf ("---------------------------------------------------------------------\n");
        do{//VALIDA SE A PESSOA APERTOU ENTER
                 fflush (stdin);
                 enter = getch();
        }while (enter != 13);    
     }                 
}
//------------------------------------------------------------------------------
int menuMudarCli (int p) {
     int op = -1;
     do{
        fflush (stdin);
        system ("cls");
        printf ("Alterar dados\n"); 
        printf ("----------------------------------------\n");
        printf ("      Cliente: %s\n", cadastro[p].nome);
        printf ("       Cidade: %s\n", cadastro[p].cidade);
        printf ("           UF: %s\n", cadastro[p].UF);
        printf ("  RG/CPF/CNPJ: %s\n", cadastro[p].ident);
        printf ("----------------------------------------\n");
        printf ("  1  - Alterar Nome\n");
        printf ("  2  - Alterar Cidade\n");
        printf ("  3  - Alterar UF\n");
        printf ("  4  - Alterar RG/CPF/CNPJ\n");
        printf (" ESC - Menu Cliente\n");                                                //*********************
        printf (" Escolha uma opção: ");
        op = getch ();
        if (op-48>=0 && op-48<=9) printf ("%d",op-48); 
        Sleep (timerMenu);
     }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 53 && op != 27);
     return op;
}
//------------------------------------------------------------------------------
void mudarCliente (){ 
     int k, j;
     char cod[5];
     
     system ("cls");
     fflush (stdin);
     printf ("Código do cliente a ser altualizado: ");
     gets (cod);
     qtLinhasCli++; //Por conta da forma que está implementado validaID
     k = validaID(cod);
     qtLinhasCli--;
     
     if (k != -1){
        do{
           j=0;
           j = menuMudarCli (k);
           if (j == 49){
            fflush(stdin);
            printf ("\nNovo Nome: ");
            gets (cadastro[k].nome);
            maiusc (cadastro[k].nome);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].nome, tmp2);
           }
           if (j == 50){
            fflush(stdin);
            printf ("\nNova Cidade: ");
            gets (cadastro[k].cidade);
            maiusc (cadastro[k].cidade);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].cidade, tmp2);
           }
           if (j == 51){
            fflush(stdin);
            printf ("\nNovo UF: ");
            gets (cadastro[k].UF);
            maiusc (cadastro[k].UF);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].UF, tmp2);  
           }
           if (j == 52){
            fflush(stdin);
            printf ("\nRG/CPF/CNPJ: ");
            gets (cadastro[k].ident); 
            maiusc (cadastro[k].ident);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].ident, tmp2);
           }
           if (j ==27){
              menuCliente ();
           }
        }while(j != 27);
             
     }
     else{
       printf ("Cliente não cadastrado!!!\n"); 
       printf ("<ENTER> para voltar (MENU CLIENTE)");  
       do{ //VALIDA SE A PESSOA APERTOU ENTER
          fflush (stdin);
          enter = getch();
       }while (enter != 13);
       menuCliente ();
     }
     /*printf ("%s\n",cadastro[k].id);
     printf ("%s\n",cadastro[k].nome);
     printf ("%s\n",cadastro[k].cidade);
     printf ("%s\n",cadastro[k].UF);
     printf ("%s\n",cadastro[k].ident);
     system ("pause");*/
}
//------------------------------------------------------------------------------
void cadastrarCliente (){
     int k = -10;
     
     qtLinhasCli++;
     system ("cls");
     printf ("Cadastrar NOVO Cliente\n");
     while (k != -1){
           fflush (stdin);
           printf ("Código: ");
           gets (cadastro[qtLinhasCli].id);
           k = validaID (cadastro[qtLinhasCli].id);
           if (k != -1) printf ("Código já cadastrado!!!\n");
     }
     fflush (stdin);
     printf ("Nome: ");
     gets (cadastro[qtLinhasCli].nome);
     maiusc (cadastro[qtLinhasCli].nome); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhasCli].nome, tmp2);
     
     fflush (stdin);
     printf ("Cidade: ");
     gets (cadastro[qtLinhasCli].cidade);
     maiusc (cadastro[qtLinhasCli].cidade); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhasCli].cidade, tmp2);
     
     fflush (stdin);    
     printf ("UF: ");
     gets (cadastro[qtLinhasCli].UF);
     maiusc (cadastro[qtLinhasCli].UF); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhasCli].UF, tmp2);
     
     fflush (stdin);    
     printf ("RG/CPF/CNPJ: ");
     gets (cadastro[qtLinhasCli].ident);
     maiusc (cadastro[qtLinhasCli].ident); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (cadastro[qtLinhasCli].ident, tmp2);
     
     cadastro[qtLinhasCli].status = true;
     
     /*
     printf ("%d",qtLinhasCli);
     printf ("%s\n",cadastro[qtLinhasCli].id);
     printf ("%s\n",cadastro[qtLinhasCli].nome);
     printf ("%s\n",cadastro[qtLinhasCli].cidade);
     printf ("%s\n",cadastro[qtLinhasCli].UF);
     printf ("%s\n",cadastro[qtLinhasCli].ident);
     */
     printf ("\nCadastro realizado!!!\n");
     printf ("<ENTER> para voltar ao MENU CLIENTE");
     do{ //VALIDA SE A PESSOA APERTOU ENTER
        fflush (stdin);
        enter = getch();
     }while (enter != 13);
     menuCliente ();
}
//------------------------------------------------------------------------------ 
void menuDeletarCliente (){
     char codigo[5];
     int k = -100;
     bool flag;
     
     system ("cls");
     qtLinhasCli++; //Sem isso, não pega o último código do cliente
     do{
        system ("cls");
        printf ("Deletar Cliente\n\n");
        fflush (stdin);
        printf ("Código do Cliente: ");
        gets (codigo);
        k = validaID (codigo);
        if (k == -1){
           fflush (stdin);
           printf ("Cliente não cadastrado.\n");
           printf ("<ENTER> para tentar novamente.");
           do
             enter = getch();
           while (enter != 13);
        } 
     }while (k == -1);
     qtLinhasCli--; //Para voltar o vetor ao normal. 
     
     flag = true;
     flag = deletarCliente (codigo);
     
     if (flag){
        cadastro[k].status = false;
        
        for (int i=0; i<=qtLinhasParc; i++){
            if ((strcmp(codigo, registro[i].idCli)==0))
               registro[i].st = false;
        }
        system ("cls");
        printf ("Deletar Cliente\n\n");
        printf ("Código: %s\n",cadastro[k].id);
        printf ("Cliente: %s deletado.\n\n",cadastro[k].nome);
        printf ("<ENTER> para voltar ao MENU CLIENTE");
        do{ //VALIDA SE A PESSOA APERTOU ENTER
            fflush (stdin);
            enter = getch();
        }while (enter != 13);
        menuCliente ();   
     }
     else{
        system ("cls");
        printf ("Deletar Cliente\n\n");
        printf ("Não foi possível apagar os registros\n\n");
        printf ("Cliente: %s tem parcelas em aberto.\n\n",cadastro[k].nome);
        printf ("<ENTER> para voltar ao MENU CLIENTE");
        do{ //VALIDA SE A PESSOA APERTOU ENTER
            fflush (stdin);
            enter = getch();
        }while (enter != 13);
        menuCliente ();
     }
}
//------------------------------------------------------------------------------
bool deletarCliente (char cod[5]){
     int k = -100;
     
     for (int i=0; i<=qtLinhasParc; i++){
         if ((strcmp(cod, registro[i].idCli)==0) && (strcmp(registro[i].rec, "N/D")==0))
            return false; 
     }
     return true;
}
//------------------------------------------------------------------------------
void menuParcela (){
     int op;
     
     do {
     system ("cls");
         printf ("MENU PARCELAS\n\n");
         printf ("  1  - Importar\n");
         printf ("  2  - Mostrar Parcelas\n");
         printf ("  3  - Adicionar Parcela\n");
         printf ("  4  - Alterar Parcela\n");
         printf ("  5  - Excluir Parcela\n");
         printf (" ESC - Menu Principal\n");
         printf ("Escolha um opção: ");
         op = getch ();
         if (op-48>=0 && op-48<=9) printf ("%d",op-48); 
         Sleep (timerMenu);
     }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 53 && op != 27);
     
     switch (op){
            case 49:
                 if (flagParc){
                    system ("cls");
                    printf ("Dados das Parcelas já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    do{ //VALIDA SE A PESSOA APERTOU ENTER
                        fflush (stdin);
                        enter = getch();
                    }while (enter != 13);
                    menuParcela (); 
                 }
                 leArquivo ("PARCELAS.txt");
                 salvaParcela ();
                 apresenta2 ("Obrigado por esperar! <ENTER> voltar ao MENU PARCELA");
                 menuParcela ();
                 break;
            case 50:
                 dadosImp (2, flagParc);
                 mostrarParcela ("Menu Parcela"); 
                 break;
            case 51:
                 dadosImp (2, flagParc);
                 addParcela ();
                 break;
            case 52:
                 dadosImp (2, flagParc);
                 mudarParc ();
                 break;
            case 53:
                 dadosImp (2, flagParc);
                 deletarParcela ();
                 break;
            case 27:
                 menuPrincipal ();
                 break;   
     }  
}
//------------------------------------------------------------------------------
void mostrarParcela (char opMenu[15]){
    int op; //tipo de ordenação
    int temp[qtLinhasParc];
    float total;
    int ini = 0, fim = 0, linhasE = 24;
    
    do{
       system ("cls");
       printf ("LISTAR PARCELAS CADASTRADAS\n\n");
       fflush (stdin);
       printf ("  1  - Por Número da Parcela\n");
       printf ("  2  - Por Vencimento da Parcela\n");
       if (strcmp(opMenu, "menu parcela") == 0) printf (" ESC - Menu Parcelas\n");
       if (strcmp(opMenu, "munu busca") == 0) printf (" ESC - Menu Busca");
       printf (" Escolha uma opção: ");
       op = getch ();
       if (op-48>=0 && op-48<=9) printf ("%d",op-48); 
       Sleep (timerMenu);
    }while (op != 49 && op != 50 && op != 27);
    
    if (op == 27) menuParcela ();
    
    if (op == 49){
       selectionNumeroPar ();
    }else{
       selectionVencPar ();
    } 

     system ("cls");
     total = qtLinhasParc;
     while (total / 24.0 > 0){
           total = total - linhasE;
           ini = ini;
           fim = fim + linhasE;
     system ("cls");
     //printf ("IMPORTANDO DADOS DAS PARCELAS...\n");
     printf ("  Parcela    ID    Vencimento Recebimento    Valor     BC\n");
     printf ("----------------------------------------------------------\n");
     for (int x=ini;x<=fim;x++){
         if (registro[x].st == true){
             printf("%9s | %4s | %9s | %9s | %9s | %.3d\n",registro[x].idPar, registro[x].idCli, registro[x].venc, registro[x].rec, registro[x].val, registro[x].banco);
             Sleep (20);
         }
     }
     printf ("----------------------------------------------------------\n");
     if (total / 24.0 <= 0){
/*------------------VER ERRO-------------------------*/        printf ("<ENTER> para voltar ao MENU PARCELAS");
        do{ //VALIDA SE A PESSOA APERTOU ENTER
            fflush (stdin);
            enter = getch();
        }while (enter != 13);
/*--------------VER ERRO-----------------------------*/         menuParcela ();
     }else{
        printf ("<Enter> para continuar");
        do{ //VALIDA SE A PESSOA APERTOU ENTER
            fflush (stdin);
            enter = getch();
        }while (enter != 13);  
     }
     ini = ini + linhasE;
     }
}
//------------------------------------------------------------------------------
void addParcela (){ //Para realizar a busca binaria, tem-se que descontar qtLinhasParc, se não, sempre irá achar a ultima linha que add.
     int k = -1, j;
     bool flag;
  
     qtLinhasParc++;
     system ("cls");
     
     //Validando ID CLIENTE
     while (k == -1){ 
           printf ("Adicionar Parcelas\n\n");
           fflush (stdin);
           printf ("Código do cliente: ");
           gets (registro[qtLinhasParc].idCli);
           //selectionNumeroPar ();
           
           k = validaID(registro[qtLinhasParc].idCli);
           
           if (k == -1){
              printf ("Código não cadastrado.\n");
              printf ("<ENTER> para tentar novamente\n");
              do{ //VALIDA SE A PESSOA APERTOU ENTER
                 fflush (stdin);
                 enter = getch();
              }while (enter != 13);
              system ("cls");
           }
     }
  
     //Validando CÓDIGO PARCELA
     j = 0;
     while (j != -1){ 
           system ("cls");
           printf ("Adicionar Parcelas\n\n");
           printf ("Cliente: %s\n", cadastro[k].nome);
           printf ("Código: %s\n\n", cadastro[k].id);
           
           fflush (stdin);
           printf ("Informe código da parcela(Ex: 1234/1): ");
           gets (registro[qtLinhasParc].idPar);
            
           j = buscaBinaria (registro[qtLinhasParc].idPar, 1); //Passando como parametro o '1' para descontar a qtLinhasParc, se não da ruim.
           
           if (j != -1){
              printf ("Número de parcela já cadastrado.\n"); 
              printf ("<ENTER> para tentar novamente.");
              do{
                 enter = getch();
              }while (enter != 13);
           }    
     }
     
     //Valida Data Vencimento
     flag = false;
     while (not flag){
         system ("cls");
         printf ("Adicionar Parcelas\n\n");
         printf ("Cliente: %s\n", cadastro[k].nome);
         printf ("Código: %s\n\n", cadastro[k].id);
         printf ("Código da parcela(Ex: 1234/1): %s\n", registro[qtLinhasParc].idPar);
         
         fflush (stdin);
         printf ("Data do vencimento(Ex: 02/11/21): ");
         gets (registro[qtLinhasParc].venc);
         flag = validaDate (registro[qtLinhasParc].venc);
         if (not flag){ 
            printf ("Data Inválida.\n");
            printf ("<ENTER> para tentar novamente.");
            do{
               enter = getch();
            }while (enter != 13);
         }
     }   
     
     //Valida Valor da parcela
     do {
        system ("cls");
        printf ("Adicionar Parcelas\n\n");
        printf ("Cliente: %s\n", cadastro[k].nome);
        printf ("Código: %s\n\n", cadastro[k].id);
        printf ("Código da parcela(Ex: 1234/1): %s\n", registro[qtLinhasParc].idPar);
        printf ("Data do vencimento(Ex: 02/11/21): %s\n", registro[qtLinhasParc].venc);
        
        fflush (stdin);
        printf ("Valor da Parcela (Ex: 150,00): ");
        gets (registro[qtLinhasParc].val);
        if (strtol(registro[qtLinhasParc].val, NULL, 10) <= 0){ //Convertendo de CHAR para INT (Função 'strtol')
           printf ("Valor de parcela Inválido\n");
           printf ("<ENTER> para tentar novamente.");
           do{
              enter = getch();
           }while (enter != 13);
        }
     } while (strtol(registro[qtLinhasParc].val, NULL, 10) <= 0);
     
     //Valida Banco
     do{
        system ("cls");
        printf ("Adicionar Parcelas\n\n");
        printf ("Cliente: %s\n", cadastro[k].nome);
        printf ("Código: %s\n\n", cadastro[k].id);
        printf ("Código da parcela(Ex: 1234/1): %s\n", registro[qtLinhasParc].idPar);
        printf ("Data do vencimento(Ex: 02/11/21): %s\n", registro[qtLinhasParc].venc);
        printf ("Valor da Parcela (Ex: 150,00): %s\n", registro[qtLinhasParc].val);
        
        fflush (stdin);
        printf ("[000] Carteira\n");                                                                                
        printf ("[001] Banco do Brasil\n");
        printf ("[104] Caixa Econômica Federal\n");
        printf ("[237] Bradesco\n");
        printf ("[260] Nubank\n");
        printf ("[341] Itaú\n");
        printf ("Código Banco: ");
        scanf ("%d",&registro[qtLinhasParc].charBanco);
     }while (registro[qtLinhasParc].banco !=0 &&
      registro[qtLinhasParc].banco != 001 &&
      registro[qtLinhasParc].banco != 104 && 
      registro[qtLinhasParc].banco != 237 && 
      registro[qtLinhasParc].banco != 260 &&
      registro[qtLinhasParc].banco != 341);
      
      k = validaBanco (registro[qtLinhasParc].charBanco);
      
      system ("cls");
      printf ("Adicionar Parcelas\n\n");
      printf ("Cliente           : %s\n", cadastro[k].nome);
      printf ("Código do Cliente : %s\n", cadastro[k].id);
      printf ("Código Parcela    : %s\n", registro[qtLinhasParc].idPar);
      printf ("Valor             : %s\n", registro[qtLinhasParc].val);
      printf ("Banco             : %s\n\n", nomeBanco[k]);
      printf ("Adicionado com sucesso.\n");
      printf ("<ENTER> voltar MENU PARCELA");
      do{ //VALIDA SE A PESSOA APERTOU ENTER
         fflush (stdin);
         enter = getch();
      }while (enter != 13);
      menuParcela ();   
}
//------------------------------------------------------------------------------
void mudarParc (){ //Busca binaria pasa o tipo igual 0. Pois não add nenhuma linha aqui
     int k=-1, j=-1;
     char cod[5], parc[10];
     
     while (k == -1){
         system ("cls");
         printf ("Alterar PARCELAS\n\n");
         fflush(stdin);
         printf ("Código do cliente: ");
         gets (cod);
         
         k = validaID(cod); //Busca o ID do arquivo cliente
         
         if (k == -1){
            printf ("Cliente não cadastrado.\n");
            printf ("Por favor, tente novamente <ENTER>.");
            do{ //VALIDA SE A PESSOA APERTOU ENTER
                fflush (stdin);
                enter = getch();
            }while (enter != 13);
         }
     }
     
     //j = -1;
     while (j ==-1){
         fflush(stdin);
         printf ("Código da parcela: ");
         gets (parc);
         
         j = buscaBinaria(parc, 0); //Verifica o NúMERO DA PARCELA
          
         if (j ==-1){
            printf ("Código da parcela não encontrado\n");
            printf ("Por favor, tente novamente <ENTER>.");
            do{ //VALIDA SE A PESSOA APERTOU ENTER
                fflush (stdin);
                enter = getch();
            }while (enter != 13);
            
            system ("cls");
            printf ("Alterar PARCELAS\n\n");
            printf ("Código do cliente: %s\n", cod);
            
         }
     }
          
     //SE A PARCELA PERTENCER AO CLIENTE É PERMITIDO ELE ALTERAR A PARCELA, CASO CONTRARIO, TENTA NOVAMENTE
     if (strcmp(cadastro[k].id, registro[j].idCli)==0){
        menuMudarPar (j, k); //Passa a posição da parcela no vetor por parametro para 'int q'

     }else{
        printf ("\nCódigo informado não é compativel com a parcela desejada\n");
        printf ("Por favor, tente novamente <ENTER>.");
        do{ //VALIDA SE A PESSOA APERTOU ENTER
            fflush (stdin);
            enter = getch();
        }while (enter != 13);
        
        mudarParc();
     }
}
//------------------------------------------------------------------------------
int subMenuMudarPac (int p, int cliente){
    int op = -1;
    
    do{
        fflush (stdin);
        system ("cls");
        printf ("Cliente: %s\n", cadastro[cliente].nome);
        printf ("PARCELA: %s\n\n",registro[p].idPar);
        printf ("  1  - Alterar Data Vencimento\n");
        printf ("  2  - Alterar Data Recebimento\n");
        printf ("  3  - Alterar Valor\n");
        printf (" ESC - Menu Parcela\n");
        printf (" Escolha uma opção: ");
        op = getch ();
       if (op-48>=0 && op-48<=9) printf ("%d",op-48); 
       Sleep (timerMenu);
    }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 27);
        

    return op;
     
}
//------------------------------------------------------------------------------
void menuMudarPar (int q, int c){
     int k;
     bool flag;

     
     k = subMenuMudarPac (q, c);
     while (k > 48 && k < 53){ //Isto é k entre 1 e 4 (Tabela ASCII)
         
         //ALTERAR DATA DE VENCIMENTO  
         if (k == 49){
            flag = false;
            while (not flag){ //VALIDA A DATA QUE SERÁ ALTERADA
                  system ("cls");
                  printf ("Alterar PARCELA  : %s\n",registro[q].idPar);
                  printf ("-----------------------------------\n");
                  printf ("Cliente          : %s\n", cadastro[c].nome);
                  printf ("Vencimento Atual : %s\n", registro[q].venc);
                  printf ("-----------------------------------\n");
                  
                  fflush (stdin);
                  printf ("Nova Data Vencimento(Ex: 02/11/21): ");
                  gets (tmp);
                  flag = validaDate (tmp);
                  if (not flag){ 
                     printf ("Data Inválida.\n");
                     printf ("Tentar novamente <ENTER>");
                     do{ //VALIDA SE A PESSOA APERTOU ENTER
                         fflush (stdin);
                         enter = getch();
                     }while (enter != 13);
                  }
            }while(not flag);
            
            strcpy (registro[q].venc, tmp); //Se a data for valida é salvo a nova data no vetor.
            registro[q].venc[8] = '\0';
            
            system ("cls");
            printf ("Alterar PARCELA  : %s\n",registro[q].idPar);
            printf ("-----------------------------------\n");
            printf ("Cliente          : %s\n", cadastro[c].nome);
            printf ("Novo Vencimento  : %s\n", registro[q].venc);
            printf ("-----------------------------------\n");
            printf ("Parcela alterada com sucesso.\n");
            printf ("<ENTER> para voltar");
            do{
               enter = getch();
            }while (enter != 13);
            
            k = subMenuMudarPac (q, c); //Para voltar ao subMenuMudarParc para ficar em loop ate k= 27 (Tabela ASCII = ESC).
            
         }     
         
         //ALTERAR DATA RECEBIMENTO
         if (k == 50){
            flag = false;
            while (not flag){ //VALIDA A DATA QUE SERÁ 
                  system ("cls");
                  printf ("Alterar PARCELA  : %s\n",registro[q].idPar);
                  printf ("-----------------------------------\n");
                  printf ("Cliente          : %s\n", cadastro[c].nome);
                  printf ("Recebido Atual : %s\n", registro[q].rec);
                  printf ("-----------------------------------\n");
                  
                  fflush (stdin);
                  printf ("Nova Data Recebimento(Ex: 02/11/21): ");
                  gets (tmp);
                  flag = validaDate (tmp);
                  if (not flag){ 
                     printf ("Data Inválida.\n");
                     printf ("Tentar novamente <ENTER>");
                     do{ //VALIDA SE A PESSOA APERTOU ENTER
                         fflush (stdin);
                            enter = getch();
                     }while (enter != 13);
                  }
            }while(not flag);
            
            strcpy (registro[q].rec, tmp); //Se a data for valida é salvo a nova data no vetor.
            registro[q].rec[8] = '\0';
            
            system ("cls");
            printf ("Alterar PARCELA  : %s\n",registro[q].idPar);
            printf ("-----------------------------------\n");
            printf ("Cliente          : %s\n", cadastro[c].nome);
            printf ("Novo Recebido    : %s\n", registro[q].rec);
            printf ("-----------------------------------\n");
            printf ("Parcela alterada com sucesso.\n");
            printf ("<ENTER> para voltar");
            do{
               enter = getch();
            }while (enter != 13);
            
            k = subMenuMudarPac (q, c); //Para voltar no subMenuMudarParc paficar em loop ate k= 27 (Tabela ASCII = ESC). 
         }
         
         //ALTERAR VALOR DA PARCELA
         if (k == 51){
            do {
               system ("cls");
               printf ("Alterar PARCELA  : %s\n",registro[q].idPar);
               printf ("-----------------------------------\n");
               printf ("Cliente          : %s\n", cadastro[c].nome);
               printf ("Valor Atual      : %s\n", registro[q].val);
               printf ("-----------------------------------\n");
                
               fflush(stdin);
               printf ("Valor da Parcela (Ex: 150,00): ");
               gets (tmp);
               if (strtol(tmp, NULL, 10) <= 0){ //Convertendo de CHAR para INT (Função 'strtol')
                  printf ("Valor de parcela Inválido\n");
                  do{
                     enter = getch();
                  }while (enter != 13);
               }
            }while (strtol(tmp, NULL, 10) <= 0);
            
            strcpy (registro[q].val, tmp); //Se a data for valida é salvo a nova data no vetor.
            registro[q].val[8] = '\0';
            
            system ("cls");
            printf ("Alterar PARCELA  : %s\n",registro[q].idPar);
            printf ("-----------------------------------\n");
            printf ("Cliente          : %s\n", cadastro[c].nome);
            printf ("Novo Valor       : %s\n", registro[q].val);
            printf ("-----------------------------------\n");
            printf ("Parcela alterada com sucesso.\n");
            printf ("<ENTER> para voltar");
            do{
               enter = getch();
            }while (enter != 13);
            
            k = subMenuMudarPac (q, c); //Para voltar no subMenuMudarParc paficar em loop ate k= 4.
         }
         if (k == 27){
            menuParcela ();
         }
     }
}
//------------------------------------------------------------------------------
void deletarParcela (){
     char cod[5];
     int k = -1, j, i;
     
     while (k == -1){
         system("cls");
         printf("EXCLUSÃO DE PARCELAS\n\n");
         printf("Código da parcela (Ex:1234/1): "); 
         gets(cod);
         
         k = buscaBinaria (cod, 0);
     }
     
     j = validaBanco (registro[k].charBanco); //Para buscar o nome do Banco
     i = validaID (registro[k].idCli); //Para buscar o nome do cliente
     
     if ((k != -1) && (registro[k].st != false)){
        registro[k].st = false;
        
        system ("cls");
        printf("EXCLUSÃO DE PARCELAS\n\n");
        printf ("-----------------------------------------\n");
        printf("Nome do Cliente       : %s\n", cadastro[i].nome);
        printf("Código do Cliente     : %s\n", registro[k].idCli);
        printf("Código da parcela     : %s\n", registro[k].idPar);
        printf("Vencimento da parcela : %s\n", registro[k].venc);
        printf("Recebido em           : %s\n", registro[k].rec);
        printf("Valor                 : %s\n", registro[k].val);
        printf("Banco                 : %s\n", nomeBanco[j]);
        printf ("-----------------------------------------\n");
        printf ("Parcela excluida com sucesso.\n");
        printf ("<ENTER> para voltar MENU PARCELA");
        do{
           enter = getch();
        }while (enter != 13);
     }
     menuParcela ();
      
}
//------------------------------------------------------------------------------
void menuBusca (){
     int op;

     do {
         fflush (stdin);
         system ("cls");
         printf ("MENU BUSCA\n\n");
         printf ("  1  - Importar Cliente\n");
         printf ("  2  - Importar Parcelas\n");
         printf ("  3  - Buscar Cliente\n");
         printf ("  4  - Buscar Parcela\n");
         printf (" ESC - Menu Principal\n");
         printf (" Escolha um opção: ");
         op = getch ();
         if (op-48>=0 && op-48<=9) printf ("%d",op-48); 
         Sleep (timerMenu);
     }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 27);
     
     switch (op){
            case 49:
                 if (flagCli){
                    system ("cls");
                    printf ("Dados dos Clientes já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    do{ //VALIDA SE A PESSOA APERTOU ENTER
                        fflush (stdin);
                        enter = getch();
                    }while (enter != 13);
                    menuBusca (); 
                 }else{
                  
                    leArquivo ("CLIENTES.txt");
                    salvaCliente ();
                    apresenta ("AGUARDE, IMPORTANDO...","Obrigado por esperar! <ENTER> voltar ao MENU BUSCA");
                    menuBusca ();
                 }
                 break;
            case 50:
                 if (flagParc){
                    system ("cls");
                    printf ("Dados das Parcelas já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    menuBusca();
                 }else{
                  
                    leArquivo ("PARCELAS.txt");
                    salvaParcela ();
                    apresenta2 ("Obrigado por esperar! <ENTER> voltar ao MENU BUSCAR");
                    menuBusca (); 
                 }
                 break;
            case 51:
                 dadosImp (3, flagCli);
                 mostrarCadastro ("<ENTER> para voltar ao MEU BUSCA");
                 menuBusca ();
                 break;
            case 52:
                 dadosImp (3, flagParc);
                 mostrarParcela ("menu parcela");
                 menuBusca ();
                 break;
            case 27:
                 menuPrincipal ();
                 break;     
     }      
}
//------------------------------------------------------------------------------
void menuReceita (){
     int op;

     do {
         fflush (stdin);
         system ("cls");
         printf ("MENU RECEITAS\n\n");
         printf ("  1  - Personalizado\n");
         printf ("  2  - Resumo por Banco\n");
         printf (" ESC - Menu Principal\n");
         printf (" Escolha um opção: ");
         op = getch ();
         if (op-48>=0 && op-48<=9) printf ("%d",op-48); 
         Sleep (timerMenu);
     }while (op != 49 && op != 50 && op != 27);

     switch (op){
            case 49:
                 dadosImp (4, flagCli);
                 dadosImp (4, flagParc);

                 break;
            case 50:
                 dadosImp (4, flagCli);
                 dadosImp (4, flagParc);
                 resumoBanco ();
                 menuReceita ();
                 break;
            case 27:
                 menuPrincipal ();
                 break;          
     } 
}
//------------------------------------------------------------------------------
void resumoBanco (){
     float totalAberto[6], totalRecebido[6], totalBanco[6];
     float totalAbertoG=0, totalRecebidoG=0, totalBancoG=0;
     
     for (int i=0; i<6; i++){
         totalAberto[i] = 0;
         totalRecebido[i] = 0;
         totalBanco[i] = 0;
     }    
     for (int i = 0; i <= qtLinhasParc; i++){
         for (int j = 0; j < 6; j++){
             if (  (strcmp (registro[i].charBanco, idBanco[j])==0) && (registro[i].st == true)){             
                if (strcmp(registro[i].rec, "N/D") == 0){ //Se data recebimento for NULO
                   totalAberto[j] = totalAberto[j] + registro[i].valor;
                   totalBanco [j] = totalBanco [j] + registro[i].valor;
                }else{
                   totalRecebido[j] = totalRecebido[j] + registro[i].valor;
                   totalBanco   [j] = totalBanco   [j] + registro[i].valor;
                } 
             }
         }
     }     
     for (int i=0; i<6; i++){
         totalAbertoG = totalAbertoG + totalAberto[i];
         totalRecebidoG = totalRecebidoG + totalRecebido[i];
         totalBancoG = totalBancoG + totalBanco[i];
     }   
     system ("cls"); 
     printf ("-----------------------------------------------------------\n");
     printf ("  COD      BANCO      A RECEBER    RECEBIDO       TOTAL\n");
     printf ("-----------------------------------------------------------\n");
     for (int i = 0; i < 6; i++){
         printf ("| %.3d | %10s | %10.2f | %10.2f | %10.2f |\n", idBanco[i], nomeBanco[i], totalAberto[i], totalRecebido[i], totalBanco[i]);    
     }
     printf ("-----------------------------------------------------------\n");
     printf ("             TOTAL | %10.2f | %10.2f | %10.2f |\n", totalAbertoG, totalRecebidoG, totalBancoG);
     printf ("-----------------------------------------------------------\n");
     printf ("<ENTER> para voltar MENU RECEITAS");
     do{ //VALIDA SE A PESSOA APERTOU ENTER
         fflush (stdin);
         enter = getch();
     }while (enter != 13);
}
//------------------------------------------------------------------------------
void personalizado (){
     
     printf ("TEM QUE ADAPTAR PARA A OPÇÃO DE PEGAR TODOS...\\n\n\n");
     
     char clienteID[5];
    char banco[5];
     int k = -1;
     int ord, parcela;
     
     system ("cls");
     do{
        fflush (stdin);
        printf ("Código Cliente: ");
        gets (clienteID);
        k = validaID (clienteID);
        if (k == -1 || cadastro[k].status == false){
           printf ("Cliente não cadastrado\n");
           printf ("<ENTER> para tentar novamente\n");
           do{ //VALIDA SE A PESSOA APERTOU ENTER
               fflush (stdin);
               enter = getch();
           }while (enter != 13);
           system ("cls");
        }
     }while (k == -1 || cadastro[k].status == false);
     
     do{
        fflush (stdin);
        printf ("Código do banco: ");
        scanf ("%d",&banco);
        k = validaBanco (banco);
        if (k == -1){
           printf ("Banco não cadastrado\n");
           printf ("<ENTER> para tentar novamente\n");
           do{ //VALIDA SE A PESSOA APERTOU ENTER
               fflush (stdin);
               enter = getch();
           }while (enter != 13);
           system ("cls");
           printf ("Código Cliente: %s\n", clienteID);
        }    
     }while (k == -1); 
     
     do{
        fflush (stdin);
        printf ("Ordenar por [1]-PARCELA  [2]-VENCIMENTO: ");
        scanf ("%d",&ord);
        if (ord !=1 && ord !=2){
           system ("cls");
           printf ("Código Cliente: %s\n", clienteID);
           printf ("Código do banco: %d\n", banco);
        
        }
     }while (ord !=1 && ord !=2);
     
     if (ord == 1){
        selectionNumeroPar ();
     }else{
        selectionVencPar ();
     }
     
     do{
        fflush (stdin);
        printf ("Parcelas em [1]ABERTO ou [2]RECEBIDAS ou <ENTER> para ambos: ");
        scanf ("%d",&parcela);
        if (parcela !=1 && parcela !=2){
           system ("cls");
           printf ("Código Cliente: %s\n", clienteID);
           printf ("Código do banco: %d\n", banco);
           printf ("Ordenar por [1]-PARCELA  [2]-VENCIMENTO: %d\n",ord);
        }
     }while(parcela !=1 && parcela !=2);
     
     
     
     //VALIDAÇÃO SE TEM A PARCELA MAS NÃO É DO BANCO INFORMADO
     bool j;
     j = false;
     j = parcelaBanco(clienteID, banco);
     
     clienteEUmbanco (clienteID, banco, ord, parcela, j);
     //PASSO POR PARAMETRO
         
}
//------------------------------------------------------------------------------
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
void dadosImp (int tipo, bool flag){
    if (not flag){
        system ("cls");
        printf ("Dados NÃO foram importados!!!\n");
        printf ("<ENTER> para voltar");
        getch();
        if (tipo == 1) menuCliente (); 
        if (tipo == 2) menuParcela ();
        if (tipo == 3) menuBusca ();
        if (tipo == 4) menuReceita ();
    }   
}
//------------------------------------------------------------------------------
void apresenta(char legenda[50], char menu[50]){
     int total;
     int ini = 0, fim = 0, linhasE = 24;
     
     system ("cls");
     total = qtLinhasCli;
     while (total / 24.0 > 0){
           total = total - linhasE;
           ini = ini;
           fim = fim + linhasE;
     system ("cls");
     printf ("IMPORTANDO DADOS DOS CLIENTE...\n");
     printf (" ID          Cliente                  Cidade              UF     RG/CPF/CNPJ\n");
     printf ("-----------------------------------------------------------------------------------\n");
     for (int x=ini;x<=fim;x++){
         if (cadastro[x].status == true){
            printf("%4s | %20s | %25s | %2s | %19s | %d\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident, cadastro[x].status);
            Sleep (20);
         }
     }
     printf ("-----------------------------------------------------------------------------------\n");
     if (total / 24.0 <= 0){
        printf (menu);
        getch ();
     }else{
        printf (legenda);
        Sleep (1000);   
     }
     ini = ini + linhasE;
     }
}
//------------------------------------------------------------------------------
void apresenta2(char menu[50]){
     float total;
     int ini = 0, fim = 0, linhasE = 24;
     
     system ("cls");
     total = qtLinhasParc;
     while (total / 24.0 > 0){
           total = total - linhasE;
           ini = ini;
           fim = fim + linhasE;
     system ("cls");
     printf ("IMPORTANDO DADOS DAS PARCELAS...\n");
     printf ("  Parcela    ID    Vencimento Recebimento    Valor     BC\n");
     printf ("----------------------------------------------------------\n");
     for (int x=ini;x<=fim;x++){
         if (registro[x].st == true){
             printf("%9s | %4s | %9s | %9s | %9s | %.3d\n",registro[x].idPar, registro[x].idCli, registro[x].venc, registro[x].rec, registro[x].val, registro[x].banco);
             Sleep (20);
         }
     }
     printf ("----------------------------------------------------------\n");
     if (total / 24.0 <= 0){
        printf (menu);
        do{ //VALIDA SE A PESSOA APERTOU ENTER
           fflush (stdin);
           enter = getch();
        }while (enter != 13);
     }else{
        printf ("AGUARDE, IMPORTANDO...");
        Sleep (1000);   
     }
     ini = ini + linhasE;
     }
     
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
         
         cadastro[i].status = true;
     }
     //cadastro[0].status = false;
     qtLinhasCli = qtLinhas;
     flagCli = true; //Significa que já realizou a importação dos CLIENTE...
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
         //For para mudar o PONTO do valor da parcela para VIRGULA
         //Pois a função atof não converte certo para float se estiver com PONTO.
         for (int j = 0; j <= strlen(registro[i].val); j++){
             if (registro[i].val[j] ==  '.')
                registro[i].val[j] = ',';
         }
         //Salvar os valores como float, para usar mais pra frente
         registro[i].valor = atof (registro[i].val);  //atof Função converte CHAR para FLOAT.
         
         divisao (i);
         strcpy (registro[i].charBanco, tmp);
         bc = strtol (tmp, NULL, 10); //FUNÇÃO PADRÃO QUE CONVERTE char p/ int
         registro[i].banco = bc;
         
         registro[i].st = true;        
     }
     qtLinhasParc = qtLinhas;
     flagParc = true;        //Significa que já realizou a importação das PARCELA...
}
//------------------------------------------------------------------------------

void selectionNome (){ //Organiza por nome do cliente
     struct Cliente tmpCad;
     
     for (int i=0; i<=qtLinhasCli-1; i++){
         for (int j=i+1; j<=qtLinhasCli; j++){
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
     
     for (int i=0; i<=qtLinhasCli-1; i++){
         for (int j=i+1; j<=qtLinhasCli; j++){
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
     
     for (int i=0; i<=qtLinhasParc-1; i++){
         for (int j=i+1; j<=qtLinhasParc; j++){
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
     struct Parcela dataInv [SIZE_CAD];
     
     //012
     //01/
    for (int i=0; i<=qtLinhasParc; i++){
         dataInv[i].venc[0] = registro[i].venc[6];
         dataInv[i].venc[1] = registro[i].venc[7];
         dataInv[i].venc[2] = registro[i].venc[5];
         dataInv[i].venc[3] = registro[i].venc[3];
         dataInv[i].venc[4] = registro[i].venc[4];
         dataInv[i].venc[5] = registro[i].venc[2];
         dataInv[i].venc[6] = registro[i].venc[0];
         dataInv[i].venc[7] = registro[i].venc[1];
         dataInv[i].venc[8] = '\0';
         printf ("%s\n",dataInv[i].venc);
     }
     system ("pause");
     
     
     for (int i=0; i<=qtLinhasParc-1; i++){
         for (int j=i+1; j<=qtLinhasParc; j++){
             if (strcmp(dataInv[j].venc, dataInv[i].venc) < 0){
                tmpPar = registro[i];
                registro[i]=registro[j];
                registro[j]=tmpPar;
             }           
         }         
     } 
     printf ("\n\n");
     for (int i=0; i<=qtLinhasParc; i++){
         printf ("%s\n",registro[i].venc);
     }
      system ("pause");
}
//------------------------------------------------------------------------------
int validaID (char comp[5]){ //Busca exastiva (da para melhorar se sobrar tempo)
     
     for (int i = 0; i <= qtLinhasCli-1; i++){
         if (strcmp(comp, cadastro[i].id) == 0){
            if (cadastro[i].status == false){
               return -1;
            }
            return i;
         }
     }
     return -1;
}
//------------------------------------------------------------------------------
void maiusc (char palavra[30]){
     for (int i = 0; i <= strlen(palavra); i++){
         tmp2[i] = toupper (palavra[i]); //tmp variavel global
     }
     tmp2[strlen(palavra)] ='\0';
}
//------------------------------------------------------------------------------
int buscaBinaria (char pesquisa[5], int tipo){ //BUSCA PARA ACHAR O número da parcela
    int ini, fim, meio, p = 0; 
    
    /*printf ("%s\n",pesquisa);
    printf ("%d\n", tipo);
    system ("pause");*/
            
    
    if (tipo == 1) qtLinhasParc--;
    
    
    selectionNumeroPar ();
    ini = 0;
    fim = qtLinhasParc;
    while (ini <= fim){
          meio = (ini+fim)/2;
          if (strcmp(registro[meio].idPar, pesquisa) == 0){
             p = meio;
             if (tipo == 1) qtLinhasParc++;
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
    if (tipo == 1) qtLinhasParc++;
    return -1; // retorna -1 número da parcela não encontrado
}
//------------------------------------------------------------------------------
bool validaDate (char data[7]){
     char dia[3], mes[3], ano[5];
     int nDia, nMes, nAno;
                                             //       01234567   0123456789 
     for (int i=0; i<= strlen(data); i++){  //    Ex: 17/01/94   17/01/1994
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
     if (strlen(ano) > 2) return false;
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
       
     if (nDia <=0 || nDia >= 32 || nMes <= 0 || nMes >=13 || nAno < 00 || nAno >= 100){ 
        return false;
     }else{
        return true;
     }        
}
//------------------------------------------------------------------------------
/*void totalGeral (){
     float totalGeral = 0, totalRecebidoG = 0, totalAbertoG = 0;
     
     for (int i = 0; i<= qtLinhasParc; i++){
         if (strcmp (registro[i].rec, "N/D") == 0){
            totalAbertoG = totalAbertoG + registro[i].valor;      //Para TOTAL ABERTO GERAL
            
         }else{
            totalRecebidoG = totalRecebidoG + registro[i].valor;  //Para TOTAL RECEBIDO GERAL 
         }
     }
     totalGeral = totalAbertoG+totalRecebidoG;
     menuResumidoPag (totalAbertoG, totalRecebidoG, totalGeral);
}
//------------------------------------------------------------------------------
void menuResumidoPag (float a, float r, float t){
     
     printf ("RESUMO DAS RECEITAS\n\n");
     printf ("Receitas em Aberto : %.2f\n", a);
     printf ("Receitas Recebido  : %.2f\n", r);
     printf ("Receita TOTAL      : %.2f\n", t);
     getch ();     
}*/
//------------------------------------------------------------------------------
void receitaBancoCliente (int tipo){   //Tipo 1: Banco - Tipo 2: Cliente
     int cod, cont=1, k, parada;
     char cliente[5];
     bool flag;
     float totalBanco = 0, totalCliente = 0;
     
     do{
         
         if (tipo == 1){
            parada = qtLinhasParc;
            printf ("Código do Banco: ");
            scanf ("%d",&cod);
         }
         if (tipo == 2){
            parada = qtLinhasCli;
            printf ("Código do Cliente: ");
            gets (cliente);
            k = validaID(cliente);
         }
         flag = false;
         while (not flag || cont < parada && k != -1 ){
             for (int i=cont-1; i<= cont; i++){
                 if (cod == registro[i].banco || strcmp (cliente, registro[cont].idCli) == 0)
                    flag = true;
             }
         cont++;
     }
     if (not flag && tipo == 1){
        printf ("Banco não cadastrado.\n");
        printf ("<ENTER> para nova consulta");
        do{ //VALIDA SE A PESSOA APERTOU ENTER
            fflush (stdin);
            enter = getch();
        }while (enter != 13);
        system ("cls");
     }
     if (not flag && tipo == 2){
        if (k == -1){
           printf ("Cliente não cadastrado\n");
           printf ("<ENTER> para nova consulta\n");
           do{ //VALIDA SE A PESSOA APERTOU ENTER
               fflush (stdin);
               enter = getch();
           }while (enter != 13);
           system ("cls");
        }
     }
     }while (not flag);

     for (int i=0; i<= qtLinhasParc; i++){
         if (cod == registro[i].banco)
            totalBanco = totalBanco + registro[i].valor;
     }
     
     if (k != 1){
        for (int i=0; i<=qtLinhasParc; i++){
            if (strcmp(cliente, registro[i].idCli) == 0)
                totalCliente = totalCliente + registro[i].valor;
        }
     }
     
     if (tipo == 1){
     printf ("Banco: %d\n",cod);
     printf ("Total: %.2f\n",totalBanco);
     getch();
     }
     if (tipo == 2){
     printf ("Cliente: %s\n",cliente);
     printf ("Total: %.2f\n",totalCliente);
     getch ();
     }     
}
//------------------------------------------------------------------------------
bool parcelaBanco (char cli[5], char bc[5]){
    for (int i=0; i<=qtLinhasParc; i++){
        if ( (strcmp(cli, registro[i].idCli) == 0 ) && ( strcmp (bc, registro[i].charBanco) == 0)  )
           return true;
    }
    return false;
//Isto é, se retornar TRUE significa que tem PELO MENOS 1 parcela no banco desejado
//Caso retorne FALSE significa que não esse cliente NÃO TEM PARCELA NESTE BANCO.
}
//------------------------------------------------------------------------------
void clienteEUmbanco (char cli[5], char bc[5], int orde, int parc, bool flag){ //Serve para imprimir dados de parcela de um cliente de um banco especifico.
     float totalCli;
     float cont=0;
     int k;
     
     system ("cls");
     
     k = validaID (cli); //Só para trazer a posição do vetor do id. Para usar o próximo printf
     printf ("falta fazer busca por parcela de todos os cliente e banco\n\n");
     if (flag){
         printf ("___________________________________________________________\n");
         printf ("CLIENTE: %20s                 Código: %s\n",cadastro[k].nome, cli);
         printf ("-----------------------------------------------------------\n");
         printf ("  Parcela    ID    Vencimento Recebimento    Valor     BC \n");
         printf ("-----------------------------------------------------------\n");
         for (int i=0; i<=qtLinhasParc; i++){
             if ( (strcmp(cli, registro[i].idCli) == 0) && (strcmp (bc, registro[i].charBanco) == 0 ) ){
                //totalCli = totalCli + registro[i].valor; //Pega todos os valores independente do BANCO    
                printf("%9s | %4s | %9s | %9s | %9s | %.3d\n",registro[i].idPar, registro[i].idCli, registro[i].venc, registro[i].rec, registro[i].val, registro[i].banco);
                Sleep (100); 
             }
         }
         printf ("-----------------------------------------------------------\n");
         printf ("<ENTER> para Nova Consulta");
         do{ //VALIDA SE A PESSOA APERTOU ENTER
               fflush (stdin);
               enter = getch();
         }while (enter != 13); 
     }
     else{
         printf ("-----------------------------------------------------------\n");
         printf ("  %s: não tem parcelas no Banco (%d)\n",cadastro[k].nome,bc);
         printf ("-----------------------------------------------------------\n");
         printf ("<ENTER> para Nova Consulta");
         do{ //VALIDA SE A PESSOA APERTOU ENTER
               fflush (stdin);
               enter = getch();
         }while (enter != 13);
     } 
     printf ("\n%.2f",totalCli);  

}
//------------------------------------------------------------------------------
void Bancos (){   
    
     strcpy (idBanco[0], "0");
     idBanco[0][3] = '\0';
     strcpy (nomeBanco[0], "CARTEIRA");
     nomeBanco[0][8] = '\0';
     
     strcpy (idBanco[1], "001");
     idBanco[1][3] = '\0';
     strcpy (nomeBanco[1], "BB");
     nomeBanco[1][2] = '\0';
     
     strcpy (idBanco[2], "104");
     idBanco[2][3] = '\0';
     strcpy (nomeBanco[2], "CAIXA");
     nomeBanco[2][5] = '\0';
     
     strcpy (idBanco[3], "237");
     idBanco[3][3] = '\0';
     strcpy (nomeBanco[3], "BRADESCO");
     nomeBanco[3][8] = '\0';
     
     strcpy (idBanco[4], "260");
     idBanco[4][3] = '\0';
     strcpy (nomeBanco[4], "NUBANK");
     nomeBanco[4][6] = '\0';
     
     strcpy (idBanco[5], "341");
     idBanco[5][3] = '\0';
     strcpy (nomeBanco[5], "ITAÚ");
     nomeBanco[5][4] = '\0';
}
//------------------------------------------------------------------------------
int validaBanco (char bc[5]){ 
     for (int i=0; i<= totalBanco; i++){
     //printf ("%s\n", idBanco[i]);
     //system ("pause");
     }
     
     for (int i=0; i<=totalBanco; i++){
         if (strcmp (bc, idBanco[i]) == 0)
            return i;
     }
     return -1;
}
//------------------------------------------------------------------------------
void resumoSintBanco (){
     char todosBancos[6], codBanco[5];
     int codBancoInt;
     int parcela, ordem;
     int k=-1;
     
     //ENTRADA DO CÓDIGO DO BANCO A SER SELECIONADO
     do{
        system ("cls");
        printf ("Código do Banco ou <ENTER> Para todos: ");
        gets (codBanco);
        if (codBanco[0] == '\0'){ 
           k = -10;
           strcpy (todosBancos, "TODOS");
           todosBancos[5] = '\0';
        }else{
           k = validaBanco(codBanco); //Recebe a posição do banco no vetor idBanco ou nomeBanco
           codBancoInt = strtol (idBanco[k], NULL, 10); //TRAZ CODbANCO COMO int.
        }
     }while (k == -1);
     
     //SITUAÇÃO DA PARCELA A SER SELECIONADA
     do{
        system ("cls");
        if (k == -10){
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", "TODOS");
        }else{
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", nomeBanco[k]);
        } 
         
        printf ("Parcelas em [1]Aberto ou [2]Recebidas ou <ENTER>Todas: ");
        enter = getch();
        parcela = enter-48;
        if (parcela>=0 && parcela<10){
           printf ("%d\n",enter-48);
           Sleep (timerMenu);
        } 
     }while (parcela !=  1 && parcela != 2 && enter != 13);
     
     //TIPO DE ORDENAÇÃO
     do{
        system ("cls");
        if (k == -10){
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", "TODOS");
        }else{
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", nomeBanco[k]);
        }
        if (enter == 13){ 
           printf ("Parcelas em [1]Aberto ou [2]Recebidas ou <ENTER>Todas: %s\n","TODOS");
        }else{
           if (parcela == 1){
              printf ("Parcelas em [1]Aberto ou [2]Recebidas ou <ENTER>Todas: %s\n", "PARCELAS EM ABERTO");
           }else{
              printf ("Parcelas em [1]Aberto ou [2]Recebidas ou <ENTER>Todas: %s\n", "PARCELAS RECEBIDAS");   
           }   
        } 

        printf ("Ordem por [1]Código ou [2]Nome: ");
        scanf ("%d", &ordem);
     }while (ordem != 1 && ordem != 2);
     
     if (ordem == 1){
        selectionIdCliente ();
     }else{
        selectionNome ();   
     }

     
     float totalAreceber = 0;
     float totalGeral = 0;
     for (int i=0; i<= qtLinhasParc; i++){
         if ( ((strcmp(todosBancos, "TODOS") == 0) || (codBancoInt == registro[i].banco))  &&  (registro[i].st == true)){
            if ( ( (parcela == 1) && (strcmp (registro[i].rec, "N/D")==0) )  ||  ( (parcela == 2)  && ( (strcmp (registro[i].rec, "N/D")>0  || strcmp (registro[i].rec, "N/D")<0)) ) || (parcela == -35)  )
               totalGeral = totalGeral + registro[i].valor; //PARA FAZER O % DE CADA CLIENTE  
         }   
     }
     printf ("totalGeral: %f\n",totalGeral);
     system ("pause");
     float totalCliente;
     char nome[30];
     char codCliente[5];
     bool flagCliente;
     int idCadCli, idRegCli;
     int linha = 0;
     int s;
     
     system ("cls");
     for (int i=0; i<=qtLinhasCli; i++){
         totalCliente = 0;
         if (cadastro[i].status == true){
            strcpy (nome, cadastro[i].nome);
            strcpy (codCliente, cadastro[i].id);
            
            for (int j=0; j<= qtLinhasParc; j++){
                flagCliente = true;
                //codBancoInt = strtol (codBanco, NULL, 10);    // converte char p/ int
                
                if ( (parcela != -35) && (codBancoInt != registro[j].banco) )
                   flagCliente = false;
                   
                s = palavraIgual (registro[j].rec, "N/D"); //s=1 (palavras iguais)  s=0 (palavras diferentes)
                //PARCELA = 1 (ABERTO)  PARCELA = 2 (RECEBIDO)
                if ( (parcela == 1) && ( s == 0 ) ){
                   flagCliente = false; //PARCELA NÃO ESTA ABERTA (JÁ FOI RECEBIDA)
                   
                if ( (parcela == 2) && ( s == 1 ) ){
                   flagCliente == false; //PARCELA ESTA EM ABERTO (NÃO FOI RECEBIDA)
                   
                idCadCli = strtol (codCliente, NULL, 10);     //Convertr CHAR p/ INT
                idRegCli = strtol (registro[j].idCli, NULL, 10); //Convertr CHAR p/ INT
                if ( (idCadCli != idRegCli) || (registro[j].st == false) )
                   flagCliente = false;
                   
                if (flagCliente == true)
                   totalCliente = totalCliente + registro[j].valor;
            }
         }
         float porcentagem;
         char bancoPesq[15];
         if (totalCliente > 0){
            if (strcmp(todosBancos, "TODOS")==0){
               strcpy(bancoPesq, "TODOS");
            }else{
               strcpy(bancoPesq, nomeBanco[k]);   
            }
            if (linha==0){
            if (parcela == 1){
               printf ("Resumo por Cliente. Banco:%s  Situação:%s\n",bancoPesq, "EM ABERTO");
            }else{
               printf ("Resumo por Cliente. Banco:%s  Situação:%s\n",bancoPesq, "RECEBIDO");
            }
            printf ("-------------------------------------------------------\n");
            printf ("  ID              Cliente             TOTAL       %%\n");
            printf ("-------------------------------------------------------\n");
            }//printf ("| %.3d | %10s | %10.2f | %10.2f | %10.2f |\n",
            porcentagem = (totalCliente*100)/totalGeral;
            printf ("| %4s | %25s | %8.2f | %5.2f |\n", codCliente, nome, totalCliente, porcentagem);
            //Sleep (300);
            linha = linha +1;
         }
         if (linha==24){
            printf ("---------------------------------------------------------\n");
            printf ("<ENTER> para continuar");
            linha = 0;
            do{
               enter = getch();  
            }while (enter != 13); 
            system ("cls");
         }
     }
     printf ("---------------------------------------------------------\n");
     printf ("                              TOTAL: %8.2f\n",totalGeral);                  
     system ("Pause");


}

//------------------------------------------------------------------------------
void consutaTodasParcela (){
     char codCli[5], codBan[5], parcela[2];
     char nomeCli[30], nomeBan[30], tipoParc[5];
     int ordem;
     int k, j;
     
     if (qtLinhasParc > 0 && qtLinhasCli > 0){
        //PEGAR O CÓDIGO DO CLIENTE
        do{
           system ("cls");
           printf ("Consulta por  Parcelas\n\n");
           printf ("Código do Cliente ou <ENTER> TODOS: ");
           gets (codCli);
           k = validaID (codCli);
           if (k == -1 && codCli[0] != '\0'){
              printf ("Cliente não cadastrado\n");
              printf ("<ENTER> tentar novamente");
              do{
                 enter = getch();
              }while (enter != 13);
           }
              
        }while (k == -1 && codCli[0] != '\0');
        if (codCli[0] == '\0'){
           strcpy (nomeCli, "TODOS");
           nomeCli[5] = '\0';
        }else{
           strcpy (nomeCli, cadastro[k].nome);
           nomeCli[strlen(cadastro[k].nome)] = '\0'; 
        }
        
        //PEGAR O NOME DO BANCO
        do{
           system ("cls");
           printf ("Consulta por  Parcelas\n\n");
           printf ("Código do Cliente ou <ENTER> TODOS: %s\n",nomeCli);
           
           printf ("Código Banco ou <ENTER> TODOS: ");
           gets (codBan);
           j = validaBanco (codBan);
           if (j == -1 && codBan[0] != '\0'){
              printf ("Banco não cadastrado\n");
              printf ("<ENTER> tentar novamente");
              do{
                 enter = getch();
              }while (enter != 13);
           }
        }while (j == -1 && codBan[0] != '\0');
        if (codBan[0] == '\0'){
           strcpy (nomeBan, "TODOS");
           nomeBan[5] = '\0';
        }else{
           strcpy (nomeBan, nomeBanco[j]);
           nomeBan[strlen(nomeBanco[j])] = '\0';
        }
        
        //PEGAR O TIPO DE RECEITA
        do{
           system ("cls");
           printf ("Consulta por  Parcelas\n\n");
           printf ("Código do Cliente ou <ENTER> TODOS: %s\n",nomeCli);
           printf ("Código Banco ou <ENTER> TODOS: %s\n",nomeBan);
           
           printf ("Parcelas [1] Abertas ou [2] Recebidas ou <ENTER> Ambas: ");
           gets (parcela);
           if (parcela[0] != '1' && parcela[0] != '2' && parcela[0] != '\0'){
              printf ("Banco não cadastrado\n");
              printf ("<ENTER> tentar novamente");
              do{
                 enter = getch();
              }while (enter != 13);
           }
        }while (parcela[0] != '1' && parcela[0] != '2' && parcela[0] != '\0');
        if (parcela[0] == '\0'){
           strcpy (tipoParc, "AMBAS");
           tipoParc[5] = '\0';
        }else{
           strcpy (tipoParc, parcela);
           tipoParc[strlen(parcela)] = '\0';
        }
        
        //TIPO DE ORDENAÇÃO
        do{
           system ("cls");
           printf ("Consulta por  Parcelas\n\n");
           printf ("Código do Cliente ou <ENTER> TODOS: %s\n",nomeCli);
           printf ("Código Banco ou <ENTER> TODOS: %s\n",nomeBan);
           printf ("Parcelas [1] Abertas ou [2] Recebidas ou <ENTER> Ambas: %s\n",tipoParc);
           
           printf ("Ordem [1]-Parcela  [2]-Vencimento: ");
           scanf ("%d", &ordem);
            if (ordem != 1 && ordem != 2){
              printf ("<ENTER> tentar novamente");
              do{
                 enter = getch();
              }while (enter != 13);
           }
        }while (ordem != 1 && ordem != 2);
        //ORDENAÇÃO
        if (ordem == 1){
           selectionNumeroPar ();
        }else{
           selectionVencPar ();   
        }
        
        float totalCliente = 0;
        int linha = 0;
        bool flag;
        int P, Q;
        system ("cls");
        for (int i=0; i<=qtLinhasParc; i++){
            flag = true;
            
            P = palavraIgual (nomeCli,"TODOS");
            Q = palavraIgual (codCli, registro[i].idCli);
            if ( (P == 0) && (Q == 0) )
               flag = false;
            
            P = palavraIgual (nomeBan, "TODOS");
            Q = palavraIgual (codBan, registro[i].charBanco);
            if ((P==0) && (Q == 0))
               flag = false;
            
            P = palavraIgual (registro[i].rec, "N/D");
            if ((parcela[0]=='1') && (P==1))
               flag = false;
            
            P = palavraIgual (registro[i].rec, "N/D");
            if ((parcela[0]=='2' && (P==0)))
               flag = false;
            
            if ((flag==true) && (registro[i].st == true)){
               if (linha==0){
                  if (parcela[0]=='1') printf ("Resumo por Cliente                       Banco: %s                      Situação: %s\n",nomeBan, "RECEBIDO");
                  if (parcela[0]=='2') printf ("Resumo por Cliente                       Banco: %s                      Situação: %s\n",nomeBan, "A RECEBER");
                  if (parcela[0]=='\0')printf ("Resumo por Cliente                       Banco: %s                      Situação: %s\n",nomeBan, tipoParc);
                  printf ("----------------------------------------------------------------------------------------------\n");
                  printf ("   ID              CLIENTE           PARCELA      VENC        REC       VALOR        BANCO \n");
                  printf ("----------------------------------------------------------------------------------------------\n");
               }
               printf ("| %4s | %25s | %s | %9s | %9s | %8.2f | %10s |\n", registro[i].idCli, cadastro[validaID(registro[i].idCli)].nome, registro[i].idPar, registro[i].venc, registro[i].rec, registro[i].valor, nomeBanco[validaBanco(registro[i].charBanco)] );                                     
               Sleep (50);
               linha++;
               totalCliente = totalCliente + registro[i].valor;
               if (linha == 24){
                  printf ("----------------------------------------------------------------------------------------------\n");
                  printf ("<ENTER> para continuar");
                  do{
                     enter = getch();
                  }while(enter != 13);
                  linha = 0;
                  system ("cls");                  
               }
            }
        }
        printf ("----------------------------------------------------------------------------------------------\n");
        printf ("                                                                TOTAL: %8.2f\n", totalCliente);
        printf ("<ENTER> para MENU RECEITAS");
        do{
           enter = getch();
        }while(enter != 13);
     
     }else{
           printf ("TABELA DE PARCELAS ESTÁ SEM DADOS <ENTER>");
           do{
              enter = getch();
           }while(enter != 13);
     }
}
//------------------------------------------------------------------------------
int palavraIgual (char p1[30], char p2[30]){
    int i=0;
    
    while (p1[i] == p2[i] && p1[i] != '\0' && p2[i] != '\0'){
          i++;     
    }
    if (p1[i] == '\0' && p2[i] == '\0'){
       return 1; //String IGUAIS
    }else{
       return 0; //String DIFERENTES  
    }
}

//------------------------------------------------------------------------------




void creditos (){

     system ("cls");
     printf ("*--------------------------xxx CRÉDITOS xxx------------------------*\n");
     printf ("* Trabalho Desenvolvido Para o Segundo Semetre - 2021              *\n");
     printf ("* Curso      : Análise e Desenvolvimento de Sistemas               *\n");
     printf ("* Diciplina  : Algoritmo e Lógia de Programação II                 *\n");
     printf ("* Instituição: Unicesumar                                          *\n");
     printf ("* Academicos : Ana Elisa Tubino        Função: Scrum Master  e Dev *\n");
     printf ("*              Guilherme Arraes                Product Owner e Dev *\n");
     printf ("*              Tiago Freire                    UI/UX Design  e Dev *\n");
     printf ("*--------------------------xxxxxxxxxxxxxxxx------------------------*\n");
}
//------------------------------------------------------------------------------
