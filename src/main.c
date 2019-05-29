
#include <stdlib.h>
#include <stdio.h>
#include "dict.h"


int main(int argc, char* argv[]) {
    Tree_t * dictionary = NULL;
    int status;

    if(argc < 2) {
        fprintf(stderr, "Usage:\t%s path/to/dictionary.dict\n", argv[0]);
    } else {
        /* Status of those functions is not checked because without `goto` it's a pain */
        puts("Préfixe vide :");
        list_words_prefixed(dictionary, "");
        puts("\nPréfixe 'quarte' :");
        list_words_prefixed(dictionary, "quarte");

        puts("\nInsertion mots");
        status = insert_words_from_file(&dictionary, argv[1]);

        if(status != 0) {
            perror("Failed to read dict file");
        } else {
            puts("\nTous les mots :");
            list_words(dictionary);

        	puts("\nliste des cas de list_words_prefixed :");
        	puts("\nPréfixe vide");
        	list_words_prefixed(dictionary, "");

        	puts("\nPréfixe que");
        	list_words_prefixed(dictionary, "que");

        	puts("\nPréfixe qua");
        	list_words_prefixed(dictionary, "qua");

        	puts("\nPréfixe quarte");
        	list_words_prefixed(dictionary, "quarte");
        }

    	destroy_tree(dictionary);
    }

    return 0;
}
