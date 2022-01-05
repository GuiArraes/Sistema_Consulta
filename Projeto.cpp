#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

#define SIZE_CAD 200

/*
  ACADêMICOS:                               RA:
             Ana Elisa Tubino                  21097708-2
             Guilherme Andrade Costa Arraes    21032425-2
             Tiago Freire                      21129172-2
*/

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
int suporte;
bool flagCli, flagParc;
int enter, timerMenu;
int idBancoInt[15];
char idBanco[15][5];
char nomeBanco [20][15];
int totalBanco;
struct Cliente cadastro[SIZE_CAD];
struct Parcela registro[SIZE_CAD];
//*****************************XXXXXXXXXXXXXXXXX******************************//
//******************INICIALIZAÇÃO DOS PROCEDIMENTOE FUNÇÕES*******************//
void menuPrincipal ();
void imporClieParc ();
void menuCliente ();
void mostrarCadastro (char descricao[50]);
int menuMudarCli (int p);
void mudarCliente ();
void cadastrarCliente ();
void menuDeletarCliente ();
bool deletarCliente (char cod[5]);
void menuParcela ();
void mostrarParcela (char opMenu[15]);
void addParcela ();
void mudarParc ();
int subMenuMudarPac (int p, int cliente);
void menuMudarPar (int q, int c);
void deletarParcela ();
void menuBusca ();
void menuConsulta ();
void resumoBanco ();
void resumoSintCliente ();
void consutaTodasParcela ();
void tabelaBanco ();

void leArquivo(char nomeArq[15]);
void dadosImp (int tipo, bool flag);
void apresenta(char legenda[50], char menu[50]);
void apresenta2(char menu[50]);
void divisao (int id);
void divisaoCPF (int id);
void salvaCliente ();
void salvaParcela ();
void selectionNome ();
void selectionIdCliente ();
void selectionNumeroPar ();
void selectionVencPar ();
bool validaDate (char data[7]);
int validaID (char comp[5]);
int validaBanco (char bc[5]);
void Bancos ();
void maiusc (char palavra[30]);
int palavraIgual (char p1[30], char p2[30]);
int buscaBinaria (char pesquisa[5], int tipo);
void creditos ();
void notaDevs ();
//******************XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*******************//
//-----------------------------PROGRAMA PRINCIPAL-----------------------------//
int main (){
    setlocale(LC_ALL,"portuguese");
      
    flagCli = false; 
    flagParc = false;
    
    timerMenu = 300;
    totalBanco = 5;
    Bancos ();
    
    menuPrincipal ();
    
return 0;
}
//-----------------------------XXXXXXXXXXXXXXXXXX-----------------------------//
//---------------------------PROCEDIMENTOS E FUNÇÕES--------------------------//
void menuPrincipal (){
    int op=-1;
    
    do{
        system ("cls");
        printf ("MENU PRINCIPAL\n\n");
        printf ("  1  - Menu Cliente\n");
        printf ("  2  - Menu Parcelas\n");
        printf ("  3  - Menu Busca\n");
        printf ("  4  - Menu Consulta\n");
        printf ("  5  - Importar Clientes/Parcelas\n");
        printf ("  6  - Nota dos Desenvolvedores\n");
        printf ("  0  - Créditos\n");
        printf (" ESC - Sair\n");
        printf (" Escolha uma opção: ");
        op = getch ();
        if (op-48>=0 && op-48<=9) printf ("%d",op-48);
        Sleep (timerMenu);  
    }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 53 && op != 54 && op != 48 && op != 27);
    
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
                menuConsulta ();
                break;
           case 53:
                imporClieParc ();
                menuPrincipal ();
                break;
           case 54:
                notaDevs ();
                menuPrincipal ();
                break;
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
void imporClieParc (){
     system ("cls");
     if (flagCli){
        printf ("Dados dos Clientes já IMPORTADOS\n");
        printf ("<ENTER> continuar");
        do{
           enter = getch();
        }while(enter != 13);  
     }else{
        leArquivo ("CLIENTES.txt");
        salvaCliente ();
        apresenta ("AGUARDE, IMPORTANDO...", "Obrigado por esperar! <ENTER> continuar");  
     }
     
     if (flagParc){
        system ("cls");
        printf ("Dados das Parcelas já IMPORTADOS\n");
        printf ("<ENTER> continuar");
     }else{
        leArquivo ("PARCELAS.txt");
        salvaParcela ();
        apresenta2 ("Obrigado por esperar! <ENTER> voltar ao MENU PRINCIPAL");
        menuPrincipal ();
     }
     do{
        enter = getch();
     }while(enter != 13);
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
                 apresenta ("AGUARDE, IMPORTANDO...", "Obrigado por esperar! <ENTER> voltar ao MENU CLIENTE");
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
     char ord[2];
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
        gets(ord);
     }while (ord[0] != '1' && ord[0] != '2');
     
     if (ord[0] == '1'){
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
                 menuParcela ();
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
        scanf ("%d",&registro[qtLinhasParc].banco);
     }while (registro[qtLinhasParc].banco != 0 &&
      registro[qtLinhasParc].banco != 001 &&
      registro[qtLinhasParc].banco != 104 && 
      registro[qtLinhasParc].banco != 237 && 
      registro[qtLinhasParc].banco != 260 &&
      registro[qtLinhasParc].banco != 341);
          
      //j = validaBanco (registro[qtLinhasParc].banco);
      
      system ("cls");
      printf ("Adicionar Parcelas\n\n");
      printf ("Cliente           : %s\n", cadastro[k].nome);
      printf ("Código do Cliente : %s\n", cadastro[k].id);
      printf ("Código Parcela    : %s\n", registro[qtLinhasParc].idPar);
      printf ("Valor             : %s\n", registro[qtLinhasParc].val);
      printf ("Banco             : %d\n\n",registro[qtLinhasParc].banco);
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
void menuConsulta (){
     int op;

     do {
         fflush (stdin);
         system ("cls");
         printf ("MENU RECEITAS\n\n");
         printf ("  1  - Resumo por Cliente\n");
         printf ("  2  - Resumo Sintético das Receitas\n");
         printf ("  3  - Resumo Banco\n ");
         printf (" 4  - Tabela de Bancos\n");
         printf (" ESC - Menu Principal\n");
         printf (" Escolha um opção: ");
         op = getch ();
         if (op-48>=0 && op-48<=9) printf ("%d",op-48); 
         Sleep (timerMenu);
     }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 27);

     switch (op){
            case 49:
                 dadosImp (4, flagCli);
                 dadosImp (4, flagParc);
                 resumoSintCliente ();
                 do{
                    enter = getch();
                 }while (enter != 13);
                 menuConsulta ();
                 break;
            case 50:
                 consutaTodasParcela ();
                 do{
                    enter = getch();
                 }while (enter != 13);
                 menuConsulta ();
                 break;
            case 51:
                 dadosImp (4, flagCli);
                 dadosImp (4, flagParc);
                 resumoBanco ();
                 menuConsulta ();
                 break;
            case 52:
                 tabelaBanco ();
                 printf ("<ENTER> voltar MENU CONSULTA");
                 do{
                    enter = getch();
                 }while (enter != 13);
                 menuConsulta();
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
     printf ("RESUMO SINTÉTICO POR BANCO CADASTRADO\n"); 
     printf ("---------------------------------------------------------------\n");
     printf ("  COD          BANCO      A RECEBER    RECEBIDO      TOTAL\n");
     printf ("---------------------------------------------------------------\n");
     for (int i = 0; i < 6; i++){
         printf ("| %4s | %10s | %10.2f | %10.2f | %10.2f |\n", idBanco[i], nomeBanco[i], totalAberto[i], totalRecebido[i], totalBanco[i]);    
     }
     printf ("---------------------------------------------------------------\n");
     printf ("                 TOTAL | %10.2f | %10.2f | %10.2f |\n", totalAbertoG, totalRecebidoG, totalBancoG);
     printf ("---------------------------------------------------------------\n");
     printf ("<ENTER> para voltar MENU RECEITAS");
     do{ //VALIDA SE A PESSOA APERTOU ENTER
         fflush (stdin);
         enter = getch();
     }while (enter != 13);
}
//------------------------------------------------------------------------------
void resumoSintCliente (){
     char todosBancos[6], codBanco[5], parcela[2];
     char nomeBan[15];
     char ordem[2];
     int codBancoInt;
     int k=-1;
     
     //ENTRADA DO CÓDIGO DO BANCO A SER SELECIONADO
     do{
        system ("cls");
        printf ("RESUMO POR CLIENTE\n\n");
        printf ("Código do Banco ou <ENTER> Para todos: ");
        gets (codBanco);
        if (codBanco[0] == '\0'){ 
           k = -10;
           strcpy (todosBancos, "TODOS");
           todosBancos[5] = '\0';
        }else{
           k = validaBanco(codBanco); //Recebe a posição do banco no vetor idBanco ou nomeBanco
           codBancoInt = strtol (idBanco[k], NULL, 10); //TRAZ CODbANCO COMO int.
           strcpy (nomeBan,  nomeBanco[validaBanco(codBanco)]);
        }
     }while (k == -1);
     
     //SITUAÇÃO DA PARCELA A SER SELECIONADA
     do{
        system ("cls");
        if (k == -10){
           printf ("RESUMO POR CLIENTE\n\n");
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", "TODOS");
        }else{
           printf ("RESUMO POR CLIENTE\n\n");
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", nomeBanco[k]);
        } 
         
        printf ("Parcelas em [1] Aberto ou [2] Recebidas ou <ENTER>Todas: ");
        gets (parcela); 
     }while (parcela[0] !=  '1' && parcela[0] != '2' && parcela[0] != '\0');
     
     //TIPO DE ORDENAÇÃO
     do{
        system ("cls");
        if (k == -10){
           printf ("RESUMO POR CLIENTE\n\n");
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", "TODOS");
        }else{
           printf ("RESUMO POR CLIENTE\n\n");
           printf ("Código do Banco ou <ENTER> Para todos: %s\n", nomeBanco[k]);
        }
        if (parcela[0] == '\0'){ 
           printf ("Parcelas em [1] Aberto ou [2] Recebidas ou <ENTER>Todas: %s\n","TODOS");
        }else{
           if (parcela[0] == '1'){
              printf ("Parcelas em [1] Aberto ou [2] Recebidas ou <ENTER>Todas: %s\n", "PARCELAS EM ABERTO");
           }else{
              printf ("Parcelas em [1] Aberto ou [2] Recebidas ou <ENTER>Todas: %s\n", "PARCELAS RECEBIDAS");   
           }   
        } 

        printf ("Ordem por [1]Código ou [2]Nome: ");
        gets (ordem);
     }while (ordem[0] != '1' && ordem[0] != '2');
     
     if (ordem[0] == '1'){
        selectionIdCliente ();
     }else{
        selectionNome ();   
     }
 
     float totalAreceber = 0;
     float totalGeral = 0;
     for (int i=0; i<= qtLinhasParc; i++){
         if ( ((strcmp(todosBancos, "TODOS") == 0) || (codBancoInt == registro[i].banco))  &&  (registro[i].st == true)){
            if ( ( (parcela[0] == '1') && (strcmp (registro[i].rec, "N/D")==0) )  ||  ( (parcela[0] == '2')  && ( (strcmp (registro[i].rec, "N/D")>0  || strcmp (registro[i].rec, "N/D")<0)) ) || (parcela[0] == '\0')  )
               totalGeral = totalGeral + registro[i].valor; //PARA FAZER O % DE CADA CLIENTE  
         }   
     }
     
     if (totalGeral == 0){
        if (parcela[0] == '1'){
           system ("cls");
           printf ("%s não tem contas %s", nomeBan, "A RECEBER\n");
           printf ("<ENTER> voltar MENU RECEITA");
           do{
              enter = getch();
           }while (enter != 13);
           menuConsulta ();
        }else{
           system ("cls");
           printf ("%s não tem contas %s", nomeBan, "RECEBIDAS\n");
           printf ("<ENTER> voltar MENU RECEITA");
           do{
              enter = getch();
           }while (enter != 13);
           menuConsulta ();
        }
     }
     float totalCliente;
     char nome[30];
     char codCliente[5];
     bool flagCliente;
     int idCadCli, idRegCli;
     int linha = 0;
     int s, p;
     
     system ("cls");
     for (int i=0; i<=qtLinhasCli; i++){
         totalCliente = 0;
         if (cadastro[i].status == true){
            strcpy (nome, cadastro[i].nome);
            strcpy (codCliente, cadastro[i].id);
            
            for (int j=0; j<= qtLinhasParc; j++){
                flagCliente = true;
                
                s = palavraIgual (codBanco, registro[j].charBanco);
                //printf ("S: %d | CodBancoInt: %d | codBanco: %s | registro[j].charBanco: %s\n", s, codBancoInt, codBanco, registro[j].charBanco);
                //system ("pause");
                if ( (k != -10) && (s == 0) )  //codBanco != registro[j].charBanco
                   flagCliente = false;
                   
                s = palavraIgual (registro[j].rec, "N/D"); //s=1 (palavras iguais)  s=0 (palavras diferentes)
                if ( parcela[0] == '1' &&  s == 0  )
                   flagCliente = false; //PARCELA NÃO ESTA ABERTA (JÁ FOI RECEBIDA)
                
                s = palavraIgual (registro[j].rec, "N/D"); 
                if ( parcela[0] == '2' &&  s == 1  )
                   flagCliente == false; //PARCELA ESTA EM ABERTO (NÃO FOI RECEBIDA)
                   
                //idCadCli = strtol (cadastro[i].id, NULL, 10);     //Convertr CHAR p/ INT
                //idRegCli = strtol (registro[j].idCli, NULL, 10); //Convertr CHAR p/ INT
                s = palavraIgual (cadastro[i].id, registro[j].idCli);
                if ( (s == 0) || (registro[j].st == false) )        //idCadCli != idRegCli
                   flagCliente = false;
                   
                if (flagCliente == true)
                   totalCliente = totalCliente + registro[j].valor;
            }
            //printf ("totalCliente = %f",totalCliente);
            //system ("pause");
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
            if (parcela[0] == '1'){
               printf ("Resumo por Cliente. Banco:%s  Situação:%s\n",bancoPesq, "EM ABERTO");
            }else{
               printf ("Resumo por Cliente. Banco:%s  Situação:%s\n",bancoPesq, "RECEBIDO");
            }
            printf ("--------------------------------------------------------\n");
            printf ("  ID              Cliente             TOTAL       %%\n");
            printf ("--------------------------------------------------------\n");
            }
            porcentagem = (totalCliente*100)/totalGeral;
            printf ("| %4s | %25s | %8.2f | %6.2f |\n", codCliente, nome, totalCliente, porcentagem);
            Sleep (50);
            linha = linha +1;
         }
         if (linha==24){
            printf ("--------------------------------------------------------\n");
            printf ("<ENTER> para continuar");
            linha = 0;
            do{
               enter = getch();  
            }while (enter != 13); 
            system ("cls");
         }
     }
     printf ("----------------------------------------------------------\n");
     printf ("                              TOTAL: %8.2f\n",totalGeral);                  
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
           printf ("CONSULTA POR PARCELAS\n\n");
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
           printf ("CONSULTA POR PARCELAS\n\n");
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
           printf ("CONSULTA POR PARCELAS\n\n");
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
           tipoParc[1] = '\0';
        }
        
        //TIPO DE ORDENAÇÃO
        do{
           system ("cls");
           printf ("CONSULTA POR PARCELAS\n\n");
           printf ("Código do Cliente ou <ENTER> TODOS: %s\n",nomeCli);
           printf ("Código Banco ou <ENTER> TODOS: %s\n",nomeBan);
           printf ("Parcelas [1] Abertas ou [2] Recebidas ou <ENTER> Ambas: %s\n",tipoParc);
           
           printf ("Ordem [1]-Parcelas  [2]-Vencimento: ");
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
            if ((parcela[0]=='1') && (P==0))
               flag = false;
            
            P = palavraIgual (registro[i].rec, "N/D");
            if ((parcela[0]=='2' && (P==1)))
               flag = false;
            
            if ((flag==true) && (registro[i].st == true)){
               if (linha==0){
                  if (parcela[0]=='1') printf ("Resumo por Cliente                       Banco: %s                      Situação: %s\n",nomeBan, "A RECEBER");
                  if (parcela[0]=='2') printf ("Resumo por Cliente                       Banco: %s                      Situação: %s\n",nomeBan, "RECEBIDO");
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
        
         if (totalCliente == 0 && parcela[0] == '2'){
           printf ("Resumo por Cliente\n\n");
           printf ("Código: %5s\n",nomeCli);
           printf ("Banco : %5s\n",nomeBan);
           printf ("NÃO há nenhuma receita RECEBIDA\n\n");
           printf ("<ENTER> para MENU RECEITAS");
           do{
              enter = getch ();
           }while (enter != 13);
           menuConsulta ();
        }
        
        if (totalCliente == 0){
           printf ("Resumo por Cliente\n\n");
           printf ("Código: %5s\n",codCli);
           printf ("Cliente: %s não tem parcelas cadastradas\n\n",cadastro[k].nome);
           printf ("<ENTER> para MENU RECEITAS");
           do{
              enter = getch ();
           }while (enter != 13);
           menuConsulta ();
        }
                
        printf ("----------------------------------------------------------------------------------------------\n");
        printf ("                                                                TOTAL: %8.2f\n", totalCliente);
        printf ("<ENTER> para MENU RECEITAS"); 
     }else{
           printf ("TABELA DE PARCELAS ESTÁ SEM DADOS <ENTER>");
     }
}
//------------------------------------------------------------------------------
void tabelaBanco (){
     
     system ("cls");
     printf ("Tabela dos Bancos. Total: %d\n",totalBanco);
     printf ("----------------------------\n");
     printf ("  COD          BANCOS\n");
     printf ("----------------------------\n");
     for (int i=0; i<=totalBanco; i++){
         printf ("|%5s | %15s   |\n", idBanco[i], nomeBanco[i]);
     }
     printf ("----------------------------\n");
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
          result = fgets(linha[qtLinhas], 200, arq);  // o 'fgets' le ate 199 caracteres ou ate o '\n'
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
        if (tipo == 4) menuConsulta ();
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
     printf ("------------------------------------------------------------------------------------\n");
     for (int x=ini;x<=fim;x++){
         if (cadastro[x].status == true){
            printf("%4s | %20s | %25s | %2s | %19s |\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident);
            Sleep (20);
         }
     }
     printf ("------------------------------------------------------------------------------------\n");
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
     printf ("-----------------------------------------------------------\n");
     for (int x=ini;x<=fim;x++){
         if (registro[x].st == true){
             printf("%9s | %4s | %9s | %9s | %9s | %.3d\n",registro[x].idPar, registro[x].idCli, registro[x].venc, registro[x].rec, registro[x].val, registro[x].banco);
             Sleep (20);
         }
     }
     printf ("-----------------------------------------------------------\n");
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
        strcpy (tmp, "SEM IDENTIFICAÇÃO.");
        tmp[18] = '\0';
     }
     
     if (k == 0 || k == 2){
        if (k == 2) ref = ref -1;
        divisao (id);
     }
     
     if (k == 2){
        if (suporte == 1){
           strcpy (tmp, "N/D");
           tmp[3] = '\0';
        }else{
           strcpy (tmp, "SEM IDENTIFICAÇÃO.");
           tmp[18] = '\0';
        }
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
         suporte = 1;
         divisaoCPF (i);
         strcpy (registro[i].rec, tmp);
         suporte = 0;
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
     //01234567
     //01/01/21
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
     }     
     for (int i=0; i<=qtLinhasParc-1; i++){
         for (int j=i+1; j<=qtLinhasParc; j++){
             if (strcmp(dataInv[j].venc, dataInv[i].venc) < 0){
                tmpPar = dataInv[i];
                dataInv[i]=dataInv[j];
                dataInv[j]=tmpPar;
             }           
         }         
     } 
     for (int i=0; i<=qtLinhasParc; i++){
         //01234567
         //21/01/10
         registro[i].venc[0] = dataInv[i].venc[6];
         registro[i].venc[1] = dataInv[i].venc[7];
         
         registro[i].venc[2] = dataInv[i].venc[5];
         
         registro[i].venc[3] = dataInv[i].venc[3];
         registro[i].venc[4] = dataInv[i].venc[4];
         
         registro[i].venc[5] = dataInv[i].venc[2];
         
         registro[i].venc[6] = dataInv[i].venc[0];
         registro[i].venc[7] = dataInv[i].venc[1];
         registro[i].venc[8] = '\0';
     }
}
//------------------------------------------------------------------------------
bool validaDate (char data[7]){
     char dia[3], mes[3], ano[5];
     int nDia, nMes, nAno;
                                             //       01234567     0123456789 
     for (int i=0; i<= strlen(data); i++){  //    Ex: 17/01/94 ou  17.01.1994
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
void Bancos (){   
    
     idBancoInt[0] = 0;
     strcpy (idBanco[0], "0");
     idBanco[0][3] = '\0';
     strcpy (nomeBanco[0], "CARTEIRA");
     nomeBanco[0][8] = '\0';
     
     idBancoInt[1] = 001;
     strcpy (idBanco[1], "001");
     idBanco[1][3] = '\0';
     strcpy (nomeBanco[1], "BB");
     nomeBanco[1][2] = '\0';
     
     idBancoInt[2] = 104;
     strcpy (idBanco[2], "104");
     idBanco[2][3] = '\0';
     strcpy (nomeBanco[2], "CAIXA");
     nomeBanco[2][5] = '\0';
     
     idBancoInt[3] = 237;
     strcpy (idBanco[3], "237");
     idBanco[3][3] = '\0';
     strcpy (nomeBanco[3], "BRADESCO");
     nomeBanco[3][8] = '\0';
     
     idBancoInt[4] = 260;
     strcpy (idBanco[4], "260");
     idBanco[4][3] = '\0';
     strcpy (nomeBanco[4], "NUBANK");
     nomeBanco[4][6] = '\0';
     
     idBancoInt[5] = 341;
     strcpy (idBanco[5], "341");
     idBanco[5][3] = '\0';
     strcpy (nomeBanco[5], "ITAÚ");
     nomeBanco[5][4] = '\0';
}
//------------------------------------------------------------------------------
void maiusc (char palavra[30]){
     for (int i = 0; i <= strlen(palavra); i++){
         tmp2[i] = toupper (palavra[i]); //tmp variavel global
     }
     tmp2[strlen(palavra)] ='\0';
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
void creditos (){

     system ("cls");
     printf ("*--------------------------xxx CRÉDITOS xxx------------------------*\n");
     printf ("* Trabalho Desenvolvido Para o Segundo Semetre - 2021              *\n");
     printf ("* Curso      : Análise e Desenvolvimento de Sistemas               *\n");
     printf ("* Diciplina  : Algoritmo e Lógia de Programação II                 *\n");
     printf ("* Instituição: Unicesumar                                          *\n");
     printf ("* Acadêmicos : Ana Elisa Tubino        Função: Scrum Master  e Dev *\n");
     printf ("*              Guilherme Arraes                Product Owner e Dev *\n");
     printf ("*              Tiago Freire                    UI/UX Design  e Dev *\n");
     printf ("*--------------------------xxxxxxxxxxxxxxxx------------------------*\n");
}
//------------------------------------------------------------------------------
void notaDevs (){
     system ("cls");
     printf ("*-------------------------------------------------------------------------------------------------------------------*\n");                                                                 
     printf ("                                                     Lições Aprendida\n");
     printf ("*-------------------------------------------------------------------------------------------------------------------*\n");
     printf (" DESENVOLVEDOR(A)  |       FUNÇÃO       |        O QUE APRENDEU?         |                MAIOR DIFICULDADE?\n"); 
     printf ("---------------------------------------------------------------------------------------------------------------------\n"); 
     printf ("                   |                    |  Aplicar ordenação em C        |   Problemas em seguir um padrão do código\n");
     printf (" Ana Elisa Tubino  |    Srum Master     |  Structs                       |   Dificuldade na manipulação de String\n");
     printf ("                   |                    |  Trabalhar melhor em equipe    |\n");
     printf ("---------------------------------------------------------------------------------------------------------------------\n"); 
     printf ("                   |                    |                                |   Delegar tarefas e cobralas\n");
     printf (" Guilherme Arraes  |    Product Owner   |  Manipular melhor Strings      |   Dificuldade na manipulação de String\n");
     printf ("                   |                    |  Trabalhar melhor em equipe    |   Problemas em seguir um padrão do código\n");
     printf ("                   |                    |                                |   Documentar as tarefas (não realizado)\n");
     printf ("---------------------------------------------------------------------------------------------------------------------\n");
     printf ("                   |                    |  Structs                       |   Problemas em seguir um padrão do código\n");
     printf (" Tiago Freire      |    UI/UX Design    |  Trabalhar melhor em equipe    |   Dificuldade na manipulação de String\n");
     printf ("                   |                    |                                |\n");
     printf ("---------------------------------------------------------------------------------------------------------------------\n");
     
     printf ("\n\n*------------------------------------------------------------------------*\n");
     printf ("                         DESENVOLVIMENTO DO PROJETO\n");
     printf ("*------------------------------------------------------------------------*\n");
     printf (" Reuniões todas as Quintas -> Desenvolvimento conjunto\n");
     printf ("                           -> Estabelecer entregas para próxima semana\n");
     printf (" Reunião Sabado ou Domingo -> Desenvolvimento conjunto para tirar dúvidas\n");
     printf ("--------------------------------------------------------------------------\n");
     printf ("<ENTER> voltar MENU PRINCIPAL");
     do{
        enter = getch();
     }while (enter != 13); 
}
