#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#define SIZE 200
int n[SIZE];//quantidade de pedidos do cliente

char nome[SIZE][50];        //variaveis dos clientes
int dia[SIZE], mes[SIZE], ano[SIZE], idc[SIZE], ViagensCliente[SIZE], idHistorico[SIZE][SIZE];

char alimento[SIZE][50], marca[SIZE][50];       //variavies dos alimentos
int ida[SIZE];
double  preco[SIZE], calorias[SIZE];

void iniciacaoDeVetor(){
    int i;
    for(i = 0; i<SIZE; i++){
        idc[i] = -1;
        ida[i] = -1;
    }
}

int registerID(){     //Gera IDs Aleatoriamente/Le um ID pelo teclado.
    int i;
    int op;
    long long int id;
    printf("deseja cadastrar o ID manualmente ou aleatoriamente?\n");
    printf("1 - manualmente\n");
    printf("2 - aleatoriamente\n");
    scanf("%d", &op);
    
    if((op!=1)&&(op!=2)){       // caso as opcoes sejam diferentes de 1 e 2 o procedimento se repete
        printf("Opcao invalida\n");
        registerID();
    }
    else if(op == 1){
        id = 0;
        printf("O id deve conter apenas numeros entre 1 e 10000, Insira o ID:\n");
        scanf("%d", &id);
        if ((id<0)||(id>10000)){
            printf("ID invalido\n");
            registerID();
        }
        for(i=0; i<SIZE; i++){      //percorre a matriz SIZE linha por linha para verificar se o ID existe.
            if((idc[i]==id)||(ida[i]==id)){
                printf("Ja utilizado\n");
                registerID();
            }  
        }  
            return id;
    }
    else if(op == 2){
        id = 1;
        srand(time(NULL));
        id = rand() % 10000;      //gera numeros aleatorios entre 1 e 10000
        for(i=0; i<SIZE; i++){      //percorre a matriz SIZE linha por linha para verificar se o ID existe.
            if((idc[i]==id)||(ida[i]==id)){
                id = rand() % 10000;
            }  
        }  
        printf("ID cadastrado = %d\n", id);
            return id;
    }
}

void cadastroCliente(){     //cadastra informacoes sobre os clientes.
    static int linha;   //static faz com que o a variavel sempre inicie com o mesmo valor, independente se ela for allterada no meio do proceso.
    int  op;

    FILE *f;
    f = fopen("register.txt", "a");

    do{
    
        system("cls");
        printf("Digite o nome do cliente:\n");
        fflush(stdin);
        scanf("%[^\n]s", &nome[linha]);
        printf("\n");

        fprintf(f,"nome cadastrado = %s\n", nome[linha]);
        

        printf("Digite a data de nascimento: dia mes ano \n");
        scanf("%02d %02d %04d", &dia[linha],&mes[linha],&ano[linha]);

        fprintf(f,"data de nascimento cadastrada = %d / %d / %d\n", dia[linha],mes[linha],ano[linha]);

        printf("\n");

        idc[linha] = registerID();

        fprintf(f,"ID cadastrado =  %d\n", idc[linha]);

        printf("\n");

        printf("insira a quantidade de viagens do cliente, caso nao deseje informar digite 0:\n");
        scanf("%d", &ViagensCliente[linha]);

        fprintf(f,"quantidade de viagens cadastrada =  %d\n\n", ViagensCliente[linha]);

        printf("\n");
        
        printf("Digite 1 para continuar ou 0 para sair\n");
        scanf("%d", &op);

        linha++;
        system("cls");
    }
    while(op==1);
    fclose(f);
}

void ConsultaCliente(){     //consulta as informaçoes do cliente.
    int pesquisaid,i,op;

    FILE *f;
    f = fopen("register.txt", "a");

    do{
        system("cls");
        printf("Digite o id do cliente:\n");
        scanf("%d", &pesquisaid);
        for(i=0; i<SIZE; i++){      //percorre a matriz SIZE linha por linha para encontrar o id assiciado aos dados do cliente.
            if((idc[i]==pesquisaid)){
                printf("nome do cliente = %s\ndata de nascimento = %02d:%02d:%04d\n", nome[i], dia[i],mes[i],ano[i]);
                printf("Viagens realizadas = %d\n", ViagensCliente[i]);
                fprintf(f,"ID consultado = %d\n\n", idc[i]);
                break;
            }  
        }  
        if(idc[i]!= pesquisaid){
            printf("ID nao cadastrado.\n");
            fprintf(f,"ID consultado nao existente = %d\n\n", pesquisaid);
        }
         
        printf("Digite 1 para continuar pesquisando ou 0 para sair\n");
        scanf("%d", &op);
        system("cls");
    }while(op==1);
    fclose(f);
}

void RemoveCliente(){   //remove o cliente cadastrado.

    int idremove,op,i;
    FILE *f;
    f = fopen("register.txt", "a");
    
    do{ 
        system("cls");
        printf("Digite o id de cadastro para ser removido:\n");
        scanf("%d", &idremove);
        for(i=0; i<SIZE;i++){ 
            if(idc[i]==idremove){
                fprintf(f,"Cadastro removido, ID = %d\n\n", idc[i]);
                for(;i<SIZE-1;i++){
                    idc[i] = idc[i+1];
                }
                printf("Cadastro removido!\n\n");
                break;
            }
        }
        if(i == SIZE){
            printf("ID nao cadastrado\n");
        }
        
        printf("Digite 1 para continuar removendo ou 0 sair\n");
        scanf("%d", &op);
        system("cls");
    }while(op==1);
    fclose(f);
}

void alteraCliente(){   //altera as informaçoes do cliente.
    int pesquisaid, i, op, j;

    FILE *f;
    f = fopen("register.txt", "a");

    do{
        system("cls");
        printf("Digite o id do cliente:\n");
        scanf("%d", &pesquisaid);
        for(i=0; i<SIZE; i++){     //percorre os vetores para encontrar o id assiciado aos dados do cliente.
            if((idc[i]==pesquisaid)){
                for(j=0;j<=50;j++){     // percorre pelas colunas da matriz nome para zerar os nomes.
                    nome[i][j]='\0';
                }
                printf("Digite o novo nome do cadastro:\n");
                scanf("%*c");
                scanf("%[^\n]", &nome[i]);
                fprintf(f,"O cliente com ID = %d mudou o nome para : %s\n", pesquisaid, nome[i]);
                printf("Digite a nova data de nascimento:\n");
                scanf("%02d %02d %04d", &dia[i], &mes[i], &ano[i]);
                fprintf(f,"A nova data de nascimento do cliente com id = %d eh: %d %d %d\n", pesquisaid, dia[i], mes[i], ano[i]);
                printf("\n");
                printf("Digite a nova quantidade de viagens do cliente\n");
                scanf("%d", &ViagensCliente[i]);
                fprintf(f,"A nova quantidade de viagens do cliente com id = %d eh: %d\n\n", pesquisaid, ViagensCliente[i]);
                break;
            }
        }

        if(i == SIZE){
            printf("ID nao cadastrado\n");
            fprintf(f,"ID para alteracao nao encontrado");
        }         
        
        printf("Digite 1 para continuar alterando ou 0 para sair\n");
        scanf("%d", &op);
        system("cls");
    }while(op==1);
    fclose(f);
}

void inserirHistorico(){ //usada para inserir os alimentos no historico de pedido
int quantidade;
int pesquisaid;
int i, j, k;

FILE *f;
    f = fopen("register.txt", "a");

printf("Digite o id do cliente:\n");
scanf("%d", &pesquisaid);
printf("\n");

    for(i = 0;i<SIZE;i++){
        if((idc[i]==pesquisaid)){  //procura o id que foi solicitado
            printf("Quantos alimentos deseja inserir?\n");
            scanf("%d", &quantidade);
            printf("\n");
            n[i] = quantidade;
            if(n[i]!=0){
                printf("Entre com os ID's dos alimentos pedidos pelo cliente:\n");
                for(j = 0; j<n[i]; j++){   //usado para inserir os alimentos de acordo com a quantidade de entradas usadas
                    scanf("%d", &idHistorico[i][j]);
                    fprintf(f," cliente com id = %d\n inseriu o alimento: %d no historico\n",pesquisaid,idHistorico[i][j]);
                }
            }else{
                printf("quantidade = 0, nao e possivel adcionar alimentos\n");
            }
            break;
        }
    }
    if(i == SIZE){
        printf("ID nao encontrado\n");
    }
    fclose(f);
}

void PesquisaHistorico(){
    int i, j, k;
    int pesquisaid;
    int op;

    printf(" (1) -- consultar historico completo\n");
    printf(" (2) -- consultar historico atual\n");

    printf("escolha a opcao desejada: \n");
    scanf("%d", &op);
    printf("\n");
    system("cls");

    printf("Digite o id do cliente:\n");
    scanf("%d", &pesquisaid);
    printf("\n");
    if(op == 1){
        for(i = 0; i<SIZE;i++){
            if((idc[i]==pesquisaid)){
                if(n[i]!=0){
                    for(j = 0; j<n[i]; j++){
                        printf("\n");
                        printf("ID do alimento :%d\n", idHistorico[i][j]);
                    }
                }else{
                    printf("A quantidade de alimentos no historico e 0, nao e possivel mostrar historico\n");
                }
                break;
            }

        }
    if(i == SIZE){
    printf("ID nao cadastrado\n");
    } 
   }

    if(op == 2){      
        for(i = 0; i<SIZE;i++){
            if((idc[i]==pesquisaid)){ //busca se o id do cliente cadastrado existe
                if(n[i]!=0){
                    for(j = 0; j<n[i]; j++){
                        for(k = 0; k<SIZE; k++){      //percorre a matriz SIZE linha por linha para encontrar o id assiciado aos dados do Alimento.
                            if((ida[k]==idHistorico[i][j])){
                                printf("ID do alimento no sistema:%d\n", idHistorico[i][j]);
                                
                            }  
                        }  
                    }
                }else{
                    printf("A quantidade de alimentos no historico e 0, nao e possivel mostrar historico\n");
                }
             break;
            }
        }
    if(i == SIZE){
        printf("ID nao cadastrado\n");
    }   
  }
}
    


void historicopedidos(){
    int menu, pesquisaid;
    int i;
    while(menu!=3){
        
    printf("Deseja consultar o historico ou inserir um novo alimento?\n");
    printf("\n");
    printf(" (1) -- Inserir/Alterar alimento no historico de pedidos\n");
    printf(" (2) -- consultar historico de pedidos\n");
    printf(" (3) -- Digite outro valor para sair\n");
    printf("\n");

    printf("escolha a opcao desejada: \n");
    scanf("%d", &menu);
    printf("\n");
    system("cls");

    switch (menu){
        case 1:
            inserirHistorico();
        break;

        case 2:
            PesquisaHistorico();
        break;
        }
    }
}

int cliente(){  // menu de opcoes para o cliente.

int menu;

    while(menu!=6){
        printf(" (1) -- Inserir cadastro do Cliente\n");
        printf(" (2) -- consultar cadastro do Cliente\n");
        printf(" (3) -- remover cadastro do Cliente\n");
        printf(" (4) -- alterar cadastro do Cliente\n");
        printf(" (5) -- Historico de pedidos\n");
        printf(" (6) -- Voltar ao menu principal\n");
        printf("\n");

        printf("escolha a opcao desejada: \n");
        scanf("%d", &menu);
        system("cls");
    switch(menu){

   case 1:
   cadastroCliente();

   break;

   case 2:
   ConsultaCliente();

   break;

   case 3:
   RemoveCliente();

   break;

   case 4:
   alteraCliente();

   break;

   case 5:
   historicopedidos();

   break;
    }
  }
}

void cadastrAlimento(){  //cadastra as informacoes sobre os alimentos.

FILE *f;
    f = fopen("register.txt", "a");

    static int linha2;   
    int  op;
    int opindustria;
    do{
        system("cls");

        printf("Digite o nome do Alimento:\n");
        fflush(stdin);
        scanf("%[^\n]s", &alimento[linha2]);
            printf("\n");

        fprintf(f,"Alimento cadastrado: %s\n", alimento[linha2]);

        printf("Digite o valor calorico do alimento: \n");
        scanf("%lf", &calorias[linha2]);
        fprintf(f,"Valor calorico cadastrado do alimento: %.2lf kcal\n", calorias[linha2]);
            printf("\n");

        printf("Digite o preco do alimento: \n");
        scanf("%lf", &preco[linha2]);
        fprintf(f,"Preço do alimento cadastrado: R$%.2lf\n", preco[linha2]);
            printf("\n");

        ida[linha2] = registerID();
        fprintf(f,"ID de alimento cadastrado =  %d\n", ida[linha2]);
            printf("\n");

        printf("O alimento e industrializado?(1 = sim , outro valor = nao)\n");
        scanf("%d", &opindustria);

        if(opindustria == 1){
             printf("Insira o nome da marca:\n");
             fflush(stdin);
             scanf("%[^\n]s", &marca[linha2]);
             fprintf(f,"marca de alimento cadastrada: %s\n", marca[linha2]);
             printf("\n");
        }
        else{
            marca[linha2][0] = '\0';
            printf("\n");
        }
        fprintf(f,"\n");

        printf("Digite 1 para continuar ou 0 para sair\n");
        scanf("%d", &op);

        linha2++;
        system("cls");
    }
    while(op==1);
    fclose(f);
}

void ConsultaAlimento(){     //consulta as informaçoes do alimento.
    int pesquisaid,i,op;

    FILE *f;
    f = fopen("register.txt", "a");
    do{
        system("cls");
        printf("Digite o id do Alimento:\n");
        scanf("%d", &pesquisaid);
        for(i=0; i<SIZE; i++){      //percorre a matriz SIZE linha por linha para encontrar o id assiciado aos dados do Alimento.
            if((ida[i]==pesquisaid)){
                printf("nome do alimento = %s\nValor calorico = %.2lf Kcal\n",alimento[i], calorias[i]);
                fprintf(f,"ID de alimento consultado = %d\n", pesquisaid);
                fprintf(f,"\n");
                printf("Marca = %s\n",marca[i]);
                printf("Preco do alimento = R$%.2lf \n", preco[i]);
                break;
            }  
        }  
        if(ida[i]!= pesquisaid){
            printf("ID nao cadastrado.\n");
        }
        
        printf("Digite 1 para continuar pesquisando ou 0 para sair\n");
        scanf("%d", &op);
        system("cls");
    }while(op==1);
    fclose(f);
}

void removeAlimento(){      //remove o alimento cadastrado
    int idremove,op,i;
    FILE *f;
    f = fopen("register.txt", "a");
    do{ 
        system("cls");
        printf("Digite o ID do alimento para ser removido:\n");
        scanf("%d", &idremove);
        for(i=0; i<SIZE;i++){ 
            if(ida[i]==idremove){
                fprintf(f,"Cadastro de alimento removido, ID = %d\n\n", ida[i]);
                fprintf(f,"\n");
                for(;i<SIZE-1;i++){
                    ida[i] = ida[i+1];
                }
                printf("Cadastro removido!\n");
                break;
            }
        }

        if(i == SIZE){
            printf("ID nao cadastrado\n");
        }
        
        
        printf("Digite 1 para continuar removendo ou 0 para sair\n");
        scanf("%d", &op);
        system("cls");
    }while(op==1);
    fclose(f);
}

void alterarAlimento(){     //altera os dados do alimento
    int pesquisaid, i, op, j, opindustria;
    FILE *f;
    f = fopen("register.txt", "a");

    do{
        system("cls");
        printf("Digite o id do Alimento:\n");
        scanf("%d", &pesquisaid);
        for(i=0; i<=SIZE; i++){     //percorre a matriz SIZE linha por linha para encontrar o id associado aos dados do alimento
            if((ida[i]==pesquisaid)){
                for(j=0;j<=50;j++){     // percorre pelas colunas da matrizes para zerar os caracteres.
                    alimento[i][j]='\0';
                    marca[i][j] = '\0';
                }
                printf("Digite o novo Alimento:\n");
                scanf("%*c");
                scanf("%[^\n]s", &alimento[i]);
                fprintf(f,"Novo alimento cadastrado pelo id:%d eh %s\n", pesquisaid, alimento[i]);

                printf("Digite o novo valor valor calorico do alimento:\n");
                scanf("%lf", &calorias[i]);
                fprintf(f,"Novo valor calorico do alimento de id:%d eh %lf kcal\n", pesquisaid, calorias[i]);

                printf("Digite o novo preco do alimento:\n");
                scanf("%lf",&preco[i]);
                fprintf(f,"O novo preco do alimento de id:%d eh R$%lf\n", pesquisaid,preco[i]);

                printf("O alimento e industrializado?(1 = sim , outro valor = nao)\n");
                scanf("%d", &opindustria);

                if(opindustria == 1){
                    printf("Insira o novo nome da marca:\n");
                    fflush(stdin);
                    scanf("%[^\n]s", &marca[i]);
                    fprintf(f,"O novo nome da marca do alimento de id:%d eh %s", pesquisaid,marca[i]);
                    printf("\n");
                    fprintf(f,"\n");
                }
                else{
                    marca[i][0] = '\0';
                    printf("\n");
                    }   
                break;
            }
        } 
        if(i == SIZE){
            printf("ID nao cadastrado\n");
        }        
        
        printf("Digite 1 para continuar alterando ou 0 sair\n");
        scanf("%d", &op);
        system("cls");
    }while(op==1);
    fclose(f);
}

int alimentos(){    //menu para os alimentos
    int menu;

    while(menu!=5){
        printf(" (1) -- Inserir cadastro de Alimento\n");
        printf(" (2) -- consultar cadastro de Alimento\n");
        printf(" (3) -- remover cadastro de Alimento\n");
        printf(" (4) -- alterar cadastro de Alimento\n");
        printf(" (5) -- Voltar ao menu principal\n");

        printf("escolha a opcao desejada: \n");
        scanf("%d", &menu);
        system("cls");
            switch(menu){

            case 1: 
            cadastrAlimento();

            break;

            case 2:
            ConsultaAlimento();

            break;

            case 3:
            removeAlimento();
            
            break;

            case 4:
            alterarAlimento();

            break;
    }
  }
}

void relatorio(){
    int i;
    FILE *f;
    f = fopen("relatorio.txt", "a");
    fprintf(f,"Clientes Cadastrados:\n");
    for(i = 0; i<SIZE; i++){
        if(idc[i]!=0){
            fprintf(f, "ID Cliente = %d\n", idc[i]);
            fprintf(f, "nome do cliente = %s\ndata de nascimento = %02d:%02d:%04d\n", nome[i], dia[i],mes[i],ano[i]);
            fprintf(f, "Viagens realizadas = %d\n", ViagensCliente[i]);
            fprintf(f, "\n");
        }   
    }
    fprintf(f,"Alimentos Cadastrados:\n");
    for(i = 0; i<SIZE; i++){
        if(ida[i]!=0){
                fprintf(f, "ID alimento = %d\n", ida[i]);
                fprintf(f,"nome do alimento = %s\nValor calorico = %.2lf Kcal\n",alimento[i], calorias[i]);
                fprintf(f,"Marca = %s\n",marca[i]);
                fprintf(f,"Preco do alimento = R$%.2lf \n", preco[i]);
                fprintf(f,"\n");
        }     
    }
    fclose(f);
}

int main(){     //menu principal

int menup;

while (menup!=4){       //interface para selecionar se ira para a aba de cliente ou para a aba de alimentos.
    printf("(1) - Cadastro de Clientes: \n");
    printf("(2) - Cadastro de Alimentos: \n");
    printf("(3) - gerar relatorio: \n");
    printf("(4) - Sair do programa: \n");
    scanf("%d", &menup);
    system("cls");      // usado para limpar o que estava na tela ate o momento.

    switch(menup){
        case 1:
        cliente();

        break;

        case 2:
        alimentos();

        break;
        case 3:
        relatorio();
        break;
  }
 }
}