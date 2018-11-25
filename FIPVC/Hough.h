//
//  Hough.h
//  FIPVC
//
//  Created by leon on 2018/11/23.
//  Copyright © 2018年 leon. All rights reserved.
//

#ifndef Hough_h
#define Hough_h

#include <stdio.h>
#include "Matrix.h"


/**
 霍夫变换

 @param src 边缘矩阵
 @param dst 极坐标系(Polar coordinate system)的三角函数图像矩阵
 @param length 线长阀值
 */
Matrix * Hough(Matrix *src, Matrix *dst, int length);

#endif /* Hough_h */
