//
//  algrithm.c
//  OCImageProcessing
//
//  Created by appl on 2018/10/31.
//  Copyright © 2018年 appl. All rights reserved.
//

#include "algrithm.h"
#include <string.h>
void InsertSort(int a[], int n){
    for(int i = 1; i < n; i ++){
        int p = a[i];
        int j;
        for(j = i; j > 0; j--){
            if(p < a[j - 1]){
                a[j] = a[j - 1];
            }else{//马上跳出 否则j的位置无法确定
                break;
            }
        }
        a[j] = p;
    }
}


