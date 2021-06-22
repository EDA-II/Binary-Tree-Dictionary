#include "utils.h"

/**
 * TODO: Convert upper case to lower case
 * Modifies the given string mapping all characters in [A-Z] to [a-z].
*/
void str_to_lowercase(char *s) {
    while (*s != '\0') {
        if (*s >= 65 && *s <= 90) *s += 32;
        s++;
    }
}

/**
 *  Function strsep is not standard in Windows, we implement our own
*/
char *mystrsep(char **str_ptr, char *delim) {
    if (*str_ptr == NULL) return NULL;
    char *start = *str_ptr;
    *str_ptr = strpbrk(start, delim);
    if (*str_ptr != NULL) {
        **str_ptr = '\0';
        *str_ptr = *str_ptr + 1;
    }
    return start;
}

/**
 * Reads one line from console
*/
bool scan_line(char *message, char *format, void *buffer) {
    printf("%s", message);
    fflush(stdout);
    char line[1000]; // this should be a sufficiently long buffer
    char *res = fgets(line, sizeof(line), stdin);
    if (res == NULL) return false; // reading from stdin failed
    line[strcspn(line, "\n")] = '\0'; // remove '\n'
    if (format == NULL || strcmp(format, "%s") == 0) strcpy(buffer, line);
    else sscanf(line, format, buffer); // we asume here that format is a single specifier (e.g. only %d)
    return true;
}

/**
 * Check file exists
 */
bool exists(char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void flush_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int read_int_option(const char *msg) {
    int option = INVALID_OPTION;
    printf("%s", msg);
    scanf("%d", &option);

    flush_input();

    return option;
}

/**
 * Pre: Parameter "position" must be an integer between zero and length of "word" plus one
 * Post: Returns a string with an inserted character.
 */

char *insert_letter_into_pos(char *word, const char *character, int position) {
    int new_length = strlen(word) + 1;
    char *tmp_word = malloc(new_length * sizeof(char));
    char *word_tmp = word;

    for(int i = 0; i < new_length; i++ ) {
        if (i == position) {
            tmp_word[i] = *character;
        } else {
            tmp_word[i] = *word_tmp;
            word_tmp++;
        }
    }

    return tmp_word;
}


/**
 * Pre: Parameter "position" must be length of "word" minus 2
 * Post: Function returns a string with two of its characters swapped (character i and i+1).
 */

char *swapping_letters(char *word, int position){
    char *return_word = malloc(strlen(word) * sizeof(char));
    strcpy(return_word, word);

    char tmp_char = return_word[position];
    return_word[position] = return_word[position + 1];
    return_word[position + 1] = tmp_char;

    return return_word;
}

/**
 * Pre: Parameter "position" must be a value between zero and "word" length minus 1.
 * Post: Function returns a string without the letter indicated by the position index.
 */
char *delete_letter_from_position(char* word, int position){
    int new_length = strlen(word) - 1;
    char *tmp_word = malloc(new_length * sizeof(char));
    char *word_tmp = word;
    for (int iter_index = 0, word_index = 0; iter_index <= new_length; iter_index++) {
        if (iter_index == position) {
            word_tmp++;
        } else {
            tmp_word[word_index] = *word_tmp;
            word_tmp++;
            word_index += 1;
        }
    }

    return tmp_word;
}

bool is_empty_word(char *word) {
    int length_word = strlen(word);

    for (int i = 0; i < length_word; i++) {
        if (word[i] != ' ') {
            return false;
        }
    }

    return true;
}