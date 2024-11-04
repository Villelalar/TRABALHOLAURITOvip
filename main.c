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
  char horario[5];
  float valorTotal;
};


// FUNÇÃO
int validarSexo(char sexo);
int validarNome(char *nome);
int validarNum(int num);
void cadastrarVendas(struct Venda *vendas, int quantidade);

int main(void) {

  char procurado[16];
  int operador;
  char resposta = 'S';
  int quantidade;
  struct Venda *vendas = NULL;
  int total_vendas = 0;

  vendas = (struct Venda *)malloc(sizeof(struct Venda) * 0); // Alocação inicial
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
      if (contador > 0){
        printf("%i compras vendas em nome de %s\n", contador, procurado);
      }
      

      for (int i = 0; i < total_vendas; i++){
        if (strcmp(vendas[i].cliente.nome, procurado) == 0){
          printf("Venda encontrada!\n\n");
          contadorC++;
          
          printf("== Venda #%d ==\n\n", i + 1);
          printf("Nome do comprador: %s\n", vendas[i].cliente.nome);
          printf("Sexo: %c\n", vendas[i].cliente.sexo);
          printf("Idade: %d\n", vendas[i].cliente.idade);
          printf("Número de itens: %d\n", vendas[i].numItens);
          printf("Horário: %s\n", vendas[i].horario);
          printf("Valor total: %.2f\n\n", vendas[i].valorTotal);
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
    // PROCURA GERAL
    // valor acima do pedido pelo user
      float valorDesjd;
      for (int i = 0; i < total_vendas; i++){
        printf("Valor a achar compras maiores que : \n")
        scanf("%f", &valorDesjd)
        if(vendas[i].valorTotal > valorDesjd){
          contador++;
        }
      }
      printf("== nQuantidade de vendas de valor maior que %f: %i ==\n\n",  valorDesjd, contador);
      contador = 0;

      //maiores que 2 itens
      for (int i = 0; i < total_vendas; i++){
        if(vendas[i].numItens = 2){
          contador++;
        }
      }
      printf("== Quantidade de vendas com 2 itens: %i ==\n", contador);
      contador = 0;
      
      //pesquisa nomes
      for (int i = 0; i < total_vendas; i++){
        if (strcmp(vendas[i].cliente.nome, procurado) == 0){
          printf("aaaa")
        } 
      }
      break;
    case 4:
      resposta = 'N';
      break;
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
      printf("Horário da compra (HH:MM, formato 24h): \n");
      scanf("%s", vendas[i].horario);
  
      // VALOR TOTAL 
      printf("Valor total da compra (em R$): \n");
      scanf("%f", &vendas[i].valorTotal);
      
      // CONFIRMA FINALIZAÇÃO
      printf("Venda %d cadastrada com sucesso!\n", i+1);
    
    }
}