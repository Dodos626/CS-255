#include <stdio.h>
#include <assert.h>
#include "mystring.h"

/*returns the length of the string array*/
/*it checks if the array is NULL*/
size_t ms_length(const char array[]){
	int i;
	i=0;
	assert(array!=NULL);
		while(array[i]!='\0'){
			i++;
		}
		return i;
}
/*copies string of array1 to the string of array2 */
/*checks if array1 and array2 are NULL*/
char* ms_copy(char array2[],const char array1[]){
	int i;
	assert(array1!=NULL);
	assert(array2!=NULL);
	i=0;
	while(array1[i]!='\0'){
		array2[i]=array1[i];
		i++;
	}
	array2[i]='\0';
	return 0;
}
/*copies up to n char from string array1 to string array2*/
/*checks if array1 and array2 are NULL*/
char* ms_ncopy(char array2[],const char array1[],size_t n){
	int i;
	assert(array1!=NULL);
	assert(array2!=NULL);
	i=0;
	while((array1[i]!='\0')&&(i<n)){
		array2[i]=array1[i];
		i++;
	}
	array2[i]='\0';
	return 0;
}
/*copies the string of array1 to the end of string array2*/
/*checks if array1 and array2 are NULL*/
char* ms_concat(char array2[], const char array1[]){
	int i,x;
	assert(array1!=NULL);
	assert(array2!=NULL);
	x = ms_length(array2);
	i=0;
	while(array1[i]!='\0'){
		array2[i+x]=array1[i];
		i++;
	}
	array2[x+i]='\0';
	return 0;
}
/*copies up to the n char of string array1 to the end of string array2*/
/*checks if array1 and array 2 are NULL*/
char* ms_nconcat(char array2[], const char array1[], size_t n){
	int i,x;
	assert(array1!=NULL);
	assert(array2!=NULL);
	x= ms_length(array2);
	i=0;
	while((array1[i]!='\0')&&(i<n)){
		array2[i+x]=array1[i];
		i++;
	}
	array2[x+i]='\0';
	return 0;
}
/*returns 0 if string of array2 is the same as string of array1*/
/*returns -1 if string of array2 is bigger than string of array1*/
/*returns 1 if string of array2 is smaller than string of array1*/
/*it checks if array2 and array1 are NULL*/
int ms_compare(const char array2[],const char array1[]){
	int x;
	assert(array1!=NULL);
	assert(array2!=NULL);
	x=0;
	if(ms_length(array2)<ms_length(array1)){
		return -1;
	}else if (ms_length(array2)>ms_length(array1)){
		return 1;
	}else{
		while(array1[x]!='\0'){
			if(array1[x]!=array2[x]){
				return -1;
			}
			x++;
		}
	}
	return 0;
}
/*returns 0 if the first n chars of both string array1 and array2 are the same*/
/*returns -1 if the first n chars of both string array1 and array2 are not the same*/
/*it checks if array2 and array1 are NULL*/
int ms_ncompare(const char array2[],const char array1[],size_t n){
	int i,x;
	assert(array1!=NULL);
	assert(array2!=NULL);
	x=ms_length(array2);
	i=0;
	
	
	if((x-n)<0){
		return -1;
	}else{
		while(array1[i]!='\0'&&i<n){
			if(array1[i]!=array2[i]){
				return -1;
			}
			i++;
		}
	}
	return 0;
}
/*searchers string of array1 inside the string of array2 and*/
/*returns a pointer to a position in array2 where array1 is found*/
/*or returns a NULL pointer if it cant be found*/
/*it checks if array2 and array1 are NULL*/
char* ms_search(char array2[],const char array1[]){
	int i,j,needle_size,haystack_size,flag;
	char *p;
	assert(array1!=NULL);
	assert(array2!=NULL);
	needle_size=ms_length(array1);
	haystack_size=ms_length(array2);
	i=0;
	p=NULL;
	while(array2[i]!='\0'){
		flag=1;
		if((haystack_size - i)< needle_size){
			p=NULL;
			return p;
		}
		for(j=0;j<needle_size;j++){
			if(array2[j+i]!=array1[j]){
				flag=0;
				break;
			}
		}
		if(flag==1){
			p= (char *) &array2[i];
			
			 
			return p;
		}
		i++;		
	}
	return NULL;
}	
