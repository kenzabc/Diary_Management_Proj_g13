//
// Created by kenza on 10/12/2023.
//

#include "cell.h"
#include <stdlib.h>
#include <stdio.h>

// level cells, with the following functions:
//• Create a cell: enter its value and the number of levels in the cell to obtain a pointer to the cell.
t_cell *create_cell(int value, int max_value){
    t_cell *cell = (t_cell *)malloc(sizeof(t_cell)); // Corrected line
    cell->max_level = max_value;
    cell->value = value;
    cell->pointers = (t_cell **)malloc(max_value * sizeof(t_cell *));
    return cell;
}

