### Makefile ###

# Nome do compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -g

# Ligação com as bibliotecas
LDFLAGS = -lm

# wildcard é utilizado para listar os arquivo-fontes no diretório atual
FONTES = $(wildcard *.c)

# gera a lista de arquivos-objeto usando a lista de arquivos-fonte
OBJETOS = $(FONTES:.c=.o)

# Nome do arquivo executável
EXECUTAVEL = wiked

#all: wiked
all : $(EXECUTAVEL)

# wiked: contribuicoes.o editores.o links.o pagina.o log.o wiked.o
#	gcc -o wiked contribuicoes.o editores.o links.o pagina.o log.o print.o wiked.o
$(EXECUTAVEL) : $(OBJETOS)
	$(CC) -o $@ $^ $(LDFLAGS)

# wiked.o: wiked.c
#	gcc -c wiked.c
#
# contribuicoes.o: contribuicoes.c
#	gcc -c contribuicoes.c
#
# editores.o: editores.c
#	gcc -c editores.c
#
# links.o: links.c
#	gcc -c links.c
#
# pagina.o: pagina.c
#	gcc -c pagina.c
#
# log.o: log.c
#	gcc -c log.c
#
# print.o: print.c
#	gcc -c print.c
%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o

# rmproper: clean
#	rm -rf wiked
rmproper: clean
	rm -rf $(EXECUTAVEL)
