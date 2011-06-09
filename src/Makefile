# MAKEFILE - Trabalho 1 de Redes
# PROGRAMA:  Raw Network
# DESCRIÇÃO: Cliente e Servidor entre duas máquinas
# utilizando RAW_SOCKET.

# Compilador, Opções de Compilação e Arquivos Fonte
CSOURCES=main.c
CFLAGS=-Wall
CC=gcc

# Objetos do trabalho
OBJECTS=$(CSOURCES:.c=.o)

# Executavel do projeto
EXEC=raw_network

# Regras de compilação
.PHONY: all
# %.o:
all: $(EXEC) $(OBJECTS)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Regras de limpeza
.PHONY: clean

clean:
	@rm -rf *.bak *.o *~* core* *.out *.gch $(EXEC)
