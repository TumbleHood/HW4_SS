#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A3n01122n10022n20011PB3001122B033B133B233PD2P

int get_args(char **args, char *input, int i){
    free(*args);
    *args = (char*)malloc(sizeof(char));
    int j = 0;
    while (input[i] != 'A' && input[i] != 'B' && input[i] != 'D' && input[i] != 'S' && input[i] != 'T' && input[i] != 'P' && input[i] !='\0'){
        *args = (char*)realloc(*args, (j+1)*sizeof(char));
        (*args)[j++] = input[i++];
    }
    (*args)[j] = '\0';
    return i;
}

int main(void)
{
    char *input = (char*)malloc(sizeof(char)), c = ' ';
    int len = 0;
    while (c != '\n'){
        c = getc(stdin);
        if (c != ' '){
            input = (char*)realloc(input, (len+1)*sizeof(char));
            input[len++] = c;
        }
    }
    input[--len] = '\0';
    pnode head = NULL;
    int i = 0;
    while (i < len){
        if (input[i] == 'A'){
            delete_graph_cmd(&head);
            char *args = NULL;
            i = get_args(&args, input, ++i);
            build_graph_cmd(&head, args);
            free(args);
        }
        else if (input[i] == 'B'){
            char *args = NULL;
            i = get_args(&args, input, ++i);
            insert_node_cmd(&head, args);
            free(args);
        }
        else if (input[i] == 'D'){
            char *args = NULL;
            i = get_args(&args, input, ++i);
            delete_node_cmd(&head, args);
            free(args);
        }
        else if (input[i] == 'S'){
            char *args = NULL;
            i = get_args(&args, input, ++i);
            printf("Dijsktra shortest path: %d\n", short_path_cmd(head, args));
            free(args);
        }
        else if (input[i] == 'T'){
            char *args = NULL;
            i = get_args(&args, input, ++i);
            tsp_cmd(head, args);
            free(args);
        }
        else if (input[i] == 'P'){
            print_graph_cmd(head);
            printf("\n");
            i++;
        }
        else
            i++;
    }

    return 0;
}