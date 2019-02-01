#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contribuicoes.h"
#include "editores.h"
#include "log.h"

struct celulaEditor {
  char* nome;
  CelulaEditor* prox;
};

struct listaeditor {
  CelulaEditor* prim;
  CelulaEditor* ult;
};

ListaEditor* inicializarListaEditor () {
  ListaEditor* lst = (ListaEditor*) malloc (sizeof(ListaEditor));

  lst->prim = lst->ult = NULL;

  return lst;
}

CelulaEditor* inicializarEditor (char* nome_editor) {
  CelulaEditor* novo = (CelulaEditor*) malloc (sizeof(CelulaEditor));

  novo->nome = (char*) malloc ((strlen(nome_editor)+1)*sizeof(char));
  strcpy(novo->nome, nome_editor);

  return novo;
}

void insereEditor(ListaEditor* lista, char* nome_editor) {
  
  //Se o editor <nome_editor> ainda nao existir, inserimos ele.
  if(!existeEditor(lista, nome_editor)){
    CelulaEditor *editor = inicializarEditor(nome_editor);

    if(lista->prim == NULL) {
      lista->prim = lista->ult = editor; //Caso em que a lista está vazia
    } else { //Se a lista não estiver vazia, inserimos na última posição
      lista->ult->prox = editor;
      lista->ult = lista->ult->prox;
    }
    lista->ult->prox = NULL;
  } else {
    //Se o editor <nome_editor> já existir, não inserimos ele
    //e escrevemos uma mensagem no arquivo de log.
    arqlog(19, nome_editor, "");
  }
}

void liberaEditor(CelulaEditor* editor) {
  free(editor->nome);
  free(editor);
}

void retiraEditor(ListaEditor* lista, char* nome_editor) {
  CelulaEditor *aux = lista->prim, *ant;

  //Procuramos a célula em que <nome_editor> está.
  while (aux != NULL && strcmp(aux->nome,nome_editor)!=0) {
    ant = aux;
    aux = aux->prox;
  }

  //Caso em que a célula é o único elemento da lista.
  if(aux == lista->prim && aux == lista->ult) {
    lista->prim = lista->ult = NULL;
    liberaEditor(aux);
    return;
  }

  //Caso em que a célula é o último elemento da lista.
  if(aux == lista->ult){
    lista->ult = ant;
    ant->prox = NULL;
    liberaEditor(aux);
    return;
  }

  //Caso em que a célula é o primeiro elemento da lista.
  if(aux == lista->prim){
    lista->prim = aux->prox;
  } else { //Caso em que a célula está no meio da lista.
    ant->prox = aux->prox;
  }
  liberaEditor(aux);
}


ListaEditor* liberaListEdit(ListaEditor* lista) {
  CelulaEditor *aux = lista->prim, *aux2;
  while(aux!=NULL) {
    aux2 = aux;
    aux = aux->prox;
    liberaEditor(aux2);
  }
  free(lista);
  return NULL;
}

int existeEditor(ListaEditor *lista, char* nome_editor){
  CelulaEditor *aux = lista->prim;

  while(aux!=NULL && strcmp(aux->nome, nome_editor)!=0) {
    aux = aux->prox;
  }
  if(aux == NULL){
    return 0;
  } else {
    return 1;
  }
}
