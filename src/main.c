#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt, option_index = 0;

    static struct option long_options[] = {
        {"client", 0, 0, 'c'},
        {"server", 0, 0, 's'},
        {0, 0, 0, 0}
    };

    if ((opt = getopt_long(argc, argv, "cs", long_options, &option_index)) != -1) {
        switch (opt) {
           case 'c':
               fprintf(stdout, "Chama funcao cliente.\n");
               break;
           case 's':
               fprintf(stdout, "Chama funcao server.\n");
               break;
           default: /* '?' */
               fprintf(stderr, "Usage: %s [-c|--client] or [-s|--server]\n", argv[0]);
               exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
