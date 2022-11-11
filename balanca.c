// Aluno - Matricula
// Leandro Braga - 2022004260
// Joao Pedro Renno - 2022010651

#include <stdio.h>
#include <stdlib.h>

// TODO implementar essa funcao, voce pode criar outras funcoes
// e outros structs que achar necessario
// Devolve 0 se naum existe solucao
// devolve 1 se existe solucao, e nesse caso deve preencher o
// arranjo lados com 0 ou 1 para cada item indicando qual prato
// esta cada item

// USAMOS A MESMAS CONSTRUCOES DE STRUCTS E TYPES DAS AULAS DE FILAS
// POREM APLICANDO PARA O CONCEITO DE PILHAS

// criando a o tipo / estrutura do "elemento" da pilha
typedef struct TypeElemento
{
  int peso;
  struct TypeElemento *proximo;
} Elemento;

// definindo o tipo / estrutura de uma pilha em si, ou seja, que aponta pro topo
struct TypePilha
{
  Elemento *topo;
};

// definindo o tipo Pilha que é um apontador pro topo da pilha
typedef struct TypePilha *Pilha;

Pilha CriarPilha()
{
  Pilha P = (Pilha)malloc(sizeof(struct TypePilha));
  P->topo = NULL;
  return P;
}

void Empilhar(Pilha P, int novoPeso)
{
  // novo elemento
  Elemento *novoElemento = (Elemento *)malloc(sizeof(Elemento));
  novoElemento->peso = novoPeso;
  novoElemento->proximo = P->topo;
  P->topo = novoElemento;
}

Pilha Desimpilhar(Pilha P)
{
  // nova pilha auxiliar
  Pilha auxPilha = CriarPilha();
  auxPilha->topo = P->topo->proximo;
  free(P);
  return auxPilha;
}

int PilhaVazia(Pilha P)
{
  if (P->topo == NULL)
    return 1;
  return 0;
}

void AjustaLados(int *lados, Pilha P, int numero_items, int *pesos)
{

  // setando todos os lados como 1
  for (int i = 0; i < numero_items; i++)
  {
    lados[i] = 1;
  }

  int i = 0;

  // ir passando pro lado 0 os items da pilha
  while (!PilhaVazia(P))
  {
    if (pesos[i] == P->topo->peso)
    {
      lados[i] = 0;
      P = Desimpilhar(P);
    }

    if (i == numero_items)
    {
      i = 0;
      continue;
    }
    i++;
  }
}

int balanca_julgamento(int numero_itens, int *pesos, int *lados)
{
  int ladoAux = 0, check = 0, metade = 0;

  // iterando pelos pesos para verificar se a soma de todos resulta em um numero par
  for (int i = 0; i < numero_itens; i++)
  {
    check += pesos[i];
  }
  // caso nao seja par, ja finaliza o codigo
  if (check % 2 != 0)
    return 0;

  metade = check / 2;

  // criando a pilha e colocando o primeiro item
  Pilha pilha = CriarPilha();
  Empilhar(pilha, pesos[0]);
  ladoAux += pilha->topo->peso;

  for (int i = 1; i < numero_itens; i++)
  {

    if (ladoAux == metade)
    {
      AjustaLados(lados, pilha, numero_itens, pesos);
      return 1;
    }

    Empilhar(pilha, pesos[i]);
    ladoAux += pilha->topo->peso;

    if (ladoAux > metade)
    {
      ladoAux -= pesos[i];
      pilha = Desimpilhar(pilha);
    }

    for (int j = i + 1; j < numero_itens; j++)
    {
      if (ladoAux == metade)
      {
        AjustaLados(lados, pilha, numero_itens, pesos);
        return 1;
      }

      Empilhar(pilha, pesos[j]);
      ladoAux += pilha->topo->peso;

      if (ladoAux > metade)
      {
        ladoAux -= pesos[j];
        pilha = Desimpilhar(pilha);
      }
    }

    ladoAux -= pilha->topo->peso;
    pilha = Desimpilhar(pilha);
  }

  // apos resolver o lado, usar um while(!pilhavazia) e ir desimpilhando e virificando qual a posicao dele em lados

  return 0;
}
//*********************
// NAO ALTERE A MAIN
//*********************
int main(int argc, char *argv[])
{
  int numero_itens;
  int *lados;
  int *pesos;
  int *pesos_originais;
  int tem_solucao = 0;

  scanf("%d\n", &numero_itens);

  // alocando memoria para os arranjos
  pesos = (int *)malloc(numero_itens * sizeof(int));
  pesos_originais = (int *)malloc(numero_itens * sizeof(int));
  lados = (int *)malloc(numero_itens * sizeof(int));
  for (int i = 0; i < numero_itens; i++)
    lados[i] = 0;

  if (pesos == NULL || lados == NULL || pesos_originais == NULL)
  {
    perror("Erro na alocacao de memoria.\n");
    exit(EXIT_FAILURE);
  }

  // lendo os pesos
  for (int i = 0; i < numero_itens; i++)
  {
    scanf("%d", &(pesos[i]));
    pesos_originais[i] = pesos[i];
  }

  // resolvendo
  tem_solucao = balanca_julgamento(numero_itens, pesos, lados);
  // tem_solucao = balanca_meupau(numero_itens, pesos, lados);

  // verificando a solucao
  if (tem_solucao)
  {
    int soma_esquerdo = 0;
    int soma_direito = 0;
    for (int i = 0; i < numero_itens; i++)
    {
      if (lados[i] == 0)
        soma_esquerdo += pesos_originais[i];
      else
        soma_direito += pesos_originais[i];
    }
    if (soma_direito == soma_esquerdo)
    {
      printf("Foi para o ceu pois achou uma solucao com %d quilos de cada lado\n", soma_esquerdo);
    }
    else
    {
      // nao deveria cair aqui nunca
      printf("Foi para o inferno, pois achou que tinha achado a solucao mas nao tinha\n");
    }
  }
  else
  {
    printf("Foi para o inferno, pois nao existe solucao mesmo\n");
  }

  free(pesos);
  free(lados);
  free(pesos_originais);

  return 0;
}

//*********************
// NAO ALTERE A MAIN
//*********************
