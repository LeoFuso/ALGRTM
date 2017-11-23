#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Leonardo Fuso  21/11/2017

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

/* get_struct functions */
struct Graph *create_graph(int n_path, int n_node);
struct Path *create_path(struct Node *node_a, struct Node *node_b, int distance);
struct Node *create_node(char *name);

/* aux functions */
int compare(const void *s1, const void *s2);
void print_paths(struct Graph *graph);
void print_nodes(struct Graph *graph);
int get_path_size(struct Graph *graph);

/* structural functions */
int remove_cycle_element(struct Graph *graph, int index);


/* main test */
void _test(struct Graph **(*mount)(void));
struct Graph *mount_initial_graph_1(void);
struct Graph *mount_initial_graph_2(void);
struct Graph *mount_initial_graph_3(void);

/* logic functions */
void kruskal(struct Graph *graph);
struct Node *_find(struct Node *node);
void _union(struct Node *n_from, struct Node *n_to);


int main(void) {


    printf("\n\nTEST 1: \n");
    _test(&mount_initial_graph_1);
    printf("\n\nTEST 2: \n");
    _test(&mount_initial_graph_2);
    printf("\n\nTEST 3: \n");
    _test(&mount_initial_graph_3);

    return 0;
}


void _test(struct Graph **(*mount)(void)) {

    struct Graph *graph = mount();

    printf("\n\nORIGINAL GRAPH: \n");
    printf("%d NODES \n", graph->n_node);
    printf("%d PATHS \n", graph->n_path);

    printf("\n\nORIGINAL PATH:\n");
    print_paths(graph);

    printf("\n\nORIGINAL NODES:\n");
    print_nodes(graph);

    qsort(graph->path, graph->n_path, sizeof(struct Path *), compare);

    printf("\n\nSORTED PATH:\n");
    print_paths(graph);

    kruskal(graph);

    printf("\n\nKRUSKAL GRAPH: \n");
    printf("%d NODES \n", graph->n_node);
    printf("%d PATHS \n", graph->n_path);

    printf("\n\nSHORTEST PATH: \n");
    print_paths(graph);
    printf("PATH DISTANCE SIZE: %d\n", get_path_size(graph));

    printf("\n\nKRUSKAL TREE: \n");
    print_nodes(graph);


}

void kruskal(struct Graph *graph) {

    for (int i = 0; i < graph->n_path; ++i) {

        struct Node *x_parent = _find(graph->path[i]->node_a);
        struct Node *y_parent = _find(graph->path[i]->node_b);

        if (strcmp(x_parent->name, y_parent->name) == 0)
            i = remove_cycle_element(graph, i);
        else
            _union(x_parent, y_parent);
    }
}

int remove_cycle_element(struct Graph *graph, int index) {

    for (int i = index; i < graph->n_path - 2; i++) graph->path[i] = graph->path[i + 1];

    struct Path **tmp = (struct Path **) realloc(graph->path, (graph->n_path - 1) * sizeof(struct Path *));

    /* No memory available */
    if (tmp == NULL && graph->n_path > 1)
        exit(EXIT_FAILURE);

    graph->n_path = graph->n_path - 1;
    graph->path = tmp;

    return --index;
}

struct Node *_find(struct Node *node) {
    if (node->parent == NULL)
        return node;
    return _find(node->parent);
}

void _union(struct Node *n_from, struct Node *n_to) {

    struct Node *x_set = _find(n_from);
    struct Node *y_set = _find(n_to);

    x_set->parent = y_set;
}

struct Graph *create_graph(int n_path, int n_node) {

    struct Graph *graph =
            (struct Graph *) malloc(sizeof(struct Graph));

    graph->n_path = n_path;
    graph->n_node = n_node;
    graph->path = (struct Path **) malloc(n_path * sizeof(struct Path));
    graph->node = (struct Node **) malloc(n_node * sizeof(struct Node));
}

struct Path *create_path(struct Node *node_a, struct Node *node_b, int distance) {

    struct Path *new_path = NULL;

    new_path = (struct Path *) malloc(sizeof(struct Path));
    new_path->node_a = node_a;
    new_path->node_b = node_b;
    new_path->distance = distance;

    return new_path;
}

struct Node *create_node(char *name) {

    struct Node *new_node = NULL;
    new_node = (struct Node *) malloc(sizeof(struct Node));
    strcpy(new_node->name, name);
    new_node->parent = NULL;
    return new_node;
}

struct Graph *mount_initial_graph_1(void) {

    int nodes_qtd = 4;
    int path_size = 5;

    struct Graph *graph = create_graph(path_size, nodes_qtd);

    struct Node *node_A = create_node("A");
    struct Node *node_B = create_node("B");
    struct Node *node_C = create_node("C");
    struct Node *node_D = create_node("D");

    graph->node[0] = node_A;
    graph->node[1] = node_B;
    graph->node[2] = node_C;
    graph->node[3] = node_D;

    //A --> B = 25
    graph->path[0] = create_path(node_A, node_B, 25);

    //B --> C = 50
    graph->path[1] = create_path(node_B, node_C, 50);

    //C --> D = 10
    graph->path[2] = create_path(node_C, node_D, 10);

    //A --> D = 25
    graph->path[3] = create_path(node_A, node_D, 25);

    //A --> C = 40
    graph->path[4] = create_path(node_A, node_C, 40);

    return graph;
}

struct Graph *mount_initial_graph_2(void) {

    int nodes_qtd = 5;
    int original_path_size = 10;

    struct Graph *graph = create_graph(original_path_size, nodes_qtd);

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
    graph->path[0] = create_path(node_v1, node_v2, 9);

    //v2 --> v3 = 8
    graph->path[1] = create_path(node_v2, node_v3, 8);

    //v3 --> v4 = 10
    graph->path[2] = create_path(node_v3, node_v4, 10);

    //v4 --> v5 = 7
    graph->path[3] = create_path(node_v4, node_v5, 7);

    //v1 --> v3 = 6
    graph->path[4] = create_path(node_v1, node_v3, 6);

    //v1 --> v4 = 15
    graph->path[5] = create_path(node_v1, node_v4, 15);

    //v1 --> v5 = 14
    graph->path[6] = create_path(node_v1, node_v5, 14);

    //v2 --> v4 = 17
    graph->path[7] = create_path(node_v2, node_v4, 17);

    //v2 --> v5 = 12
    graph->path[8] = create_path(node_v2, node_v5, 12);

    //v3 --> v5 = 9
    graph->path[9] = create_path(node_v3, node_v5, 9);

    return graph;
}

struct Graph *mount_initial_graph_3(void) {

    int nodes_qtd = 6;
    int path_size = 15;

    struct Graph *graph = create_graph(path_size, nodes_qtd);

    struct Node *node_L  = create_node("L ");
    struct Node *node_T  = create_node("T ");
    struct Node *node_MC = create_node("MC");
    struct Node *node_Pe = create_node("Pe");
    struct Node *node_NY = create_node("NY");
    struct Node *node_Pa = create_node("Pa");


    graph->node[0] = node_L;
    graph->node[1] = node_T;
    graph->node[2] = node_MC;
    graph->node[3] = node_Pe;
    graph->node[4] = node_NY;
    graph->node[5] = node_Pa;

    graph->path[0] = create_path(node_L, node_MC, 56);

    graph->path[1] = create_path(node_L, node_NY, 35);

    graph->path[2] = create_path(node_L, node_Pa, 2);

    graph->path[3] = create_path(node_L, node_Pe, 51);

    graph->path[4] = create_path(node_L, node_T, 60);

    graph->path[5] = create_path(node_MC, node_T, 70);

    graph->path[6] = create_path(node_MC, node_NY, 21);

    graph->path[7] = create_path(node_MC, node_Pa, 57);

    graph->path[8] = create_path(node_MC, node_Pe, 78);

    graph->path[9] = create_path(node_NY, node_T, 68);

    graph->path[10] = create_path(node_NY, node_Pe, 68);

    graph->path[11] = create_path(node_NY, node_Pa, 36);

    graph->path[12] = create_path(node_Pa, node_Pe, 51);

    graph->path[13] = create_path(node_Pa, node_T, 61);

    graph->path[14] = create_path(node_Pe, node_T, 13);

    return graph;
}

void print_nodes(struct Graph *graph) {
    int i;
    for (i = 0; i < graph->n_node; ++i) {
        struct Node *n = graph->node[i];
        if (n->parent == NULL)
            printf("\n%s --> NULL", n->name);
        else
            printf("\n%s --> %s", n->name, n->parent->name);
    }
    printf("\n\n");
}

void print_paths(struct Graph *graph) {
    int i;
    for (i = 0; i < graph->n_path; ++i) {
        struct Path *p = graph->path[i];
        printf("\n%s --> %s = %d", p->node_a->name, p->node_b->name, p->distance);
    }
    printf("\n\n");
}

int get_path_size(struct Graph *graph) {
    int sum = 0;
    int i;
    for (i = 0; i < graph->n_path; ++i) {
        sum += graph->path[i]->distance;
    }
    return sum;
}

int compare(const void *s1, const void *s2) {

    struct Path *p1 = *(struct Path **) s1;
    struct Path *p2 = *(struct Path **) s2;

    if (p1->distance != p2->distance)
        return p1->distance - p2->distance;
    else
        return strcmp(p1->node_a->name, p2->node_a->name) <
               strcmp(p1->node_b->name, p2->node_b->name);
}