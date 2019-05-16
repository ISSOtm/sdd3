
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

	puts("prefix quart");
	list_words_prefixed(&dictionary, "quarte");
	
    (void)argc;
    (void)argv;
    return 0;
}
