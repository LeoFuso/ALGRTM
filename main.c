#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[3];
    struct Node *parent;
};

struct Path {
    struct Node *node_a;
    struct Node *node_b;
    int distance;
};

struct Graph {
    int n_path, n_node;
    struct Path **path;
    struct Node **node;
};


struct Graph *create_graph(int n_path, int n_node);
struct Path *create_path(struct Node *node_a, struct Node *node_b, int distance);
struct Node *create_node(char *name);

struct Graph ** mount_initial_graph_1(void);
struct Graph ** mount_initial_graph_2(void);

void _test(struct Graph **(*mount)(void));
int compare(const void *s1, const void *s2);
void print_paths(struct Graph *graph);
void print_nodes(struct Graph *graph);


void kruskal(struct Graph *o_graph, struct Graph *k_graph);
int check_graph(struct Graph *k_graph, int path_size);
struct Node * _find(struct Node *node);
void _union(struct Path **path, struct Node *n_from, struct Node *n_to);

int main(void) {


    printf("\n\nTEST 1: \n");
    _test(&mount_initial_graph_1);
    printf("\n\nTEST 2: \n");
    _test(&mount_initial_graph_2);

    return 0;
}

void _test(struct Graph **(*mount)(void)){

    struct Graph ** graph_to_test = mount();
    struct Graph * o_graph = graph_to_test[0];
    struct Graph * k_graph = graph_to_test[1];


    printf("\n\nORIGINAL GRAPH: \n");
    printf("%d NODES \n", o_graph->n_node);
    printf("%d PATHS \n", o_graph->n_path);

    printf("\n\nORIGINAL PATH:\n");
    print_paths(o_graph);

    qsort(o_graph->path, o_graph->n_path, sizeof(struct Path *), compare);

    printf("\n\nSORTED PATH:\n");
    print_paths(o_graph);

    kruskal(o_graph,k_graph);
    printf("\n\nKRUSKAL GRAPH: \n");
    printf("%d NODES \n", k_graph->n_node);
    printf("%d PATHS \n", k_graph->n_path);
    printf("\n\nKRUSKAL PATH: \n");
    print_paths(k_graph);

    free(graph_to_test);
}


void kruskal(struct Graph *o_graph, struct Graph *k_graph){


    int *path_to_ignore = malloc(o_graph->n_path * sizeof(int *));
    int has_cycle = 999999;

    while(has_cycle != 0){
        has_cycle = _do_loop_kruskal(o_graph,k_graph, path_to_ignore);
    }

}

int _do_loop_kruskal(struct Graph *o_graph, struct Graph *k_graph, int *path_to_ignore){

    int i = 0;
    int j = 0;

    while (i < o_graph->n_path){

        struct Node *node_a = o_graph->path[i]->node_a;
        struct Node *node_b = o_graph->path[i]->node_b;
        int distance = o_graph->path[i]->distance;

        if(i != path_to_ignore[j]){
            k_graph->path[i] = create_path(node_a,node_b,distance);
        }else if(i == 0) {
            k_graph->path[i] = create_path(node_a, node_b, distance);
        }else{
            j++;
        }
        i++;
    }

    int has_cycle = check_graph(k_graph,o_graph->n_path);

    if(has_cycle != 0){
        path_to_ignore[j++] = has_cycle;
        return 1;
    }
}

int check_graph(struct Graph *k_graph, int path_size){

    for (int i = 0; i < path_size; ++i) {
        struct Node *x = _find(k_graph->path[i]->node_a);
        struct Node *y = _find(k_graph->path[i]->node_b);

        if(strcmp(x->name,y->name) == 0)
            return i;

        _union(k_graph->path,x,y);
    }
    return 0;
}

struct Node * _find(struct Node *node){
    if(node->parent == NULL)
        return node;
    return _find(node->parent);
}

void _union(struct Path **path, struct Node *n_from, struct Node *n_to){

    struct Node *x_set = _find(n_from);
    struct Node *y_set = _find(n_to);
    x_set->parent = y_set;
}

struct Graph *create_graph(int n_path, int n_node) {
    struct Graph *graph =
            (struct Graph *) malloc(sizeof(struct Graph));
    graph->n_path = n_path;
    graph->n_node = n_node;
    graph->path = (struct Path *)malloc(n_path * sizeof(struct Path));
    graph->node = (struct Node *)malloc(n_node * sizeof(struct Node));
}

struct Path *create_path(struct Node *node_a, struct Node *node_b, int distance) {

    struct Path *new_path = NULL;

    new_path = malloc(sizeof(struct Path));
    new_path->node_a = node_a;
    new_path->node_b = node_b;
    new_path->distance = distance;

    return new_path;
}

struct Node *create_node(char *name){

    struct Node *new_node = NULL;
    new_node = malloc(sizeof(struct Node));
    strcpy(new_node->name, name);
    new_node->parent = NULL;
    return new_node;
}

struct Graph ** mount_initial_graph_1(void) {

    int nodes_qtd = 4;
    int original_path_size = 5;
    int kruskal_path_size = nodes_qtd - 1;

    struct Graph *k_graph = create_graph(kruskal_path_size,nodes_qtd);
    struct Graph *graph = create_graph(original_path_size,nodes_qtd);

    struct Node *node_A = create_node("A");
    struct Node *node_B = create_node("B");
    struct Node *node_C = create_node("C");
    struct Node *node_D = create_node("D");

    graph->node[0] = node_A;
    graph->node[1] = node_B;
    graph->node[2] = node_C;
    graph->node[3] = node_D;

    //A --> B = 25
    graph->path[0] = create_path(node_A,node_B,25);

    //B --> C = 50
    graph->path[1] = create_path(node_B,node_C,50);

    //C --> D = 10
    graph->path[2] = create_path(node_C,node_D,10);

    //A --> D = 25
    graph->path[3] = create_path(node_A,node_D,25);

    //A --> C = 40
    graph->path[4] = create_path(node_A,node_C,40);

    struct Graph ** graphs = NULL;
    graphs = malloc(2 * sizeof(struct Graph *));

    graphs[0] = graph; // original_graph
    graphs[1] = k_graph; // kruskal_graph

    return graphs;
}

struct Graph ** mount_initial_graph_2(void) {

    int nodes_qtd = 5;
    int original_path_size = 10;
    int kruskal_path_size = nodes_qtd - 1;

    struct Graph *k_graph = create_graph(kruskal_path_size,nodes_qtd);
    struct Graph *graph = create_graph(original_path_size,nodes_qtd);

    struct Node *node_v1 = create_node("v1");
    struct Node *node_v2 = create_node("v2");
    struct Node *node_v3 = create_node("v3");
    struct Node *node_v4 = create_node("v4");
    struct Node *node_v5 = create_node("v5");

    graph->node[0] = node_v1;
    graph->node[1] = node_v2;
    graph->node[2] = node_v3;
    graph->node[3] = node_v4;
    graph->node[4] = node_v5;


    //v1 --> v2 = 9
    graph->path[0] = create_path(node_v1,node_v2,9);

    //v2 --> v3 = 8
    graph->path[1] = create_path(node_v2,node_v3,8);

    //v3 --> v4 = 10
    graph->path[2] = create_path(node_v3,node_v4,10);

    //v4 --> v5 = 7
    graph->path[3] = create_path(node_v4,node_v5,7);

    //v1 --> v3 = 6
    graph->path[4] = create_path(node_v1,node_v3,6);

    //v1 --> v4 = 15
    graph->path[5] = create_path(node_v1,node_v4,15);

    //v1 --> v5 = 14
    graph->path[6] = create_path(node_v1,node_v5,14);

    //v2 --> v4 = 17
    graph->path[7] = create_path(node_v2,node_v4,17);

    //v2 --> v5 = 12
    graph->path[8] = create_path(node_v2,node_v5,12);

    //v3 --> v5 = 9
    graph->path[9] = create_path(node_v3,node_v5,9);

    struct Graph ** graphs = NULL;
    graphs = malloc(2 * sizeof(struct Graph *));

    graphs[0] = graph; // original_graph
    graphs[1] = k_graph; // kruskal_graph

    return graphs;
}

void print_nodes(struct Graph *graph) {

}

void print_paths(struct Graph *graph) {
    int i;
    for (i = 0; i < graph->n_path; ++i) {
        struct Path *p = graph->path[i];
        printf("\n%s --> %s = %d",p->node_a->name,p->node_b->name, p->distance);
    }
    printf("\n\n");
}

int compare(const void *s1, const void *s2) {

    struct Path *p1 = *(struct Path **) s1;
    struct Path *p2 = *(struct Path **) s2;

    if (p1->distance != p2->distance)
        return p1->distance - p2->distance;
    else
        return strcmp(p1->node_a->name,p2->node_a->name) <
               strcmp(p1->node_b->name,p2->node_b->name);
}

void setup(struct Graph *o_graph, struct Graph *k_graph) {

}