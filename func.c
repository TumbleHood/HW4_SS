#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pnode find(pnode head, int node_num){
    pnode current = head;
    while (current != NULL && current->node_num != node_num)
        current = current->next;
    return current;
}

void build_graph_cmd(pnode *head, char *args){
    *head = NULL;
    int num_of_nodes = (int)(args[0]-'0');
    for (int i = 0; i < num_of_nodes; i++){
        pnode new_node = (pnode)malloc(sizeof(node));
        new_node->node_num = i;
        new_node->edges = NULL;
        new_node->next = *head;
        *head = new_node;
    }
    int i = 1;
    while (args[i++] == 'n'){
        pnode src = find(*head, (int)(args[i++]-'0'));
        while (args[i] != 'n' && args[i] != '\0'){
            pedge new_edge = (pedge)malloc(sizeof(edge));
            new_edge->endpoint = find(*head, (int)(args[i++]-'0'));
            new_edge->weight = (int)(args[i++]-'0');
            new_edge->next = src->edges;
            src->edges = new_edge;
        }
    }
}

void insert_node_cmd(pnode *head, char *args){
    pnode new_node = find(*head, (int)(args[0]-'0'));
    if (new_node == NULL){
        new_node = (pnode)malloc(sizeof(node));
        new_node->node_num = (int)(args[0]-'0');
        new_node->next = *head;
        *head = new_node;
    }

    int i = 1;
    while (args[i] != '\0'){
        pedge new_edge = (pedge)malloc(sizeof(edge));
        new_edge->endpoint = find(*head, (int)(args[i++]-'0'));
        new_edge->weight = (int)(args[i++]-'0');
        new_edge->next = new_node->edges;
        new_node->edges = new_edge;
    }
}

pnode exchange(pnode *obj, pnode newval){
    pnode temp = *obj;
    *obj = newval;
    return temp;
}

pedge e_exchange(pedge *obj, pedge newval){
    pedge temp = *obj;
    *obj = newval;
    return temp;
}

void delete_node_cmd(pnode *head, char *args){
    int del = (int)(args[0]-'0');
    
    for (pnode current = *head; current != NULL; current = current->next){
        pedge *e_head = &current->edges;
        if (*e_head != NULL){
            if ((*e_head)->endpoint->node_num == del)
                free(e_exchange(e_head, (*e_head)->next));
            else for (pedge e_current = *e_head; e_current != NULL; e_current = e_current->next){
                if (e_current->next != NULL && e_current->next->endpoint->node_num == del)
                    free(e_exchange(&e_current->next, e_current->next->next));
            }
        }
    }
    if ((*head)->node_num == del)
        free(exchange(head, (*head)->next));
    else for (pnode current = *head; current != NULL; current = current->next){
        if (current->next != NULL && current->next->node_num == del)
            free(exchange(&current->next, current->next->next));
    }
}

void print_graph_cmd(pnode head){
    pnode current = head;
    while (current != NULL){
        printf("node: %d, edges: ", current->node_num);
        pedge e_head = current->edges;
        while (e_head != NULL){
            printf("%d->%d (%d), ", current->node_num, e_head->endpoint->node_num, e_head->weight);
            e_head = e_head->next;
        }
        printf("\n");
        current = current->next;
    }
}

void delete_graph_cmd(pnode *head){
    pnode current = *head;
    for (pnode current = *head; current != NULL; current = current->next){
        pedge e_current = current->edges;
        while (e_current != NULL && e_current->next != NULL){
            pedge e_temp = e_current;
            e_current = e_current->next;
            free(e_temp);
        }
        free(e_current);
    }
    current = *head;
    while (current != NULL && current->next != NULL){
        pnode temp = current;
        current = current->next;
        free(temp);
    }
    free(current);

    *head = NULL;
}

int is_empty(int q[], int len){
    for (int i = 0; i < len; i++){
        if (q[i] == 1){
            return 0;
        }
    }
    return 1;
}

int first_element(int q[], int len){
    for (int i = 0; i < len; i++){
        if (q[i] == 1){
            return i;
        }
    }
    return 0;
}

int short_path_cmd(pnode head, char *args){ // dijkstra's algorithm.
    int src = (int)(args[0]-'0'), dest = (int)(args[1]-'0');

    int max = 0;
    pnode current = head;
    while (current != NULL){
        if (current->node_num > max){
            max = current->node_num;
        }
        current = current->next;
    }

    int dist[max+1];
    int q[max+1];
    current = head;
    while (current != NULL){
        q[current->node_num] = 1;
        current = current->next;
    }

    for (int i = 0; i < max+1; i++){
        dist[i] = 10;// since you can enter numbers between 0 to 9, 10 would be larger than anything.
    }
    dist[src] = 0;

    while (!is_empty(q, max+1)){
        int min = 10, u = first_element(q, max+1);
        for (int i = 0; i < max+1; i++){
            if (q[i] == 1 && dist[i] < min){
                min = dist[i];
                u = i;
            }
        }
        q[u] = 0;

        pedge u_edge = find(head, u)->edges;
        while (u_edge != NULL){
            if (q[u_edge->endpoint->node_num] == 1){// node is still in q
                int alt = dist[u] + u_edge->weight;
                if (alt < dist[u_edge->endpoint->node_num]){
                    dist[u_edge->endpoint->node_num] = alt;
                }
            }
            u_edge = u_edge->next;
        }
    }
    if (dist[dest] == 10)
        return -1;
    return dist[dest];
}

void swap(char *x, char *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void calc_tsp(pnode head, char *a, int len_a, int *min){
    int dist = 0;
    // printf("current a: %s\n", a);
    for (int i = 0; i < len_a-1; i++){
        char duo[2];
        duo[0] = a[i];
        duo[1] = a[i+1];
        int temp_dist = short_path_cmd(head, duo);
        if (temp_dist == -1){
            dist = *min;
            break;
        }
        // printf("%c->%c: %d | ", a[i], a[i+1], temp_dist);
        dist += temp_dist;
    }
    if (dist != -1 && dist < *min)
        *min = dist;
    // printf("\ncurrent min: %d\n", *min);
}

void permute(pnode head, int *min, char *a, int len_a, int l, int r) 
{ 
    if (l == r){
        calc_tsp(head, a, len_a, min);
    }
    else
    { 
        for (int i = l; i <= r; i++) 
        { 
            swap((a+l), (a+i)); 
            permute(head, min, a, len_a, l+1, r);
            swap((a+l), (a+i));
        } 
    } 
}

void tsp_cmd(pnode head, char *args){
    int min = 1000;
    int len_a = 0;
    while (args[len_a] != '\0'){
        len_a++;
    }
    permute(head, &min, args, len_a, 0, len_a-1);
    if (min == 1000)
        min = -1;
    printf("TSP shortest path: %d\n", min);
}