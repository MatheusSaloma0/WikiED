#ifndef CONTRIBUICOES_H
#define CONTRIBUICOES_H

/* tipo contribuicao(tipo opaco). Contém campo:
  - nome do arquivo
  - nome do editor
  - status
*/
typedef struct contribuicao Contribuicao;

/* célula de contribuicao (tipo opaco). Contém campos:
  - contribuicao
  - ponteiro para a próxima célula
*/
typedef struct celulacont CelulaCont;

/* lista de contribuicoes (tipo opaco). Contém campos:
  - sentinela para a primeiro e a última célula da lista
*/
typedef struct listacontribuicao ListaCont;

/*Inicializa o sentinela de uma lista de contribuições
  Inputs: nenhum
  Output: sentinela inicializado
  Pré-condicao: nenhuma
  Pós-condicao: sentinela da lista de retorno existe e os campos primeiro e último apontam para NULL
 */
ListaCont* inicializarListaCont ();

/*Inicializa um item do tipo Contribuicao
  Inputs: o nome do editor e o nome do arquivo
  Output: um ponteiro para o tipo contribuicao criado
  Pré-condicao: nome do editor e nome do arquivo validos
  Pós-condicao: item do tipo contribuicao criado com os campos nome_editor e nome_arq
 */
Contribuicao* inicializarCont (char* nome_editor, char* nome_arq);

/*Retorna o primeiro elemento de uma lista de contribuições
  Inputs: lista de contribuições
  Output: primeiro elemento da lista de contribuições
  Pré-condicao: lista existe
  Pós-condicao: primeira célula da lista como retorno
 */
CelulaCont* retornaLstContPrim (ListaCont* lista);

/*Retorna a próxima célula
  Inputs: uma célula de contribuicao
  Output: a próxima célula de contribuicao
  Pré-condicao: célula existe
  Pós-condicao: próxima célula como retorno
 */
CelulaCont* retornaContProx (CelulaCont* celula);

/*Retorna o nome do arquivo de uma contribuição
  Inputs: célula de contribuicao
  Output: nome do arquivo de contribuição
  Pré-condicao: a célula existe
  Pós-condicao: o nome do arquivo de contribuição e retornado
 */
char* retornaContNomeArq (CelulaCont* celula);

/*Retorna o nome do editor que contribuiu
  Inputs: célula de contribuicao
  Output: nome do editor
  Pré-condicao: a célula existe
  Pós-condicao: o nome do editor que contribuiu e retornado
 */
char* retornaContNomeEditor (CelulaCont* celula);

/*Retorna o status da contribuição
  Inputs: celula de contribuicao
  Output: status da contribuicao (ativa ou inativa)
  Pré-condicao: a célula existe
  Pós-condicao: retorna o status da contribuição
 */
int retornaContStatus (CelulaCont* celula);

#include "editores.h"

/* Insere uma contribuição na lista de contribuições
  Inputs: a lista de contribuições, nome do editor, nome do arquivo, lista de editores
  Output: nenhum
  Pré-condicao: o editor e o arquivo existem
  Pós-condicao: contribuição inserida na lista de contribuicoes
 */
void insereContribuicao (ListaCont *conts, char* nome_editor, char* nome_arq, ListaEditor* lista);

/* Libera o espaço alocado de uma célula de Contribuições
  Inputs: célula de contribuição
  Output: nenhum
  Pre-condicao: a célula existe
  Pos-condicao: memória alocada e liberada
 */
void liberaCelulaCont (CelulaCont* celula);

/*Retira a a contribuição de determinada página
  Inputs: a lista de contribuicçõs, nome do editor, nome do arquivo, nome da página
  Output: nenhum
  Pré-condicao: o editor deve existir e ser o dono dessa contribuição e a página deve existir
  Pós-condicao: a contribuição se torna inativa
 */
void retiraContribuicao (ListaCont* lista,char* nome_editor, char* nome_arq, char* nome_pag);

/*Retira da lista de contribuições todas as conts que estejam associadas ao editor
  Inputs: lista de contribuições, nome do editor
  Output: nenhum
  Pré-condicao: o editor existe
  Pós-condicao: contribuicoes associadas ao editor retiradas da lista
 */
void retiraContPeloEditor (ListaCont* lista, char* nome_editor);

/*Libera toda a memória alocada para a lista de contribuições
  Inputs: a lista de contribuições
  Output: lista vazia (NULL)
  Pré-condicao: lista não é nula
  Pós-condicao: libera toda a memória alocada para a lista de contribuições
 */
ListaCont* liberaListCont(ListaCont* lista);

#endif /* CONTRIBUICOES_H */
