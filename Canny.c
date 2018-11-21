//
//  Canny.c
//  OCImageProcessing
//
//  Created by appl on 2018/11/12.
//  Copyright © 2018年 appl. All rights reserved.
//

#include "Canny.h"
#include <stdlib.h>
#include <math.h>
#include "mathematic.h"


void Gaussission(Matrix *src,Matrix *dst){
    Matrix *gauss = matrixMake(5, 5);
    double arr[25] = { 2, 4, 5, 4, 2,
        4, 9,12, 9, 4,
        5,12,15,12, 5,
        4, 9,12, 9, 4,
        2, 4, 5, 4, 2};
    matrixSet(gauss, arr);
    matrixConvolution(src, dst, gauss);
    matrixMultreal(dst, dst, 1.0/159.0);
    matrixFree(gauss);
}

void getAngle(Matrix *amplitude, Matrix *directionX, Matrix *directionY){
    int width = directionX->width;
    int height = directionX->height;
    /// 计算幅值
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            int index = j * width + i;
            double a =   atan2(directionY->array[index], directionX->array[index]) * (180.0/M_PI);
        }
}


void Sobel(Matrix *src,Matrix *amplitude, Matrix *direction){
    int width = src->width;
    int height = src->height;
    Matrix *dst_x = matrixMake(width, height);
    Matrix *dst_y = matrixMake(width, height);
    double sobel_x[9] = { -1, -2, -1, 0, 0, 0, -1, -2, -1};
    double sobel_y[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};
    Matrix *m_sobel_x = matrixMake(3, 3);
    Matrix *m_sobel_y = matrixMake(3, 3);
    matrixSet(m_sobel_x, sobel_x);
    matrixSet(m_sobel_y, sobel_y);
    matrixConvolution(src, dst_x, m_sobel_x);
    matrixConvolution(src, dst_y, m_sobel_y);
    
    /// 计算幅值
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            int index = j * width + i;
            amplitude->array[index] = sqrt(pow(dst_x->array[index], 2) + pow(dst_y->array[index], 2));
        }
    
    /// 计算梯度方向
    getAngle(amplitude, dst_x, dst_y);
    
    matrixFree(dst_x);
    matrixFree(dst_y);
    matrixFree(m_sobel_x);
    matrixFree(m_sobel_y);
}
void Canny(Matrix *src,Matrix *dst,int sobel_size,double threshold1,double threshold2){
    if(src->width != dst->width && src->height != dst->height){
        printf("size is not match !");
        exit(0);
    }
    if(dst == NULL){
        printf("dst can not be NULL\n");
        exit(0);
    }
    int width = src->width;
    int height = src->height;
    //梯度幅度
    Matrix *edge_a = matrixMake(width, height);
    //梯度方向
    Matrix *edge_d = matrixMake(width, height);
    Matrix *threshold_max = matrixMake(width, height);
    Matrix *threshold_min = matrixMake(width, height);
    
    ///高斯滤波
    Gaussission(src, dst);
    
    ///sobel 算子 获取梯度方向和幅值
    Sobel(src, edge_a, edge_d);
    
    
    
    matrixFree(edge_a);
    matrixFree(edge_d);
    matrixFree(threshold_max);
    matrixFree(threshold_min);
}
