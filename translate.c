#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char** table_creation();
char tprint(char c,char **map);
char** print_table(char **map);
char state_N(char c,char **map);
char (*actions[4]) (char c,char **map);
char state_n(char c,char **map);
char state_M(char c,char **map);
char state_m(char c,char **map);

int main(void){
	char **map;
	
	char ch;
	map=table_creation(); 			/*arxikopoiw ton pinaka/guide mou */	

	ch=getc(stdin); 			/*diavazw to prwto stoixeio*/

	tprint(ch,map);				/*kai to stelnw stin fsm wste na ksekinisei*/
		
	
		
	
	return 0;
}

char tprint(char c,char **map){			/*to arxiko stadio tis fsm */
	int x,i,flag;
	enum states{dc,N,n,M,m}states;
	
	char fsm;
	actions[N]=&state_N;
	actions[n]=&state_n;
	actions[M]=&state_M;
	actions[m]=&state_m;
	states=dc;
	flag=0;
	if(c==map[12][0]){			/*tsekarw ama auto p diavasa peftei stisi idikes katigories*/
		states=N;
	
	}else if(c==map[36][0]){
		states=n;
	}else if(c==map[11][0]){
		states=M;
	}else if(c==map[35][0]){
		states=m;
	}
	
	
	if(states==dc){				/*an den anikei ekei tote */
		for(x=0 ; x<69; x++ ){
			if(c==map[x][0]){
				for(i=0;i<4;i++){
					if(map[x][i+1]!=' ')	{	/*psaxnw ton map gia to elliniko gramma kai otan to brw*/
						putchar(map[x][i+1]);
						flag=1;			/*tipwnw ola ta mi kena kelia  */
								}
						}				
									
			}
		}
		if(flag==0){			/*se periptwsi p den einai ston pinaka / guide mou*/
			putchar(c);		/* apla to tipwnw giati einai iso 5589-1 character */
		}
	}else{
		fsm=actions[states](c,map);	/*ama anoikei se idiki katigoria tis fsm allazw katastasi */
		if(fsm!=0){			/*ama i fsm girisei 0 tote tipwthike apo ekei o xaraktiras*/
			tprint(fsm,map);
			}

			

	}
	c=getc(stdin);				/*diavazw to epomeno stoixeio kai an den einai EOF */
	if(c==EOF){				
		return 0;
	}
		tprint(c,map);			/*ksanatrexw tin tprint mesa apo ton eauto tis */
	 	return 0;
	
	
}
char state_N(char c,char **map){		/*state tis fsm gia to N , antistoixa ginontai kai ta alla 3 */
	char nextc;
	
	nextc=getc(stdin);			/*paei ena stoixeio mprosta enw exei kai to palio stin mnimi*/
	if(nextc==map[18][0]||nextc==map[42][0]){	/*tsekarei ama to epomeno einai T i t kai an nai*/
		c='D';					/*tipwnei to d kai tha epistrepsei 0 gia na min */
		putchar(c);				/*ksana tipwthei parapanisio char*/
		
	}else if(nextc==c){				/*an to epomeno einai pali N tote ksana kalo to state*/
		putchar(map[12][1]);			/*kai tipwnw to N giati den tha to exw sto epomeno*/
		nextc=state_N(c,map);			/*state giati tha perasei to neo N*/
		return nextc;
	}else{
		putchar(map[12][1]);			/*an o epomenos einai adiaforos tote tipwnw N */
		return nextc;				/*kai epistrefw ton epomeno gia tin periptwsi*/
	}						/*an anoikei se kapoio allo state*/
	return 0;					/*omoia ginontai kai ta states twn n , M , m*/
}
char state_n(char c,char **map){			/*state gia to n*/
	char nextc;
	nextc=getc(stdin);
	if(nextc==map[18][0]||nextc==map[42][0]){
		c='d';
		putchar(c);
	}else if(nextc==c){
		putchar(map[36][1]);
		nextc=state_n(c,map);
		return nextc;
	}else{
		putchar(map[36][1]);
		return nextc;
	}
	return 0;
}
char state_M(char c,char **map){			/*state gia to M */
	char nextc;
	nextc=getc(stdin);
	if(nextc==map[15][0]||nextc==map[39][0]){
		c='B';
		putchar(c);
	}else if(nextc==c){
		putchar(map[11][1]);
		nextc=state_M(c,map);
		return nextc;
	}else{
		putchar(map[11][1]);
		return nextc;
	}
	return 0;
}
char state_m(char c,char **map){			/* state gia to m */
	char nextc;
	nextc=getc(stdin);
	if(nextc==map[15][0]||nextc==map[39][0]){
			c='b';
			putchar(c);
	}else if(nextc==c){
		putchar(map[35][1]);
		nextc=state_m(c,map);
		return nextc;
	}else{
		putchar(map[35][1]);
		return nextc;
	}
	return 0;
}













char** table_creation(){
	char **table;
	char **map_pr;
	int i,j,y;
	
	
	map_pr=malloc(69*sizeof(char*));				
	for(i=0;i<69;i++){			
	       	map_pr[i]=malloc(4*sizeof(char));
		for(j=0;j<5;j++){
			map_pr[i][j]=' ';	/*ton pinaka ton gemizw kena gia na me boithisei meta*/
		}
	}
	

	table=malloc(4*sizeof(char*));
	for(i=0;i<5;i++){
		table[i]=malloc(69*sizeof(char));
	}
	y=193;	
	j=0;
	for(i=0;i<24;i++){
		if(i==17){			/*arxikopoiw ton pinaka p metepeita tha girisw sto plai*/
			y=y+1;			/*wste na mporw na deiksw me pointer kai na blepei %s*/
		}				/*ousiastika dinw tis times tou iso 8859-7 me mia boliki*/
		table[0][j]=y;			/*seira wste meta me to strcpy na katsei 1 pros 1 to iso -1*/
		table[0][j+24]=y+32;
		j++;
		y++;
	}	
	y=0;
	j=182;
	for(i=0;i<20;i++){
		if((j==183)|(j==187)|(j==189)){
			j=j+1;
		}
		if((j==193)|(j==225)){
			j=j+25;
		}
		table[0][48+i]=j;
		
		j++;
	}
	j=242;					/*sigma teliko*/	
	table[0][68]=j;
	strcpy(table[1], "AVGDEZH8IKLMNKOPRSTYFXPWavgdezh8iklmnkoprstyfxpwAEHIOYWiIYaehiuiuouws");
	for(j=0;j<69;j++){
		map_pr[j][0]=table[0][j];	/*edw girizw sto plai ton pinaka*/
		map_pr[j][1]=table[1][j];
	}
	j=39;					
	for(i=48;i<55;i++){
		map_pr[i][2]=map_pr[i][1];	/*arxikopoiw apo to 48 kai meta to ' stin deuteri thesi*/
		map_pr[i][1]=j;			/*wste opote diavazw kati x me tono  na dinei 'x */
	}
	for(i=55;i<68;i++){
		map_pr[i][2]=j;			/*bazw tonous  pantou meta tha to allaksw se 4 grammata*/
	}
	j=34;					/*iso 5589-1 code twn dialitikwn*/
	map_pr[55][3]=j;			/*bazw dialitika  meta ton tono se 2 grammata */
	map_pr[56][2]=j;			/*enw opou thelei mono dialitika antikatastw ton */
	map_pr[57][2]=j;			/*idi iparxwn tono pou ebala prin*/
	map_pr[62][3]=j;
	map_pr[63][2]=j;
	map_pr[64][2]=j;
	map_pr[13][2]='S';			/*sta gramata ps kai ks bazw ta s stin 2 thesi tou map*/
	map_pr[37][2]='s';
	map_pr[22][2]='S';
	map_pr[46][2]='s';

	return map_pr;
}



