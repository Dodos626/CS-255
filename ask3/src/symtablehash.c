#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "SymTable.h"
#define HASH_MULTIPLIER 65599
SymTable_T SymTable_newnode(void);
void SymTable_freenode(SymTable_T oSymTable);
unsigned int SymTable_getLengthnode(SymTable_T oSymTable);
typedef struct SymTable{
	char *key;
	void *value;
	struct SymTable *p2next;
}STable;
/* hash function */
static unsigned int SymTable_hash(const char *pcKey){
	size_t ui;
        unsigned int uiHash = 0U;
        for (ui = 0U; pcKey[ui] != '\0'; ui++){
            uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	}
	return (uiHash%509);
}
/*arxikopoiisi tou symtable */
/*san pinakas p perixei listes */
SymTable_T SymTable_new(void){
	SymTable_T hashtable;
	int i;
	hashtable=(SymTable_T)malloc(509*sizeof(STable));
	for(i=0;i<509;i++){
		hashtable[i].key = (char*)malloc(6*sizeof(char));
		strcpy(hashtable[i].key, "dummy");
		hashtable[i].p2next=NULL;
	}
	return hashtable;
}
/* exw tin free node p tha tin kalesw gia kathe */
/* thesi ston pinaka kai sto telos kai ton pinaka */
void SymTable_free(SymTable_T oSymTable){
	int i;
	assert(oSymTable!=NULL);
	for(i=0;i<509;i++){
		SymTable_freenode(&oSymTable[i]);
	}
	free(oSymTable);
}
/*mpainei se kathe lista kai kanei free */
/*apo to telos stin arxi */
void SymTable_freenode(SymTable_T oSymTable){
	assert(oSymTable!=NULL);
	if(oSymTable->p2next!=NULL){
		SymTable_freenode(oSymTable->p2next);
	}
	/* 2021 allagi
	if(strcmp(oSymTable->key,"dummy")!=0){
	free(oSymTable);	
	}
	*/
	
	if (strcmp(oSymTable->key,"dummy")!=0)
	{
		free(oSymTable->key);
		free(oSymTable);
	}else{
		free(oSymTable->key);
	}
	
	
}

/* psaxnw gia an iparxei to pcKey */
/* an iparxei return 0 alliws dimiourgw */
/* kai epistrefw 1 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
	SymTable_T p,prev;
	int i,position;
	char *klidi;
	assert(pcKey!=NULL);
	assert(oSymTable!=NULL);
	/* psaxnw mono sto keli pou */
	/* antistoixei sto hash toy key p psaxnw */
	position=SymTable_hash(pcKey);
	oSymTable=&oSymTable[position];
	prev=oSymTable;
	if(oSymTable->p2next!=NULL){
		while(oSymTable!=NULL){
			if(strcmp(pcKey,oSymTable->key)==0){
				/*vrethike to key*/
				return 0;
			}
			prev=oSymTable;
			oSymTable=oSymTable->p2next;
		}
	}		
	/*den vrethike */
	i=strlen(pcKey) + 1;
	klidi=malloc(i*sizeof(char));
	strcpy(klidi,pcKey);
	/* ftiaxnw to neo node */
	/* kai vazw mesa ta stoixeia */
	p=SymTable_newnode();
	p->key=(char *)klidi;
	p->value=(void *)pvValue;
	
	prev->p2next=p;
	return 1;
}
/*gia kathe mia thesi tou pinaka tha kalesei */
/*tin getlenghtnode kai tha epistrepsei to sinoliko */
/*poso agnowontas ta nodes me key dump */
unsigned int SymTable_getLength(SymTable_T oSymTable){
	int i=0;
	int j=0;
	assert(oSymTable!=NULL);
	for(i=0;i<509;i++){
		j=j+SymTable_getLengthnode(&oSymTable[i]);
	}
	return j;
}

/*pairnei to megethos gia kathe thesi tou pinaka */
unsigned int SymTable_getLengthnode(SymTable_T oSymTable){
	int i=0;
	assert(oSymTable!=NULL);
	while(oSymTable->p2next!=NULL){
		i++;
		oSymTable=oSymTable->p2next;
	}
	return i;
}


/* dimiourgw neo node */
	
SymTable_T  SymTable_newnode(void){
	SymTable_T p;
	p=(SymTable_T)malloc(sizeof(STable));
	p->p2next = NULL;
	return p;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	SymTable_T prev;
	assert(pcKey!=NULL);
	assert(oSymTable!=NULL);
	/* kanw ton pointer na deixnei */
	/* sto keli pou mou leei to */
	/* hash function oti */
	/* antistoixei sto pcKey */
	/* kai meta aplo remove */
	/* node apo list */
	oSymTable=&oSymTable[SymTable_hash(pcKey)];
	prev=oSymTable;
	if((oSymTable->p2next!=NULL)){
		while(oSymTable!=NULL){
			if(strcmp(pcKey,oSymTable->key)==0){
				/*vrethike to key*/
				/* enwnw to proigoumeno me to epomeno */
				/* kai kanw free auto p edwse o xristis */
				/* gia remove */
				prev->p2next=oSymTable->p2next;
				
				free(oSymTable->key); /*2021 ALLAGI */
				free(oSymTable);
				return 1;
																				}
			prev=oSymTable;
			oSymTable=oSymTable->p2next;
		}
	}
	return 0;
}
/*psaxnw tin lista tou keliou pou kanei point to hash function */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	oSymTable=&oSymTable[SymTable_hash(pcKey)];
	while(oSymTable!=NULL){
		if(strcmp(oSymTable->key,pcKey)==0){
			/*brethike antistoixo key*/
			return 1;
		}
		oSymTable=oSymTable->p2next;
	}
	/*den vrethike antistoixo key*/
	return 0;
}
/* idio me to SymTable_contains apla epistrefw to value */
/* an iparxei kai NULL an den iparxei binding */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	oSymTable=&oSymTable[SymTable_hash(pcKey)];
	while(oSymTable!=NULL){
		if(strcmp(oSymTable->key,pcKey)==0){
			return oSymTable->value;
		}
		oSymTable=oSymTable->p2next;
	}
	return NULL;
}
/*ektelw tin pfapply gia kathe ena stoixeio */
/* tis kathe listas p einai gia to kathe */
/* keli tou pinaka */
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
	SymTable_T p;
	int i=0;
	assert(oSymTable!=NULL);
	assert(pvExtra!=NULL);
	for(i=0;i<509;i++){
		p=&oSymTable[i];
		if(p->p2next!=NULL){
			p=p->p2next;
			pfApply(p->key,p->value,(void *)pvExtra);
		}
	}
}
