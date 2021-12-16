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

#define MAX_LEN 100000

//#define ROW_SIZE 600
//#define COL_SIZE 4177
#define ROW_SIZE 7
#define COL_SIZE 11

typedef struct {
    int* index;
    int* value;
} Paired_Array;

// 첫번째 배열에서는 < 10 이면 0으로 하고 아니면 다 올린다
// 두번째 배열에서는 < 10 이면 0은 빼고 x값은 넣어주고

int main(int argc, const char * argv[]) {
    time_t start, end;
    time(&start);
    FILE *stream = fopen("samplingData.csv", "r");
    char line[MAX_LEN], *result;
    char *sep = ",";
    char *lasts = NULL;
    
    int** filtered_array = malloc(sizeof(int*) * ROW_SIZE);
    Paired_Array* index_and_value = malloc(sizeof(Paired_Array) * ROW_SIZE);
    
    int row_index = 0;

    while((result = fgets(line, MAX_LEN, stream)) != NULL) {
        filtered_array[row_index] = malloc(sizeof(int) * COL_SIZE);
        memset(filtered_array[row_index], 0, COL_SIZE * sizeof(int));
        
        index_and_value[row_index].value = malloc(sizeof(int) * COL_SIZE);
        memset(index_and_value[row_index].value, 0, COL_SIZE * sizeof(int));
        index_and_value[row_index].index = malloc(sizeof(int) * COL_SIZE);
        memset(index_and_value[row_index].index, 0, COL_SIZE * sizeof(int));
        
        int col_index = 0;
        int paired_array_index = 0;

        char* first_token = strtok_r(line, sep, &lasts);
        int first_token_int = atoi(first_token);
        if(first_token_int < 10) {
            filtered_array[row_index][col_index] = 0;
        }
        else {
            filtered_array[row_index][col_index] = first_token_int;
            
            index_and_value[row_index].index[paired_array_index] = col_index;
            index_and_value[row_index].value[paired_array_index] = first_token_int;

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
                filtered_array[row_index][col_index] = 0;
            }
            else {
                filtered_array[row_index][col_index] = next_token_int;
                
                index_and_value[row_index].index[paired_array_index] = col_index;
                index_and_value[row_index].value[paired_array_index] = next_token_int;
                
                paired_array_index++;
            }
            
            col_index++;
        }
        
        row_index++;
    }
    
    for(int i=0; i<ROW_SIZE; i++){
        for(int j=0; j<COL_SIZE; j++) {
            int val = filtered_array[i][j];
            printf("%d ", val);
        }
        printf("\n");
    }
    
    printf("end of print filtered_array\n");
    
    for(int i=0; i<ROW_SIZE; i++) {
        for(int j=0; j<COL_SIZE; j++) {
            printf("%d %d\n", index_and_value[i].index[j], index_and_value[i].value[j]);
        }
        printf("\n");
    }
    
    for(int i=0; i<ROW_SIZE; i++) {
        free(filtered_array[i]);
        free(index_and_value[i].value);
        free(index_and_value[i].index);
    }
    free(filtered_array);
    free(index_and_value);
    
    printf("\n");

    fclose(stream);
    time(&end);
    printf("%.2lf seconds\n", difftime(end, start));
}
