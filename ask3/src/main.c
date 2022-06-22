#include <stdio.h>
#include <stdlib.h>
#include "SymTable.h"
int main(){
	SymTable_T p;
	void *d,*q;
	char *key;
	int i;
	key="dd";
	d="aa";
	p=SymTable_new();
	i=SymTable_put(p,key,d);
	printf("put must print 1 here      :%d\n",i);
	key="aa";
	i=SymTable_put(p,key,d);
	printf("put must print 1 here      :%d\n",i);
	i=SymTable_getLength(p);
	printf("length must print 2 here   :%d\n",i);
	i=SymTable_contains(p,key);
	printf("contains must print 1 here :%d\n",i);
	q=SymTable_get(p,key);
	printf("get must print ''aa'' here :%s\n",(char *)q);
	i=SymTable_remove(p,key);
	printf("remove must print 1 here   :%d\n",i);
	i=SymTable_getLength(p);
	printf("length must print 1 here   :%d\n",i);
	i=SymTable_contains(p,key);
	printf("contains must print 0 here :%d\n",i);
	q=SymTable_get(p,key);
	printf("get must print NULL here   :%s\n",(char*)q);
	SymTable_free(p);
	return 0;
 
}
