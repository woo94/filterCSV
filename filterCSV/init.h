//
//  init.h
//  filterCSV
//
//  Created by woo94 on 2021/12/17.
//

#ifndef init_h
#define init_h

#define MAX_LEN 2000000

// 600TypeA
#define ROW_SIZE 600
#define COL_SIZE 4177

// TypeF_4_test
//#define ROW_SIZE 4
//#define COL_SIZE 4177

// TypeAx
//#define ROW_SIZE 1906
//#define COL_SIZE 2

// samplingData
//#define ROW_SIZE 7
//#define COL_SIZE 11

#include <stdio.h>

typedef struct {
    int* index;
    int* value;
} Paired_Array;

void initialize(void);

#endif /* init_h */
