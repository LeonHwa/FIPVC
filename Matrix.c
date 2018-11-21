//
//  Matrix.c
//  FIPVC
//
//  Created by appl on 2018/11/21.
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

void matrixSet(Matrix *src, double *array){
    for(int i=0;i<src->width * src->height;i++)
        src->array[i] = array[i];
}

void matrixCopy(Matrix *src, Matrix *dst){
    for(int i=0;i<src->width * src->height;i++)
        dst->array[i] = src->array[i];
}
