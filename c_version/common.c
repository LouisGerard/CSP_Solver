#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"

/**
 * FILE
 **/
size_t read_file(char *path, char** result)
{
    #define CHUNK 1024
    char buf[CHUNK];
    size_t nread;
    size_t result_size = 1;
    FILE *file= fopen(path, "r");
    *result = NULL;

    if (file == NULL) {
        perror("file open");
        exit(1);
    }
    while ((nread = fread(buf, 1, sizeof buf -1, file)) > 0) {
        buf[nread] = '\0';
        result_size += nread;
        char *temp = *result;
        *result = (char*) malloc(result_size);
        if (temp) {
            sprintf(*result, "%s%s", temp, buf);
            free(temp);
        }
        else
            sprintf(*result, "%s", buf);
    }
    if (ferror(file)) {
        perror("file read");
        exit(1);
    }
    fclose(file);

    printf("Fichier lu !\n");

    return result_size;
}

void parse_grid(char *grid_text, size_t text_size)
{
    char *grid_text_cpy = malloc(text_size);
    strcpy(grid_text_cpy, grid_text);
    char *line = strtok(grid_text_cpy, "\n");
    grid_size = atoi(line);

    if (grid_size == 0) {
        perror("file format");
        exit(1);
    }

    grid = (int*) malloc(grid_size*grid_size*sizeof(int));

    for (unsigned y = 0; y < grid_size; ++y) {
        //lire la ligne courante
        char *line = strtok(NULL, "\n");
        if (line == NULL) {
            perror("file format");
            exit(1);
        }

        for (unsigned x = 0; x < grid_size; ++x) {
            int value = atoi(&line[x*2]);
            grid[y*grid_size+x] = value;
        }

        //sauter une ligne
        strtok(NULL, "\n");
    }

    free(grid_text_cpy);
    show_grid();
}

void parse_cons(char *cons_text, size_t text_size)
{
    constraint* constraints_temp[grid_size*grid_size];  //todo calculer taille
    constraints_size = 0;
    char *cons_text_cpy = malloc(text_size);
    strcpy(cons_text_cpy, cons_text);
    char *line = strtok(cons_text_cpy, "\n");

    //superiority
    for (unsigned y = 0; y < grid_size; ++y) {
        //horizontal
        line = strtok(NULL, "\n");
        if (line == NULL) {
            perror("file format");
            exit(1);
        }
        for (unsigned x = 0; x < grid_size-1; ++x) {
            if (line[x*2+1] == ' ')
                continue;

            int x1, x2;
            if (line[x*2+1] == '>') {
                x1 = x;
                x2 = x+1;
            }
            else if (line[x*2+1] == '<') {
                x1 = x+1;
                x2 = x;
            }
            else {
                perror("file format");
                exit(1);
            }

            int * array = (int*) malloc(sizeof(int)*4);
            *array = x1;
            *(array+1) = y;
            *(array+2) = x2;
            *(array+3) = y;
            printf("(%d,%d) > (%d,%d)\n", x1, y, x2, y);
            constraints_temp[constraints_size++] = create_constraint(&compareSuperiority, 1, array);
        }

        //vertical
        line = strtok(NULL, "\n");
        if (line == NULL) {
            if (y == grid_size-1)
                break;
            perror("file format");
            exit(1);
        }
        for (unsigned x = 0; x < grid_size; ++x) {
            if (line[x] == '.')
                continue;

            int y1, y2;
            if (line[x] == 'v') {
                y1 = y;
                y2 = y+1;
            }
            else if (line[x] == '^') {
                y1 = y+1;
                y2 = y;
            }
            else {
                perror("file format");
                exit(1);
            }

            int * array = (int*) malloc(sizeof(int)*4);
            *array = x;
            *(array+1) = y1;
            *(array+2) = x;
            *(array+3) = y2;
            printf("(%d,%d) > (%d,%d)\n", x, y1, x, y2);
            constraints_temp[constraints_size++] = create_constraint(&compareSuperiority, 1, array);
        }
    }
    free(cons_text_cpy);

    //uniqueness
    int array_size = 0;
    for (unsigned i = 1; i < grid_size; ++i)
        array_size += i;
    array_size *= 2;

    for(unsigned line_index = 0; line_index < grid_size; ++line_index) {
        int *array = (int*) malloc(sizeof(int)*(array_size*4));

        int array_offset = 0;
        for (unsigned i1 = 0; i1 < grid_size; ++i1)
            for (unsigned i2 = i1+1; i2 < grid_size; ++i2) {
                //itemHorizontal.x
                *(array+array_offset) = i1;
                //itemHorizontal.y
                ++array_offset;
                *(array+array_offset) = line_index;
                //itemHorizontal.x
                ++array_offset;
                *(array+array_offset) = i2;
                //itemHorizontal.y
                ++array_offset;
                *(array+array_offset) = line_index;

                //itemVertical.x
                ++array_offset;
                *(array+array_offset) = line_index;
                //itemVertical.y
                ++array_offset;
                *(array+array_offset) = i1;
                //itemVertical.x
                ++array_offset;
                *(array+array_offset) = line_index;
                //itemVertical.y
                ++array_offset;
                *(array+array_offset) = i2;

                ++array_offset;
            }
        printf("Line and column %d must be unique\n", line_index);
        constraints_temp[constraints_size++] = create_constraint(&compareDifference, array_size, array);
    }

    //copy constraints
    constraints = malloc(constraints_size*sizeof(constraint));
    memcpy(constraints, constraints_temp, constraints_size);
}

/**
 * SHOW
 */
void show_grid()
{
    for (unsigned y = 0; y < grid_size; ++y) {
        for (unsigned x = 0; x < grid_size; ++x)
            printf("%d,", grid[y*grid_size+x]);
        printf("\n");
    }
}


constraint * create_constraint (function f, unsigned size, int * array)
{
    constraint * constr = (constraint*)malloc(sizeof(constraint));

    constr->operation = f;
    constr->array = array;
    constr->size = size;

    return constr;
}

inline bool compareDifference(unsigned first, unsigned second)
{
    return  first == 0 || second == 0 || first != second;
}

inline bool compareSuperiority(unsigned first, unsigned second)
{
    return first == 0 || second == 0 || first > second;
}
