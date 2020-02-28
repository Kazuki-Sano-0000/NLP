/* 第一引数:読み込むテキストファイル*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LIMIT 128                  /*音素の文字の長さの上限値*/
#define WORDLIMIT 1024             /*音素の種類の上限値*/

/*音素の構造体の型定義*/
struct unigram{
  char phoneme[LIMIT];             /*音素*/
  int  freq;                       /*音素の出現数*/
  double prob;                     /*音素の確率*/
};

struct unigram unigram[WORDLIMIT]; /*それぞれの音素の格納用構造体配列*/

int freq(FILE *fp_open);           /*ファイルにある音素の出現数を求める関数*/
void sort(int count);              /*並び替え関数（バブルソート）*/

int main(void){

  FILE *fp_in,*result;             /*ファイルポインタ*/
  int i,j,count=0;                 /*ループカウンタ、音素の種類*/
  int freqsum=0;                   /*出現頻度の総和を格納する変数*/

  /*初期化*/
  for(i=0;i<WORDLIMIT;i++){
    for(j=0;j<LIMIT;j++){
      unigram[i].phoneme[j] = '\0'; /*音素名を初期化*/
    }
    unigram[i].freq = 0;            /*音素の出現数の初期化*/
  }


  fp_in = fopen("75.60k999.htkdic", "r");     /*辞書ファイルを読み込み*/

  if(fp_in == NULL){		   /* fopenが失敗している場合 */
    fprintf(stderr, "Cannot open file:%s\n", "75.60k999.htkdic"); /* エラー文を表示し */
    return -1;		           /* 異常終了 */
  }
  
  /*音素のユニグラムを求める*/
  count = freq(fp_in);             /*発生回数計算し、音素の種類数をcountに代入*/
  
  /*出現頻度の総和計算処理*/
  for(i=0;i<count;i++){
    freqsum += unigram[i].freq;
  }

  /*ユニグラム確率の計算処理*/
  for(i=0;i<count;i++){
    unigram[i].prob = (double)unigram[i].freq / (double)freqsum;
  }
  
  fclose(fp_in);                   /*読み込みファイルを閉じる*/

  /*並び替え処理*/
  sort(count);

  /*結果を出力*/
  result = fopen("result_unigram.txt", "w");
  fprintf(result,"音素 , 発生回数 ,ユニグラム確率 \n");
  for(i=0;i<count;i++){
    fprintf(result," %s \t%d \t%lf \n",unigram[i].phoneme,unigram[i].freq,unigram[i].prob);
  }
  
  fclose(result);                  /*出力ファイルを閉じる*/

  return 0;                        /*正常終了*/

}

int freq(FILE *fp_open){       /*引数fp_openは読み込みファイルのファイルポインタ*/
  int i,j,k=0,flg;            /*ループカウンタ、記憶保持用変数*/
  char data[WORDLIMIT];       /*読み込んだデータを格納する配列*/
  char word[WORDLIMIT];       /*読み込んだデータの音素を格納する配列*/
  char *temp;                 /*文字列一時保存用ポインタ*/

  /*---音素頻度計算処理----*/
  while(fgets(data,sizeof(data),fp_open) != NULL){ /*ファイルデータが読み終わるまで*/

    sscanf(data,"%[^\n]",word); /*1行文の音素列の抽出*/

    flg = 0; /*フラグの初期化*/
    
    word[strlen(word)-1] = '\0';  /*文字列の最後の改行コードを消す処理*/
    word[strlen(word)-1] = '\0';
    word[strlen(word)-1] = '\0';

    temp = strtok(word," ");      /*wordの文字列を空白ごとに区切り1つ目をtempに格納*/

    while(temp != NULL){          /*音素が読み取れなくなるまでループ*/
      if(temp == " "){                  /*空白を読み込んだときのエラー処理*/
	temp = strtok(NULL," ");        /*次の区切られた文字列を読み込む*/
	continue;                       /*ループの最初へ*/
      }
      
      for(i=0;i<WORDLIMIT;i++){
	if(strcmp(unigram[i].phoneme, temp) == 0){  /*同じ音素があるとき*/
	  unigram[i].freq++;                        /*頻度の件数カウント*/
	  flg=1;                        /*同じ形態素が見つかったためフラグを立てる*/
	  break;
	}
      }
      
      if(flg == 0){                                 /*同じ音素が見つからなかったとき*/
	strcpy(unigram[k].phoneme,temp);            /*音素を新たに配列に格納する*/
	unigram[k].freq++;                          /*頻度の件数カウント*/
	k++;                                        /*音素データの種類数をカウント*/
      }
      
      temp = strtok(NULL," ");                      /*次の区切られた文字列を読み込む*/
      flg = 0;                          /*フラグの初期化*/
    }
  }
  return k;                                         /*音素の種類数を返す*/
}

void sort(int count){             /*引数countは音素の種類数*/
  int i,j,tempfreq=0;    /*ループカウンタ、出現頻度記憶保持用変数*/
  double tempprob=0;     /*ユニグラム確率記憶保持用変数*/
  char wordtemp[LIMIT];  /*記憶保持用配列*/

  /*ユニグラム確率において並べ替え処理(バブルソート)*/
  for(i=0;i<count;i++){
    for(j=i+1;j<count;j++){
      if(unigram[i].prob < unigram[j].prob){  /*ユニグラム確率比較*/
	
	strcpy(wordtemp,unigram[i].phoneme);
	tempfreq = unigram[i].freq;
	tempprob = unigram[i].prob;
	
	strcpy(unigram[i].phoneme,unigram[j].phoneme);
	unigram[i].freq = unigram[j].freq;
	unigram[i].prob = unigram[j].prob;
	
	strcpy(unigram[j].phoneme,wordtemp);
	unigram[j].freq = tempfreq;
	unigram[j].prob = tempprob;
      }
    }
  }

}