//
//  join.c
//  filterCSV
//
//  Created by woo94 on 2021/12/17.
//
#include "init.h"
#include "join.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONCAT_SIZE 10

void join_results() {
    FILE *process_x_fp = fopen("process_x.csv", "r");
    FILE *process_y_fp = fopen("process_y.csv", "r");
    FILE *process_x_10_fp = fopen("process_x_10.csv", "w+");
    FILE *process_y_10_fp = fopen("process_y_10.csv", "w+");
    
    concat_rows(process_x_fp, process_x_10_fp, CONCAT_SIZE);
    concat_rows(process_y_fp, process_y_10_fp, CONCAT_SIZE);
    
    fclose(process_x_fp);
    fclose(process_y_fp);
    fclose(process_x_10_fp);
    fclose(process_y_10_fp);
}

void concat_rows(FILE *input_fp, FILE *output_fp, int concat_size) {
    char line[MAX_LEN], *result;
    
    int concat_counter = 0;
    int counter = 0;
    char *sep = ",";
    char *lasts = NULL;
    
    while((result = fgets(line, MAX_LEN, input_fp)) != NULL) {
        
        if(concat_counter < concat_size - 1) {
            line[strlen(line)-1] = ',';
            fprintf(output_fp, "%s", line);
            concat_counter++;
        }
        else {
            fprintf(output_fp, "%s", line);
            concat_counter = 0;
        }
        
        char *first_token = strtok_r(line, sep, &lasts);
        int first_token_int = atoi(first_token);
        printf("%d %d %d\n", counter, concat_counter, first_token_int);
        counter++;
    }
    fseek(output_fp, -1, SEEK_END);
    fprintf(output_fp, "\n");
}
