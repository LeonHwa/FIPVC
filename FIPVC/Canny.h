//
//  Canny.h
//  FIPVC
//
//  Created by leon on 2018/11/12.
//  Copyright © 2018年 appl. All rights reserved.
//

#ifndef Canny_h
#define Canny_h

#include <stdio.h>
#include "Matrix.h"
#include "mathematic.h"

void Canny(Matrix *src,Matrix *dst,int sobel_size,double threshold_min,double threshold_max);


/**
 高斯平滑滤波
 */
void Gaussission(Matrix *src,Matrix *dst);


/**
 通过Scharr算子计算幅值，边缘角度（注意不是方向）

 @param src 输入矩阵
 @param amplitude 输出幅值
 @param edgeAngle 输出边缘角度
 */
void Scharr(Matrix *src,Matrix *amplitude, Matrix *edgeAngle);


/**
 计算中心点边缘的角度
 以x轴正方向为起点逆时针旋转360 计量0～360
 @param edgeAngle 输出结果
 @param directionX x方向偏导数
 @param directionY y方向偏导数
 */
void getAngle(Matrix *edgeAngle, Matrix *directionX, Matrix *directionY);


/**
 转换边缘角度的方向
 *   0 1 2
 *   3 * 5
 *   6 7 8
 -1 表示没有方向
 @param edgeAngle 边缘的角度集合
 @param edgeDirection 输出结果
 */
void getAngleDirection(Matrix *edgeAngle, Matrix *edgeDirection);




/**
 非最大抑制
 在中心点边缘方向上对比相邻的两个幅值，
 满足至少小于其中的一个时置为0

 @param dst 待处理的矩阵
 @param amplitude src 的幅值矩阵
 @param edgeDirection src 的边缘方向矩阵
 */
void suppressionUnlessMax(Matrix *amplitude, Matrix *edgeDirection, Matrix *dst);


/**
 阀值处理
 */
void threshold(Matrix *src, Matrix *dst, double threshold);


/**
 连接边缘
 低阀值矩阵中包含了高阀值点，首先高阀值点本身就是边缘点，
 以高阀值点为中心找出 周围8个点是否为有阀值点（低阀值点或高阀值点），
 如果有将其标记为边缘点（值置为2），再以标记为阀值点的像素为中心查找周围8个点，以此递归下去
 @param thresholds_min 低阀值矩阵
 @param thresholds_max 低阀值矩阵
 */
void edgesConnect(Matrix *thresholds_min, Matrix *thresholds_max);



/**
 边缘追踪
 检查中心点为中心查找周围8个点是否有低阀值区间点
 有则标记为边缘点

 @param thresholds_min 标记了低阀值的矩阵
 @param p 检查中心点
 */
void edgeTrack(Matrix *thresholds_min, Position *p);
#endif /* Canny_h */
