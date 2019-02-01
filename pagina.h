#ifndef PAGINA_H
#define PAGINA_H

#include "contribuicoes.h"
#include "editores.h"
#include "links.h"
#include "log.h"

/* pagina (tipo opaco). Contém campos:
  - nome;
  - arquivo;
  - lista de contribuições;
  - lista de links;
*/
typedef struct pagina Pagina;

/* celulapagina (tipo opaco). Contém campos:
  - pagina
  - ponteiro para a próxima célula
*/
typedef struct celulapagina CelulaPagina;

/* listapagina (tipo opaco). Contém campos:
  - sentinela para a primeiro e a última célula da lista
*/
typedef struct listapagina ListaPag;

/*Inicializa o tipo pagina, alocando o espaço necessário e preenchendo seus campos
  Inputs: nome da página e nome do arquivo
  Output: página inicializada
  Pré-condição: o nome da página e do arquivo não podem ser nomes compostos
  Pós-condição: os campos do tipo pagina foram preenchidos
 */
Pagina* inicializarPagina (char* nome_pag, char* nome_arq);

/*Inicializa o sentinela de uma lista de páginas
  Inputs: nome da página e nome do arquivo
  Output: sentinela inicializado
  Pré-condição: o nome da página e do arquivo não podem ser nomes compostos
  Pós-condição: sentinela da lista de retorno existe e os campos primeiro e último apontam para NULL
 */
ListaPag* inicializarListaPagina ();

/* Insere uma página na lista de páginas
  Inputs: lista de páginas, nome da página e nome do arquivo
  Output: nenhum
  Pré-condição: a lista de páginas existe
  Pós-condição: lista modificada, isto é, a célula página foi inserida na lista
 */
void inserePagina (ListaPag* wiked,char* nome_pag, char* nome_arq);

/* Retira um pagina da lista de páginas
  Inputs: lista de páginas e nome da página
  Output: nenhum
  Pré-condição: a lista de páginas existe
  Pós-condição: a página foi excluída (caso ela estevisse na lista) assim como suas contribuições e links
 */
void retiraPagina (ListaPag* lista, char* nome_pag);

/* Verifica se há caminho entre duas páginas (por meio das listas de links). Escreve no arquivo de log
(HA/não HA CAMINHO DA <pagina_origem> PARA <pagina_destino>)
  Inputs: lista de páginas, página de origem e página de destino
  Output: nenhum
  Pré-condição: a página de origem e destino existem
  Pós-condição: o arquivo log foi alterado com a resposta apropriada para o caso
 */
void caminho (ListaPag* lista,char* pagina_origem, char* pagina_destino);

/* Gera o arquivo e imprime as informações da página especificada
  Inputs: lista de páginas e nome da página
  Output: nenhum
  Pré-condição: a lista de páginas e a página existem
  Pós-condição: o arquivo para a página foi gerado e suas informações foram impressas
 */
void imprimePagina (ListaPag* lista, char* nome_pag);

/* Gera os arquivos e imprime todas as informações das páginas da wiked!, como	especificado acima
  Inputs: nenhum
  Output: nenhum
  Pré-condição: a wiked existe
  Pós-condição: arquivos gerados com as informações correspondentes
 */
void imprimewiked(ListaPag* wiked);

/* Determina a finalização do programa
  Inputs:nenhum
  Output: nenhum
  Pré-condição: a lista de páginas e a lista de editores existem
  Pós-condição: toda a memória foi liberada
 */
void fim(ListaPag* paginas, ListaEditor* editores);

/* Insere um link na lista de links de uma determinada página
  Inputs: lista de páginas, nome da página de origem e da página de destino
  Output: nenhum
  Pré-condição: a lista de páginas existe
  Pós-condição: o link foi inserido na lista de links da página
 */
void insereLinkPag (ListaPag* lista, char* pagina_origem, char* pagina_destino);

/* Retira um link na lista de links de uma determinada página
  Inputs: lista de páginas, nome da página de origem e da página de destino
  Output: nenhum
  Pré-condição: a lista de páginas existe
  Pós-condição: o link foi retirado da lista de links da página
 */
void retiraLinkPag (ListaPag* lista, char* pagina_origem, char* pagina_destino);

/*  Insere uma contribuição na lista de contribuições de uma página
  Inputs: lista de páginas,nome da página, nome do editor, nome do arquivo de contribuição, lista de editores
  Output: nenhum
  Pré-condição: lista de páginas e de editores existem, assim como o arquivo de contribuição
  Pós-condição: contribuição inserida na página
 */
void insereContPag (ListaPag* lista,char* nome_pagina, char* nome_editor, char* nome_arquivo, ListaEditor* editores);

/* Retira a contribuição da lista de contribuições de uma página
  Inputs: lista de páginas, nome da página, nome do editor e nome do arquivo de contribuição
  Output: nenhum
  Pré-condição: lista de páginas existe
  Pós-condição: lista de contribuições da página foi modificada com a nova contribuição
 */
void retiraContPag (ListaPag* lista,char* nome_pagina, char* nome_editor, char* nome_arquivo);

/* Retira as contribuições de um determinado editor da lista de páginas se este foi exluído da lista de contribuições
  Inputs: lista de páginas, lista de editores e nome do editor
  Output: nenhum
  Pré-condição: lista de páginas e de editores existe
  Pós-condição: as contribuições desse editor foram retiradas de toda a lista de páginas
 */
void retiraEditorListaPag (ListaPag* wiked, ListaEditor* editores,char* nome_editor);

/* Procura uma página lista de páginas
  Inputs: lista de páginas e nome da página
  Output: célula página ou NULL caso ela não tenha sido encontrada
  Pré-condição: lista de páginas existe
  Pós-condição: CelulaPagina ou NULL como retorno da função
 */
CelulaPagina* procuraPagina (ListaPag* lista, char* nome_pagina);

/* Verifica se uma página existe na lista de páginas
  Inputs: lista de páginas e nome da página
  Output: um inteiro
  Pré-condição: lista de páginas existe
  Pós-condição: 0 se a página não existe ou 1 se a página existe
 */
int existePagina(ListaPag *lista, char* pagina);

/*É utilizada quando vamos retirar uma página e precisamos remover de todas as
  outras páginas os links que levam à esta página em questão.
  Inputs: a lista de páginas, página de destino, código
  Output: nenhum
  Pré-condição: lista não nula, pagina de destino existe
  Pós-condição: links removidos
 */
void retiraLinkAlternativa (ListaPag* lista, char* pagina_destino, int cod);

/* Retorna a lista de contribuições da página
  Inputs: célula de página
  Output: nenhum
  Pré-condição: célula existe
  Pós-condição: lista de contribuições da página retornada
 */
ListaCont* retornaLstContPag(CelulaPagina *pag);

/* Retorna a lista de links da página
  Inputs: célula de página
  Output: nenhum
  Pré-condição: célula existe
  Pós-condição: lista de links da página retornada
 */
ListaLink* retornaLstLinkPag(CelulaPagina *pag);

/* Retorna a primeira celula da pagina
  Inputs: lista de paginas
  Output: celula da pagina
  Pre-condição: lista existe
  Pos-condição: celula da primeira posicao retornada
 */
CelulaPagina* retornaLstPagPrim(ListaPag* lista);

/* Retorna a próxima célula
  Inputs: célula de pagina
  Output: próxima célula da página
  Pré-condição: celula existe
  Pós-condição: próxima célula retornada
 */
CelulaPagina* retornaPagProx(CelulaPagina* pag);

/* Retorna o nome de uma página
  Inputs: celula de página
  Output: string
  Pré-condição: célula existe
  Pós-condição: nome da página retornado
 */
char* retornaNomePag(CelulaPagina *pag);

/* Retorna o nome do arquivo da página
  Inputs: célula de página
  Output: string
  Pré-condição: célula existe
  Pós-condição: nome do arquivo da página retornado
 */
char* retornaNomeArq(CelulaPagina *pag);

#endif /* PAGINA_H */
