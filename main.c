#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[2];
    int last;
    struct Node *nodes;
};

typedef struct {
    struct Node node_a;
    struct Node node_b;
    int distance;
} Path;

void print_paths(Path *p, int path_size);

void print_nodes(struct Node *n, int nodes_qtd);

int compare(const void *s1, const void *s2);

void kruskal(Path *original_path, int original_path_size, Path *kruskal_path, int kruskal_path_size,
             struct Node *original_nodes, struct Node *kruskal_nodes, int nodes_qtd);

char *check_parent(struct Node node, struct Node *kruskal_nodes, int qtd_nodes);

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
    printf("FIM");


    kruskal(original_path, original_path_size, kruskal_path, kruskal_path_size, original_nodes, kruskal_nodes,
            nodes_qtd);

    printf("\n\nTESTE:\n");
    print_nodes(kruskal_nodes, nodes_qtd);

    return 0;
}

void kruskal(Path *original_path, int original_path_size, Path *kruskal_path, int kruskal_path_size,
             struct Node *original_nodes, struct Node *kruskal_nodes, int nodes_qtd) {
    int i;
    int j;
    int k;
    Path i_path;
    int from_node;
    int to_node;


    int kruskal_path_control = 0;
    //Make a copy
    for (k = 0; k < nodes_qtd; ++k) {
        strcpy(kruskal_nodes[k].name, original_nodes[k].name);
        kruskal_nodes[k].nodes = malloc((nodes_qtd - 1) * sizeof(struct Node));
    }

    for (i = 0; i < original_path_size; ++i) {

        i_path = original_path[i];

        for (j = 0; j < nodes_qtd; ++j) {

            if (strcmp(kruskal_nodes[j].name, i_path.node_a.name) == 0) {
                from_node = j;

            }

            if (strcmp(kruskal_nodes[j].name, i_path.node_b.name) == 0) {
                to_node = j;
            }
        }

        if (check_parent(kruskal_nodes[to_node], kruskal_nodes, nodes_qtd) == NULL) {
            //n1 is father;
            if (check_parent(kruskal_nodes[from_node], kruskal_nodes, nodes_qtd) == NULL) {
                //isolated pair
                kruskal_path[kruskal_path_control++] = i_path;
                kruskal_nodes[from_node].nodes[kruskal_nodes[from_node].last++] = kruskal_nodes[to_node];
            }
        } else {
            printf("FIM");
            i = original_path_size;
        }

    }
}

char *check_parent(struct Node node, struct Node *kruskal_nodes, int qtd_nodes) {
    int i;
    if (node.last == 0) {

        return NULL;
    }
    for (i = 0; i < node.last; i++) {
        check_parent(kruskal_nodes[i], kruskal_nodes, qtd_nodes);
    }
}


void mount_paths_nodes(Path *p, struct Node *n, int nodes_qtd) {

    strcpy(n[0].name, "A");
    n[0].nodes = malloc((nodes_qtd - 1) * sizeof(struct Node));

    strcpy(n[1].name, "B");
    n[1].nodes = malloc((nodes_qtd - 1) * sizeof(struct Node));

    strcpy(n[2].name, "C");
    n[2].nodes = malloc((nodes_qtd - 1) * sizeof(struct Node));

    strcpy(n[3].name, "D");
    n[3].nodes = malloc((nodes_qtd - 1) * sizeof(struct Node));

    //A -> B = 25
    p[0].distance = 25;
    p[0].node_a = n[0];
    p[0].node_b = n[1];
    n[0].nodes[n[0].last++] = n[1];

    //B -> C = 50
    p[1].distance = 50;
    p[1].node_a = n[1];
    p[1].node_b = n[2];
    n[1].nodes[n[1].last++] = n[2];

    //C -> D = 10
    p[2].distance = 10;
    p[2].node_a = n[2];
    p[2].node_b = n[3];
    n[2].nodes[n[2].last++] = n[3];

    //A -> D = 25
    p[3].distance = 25;
    p[3].node_a = n[0];
    p[3].node_b = n[3];
    n[0].nodes[n[0].last++] = n[3];

    //A -> C = 40
    p[4].distance = 40;
    p[4].node_a = n[0];
    p[4].node_b = n[2];
    n[0].nodes[n[0].last++] = n[2];
}

void print_nodes(struct Node *n, int nodes_qtd) {
    int i;
    int j;
    for (i = 0; i < nodes_qtd; ++i) {

        printf("\n--%s", n[i].name);

        for (j = 0; j < n[i].last; ++j) {
            printf("\n  |__%s", n[i].nodes[j].name);
        }
        printf("\n\n");
    }
}

void print_paths(Path *p, int path_size) {
    int i;
    for (i = 0; i < path_size; ++i) {
        printf("\n%s -> %s = %d", p[i].node_a.name, p[i].node_b.name, p[i].distance);
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