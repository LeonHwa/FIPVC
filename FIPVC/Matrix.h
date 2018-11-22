//
//  Matrix.h
//  FIPVC
//
//  Created by appl on 2018/11/21.
//  Copyright © 2018年 leon. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

#include <stdio.h>


#pragma pack(1)
typedef struct MatrixStruct {
    int  width;
    int  height;
    double  *array;
}Matrix;

typedef struct Position_ Position;
struct Position_{
    int x;
    int y;
};

#pragma pack()

Matrix *matrixMake(int width, int height);
Position *positionMake(int x, int y);

void matrixSet(Matrix *src, double *array);

void matrixCopy(Matrix *src, Matrix *dst);
void matrixFree(Matrix *m);
#endif /* Matrix_h */
