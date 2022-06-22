#include <stdio.h>
#include <assert.h>
#include "mystring.h"
/*returns the length of the string array*/
/*it checks if the array is NULL*/
size_t ms_length(const char *ptrpc) {

   size_t uiLength = 0U;

   assert(ptrpc != NULL);

   while (*(ptrpc + uiLength) != '\0'){
		uiLength++;
   }
   return uiLength;
}
/*copies string of array1 to the string of array2 */
/*checks if array1 and array2 are NULL*/
char* ms_copy(char *ptr2,const char *ptr1){
	char *tmp=ptr2;
	
	assert(ptr2 !=NULL);
	assert(ptr1 !=NULL);
	while(*ptr1!='\0'){
		*tmp=*ptr1;
		tmp++;
		ptr1++;
	}
	
	*tmp='\0';
	return ptr2;
}
/*copies up to n char from string array1 to string array2*/
/*checks if array1 and array2 are NULL*/
char* ms_ncopy(char *ptr2,const char *ptr1,size_t n){
	char *start=ptr2;
	int i=0;
	assert(ptr2!=NULL);
	assert(ptr1!=NULL);
	while((*ptr1!='\0')&&(i<n)){
		*ptr2=*ptr1;
		ptr2++;
		ptr1++;
		i++;
	}
	*ptr2='\0';
	return start;
}
/*copies the string of array1 to the end of string array2*/
/*checks if array1 and array2 are NULL*/
char* ms_concat(char *ptr2,const char *ptr1){
	size_t x;
	char *start=ptr2;
	assert(ptr2!=NULL);
	assert(ptr1!=NULL);
	x=ms_length(ptr2);
	while(*ptr1!='\0'){
		*(start+x)=*ptr1;
		start++;
		ptr1++;
	}
	*(start+x)='\0';
	return ptr2;
}
/*copies up to the n char of string array1 to the end of string array2*/
/*checks if array1 and array 2 are NULL*/
char* ms_nconcat(char *ptr2,const char *ptr1,size_t n){
	size_t x;
	int i;
	char *start=ptr2;
	assert(ptr2!=NULL);
	assert(ptr1!=NULL);
	x=ms_length(ptr2);
	i=0;
	while((*ptr1!='\0')&&(i<n)){
		*(start+x)=*ptr1;
		start++;
		ptr1++;
		i++;
	}
	*(start+x)='\0';
	return ptr2;
}
/*returns 0 if string of array2 is the same as string of array1*/
/*returns -1 if string of array2 is bigger than string of array1*/
/*returns 1 if string of array2 is smaller than string of array1*/
/*it checks if array2 and array1 are NULL*/
int ms_compare(const char *ptr2,const char *ptr1){
	int l2,l1;
	assert(ptr1!=NULL);
	assert(ptr2!=NULL);
	l2=ms_length(ptr2);
	l1=ms_length(ptr1);
	if(l2<l1){
		return -1;
	}else if(l1<l2){
		return 1;
	}else{
		while(*ptr1!='\0'){
			if(*ptr2!=*ptr1){
				return -1;
			}
			ptr1++;
			ptr2++;
		}
	}
	return 0;
}
/*returns 0 if the first n chars of both string array1 and array2 are the same*/
/*returns -1 if the first n chars of both string array1 and array2 are not the same*/
/*it checks if array2 and array1 are NULL*/
int ms_ncompare(const char *ptr2,const char *ptr1,size_t n){
	int l2,i=0;
	assert(ptr1!=NULL);
	assert(ptr2!=NULL);
	l2=ms_length(ptr2);
	if((l2-n)<0){
		return -1;
	}else{
		while((*ptr1!='\0')&&(i<n)){
				if(*ptr1!=*ptr2){
					return -1;
					}
				ptr1++;
				ptr2++;
				i++;
		}
	}
	return 0;
}
/*searchers string of array1 inside the string of array2 and*/
/*returns a pointer to a position in array2 where array1 is found*/
/*or returns a NULL pointer if it cant be found*/
/*it checks if array2 and array1 are NULL*/
char* ms_search(char *ptr2, const char *ptr1)
  {
      const char *position, *tmp;
      assert(ptr2 && ptr1);
      while(*ptr2 != '\0')
        {
            if(*ptr2 == *ptr1)
              {
                 position = ptr2;
                 tmp = ptr1;
                 for(;*tmp != '\0' ; position++,tmp++)
                   {
                       if(*position != *tmp) break;
                   }
                 if(*tmp == '\0' )
                   {
                      return ptr2;
                   }
              }
            ptr2++;
        }
      return NULL;
  }
