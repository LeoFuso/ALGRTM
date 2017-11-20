#include <stdio.h>
#include<stdlib.h>

void random_vector(int v[], int size);
void to_print(int v[], int size);
void sort(int v[], int size);
void insertion_sort(int v[], int size);

int main(void) {

    printf("Insertion Sort demonstration:\n");

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
    insertion_sort(v,size);
}

void insertion_sort(int v[], int size){

    int j = 0;
    int i = 0;
    int key = 0;

    for(j=1; j<size; j++){
        key = v[j];
        i = j-1;
        while(i >= 0 && v[i] > key){
            v[i+1] = v[i];
            i = i-1;
            v[i+1] = key;
        }
    }
}