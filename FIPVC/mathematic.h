//
//  mathematic.h
//  FIPVC
//
//  Created by appl on 2018/11/21.
//  Copyright © 2018年 leon. All rights reserved.
//

#ifndef mathematic_h
#define mathematic_h

#include <stdio.h>
#include "Matrix.h"





void Zero(double *src,int width,int height);


/**
 矩阵卷积操作
 */
void matrixConvolution(Matrix *src, Matrix *dst, Matrix *mask);

/**
 矩阵乘实数
 */
void matrixMultreal(Matrix *src, Matrix *dst,double k);

void matrixToBinary(Matrix *src, Matrix *dst);

#endif /* mathematic_h */
