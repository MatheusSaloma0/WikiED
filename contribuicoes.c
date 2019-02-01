#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contribuicoes.h"
#include "editores.h"
#include "log.h"

struct contribuicao {
  char *nome_arq;
  char* nome_editor;
  int status;
};

struct celulacont {
  Contribuicao* info;
  CelulaCont* prox;
};

struct listacontribuicao {
  CelulaCont* prim;
  CelulaCont* ult;
};

CelulaCont* retornaLstContPrim (ListaCont* lista) {
  return lista->prim;
}

CelulaCont* retornaContProx (CelulaCont* celula) {
  return celula->prox;
}

char* retornaContNomeArq (CelulaCont* celula) {
  return celula->info->nome_arq;
}

char* retornaContNomeEditor (CelulaCont* celula) {
  return celula->info->nome_editor;
}

int retornaContStatus (CelulaCont* celula) {
  return celula->info->status;
}

ListaCont* inicializarListaCont () {
  ListaCont* lst = (ListaCont*) malloc (sizeof(ListaCont));
  lst->prim = lst->ult = NULL;
  return lst;
}

CelulaCont* procuraCont (ListaCont* lista, char* nome_arq){
  CelulaCont *aux = lista->prim;
  while(aux!=NULL && strcmp(aux->info->nome_arq, nome_arq)!=0){
    aux = aux->prox;
  }
  return aux;
}

Contribuicao* inicializarCont (char* nome_editor, char* nome_arq) {
  Contribuicao* nova = (Contribuicao*) malloc (sizeof(Contribuicao));

  nova->nome_arq = (char*) malloc ((strlen(nome_arq)+1)*sizeof(char));
  strcpy(nova->nome_arq, nome_arq);

  nova->nome_editor = (char*) malloc ((strlen(nome_editor)+1)*sizeof(char));
  strcpy(nova->nome_editor, nome_editor);

  nova->status = 1;

  return nova;
}

void insereContribuicao (ListaCont *conts, char* nome_editor, char* nome_arq, ListaEditor *editores) {
  //Se o editor estiver cadastrado, a contribuição pode ser inserida.
  if(existeEditor(editores, nome_editor))
  {
    CelulaCont* nova = (CelulaCont*) malloc (sizeof(CelulaCont));

    nova->info = inicializarCont(nome_editor,nome_arq);

    if(conts->prim == NULL) { //Caso em que a lista está vazia
    conts->prim = conts->ult = nova;
    } else { //Se a lista não estiver vazia, inserimos na última posição
      conts->ult->prox = nova;
      conts->ult = conts->ult->prox;
    }
  conts->ult->prox = NULL;
  } else {
    arqlog(8, nome_arq, nome_editor);
  }

}

void retiraContribuicao (ListaCont* lista, char* nome_editor, char* nome_arq, char* nome_pag) {
  CelulaCont* aux = procuraCont(lista, nome_arq);

  //Se aux for diferente de NULL, significa que a contribuição existe, então
  //podemos retirá-la.
  if(aux!=NULL) {
    //Se <nome_editor> for igual ao nome do editor que contribuiu, retiramos a
    //contribuição, tornando o status igual a zero.
    //(Apenas o próprio editor pode retirar suas contribuições)
    if (strcmp(aux->info->nome_editor,nome_editor) == 0) {
      aux->info->status = 0;
    } else {
      arqlog(6, nome_arq, nome_editor);
    }
  } else{
    arqlog(4, nome_arq, nome_pag);
  }
}

void retiraContPeloEditor (ListaCont* lista, char* nome_editor) {
  CelulaCont* aux = lista->prim;
  CelulaCont* ant = NULL;
  CelulaCont* aux2;

  //Percorremos toda a lista de contribuições
  while(aux != NULL) {
    //Se o editor da contribuição for <nome_editor>, retiramos ela.
    if(strcmp(aux->info->nome_editor,nome_editor) == 0) {

      if(aux == NULL) {
        return;
      }

      //Caso em que a célula é o único elemento da lista.
      if(aux == lista->prim && aux == lista->ult) {
        lista->prim = lista->ult = NULL;
        liberaCelulaCont(aux);
        return;
      }

      //Caso em que a célula é o último elemento da lista.
      if(aux == lista->ult) {
        lista->ult = ant;
        ant->prox = NULL;
        aux2 = aux;
      }

      //Caso em que a célula é o primeiro elemento da lista.
      if(aux == lista->prim) {
        lista->prim = aux->prox;
      } else { //Caso em que a célula está no meio da lista.
        ant->prox = aux->prox;
      }
      aux2 = aux;
      aux = aux->prox;
      liberaCelulaCont(aux2);
    } else {
      ant = aux;
      aux = aux->prox;
    }
  }
}

void liberaCelulaCont (CelulaCont* celula) {
  free(celula->info->nome_arq);
  free(celula->info->nome_editor);
  free(celula->info);
  free(celula);
}

ListaCont* liberaListCont(ListaCont* lista) {
  CelulaCont *aux = lista->prim, *aux2;
  while(aux!=NULL) {
    aux2 = aux;
    aux = aux->prox;
    liberaCelulaCont(aux2);
  }
  free(lista);
  return lista;
}
