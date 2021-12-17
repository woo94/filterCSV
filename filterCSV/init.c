//
//  init.c
//  filterCSV
//
//  Created by woo94 on 2021/12/17.
//

#include "init.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize() {
    FILE *input_stream = fopen("600TypeA.csv", "r");

    FILE *process_0_fp = fopen("process_0.csv", "w+");
    FILE *process_x_fp = fopen("process_x.csv", "w+");
    FILE *process_y_fp = fopen("process_y.csv", "w+");
    
    char line[MAX_LEN], *result;
    char *sep = ",";
    char *lasts = NULL;

    int** mapped_array = malloc(sizeof(int*) * ROW_SIZE);
    Paired_Array* filtered_array = malloc(sizeof(Paired_Array) * ROW_SIZE);

    int row_index = 0;

    while((result = fgets(line, MAX_LEN, input_stream)) != NULL) {
        mapped_array[row_index] = malloc(sizeof(int) * COL_SIZE);
        memset(mapped_array[row_index], 0, COL_SIZE * sizeof(int));

        filtered_array[row_index].value = malloc(sizeof(int) * COL_SIZE);
        memset(filtered_array[row_index].value, 0, COL_SIZE * sizeof(int));
        filtered_array[row_index].index = malloc(sizeof(int) * COL_SIZE);
        memset(filtered_array[row_index].index, 0, COL_SIZE * sizeof(int));

        int col_index = 0;
        int paired_array_index = 0;

        char* first_token = strtok_r(line, sep, &lasts);
        int first_token_int = atoi(first_token);
        if(first_token_int < 10) {
            mapped_array[row_index][col_index] = 0;
        }
        else {
            mapped_array[row_index][col_index] = first_token_int;

            filtered_array[row_index].index[paired_array_index] = col_index;
            filtered_array[row_index].value[paired_array_index] = first_token_int;

            paired_array_index++;
        }
        col_index++;

        while(1) {
            char* next_token = strtok_r(NULL, sep, &lasts);

            if(next_token == NULL) {
                break;
            }
            int next_token_int = atoi(next_token);

            if(next_token_int < 10) {
                mapped_array[row_index][col_index] = 0;
            }
            else {
                mapped_array[row_index][col_index] = next_token_int;

                filtered_array[row_index].index[paired_array_index] = col_index;
                filtered_array[row_index].value[paired_array_index] = next_token_int;

                paired_array_index++;
            }

            col_index++;
        }

        row_index++;
    }

//    int simple_counter = 0;
//    for(int i=0; i<ROW_SIZE; i++){
//        for(int j=0; j<COL_SIZE; j++) {
//            int val = mapped_array[i][j];
//            if(val >= 10) {
//                simple_counter++;
//            }
//        }
//    }

    for(int i=0; i<ROW_SIZE; i++) {
        for(int j=0; j<COL_SIZE; j++) {
            int val = mapped_array[i][j];
            if(j < COL_SIZE-1) {
                fprintf(process_0_fp, "%d,", val);
            }
            else {
                fprintf(process_0_fp, "%d\n", val);
            }
        }
    }

    for(int i=0; i<ROW_SIZE; i++) {
        for(int j=0; j<COL_SIZE; j++) {
            int index = filtered_array[i].index[j];
            int value = filtered_array[i].value[j];

            // 0번째 column에 0이 들은 경우 다음 row로 넘어간다.
            if(index == 0 && j == 0) {
                break;
            }

            // j번째 column에 0이 아닌 값이 들었을때
            // 1) j+1이 COL_SIZE인 경우
            // "%d\n" 출력
            if(index != 0 && j+1 == COL_SIZE) {
//                printf("%d\n", i);
                
                fprintf(process_x_fp, "%d\n", index);
                fprintf(process_y_fp, "%d\n", value);
            }

            // 2) j+1이 COL_SIZE를 초과하지 않는 경우
            else if(index != 0 && j+1 != COL_SIZE) {
//                printf("%d\n", i);
                
                int next_index = filtered_array[i].index[j+1];

                // 2-1) n+1번째 column에 0이 들은 경우
                // "%d\n" 출력
                if(next_index == 0) {
                    fprintf(process_x_fp, "%d\n", index);
                    fprintf(process_y_fp, "%d\n", value);
                }
                // 2-2) n+1번째 column에 0이 아닌 값이 들은 경우
                // "%d," 출력
                else {
                    fprintf(process_x_fp, "%d,", index);
                    fprintf(process_y_fp, "%d,", value);
                }
            }
        }
    }

    // close all file pointers
    fclose(input_stream);
    fclose(process_0_fp);
    fclose(process_x_fp);
    fclose(process_y_fp);
//    fclose(process_x_10_fp);
//    fclose(process_y_10_fp);

    // free all allocated memory
    for(int i=0; i<ROW_SIZE; i++) {
        free(mapped_array[i]);
        free(filtered_array[i].value);
        free(filtered_array[i].index);
    }
    free(mapped_array);
    free(filtered_array);
}
