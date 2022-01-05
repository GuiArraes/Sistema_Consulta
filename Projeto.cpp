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
       char id[5], nome[30], cidade[20], UF[3], ident[25];  
       bool status;
};
struct Parcela{
       char idPar[10], idCli[5], venc[9], rec[9], val[9];
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

struct Cliente cadastro[SIZE_CAD];
struct Parcela registro[SIZE_CAD];
//*****************************XXXXXXXXXXXXXXXXX******************************//

//******************INICIALIZAÇÃO DOS PROCEDIMENTOE FUNÇÕES*******************//
/*Feito*/void menuCliente ();
void mostrarCadastro (char descricao[50]); //FALRA LISTAR TODOS, SEM SELECIONAR CIDADE.
void menuParcela ();
void mostrarParcela (char opMenu[15]);

void menuPrincipal ();
/*Feito*/void leArquivo(char nomeArq[15]);
/*Feito*/void dadosImp (int tipo, bool flag);
/*Feito*/void apresenta(char menu[50]);
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
/*Feito*//*Feito*//*Feito*//*Feito*//*Feito*/void deletarCliente ();
/*Feito*/int buscaBinaria (char pesquisa[5], int tipo);
int buscaBinariaIdCli (char pesquisa[5], int tipo);
/*Feito*/void valCliPar ();
/*Feito*/void addParcela ();
/*Feito*/void mudarParc ();
void menuMudarPar (int q, int c);
/*Feito*/int subMenuMudarPac (int p, int cliente);
/*Feito*/bool validaDate (char data[7]);

//void totalGeral ();
//void menuResumidoPag (float a, float r, float t);
void contaBanco ();
void receitaBancoCliente (int tipo);
void menuReceita ();

void menuBusca ();

void personalizado ();
bool parcelaBanco (char cli[5], int bc);
void clienteEUmbanco (char cli[5], int bc, int orde, int parc, bool flag);

int validaBanco (int bc);
/*Feito*/void creditos ();
//******************XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*******************//

//-----------------------------PROGRAMA PRINCIPAL-----------------------------//
int main (){
    setlocale(LC_ALL,"portuguese");
    
    flagCli = false; 
    flagParc = false;
    
    //menuPrincipal ();
    leArquivo ("CLIENTES.txt");
    salvaCliente ();
    leArquivo ("PARCELAS.txt");
    salvaParcela ();
    
    
    //selectionVencPar ();
    
    menuPrincipal ();
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
        printf ("Escolha uma opção: ");
        op = getch ();
        if (op-48==27) printf ("ESC");
        if (op-48>=0 && op-48<5) printf ("%d",op-48);
        
        
        Sleep (500);
        //scanf ("%d", &op);
    //}while (op[0] < '0' || op[0] > '5' && op[0]);
    }while (op != 49 && op != 50 && op != 51 && op != 52 && op != 48 && op != 27);
    //}while (op[0] !='1' && op[0] !='2' && op[0] !='3' && op[0] !='4' && op[0] !='0' && op[0] !='\0');

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
                getch ();
                menuPrincipal ();
                break;
           case 27:
                break;
    }
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
void menuCliente (){
     int op;
     
     do {
         fflush (stdin);
         system ("cls");
         printf ("MENU CLIENTE\n\n");
         printf ("1 - Importar\n");
         printf ("2 - Mostrar Cadastros\n");
         printf ("3 - Adicionar\n");
         printf ("4 - Alterar\n");
         printf ("5 - Excluir\n");
         printf ("0 - Menu Principal\n");
         printf ("Escolha um opção: ");
         scanf ("%d",&op);
     }while (op < 0 || op >5);
     
     switch (op){
            case 1:
                 if (flagCli){
                    system ("cls");
                    printf ("Dados dos Clientes já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    getch();
                    menuCliente (); 
                 }
                 leArquivo ("CLIENTES.txt");
                 salvaCliente ();
                 apresenta ("Obrigado por esperar! <ENTER> voltar ao MENU CLIENTE");
                 menuCliente ();
                 break;
            case 2:
                 dadosImp (1, flagCli);
                 mostrarCadastro ("<ENTER> para voltar ao MEU CLIENTE"); 
                 menuCliente ();
                 break;
            case 3:
                 dadosImp (1, flagCli);
                 cadastrarCliente ();
                 break;
            case 4:
                 dadosImp (1, flagCli);
                 mudarCliente ();
                 break;
            case 5:
                 dadosImp (1, flagCli);
                 deletarCliente ();
                 break;
                 case 0:
                 menuPrincipal ();
                 break;
                 
     }    
}
//------------------------------------------------------------------------------
void mostrarCadastro (char descricao[50]){
     char cidade[10], uf[3];
     int ord;
     int temp[qtLinhasCli];
     int linha = 0;
     
     system ("cls");
     printf ("%d",qtLinhasCli);
     printf ("Lista de Clientes Cadastrados\n\n");
     
     fflush (stdin);
     printf ("Cidade desejada (Enter para TODAS): ");
     gets (cidade);
     maiusc (cidade); //PARA GRAVAR E PESQUISAR TUDO EM MAIUSCULO
     strcpy (cidade, tmp2);
     
     fflush (stdin);
     printf ("UF desejada (Enter para TODOS): ");
     gets (uf);
     maiusc (uf); //PARA GRAVAR TUDO EM MAIUSCULO
     strcpy (uf, tmp2);
     
     do{
        fflush (stdin);
        printf ("Ordenação (1 - Nome | 2 - ID):");
        scanf ("%d",&ord);
     }while (ord != 1 && ord != 2);
     
     if (ord == 1){
        selectionNome ();
     }else{
        selectionIdCliente ();
     }
     
     
     
     
     //AQUI É O FILTRO PARA A SELEÇÃO DE CIDADE E UF
     system ("cls");
     printf (" ID          Cliente                  Cidade           UF        RG/CPF/CNPJ\n");
     printf ("---------------------------------------------------------------------------------\n");
     for (int x=0; x<=qtLinhasCli;x++){
         if ((strcmp(cidade, cadastro[x].cidade)==0  )  &&  (strcmp(uf, cadastro[x].UF)==0  )){ ////////////////TENTEI USAR O 13 DA TABELA ASCII COMO PADRAO PARA O ENTER
           if (cadastro[x].status == true){
              printf("%4s | %20s | %22s | %2s | %19s |\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident);
              Sleep (20);
              linha++;
              if (linha == 26) {
                 printf ("---------------------------------------------------------------------------------\n");
                 printf ("<Enter> para mostrar mais");
                 getch();
                 system ("cls");
                 printf (" ID          Cliente                  Cidade           UF        RG/CPF/CNPJ\n");
                 printf ("---------------------------------------------------------------------------------\n");
              } 
           }
           
           if (linha > 26){
              if ((strcmp(cidade, cadastro[x].cidade)==0  )  &&  (strcmp(uf, cadastro[x].UF)==0  )){ ////////////////TENTEI USAR O 13 DA TABELA ASCII COMO PADRAO PARA O ENTER
                 if (cadastro[x].status == true){
                    printf("%4s | %20s | %22s | %2s | %19s |\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident);
                    Sleep (20);
                    linha++;
                 } 
              }
           }
         }
     }
     printf ("---------------------------------------------------------------------------------\n");
     printf (descricao);
     getch();     
}
//------------------------------------------------------------------------------
void menuParcela (){
     int op;
     char menu[15] = "Menu Parcela";
     
     do {
     system ("cls");
         printf ("MENU PARCELAS\n\n");
         printf ("1 - Importar\n");
         printf ("2 - Mostrar Parcelas\n");
         printf ("3 - Adicionar Parcela\n");
         printf ("4 - Alterar Parcela\n");
         printf ("5 - Excluir Parcela\n");
         printf ("0 - Menu Principal\n");
         printf ("Escolha um opção: ");
         scanf ("%d",&op);
     }while (op < 0 || op >5);
switch (op){
            case 1:
                 if (flagParc){
                    system ("cls");
                    printf ("Dados das Parcelas já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    getch();
                    menuParcela (); 
                 }
                 leArquivo ("PARCELAS.txt");
                 salvaParcela ();
                 apresenta2 ("Obrigado por esperar! <ENTER> voltar ao MENU PARCELA");
                 menuParcela ();
                 break;
            case 2:
                 dadosImp (2, flagParc);
                 mostrarParcela (menu); 
                 break;
            case 3:
                 dadosImp (2, flagParc);
                 addParcela ();
                 break;
            case 4:
                 dadosImp (2, flagParc);
                 mudarParc ();
                 break;
            case 5:
                 dadosImp (2, flagParc);
                 printf ("FALTA FAZER");
                 getch ();
                 menuParcela ();
                 break;
                 case 0:
                 menuPrincipal ();
                 break;   
     }  
}
//------------------------------------------------------------------------------
void mostrarParcela (char opMenu[15]){
    int ord;
    int temp[qtLinhasParc];
    float total;
    int ini = 0, fim = 0, linhasE = 24;
    
    do{
       system ("cls");
       printf ("LISTAR PARCELAS CADASTRADAS\n\n");
       fflush (stdin);
       printf ("1 - Por Número da Parcela\n");
       printf ("2 - Por Vencimento da Parcela\n");
       if (strcmp(opMenu, "menu parcela") == 0) printf ("0 - Menu Parcelas\n");
       if (strcmp(opMenu, "munu busca") == 0) printf ("0 - Menu Busca");
       printf ("Escolha uma opção: ");
       scanf ("%d",&ord);
    }while (ord != 1 && ord != 2 && ord != 0);
    
    if (ord == 0) menuParcela ();
    
    if (ord == 1){
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
        printf ("<ENTER> para voltar ao MENU PARCELAS");
        getch ();
        menuParcela ();
     }else{
        printf ("<Enter> para continuar");
        getch ();  
     }
     ini = ini + linhasE;
     }
}
//------------------------------------------------------------------------------
void apresenta(char menu[50]){
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
     printf (" ID          Cliente                  Cidade           UF        RG/CPF/CNPJ\n");
     printf ("---------------------------------------------------------------------------------\n");
     for (int x=ini;x<=fim;x++){
         if (cadastro[x].status == true){
            printf("%4s | %20s | %22s | %2s | %19s | %d\n",cadastro[x].id, cadastro[x].nome, cadastro[x].cidade, cadastro[x].UF, cadastro[x].ident, cadastro[x].status);
            Sleep (20);
         }
     }
     printf ("---------------------------------------------------------------------------------\n");
     if (total / 24.0 <= 0){
        printf (menu);
        getch ();
     }else{
        printf ("AGUARDE, IMPORTANDO...");
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
        getch ();
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
     cadastro[0].status = false;
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
int menuMudarCli (int p) {
     int op = -1;
     do{
        fflush (stdin);
        system ("cls");
        printf ("Alterar dados do Cliente: %s\n", cadastro[p].nome);
        printf ("1 - Alterar Nome\n");
        printf ("2 - Alterar Cidade\n");
        printf ("3 - Alterar UF\n");
        printf ("4 - Alterar RG/CPF/CNPJ\n");
        printf ("5 - Menu Cliente\n");                                                //*********************
        printf ("Escolha uma opção: ");
        scanf ("%d", &op);
     }while (op <=0 || op >=6);
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
           if (j == 1){
            fflush(stdin);
            printf ("Novo Nome: ");
            gets (cadastro[k].nome);
            maiusc (cadastro[k].nome);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].nome, tmp2);
           }
           if (j == 2){
            fflush(stdin);
            printf ("Nova Cidade: ");
            gets (cadastro[k].cidade);
            maiusc (cadastro[k].cidade);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].cidade, tmp2);
           }
           if (j == 3){
            fflush(stdin);
            printf ("Novo UF: ");
            gets (cadastro[k].UF);
            maiusc (cadastro[k].UF);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].UF, tmp2);  
           }
           if (j == 4){
            fflush(stdin);
            printf ("RG/CPF/CNPJ: ");
            gets (cadastro[k].ident); 
            maiusc (cadastro[k].ident);      //PARA GRAVAR TUDO EM MAIUSCULO
            strcpy (cadastro[k].ident, tmp2);
           }
           if (j ==5){
              menuCliente ();
           }
        }while(j != 5);
             
     }
     else{
       printf ("Cliente não cadastrado!!!\n"); 
       printf ("<ENTER> para voltar (MENU CLIENTE)");  
       getch();
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
int validaID (char comp[5]){ //Busca exastiva (da para melhorar se sobrar tempo)
     
     for (int i = 0; i <= qtLinhasCli-1; i++){
         if (strcmp(comp, cadastro[i].id) == 0){
            /*if (cadastro[i].status == false){
               return -1;
            }*/
            return i;
         }
     }
     return -1;
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
     getch();
     menuCliente ();
}
//------------------------------------------------------------------------------
void maiusc (char palavra[30]){
     for (int i = 0; i <= strlen(palavra); i++){
         tmp2[i] = toupper (palavra[i]); //tmp variavel global
     }
     tmp2[strlen(palavra)] ='\0';
}
//------------------------------------------------------------------------------
void deletarCliente (){ ///************************************************************************************************
     char cod[5];
     int k = -100;
     
     system ("cls");
     qtLinhasCli++; //Sem isso, não pega o último código do cliente
     printf ("Deletar Cliente\n");
     do{
        fflush (stdin);
        printf ("Código do Cliente: ");
        gets (cod);
        k = validaID (cod);
     if (k == -1) printf ("Cliente não cadastrado.\n");
     }while (k == -1);
     
     cadastro[k].status = false;
     qtLinhasCli--; //Para voltar ao normal
     
     printf ("\nCliente %s deletado.\n\n",cadastro[k].nome);
     printf ("<ENTER> para voltar ao MENU CLIENTE");
     getch();
     menuCliente ();
     
     //printf ("%d",cadastro[k].status);
     //system ("pause");
}
//------------------------------------------------------------------------------
int buscaBinaria (char pesquisa[5], int tipo){ //BUSCA PARA ACHAR O número da parcela
    int ini, fim, meio, p = 0; 
    
    selectionNumeroPar ();        
    
    if (tipo == 1) qtLinhasParc--;
    
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
    if (tipo == 1) qtLinhasParc++;
    return -1; // retorna -1 número da parcela não encontrado
}
//------------------------------------------------------------------------------
/*int buscaBinariaIdCli (char pesquisa[5], int tipo){ //BUSCA PARA ACHAR O número da parcela
    int ini, fim, meio, p = 0;           
    
    selectionIdCliente ();
    
    if (tipo == 1) qtLinhasParc--;

    ini = 0;
    fim = qtLinhasParc;
    while (ini <= fim){
          meio = (ini+fim)/2;
          if (strcmp(cadastro[meio].id, pesquisa) == 0){
             p = meio;
             if (tipo == 1) qtLinhasParc++;
             return p;//retorna a posição da parcela
          }else{
              if (strcmp(pesquisa, cadastro[meio].id) < 0){ 
                 fim = meio - 1;           
              }
              else {
                   ini = meio + 1;
              }
          }                  
    }
    if (tipo == 1) qtLinhasParc++;
    return -1; // retorna -1 número da parcela não encontrado
}*/
//------------------------------------------------------------------------------
void valCliPar (){
    if (flagCli == false){
        printf ("ATENÇÃO: Dados dos Clientes devem serem IMPORTADOS\n");
        printf ("<ENTER> para voltar ao MENU PRINCIPAL");
        getch ();
        menuPrincipal ();
    }          
}
//------------------------------------------------------------------------------**********************************
void addParcela (){ //Para realizar a busca binaria, tem-se que descontar qtLinhasParc, se não, sempre irá achar a ultima linha que add.
     int k = -1, j;
     bool flag;
     
     valCliPar ();
  
     qtLinhasParc++;
     system ("cls");
     while (k == -1){ //Validando ID CLIENTE
           printf ("Adicionar Parcelas\n\n");
           fflush (stdin);
           printf ("Código do cliente: ");
           gets (registro[qtLinhasParc].idCli);
           //selectionNumeroPar ();

           k = validaID(registro[qtLinhasParc].idCli);
           
           if (k == -1){
              printf ("Código não cadastrado.\n");
              printf ("<ENTER> para tentar novamente\n");
              getch ();
              system ("cls");
           }
     }
     system ("cls");
     printf ("Adicionar Parcelas\n\n");
     printf ("Cliente: %s\n", cadastro[k].nome);
     printf ("Código: %s\n\n", cadastro[k].id);
     j = 0;
     selectionNumeroPar ();
     while (j != -1){ //Validando CÓDIGO PARCELA
           fflush (stdin);
           printf ("Informe código da parcela(Ex: 1234/1): ");
           gets (registro[qtLinhasParc].idPar);
            
           j = buscaBinaria (registro[qtLinhasParc].idPar, 1); //Passando como parametro o '1' para descontar a qtLinhasParc, se não da ruim.
           
           if (j != -1) printf ("Número de parcela já cadastrado.\n");     
     }
     
     flag = false;
     while (not flag){
         fflush (stdin);
         printf ("Data do vencimento(Ex: 02/11/21): ");
         gets (registro[qtLinhasParc].venc);
         flag = validaDate (registro[qtLinhasParc].venc);
         if (not flag) printf ("Data Inválida.\n");
     }   
     
     do {
        fflush (stdin);
        printf ("Valor da Parcela (Ex: 150,00): ");
        gets (registro[qtLinhasParc].val);
        if (strtol(registro[qtLinhasParc].val, NULL, 10) <= 0) //Convertendo de CHAR para INT (Função 'strtol')
           printf ("Valor de parcela Inválido\n");
     } while (strtol(registro[qtLinhasParc].val, NULL, 10) <= 0);
     
     do{
        fflush (stdin);
        printf ("(0   - Carteira)\n(001 - Banco do Brasil)\n(104 - Caixa Econômica Federal)\n(237 - Bradesco)\n(260 - Nubank)\nCódigo Banco: ");                                                                                
        //gets (registro[qtLinhasParc].banco);
        scanf ("%d",&registro[qtLinhasParc].banco);
     }while (registro[qtLinhasParc].banco !=0 &&
      registro[qtLinhasParc].banco !=001 &&
      registro[qtLinhasParc].banco !=104 && 
      registro[qtLinhasParc].banco !=237 && 
      registro[qtLinhasParc].banco !=260);
      //ESSA MERDA FUNCIONA ASSIM SÓ SE A VARIAVEL FOR int (só Deus sabe o motivo)... 
      
      system ("cls");
      printf ("Adicionar Parcelas\n\n");
      printf ("Cliente        : %s\n", cadastro[k].nome);
      printf ("Código         : %s\n", cadastro[k].id);
      printf ("Código Parcela : %s\n", registro[qtLinhasParc].idPar);
      printf ("Valor          : %s\n\n", registro[qtLinhasParc].val);
      printf ("Salvo com sucesso.\n");
      printf ("<ENTER> voltar MENU PARCELA");
      getch ();
      menuParcela ();   
}
//------------------------------------------------------------------------------
void mudarParc (){ //Busca binaria pasa o tipo igual 0. Pois não add nenhuma linha aqui
     int k=-1, j=-1;
     char cod[5], parc[10];
     
     valCliPar ();
     
     system ("cls");
     printf ("Alterar PARCELAS\n\n");
     while (k == -1){
         fflush(stdin);
         printf ("Código do cliente: ");
         gets (cod);
         k = validaID(cod); //Busca o ID do arquivo cliente
         if (k == -1) printf ("Cliente não cadastrado.\n");
     }

     //j = -1;
     while (j ==-1){
         selectionNumeroPar ();
         fflush(stdin);
         printf ("Código da parcela: ");
         gets (parc);
         j = buscaBinaria(parc, 0); 
         if (k==-1) printf ("Código da parcela não encontrado\n");
     }
     //printf ("id    - %s\n",cadastro[k].id);
     //printf ("idCli - %s\n",registro[j].idCli);
     //system ("pause");
          
     if (strcmp(cadastro[k].id, registro[j].idCli)==0){
        menuMudarPar (j, k); //Passa a posição da parcela no vetor por parametro para 'int q'

     }else{
        system ("cls");
        printf ("Código informado não é compativel com a parcela desejada\n");
        printf ("Por favor, tente novamente <ENTER>.");
        getch ();
        mudarParc();
     }
     
     printf ("Parcela %s\n", registro[j].idPar);
}
//------------------------------------------------------------------------------
int subMenuMudarPac (int p, int cliente){
    int op = -1;
    
    do{
        fflush (stdin);
        system ("cls");
        printf ("Cliente: %s\n", cadastro[cliente].nome);
        printf ("PARCELA: %s\n\n",registro[p].idPar);
        printf ("1 - Alterar Data Vencimento\n");
        printf ("2 - Alterar Data Recebimento\n");
        printf ("3 - Alterar Valor\n");
        printf ("4 - Menu Parcela\n");
        printf ("Escolha uma opção: ");
        scanf ("%d", &op);
    }while (op <=0 || op >=5);
    return op;
     
}
//------------------------------------------------------------------------------
void menuMudarPar (int q, int c){
     int k;
     bool flag;
     
     k = subMenuMudarPac (q, c);
     while (k > 0 && k < 5){ //Isto é k entre 1 e 4
         if (k == 1){
            flag = false;
            while (not flag){ //VALIDA A DATA QUE SERÁ ALTERADA
                  system ("cls");
                  printf ("Cliente: %s\n", cadastro[c].nome);
                  printf ("Alterar PARCELA: %s\n\n",registro[q].idPar);
                  
                  fflush (stdin);
                  printf ("Nova Data Vencimento(Ex: 02/11/21): ");
                  gets (registro[q].venc);
                  flag = validaDate (registro[q].venc);
                  if (not flag){ 
                     printf ("Data Inválida.\n");
                     printf ("Tentar novamente <ENTER>");
                     getch ();
                  }
            }while(not flag); 
            k = subMenuMudarPac (q, c); //Para voltar no subMenuMudarParc paficar em loop ate k= 4.
         }     
         if (k == 2){
            flag = false;
            while (not flag){ //VALIDA A DATA QUE SERÁ 
                  system ("cls");
                  printf ("Cliente: %s\n", cadastro[c].nome);
                  printf ("Alterar PARCELA: %s\n\n",registro[q].idPar);
                  
                  fflush (stdin);
                  printf ("Nova Data Recebimento(Ex: 02/11/21): ");
                  gets (registro[q].rec);
                  flag = validaDate (registro[q].rec);
                  if (not flag){ 
                     printf ("Data Inválida.\n");
                     printf ("Tentar novamente <ENTER>");
                     getch ();
                  }
            }while(not flag);
            k = subMenuMudarPac (q, c); //Para voltar no subMenuMudarParc paficar em loop ate k= 4. 
         }
         if (k == 3){
            do {
               system ("cls");
               printf ("Cliente: %s\n", cadastro[c].nome);
               printf ("Alterar PARCELA: %s\n\n",registro[q].idPar);
                
               fflush(stdin);
               printf ("Valor da Parcela (Ex: 150,00): ");
               gets (registro[q].val);
               if (strtol(registro[q].val, NULL, 10) <= 0) //Convertendo de CHAR para INT (Função 'strtol')
                  printf ("Valor de parcela Inválido\n");
            }while (strtol(registro[q].val, NULL, 10) <= 0);
            k = subMenuMudarPac (q, c); //Para voltar no subMenuMudarParc paficar em loop ate k= 4.
         }
         if (k == 4){
            menuParcela ();
         }
     }
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
void contaBanco (){
     float totalCarteiraA = 0, totalCarteiraR = 0, totalCarteiraG = 0;
     float totalBbA = 0, totalBbR = 0, totalBbG = 0;
     float totalCxA = 0, totalCxR = 0, totalCxG = 0;
     float totalBdA = 0, totalBdR = 0, totalBdG = 0;
     float totalNuA = 0, totalNuR = 0, totalNuG = 0;
     float totalItA = 0, totalItR = 0, totalItG = 0;
     float totalAberto, totalRecebido, totalBanco;
     
     for (int i = 0; i <= qtLinhasParc; i++){
         //CARTEIRA (0)
         if ((strcmp (registro[i].rec, "N/D") == 0) && (registro[i].banco == 0)) //Pega todos os valores da CCARTEIRA em ABERTO
            totalCarteiraA = totalCarteiraA + registro[i].valor;      //Para TOTAL ABERTO CARTEIRA
         if (registro[i].banco == 0) //Pega todos os valores da CCARTEIRA
            totalCarteiraG = totalCarteiraG + registro[i].valor;//Pega todos os valores da CARTEIRA.
         
         //printf ("%.2f\n",registro[i].valor);
        //getch ();
            
         //BANCO DO BRASIL (001)   
         if ((strcmp (registro[i].rec, "N/D") == 0) && (registro[i].banco == 001)) //Pega todos os valores da CCARTEIRA em ABERTO
            totalBbA = totalBbA + registro[i].valor;      //Para TOTAL ABERTO BANCO DO BRASIL
         if (registro[i].banco == 001) //Pega todos os valores do BANCO DO BRASIL CCARTEIRA
            totalBbG = totalBbG + registro[i].valor;
            
         //CAIXA ECÔNOMICA FERERAL (104)   
         if ((strcmp (registro[i].rec, "N/D") == 0) && (registro[i].banco == 104)) //Pega todos os valores da CCARTEIRA em ABERTO
            totalCxA = totalCxA + registro[i].valor;      //Para TOTAL ABERTO CAIXA ECÔNOMICA FERERAL
         if (registro[i].banco == 104) //Pega todos os valores da CAIXA ECÔNOMICA FERERAL
            totalCxG = totalCxG + registro[i].valor;
            
         //BRADESCO (237)  
         if ((strcmp (registro[i].rec, "N/D") == 0) && (registro[i].banco == 237)) //Pega todos os valores da CCARTEIRA em ABERTO
            totalBdA = totalBdA + registro[i].valor;      //Para TOTAL ABERTO BRADESCO
         if (registro[i].banco == 237) //Pega todos os valores do BRADESCO
            totalBdG = totalBdG + registro[i].valor;
            
         //NUBANCK (260)  
         if ((strcmp (registro[i].rec, "N/D") == 0) && (registro[i].banco == 260)) //Pega todos os valores da CCARTEIRA em ABERTO
            totalNuA = totalNuA + registro[i].valor;      //Para TOTAL ABERTO NUBANCK
         if (registro[i].banco == 260) //Pega todos os valores do NUBANCK
            totalNuG = totalNuG + registro[i].valor;
            
         //ITAÚ (341)  
         if ((strcmp (registro[i].rec, "N/D") == 0) && (registro[i].banco == 341)) //Pega todos os valores da CCARTEIRA em ABERTO
            totalItA = totalItA + registro[i].valor;      //Para TOTAL ABERTO ITAÚ
         if (registro[i].banco == 341) //Pega todos os valores do ITAÚ
            totalItG = totalItG + registro[i].valor;
     }
     //Conta para achar o Total Recebido por Banco
     totalCarteiraR = totalCarteiraG - totalCarteiraA;
     totalBbR = totalBbG - totalBbA;
     totalCxR = totalCxG - totalCxA;
     totalBbR = totalBdG - totalBdA;
     totalNuR = totalNuG - totalNuA;
     totalItR = totalItG - totalItA;
     
     totalAberto   = totalCarteiraA + totalBbA + totalCxA + totalBdA + totalNuA + totalItA;
     totalRecebido = totalCarteiraR + totalBbR + totalCxR + totalBdR + totalNuR + totalItR;
     totalBanco    = totalAberto + totalRecebido;
     
     system ("cls"); 
     printf ("------------------------------------------------------------------\n");
     printf ("  COD      BANCO         A RECEBER      RECEBIDO       TOTAL\n");
     printf ("------------------------------------------------------------------\n");
     printf ("| 000 |   Carteira   |    %.2f   |   %.2f  |    %.2f  |\n", totalCarteiraA, totalCarteiraR, totalCarteiraG);
     printf ("| 001 |      BB      |    %.2f    |    %.2f    |    %.2f   |\n", totalBbA, totalBbR, totalBbG);
     printf ("| 104 |    CAIXA     |    %.2f    |    %.2f    |    %.2f   |\n", totalCxA, totalCxR, totalCxG);
     printf ("| 237 |   BRADESCO   |    %.2f    |    %.2f    |    %.2f   |\n", totalBdA, totalBdR, totalBdG);
     printf ("| 341 |     ITAÚ     |    %.2f    |    %.2f    |    %.2f   |\n", totalItA, totalItR, totalItG);
     printf ("| 260 |    NUBANK    |    %.2f    |    %.2f    |    %.2f   |\n", totalNuA, totalNuR, totalNuG);
     printf ("------------------------------------------------------------------\n");
     printf ("           TOTAL          %.2f       %.2f       %.2f \n", totalAberto, totalRecebido, totalBanco);
     printf ("<ENTER> para voltar MENU RECEITAS");
     getch();    
}
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
        getch ();
        system ("cls");
     }
     if (not flag && tipo == 2){
        if (k == -1){
           printf ("Cliente não cadastrado\n");
           printf ("<ENTER> para nova consulta\n");
           getch ();
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
void menuBusca (){
     int op;

     do {
         fflush (stdin);
         system ("cls");
         printf ("MENU BUSCA\n\n");
         printf ("1 - Importar Cliente\n");
         printf ("2 - Importar Parcelas\n");
         printf ("3 - Buscar Cliente\n");
         printf ("4 - Buscar Parcela\n");
         printf ("0 - Menu Principal\n");
         printf ("Escolha um opção: ");
         scanf ("%d",&op);
     }while (op < 0 || op >4);
     
     switch (op){
            case 1:
                 if (flagCli){
                    system ("cls");
                    printf ("Dados dos Clientes já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    getch();
                    menuBusca (); 
                 }else{
                  
                    leArquivo ("CLIENTES.txt");
                    salvaCliente ();
                    apresenta ("Obrigado por esperar! <ENTER> voltar ao MENU BUSCA");
                    menuBusca ();
                 }
                 break;
            case 2:
                 if (flagParc){
                    system ("cls");
                    printf ("Dados das Parcelas já importados!!!\n");
                    printf ("<ENTER> para voltar");
                    getch();
                    menuBusca();
                 }else{
                  
                    leArquivo ("PARCELAS.txt");
                    salvaParcela ();
                    apresenta2 ("Obrigado por esperar! <ENTER> voltar ao MENU BUSCAR");
                    menuBusca (); 
                 }
                 break;
            case 3:
                 dadosImp (3, flagCli);
                 mostrarCadastro ("<ENTER> para voltar ao MEU BUSCA");
                 menuBusca ();
                 break;
            case 4:
                 dadosImp (3, flagParc);
                 mostrarParcela ("menu parcela");
                 menuBusca ();
                 break;
            case 0:
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
         printf ("1 - Personalizado\n");
         printf ("2 - Resumo por Banco\n");
         printf ("0 - Menu Principal\n");
         printf ("Escolha um opção: ");
         scanf ("%d",&op);
     }while (op < 0 || op >2);

     switch (op){
            case 1:
                 dadosImp (4, flagCli);
                 dadosImp (4, flagParc);

                 break;
            case 2:
                 dadosImp (4, flagCli);
                 dadosImp (4, flagParc);
                 contaBanco ();
                 menuReceita ();
                 break;
            case 0:
                 menuPrincipal ();
                 break;
                 
     } 
}
//------------------------------------------------------------------------------
void personalizado (){
     
     printf ("TEM QUE ADAPTAR PARA A OPÇÃO DE PEGAR TODOS...\\n\n\n");
     
     char clienteID[5];
     int banco;
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
           getch ();
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
           getch ();
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
bool parcelaBanco (char cli[5], int bc){
    for (int i=0; i<=qtLinhasParc; i++){
        if (strcmp(cli, registro[i].idCli) == 0 && bc == registro[i].banco)
           return true;
    }
    return false;
//Isto é, se retornar TRUE significa que tem PELO MENOS 1 parcela no banco desejado
//Caso retorne FALSE significa que não esse cliente NÃO TEM PARCELA NESTE BANCO.
}
//------------------------------------------------------------------------------
void clienteEUmbanco (char cli[5], int bc, int orde, int parc, bool flag){ //Serve para imprimir dados de parcela de um cliente de um banco especifico.
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
             if (strcmp(cli, registro[i].idCli) == 0 && bc == registro[i].banco){
                //totalCli = totalCli + registro[i].valor; //Pega todos os valores independente do BANCO    
                printf("%9s | %4s | %9s | %9s | %9s | %.3d\n",registro[i].idPar, registro[i].idCli, registro[i].venc, registro[i].rec, registro[i].val, registro[i].banco);
                Sleep (100); 
             }
         }
         printf ("-----------------------------------------------------------\n");
         printf ("<ENTER> para Nova Consulta");
         getch (); 
     }
     else{
         printf ("-----------------------------------------------------------\n");
         printf ("  %s: não tem parcelas no Banco (%d)\n",cadastro[k].nome,bc);
         printf ("-----------------------------------------------------------\n");
         printf ("<ENTER> para Nova Consulta");
         getch ();
     } 
     printf ("\n%.2f",totalCli);  

}
//------------------------------------------------------------------------------
int validaBanco (int bc){
     int nome[6];

     nome[0] = 000;
     nome[1] = 001;
     nome[2] = 104;
     nome[3] = 237;
     nome[4] = 341;
     nome[5] = 260;
     for (int i=0; i<=5;i++){
         if (bc == nome[i])
            return 1;
     }
     return -1;
}
//PROVA REAL cod:3110  ---  Banco: 104
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
