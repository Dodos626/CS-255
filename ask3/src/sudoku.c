#include "sudoku.h"
#include <string.h>
/*CUSTOM FUNCTIONS*/
int check_row_errors(Grid_T g, int i);
int check_collumn_errors(Grid_T g, int i);
int check_boxes_errors(Grid_T g);
int check_row_errors_no_print(Grid_T g, int i);
int check_collumn_errors_no_print(Grid_T g, int i);
int check_boxes_errors_no_print(Grid_T g);
void sudoku_init_choices(Grid_T *g);
static int next_choice(Grid_T g, int *i, int *j);
void eliminate_choice(Grid_T *g, int i, int j, int n);
int sudoku_update_choice(Grid_T *g, int i, int j, int n);
static Grid_T sudoku_generate_complete(void);
Grid_T sudoku_generate(int nelts);
/*END OF DECLARATION OF CUSTOM FUNCTIONS*/

int main(int argc, char **argv)
{
    Grid_T unsolved, solved;
   
    srand(getpid());
    switch (argc)
    {
    case 1: /*case one no arguments given*/
        unsolved = sudoku_read();
        sudoku_print(stderr, unsolved);
        solved = sudoku_solve(unsolved);
        if (sudoku_solution_is_unique(solved))
        {
            fprintf(stderr, "Solution is unique\n");
        }
        else
        {
            fprintf(stderr, "Solution is not unique\n");
        }
        sudoku_print(stdout, solved);
        break;
    case 2: /*case 2 -c given*/
        if (strcmp(argv[1], "-c") == 0)
        {
            unsolved = sudoku_read();
            sudoku_print(stderr, unsolved);
            if (sudoku_is_correct(unsolved))
            {
                fprintf(stderr, "Puzzle is correct\n");
            }
            else
            {
                fprintf(stderr, "Puzzle is not correct\n");
                sudoku_print_errors(unsolved);
            }
        }
        else
        {
            fprintf(stderr, "ERROR\n");
        }

        break;
    case 3: /*case 3 -g given and a number for the nelts*/
        if (strcmp(argv[1], "-g") == 0 && atoi(argv[2])<82 && atoi(argv[2])>-1)
        {
            unsolved = sudoku_generate(atoi(argv[2]));
            sudoku_print(stdout,unsolved);
        }else{
             fprintf(stderr, "ERROR\n");
        }
    case 4: /*case 4 -g and nelts number given + unique choice requested*/
        if (strcmp(argv[1], "-g") == 0 && atoi(argv[2])<82 && atoi(argv[2])>-1 && strcmp(argv[3], "-u") == 0)
        {
            int nelts = 0;
            int odiseas = 0;
            unsolved = sudoku_generate(atoi(argv[2]));
            solved = sudoku_solve(unsolved);
            while (!sudoku_solution_is_unique(solved))
            {
                
                unsolved = sudoku_generate(atoi(argv[2])+nelts);
                solved = sudoku_solve(unsolved);
                odiseas++;
                if (odiseas==10)/*every 10 tries at finding a unique puzzle with user given nelts*/
                {               /*make the nelts +1*/
                    odiseas=0;
                    nelts++;
                }
                
            }
            if (nelts > 0)  /*if the nelts were raised by programm print number*/
            {
               printf("to achieve unique solution %d nelts were added\n",nelts);
            }
            
            
            
            sudoku_print(stdout,unsolved);
        }else{
             fprintf(stderr, "ERROR\n");
        }
        break;
    default:
        fprintf(stderr, "ERROR\n");
        break;
    }

    return 0;
}

Grid_T sudoku_read(void)
{
    Grid_T to_ret;
    int n, i, j;
    int total_num_given;
    char c;
    total_num_given = 0;
    i = 0;
    j = 0;

    while ((c = getchar()) != EOF && total_num_given < 81)
    {
        /*if end of line goes to next grid row of sudoku*/
        if (c == '\n')
        {
            i++;
            j = 0;
            continue;
        }
        /*if it is a digit it stores it and continues*/
        /*if the ascii code is 48-57 then it belongs from 0 to 9 */
        if (c != ' ' && c != '\n')
        {
            n = ((int)c) - 48; /*convert from string to int */

            if (n > 9 || n < 0)
            {
                printf("Number %d not valid\n", n);
                exit(EXIT_FAILURE);
            }
            grid_update_value(&to_ret, i, j, n);

            if (n == 0) /* initialize 9 choices if the cell is 0 */
            {
                grid_set_count(&to_ret, i, j);
            }
            else
            {
                grid_clear_count(&to_ret, i, j);
            }

            j++;
            total_num_given++;
        }
    }
    if (total_num_given != 81)
    {
        printf("Wrong total of numbers given\n");
        exit(EXIT_FAILURE);
    }
    grid_set_unique(&to_ret);
    sudoku_init_choices(&to_ret);
    return to_ret;
}

void sudoku_print(FILE *s, Grid_T g)
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            fprintf(s, "%d ", grid_read_value(g, i, j));
        }
        fprintf(s, "\n");
    }
    return;
}

void sudoku_print_errors(Grid_T g)
{

    int i = 0;

    for (i = 0; i < 9; i++)
    {
        check_row_errors(g, i);
        check_collumn_errors(g, i);
    }
    check_boxes_errors(g);
}
int check_row_errors(Grid_T g, int i)
{
    int flag = 1;
    int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int j; /*to parse the row one by one*/
    int n; /*to hold the value of the cell to be checked*/
    for (j = 0; j < 9; j++)
    {
        n = grid_read_value(g, i, j);
        if (n == 0) /*if n == 0 then we go into the next one ignoring the 0 */
        {
            continue;
        }
        if (check[n - 1] == 0)
        {
            fprintf(stderr, "Error in row %d , number %d already exists \n", i + 1, n);
            flag = 0;
        }
        else
        {
            check[n - 1] = 0;
        }
    }
    return flag;
}
int check_collumn_errors(Grid_T g, int i)
{
    int flag = 1;
    int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int j; /*to parse the collumn one by one*/
    int n; /*to hold the value of the cell to be checked*/
    for (j = 0; j < 9; j++)
    {
        n = grid_read_value(g, j, i);
        if (n == 0) /*if n == 0 then we go into the next one ignoring the 0 */
        {
            continue;
        }
        if (check[n - 1] == 0)
        {
            fprintf(stderr, "Error in collumn %d , number %d already exists \n", i + 1, n);
            flag = 0;
        }
        else
        {
            check[n - 1] = 0;
        }
    }
    return flag;
}
int check_boxes_errors(Grid_T g)
{
    int flag = 1;
    int n; /*to hold the value of the cell to be checked*/
    int i; /*to hold the row */
    int j; /*to hold the collumn*/
    int a; /*to change the row of the starting box*/
    int b; /*to change the collumn of the starting box*/

    /*the whole concept is to break down the i and j into 3x3 grid*/
    /*so i can check every box individually*/
    /*that is achieved by making a and b go up by 3 (3x3 boxes) */
    /*and adding all combinations into the 2 for loops with i and j*/
    /*so i can create the 0,0 0,3 0,6 3,0 3,3 boxes etx*/

    for (a = 0; a < 9; a = a + 3)
    {
        for (b = 0; b < 9; b = b + 3)
        {
            int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (i = 0 + a; i < 3 + a; i++)
            {
                for (j = 0 + b; j < 3 + b; j++)
                {
                    n = grid_read_value(g, i, j);
                    if (n == 0) /*if n == 0 then we go into the next one ignoring the 0 */
                    {
                        continue;
                    }
                    if (check[n - 1] == 0)
                    {
                        fprintf(stderr, "Error in box %d %d , number %d already exists \n", a / 3 + 1, b / 3 + 1, n);
                        flag = 0;
                    }
                    else
                    {
                        check[n - 1] = 0;
                    }
                }
            }
        }
    }
    return flag;
}

/*returns 1 if puzzle is finished and correct otherwise 0*/
int sudoku_is_correct(Grid_T g)
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        if (!check_row_errors_no_print(g, i) || !check_collumn_errors_no_print(g, i))
        {
            return 0;
        }
    }
    if (!check_boxes_errors_no_print(g))
    {
        return 0;
    }

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (grid_read_value(g, i, j) == 0 && grid_read_count(g, i, j) == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}
int check_row_errors_no_print(Grid_T g, int i)
{
    int flag = 1;
    int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int j; /*to parse the row one by one*/
    int n; /*to hold the value of the cell to be checked*/
    for (j = 0; j < 9; j++)
    {
        n = grid_read_value(g, i, j);
        if (n == 0) /*if n == 0 then we go into the next one ignoring the 0 */
        {
            continue;
        }
        if (check[n - 1] == 0)
        {

            flag = 0;
        }
        else
        {
            check[n - 1] = 0;
        }
    }
    return flag;
}
int check_collumn_errors_no_print(Grid_T g, int i)
{
    int flag = 1;
    int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int j; /*to parse the collumn one by one*/
    int n; /*to hold the value of the cell to be checked*/
    for (j = 0; j < 9; j++)
    {
        n = grid_read_value(g, j, i);
        if (n == 0) /*if n == 0 then we go into the next one ignoring the 0 */
        {
            continue;
        }
        if (check[n - 1] == 0)
        {

            flag = 0;
        }
        else
        {
            check[n - 1] = 0;
        }
    }
    return flag;
}
int check_boxes_errors_no_print(Grid_T g)
{
    int flag = 1;
    int n; /*to hold the value of the cell to be checked*/
    int i; /*to hold the row */
    int j; /*to hold the collumn*/
    int a; /*to change the row of the starting box*/
    int b; /*to change the collumn of the starting box*/

    /*the whole concept is to break down the i and j into 3x3 grid*/
    /*so i can check every box individually*/
    /*that is achieved by making a and b go up by 3 (3x3 boxes) */
    /*and adding all combinations into the 2 for loops with i and j*/
    /*so i can create the 0,0 0,3 0,6 3,0 3,3 boxes etx*/

    for (a = 0; a < 9; a = a + 3)
    {
        for (b = 0; b < 9; b = b + 3)
        {
            int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (i = 0 + a; i < 3 + a; i++)
            {
                for (j = 0 + b; j < 3 + b; j++)
                {
                    n = grid_read_value(g, i, j);
                    if (n == 0) /*if n == 0 then we go into the next one ignoring the 0 */
                    {
                        continue;
                    }
                    if (check[n - 1] == 0)
                    {
                        flag = 0;
                    }
                    else
                    {
                        check[n - 1] = 0;
                    }
                }
            }
        }
    }
    return flag;
}

Grid_T sudoku_solve(Grid_T g)
{

    int i, j, n, choice;

    Grid_T tmp, solved;
    sudoku_init_choices(&g);
    if (sudoku_is_correct(g) == 0) /*if it is correct and solved it returns it*/
    {
        grid_clear_unique(&g);
        return g;
    }
    /*finds the next choice and holds the i,j*/
    /*when there are no choices n==0 and while will brake*/
    n = next_choice(g, &i, &j);

    while (n)
    {

        choice = sudoku_update_choice(&g, i, j, n); /*finds the number of choices available to check for unique*/

        if (choice == 0) /*if unique choice for this cell*/
        {
            grid_update_value(&g, i, j, n); /*and updates it self*/
            grid_clear_count(&g, i, j);     /*clears the count from the cell coz it now contains a number*/

            eliminate_choice(&g, i, j, n); /*if choice is unique then it removes it from all other cells*/
            if (sudoku_is_correct(g) == 0) /*if it is correct and solved it returns it*/
            {
                return g;
            }
        }
        else
        {
            grid_clear_unique(&g);            /*more than one paths to go so it isnt unique*/
            tmp = g;                          /*tmp = g to initiate reccursion*/
            grid_update_value(&tmp, i, j, n); /*puts the n in the tmp grid */
            grid_clear_count(&tmp, i, j);     /*clears the count from the cell coz it now contains a number*/

            solved = sudoku_solve(tmp);    /*reccursively tries to solve the tmp*/
            if (sudoku_is_correct(solved)) /*if it is correct and solved it returns it*/
            {
                g = solved;
            }
            else
            { /* If we didn't make the right choice, we go back to zero 
            (and the value we chose is already opted-out for the specific cell) */
                grid_update_value(&g, i, j, 0);
            }
        }

        n = next_choice(g, &i, &j);
    }

    return g;
}

void sudoku_init_choices(Grid_T *g)
{
    int i, k, j;

    int n; /*to hold the value of the cell to be checked*/
    /* i to hold the row */
    /*j to hold the collumn*/
    int a; /*to change the row of the starting box*/
    int b; /*to change the collumn of the starting box*/
    /*k to change the check board */
    /*the whole concept is to break down the i and j into 3x3 grid*/
    /*so i can check every box individually*/
    /*that is achieved by making a and b go up by 3 (3x3 boxes) */
    /*and adding all combinations into the 2 for loops with i and j*/
    /*so i can create the 0,0 0,3 0,6 3,0 3,3 boxes etx*/

    for (i = 0; i < 9; i++) /*for every row*/
    {
        for (k = 0; k < 9; k++) /*for every cell in that row */
        {
            if (g->elts[i][k].val != 0) /*if it isnt a 0*/
            {
                for (j = 0; j < 9; j++) /*go into every cell from the beginning of the row*/
                {
                    grid_remove_choice(g, i, j, g->elts[i][k].val); /*and remove the number u found at i,k*/
                    grid_remove_choice(g, j, k, g->elts[i][k].val); /*same for the k'th column*/
                }
            }
        }
    }

    for (a = 0; a < 9; a = a + 3)
    {
        for (b = 0; b < 9; b = b + 3)
        {
            int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (i = 0 + a; i < 3 + a; i++)
            {
                for (j = 0 + b; j < 3 + b; j++)
                {

                    n = grid_read_value(*g, i, j);

                    if (n == 0) /*if n == 0 then we go into the next one ignoring the 0 */
                    {
                        continue;
                    }
                    check[n - 1] = 0;
                }
            }

            for (k = 0; k < 9; k++)
            {
                if (check[k] == 0)
                {

                    for (i = 0 + a; i < 3 + a; i++)
                    {
                        for (j = 0 + b; j < 3 + b; j++)
                        {
                            grid_remove_choice(g, i, j, k + 1);
                        }
                    }
                }
            }
        }
    }
}

/*returns randomly one of the lowest count cell*/
/*if there is no cell available then returns 0*/
static int next_choice(Grid_T g, int *i, int *j)
{
    int a, b, c, min_choice, check_choice, k;
    min_choice = 10; /* needs to be bigger than 9*/

    for (a = 0; a < 9; a++)
    {
        for (b = 0; b < 9; b++)
        {

            check_choice = grid_read_count(g, a, b);

            if (check_choice > 0 && check_choice < min_choice) /*search for the least */
            {                                                  /*choice of counts */
                min_choice = check_choice;
            }
        }
    }

    while (min_choice != 10) /*checks if the min choice is <10 coz if ==10 there are no other choices*/
    {
        a = rand() % 9; /*takes two random cordinates for the cell*/
        b = rand() % 9;
        c = grid_read_count(g, a, b); /*reads the count of choices of this cell*/
        if (c == min_choice)          /*if the cell count == min_choice*/
        {

            for (k = 1; k <= 9; k++)
            { /* Find the proper value for the chosen cell */
                if (grid_choice_is_valid(g, a, b, k))
                {
                    *i = a;
                    *j = b;
                    return k;
                }
            }
        }
    }
    return 0;
}
/*that was put in the cell i , j */
void eliminate_choice(Grid_T *g, int i, int j, int n)
{
    int k, l;
    for (k = 0; k < 9; k++)
    {
        grid_remove_choice(g, i, k, n); /* remove from the whole row */
        grid_remove_choice(g, k, j, n); /* and the collumn */
    }
    /* find the the 3x3 square area with a formula found online*/
    for (k = (i / 3) * 3; k < (i / 3) * 3 + 3; k++)
    {
        for (l = (j / 3) * 3; l < (j / 3) * 3 + 3; l++)
        {
            grid_remove_choice(g, k, l, n); /* remove from the 3x3 square area */
        }
    }
}

/*removes from the grid the n*/
/*updates the value and returns the count of choices*/
int sudoku_update_choice(Grid_T *g, int i, int j, int n)
{
    grid_remove_choice(g, i, j, n);

    return grid_read_count(*g, i, j);
}

/*generates a solved sudoku at random or a default one if it takes too long*/
static Grid_T sudoku_generate_complete(void)
{
    Grid_T g, to_ret;
    int i, j, count;
    int if_fail[9][9] = {/*IF THE WaILE LOOP FAILS*/
                         {5, 3, 6, 9, 1, 4, 2, 8, 7},
                         {2, 4, 7, 5, 8, 3, 1, 9, 6},
                         {9, 1, 8, 6, 2, 7, 5, 4, 3},
                         {8, 2, 3, 7, 5, 1, 4, 6, 9},
                         {4, 9, 5, 3, 6, 2, 8, 7, 1},
                         {6, 7, 1, 8, 4, 9, 3, 5, 2},
                         {7, 6, 2, 4, 3, 8, 9, 1, 5},
                         {1, 8, 9, 2, 7, 5, 6, 3, 4},
                         {3, 5, 4, 1, 9, 6, 7, 2, 8}};
    count = 0;
    while (count != 1000)   /*give it some tries AKA 1000*/
    {
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                grid_update_value(&g, i, j, 0); /*value == 0 */
                grid_set_count(&g, i, j);
            }
        }

        to_ret = sudoku_solve(g);   /*trying to solve it */
        count++;
        if (sudoku_is_correct(to_ret)) /*if its correct return it else count ++ back in the loop */
        {
            grid_set_unique(&to_ret);
            return to_ret;
        }
    }

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            grid_update_value(&g, i, j, if_fail[i][j]); /*if generate fails or takes too long*/
            grid_clear_count(&g,i,j);                   /*return a default grid*/
        }
    }
    grid_set_unique(&g);
    return g;
}

/*generates one random sudoku with x=nelts empty cells*/
Grid_T sudoku_generate(int nelts)
{
    Grid_T g = sudoku_generate_complete();  /*generate a solved one*/
    int i, a, b;
    
    for (i = 0; i < 81 - nelts; i++)        
    {
        a = rand() % 9;
        b = rand() % 9;
        while (grid_read_value(g, a, b) == 0)   /*if there isnt a number at the random position*/
        {
            a = rand() % 9; /*try other cordinates*/
            b = rand() % 9;
        }
        grid_update_value(&g, a, b, 0); /*make the value 0 */
        grid_set_count(&g, a, b);   /*and set the count to 9*/
    }

    return g;
}

/*self ecplatno*/
int sudoku_solution_is_unique(Grid_T g)
{
    return grid_read_unique(g);
}

/*theodoros chalkidis csd4198 2021*/
/*never again*/