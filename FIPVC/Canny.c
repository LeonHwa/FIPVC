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



void threshold(Matrix *src, Matrix *dst, double threshold){
    int width = src->width;
    int height = src->height;
    for(int i=0;i<width * height;i++){
        int v = src->array[i];
        dst->array[i] = v > threshold ? v : 0;
    }
}

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

void getAngle(Matrix *edgeAngle, Matrix *directionX, Matrix *directionY){
    int width = directionX->width;
    int height = directionX->height;
    double x =0,y =0;
    /// 计算幅值
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            int index = j * width + i;
            x = directionX->array[index];
            y = directionY->array[index];
            if(!(x == 0 && y == 0)){
                double angle =   atan2(y, x) * (180.0/M_PI);
                edgeAngle->array[index] = (angle >= 0 ? angle : angle + 360);
            }else{
                edgeAngle->array[index] = -1;
            }
        }
}

void getAngleDirection(Matrix *edgeAngle, Matrix *edgeDirection){
    int width = edgeAngle->width;
    int height = edgeAngle->height;
    double angle = 0;
    for(int i=0;i<width*height;i++){
        angle = edgeAngle->array[i];
        if(angle== -1)
            edgeDirection->array[i]=-1.0;
        else if(angle <22.5 || angle > 337.5)
            edgeDirection->array[i] = 5;
        else if(angle<67.5&&angle>=22.5)
            edgeDirection->array[i]=2.0;
        else if(angle<112.5&&angle>=67.5)
            edgeDirection->array[i]=1.0;
        else if(angle<157.5&&angle>=112.5)
            edgeDirection->array[i]=0.0;
        else if(angle<202.5&&angle>=157.5)
            edgeDirection->array[i]=3.0;
        else if(angle<247.5&&angle>=202.5)
            edgeDirection->array[i]=6.0;
        else if(angle<292.5&&angle>=247.5)
            edgeDirection->array[i]=7.0;
        else if(angle<337.5&&angle>=292.5)
            edgeDirection->array[i]=8.0;
    }
}

void Scharr(Matrix *src,Matrix *amplitude, Matrix *edgeAngle){
    int width = src->width;
    int height = src->height;
    Matrix *dst_x = matrixMake(width, height);
    Matrix *dst_y = matrixMake(width, height);
    
    //    double sobel_x[9] = { 1,0,-1,
    //        1, 0, -1,
    //        1, 0, -1};
    //    double sobel_y[9] = { 3,10,3,
    //        0, 0, 0,
    //        -3, -10, -3};

    double sobel_y[9] = { -1,-2,-1,
                           0, 0, 0,
                           1, 2, 1};
    double sobel_x[9] = { -1, 0, 1,
                           -2, 0, 2,
                           -1, 0, 1};
    Matrix *m_sobel_x = matrixMake(3, 3);
    Matrix *m_sobel_y = matrixMake(3, 3);
    matrixSet(m_sobel_x, sobel_x);
    matrixSet(m_sobel_y, sobel_y);
    matrixConvolution(src, dst_x, m_sobel_x);
    matrixConvolution(src, dst_y, m_sobel_y);
    for(int i=0;i<width * height;i++)
        dst_y->array[i] = -dst_y->array[i];
   
    /// 计算幅值
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            int index = j * width + i;
            amplitude->array[index] = sqrt(pow(dst_x->array[index], 2) + pow(dst_y->array[index], 2));
        }
    
    /// 计算梯度角度
    getAngle(edgeAngle, dst_x, dst_y);
    
    matrixFree(dst_x);
    matrixFree(dst_y);
    matrixFree(m_sobel_x);
    matrixFree(m_sobel_y);
}

void suppressionUnlessMax(Matrix *amplitude, Matrix *edgeDirection, Matrix *dst){
    int width = amplitude->width;
    int height = amplitude->height;
    int x , y = 0;
    Matrix *temp = matrixMake(width, height);
    int m = 0;
    for(int j=1;j<height-1;j++)
        for(int i=1;i<width-1;i++){
            int index = j * width + i;
            int d = edgeDirection->array[index];
            if(d != -1){
                y = d / 3 - 1;
                x = d % 3 - 1;
                m =  amplitude->array[index];
                int m1 = amplitude->array[(j + y) * width + i + x];
                int m2 = amplitude->array[(j - y) * width + i - x];
                if(m <= m1 || m < m2){
                    temp->array[index] = 0;
                }else{
                    temp->array[index] = m;
                }
            }
        }
    matrixCopy(temp, dst);
    matrixFree(temp);
}


void edgeTrack(Matrix *thresholds_min, Position *p){
    int width = thresholds_min->width;
    int height = thresholds_min->height;
    int x = p->x;
    int y = p->y;
    free(p);
    if(x >= 0 && x < width && y >= 0 && y < height && thresholds_min->array[y * width + x] == 1){
        thresholds_min->array[y * width + x] = 2;
        for(int j=-1;j<2;j++)
            for(int i=-1;i<2;i++){
                int n = x + i;
                int m = y + j;
               
                edgeTrack(thresholds_min, positionMake(n, m));
                
            }
    }
}
void edgesConnect(Matrix *thresholds_min, Matrix *thresholds_max){
    int width = thresholds_min->width;
    int height = thresholds_min->height;
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            int index = j * width + i;
            /// 以高阀值点为中心连接周围的边缘点
            if(thresholds_max->array[index] == 1 && thresholds_min->array[index] != 2){
                edgeTrack(thresholds_min, positionMake(i, j));
            }
            
        }
}

void Canny(Matrix *src,Matrix *dst,int sobel_size,double threshold_min,double threshold_max){
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
    Matrix *thresholds_max = matrixMake(width, height);
    Matrix *thresholds_min = matrixMake(width, height);
    
    ///高斯滤波
    Gaussission(src, dst);
    
    ///Scharr 算子 获取梯度角度和幅值
    Scharr(dst, edge_a, edge_d);

    ///转换角度成方向
    getAngleDirection(edge_d, edge_d);

    ///非最大抑制
    suppressionUnlessMax(edge_a, edge_d, dst);

    ///双阀值处理 （thresholds_min 包含 thresholds_max）
    threshold(dst, thresholds_min, threshold_min);
    threshold(dst, thresholds_max, threshold_max);

    /// 将两个阀值的点转成二进制点
    matrixToBinary(thresholds_min, thresholds_min);
    matrixToBinary(thresholds_max, thresholds_max);

    ///连接边缘
    edgesConnect(thresholds_min, thresholds_max);
    Zero(dst->array, dst->width, dst->height);
    for(int i=0;i<width * height;i++){
        if(thresholds_min->array[i] == 2)
            dst->array[i] = 255;
    }

    matrixFree(edge_a);
    matrixFree(edge_d);
    matrixFree(thresholds_max);
    matrixFree(thresholds_min);
}
