
#include <stdlib.h>
#include <stdio.h>
#include "dict.h"


int main(int argc, char* argv[]) {
    Tree_t * dictionary = NULL;
    char const * const words[] = {
        "quatre", "bien", "quarte", "quartiles", "bien", "bielle", "quartile", "quarte", "quartet", "quantifiable"
    };
    insert_words(&dictionary, words, sizeof(words) / sizeof(char *));

    list_words(dictionary);

	puts("Préfixe 'quarte': ");
	list_words_prefixed(&dictionary, "quarte");
	puts("Préfixe vide:");
	list_words_prefixed(&dictionary, "");
    puts("Préfixe 'sdd' :");
    list_words_prefixed(&dictionary, "sdd");
	
    (void)argc;
    (void)argv;
    return 0;
}
