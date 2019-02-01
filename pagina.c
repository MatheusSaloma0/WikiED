#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagina.h"

struct pagina {
  char* nome;
  char* nomeArq;
  ListaCont* conts;
  ListaLink* links;
  int passou;
};

struct celulapagina {
  Pagina* info;
  CelulaPagina* prox;
};

struct listapagina {
  CelulaPagina* prim;
  CelulaPagina* ult;
};

ListaPag* inicializarListaPagina (){
    ListaPag* lst;
    lst = (ListaPag*) malloc (sizeof(ListaPag));
    lst->prim = lst->ult = NULL;
    return lst;
}

Pagina* inicializarPagina (char* nome_pag, char* nome_arq){
  Pagina *nova = (Pagina*) malloc (sizeof(Pagina));

  nova->nome = (char*) malloc ((strlen(nome_pag)+1)*(sizeof(char)));
  strcpy(nova->nome,nome_pag);

  nova->nomeArq = (char*) malloc ((strlen(nome_arq)+1)*(sizeof(char)));
  strcpy(nova->nomeArq,nome_arq);

  nova->conts = inicializarListaCont();
  nova->links = inicializarListaLink();
  nova->passou = 0;

  return nova;
}

CelulaPagina* procuraPagina (ListaPag* lista, char* nome_pagina){
  CelulaPagina *aux;
  aux = lista->prim;

  while(aux!=NULL && strcmp(aux->info->nome, nome_pagina)!=0){
    aux = aux->prox;
  }
  return aux;
}

int existePagina(ListaPag *lista, char* pagina) {
  CelulaPagina *aux = procuraPagina (lista,pagina);

  if(aux == NULL){
    return 0;
  } else {
    return 1;
  }
}

void inserePagina (ListaPag* wiked, char* nome_pag, char* nome_arq) {

  //Se a pagina <nome_pag> ainda nao existir, inserimos ela.
  if(!existePagina(wiked, nome_pag)){
    CelulaPagina *nova = (CelulaPagina*) malloc (sizeof(CelulaPagina));

    nova->info = inicializarPagina(nome_pag, nome_arq);

    if(wiked->prim == NULL) { //Caso em que a lista está vazia
    wiked->prim = wiked->ult = nova;
    } else { //Se a lista não estiver vazia, inserimos na última posição
      wiked->ult->prox = nova;
      wiked->ult = wiked->ult->prox;
    }
    wiked->ult->prox = NULL;
  } else {
    //Se a pagina <nome_pag> já existir, não inserimos ela 
    //e escrevemos uma mensagem no arquivo de log.
    arqlog(18, nome_pag, ""); 
  }
}

void liberaPagina (CelulaPagina* pag) {
  free(pag->info->nome);
  free(pag->info->nomeArq);
  pag->info->conts = liberaListCont(pag->info->conts);
  pag->info->links = liberaListLinks(pag->info->links);
  free(pag->info);
  free(pag);
}

void retiraLinkAlternativa (ListaPag* pag, char* pagina_destino, int cod){
  CelulaPagina *aux = pag->prim;
  while(aux!=NULL) {
    retiraLink(aux->info->links, pagina_destino, cod, "");
    aux = aux->prox;
  }
}

void retiraPagina (ListaPag* lista, char* nome_pag){
  //Verificamos se a página a ser retirada existe.
  if(existePagina(lista, nome_pag)){
    CelulaPagina *aux = lista->prim, *ant;

    //Procuramos a célula em que <nome_pag> está.
    while(aux!=NULL && strcmp(aux->info->nome, nome_pag)!=0){
      ant = aux;
      aux = aux->prox;
    }

    //Caso em que a célula é o único elemento da lista.
    if(aux == lista->prim && aux == lista->ult){
      lista->prim = lista->ult = NULL;
      liberaPagina(aux);
      retiraLinkAlternativa(lista, nome_pag, 0);
      return;
    }

    //Caso em que a célula é o último elemento da lista.
    if(aux == lista->ult){
      lista->ult = ant;
      ant->prox = NULL;
      liberaPagina(aux);
      retiraLinkAlternativa(lista, nome_pag, 0);
      return;
    }

    //Caso em que a célula é o primeiro elemento da lista.
    if(aux == lista->prim){
      lista->prim = aux->prox;
    } else { //Caso em que a célula está no meio da lista.
      ant->prox = aux->prox;
    }
    liberaPagina(aux);
    retiraLinkAlternativa(lista, nome_pag, 0);

  } else {
    arqlog(3, nome_pag, "");
  }
}

ListaPag* liberaListPag(ListaPag* lista) {
  CelulaPagina *aux = lista->prim, *aux2;

  while(aux!=NULL) { //Liberamos cada célula até o final da lista.
   aux2 = aux;
   aux = aux->prox;
   liberaPagina(aux2);
  }
  free(lista);

  return NULL;
}

void fim(ListaPag* paginas, ListaEditor* editores) {
  paginas = liberaListPag(paginas);
  editores = liberaListEdit(editores);
}

int caminhoDireto (ListaPag* lista, char* pagina_origem, char* pagina_destino) {
  CelulaPagina* auxPag;
  int cd = 0; //cd = "caminho direto": Se cd == 0, não há caminho. Se cd == 1, há caminho.
  //Setamos cd = 0 pois inicialmente não sabemos se há caminho.

  //Procuramos o ponteiro da celula que corresponde a <pagina_origem> na lista de paginas.
  auxPag = procuraPagina (lista,pagina_origem);

  auxPag->info->passou = 1; //Setando o campo passou = 1
  CelulaLink* auxLink;
  ListaLink* listaL = auxPag->info->links; //listaL é a lista de links da página que está em auxPag
  auxLink = retornaLstLinkPrim(listaL); //auxLink vai receber a primeira CelulaLink desta lista de links

  //Caminhando na lista de links até que ela acabe ou encontremos um link que tem como destino <pagina_destino>
  while(auxLink!=NULL && (strcmp(retornaDestino(auxLink), pagina_destino)!=0)){
    auxLink = retornaLinkProx(auxLink);
  }

  if(auxLink != NULL){ //Se auxLink não for nulo, significa que existe cd de origem para destino
    return 1;          //Então, retornamos 1
  } else {
    //Porém, se auxLink for nulo, significa que ele percorreu toda a lista de links e não encontrou
    //um link que tem como destino a pagina_destino

    auxLink = retornaLstLinkPrim(listaL); //Resetamos auxLink para a primeira CelulaLink da lista de links

    //Com este while mais externo vamos percorrer toda a lista de links
    while(auxLink!=NULL && cd == 0){
      //Procurando o ponteiro da celula que corresponde a pagina_origem na lista de paginas.
      //Porém agora, nossa <pagina_origem> "mudou". Agora vamos verificar se há cd na página destino de auxLink
      auxPag = procuraPagina(lista, retornaDestino(auxLink));

      //Se ainda não tivermos passado nesta página, chamamos a função caminhoDireto recursivamente
      if(!(auxPag->info->passou)){
        cd = caminhoDireto(lista, retornaDestino(auxLink), pagina_destino);
      }
      auxLink = retornaLinkProx(auxLink); //Atualizando auxLink para percorrer na lista
    }
  }
  //Por fim, retornamos cd. Se após todas estas operações:
  //cd == 0, não há caminho;
  //cd == 1, há caminho.
  return cd;
}

void caminho (ListaPag* lista, char* pagina_origem, char* pagina_destino){

    if(existePagina(lista, pagina_origem)){
      if(caminhoDireto(lista, pagina_origem, pagina_destino)){
        arqlog(1, pagina_origem, pagina_destino);
      } else {
        arqlog(2, pagina_origem, pagina_destino);
      }

      //Resetando o campo "passou" das paginas
      CelulaPagina *auxPag = lista->prim;
      while(auxPag!=NULL){
        auxPag->info->passou = 0;
        auxPag = auxPag->prox;
      }
    } else {
      arqlog(17, pagina_origem, pagina_destino);
    }
}

void insereLinkPag(ListaPag* lista, char* pagina_origem, char* pagina_destino) {

  CelulaPagina *aux = procuraPagina(lista,pagina_origem);

  //Se aux for diferente de NULL, sabemos que <pagina_origem> existe, então
  //podemos inserir um link nela.
  if(aux != NULL) {
    //Se <pagina_destino> existe, então podemos adicioná-la à lista de links
    //de <página_origem>
    if(existePagina(lista, pagina_destino)) {
      insereLink(aux->info->links, pagina_destino);
    } else {
      arqlog(10, pagina_destino, "");
    }
  } else {
    arqlog(9, pagina_origem, "");
  }
}

void retiraLinkPag(ListaPag* lista, char* pagina_origem, char* pagina_destino){
  CelulaPagina *aux =  procuraPagina(lista,pagina_origem);

  //Se aux for diferente de NULL, sabemos que <pagina_origem> existe, então
  //podemos retirar um link desta página.
  if(aux != NULL){
    retiraLink(aux->info->links, pagina_destino, 1, pagina_origem);
  } else {
    arqlog(12, pagina_origem, "");
  }
}

void insereContPag (ListaPag* lista,char* nome_pagina, char* nome_editor, char* nome_arquivo, ListaEditor* editores){
  CelulaPagina *aux =  procuraPagina(lista,nome_pagina);

  //Se aux for diferente de NULL, sabemos que a página <nome_pagina> existe, então
  //podemos inserir uma contribuição nela.
  if(aux != NULL){
    FILE *arq = fopen(nome_arquivo, "r");
    if(arq != NULL){ //Se arq for diferente de NULL, significa que o arquivo a ser contribuído existe.
      insereContribuicao(aux->info->conts,nome_editor,nome_arquivo, editores);
      fclose(arq);
    } else {
      arqlog(14, nome_arquivo, nome_pagina);
    }
  } else {
    arqlog(11, nome_arquivo, nome_pagina);
  }
}

void retiraContPag (ListaPag* lista, char* nome_pagina, char* nome_editor, char* nome_arquivo){
  CelulaPagina *aux =  procuraPagina(lista,nome_pagina);

  //Se aux for diferente de NULL, sabemos que a página <nome_pagina> existe, então
  //podemos retirar uma contribuição dela.
  if(aux != NULL){
    retiraContribuicao(aux->info->conts,nome_editor,nome_arquivo, nome_pagina);
  } else {
    arqlog(13, nome_pagina, nome_arquivo);
  }
}

void retiraEditorListaPag (ListaPag* wiked, ListaEditor* editores, char* nome_editor){
  CelulaPagina* aux = wiked->prim;

  //Se o editor existir, significa que podemos verificar as páginas, identificar
  //as contribuições que ele possui e retirá-las.
  if(existeEditor(editores, nome_editor)){
    while (aux != NULL){
      retiraContPeloEditor(aux->info->conts,nome_editor);
      aux = aux->prox;
    }
    retiraEditor(editores, nome_editor);
  } else {
    arqlog(5, nome_editor, "");
  }
}

ListaCont* retornaLstContPag(CelulaPagina *pag){
  return pag->info->conts;
}

ListaLink* retornaLstLinkPag(CelulaPagina *pag){
  return pag->info->links;
}

CelulaPagina* retornaLstPagPrim(ListaPag* lista){
  return lista->prim;
}

CelulaPagina* retornaPagProx(CelulaPagina* pag){
  return pag->prox;
}

char* retornaNomePag(CelulaPagina *pag){
  return pag->info->nome;
}

char* retornaNomeArq(CelulaPagina *pag){
  return pag->info->nomeArq;
}
