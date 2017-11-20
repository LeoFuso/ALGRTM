#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[2];
    int last_parent;
    int last_children;
    struct Node *parents;
    struct Node *children;
};

typedef struct {
    struct Node node_a;
    struct Node node_b;
    int distance;
} Path;

void print_paths(Path *p, int path_size);
void print_nodes(struct Node *n, int nodes_qtd);
int compare(const void *s1, const void *s2);
void setup(struct Node *original_nodes, struct Node *kruskal_nodes, int nodes_qtd);


void kruskal(Path *original_path, int original_path_size, Path *kruskal_path, int kruskal_path_size,
             struct Node *original_nodes, struct Node *kruskal_nodes, int nodes_qtd);

int check_parent(struct Node node_1, struct Node node_2, struct Node *kruskal_nodes);
int check_children(struct Node node_1, struct Node node_2, struct Node *kruskal_nodes);

int main(void) {

    int nodes_qtd = 4;
    int original_path_size = 5;
    int kruskal_path_size = nodes_qtd - 1;

    Path *original_path = malloc(original_path_size * sizeof(Path));
    Path *kruskal_path = malloc(kruskal_path_size * sizeof(Path));

    struct Node *original_nodes = malloc(nodes_qtd * sizeof(struct Node));
    struct Node *kruskal_nodes = malloc(nodes_qtd * sizeof(struct Node));


    mount_paths_nodes(original_path, original_nodes, nodes_qtd);


    printf("\n\nORIGINAL NODES:\n");
    print_nodes(original_nodes, nodes_qtd);

    printf("\n\nORIGINAL PATH:\n");
    print_paths(original_path, original_path_size);


    qsort(original_path, original_path_size, sizeof(Path), compare);

    printf("\n\nSORTED PATH:\n");

    print_paths(original_path, original_path_size);

    setup(original_nodes,kruskal_nodes, nodes_qtd);

    kruskal(original_path, original_path_size, kruskal_path, kruskal_path_size, original_nodes, kruskal_nodes,
            nodes_qtd);

    printf("\n\nKRUSKAL NODES:\n");
    print_nodes(kruskal_nodes, nodes_qtd);

    printf("\n\nKRUSKAL PATH:\n");
    print_paths(kruskal_path, kruskal_path_size);

    return 0;
}


void kruskal(Path *original_path, int original_path_size, Path *kruskal_path, int kruskal_path_size,
             struct Node *original_nodes, struct Node *kruskal_nodes, int nodes_qtd) {
    int i;
    int j;
    Path i_path;
    struct Node j_node;
    int from_node;
    int to_node;

    int from_is_set = 0;
    int to_is_set = 0;

    int kruskal_path_control = 0;

    for (i = 0; i < original_path_size; ++i) {

        printf("\n\nITERATION %d:", i+1);
        print_nodes(kruskal_nodes, nodes_qtd);

        i_path = original_path[i];

        for (j = 0; j < nodes_qtd; ++j) {

            j_node = kruskal_nodes[j];

            if (strcmp(j_node.name, i_path.node_a.name) == 0) {
                from_node = j;
                from_is_set = 1;
            }

            if (strcmp(j_node.name, i_path.node_b.name) == 0) {
                to_node = j;
                to_is_set = 1;
            }
            if(from_is_set == 1 && to_is_set == 1){
                j = nodes_qtd;
                from_is_set = to_is_set = 0;
            }
        }

        j = 0;

        struct Node s_from_node = kruskal_nodes[from_node];
        struct Node s_to_node = kruskal_nodes[to_node];

        if (check_parent(s_from_node,s_to_node, kruskal_nodes) == 0 &&
                check_children(s_from_node,s_to_node, kruskal_nodes) == 0) {

                kruskal_path[kruskal_path_control++] = i_path;
                kruskal_nodes[from_node].parents[kruskal_nodes[from_node].last_parent++] = kruskal_nodes[to_node];
                kruskal_nodes[to_node].children[kruskal_nodes[to_node].last_children++] = kruskal_nodes[from_node];

        }

        if(kruskal_path_control > kruskal_path_size)
            i = original_path_size;

    }
}

int check_parent(struct Node node_1, struct Node node_2, struct Node *kruskal_nodes) {
    int i;
    int j;

    if(node_1.last_parent == 0 && node_2.last_parent == 0)
        return 0;

    if(node_1.last_parent == 0){
        for (j = 0; j < node_2.last_parent ; ++j) {
            if(strcmp(node_1.name, node_2.parents[j].name) == 0){
                return 1;
            }else{
                check_parent(node_1, node_2.parents[j], kruskal_nodes);
            }
        }
    }

    if(node_2.last_parent == 0){
        for (j = 0; j < node_1.last_parent ; ++j) {
            if(strcmp(node_1.parents[j].name, node_2.name) == 0){
                return 1;
            }else{
                check_parent(node_2, node_1.parents[j], kruskal_nodes);
            }
        }
    }

    for (i = 0; i < node_1.last_parent ; ++i) {
        for (j = 0; j < node_2.last_parent ; ++j) {
            if(strcmp(node_1.parents[i].name, node_2.parents[j].name) == 0){
                return 1;
            }else{
                check_parent(node_1.parents[i], node_2.parents[j], kruskal_nodes);
            }
        }
    }
    return 0;
}

int check_children(struct Node node_1, struct Node node_2, struct Node *kruskal_nodes) {
    int i;
    int j;

    if(node_1.last_children == 0 && node_2.last_children == 0)
        return 0;

    if(node_1.last_children == 0){
        for (j = 0; j < node_2.last_children ; ++j) {
            if(strcmp(node_1.name, node_2.children[j].name) == 0){
                return 1;
            }else{
                check_parent(node_1, node_2.children[j], kruskal_nodes);
            }
        }
    }

    if(node_2.last_children == 0){
        for (j = 0; j < node_1.last_children ; ++j) {
            if(strcmp(node_1.children[j].name, node_2.name) == 0){
                return 1;
            }else{
                check_parent(node_2, node_1.children[j], kruskal_nodes);
            }
        }
    }

    for (i = 0; i < node_1.last_children ; ++i) {
        for (j = 0; j < node_2.last_children ; ++j) {
            if(strcmp(node_1.children[i].name, node_2.children[j].name) == 0){
                return 1;
            }else{
                check_parent(node_1.children[i], node_2.children[j], kruskal_nodes);
            }
        }
    }
    return 0;
}

void mount_paths_nodes(Path *p, struct Node *n, int nodes_qtd) {

    strcpy(n[0].name, "A");
    n[0].parents = malloc((nodes_qtd - 1) * sizeof(struct Node));
    n[0].children = malloc((nodes_qtd - 1) * sizeof(struct Node));

    strcpy(n[1].name, "B");
    n[1].parents = malloc((nodes_qtd - 1) * sizeof(struct Node));
    n[1].children = malloc((nodes_qtd - 1) * sizeof(struct Node));


    strcpy(n[2].name, "C");
    n[2].parents = malloc((nodes_qtd - 1) * sizeof(struct Node));
    n[2].children = malloc((nodes_qtd - 1) * sizeof(struct Node));


    strcpy(n[3].name, "D");
    n[3].parents = malloc((nodes_qtd - 1) * sizeof(struct Node));
    n[3].children = malloc((nodes_qtd - 1) * sizeof(struct Node));


    //B --> A = 25
    p[0].distance = 25;
    p[0].node_a = n[1];
    p[0].node_b = n[0];
    n[1].parents[n[1].last_parent++] = n[0];
    n[0].children[n[0].last_children++] = n[1];

    //C --> B = 50
    p[1].distance = 50;
    p[1].node_a = n[2];
    p[1].node_b = n[1];
    n[2].parents[n[2].last_parent++] = n[1];
    n[1].children[n[1].last_children++] = n[2];

    //D --> C = 10
    p[2].distance = 10;
    p[2].node_a = n[3];
    p[2].node_b = n[2];
    n[3].parents[n[3].last_parent++] = n[2];
    n[2].children[n[2].last_children++] = n[3];



    //D --> A = 25
    p[3].distance = 25;
    p[3].node_a = n[3];
    p[3].node_b = n[0];
    n[3].parents[n[3].last_parent++] = n[0];
    n[0].children[n[0].last_children++] = n[3];


    //C --> A = 40
    p[4].distance = 40;
    p[4].node_a = n[2];
    p[4].node_b = n[0];
    n[2].parents[n[2].last_parent++] = n[0];
    n[0].children[n[0].last_children++] = n[2];
}

void print_nodes(struct Node *n, int nodes_qtd) {
    int i;
    int j;
    for (i = 0; i < nodes_qtd; ++i) {

        printf("\n--%s", n[i].name);

        for (j = 0; j < n[i].last_parent; ++j) {
            printf("\n  |__%s", n[i].parents[j].name);
        }
        printf("\n\n");
    }
}

void print_paths(Path *p, int path_size) {
    int i;
    for (i = 0; i < path_size; ++i) {
        printf("\n%s --> %s = %d", p[i].node_a.name, p[i].node_b.name, p[i].distance);
    }
    printf("\n\n");
}

int compare(const void *s1, const void *s2) {
    Path *p1 = (Path *) s1;
    Path *p2 = (Path *) s2;
    if (p1->distance == p2->distance) {
        int point_compare_a = strcmp(p1->node_a.name, p2->node_a.name);
        if (point_compare_a == 0) {
            return strcmp(p1->node_b.name, p2->node_b.name);
        } else {
            return point_compare_a;
        }
    } else {
        return p1->distance - p2->distance;
    }
}
void setup(struct Node *original_nodes, struct Node *kruskal_nodes, int nodes_qtd){
    int k;

    for (k = 0; k < nodes_qtd; ++k) {
        strcpy(kruskal_nodes[k].name, original_nodes[k].name);
        kruskal_nodes[k].parents = malloc((nodes_qtd - 1) * sizeof(struct Node));
        kruskal_nodes[k].children = malloc((nodes_qtd - 1) * sizeof(struct Node));
    }

}