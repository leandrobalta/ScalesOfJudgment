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

int Desimpilhar(Pilha P)
{
  // nova pilha auxiliar
  int retirado = P->topo->peso;
  Pilha auxPilha = CriarPilha();
  auxPilha->topo = P->topo->proximo;
  free(P->topo);
  P = auxPilha;
  return retirado;
}

int PilhaVazia(Pilha P)
{
  if (P == NULL)
    return 1;
  return 0;
}

void CriaGrafo(int *pesos, int nmrItems)
{
  int helper = 0;

  while (1)
  {
    int *checados = malloc(sizeof(int) * nmrItems);

    for (int i = 0; i < pesos; i++)
    {
      /* code */
    }
  }
}

// UTILIZAR O CONCEITO DE BFS PARA PERCORRER OS PESOS E ACHAR A SOLUCAO POSSIVEL

int balanca_julgamento(int numero_itens, int *pesos, int *lados)
{
  int check = 0, metade, helper = 1, ladoAux = 0;

  // iterando pelos pesos para verificar se a soma de todos resulta em um numero par
  for (int i = 0; i < numero_itens; i++)
  {
    check += pesos[i];
  }
  // caso nao seja par, ja finaliza o codigoD
  if (check % 2 != 0)
    return 0;

  metade = check / 2;

  Pilha pilhaAux = CriarPilha();

  // Colocando o primeiro peso em um dos lados da balanca
  //  nossa ideia é ir testando as possibilidades tirando e colocando da pilha ate que
  //  o peso de um dos lados da pilha seja igual a "metade"
  Empilhar(pilhaAux, pesos[0]);

  // trabalhar com o helper, caso as possibilades tenham sido testadas, trocar o helper
  while (!PilhaVazia(pilhaAux))
  {
    if (ladoAux == metade)
    {
      printf("ESQUERDO == METADE");
      break;
    }

    int retirado = Desimpilhar(ladoAux);
    ladoAux += retirado;

    if (ladoAux < metade)
    {
      Empilhar(pilhaAux, pesos[helper]);
      printf("ESQUERDO MENOR QUE METADE: %d\n", ladoAux);
    }
    else if (ladoAux > metade)
    {
      printf("ESQUERDO MAIOR QUE METADE: %d\n", ladoAux);
      Empilhar(pilhaAux, pesos[helper]);
      ladoAux -= retirado;
    }
    else
    {
      printf("CAIU NO ELSE\n");
      break;
    }

    helper++;
  }

  //----------------------------------

  Empilhar(pilhaAux, pesos[0]);
  ladoAux += pesos[0];

  while (!PilhaVazia(pilhaAux))
  {
    if (pilhaAux->topo == pesos[0])
    {
      if (pesos[0] == metade)
      {
        printf("LADO COMPLETO");
        break;
      }

      continue;
    }

    Empilhar(pilhaAux, pesos[helper]);
    ladoAux += pesos[helper];

    if (ladoAux == metade)
    {
      printf("LADO COMPLETO");
      break;
    }
    else if (ladoAux < metade)
    {
    }
  }

  while (1)
  {
  }

  // usar pilha pra ir tirando e colocando ate que o resultado seja igual a metade

  return 1;
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
