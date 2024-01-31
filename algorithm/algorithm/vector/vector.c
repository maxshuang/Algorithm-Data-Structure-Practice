#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector* Create(int capacity){
    if(capacity<=0){
        printf("Invalid capacity\n");
        return NULL;
    }

    Vector *vector = (Vector*)malloc(sizeof(Vector));
    if(NULL == vector){
        printf("malloc failed\n");
        return NULL;
    }
    vector->size = 0;
    vector->capacity = capacity;
    vector->data = (int*)malloc(sizeof(int)*capacity);
    if(NULL == vector->data){
        printf("malloc failed\n");
        free(vector);
        return NULL;
    }
    return vector;
}

void PushBack(Vector *vector, int value){
    if(NULL == vector){
        printf("vector is NULL\n");
        return;
    }
    if(vector->size == vector->capacity){
        int* data=(int*)malloc(sizeof(int)*vector->capacity*2);
        if(NULL == data){
            printf("enlarge vector failed\n");
            return;
        }
        for(int i=0;i<vector->size;i++){
            data[i]=vector->data[i];
        }
        free(vector->data);
        vector->data=data;
    }

    vector->data[vector->size] = value;
    vector->size++;
}

int PopBack(Vector *vector){
    if(NULL == vector){
        printf("vector is NULL\n");
        return -1;
    }
    if(vector->size == 0){
        printf("vector is empty\n");
        return -1;
    }
    vector->size--;
    return vector->data[vector->size];
}

void Clear(Vector *vector){
    if(NULL == vector){
        printf("vector is NULL\n");
        return;
    }
    vector->size = 0;
}

void Destroy(Vector *vector){
    if(NULL == vector){
        printf("vector is NULL\n");
        return;
    }
    free(vector->data);
    free(vector);
}

void Print(Vector *vector){
    if(NULL == vector){
        printf("vector is NULL\n");
        return;
    }
    printf("size: %d, capacity: %d\n", vector->size, vector->capacity);
    for(int i=0;i<vector->size;i++){
        printf("%d ", vector->data[i]);
    }
    printf("\n");
}

int Get(Vector *vector, int index){
    if(NULL == vector){
        printf("vector is NULL\n");
        return -1;
    }
    if(index<0 || index>=vector->size){
        printf("index is out of range\n");
        return -1;
    }
    return vector->data[index];
}

void Set(Vector *vector, int index, int value){
    if(NULL == vector){
        printf("vector is NULL\n");
        return;
    }
    if(index<0 || index>=vector->size){
        printf("index is out of range\n");
        return;
    }
    vector->data[index] = value;
}