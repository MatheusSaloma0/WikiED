#ifndef PRINT_H
#define PRINT_H

/*Escreve no arquivo da pagina o historico de contribuicoes
  Inputs: a celula de uma pagina, o arquivo texto
  Output: nenhum
  Pre-condicao: celula existe, arquivo existe
  Pos-condicao: historico de contribuicoes escrito no arquivo texto da pagina
 */
void printHistCont(CelulaPagina *pag, FILE *arq);

/*Escreve no arquivo da pagina as contribuicoes que ela possui
  Inputs: a celula de uma pagina, o arquivo texto
  Output: nenhum
  Pre-condicao: celula existe, arquivo existe
  Pos-condicao: lista de contribuicoes escrita no arquivo texto da pagina
 */
void printCont(CelulaPagina* pag, FILE* arq);

/*Escreve no arquivo da pagina os links que ela possui
  Inputs: a lista de paginas, a celula de uma pagina, o arquivo texto
  Output: nenhum
  Pre-condicao: celula existe, arquivo existe
  Pos-condicao: lista de links escrita no arquivo texto da pagina
 */
void printLinks(ListaPag* lista, CelulaPagina* pag, FILE* arq);
/*
  Inputs: lista de paginas, nome da pagina
  Output: nenhum
  Pre-condicao: a lista existe
  Pos-condicao: arquivo texto da pagina criado com todas as informacoes
 */
void imprimePagina(ListaPag* lista, char* nome_pag);

/*
  Inputs: lista de paginas
  Output: nenhum
  Pre-condicao: a lista existe
  Pos-condicao: arquivo texto de todas as paginas criados com todas as informacoes
 */
void imprimewiked(ListaPag* wiked);

#endif /* PRINT_H */
