#include <stdio.h>
#include <stdlib.h>

int main(void){

	FILE *fp,*fp2;
	int i;
	short wav[131072];

	fp=fopen("2secA.raw","rb");
	fp2=fopen("2secA.csv","w");
	fread(wav, sizeof(short), 65536, fp);
	fclose(fp);

	for(i=0;i<65536;i++){
	  		fprintf(fp2,"%d\n",wav[i]);
	}
	fclose(fp);
	fclose(fp2);
	return 0;
}



