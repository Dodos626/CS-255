#include "grid.h"
#include <assert.h>

/* update value of i,j to n */
void grid_update_value ( Grid_T *g, int i, int j, int n){
    assert(g);
    assert((n>=0 && n<10)&&(j>=0 && j<9)&&(i>=0 && i<9));
    g->elts[i][j].val = n;
    return;
}
/* return value of i,j */
int grid_read_value(Grid_T g, int i, int j){
    
    assert((j>=0 && j<9)&&(i>=0 && i<9));
    return g.elts[i][j].val;
}
/* set (to 1)  choice n for elt i,j */
void grid_set_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert((j>=0 && j<9)&&(i>=0 && i<9));
    if (g->elts[i][j].choices.num[n] == 0)
        g->elts[i][j].choices.count++;
    g->elts[i][j].choices.num[n] = 1;
}
/* clear (to 0) choice n for elt i,j DOESN'T MAKE UPDATE COUNT*/
void grid_clear_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert((j>=0 && j<9)&&(i>=0 && i<9));
    g->elts[i][j].choices.num[n]=0;
}
/* true (1) if choice n for elt i,j is valid */
int grid_choice_is_valid(Grid_T g, int i, int j, int n){
    
    assert((n>=0 && n<10)&&(j>=0 && j<9)&&(i>=0 && i<9));
    return (g.elts[i][j].choices.num[n]);
}
/* remove n from choices of elt i,j and adjust count only if n is a
   valid choice for elt i,j */
void grid_remove_choice(Grid_T *g, int i, int j, int n){
    if (grid_choice_is_valid(*g,i,j,n))
    {
        grid_clear_choice(g,i,j,n);
        g->elts[i][j].choices.count--;
    }
}
/* return count */
int grid_read_count(Grid_T g, int i, int j){
    
    assert((j>=0 && j<9)&&(i>=0 && i<9));
    return g.elts[i][j].choices.count;
}
/*set (to 9) count for elt i, j */
void grid_set_count(Grid_T *g, int i, int j){
    int k ;
    assert(g);
    assert((j>=0 && j<9)&&(i>=0 && i<9));
    g->elts[i][j].choices.count = 9;
    g->elts[i][j].choices.num[0] = 0;
    for (k = 1; k <= 9; k++)
        g->elts[i][j].choices.num[k] = 1;
}
/*clear (to 0) count for elt i, j */
void grid_clear_count(Grid_T *g, int i, int j){
    int k;
    assert(g);
    assert((j>=0 && j<9)&&(i>=0 && i<9));
    g->elts[i][j].choices.count = 0;
    for (k = 0; k <= 9; k++)
        g->elts[i][j].choices.num[k] = 0;
}
/* return val*/
int grid_read_unique(Grid_T g){
    
    return g.unique;
}
/*set (to 1) unique flag for g */
void grid_set_unique(Grid_T *g){
    assert(g);
    g->unique=1;
}
/*clear (to 0) unique flag for g */
void grid_clear_unique(Grid_T *g){
    assert(g);
    g->unique=0;
}