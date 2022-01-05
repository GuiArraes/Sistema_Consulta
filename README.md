# Sistema_Consulta

Algoritmo desenvolvido no 2° Período de Análise e Desenvolvimento de Sistemas

### Proposta

Desenvolver um algoritmo em Linguagem C aplicando os conceitos demonstrados em sala de aula.
- Ler arquivos .txt;
- Tratar dados recebidos dos arquivos .txt;
- Ordenação (aplicamos Selection Sort);
- Buscas (aplicamos a Busca Binária);
- Validações;
- Elaboração de Menus.

### Desenvolvedores 😎
<a href="https://br.linkedin.com/in/ana-elisa-tubino?trk=people_directory">Ana Elisa Tubino</a>

<a href="https://br.linkedin.com/in/guilherme-arraes-674181107">Guilherme Arraes</a>

<a href="https://br.linkedin.com/in/tiago-freire-santos">Tiago Freire</a>

### REQUISITOS DO SISTEMA

Necessitamos construir um algoritmo/programa, de forma modular (procedimentos/funções), que resolva o problema a seguir:

A empresa BITZERO necessita manipular algumas informações de clientes e contas a receber. Através de um sistema de terceiro, dois arquivos do tipo texto (.TXT) foram gerados
O programa a ser desenvolvido, deverá efetuar a importação dos arquivos e tratar os dados para que posteriormente possibilite consultas e alterações das informações.

Os campos dos arquivos estão delimitados por aspas e separados por vírgula, por isso, deverá haver uma atenção especial no momento de manipular as strings.

As informações importantes para os Clientes são CODIGO, NOME, CIDADE, ESTADO e CPF/CNPJ.

As informações importantes para as Parcelas são NUMERO, CODIGO DO CLIENTE, DATA VENCIMENTO, DATA DE RECEBIMENTO (somente alguns registros possuem esta informação), VALOR e CODIGO DO BANCO.

Os códigos de bancos são:

0 – CARTEIRA (sem cobrança bancária)

001 – Banco do Brasil

104 – CEF - Caixa Econômica Federal

237 – Bradesco

260 - Nubank

341 - Itaú

O Sistema deverá conter MENU e SUBMENUS (a critério dos programadores de acordo com os requisitos observados)

#### O SISTEMA DEVERÁ CONTEMPLAR:
- importação de Clientes e Parcelas (não permitir importar mais de uma vez);
- possibilidade de Classificar Clientes por NOME ou CODIGO;
- inclusão de clientes (validar CODIGO pois não poderá haver duplicidade);
- alteração de clientes (exceto do campo CODIGO que será chave);
- exclusão de clientes (somente se não houver parcelas vinculadas a eles);
- Possibilidade de Classificar Parcelas por NUMERO ou VENCIMENTO;
- inclusão de parcelas (atenção ao validar o campo NUMERO pois não poderá haver duplicidade). Atenção também ao CODIGO do CLIENTE pois o mesmo deverá existir;
- alteração de parcelas (se alterado o campo CODIGO do CLIENTE, este deverá ser validado pois necessita haver um código válido – cliente existente);
- exclusão de parcelas.

#### O SISTEMA DEVERÁ PROPORCIONAR CONSULTAS COMO:
- Clientes Geral, por cidade ou estado;
- Receitas em aberto (não recebidas) de um cliente específico ou todos (com dias em atraso);
- Receitas em aberto (não recebidas) de um banco específico ou todos (com dias em atraso);
- Receitas recebidas de um cliente específico ou todos;
- Receitas recebidas de um banco específico ou todos;
- Receitas por cliente específico (independente de recebido ou não);
- Receitas por banco específico (independente de recebido ou não);
- Resumo sintético de receitas em aberto por banco (banco a banco com o total);
- Resumo sintético de Receitas recebidas por banco (banco a banco com o total);
- Total em aberto (geral);
- Total recebido (geral);
- Total Geral (em aberto e recebidas).

Outras consultas e funcionalidades que considerarem importantes poderão ser implementadas, e é aí que entra a contribuição intelectual e técnica de cada um.

#### OBSERVAÇÕES:
- A exclusão de um registro poderá ser LÓGICA ou FÍSICA;
- Há nos arquivos, 147 clientes e 76 parcelas (os arquivos não poderão ser modificados e serão entregues a vocês);
- Deverá haver uma opção para mostrar os créditos do programa (quem são os desenvolvedores);
- Os campos deverão ser validados (quando possível);
- Deverá haver mensagens de erro ao usuário;
- As listagens/consultas deverão possuir paradas para avanço da próxima página.
