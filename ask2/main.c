#include <stddef.h>
#include <stdlib.h>
#include "mystring.h"
#include <stdio.h>

int main(void){
	char test1[]={"2355"};
    char *test2;
    char *test3;

   
    test2 = (char*)malloc(4*sizeof(char));
    test3 = (char*)malloc(10*sizeof(char));
		
        
    test2="1234";
    test3="1032355890";
    printf("Testing ms_length\n");
    if (4==ms_length(test1))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    if (4==ms_length(test2))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    if (10==ms_length(test3))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    if (0==ms_length(""))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    

    
    printf("Testing ms_compare and ms_copy at the same time\n");
    
    ms_copy(test1,test2);
    
    if (0==ms_compare(test1,"1234"))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    
	ms_copy(test1,"");
    
    if (0==ms_compare(test1,""))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }

    

    printf("Testing ms_ncompare and ms_ncopy at the same time\n");
    
    ms_ncopy(test1,"1234",2);
    if (0==ms_ncompare(test1,"1234",2))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }

    ms_ncopy(test1,"0acb",4);
    if (0==ms_ncompare(test1,"0acb",4))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
	
    printf("Testing ms_concat\n");

    ms_copy(test1,"1");
    ms_concat(test1,"123");

    if (0==ms_compare(test1,"1123"))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    
    ms_copy(test1,"1");
    ms_concat(test1,"");

    if (0==ms_compare(test1,"1"))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    
    printf("Testing nconcat\n");
    
    ms_copy(test1,"1");
    ms_nconcat(test1,"123",1);

    if (0==ms_compare(test1,"11"))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }

    ms_copy(test1,"1");
    ms_nconcat(test1,"123123123123124354214312425",3);

    if (0==ms_compare(test1,"1123"))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }

    printf("Testing ms_search \n");
    ms_copy(test1,"3235");
    test2=ms_search(test3,test1);

     if (0==ms_compare(test2,"32355890"))
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }

    ms_copy(test1,"666");
    test2=ms_search(test3,test1);

    

    if (test2==NULL)
    {
        printf("\033[0;32m");
        printf("PASS\n");
        printf("\033[0;0m");
    }
    else{
        printf("\033[0;31m");
        printf("FAIL\n");
        printf("\033[0;0m");
    }
    
    
    return 0;



} 