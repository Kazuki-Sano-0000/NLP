//
//  main.c
//  kadai1
//
//  Created by 佐野和樹 on 2019/10/04.
//  Copyright © 2019 佐野和樹. All rights reserved.
//

#include <stdio.h>

int main2(void)
{
         FILE *fp ,*fp2;
    short wav[131072];
    int i;
    fp = fopen("2secA.raw","rb");
    fp2 = fopen("2secA.csv","w");
   if (fp == NULL)
       printf("ファイルをオープンできません");
   else{
       fread(wav,sizeof(short),65536,fp);
       printf("%d/n",wav[0]);
       for(i=0; i<131072; i++) {
       fprintf(fp2,"%d/n",wav[i]);
       
   }
   fclose(fp);
    fclose(fp2);
    return 0;
    
}
}
