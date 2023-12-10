//
// Created by kenza on 10/12/2023.
//

#include "list.h"
#include "list.h"
#include "stdlib.h"
#include "stdio.h"
#include "cell.h"
// Create an empty level list: we'll give the maximum number of levels this list can have
t_list *create_list(int max_value){
    t_list *head_list = (t_list*) malloc(sizeof (t_list));
    head_list->max_level = max_value;
    head_list->heads = (t_cell **) malloc(max_value*sizeof (t_cell *));
    for (int i=0; i<max_value; i++){
        head_list->heads[i] = NULL;
    }
    return head_list;
}
//• Insert a cell with levels at the beginning (head) of the list (be careful to take into account the number of levels in the cell)
void InsertHeadList(t_list* list, t_cell *newcell, int max_value){
    for (int i=0; i<max_value; i++){
        newcell->pointers[i] = list->heads[i];
        list->heads[i] = newcell;
    }
}

//• Display all the cells in the list for a given level
void DisplayLevelList(t_list* list, int level){
    t_cell* temp = list->heads[level];
    printf("list [head_%d @-]-->", level);
    while (temp!=NULL) {
        printf("[ %d|@-]-->", temp->value);
        temp = temp->pointers[level];
    }
    printf("NULL");
}

//• Show all levels in the list
void ShowAllLevels(t_list* list){
    for (int i=0; i<list->max_level; i++){
        DisplayLevelList(list, i);
        printf("\n");
    }
}

//• Optional: display all levels of the list, by aligning the cells
//pas encore fait

//• Insert a level cell in the list, at the right place, so that the list remains sorted in
//ascending order
//For this last function, it is possible to make a 'simple' insertion at each level, starting
//from the beginning of the list, but it is possible to be more efficient - it's up to you
//to work out how.
void InsertCellInList(t_list* list, t_cell *newcell, int max_value){
    if (max_value > list->max_level) // si le niveau max de la cellule > max level de level list, alors impossible
    {
        printf("Insertion impossible, le niveau de la liste demandee est plus grande que le niveau de la liste créée\n");
        return;
    }
    else
    {
        for (int i=0; i<max_value; i++){ //on parcourt pour chaque liste chainée(celle à l'horizontal)
            t_cell *temp = list->heads[i];
            if (list->heads[i]==NULL || newcell->value < list->heads[i]->value){ //si la head pointe sur rien, alors elle va pointer sur la newcell
                newcell->pointers[i] = list->heads[i];
                list->heads[i] = newcell;
            }
            else {
                while (temp->pointers[i] != NULL && temp->pointers[i]->value < newcell->value) { //temp parcourt la liste
                    temp = temp->pointers[i];
                }
                if (temp->pointers[i] == NULL) { //si ça parcourt jusque la tail, la cellule devient la tail
                    newcell->pointers[i] = NULL;
                    temp->pointers[i] = newcell;
                }
                else {
                    newcell->pointers[i] = temp->pointers[i]; //sinon ça s'insère là où ça pourra être sorted (cas général ici)
                    temp->pointers[i] = newcell;
                }
            }
        }
    }
}


int searchValue(t_list* list, int value) {
    t_cell* current = list->heads[0]; // Start from the first level

    while (current != NULL) {
        if (current->value == value) {
            return 1; // Value found
        } else if (current->value < value) {
            current = current->pointers[0]; // Move to the next cell at the same level
        } else {
            break; // Stop searching if the current cell's value is greater than the target value
        }
    }

    return 0; // Value not found
}

int searchLevelValue(t_list* list, int value) {
    int currentLevel = list->max_level - 1; // Start from the highest level

    while (currentLevel >= 0) {
        t_cell* current = list->heads[currentLevel];

        while (current != NULL) {
            if (current->value == value) {
                return 1; // Value found
            } else if (current->value < value) {
                current = current->pointers[currentLevel]; // Move to the next cell at the same level
            } else {
                break; // Stop searching if the current cell's value is greater than the target value
            }
        }

        currentLevel--; // Move to the next lower level
    }

    return 0; // Value not found
}

t_list *createListToSearch(int maxvalue) {
    t_list *newlist = (t_list*) malloc(sizeof(t_list));
    newlist->max_level = 7; // Set the maximum level for the entire list

    int max = newlist->max_level;
    newlist->heads = (t_cell**) malloc(sizeof(t_cell*) * max);

    for (int i = 0; i < max; i++) {
        newlist->heads[i] = NULL;
    }

    for (int i = 1; i <= maxvalue; i++) {
        int currentMax = 7;  // Default maximum level
        if (i % 64 == 0) {
            currentMax = 7;
        } else if (i % 32 == 0) {
            currentMax = 6;
        } else if (i % 16 == 0) {
            currentMax = 5;
        } else if (i % 8 == 0) {
            currentMax = 4;
        } else if (i % 4 == 0) {
            currentMax = 3;
        } else if (i % 2 == 0) {
            currentMax = 2;
        } else {
            currentMax = 1;
        }

        t_cell *newcell = create_cell(i, currentMax);
        InsertCellInList(newlist, newcell, max);
    }

    return newlist;
}
