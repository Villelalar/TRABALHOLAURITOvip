#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente {
  char nome[16];
  char sexo;
  int idade;
};

struct Venda {
  struct Cliente cliente;
  int numItens;
  int horas;
  int minutos;
  float valorTotal;
};


// FUNÇÃO

int validarSexo(char sexo);
int validarNome(char *nome);
int validarNum(int num);
int validarHorario(int hora, int minuto);
void cadastrarVendas(struct Venda *vendas, int quantidade);
void printarVenda(struct Venda *vendas, int i);
void carregarVendas(struct Venda **vendas, int *total_vendas);

int main(void) {

  char procurado[16];
  int operador;
  char resposta = 'S';
  int quantidade;
  struct Venda *vendas = NULL;
  int total_vendas = 0;

  vendas = (struct Venda *)malloc(sizeof(struct Venda) * 0); // alocação inicial
  carregarVendas(&vendas, &total_vendas);  //carrega as compras

  // MENU ESTRUTURA //
  do {
    do {
      printf("\n//  MENU  //\n\n");
      printf("1- Cadastrar venda\n2- informações de venda "
             "específica\n3- informação de todas as vendas\n4- encerrar "
             "programa\n\nEscolha: ");
      scanf("%d", &operador);

      if (operador > 4 || operador < 1) {
        printf("ERRO 1# \n");
      } else {
        printf("...");
      }

    } while (operador > 4 || operador < 1);

    // MENU SWITCH //

    switch (operador) {
    case 1:
      printf("Quantas vendas deseja cadastrar? \n");
      scanf("%d", &quantidade);

      total_vendas += quantidade;
      
      vendas = realloc(vendas, (total_vendas + quantidade) * sizeof(struct Venda));
      if (vendas == NULL) {
          printf("Erro ao alocar memória.\n");
          return 1;
      }
      cadastrarVendas(vendas, quantidade);

      printf("\nDeseja voltar ao menu?\nS- sim\nN- não\n\nR:");
      scanf(" %c", &resposta);

      break;
    case 2:
      printf("Informações de uma venda específica\n\n");
      printf("Nome do comprador:\n");
      scanf("%s", procurado);
      
      float media = 0;
      int contadorC = 0;
      float contadorP = 0;
      int contador = 0;
      
            
      for (int i = 0; i < total_vendas; i++){
        if (strcmp(vendas[i].cliente.nome, procurado) == 0){
          contador++;
        }
      }
      if (contador > 0){
        printf("%i casos de vendas em nome de %s\n", contador, procurado);
      }
      

      for (int i = 0; i < total_vendas; i++){
        if (strcmp(vendas[i].cliente.nome, procurado) == 0){
          printf("Venda encontrada!\n\n");
          contadorC++;
          printarVenda(vendas, i);
          contadorP += vendas[i].valorTotal;
        } 
      }
      
      if (contadorC > 0) {
        media = contadorP / contadorC;
        printf("Média de valores das compras de %s: %.2f\n", procurado, media);
      } else {
        printf("Nenhuma venda encontrada para o comprador %s. \n", procurado);
      }
      
      break;
    case 3:
      // ==PROCURA GERAL==
      // valor acima do pedido pelo user
      printf("== Pesquisa Geral de Compras == \n\n");
      
      //variaveis usadas somente aqui
      float valorDesjd;
      contador = 0;

      printf("Valor a achar compras maiores que : \n");
      scanf("%f", &valorDesjd);
      for (int i = 0; i < total_vendas; i++){
        if(vendas[i].valorTotal > valorDesjd){
          contador++;
        }
      }
      printf("== Quantidade de vendas de valor maior que %2.f: %i ==\n\n",  valorDesjd, contador);
      contador = 0;

      //maiores que 2 itens
      for (int i = 0; i < total_vendas; i++){
        if(vendas[i].numItens = 2){
          contador++;
        }
      }
      printf("== Quantidade de VENDAS com 2 itens: %i ==\n", contador);
      contador = 0;
      // após medio dia
      for (int i = 0; i < total_vendas; i++){
        if(vendas[i].horas > 12){
          contador++;
        }
      }
      printf("== Quantidade de VENDAS após meio dia: %i ==\n", contador);
      contador = 0;

      //pesquisa numero de mulheres
      for (int i = 0; i < total_vendas; i++){
        if (vendas[i].cliente.sexo == 'f'){
          contador++;
        } 
      }
      printf("== Quantidade de CLIENTES mulheres: %i ==\n", contador);
      contador = 0;

      //pesquisa total de preço dos homens
      for (int i = 0; i < total_vendas; i++){
        if (vendas[i].cliente.sexo == 'f'){
          contador += vendas[i].valorTotal;
        } 
      }
      printf("== Quantidade de DINHEIRO gasto pelos homens: %i ==\n", contador);
      contador = 0;

      //pesquisa total de itens vendidos
      for (int i = 0; i < total_vendas; i++){
        if (vendas[i].numItens >= 1){
          contador += vendas[i].numItens;
        } 
      }
      printf("== Quantidade de ITENS vendidos: %i ==\n", contador);
      contador = 0;

      //pesquisa valor somado de todas as vendas
      for (int i = 0; i < total_vendas; i++){
        if (vendas[i].valorTotal >= 1){
          contador += vendas[i].valorTotal;
        } 
      }
      printf("== Valor total das compras: %i ==\n", contador);
      //aproveita o total e faz o calculo da media usando ja o total descoberto
      contador = contador / total_vendas;
      printf("== Valor MÉDIO das compras: %i ==\n", contador);
      contador = 0; 

      //pesquisa total da compra mais cara
      float maior = 0;
      for (int i = 0; i < total_vendas; i++){
        if (vendas[i].valorTotal > maior){
          maior = vendas[i].valorTotal;
        } 
      }
      printf("== Maior compra: %i ==\n", contador);
      contador = 0;

      //pesquisa pelo cliente com menor nome
      char menorNome[16];
      strcpy(menorNome, vendas[0].cliente.nome); //inicia com o menor nome, copia e poe na variavel

      for (int i = 0; i < total_vendas; i++){
        if (strcmp(vendas[i].cliente.nome, menorNome) < 0) { //retorna neg caso menor
          strcpy(menorNome, vendas[i].cliente.nome); //copia o nome
        }
      }
      printf("== Compra(s) feita por: %s (menor nome)==\n", menorNome);

      for (int i = 0; i < total_vendas; i++){
        if (strcmp(vendas[i].cliente.nome, menorNome) == 0){
          printf("== Venda #%d ==\n\n", i + 1);
          printarVenda(vendas, i); 
        } 
      }

      //mais velho, usando a mesma variavel pra facilitar minha vida!!!!!!
      //nao tem problema pq esses loops se zeram toda vez após iterados
      maior = 0;
      for (int i = 0; i < total_vendas; i++){
        if (vendas[i].cliente.idade > maior){
          maior = vendas[i].cliente.idade;
          strcpy(menorNome, vendas[i].cliente.nome); //copia o nome, estou usando o mesmo pois facilita
        } 
      }
      printf("== Compra(s) feita por: %i (maior idade)==\n", menorNome);
      for (int i = 0; i < total_vendas; i++){
        if (strcmp(vendas[i].cliente.nome, menorNome) == 0){
          printarVenda(vendas, i);
        } 
      }


      printf("\nDeseja voltar ao menu?\nS- sim\nN- não\n\nR:");
      scanf(" %c", &resposta);
      break;
    case 4:
      resposta = 'N';
      break;
  }
  
  } while (resposta == 'S' || resposta == 's');

  return 0;

}

int validarSexo(char sexo) {
  return (sexo == 'm' || sexo == 'f'  || sexo=='n');
};

int validarNome(char *nome) {
  int len = strlen(nome);
  return (len >= 4 && len <= 16);
};

int validarNum(int num) {
  return (num > 0);
};

int validarHorario(int hora, int minuto){
  int validado = 0;
  if (hora <= 24 && hora >= 0){
    validado ++;
  }
  if( minuto < 60 && minuto >= 0){
    validado ++;
  }
  return(validado == 2);
}

// Função para carregar vendas do arquivo
//usa dois * pq tem realloc la dentro (cristo) então rpecisamos alterar o proprio "vendas"
void carregarVendas(struct Venda **vendas, int *total_vendas) {

FILE *arquivo = fopen("registro.txt", "r");
//se nao existee, para tudo ! tudo bem ate aquii
if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
}

// temp que armazena cada iteração do loop
struct Venda venda_temp;
//loop que acessa as linhas :D
do {
    int resultado = fscanf(arquivo, "Nome: %15[^\n]\nSexo: %c\nIdade: %d\nNúmero de Itens: %d\nHoras: %d\nMinutos: %d\nValor Total: %f\n\n",
                           venda_temp.cliente.nome,
                           &venda_temp.cliente.sexo,
                           &venda_temp.cliente.idade,
                           &venda_temp.numItens,
                           &venda_temp.horas,
                           &venda_temp.minutos,
                           &venda_temp.valorTotal);
    // EOF == end of file, ele para quando nao tem mais porra nenhuma
    if (resultado == EOF) {
        break;
    }

    // realloc tipo la em cima no total de vendas, aumenta 1 a cada iteração
    *vendas = realloc(*vendas, (*total_vendas + 1) * sizeof(struct Venda));
    if (*vendas == NULL) {
        printf("Erro ao alocar memória #004 !\n");
        fclose(arquivo);
    }

    // *vendas é nosso array de vendas normal, sem ser ponteiro, ele propriamente dito
    // *total_vendas é o [i] da venda_temp dentro do array normal
    //quando atribuimos assim, estamos falando pra ele adicionar os elementos lidos no vetor verdadeiro usado na main
    (*vendas)[*total_vendas] = venda_temp;
    (*total_vendas)++; // Incrementa o contador total de vendas

} while (1);
  fclose(arquivo);
  printf("Vendas carregadas com sucesso!\n");
}

void cadastrarVendas(struct Venda *vendas, int quantidade) {
  
  for (int i = 0; i < quantidade; i++) {
    printf("== Cadastro da venda %d == \n", i + 1);
      // NOME 
      printf("Nome cliente: \n");
      scanf("%s", vendas[i].cliente.nome);

      if(!validarNome(vendas[i].cliente.nome)){
        printf("Erro: Nome inválido. Deve ter entre 4 e 16 caracteres.\n");
        i--;
        continue;
      }
      
      // SEXO 
      printf("Sexo (m/f/n): \n"); 
      scanf(" %c", &vendas[i].cliente.sexo);

      if(!validarSexo(vendas[i].cliente.sexo)){
        printf("Erro: Sexo inválido. \n");
        i--;
        continue;
      }
      
      //IDADE 
      printf("Idade: \n");
      scanf("%d", &vendas[i].cliente.idade);
      
      if(!validarNum(vendas[i].cliente.idade)){
        printf("Erro: Idade inválida. \n");
        i--;
        continue;
      }

      printf("quantidade de itens: \n");
      scanf("%d", &vendas[i].numItens);
      
      if(!validarNum(vendas[i].numItens)){
        printf("Erro: Quantidade precisa ser no mínimo 1. \n");
        i--;
        continue;
      }
      
      // HORÁRIO
      printf("=Horário da compra (24h)= \n");
      printf("Horas: \n");
      scanf("%i", &vendas[i].horas);
      printf("Minutos: \n");
      scanf("%i", &vendas[i].minutos);

    if(!validarHorario(vendas[i].horas, vendas[i].minutos)){
        printf("Erro: Horário precisa respeitar o modelo 24 horas. \n");
        i--;
        continue;
    }

      // VALOR TOTAL 
      printf("Valor total da compra (em R$): \n");
      scanf("%f", &vendas[i].valorTotal);
      

      //  código que escreve tudo bonitao uhuuu 

      FILE *arquivo;
      arquivo = fopen("registro.txt", "r"); //teste

      if (arquivo == NULL) {
          // se o arquivo não existir, cria e escreve 
          //como nao existe nao precisa fechar
          arquivo = fopen("registro.txt", "w");
          if (arquivo == NULL) {
              printf("Erro ao criar o arquivo!\n");
              return;
          }
      } else {
          // se ja existe, só adiciona 
          //precisa fechar modo leitura pq ja existe ent abrir dnv em append
          fclose(arquivo);  
          arquivo = fopen("registro.txt", "a");
          if (arquivo == NULL) {
              printf("Erro ao abrir o arquivo para append!\n");
              return;
          }
      }

      fprintf(arquivo, "Nome: %s\nSexo: %c\nIdade: %d\nNúmero de Itens: %d\nHoras: %d\nMinutos: %d\nValor Total: %.2f\n\n", 
              vendas[i].cliente.nome, 
              vendas[i].cliente.sexo,
              vendas[i].cliente.idade, 
              vendas[i].numItens,
              vendas[i].horas,
              vendas[i].minutos,
              vendas[i].valorTotal);

      fclose(arquivo);
      
      // CONFIRMA FINALIZAÇÃO
      printf("Venda %d cadastrada com sucesso!\n", i+1);
    
    }
}

void printarVenda(struct Venda *vendas, int i){
          printf("== Venda #%d ==\n\n", i + 1);
          printf("Nome do comprador: %s\n", vendas[i].cliente.nome);
          printf("Sexo: %c\n", vendas[i].cliente.sexo);
          printf("Idade: %d\n", vendas[i].cliente.idade);
          printf("Número de itens: %d\n", vendas[i].numItens);
          printf("Horário: %d:%d\n", vendas[i].horas, vendas[i].minutos);
          printf("Valor total: %.2f\n\n", vendas[i].valorTotal);
}

