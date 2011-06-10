#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *dir;
    int tam;

    if (argc < 2)
    {
        printf("Número de parâmetros inválidos.\n");
        printf("Uso: ls [-la] [DIRETÓRIO]\n");
        exit(EXIT_FAILURE);
    }

    tam = strlen("ls -la ") + strlen(argv[1]) + 1;
    dir = (char *) malloc(tam * sizeof(char));
    snprintf(dir, tam, "ls -la %s", argv[1]);
    dir[tam] = '\0';

    // Chamada de sistema que vai executar o "ls -la diretório"
    system(dir);

    free(dir);

    return 0;
}
