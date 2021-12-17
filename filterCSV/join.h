//
//  join.h
//  filterCSV
//
//  Created by woo94 on 2021/12/17.
//

#ifndef join_h
#define join_h

#include <stdio.h>

void join_results(void);
void concat_rows(FILE *input_fp, FILE *output_fp, int concat_size);

#endif /* join_h */
