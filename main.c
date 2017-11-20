#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    char point_a[2];
    char point_b[2];
    int distance;
} Path;

typedef struct {
    char father[2];
    struct Path *path;
} Tree;

void mount_paths(Path *p);

void print_graph(Path *p, int size);

void sort_graph(Path *p, int size);

int compare(const void *s1, const void *s2);

void kruskal(Path *p, Tree *t, int size);

void add_to(Path p, Tree *t, int size);

int main(void) {

    int graph_size = 5;

    Path *original_path = malloc(graph_size * sizeof(Path));
    Path *kruskal_path = malloc(graph_size * sizeof(Path));
    Tree *trees = malloc(graph_size * sizeof(Tree));


    mount_paths(original_path);

    printf("\n\nGraph:\n");
    print_graph(original_path, graph_size);


    qsort(original_path, graph_size, sizeof(Path), compare);

    printf("\n\nSorted Graph:\n");
    print_graph(original_path, graph_size);

    kruskal(original_path, trees, graph_size);

    return 0;
}

void kruskal(Path *p, Tree *t, int size) {
    int i;

    for (i = 0; i < size; ++i) {
        strcpy(t[i].father, "00");
    }

    i = 0;

    for (i = 0; i < size; ++i) {

        add_to(p[i], t, size);

    }

}

void add_to(Path p, Tree *t, int size) {
    int i;
    int current;
    Tree to_check;
    for (i = 0; i < size; ++i) {

        if (strcmp(t[i].father, "00") == 0) {
            t[i].father = p.point_b;
            t[i].path = p;
            to_check = t[i];
            current = i;
            i = size;

            printf("\n\nadd_to:\n");
        }
    }

    verify_tree(to_check,t, size);
}

int verify_tree(Tree to_check,  Tree *t, int size){
    int i;
    for (i = 0; i < size; ++i) {
        //??????????????????????????????????????
    }
}


int compare(const void *s1, const void *s2) {
    Path *p1 = (Path *) s1;
    Path *p2 = (Path *) s2;
    if (p1->distance == p2->distance) {
        int point_compare_a = strcmp(p1->point_a, p2->point_a);
        if (point_compare_a == 0) {
            return strcmp(p1->point_b, p2->point_b);
        } else {
            return point_compare_a;
        }
    } else {
        return p1->distance - p2->distance;
    }
}

void print_graph(Path *p, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        printf("\n%s -> %s = %d", p[i].point_a, p[i].point_b, p[i].distance);
    }
}

void mount_paths(Path *p) {
    //A -> B = 25
    p[0].distance = 25;
    strcpy(p[0].point_a, "A");
    strcpy(p[0].point_b, "B");

    //B -> C = 50 
    p[1].distance = 50;
    strcpy(p[1].point_a, "B");
    strcpy(p[1].point_b, "C");

    //C -> D = 10
    p[2].distance = 10;
    strcpy(p[2].point_a, "C");
    strcpy(p[2].point_b, "D");

    //A -> D = 25
    p[3].distance = 25;
    strcpy(p[3].point_a, "A");
    strcpy(p[3].point_b, "D");

    //A -> C = 40
    p[4].distance = 40;
    strcpy(p[4].point_a, "A");
    strcpy(p[4].point_b, "C");
}
