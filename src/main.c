
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
    
	puts("\nliste des cas de list_words_prefixed :");
	puts("\nPréfixe vide");
	list_words_prefixed(&dictionary, "");
	
	puts("\nPréfixe que");
	list_words_prefixed(&dictionary, "que");
	
	puts("\nPréfixe qua");
	list_words_prefixed(&dictionary, "qua");

	puts("\nPréfixe quarte");
	list_words_prefixed(&dictionary, "quarte");

	destroy_tree(dictionary);

    (void)argc;
    (void)argv;
    return 0;
}
