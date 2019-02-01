#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "links.h"
#include "pagina.h"
#include "print.h"


void printHistCont(CelulaPagina *pag, FILE *arq) {
  CelulaCont *aux = retornaLstContPrim(retornaLstContPag(pag));

  fprintf(arq, "--> Historico de contribuicoes\n");
  //Percorremos a lista de contribuições
  while(aux!=NULL){
    fprintf(arq, "%s %s",retornaContNomeEditor(aux), retornaContNomeArq(aux) );
    //Se o status for igual a zero, devemos informar que a contribuição
    //foi retirada
    if(retornaContStatus(aux) == 0) {
      fprintf(arq, " <<retirada>>");
    }
    fprintf(arq, "\n");
    aux = retornaContProx(aux);
  }
  fprintf(arq, "\n");
}

void printCont(CelulaPagina* pag, FILE* arq) {
  CelulaCont *aux = retornaLstContPrim(retornaLstContPag(pag));
  FILE *cont;
  char c;

  fprintf(arq, "\n--> Textos");

  //Percorremos a lista de contribuições
  while(aux!=NULL) {
    //Se o status for igual a 1, significa que a contribuição está ativa, então
    //devemos escrevê-la na página.
    if(retornaContStatus(aux) == 1) {
      cont = fopen(retornaContNomeArq(aux),"r");
      fprintf(arq, "\n\n-------- %s (%s) --------\n\n", retornaContNomeArq(aux), retornaContNomeEditor(aux));

      c = fgetc(cont);
      //Enquanto não chegarmos até o final do arquivo...
      while(c!=EOF) {
        //Lê um caracter do arquivo da cont. e escreve no arquivo da página.
        fprintf(arq, "%c", c);
        c = fgetc(cont);
      }
      fclose(cont);
    }
    aux = retornaContProx (aux);
  }
}

void printLinks(ListaPag* lista, CelulaPagina* pag, FILE* arq) {
  CelulaLink* aux = retornaLstLinkPrim(retornaLstLinkPag(pag));
  CelulaPagina *auxPag;

  fprintf(arq, "--> Links\n");

  //Percorremos a lista de links
  while(aux!=NULL) {
    auxPag = retornaLstPagPrim(lista);

    //Percorremos a lista de páginas até encontrar a célula que corresponde ao
    //destino de aux
    while(auxPag!=NULL && strcmp(retornaNomePag(auxPag), retornaDestino(aux))!=0) {
      auxPag = retornaPagProx(auxPag);
    }
    fprintf(arq, "%s %s\n", retornaDestino(aux), retornaNomeArq(auxPag));
    aux = retornaLinkProx(aux);
  }
}

void imprimePagina(ListaPag* lista, char* nome_pag) {
  CelulaPagina *aux = procuraPagina(lista, nome_pag);

  //Se aux for diferente de NULL, significa que a página existe, então
  //devemos gerar o arquivo texto dela com suas informações.
  if(aux!=NULL) {
    FILE *arq = fopen(retornaNomeArq(aux), "w");

    fprintf(arq, "%s\n\n", retornaNomePag(aux));

    printHistCont(aux, arq);
    printLinks(lista, aux, arq);
    printCont(aux, arq);

    fclose(arq);
  } else {
    arqlog(15, nome_pag, "");
  }
}

void imprimewiked(ListaPag* wiked) {
  CelulaPagina* aux = retornaLstPagPrim(wiked);

  //Percorremos toda a lista de páginas para que todas sejam impressas.
  while(aux!=NULL) {
    imprimePagina(wiked, retornaNomePag(aux));
    aux = retornaPagProx(aux);
  }
}
