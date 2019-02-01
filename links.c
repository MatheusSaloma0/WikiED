#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "links.h"
#include "log.h"

struct celulalink {
  char* destino;
  CelulaLink* prox;
};

struct listalink {
  CelulaLink* prim;
  CelulaLink* ult;
};

CelulaLink* retornaLstLinkPrim (ListaLink* lista) {
  return lista->prim;
}

CelulaLink* retornaLinkProx (CelulaLink* celula) {
  return celula->prox;
}

char* retornaDestino(CelulaLink* link) {
  return link->destino;
}

ListaLink* inicializarListaLink () {
  ListaLink* lst = (ListaLink*) malloc (sizeof(ListaLink));

  lst->prim = lst->ult = NULL;

  return lst;
}

CelulaLink* inicializarLink (char* nome_destino){
  CelulaLink* nova = (CelulaLink*) malloc (sizeof(CelulaLink));

  nova->destino = (char*) malloc ((strlen(nome_destino)+1)*(sizeof(char)));
  strcpy(nova->destino,nome_destino);

  return nova;
}

void insereLink (ListaLink* lista, char* pagina_destino) {

  if(lista->prim == NULL) { //Caso em que a lista está vazia
    lista->prim = lista->ult = inicializarLink(pagina_destino);
  } else { //Se a lista não estiver vazia, inserimos na última posição
    lista->ult->prox = inicializarLink(pagina_destino);
    lista->ult = lista->ult->prox;
  }
  lista->ult->prox = NULL;
}

void liberaCelulaLink (CelulaLink* celula) {
  free(celula->destino);
  free(celula);
}

void retiraLink (ListaLink* lista, char* pagina_destino, int cod, char* pagina_origem) {
  CelulaLink* aux = lista->prim;
  CelulaLink* ant = NULL;

  //Procuramos a célula que tem como destino <pagina_destino>.
  while(aux!=NULL && (strcmp(aux->destino,pagina_destino)!=0)) {
    ant = aux;
    aux = aux->prox;
  }

  if(aux == NULL) {
    //Se cod for igual a 1, significa que uma mensagem deve ser escrita
    //no arquivo de log.
    if(cod) {
      arqlog(7, pagina_origem, pagina_destino);
    }
    return;
  }

  //Caso em que a célula é o único elemento da lista.
  if(aux == lista->prim && aux == lista->ult) {
    lista->prim = lista->ult = NULL;
    liberaCelulaLink(aux);
    return;
  }

  //Caso em que a célula é o último elemento da lista.
  if(aux == lista->ult) {
    lista->ult = ant;
    ant->prox = NULL;
    liberaCelulaLink(aux);
    return;
  }

  //Caso em que a célula é o primeiro elemento da lista.
  if(aux == lista->prim) {
    lista->prim = aux->prox;
  } else {
    ant->prox = aux->prox;
  }
  liberaCelulaLink(aux);
}

ListaLink* liberaListLinks(ListaLink* lista) {
  CelulaLink *aux = lista->prim, *aux2;
  while(aux!=NULL) {
    aux2 = aux;
    aux = aux->prox;
    liberaCelulaLink(aux2);
  }
  free(lista);
  return NULL;
}
