#include <stdio.h>
#include<stdlib.h>

void random_vector(int v[], int size);
void to_print(int v[], int size);
void sort(int v[], int size);
void merge_sort(int v[], int p, int r);
void merge(int v[], int p, int q, int r);

int main(void) {

    printf("Merge Sort demonstration:\n");

    int size = 100;

    int *vector = malloc(sizeof(int)*size);

    printf("\nRandom vector: \n");
    random_vector(vector, size);
    to_print(vector, size);
    sort(vector, 100);
    printf("\nSorted vector: \n");
    to_print(vector, size);

    free(vector);
    vector = NULL;
    size = NULL;

    return 0;
}

void to_print(int v[], int size){

    int i = 0;
    int count = -1;
    printf("\nData: \n\n");
    printf(":: ");

    for (i = 0; i < size; i++){
        count = count + 1;

        if(count == 10){
            count = 0;
            printf("::\n:: ");
        }

        if(v[i] < 10)
            printf("0%d - ",v[i]);
        else
            printf("%d - ",v[i]);
    }

    printf("::\n\n"	);
}

void random_vector(int v[], int size){

    int i = 0;
    int w = 0;
    int t = 0;

    for (i = 0; i < size; ++i)
        v[i] = i;

    for (i = size - 1; i > 0; --i) {

        w = rand()%i;
        t = v[i];
        v[i] = v[w];
        v[w] = t;
    }
}

void sort(int v[], int size){

    merge_sort(v, 0, size - 1);

}

void merge_sort(int v[], int p, int r){
    int q = 0;

    if(p < r)
    {
        q = (p+r)/2;
        merge_sort(v, p, q);
        merge_sort(v, q+1, r);
        merge(v, p, q, r);
    }
}

void merge(int v[], int p, int q, int r){

    int n1 = q - p + 1;
    int n2 = r - q;

    int i;
    int j;
    int k;

    int *left = malloc(sizeof(int)*(n1 + 1));
    int *right = malloc(sizeof(int)*(n2 + 1));

    for(i = 0; i < n1; i++)
        left[i] = v[p+i];

    for(i = 0; i < n2; i++)
        right[i] = v[q+i+1];

    left[n1] = 2147483647;
    right[n2] = 2147483647;

    i =  0;
    j = 0;

    for(k = p; k <= r; k++){
        if(left[i] <= right[j])
            v[k] = left[i++];
        else
            v[k] = right[j++];
    }

    free(left);
    left = NULL;

    free(right);
    right = NULL;
}