/***************************************************************
1º Trabalho Prático – Estrutura de Dados I – 2018/1 – Ciência da Computação
Grupo: Matheus Gomes Arante de Souza e Matheus Salomão
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagina.h"
#include "print.h"

#define QTD 12 //Quantidade de funções
#define TAM 50 //Tamanho máximo de uma string

int main(int argc, char const *argv[])
{
    FILE *auxlog = fopen("log.txt","w");
    fclose(auxlog);

    char funcoes[][TAM] = {"INSEREPAGINA","RETIRAPAGINA","INSEREEDITOR","RETIRAEDITOR",
                           "INSERECONTRIBUICAO","RETIRACONTRIBUICAO","INSERELINK","RETIRALINK",
                           "CAMINHO","IMPRIMEPAGINA","IMPRIMEWIKED","FIM"};

    FILE* arq;
    char funcao[TAM];

    arq = fopen(argv[1], "r");

    //Se o arquivo de entrada não existir, paramos a execução do programa.
    if(arq == NULL) {
        printf("O arquivo de entrada nao existe.\n");
        arqlog(16, "", "");
        exit(1);
    } else {
        ListaPag* wiked = inicializarListaPagina();
        ListaEditor* editores = inicializarListaEditor();

        int i;
        char p1[TAM], p2[TAM], p3[TAM]; //Parâmetros das funções
        do {
            i = 0;

            fscanf(arq, "%s", funcao);
            //Percorremos a matriz funcoes até encontrar o índice correspondente
            //à função.
            while(strcmp(funcao, funcoes[i])!=0 && i<QTD) {
                i++;
            }

            switch(i) {
                case 0:
                    fscanf(arq, "%s %s\n", p1, p2);
                    inserePagina(wiked, p1, p2);
                    break;
                case 1:
                    fscanf(arq, "%s\n", p1);
                    retiraPagina(wiked, p1);
                    break;
                case 2:
                    fscanf(arq, "%s\n", p1);
                    insereEditor(editores, p1);
                    break;
                case 3:
                    fscanf(arq, "%s\n", p1);
                    retiraEditorListaPag(wiked, editores, p1);
                    break;
                case 4:
                    fscanf(arq, "%s %s %s\n", p1, p2, p3);
                    insereContPag(wiked, p1, p2, p3, editores);
                    break;
                case 5:
                    fscanf(arq, "%s %s %s\n", p1, p2, p3);
                    retiraContPag(wiked, p1, p2, p3);
                    break;
                case 6:
                    fscanf(arq, "%s %s\n", p1, p2);
                    insereLinkPag(wiked, p1, p2);
                    break;
                case 7:
                    fscanf(arq, "%s %s\n", p1, p2);
                    retiraLinkPag(wiked, p1, p2);
                    break;
                case 8:
                    fscanf(arq, "%s %s\n", p1, p2);
                    caminho(wiked, p1, p2);
                    break;
                case 9:
                    fscanf(arq, "%s\n", p1);
                    imprimePagina(wiked, p1);
                    break;
                case 10:
                    imprimewiked(wiked);
                    break;
                case 11:
                    fim(wiked, editores);
                    break;
                default:
                    //Quando a função chamada no arquivo de entrada não existe,
                    //utilizamos esse fgets para pegar os parâmetros que haviam
                    //sido passados para ela, "ignorá-los", e continuar a 
                    //execução normalmente.
                    //fgets(p1, TAM, arq);
                    //Após isso, escrevemos uma mensagem no arq. log informando
                    //que a função chamada não existe.
                    arqlog(0, funcao, ""); 
            }
        } while(!feof(arq) && strcmp(funcao, "FIM") != 0);
    }
    fclose(arq);

    return 0;
}
