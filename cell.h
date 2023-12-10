//
// Created by kenza on 10/12/2023.
//

#ifndef DIARY_MANAGEMENT_PROJ_G13_CELL_H
#define DIARY_MANAGEMENT_PROJ_G13_CELL_H
typedef struct s_cell
{
    int max_level;
    int value;
    struct s_cell **pointers;
} t_cell;

t_cell *create_cell(int, int);

#endif //DIARY_MANAGEMENT_PROJ_G13_CELL_H
