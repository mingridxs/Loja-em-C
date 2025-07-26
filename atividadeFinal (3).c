#include <stdio.h>
#include <string.h>
#define MAX 200 //MAX = maximo de clientes que podem ser cadastrados


typedef struct{
    float valorT;
    int compraCancelada;
    int bonus;
    float valor1Bonus; //float pois 1 bonus pode assumir valor float
}tCompra;

typedef struct{
    char nome[100];
    char cpf[12];
    char telefone[16];
    int bonus;
    float totalCompras;
    tCompra ultimaCompra;
}tCliente;

typedef struct{
    int teto;
    float valor;
    float valorBonificado;

}tBonus;

int menup(){
    //objetivo: exibir o menu principal;
    //retorno: retorna qual opçao o usuurio deseja acessar
    int opmp; //opçao menu principal
    printf("----------------------------------------------------\n");
    printf("MENU PRINCIPAL\n01 - Configurar bonus\n02 - Cadastrar cliente\n03 - Alterar cadastro do cliente\n04 - Efetivar compra\n05 - Cancelar compra\n06 - Consultar bonus\n07 - Listar dados de todos os clientes\n08 - Listar bonus de todos os clientes\n09 - Listar os clientes que realizaram um valor\ntotal em compras inferior, superior ou igual a um\nvalor.\n00 - Sair\n");
    printf("----------------------------------------------------\n");
    scanf("%d", &opmp);
    return opmp;
}

void configurarbonus(tBonus *bonus){
    //objetivo: configurar novos valores para os bonus.
    //parametros: ponteiro *bonus que aponta para a variavel bonus na main.
    int opcb = -1;// opcb = opção configura bonus
    while(opcb != 0){
    printf("MENU CONFIGURA BONUS\n1- Alterar teto\n2- Alterar valor de um bonus\n3- Alterar valor para receber bonus\n0- Sair\n");
            scanf("%d", &opcb);
            switch(opcb){
            case 1: printf("Qual o novo valor do teto?\n");
                    scanf("%d", &bonus->teto);
                    while(bonus->teto < 0){// enquanto o valor for negativo a seguinte mensagem sera exibida e o valor sera pedido novamente:
                    printf("Erro: valor negativo. Digite novamente:\n");
                    scanf("%d", &bonus->teto);//altera o valor do teto em *bonus que apontara para bonus na função main
                    }
                    break;// retorna ao menu configura bonus
            case 2: printf("Qual o novo valor de 1 bonus?\n");
                    scanf("%f", &bonus->valor);
                    while(bonus->valor < 0){
                        printf("Erro: valor negativo. Digite novamente:\n");
                        scanf("%f", &bonus->valor);
                    }
                    break;
            case 3: printf("Qual o novo valor para receber bonus?\n");
                    scanf("%f",&bonus->valorBonificado);
                    while(bonus->valorBonificado < 0){
                        printf("Erro: valor negativo. Digite novamente:\n");
                        scanf("%f", &bonus->valorBonificado);
                    }
                    break;
            default: while(opcb != 0){//se um valor diferente de 1-3 ou 0 for digitado
                        printf("Opcao Invalida. Tente novamente:\n");
                        break;//retorna ao menu configura bonus
                    }
            }
        }
}

int verificar(tCliente cliente[],char cpf[],int numcliente){
    //objetivo: verifica se o cpf ja foi armazenado anteriormente ou n�o.
    //parametros: cliente: vetor com todos os clientes e seus cpfs; cpf: cpf que estara sendo comparado com os ja cadastrados; numcliente: numero de clientes ja cadastrados.
    //retorno: retorna o valor de j que sera usado em outras funçoes ou -1.
    for(int j=0; j<numcliente; j++){// o valor de j verifica o primeiro cliente cadastrado ate o ultimo e compara com o cpf que esta sendo cadastrado
        if(strcmp(cliente[j].cpf,cpf)== 0){
            return j;
        }
    }
    return -1;
}

void cadastrar(int *numcliente, tCliente cliente[]){
    //objetivo:cadastrar novos clientes
    //parametros: *numcliente: ponteiro que aponta para o numero de clientes na main, cliente: acessa o vetor cliente na main, MAX: usado para verificar se o numero de clientes ja alcançou o maximo estipulado
    if(*numcliente == MAX){
        printf("Erro: maximo de clientes cadatrados.\n");
        return;
    }
    printf("Qual o CPF?\n");
    scanf(" %s", cliente[*numcliente].cpf); //*numcliente aponta para numcliente na main
    getchar();//limpa o buffer de entrada
    while(strlen(cliente[*numcliente].cpf)!= 11){
        printf("Tamanho invalido! Digite o cpf novamente:\n");
        scanf(" %s", cliente[*numcliente].cpf);
        getchar();
    }
    int aux = verificar(cliente,cliente[*numcliente].cpf,*numcliente); //se aux for -1 significa que a funçao verificar retornou -1 entao o cpf nao foi cadatrado antes
        if(aux == -1){
            printf("Qual o nome?\n");
            fgets(cliente[*numcliente].nome,100, stdin);
            printf("Qual o telefone?\n");
            fgets(cliente[*numcliente].telefone,16, stdin);
            cliente[*numcliente].bonus = 0;
            cliente[*numcliente].totalCompras= 0;
            (*numcliente)++;//aumenta em 1 unidade a variavel que armazena a quantidade de clientes cadastrados
        }else{
            printf("Erro: CPF ja cadastrado.\n");
        }

}

void alterar(int numcliente, tCliente cliente[]){
    //objetivo: alterar cpf,nome ou telefone do cliente
    //parametros: numcliente: numero de clientes cadastrados; cliente: lista com clientes cadatrados;
    printf("Qual o CPF do cliente?\n");
    char antigocpf[12];
    scanf(" %s", antigocpf);
    getchar();
    int aux2 = verificar(cliente,antigocpf,numcliente);
    if(aux2 == -1){ //se aux2 for -1 significa que a funçao verificar retornou -1 ent�o o cpf nao foi cadatrado antes
        printf("Erro: CPF nao cadastrado\n");
    }else{
        int oac = -1; //opçao altera cliente
        while(oac !=0 ){//enquanto a oac for diferente de 0, o menu sera exibido
        printf("MENU ALTERA CLIENTE\n1 - Alterar CPF\n2 - Alterar nome\n3 - Alterar telefone\n0 - Voltar ao menu principal\n");
        scanf("%d",&oac);
        getchar();
        switch(oac){
            case 1: printf("Qual o novo CPF?\n");
                    char novocpf[12];
                    scanf(" %s", novocpf);
                    getchar();
                    int aux3 = verificar(cliente,novocpf,numcliente);
                    if(aux3 != -1){//a  funçao verificar retorna o numero de cadastro de cliente que vai de 0 a MAX-1 ou -1 que é quando o cpf ainda não foi cadastrado
                        printf("Erro: CPF ja cadastrado.\n");
                    }else{
                        strcpy(cliente[aux2].cpf,novocpf);// aux2 foi usado anteriormente para verificar o cpf antigo do cliente e retornou o numero desse cliente dentro do vetor cliente[];
                        printf("CPF alterado com sucesso.\n");
                    }
                    break;//volta ao menu altera cliente caso o cpf ja esteja cadastrado
            case 2: printf("Qual o novo nome?\n");
                    fgets(cliente[aux2].nome,100, stdin);
                    break;
            case 3: printf("Qual o novo telefone?\n");
                    fgets(cliente[aux2].telefone,16, stdin);
                    break;
            default: if(oac != 0){
                        printf("Opcao Invalida. Tente novamente:\n");
                        break;
                    }
        }}
    }
}

void efetivar(int numcliente, tCliente cliente[], tBonus bonus){
    //objetivo: efetivar compra
    //parametros: numcliente: numero de clientes cadastrados; cliente: lista com clientes cadatrados; bonus: contem as caracteristicas dos bonus;
    printf("Qual o CPF do cliente?\n");
    char cpfcliente[12];
    scanf(" %s", cpfcliente);
    int aux = verificar(cliente,cpfcliente,numcliente);// retorna o numero do cliente dentro do vetor cliente[];
    if(aux == -1){
        printf("Erro: CPF nao cadastrado.\n");
        return;//encerra a função e retorna ao menu principal
    }else{
       printf("BONUS = %d. VALOR CORRESPONDENTE = R$ %.2f.\n", cliente[aux].bonus, cliente[aux].bonus * bonus.valor);
    }
    printf("Qual o valor da compra?  R$\n");
    float valorCompra;
    scanf("%f", &valorCompra);
    while(valorCompra < 0){
        printf("Erro: valor negativo. Digite novamente:\n");
        scanf("%f", &valorCompra);
    }
    int aux2 = cliente[aux].bonus;
    float valorCompra2 = valorCompra;
    int qntdBU = 0;//quantidade de bonus utilizado
    int res = 0;//res = resposta para utilização de bonus
    if(cliente[aux].bonus != 0){//perguntar se o cliente possuir bonus
        printf("Deseja utilizar seu bonus? [1-sim 2-nao]\n");
        scanf(" %d", &res);
        if(res == 1){
            if(valorCompra >= (aux2 * bonus.valor)){//se o valor da compra for maior ou igual ao valor em R$ que o cliente possui em bonus
                valorCompra2 = valorCompra2 - (aux2 * bonus.valor);//o valor da compra vai ser o valor total menos o valor em bonus
                qntdBU = aux2;//a quantidade de bonus utilizado vai ser todo o bonus
                aux2 = 0;//o bonus do atual do cliente é igual a 0
            }else{//se o valor da compra for menor do que valor em R$ que o cliente possui em bonus
                qntdBU = valorCompra/bonus.valor;//a quantidade de bonus utilizado vai ser o valor total da compra dividido pelo valor de 1 bonus
                aux2 = aux2 - qntdBU;//a quantidade atual de bonus vai ser o bonus total menos os bonus necessarios pra cobrir o valor da compra
                valorCompra2 = 0;//o valor da compra é igual a 0
            }
            printf("BONUS ATUAL = %d. VALOR DA COMPRA ATUALIZADO = R$ %.2f.\n", aux2, valorCompra2);
        }
    }
    int res2 = 0;
    while(res2 != 1){
        printf("Qual o valor do pagamento do cliente? R$ \n");
        float valorPagamento;
        scanf(" %f", &valorPagamento);
        while(valorPagamento < 0){
            printf("Erro: valor negativo. Digite novamente:\n");
            scanf("%f", &valorPagamento);
        }
        if(valorPagamento < valorCompra2){
            printf("Erro: Valor do pagamento inferior ao valor da compra. Deseja desitir da compra?[1-sim 2-nao]:\n");
            scanf("%d", &res2);//resposta2
            if(res2 == 1){//encerra o while e volta ao menu principal
                printf("COMPRA NAO EFETIVADA. Valor devolvido ao cliente: R$ %.2f.\n", valorPagamento);
            }
        }else{
            if(valorPagamento > valorCompra2){
                printf("TROCO = R$ %.2f\n", valorPagamento - valorCompra2);
            }
            cliente[aux].ultimaCompra.valorT = valorCompra;
            cliente[aux].ultimaCompra.compraCancelada = 0;
            cliente[aux].ultimaCompra.bonus = qntdBU;
            cliente[aux].ultimaCompra.valor1Bonus = bonus.valor;
            //se o cliente não utilizou bonus(res!=1) e o valor da compra for >= ao valor pra ser bonificado(valorCompra >= bonus.valorBonificado)
            if(res != 1 && valorCompra >= bonus.valorBonificado){
                int qntddeBonus = valorCompra/bonus.valorBonificado; //quantidade de bonus relativo ao valor da compra;
                cliente[aux].bonus =  cliente[aux].bonus + qntddeBonus;//é adicionado a quantidade de bonus do cliente;
                if(cliente[aux].bonus > bonus.teto){//se a quantidade de bonus do cliente for maior que o teto
                    cliente[aux].bonus = bonus.teto;//a quantidade de bonus do cliente se iguala ao teto
                }
            }else if(res == 1){//se o cliente utilizou os bonus;
                cliente[aux].bonus = aux2;//o total de bonus do cliente se iguala ao valor que sobrou do uso
            }
            cliente[aux].totalCompras = cliente[aux].totalCompras + valorCompra;
            printf("COMPRA EFETIVADA!\n");
            res2 = 1;//fecha o while e retorna ao menu principal
        }
    }
}

void cancelar( int numcliente,tCliente cliente[], tBonus bonus){
    //objetivo:cancelar compra
    //parametros: numcliente: numero de clientes cadastrados; cliente: lista com clientes cadatrados; bonus: contem as caracteristicas dos bonus;
    int aux = -1;
    while(aux == -1){
    printf("Qual o CPF do cliente?\n");
    char cpfdocliente[12];
    scanf(" %s", cpfdocliente);
    aux = verificar(cliente,cpfdocliente,numcliente);//a função verificar vai retornar para aux um valor diferente de -1 se houver cliente cadastrado
    if(aux == -1){//retorna ao inicio da execução do while
        printf("Erro: CPF nao cadastrado. Deseja informar outro CPF [1-sim 2-nao]\n");
        int res;
        scanf(" %d", &res);
        if(res != 1){
            return; //retorna ao menu principal
        }
    }
    }
    int opcc = -1;//opção cancela compra
    while(opcc != 0){
    printf("MENU CANCELA COMPRA\n1 - Ultima compra\n2 - Outra compra\n3 - Exibir dados da ultima compra\n0 - Sair\n");
    scanf(" %d", &opcc);
    switch(opcc){
            case 1: if(cliente[aux].ultimaCompra.compraCancelada == 1){
                        printf("ERRO: Ultima compra ja cancelada!\n");
                        break;//retorna ao menu cancela compra
                    }else{
                        printf("Tem certeza que deseja cancelar a ultima compra? [1-sim 2-nao]\n");
                        int res;
                        scanf(" %d", &res);
                        if(res != 1){
                            printf("COMPRA NAO CANCELADA!\n");
                            break;
                        }else{
                             printf("COMPRA CANCELADA!\n");
                             cliente[aux].ultimaCompra.compraCancelada = 1;
                             if(cliente[aux].ultimaCompra.bonus == 0){//se não foi utilizado bonus na ultima compra
                                int bgc;//bgc = bonus gerados pela compra
                                bgc = cliente[aux].ultimaCompra.valorT / bonus.valorBonificado;
                                cliente[aux].bonus = cliente[aux].bonus - bgc;
                                if(cliente[aux].bonus < 0){//garante que o bonus não assuma valor negativo
                                    cliente[aux].bonus = 0;
                                }
                             }else{//se foi utilizado bonus, esse bonus retorna ao cliente
                                cliente[aux].bonus = cliente[aux].bonus + cliente[aux].ultimaCompra.bonus;
                             }
                             cliente[aux].totalCompras = cliente[aux].totalCompras - cliente[aux].ultimaCompra.valorT;
                             break;
                        }
                    }

            case 2: printf("Qual o valor da compra a ser cancelada?\n");
                    float valorcancelado;
                    scanf("%f", &valorcancelado);
                    while(valorcancelado < 0){
                        printf("Erro: valor negativo. Digite novamente:\n");
                        scanf("%f", &valorcancelado);
                    }
                    int bc = valorcancelado/bonus.valorBonificado; //bc = quanto vale o valor cancelado em bonus, será multiplicado por 2
                    printf("BONUS A SER DESCONTADO = %d. Tem certeza que deseja cancelar a compra? [1-sim 2-nao]\n", bc*2);
                    int res2;
                    scanf(" %d", &res2);
                    if(res2 == 1){
                        cliente[aux].bonus = cliente[aux].bonus - (bc*2);
                        if(cliente[aux].bonus < 0){//bonus não assume valor negativo
                            cliente[aux].bonus = 0;
                        }
                        cliente[aux].totalCompras = cliente[aux].totalCompras - valorcancelado;
                        printf("COMPRA CANCELADA!\n");
                    }else{
                        printf("COMPRA NAO CANCELADA!\n");
                    }
                    break;
            case 3: printf("NOME DO CLIENTE: %s", cliente[aux].nome);//sem \n devido fgets
                    printf("CPF DO CLIENTE: %s\n", cliente[aux].cpf);
                    printf("VALOR DA COMPRA: R$ %.2f\n", cliente[aux].ultimaCompra.valorT);
                    int bgc = 0;//bgc = bonus gerados pela compra
                    if(cliente[aux].ultimaCompra.bonus == 0){//se o cliente não utilizou bonus na compra
                        bgc = cliente[aux].ultimaCompra.valorT / bonus.valorBonificado;
                    }
                    printf("PONTOS ADQUIRIDOS COM A COMPRA: %d\n",bgc);
                    printf("VALOR DE UM BONUS NA EPOCA DA COMPRA: R$ %.2f\n", cliente[aux].ultimaCompra.valor1Bonus);
                    break;
            default: while(opcc != 0){
                        printf("Opcao Invalida. Tente novamente:\n");
                        break;
                    }
            }
    }
}

void consultarBonus(int numcliente, tCliente cliente[], tBonus bonus){
    //objetivo: consultar bonus dos clientes
    //parametros: numcliente: numero de clientes, cliente: lista com clientes cadatrados; bonus: contem as caracteristicas dos bonus;
    printf("Qual o CPF do cliente?\n");
    char cpfdocliente[12];
    scanf(" %s", cpfdocliente);
    int aux;
    aux = verificar(cliente,cpfdocliente,numcliente);//verifica se o cpf ja foi cadatrado
    if(aux == -1){
        printf("Erro: CPF nao cadastrado.\n");
        return;//retorna ao menu principal
    }
    printf("BONUS = %d. VALOR CORRESPONDENTE = R$ %.2f.\n",cliente[aux].bonus,cliente[aux].bonus * bonus.valor);
}

void listarDados(int numcliente, tCliente cliente[]){
    //objetivo: listar os dados de todos os clientes
    //parametros: numcliente: numero de clientes, cliente: lista com clientes cadatrados;
    if(numcliente == 0){
        printf("Ainda nao ha clientes cadatrados.\n");
        return;//retorna ao menu principal e para a fun��o
    }
    printf("RELATORIO DADOS DOS CLIENTES\n");
    printf("\n");
    for(int i = 0; i<numcliente; i++){
        printf("Nome: %s", cliente[i].nome);//sem \n por conta do fgets
        printf("CPF: %s\n", cliente[i].cpf);
        printf("Telefone: %s",cliente[i].telefone);//sem \n por conta do fgets
        printf("Bonus: %d\n", cliente[i].bonus);
        printf("Total em compras: R$ %.2f\n",cliente[i].totalCompras);
        for(int j =0; j<60; j++){
            printf("-");
        }
        printf("\n");
    }
}

void listarBonus(int numcliente, tCliente cliente[], tBonus bonus){
    //objetivo: listar bonus de todos os clientes
    //parametros: numcliente: numero de clientes, cliente: lista com clientes cadatrados; bonus: contem as caracteristicas dos bonus;
    if(numcliente == 0){
        printf("Ainda nao ha clientes cadatrados.\n");
        return;//retorna ao menu principal
    }
    printf("RELATORIO BONUS DOS CLIENTES\n");
    printf("\n");
    for(int i = 0; i<numcliente; i++){
        printf("Nome: %s", cliente[i].nome);//sem \n por conta do fgets
        printf("CPF: %s\n", cliente[i].cpf);
        printf("Bonus: %d\n", cliente[i].bonus);
        printf("Valor do Bonus: %.2f\n", cliente[i].bonus * bonus.valor);
        for(int j =0; j<60; j++){
            printf("-");
        }
        printf("\n");
    }
}

void listarClientesPeloVTEmC(int numcliente, tCliente cliente[]){
    //objetivo: Listar os clientes pelo valor total de compras
    //parametros: numcliente: numero de clientes, cliente: lista com clientes cadatrados;
    int aux = -1;
    while(aux != 0){
    printf("RELATORIO DE COMPRAS\n1- Total de compras inferior a um valor\n2- Total de compras superior a um valor\n3- Total de compras igual a um valor\n4- Total de compras em uma faixa\n0- Sair\n");
    scanf(" %d",&aux);
        switch(aux){
                case 1: printf("Qual o valor?\n");
                        float valor;
                        scanf("%f", &valor);
                        while(valor < 0){
                            printf("Erro: valor negativo. Digite novamente:\n");
                            scanf("%f", &valor);
                        }
                        printf("RELATORIO DE COMPRAS\n\n");
                        for(int i =0; i<numcliente; i++){
                            if(cliente[i].totalCompras<valor){//lista todos os clientes com o total de compras inferior a um valor
                                printf("Nome: %s", cliente[i].nome);
                                printf("CPF: %s\n", cliente[i].cpf);
                                printf("Total em compras: R$ %.2f\n",cliente[i].totalCompras);
                                for(int j =0; j<60; j++){
                                    printf("-");
                                }
                                printf("\n");
                            }
                        }break;//retorna ao menu relatorio de compras
                case 2: printf("Qual o valor?\n");
                        float valor2;
                        scanf("%f", &valor2);
                        while(valor2 < 0){
                            printf("Erro: valor negativo. Digite novamente:\n");
                            scanf("%f", &valor2);
                        }
                        printf("RELATORIO DE COMPRAS\n\n");
                        for(int i =0; i<numcliente; i++){
                            if(cliente[i].totalCompras>valor2){//lista todos os clientes com o total de compras superior a um valor
                                printf("Nome: %s", cliente[i].nome);
                                printf("CPF: %s\n", cliente[i].cpf);
                                printf("Total em compras: R$ %.2f\n",cliente[i].totalCompras);
                                for(int j =0; j<60; j++){
                                    printf("-");
                                }
                                printf("\n");
                            }
                        }break;
                case 3: printf("Qual o valor?\n");
                        float valor3;
                        scanf("%f", &valor3);
                        while(valor3 < 0){
                            printf("Erro: valor negativo. Digite novamente:\n");
                            scanf("%f", &valor3);
                        }
                        printf("RELATORIO DE COMPRAS\n\n");
                        for(int i =0; i<numcliente; i++){
                            if(cliente[i].totalCompras==valor3){//lista todos os clientes com o total de compras igual a um valor
                                printf("Nome: %s", cliente[i].nome);
                                printf("CPF: %s\n", cliente[i].cpf);
                                printf("Total em compras: R$ %.2f\n",cliente[i].totalCompras);
                                for(int j =0; j<60; j++){
                                    printf("-");
                                }
                                printf("\n");
                            }
                        }break;
                case 4: printf("Qual o valor inicial?\n");
                        float valori;
                        scanf("%f", &valori);
                        while(valori < 0){
                            printf("Erro: valor negativo. Digite novamente:\n");
                            scanf("%f", &valori);
                        }
                        printf("Qual o valor final?\n");
                        float valorf;
                        scanf("%f", &valorf);
                        while(valorf < 0){
                            printf("Erro: valor negativo. Digite novamente:\n");
                            scanf("%f", &valorf);
                        }
                        if(valorf < valori){
                            int aux2 = valori;
                            valori = valorf;
                            valorf = aux2;
                        }
                        printf("RELATORIO DE COMPRAS\n\n");
                        for(int i =0; i<numcliente; i++){//lista todos os clientes com o total de compras em uma faixa
                            if(cliente[i].totalCompras>=valori && cliente[i].totalCompras<=valorf){
                                printf("Nome: %s", cliente[i].nome);
                                printf("CPF: %s\n", cliente[i].cpf);
                                printf("Total em compras: R$ %.2f\n",cliente[i].totalCompras);
                                for(int j =0; j<60; j++){
                                    printf("-");
                                }
                                printf("\n");
                            }
                        }break;
               default: while(aux != 0){
                        printf("Opcao Invalida. Tente novamente:\n");
                        break;
                        }

        }
    }
}

int main(){
    tBonus bonus;
    tCliente cliente[MAX];
    int numcliente = 0;
    bonus.teto = 1000;
    bonus.valor = 0.5;
    bonus.valorBonificado = 100;
    int a; //a = guarda numero da opção escolhida no menu principal
    do{
    a = menup();
    switch(a){
        case 1: configurarbonus(&bonus);
                break;
        case 2: cadastrar(&numcliente,cliente);
                break;
        case 3: alterar(numcliente,cliente);
                break;
        case 4: efetivar(numcliente,cliente, bonus);
                break;
        case 5: cancelar(numcliente,cliente,bonus);
                break;
        case 6: consultarBonus(numcliente,cliente,bonus);
                break;
        case 7: listarDados(numcliente,cliente);
                break;
        case 8: listarBonus(numcliente,cliente,bonus);
                break;
        case 9: listarClientesPeloVTEmC(numcliente,cliente);
                break;
        default: while(a != 0){
                     printf("Opcao Invalida. Tente novamente:\n");
                     break;//retorna ao menu principal
                }
    }
    }while(a != 0);

return 0;

}
