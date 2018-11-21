//
//  Canny.h
//  OCImageProcessing
//
//  Created by appl on 2018/11/12.
//  Copyright © 2018年 appl. All rights reserved.
//

#ifndef Canny_h
#define Canny_h

#include <stdio.h>
#include "Matrix.h"

void Canny(Matrix *src,Matrix *dst,int sobel_size,double threshold1,double threshold2);
void Gaussission(Matrix *src,Matrix *dst);
void Sobel(Matrix *src,Matrix *amplitude, Matrix *direction);
void getAngle(Matrix *amplitude, Matrix *directionX, Matrix *directionY);
#endif /* Canny_h */
