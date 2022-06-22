#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "SymTable.h"

typedef struct SymTable{
	char *key;
	void *value;
	struct SymTable *p2next;
}STable;

SymTable_T SymTable_new(void){
	SymTable_T p;
	p=(SymTable_T)malloc(sizeof(STable));
	p->key = (char*)malloc(6*sizeof(char));
	strcpy(p->key,"dummy");
	return p;
}
/*me anadromi gia oso to p2next iparxei ksana kalw tin free*/
/* otan ftasw sto teleutaio node to kanw kai ekeino free*/
/*kai paw pros ta pisw kanontas ola free ena ena*/
void SymTable_free(SymTable_T oSymTable){
	assert(oSymTable!=NULL);
	if(oSymTable->p2next!=NULL){
		SymTable_free(oSymTable->p2next);
	}
	free(oSymTable->key);
	free(oSymTable);
}
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
	SymTable_T p,prev;
	int i;
	char *klidi;
	assert(pcKey!=NULL);
	assert(oSymTable!=NULL);
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
	i=strlen(pcKey);
	klidi=malloc(i*sizeof(char));
	strcpy(klidi,pcKey);
	/* ftiaxnw to neo node */
	/* kai vazw mesa ta stoixeia */
	p=SymTable_new();
	free(p->key);
	p->key=(char *)klidi;
	p->value=(void *)pvValue;
	prev->p2next=p;
	return 1;
}
unsigned int SymTable_getLength(SymTable_T oSymTable){
	int i=0;
	assert(oSymTable!=NULL);
	while(oSymTable->p2next!=NULL){
		i++;
		oSymTable=oSymTable->p2next;
	}
	return i;
}
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	SymTable_T prev;
	assert(pcKey!=NULL);
	assert(oSymTable!=NULL);
	prev=oSymTable;
	if((oSymTable->p2next!=NULL)){
		while(oSymTable!=NULL){
			if(strcmp(pcKey,oSymTable->key)==0){
				/*vrethike to key*/
				/* enwnw to proigoumeno me to epomeno */
				/* kai kanw free auto p edwse o xristis */
				/* gia remove */
				prev->p2next=oSymTable->p2next;
				free(oSymTable->key);
				free(oSymTable);
				return 1;
			}
		prev=oSymTable;
		oSymTable=oSymTable->p2next;
		}
	}
	return 0;
}
/*aplo search kanei gia to key an to brei return 1 */
/* alliws return 0 */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	while(oSymTable!=NULL){
		if(strcmp(oSymTable->key,pcKey)==0){
			return 1;
		}
		oSymTable=oSymTable->p2next;
	}
	return 0;
}
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
	assert(oSymTable!=NULL);
	assert(pcKey!=NULL);
	while(oSymTable!=NULL){
		if(strcmp(oSymTable->key,pcKey)==0){
			return oSymTable->value;
		}
		oSymTable=oSymTable->p2next;
	}
	return NULL;
}
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
	assert(oSymTable!=NULL);
	assert(pvExtra!=NULL);
	if(oSymTable->p2next!=NULL){
		oSymTable=oSymTable->p2next;
		pfApply(oSymTable->key,oSymTable->value,(void *)pvExtra);
	}
}










