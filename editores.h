#ifndef EDITORES_H
#define EDITORES_H

/* célula de editor (tipo opaco). Contém campos:
  - nome do editor
  - ponteiro para a próxima célula
*/
typedef struct celulaEditor CelulaEditor;

/* lista de editores (tipo opaco). Contém campos:
  - sentinela para a primeiro e a última célula da lista
*/
typedef struct listaeditor ListaEditor;

/* Inicializa a sentinela de uma lista de editores
  Inputs: nenhum
  Output: sentinela inicializada
  Pré-condicao: nenhuma
  Pós-condicao: sentinela da lista de retorno existe e os campos primeiro e último apontam para NULL
 */
ListaEditor* inicializarListaEditor ();

/* Inicializa a celula editor e o campo nome
  Inputs: nome do editor
  Output: celula inicializada
  Pré-condicao: o nome do editor não pode ser um nome composto
  Pós-condicao: célula inicializada e campo nome alocado e preenchido
 */
CelulaEditor* inicializarEditor (char* nome_editor);

/* Insere uma célula editor com o nome especificado (deve ser único) na lista de editores
  Inputs: lista de editores e nome do editor
  Output: lista de editores com uma nova célula editor
  Pré-condicao: o nome do editor não e composto
  Pós-condicao: o editor existe e foi criado a partir do nome dado
 */
void insereEditor (ListaEditor* lista,char* nome_editor);

/* Retira uma célula editor da lista de editores(desde que ela não seja nula)
  Inputs: lista de editores e nome do editor
  Output: nenhum
  Pré-condicao: lista de editores existe
  Pós-condicao: lista modificada, isto é, sem a célula editor que desejava-se retirar
 */
void retiraEditor(ListaEditor* lista, char* nome_editor);

/* Libera a lista de editores
  Inputs: lista de editores
  Output: lista de editores
  Pré-condicao: a lista existe
  Pós-condicao: a lista foi liberada logo o valor de retorno é NULL
 */
ListaEditor* liberaListEdit(ListaEditor* lista);

/* Verifica se um determinado editor existe
  Inputs: lista de editores e nome do editor
  Output: 0(nao existe) ou 1(existe)
  Pré-condicao: lista de editores existe
  Pós-condicao: o valor retornado é 0 ou 1
 */
int existeEditor(ListaEditor *lista, char* nome_editor);

#endif /* EDITORES_H */
