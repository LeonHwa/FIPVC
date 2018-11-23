//
//  Matrix.c
//  FIPVC
//
//  Created by leon on 2018/11/21.
//  Copyright © 2018年 leon. All rights reserved.
//

#include "Matrix.h"
#include <stdlib.h>
#include "mathematic.h"




Matrix *matrixMake(int width, int height){
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->width = width;
    m->height = height;
    m->array = (double *)malloc(sizeof(double) * width * height);
    if(m->array != NULL){
      Zero(m->array, width, height);
    }
    return m;
}

Position *positionMake(int x, int y){
    Position *p = (Position *)malloc(sizeof(Position));
    p->x = x;
    p->y = y;
    return p;
}

void matrixSet(Matrix *src, double *array){
    for(int i=0;i<src->width * src->height;i++)
        src->array[i] = array[i];
}

void matrixCopy(Matrix *src, Matrix *dst){
    for(int i=0;i<src->width * src->height;i++)
        dst->array[i] = src->array[i];
}

void matrixFree(Matrix *m){
    free(m->array);
    free(m);
}
