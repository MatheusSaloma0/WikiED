#ifndef LINKS_H
#define LINKS_H

/* celula link (tipo opaco). Contém campos:
  - página destino
  - ponteiro para a proxima célula
*/
typedef struct celulalink CelulaLink;

/* lista de links (tipo opaco). Contém campos:
  - sentinela para a primeiro e a última célula da lista
*/
typedef struct listalink ListaLink;


/* Inicializa a célula link e o destino
  Inputs: nome da página de destino
  Output: célula inicializada
  Pré-condicao: o nome da página nao pode ser um nome composto
  Pós-condicao: célula inicializada e campo destino alocado e preenchido
 */
CelulaLink* inicializarLink (char* nome_destino);

/*  Inicializa o sentinela de uma lista de links
  Inputs: nenhum
  Output: sentinela inicializada
  Pré-condicao: nenhuma
  Pós-condicao: sentinela da lista de retorno existe e os campos primeiro e último apontam para NULL
 */
ListaLink* inicializarListaLink ();

/* Retorna a primeira célula da lista de links
  Inputs: lista de links
  Output: primeira célula da lista de links
  Pré-condicao: lista existe
  Pós-condicao: primeira célula da lista como retorno
 */
CelulaLink* retornaLstLinkPrim (ListaLink* lista);

/* Dada uma célula de links, retorna a próxima
  Inputs: célula link
  Output: a proxima célula link
  Pré-condicao: a célula existe
  Pós-condicao: a célula retornada é a célula seguinte a célula dada como parâmetro
 */
CelulaLink* retornaLinkProx (CelulaLink* celula);

/* Dada uma célula de link, retorna seu campo destino
  Inputs: célula link
  Output: string
  Pré-condicao: a célula existe e foi inicializada
  Pós-condicao: a string retornada é igual a string presente no campo destino da célula dada como parâmetro
 */
char* retornaDestino(CelulaLink* link);

/* Insere uma célula link na lista de links
  Inputs: lista de links e página de destino
  Output: nenhum
  Pré-condicao: a lista existe
  Pós-condicao: a lista modificada com a nova célula
*/
void insereLink (ListaLink* lista, char* pagina_destino);

/* Libera uma célula link
  Inputs: célula link
  Output: nenhum
  Pré-condicao: a célula existe
  Pós-condicao: a célula foi liberada
 */
void liberaCelulaLink (CelulaLink* celula);

/* Retira uma célula da lista de links(desde que ela não seja nula)
  Inputs: lista de links, nome da pagina_destino, nome da pagina_origem e cod(0 ou 1)
  Output: nenhum
  Pré-condicao: a lista existe
  Pós-condicao: a lista modificada,isto é, sem o elemento que desejava-se retirar
 */
void retiraLink (ListaLink* lista, char* pagina_destino, int cod, char* pagina_origem);

/* Libera a lista de links
  Inputs: lista de links
  Output: lista de links
  Pré-condicao: a lista existe
  Pós-condicao: a lista foi liberada, logo o retorno deve ser NULL
 */
ListaLink* liberaListLinks(ListaLink* lista);

#endif /* LINKS_H */
