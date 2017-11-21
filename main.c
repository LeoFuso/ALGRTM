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
};


struct Graph *create_graph(int n_path, int n_node);
struct Path *create_path(struct Node *node_a, struct Node *node_b, int distance);
struct Node *create_node(char *name);

void mount_initial_graph(struct Graph *graph);
int compare(const void *s1, const void *s2);
void print_paths(struct Graph *graph);
void print_nodes(struct Graph *graph);

void setup(struct Graph *o_graph, struct Graph *k_graph);


int main(void) {

    int nodes_qtd = 4;
    int original_path_size = 5;
    int kruskal_path_size = nodes_qtd - 1;

    struct Graph *k_graph = create_graph(kruskal_path_size,nodes_qtd);

    struct Graph *o_graph = create_graph(original_path_size,nodes_qtd);
    mount_initial_graph(o_graph);

    printf("\n\nORIGINAL PATH:\n");
    print_paths(o_graph);

    qsort(o_graph->path, o_graph->n_path, sizeof(struct Path *), compare);

    printf("\n\nSORTED PATH:\n");
    print_paths(o_graph);

    return 0;
}

struct Graph *create_graph(int n_path, int n_node) {
    struct Graph *graph =
            (struct Graph *) malloc(sizeof(struct Graph));
    graph->n_path = n_path;
    graph->n_node = n_node;
    graph->path = (struct Path *)malloc(n_path * sizeof(struct Path));
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
    return new_node;

}

void mount_initial_graph(struct Graph *graph) {

    //A --> B = 25
    graph->path[0] = create_path(create_node("A"),create_node("B"),25);

    //B --> C = 50
    graph->path[1] = create_path(create_node("B"),create_node("C"),50);

    //C --> D = 10
    graph->path[2] = create_path(create_node("C"),create_node("D"),10);

    //A --> D = 25
    graph->path[3] = create_path(create_node("A"),create_node("D"),25);

    //A --> C = 40
    graph->path[4] = create_path(create_node("A"),create_node("C"),40);

}

void mount_initial_graph_2(struct Graph graph) {

    //v1 --> v2 = 9
    graph.path[0] = create_path(create_node("v1"),create_node("v2"),9);

    //v2 --> v3 = 8
    graph.path[1] = create_path(create_node("v2"),create_node("v3"),8);

    //V4 --> V3 = 10

    //V5 --> V4 = 7

    //V3 --> V1 = 6

    //V4 --> V1 = 15

    //V5 --> V1 = 14

    //V4 --> V2 = 17

    //V5 --> V2 = 12

    //V5 --> V3 = 9

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
    struct Path *p1 = s1;
    struct Path *p2 = s2;

    if (p1->distance != p2->distance)
        return p1->distance - p2->distance;
    else
        return strcmp(p1->node_a->name,p2->node_a->name) ||
               strcmp(p1->node_b->name,p2->node_b->name);
}

void setup(struct Graph *o_graph, struct Graph *k_graph) {

}