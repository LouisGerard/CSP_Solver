#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdbool.h>

typedef bool (*function)(unsigned, unsigned);
typedef struct _constraint
{
    function operation;
    unsigned size;
    int * array;
} constraint;

int *grid;
size_t grid_size;
constraint **constraints;
size_t constraints_size;

void setup(char *path);

size_t read_file(char *path, char** result);
void parse_grid(char *grid_text, size_t text_size);
void parse_cons(char *cons_text, size_t text_size);

void show_grid();

constraint * create_constraint(function f, unsigned size, int * array);

bool compareSuperiority(unsigned first, unsigned second);
bool compareDifference(unsigned first, unsigned second);

#endif // COMMON_H
