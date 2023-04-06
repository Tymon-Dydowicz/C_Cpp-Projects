#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct getline_lines{
    char * getline_line;
    struct getline_lines * next_line;
};

struct getline_lines * getline_start = &(struct getline_lines){
    .getline_line = NULL,
    .next_line = NULL,
};

struct keys{
    char * key;
    char * value;
    struct keys * next_key;
};

struct section{
    char * section_name;
    struct section * next_section;
    struct keys * section_keys;
};

int digits_only(const char *s)
{
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }
    return 1;
}

void adding_lines(char *line){
    struct getline_lines *ptr, *temp;
    ptr = getline_start; 
    temp = (struct getline_lines*)malloc(sizeof(struct getline_lines));

    temp->getline_line = line;
    temp->next_line = NULL;

    while(ptr->next_line != NULL){
        ptr = ptr->next_line;
    }
    ptr->next_line = temp;
}

char * _getline(FILE* f_in) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(f_in);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    adding_lines(linep);
    return linep;
}

void freeing_lines(struct getline_lines * starting_line){
    struct getline_lines * curr = starting_line;
    struct getline_lines * temp = curr;
    while (curr != NULL){
        temp = temp->next_line;
        free(curr->getline_line);
        free(curr);
        curr = temp;
    }
}

void adding_keys(struct keys *start, char *wkey){
    struct keys *ptr, *temp;
    ptr = start;
    temp = (struct keys*)malloc(sizeof(struct keys));

    temp->key = strtok(wkey, " = ");
    temp->value = strtok(NULL, " = \n");
    temp->next_key = NULL;

    while(ptr->next_key != NULL){
        ptr = ptr->next_key;
    }
    ptr->next_key = temp;
}

void adding_section(struct section *start , char *sname){
    struct section *ptr, *temp;
    ptr = start;
    temp = (struct section*)malloc(sizeof(struct section));

    temp->section_name = sname;
    temp->next_section = NULL;

    while(ptr->next_section != NULL){
        ptr = ptr->next_section;
    }
    ptr->next_section = temp;
}

struct section * parsing(FILE* f_in){
    struct section * start = (struct section *)malloc(sizeof(struct section));
    char * line = _getline(f_in);
    start->section_name = line;
    start->next_section = NULL;
    struct section *curr_sec = start;

    while(!feof(f_in)){
        struct keys * start_key = (struct keys *)malloc(sizeof(struct keys));
        char *line = _getline(f_in);

        start_key->key = strtok(line, " = ");
        start_key->value = strtok(NULL, " = \n");
        start_key->next_key = NULL;
        
        curr_sec->section_keys = start_key;

        while(strcmp(line, "\n") != 0){
            line = _getline(f_in);
            adding_keys(start_key, line);
        }
        adding_section(start, _getline(f_in));
        curr_sec = curr_sec->next_section;
    }
    return start;
}

void freeing_keys(struct keys * start_key){
    struct keys * curr = start_key;
    struct keys * temp = curr;
    while (curr != NULL){
        temp = temp->next_key;
        free(curr);
        curr = temp;
    }
}

void freeing_sections(struct section * sekcje){
    struct section * curr = sekcje;
    struct section * temp = curr;
    while(curr != NULL){
        temp = temp->next_section;
        freeing_keys(curr->section_keys);
        free(curr);
        curr = temp;
    }
}

char * search2(struct section * start , char sekcja[], char klucz[]){
    struct section * curr_s = start;
    
    while (strcmp(sekcja, curr_s->section_name) != 0){
        if (curr_s->next_section == NULL){
            printf("Failed to find section %s\n\n", sekcja);
            return NULL;
        }
        curr_s = curr_s->next_section;
    }

    struct keys * curr_k = curr_s->section_keys;
    while (strcmp(klucz, curr_k->key) != 0){
        if (curr_k->next_key == NULL){
            printf("Failed to find key \"%s\" in section %s\n\n", klucz, sekcja);
            return NULL;
        }
        curr_k = curr_k->next_key;
    }
    return curr_k->value;
}

//STRUCTURELESS
char * search(FILE* f_in, char section[], char key[]){
    char * mem;
    while(!feof(f_in)){
        mem = _getline(f_in);

        if (strcmp(mem, section) == 0){

            while (strcmp(mem, "\n")){
                mem = strtok(_getline(f_in), " = ");
                if (strcmp(mem, key) == 0){
                    mem = strtok(NULL, " = \n");
                    return mem;
                }
            }
            printf("Failed to find key \"%s\" in section %s\n\n", key, section);
            return NULL;
        }
    }
    printf("Failed to find section %s\n\n", section);
    return NULL;
}

int main(int argc, char *argv[]){    

    char * decision = argv[2];
    if (strcmp(decision, "expression") == 0){
        const char * path = argv[1];
        char * direction1 = strtok(argv[3], " ");
        char * operation = strtok(NULL, " ");
        char * direction2 = strtok(NULL, " ");

        const char * middle1 = strtok(direction1, ".");
        char * key1 = strtok(NULL, "\n");

        const size_t length1 = strlen(middle1);
        char arr1[length1 + 4];
        arr1[0] = '\0';
        char * sekcja1 = strcat(strcat(strcat(arr1, "["), middle1), "]\n");

        const char * middle2 = strtok(direction2, ".");
        char * key2 = strtok(NULL, "\n");

        const size_t length2 = strlen(middle2);
        char arr2[length2 + 4];
        arr2[0] = '\0';
        char * sekcja2 = strcat(strcat(strcat(arr2, "["), middle2), "]\n");

        FILE* f_in;
        f_in = fopen(path, "r");
        struct section * sekcje = parsing(f_in);
        fclose(f_in);

        char * result1 = search2(sekcje, sekcja1, key1);
        char * result2 = search2(sekcje, sekcja2, key2);

        if (result1 == NULL || result2 == NULL){
            printf("couldn't find one of the inputed values\n");
            freeing_sections(sekcje);
            freeing_lines(getline_start);
            return 0;
        }
        if (digits_only(result1) && digits_only(result2)){
            switch(*operation){
                case '+':
                    printf("%ld\n", atol(result1) + atol(result2));
                    break;
                case '-':
                    printf("%ld\n", atol(result1) - atol(result2));
                    break;
                case '*':
                    printf("%ld\n", atol(result1) * atol(result2));
                    break;
                case '/':
                    if (atoi(result2) != 0){
                        printf("%ld\n", atol(result1) / atol(result2));
                        break;
                    }
                    printf("division by 0\n");
                    break;
                default:
                    printf("invalid expression");
            }
        }
        else{
            if (strcmp(operation, "+") == 0){
                const size_t length_result1 = strlen(result1);
                const size_t length_result2 = strlen(result2);

                char arr[length_result1 + length_result2];
                arr[0] = '\0';
                char * final_result = strcat(strcat(arr, result1), result2);
                printf("%s\n", final_result);
            }
            else{
                printf("invalid operation for strings\n");
            }
        }
        freeing_sections(sekcje);
        freeing_lines(getline_start);
        return 0;
    }

    const char * path = argv[1];

    const char * middle = strtok(argv[2], ".");
    char * key = strtok(NULL, "\n");

    const size_t length = strlen(middle);
    char arr[length + 4];
    arr[0] = '\0';
    char * sekcja = strcat(strcat(strcat(arr, "["), middle), "]\n");

    FILE* f_in;
    f_in = fopen(path, "r");
    struct section * sekcje = parsing(f_in);
    fclose(f_in);
    char * result = search2(sekcje, sekcja, key);
    if (result != NULL)
        printf("%s\n", result);

    freeing_sections(sekcje);
    freeing_lines(getline_start);
    return 0;
}