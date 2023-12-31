#include "hidden_singles.h"
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
int hidden_singles(SudokuBoard *p_board)

{
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        for(int j = 0; j < BOARD_SIZE; j ++)
        {
            int * candidates = get_candidates(&(p_board->data[i][j]));
            for(int k = 0; k < p_board->data[i][j].num_candidates; k ++)
            {
                printf("%d" , candidates[k]);
            }
            printf("\t");
        }
        printf("\n");
    }
    int hidden_single_cells_counter = 0;
    HiddenSingle hidden_single_cells[BOARD_SIZE * BOARD_SIZE];

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_single(p_board->p_rows[i], hidden_single_cells, &hidden_single_cells_counter);
        find_hidden_single(p_board->p_cols[i], hidden_single_cells, &hidden_single_cells_counter);
        find_hidden_single(p_board->p_boxes[i], hidden_single_cells, &hidden_single_cells_counter);
    }

    for(int i = 0; i < hidden_single_cells_counter; i++)
    {
        //set_candidates(hidden_single_cells[i].p_cell, &hidden_single_cells[i].value, 1);
        set_candidates(hidden_single_cells[i].p_cell, (int*)(int[]){hidden_single_cells[i].value}, 1);
    }
    return hidden_single_cells_counter;
}



// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
// cai nay la text ko dich dc nên báo lỗi, em phai comment nó
//dạ ok ạ, dich ok roi, echay debug thu xem


int find_hidden_single_values(Cell **p_cells, int *possible_values) 
{
    int number_of_hidden_singles = 0;
    int candidate_counter[BOARD_SIZE];


    for(int i = 0; i < 9; i++)
    {
        candidate_counter[i] = 0; //currently the candidate_counter = [0,0,0,0,0,0,0,0,0].
    }
     for(int i = 0; i < BOARD_SIZE; i++)
    {
         if(p_cells[i]->num_candidates > 1) //if the number of candidates of ith cell is greater than 1, then return an array of possible candidates in that row. For example num_cadidates = 3
         {
            int* candidates = get_candidates(p_cells[i]); //return an array of possible candidates, say for example 3,5,7.
            for(int j = 0; j < p_cells[i]->num_candidates; j ++) // j < 3, j = 0,1,2
            {
                candidate_counter[candidates[j] - 1] += 1; //ex j = 0, candidates[0] = 3, -> candidates[3] - 1 = 2 -> candidate_counter[2] will be set as 1. candidate_counter = [0,0,1,0,1,0,0,1,0]
            } 
            free(candidates);
         }    //free the memory of candidates array.
    }
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidate_counter[i] == 1) // i = 2,4,6
        {
            //for(int j = 0; j < BOARD_SIZE; j++)
            possible_values[number_of_hidden_singles] = i + 1;//is an array of hidden single values.
            number_of_hidden_singles += 1; 
        }
    }
    return number_of_hidden_singles;
}


bool is_in_list_hidden_single(HiddenSingle *p_array, int size, Cell *a)
{
    for (int i = 0; i < size; i++) //this size is the number of hidden single values in that hidden_single_values array.
    {
        if (p_array[i].p_cell == a) //this means if the cell contains the hidden single value is already in the array of hidden single values, then return false. It means that if the hidden_single cell is already in the row and appear one more time in an 
            return false;
    }
    return true;
}

// find hidden single cells in a row, in a collumn or in a box
void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,int *p_counter)
{
    int hidden_single_values[BOARD_SIZE];
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        hidden_single_values[i] = 0;
    
    } //an array with 9 elements
    int num_values = find_hidden_single_values(p_cells, hidden_single_values); //num_values = num_of_hidden_singles

    for(int i = 0; i < num_values; i++) 
    {
        for(int j = 0 ; j < BOARD_SIZE; j ++)
        {
            if (p_cells[j]->num_candidates > 1) //p_cells[j] is pointer to jth cell in that ith row
            {
                int *candidates = get_candidates(p_cells[j]); //candidates is an array of possible candidates in that cell
                for(int k = 0; k < p_cells[j]->num_candidates; k ++)
                {
                    if((candidates[k] == hidden_single_values[i]) && (is_in_list_hidden_single(p_hidden_singles, *p_counter, p_cells[j])) == true)
                    {    
                        p_hidden_singles[*p_counter].p_cell = p_cells[j];
                        p_hidden_singles[*p_counter].value = hidden_single_values[i];
                        // or you can write like this:
                        // p_hidden_singles[(*p_counter)] = (HiddenSingle){p_cells[j], hidden_single_values[i]};
                        (*p_counter) += 1;
                    } 
                }
                free(candidates);
            }
        }
    }
}