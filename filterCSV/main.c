//
//  main.c
//  filterCSV
//
//  Created by woo94 on 2021/12/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "init.h"
#include "join.h"

// 600TypeA
#define ROW_SIZE 600
#define COL_SIZE 4177

int main(int argc, const char * argv[]) {
    double start, end;

    start = (double) clock();
    start = start / CLOCKS_PER_SEC;
    initialize();
    join_results();
    
    end = (double) clock();
    end = end / CLOCKS_PER_SEC;
    
    printf("%lf seconds\n", end-start);
}
