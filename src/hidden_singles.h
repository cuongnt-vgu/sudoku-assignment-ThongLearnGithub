#pragma once

#include "sudoku.h"

typedef struct HiddenSingle_impl
{
    Cell *p_cell; //this is a pointer to a cell
    int value;
} HiddenSingle;

// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
int find_hidden_single_values(Cell **p_cells, int *hidden_single_values); //hidden_single_values là một cái array chứa các hidden singles. Ví dụ trong row đó tìm đc 3 hidden singles là 3,5,7 thì cái hidden_single_values sẽ là [3,5,7]. Chúng ta sẽ đặt 1 cái count số lượng phần tử trong cái hidden_single_values đó. cuối cũng return cái count để lấy số lượng hidden_single_values trong tất cả các rows 

// find hidden single cells in a row, in a collumn or in a box
void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter); //tìm ra cái cell chứa hidden single đó. ví dụ hidden single value là 7 thì ta phải tìm luôn cái số 7 đó nằm ở trong cell địa chỉ hàng cột là bao nhiêu, vì mục tiêu cuối cùng hướng đến là tìm cái cell chứa hidden_single.
//Cái *p_hidden_singles này là một array của các hidden singles, tìm đc bao nhiêu hidden singles thì cứ bỏ vào trong array đó.
// find hidden single cells in a board, return the number of hidden single cells
bool is_in_list_hidden_single(HiddenSingle *p_array, int size, Cell *a);
int hidden_singles(SudokuBoard *p_board); //trả về số lượng cell chứa hidden singles trong board đó