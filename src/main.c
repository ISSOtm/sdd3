
#include <stdlib.h>
#include <stdio.h>
#include "dict.h"


int main(int argc, char* argv[]) {
    Tree_t * dictionary = NULL;
    char const * const words[] = {
        "quatre", "bien", "quarte", "quartiles", "bien", "bielle", "quartile", "quarte", "quartet", "quantifiable"
    };

    puts("Préfixe vide :");
    list_words_prefixed(&dictionary, "");
    puts("\nPréfixe 'quarte' :");
    list_words_prefixed(&dictionary, "quarte");

    puts("\nInsertion mots");
    insert_words(&dictionary, words, sizeof(words) / sizeof(char *));

    puts("\nTous les mots :");
    list_words(dictionary);

	puts("\nPréfixe 'quarte': ");
	list_words_prefixed(&dictionary, "quarte");
	puts("\nPréfixe vide:");
	list_words_prefixed(&dictionary, "");
    puts("\nPréfixe 'sdd' :");
    list_words_prefixed(&dictionary, "sdd");

    destroy_tree(dictionary);
	
    (void)argc;
    (void)argv;
    return 0;
}
