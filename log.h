#ifndef LOG_H
#define LOG_H

/* Escreve uma mensagem no arquivo de log
  Inputs: um código referente a mensagem a ser escrita e duas strings
  Output: nenhum
  Pre-condicao: código válido
  Pos-condicao: mensagem escrita no arquivo de log
 */
void arqlog(int cod, char* str1, char* str2);

#endif /* LOG_H */
