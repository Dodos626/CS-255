/*returns the length of the string array*/
/*it checks if the array is NULL*/
size_t ms_length(const char array[]);
/*copies string of array1 to the string of array2 */
/*checks if array1 and array2 are NULL*/
char* ms_copy(char *array2,const char* array1);
/*copies up to n char from string array1 to string array2*/
/*checks if array1 and array2 are NULL*/
char* ms_ncopy(char *array2,const char *array1,size_t n);
/*copies the string of array1 to the end of string array2*/
/*checks if array1 and array2 are NULL*/
char* ms_concat(char *array2,const char *array1);
/*copies up to the n char of string array1 to the end of string array2*/
/*checks if array1 and array 2 are NULL*/
char* ms_nconcat(char *array2,const char* array1,size_t n);
/*returns 0 if string of array2 is the same as string of array1*/
/*returns -1 if string of array2 is bigger than string of array1*/
/*returns 1 if string of array2 is smaller than string of array1*/
/*it checks if array2 and array1 are NULL*/
int ms_compare(const char *array2,const char *array1);
/*returns 0 if the first n chars of both string array1 and array2 are the same*/
/*returns -1 if the first n chars of both string array1 and array2 are not the same*/
/*it checks if array2 and array1 are NULL*/
int ms_ncompare(const char *array2,const char *array1, size_t n);
/*searchers string of array1 inside the string of array2 and*/
/*returns a pointer to a position in array2 where array1 is found*/
/*or returns a NULL pointer if it cant be found*/
/*it checks if array2 and array1 are NULL*/
char* ms_search(char *array2,const char *array1);
