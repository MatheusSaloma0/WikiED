#include <stdio.h>
#include <stdlib.h>
#include "log.h"

//Cada código representa uma mensagem a ser escrita no arquivo log.txt
void arqlog(int cod, char* str1, char* str2)
{
  FILE* arq = fopen("log.txt","a");

  switch(cod)
  {
    case 1:
      fprintf(arq, "HA CAMINHO DA PAGINA %s PARA %s\n", str1, str2);
      break;
    case 2:
      fprintf(arq, "NAO HA CAMINHO DA PAGINA %s PARA %s\n", str1, str2);
      break;
    case 3:
      fprintf(arq, "ERRO 03: NAO FOI POSSIVEL RETIRAR A PAGINA %s, POIS ELA NAO EXISTE\n", str1);
      break;
    case 4:
      fprintf(arq, "ERRO 04: NAO FOI POSSIVEL RETIRAR A CONTRIBUICAO %s, POIS ELA NAO SE ENCONTRA NA PAGINA %s\n", str1, str2);
      break;
    case 5:
      fprintf(arq, "ERRO 05: NAO FOI POSSIVEL RETIRAR O EDITOR %s, POIS ELE NAO EXISTE\n", str1);
      break;
    case 6:
      fprintf(arq, "ERRO 06: A CONTRIBUICAO %s NAO PODE SER EXCLUIDA PELO EDITOR %s\n", str1, str2);
      break;
    case 7:
      fprintf(arq, "ERRO 07: NAO FOI POSSIVEL RETIRAR O LINK, POIS NA PAGINA %s NAO EXISTE O LINK PARA %s\n", str1, str2);
      break;
    case 8:
      fprintf(arq, "ERRO 08: NAO FOI POSSIVEL INSERIR %s, POIS %s NAO ESTA CADASTRADO NA LISTA DE EDITORES\n", str1, str2);
      break;
    case 9:
      fprintf(arq, "ERRO 09: NAO FOI POSSIVEL FAZER ESSE LINK, POIS A PAGINA DE ORIGEM %s NAO EXISTE\n", str1);
      break;
    case 10:
      fprintf(arq, "ERRO 10: NAO FOI POSSIVEL FAZER ESSE LINK, POIS A PAGINA DE DESTINO %s NAO EXISTE\n", str1);
      break;
    case 11:
      fprintf(arq, "ERRO 11: NAO FOI POSSIVEL INSERIR A CONTRIBUICAO %s, POIS A PAGINA %s NAO EXISTE\n", str1, str2);
      break;
    case 12:
      fprintf(arq, "ERRO 12: NAO FOI POSSIVEL RETIRAR ESSE LINK, POIS A PAGINA DE ORIGEM %s NAO EXISTE\n", str1);
      break;
    case 13:
      fprintf(arq, "ERRO 13: NAO FOI POSSIVEL RETIRAR A CONT. %s DE %s, POIS A PAGINA %s NAO EXISTE\n", str2, str1, str1);
      break;
    case 14:
      fprintf(arq, "ERRO 14: NAO FOI POSSIVEL INSERIR A CONT. %s EM %s, POIS O ARQUIVO %s NAO EXISTE\n", str1, str2, str1);
      break;
    case 15:
      fprintf(arq, "ERRO 15: NAO FOI POSSIVEL GERAR O ARQUIVO TEXTO DA PAGINA %s, POIS ELA NAO EXISTE\n", str1);
      break;
    case 16:
      fprintf(arq, "ERRO 16: O ARQUIVO DE ENTRADA NÃO EXISTE\n");
      break;
    case 17:
      fprintf(arq, "ERRO 17: NAO FOI POSSIVEL VERIFICAR SE HA CAMINHO DA PAGINA %s PARA %s, POIS %s NAO EXISTE\n", str1, str2, str1);
      break;
    case 18:
      fprintf(arq, "ERRO 18: NAO FOI POSSIVEL INSERIR A PAGINA %s, POIS UMA PAGINA COM ESSE NOME JA EXISTE\n", str1);
      break;
    case 19:
      fprintf(arq, "ERRO 19: NAO FOI POSSIVEL INSERIR O EDITOR %s, POIS UM EDITOR COM ESSE NOME JA EXISTE\n", str1);
      break;
    default:
      fprintf(arq, "ERRO 00: FUNCAO %s INEXISTENTE\n", str1);
  }
  fclose(arq);
}
