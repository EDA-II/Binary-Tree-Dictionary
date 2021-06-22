#include "generate_candidates.h"
#include "utils.h"

void candidates_by_substitution(char *word, Tree *dictionary, Tree *suggestions) {
    char *candidate;
    int l = strlen(word);
    char c;
    int i;

    for (i = 0; i < l; i++) {
        candidate = (char*)malloc((l+1) * sizeof(char));
        strcpy(candidate,word);
        for (c = 'a'; c <= 'z'; c++) {
            candidate[i] = c;
            if (find_in_tree(dictionary, candidate) != NULL) {
                insert_into_tree(suggestions, candidate);
            }
        }
    }
}


void candidates_by_insertion(char *word, Tree *dictionary, Tree *suggestions) {
    int length = strlen(word);
    char *candidate;

    for (int i = 0; i <= length; i++) {
        for (char a = 'a'; a <= 'z'; a++){
            candidate = insert_letter_into_pos(word, &a, i);
            if (find_in_tree(dictionary, candidate) != NULL) {
                insert_into_tree(suggestions, candidate);
            }
        }
    }
}


void candidates_by_swapping(char *word, Tree *dictionary, Tree *suggestions) {
    int length = strlen(word);
    char *candidate;

    for (int i = 0; i < length - 1; i++) {
        candidate = swapping_letters(word, i);
        if (find_in_tree(dictionary, candidate) != NULL) {
            insert_into_tree(suggestions, candidate);
        }
    }

}

void candidates_by_deletion(char *word, Tree *dictionary, Tree *suggestions) {
    int length = strlen(word);
    char *candidate;

    for (int i = 0; i < length; i++) {
        strcpy(candidate, word);
        candidate = delete_letter_from_position(word, i);
        if (find_in_tree(dictionary, candidate) != NULL) {
            insert_into_tree(suggestions, candidate);
        }
    }
}

void generate_candidates(char *word, Tree *dictionary, Tree *substitutes) {
    init_tree(substitutes);
    candidates_by_substitution(word, dictionary, substitutes);
    candidates_by_insertion(word, dictionary, substitutes);
    candidates_by_swapping(word, dictionary, substitutes);
    candidates_by_deletion(word, dictionary, substitutes);
}