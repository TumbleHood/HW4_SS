#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph_cmd(pnode *head, char *args);
void insert_node_cmd(pnode *head, char *args);
void delete_node_cmd(pnode *head, char *args);
void print_graph_cmd(pnode head); //for self debug
void delete_graph_cmd(pnode* head);
int short_path_cmd(pnode head, char *args);
void tsp_cmd(pnode head, char *args);

#endif
