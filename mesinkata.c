#include "mesinkata.h"
#include "mesinkar.h"
#include <stdio.h>
#include "boolean.h"
#include <stdlib.h>

boolean EndKata;
Kata CKata;
int list_of_input[99999];
int maxindex = 0;
int baris[99999];
int bar = 1;


int IsSymbol()
//memeriksa apakah CC itu simbol atau bukan
{
      return((CC > 90 || CC < 65) && (CC < 97 || CC > 122) && CC != BLANK);
}

int IsTitikKoma()
//memeriksa apakah CC itu titik koma atau bukan
{
      return(CC == ';');
}

int IsAngka()
//memeriksa apakah CC itu angka
{
  //printf("masuk");
      return((CC > 47 && CC < 58));
}

void IgnoreBlank(){
    while(CC==BLANK || CC=='\n' || CC=='\t'){
      if(CC == '\n'){
        bar++;
      }
        ADV();
    }
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
void STARTKATA(char *filename){
    START(filename);
    IgnoreBlank();
    if(CC == MARK){
        EndKata = true;
    }
    else{
        EndKata = false;
        if(IsSymbol()){
            SalinSimbol();
        }else{
            SalinKata();
        }
    }
}
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA(){
    IgnoreBlank();
    if(CC == MARK){
        EndKata = true;
    }
    else if(!IsSymbol()){
        SalinKata();
    }
    else if(IsTitikKoma()){
        list_of_input[maxindex++] = 9;
        ADV();
        IgnoreBlank();
    }
    else if(IsAngka()){
        SalinAngka();
    }
    else{
        SalinSimbol();
    }
}
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinSimbol(){
    CKata.TabKata = (char*)malloc(50);
    int i = 1;
    while((CC!=MARK && CC!=BLANK && IsSymbol() && !IsTitikKoma() && !IsAngka()) && i<=NMax) {
        CKata.TabKata[i] = CC;
        i++;
        ADV();
    }
    if (i>=NMax){
        EndKata = true;
    }
    CKata.Length = i-1;
    //printkata(CKata);
    baris[maxindex] = bar;
    list_of_input[maxindex++] = KataToIndex(CKata);
    IgnoreBlank();
}

void SalinAngka(){
    CKata.TabKata = (char*)malloc(50);
    int i = 1;
    while((CC!=MARK && CC!=BLANK && IsSymbol() && IsAngka()) && i<=NMax) {
        CKata.TabKata[i] = CC;
        i++;
        ADV();
    }
    if (i>=NMax){
        EndKata = true;
    }
    CKata.Length = i-1;
    //printkata(CKata);
    baris[maxindex] = bar;
    list_of_input[maxindex++] = KataToIndex(CKata);
    IgnoreBlank();
}

void SalinKata(){
    CKata.TabKata = (char*)malloc(50);
    int i = 1;
    while((CC!=MARK && CC!=BLANK && !IsSymbol() && !IsTitikKoma() && !IsAngka()) && i<=NMax) {
        CKata.TabKata[i] = CC;
        i++;
        ADV();
    }
    if (i>=NMax){
        EndKata = true;
    }
    CKata.Length = i-1;
    baris[maxindex] = bar;
    list_of_input[maxindex++] = KataToIndex(CKata);
    IgnoreBlank();
}
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata " dipotong"  */

int CompareKata(Kata Kata1, Kata Kata2)
/*membandingkan apakah kata 1 == kata 2
 *jika iya mengembalikan 1 jika tidak mengembalikan 0
 */
{
    int i;

    if(Kata1.Length == Kata2.Length){
        for(i = 1; i <= Kata1.Length; i++){
            if(Kata1.TabKata[i] != Kata2.TabKata[i]){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int KataToIndex(Kata CKata)
/*mengubah Kata menajdi indeks di tabel parsing*/
{
	Kata B;
	B.Length = 7;
	B.TabKata = " integer";
	if(CompareKata(CKata,B)){
	return 2;
	}

	Kata C;
	C.Length = 4;
	C.TabKata = " real";
	if(CompareKata(CKata,C)){
	return 3;
	}

	Kata D;
	D.Length = 4;
	D.TabKata = " char";
	if(CompareKata(CKata,D)){
	return 4;
	}

	Kata E;
	E.Length = 5;
	E.TabKata = " begin";
	if(CompareKata(CKata,E)){
	return 5;
	}

	Kata F;
	F.Length = 3;
	F.TabKata = " end";
	if(CompareKata(CKata,F)){
	return 6;
	}

	Kata G;
	G.Length = 1;
	G.TabKata = " .";
	if(CompareKata(CKata,G)){
	return 7;
	}

	Kata H;
	H.Length = 7;
	H.TabKata = " program";
	if(CompareKata(CKata,H)){
	return 8;
	}

	Kata I;
	I.Length = 1;
	I.TabKata = " ;";
	if(CompareKata(CKata,I)){
	return 9;
	}

	Kata J;
	J.Length = 3;
	J.TabKata = " var";
	if(CompareKata(CKata,J)){
	return 10;
	}

	Kata K;
	K.Length = 1;
	K.TabKata = " :";
	if(CompareKata(CKata,K)){
	return 11;
	}

	Kata L;
	L.Length = 1;
	L.TabKata = " ,";
	if(CompareKata(CKata,L)){
	return 12;
	}

	Kata M;
	M.Length = 5;
	M.TabKata = " array";
	if(CompareKata(CKata,M)){
	return 13;
	}

	Kata N;
	N.Length = 2;
	N.TabKata = " of";
	if(CompareKata(CKata,N)){
	return 14;
	}

	Kata O;
	O.Length = 1;
	O.TabKata = " [";
	if(CompareKata(CKata,O)){
	return 15;
	}

	Kata P;
	P.Length = 2;
	P.TabKata = " ..";
	if(CompareKata(CKata,P)){
	return 16;
	}

	Kata Q;
	Q.Length = 1;
	Q.TabKata = " ]";
	if(CompareKata(CKata,Q)){
	return 17;
	}

	Kata R;
	R.Length = 5;
	R.TabKata = " input";
	if(CompareKata(CKata,R)){
	return 18;
	}

	Kata S;
	S.Length = 1;
	S.TabKata = " (";
	if(CompareKata(CKata,S)){
	return 19;
	}

	Kata T;
	T.Length = 1;
	T.TabKata = " )";
	if(CompareKata(CKata,T)){
	return 20;
	}

	Kata U;
	U.Length = 6;
	U.TabKata = " output";
	if(CompareKata(CKata,U)){
	return 21;
	}

	Kata V;
	V.Length = 2;
	V.TabKata = " if";
	if(CompareKata(CKata,V)){
	return 22;
	}

	Kata W;
	W.Length = 4;
	W.TabKata = " then";
	if(CompareKata(CKata,W)){
	return 23;
	}

	Kata X;
	X.Length = 4;
	X.TabKata = " else";
	if(CompareKata(CKata,X)){
	return 24;
	}

	Kata Y;
	Y.Length = 5;
	Y.TabKata = " while";
	if(CompareKata(CKata,Y)){
	return 25;
	}

	Kata Z;
	Z.Length = 2;
	Z.TabKata = " do";
	if(CompareKata(CKata,Z)){
	return 26;
	}

	Kata AA;
	AA.Length = 6;
	AA.TabKata = " repeat";
	if(CompareKata(CKata,AA)){
	return 27;
	}

	Kata AB;
	AB.Length = 5;
	AB.TabKata = " until";
	if(CompareKata(CKata,AB)){
	return 28;
	}

	Kata AC;
	AC.Length = 3;
	AC.TabKata = " for";
	if(CompareKata(CKata,AC)){
	return 29;
	}

	Kata AD;
	AD.Length = 2;
	AD.TabKata = " :=";
	if(CompareKata(CKata,AD)){
	return 30;
	}

	Kata AE;
	AE.Length = 2;
	AE.TabKata = " to";
	if(CompareKata(CKata,AE)){
	return 31;
	}

	Kata AF;
	AF.Length = 6;
	AF.TabKata = " downto";
	if(CompareKata(CKata,AF)){
	return 32;
	}

	Kata AG;
	AG.Length = 4;
	AG.TabKata = " step";
	if(CompareKata(CKata,AG)){
	return 33;
	}

	Kata AH;
	AH.Length = 3;
	AH.TabKata = " not";
	if(CompareKata(CKata,AH)){
	return 34;
	}

	Kata AI;
	AI.Length = 1;
	AI.TabKata = " +";
	if(CompareKata(CKata,AI)){
	return 35;
	}

	Kata AJ;
	AJ.Length = 1;
	AJ.TabKata = " -";
	if(CompareKata(CKata,AJ)){
	return 36;
	}

	Kata AK;
	AK.Length = 1;
	AK.TabKata = " *";
	if(CompareKata(CKata,AK)){
	return 37;
	}

	Kata AL;
	AL.Length = 1;
	AL.TabKata = " /";
	if(CompareKata(CKata,AL)){
	return 38;
	}

	Kata AM;
	AM.Length = 3;
	AM.TabKata = " div";
	if(CompareKata(CKata,AM)){
	return 39;
	}

	Kata AN;
	AN.Length = 3;
	AN.TabKata = " mod";
	if(CompareKata(CKata,AN)){
	return 40;
	}

	Kata AO;
	AO.Length = 1;
	AO.TabKata = " <";
	if(CompareKata(CKata,AO)){
	return 41;
	}

	Kata AP;
	AP.Length = 1;
	AP.TabKata = " >";
	if(CompareKata(CKata,AP)){
	return 42;
	}

	Kata AQ;
	AQ.Length = 2;
	AQ.TabKata = " >=";
	if(CompareKata(CKata,AQ)){
	return 43;
	}

	Kata AR;
	AR.Length = 2;
	AR.TabKata = " <=";
	if(CompareKata(CKata,AR)){
	return 44;
	}

	Kata AS;
	AS.Length = 1;
	AS.TabKata = " =";
	if(CompareKata(CKata,AS)){
	return 45;
	}

	Kata AT;
	AT.Length = 2;
	AT.TabKata = " <>";
	if(CompareKata(CKata,AT)){
	return 46;
	}

	Kata AU;
	AU.Length = 3;
	AU.TabKata = " and";
	if(CompareKata(CKata,AU)){
	return 47;
	}

	Kata AV;
	AV.Length = 2;
	AV.TabKata = " or";
	if(CompareKata(CKata,AV)){
	return 48;
	}

	Kata AW;
	AW.Length = 1;
	AW.TabKata = " $";
	if(CompareKata(CKata,AW)){
	return 49;
	}

	Kata AX;
	AX.Length = 1;
	AX.TabKata = " S";
	if(CompareKata(CKata,AX)){
	return 50;
	}

	Kata AY;
	AY.Length = 9;
	AY.TabKata = " VAR_CONST";
	if(CompareKata(CKata,AY)){
	return 51;
	}

	Kata AZ;
	AZ.Length = 3;
	AZ.TabKata = " VAR";
	if(CompareKata(CKata,AZ)){
	return 52;
	}

	Kata BA;
	BA.Length = 5;
	BA.TabKata = " CONST";
	if(CompareKata(CKata,BA)){
	return 53;
	}

	Kata BB;
	BB.Length = 8;
	BB.TabKata = " VAR_TYPE";
	if(CompareKata(CKata,BB)){
	return 54;
	}

	Kata BC;
	BC.Length = 3;
	BC.TabKata = " NUM";
	if(CompareKata(CKata,BC)){
	return 55;
	}

	Kata BD;
	BD.Length = 5;
	BD.TabKata = " START";
	if(CompareKata(CKata,BD)){
	return 56;
	}

	Kata BE;
	BE.Length = 18;
	BE.TabKata = " PROGRAM_DEFINITION";
	if(CompareKata(CKata,BE)){
	return 57;
	}

	Kata BF;
	BF.Length = 10;
	BF.TabKata = " DICTIONARY";
	if(CompareKata(CKata,BF)){
	return 58;
	}

	Kata BG;
	BG.Length = 11;
	BG.TabKata = " VAR_DECLARE";
	if(CompareKata(CKata,BG)){
	return 59;
	}

	Kata BH;
	BH.Length = 8;
	BH.TabKata = " VAR_INIT";
	if(CompareKata(CKata,BH)){
	return 60;
	}

	Kata BI;
	BI.Length = 13;
	BI.TabKata = " ARRAY_DECLARE";
	if(CompareKata(CKata,BI)){
	return 61;
	}

	Kata BJ;
	BJ.Length = 15;
	BJ.TabKata = " ARRAY_DIMENSION";
	if(CompareKata(CKata,BJ)){
	return 62;
	}

	Kata BK;
	BK.Length = 5;
	BK.TabKata = " BLOCK";
	if(CompareKata(CKata,BK)){
	return 63;
	}

	Kata BL;
	BL.Length = 6;
	BL.TabKata = " BLOCKS";
	if(CompareKata(CKata,BL)){
	return 64;
	}

	Kata BM;
	BM.Length = 9;
	BM.TabKata = " ALGORITHM";
	if(CompareKata(CKata,BM)){
	return 65;
	}

	Kata BN;
	BN.Length = 2;
	BN.TabKata = " IO";
	if(CompareKata(CKata,BN)){
	return 66;
	}

	Kata BO;
	BO.Length = 4;
	BO.TabKata = " COND";
	if(CompareKata(CKata,BO)){
	return 67;
	}

	Kata BP;
	BP.Length = 2;
	BP.TabKata = " IF";
	if(CompareKata(CKata,BP)){
	return 68;
	}

	Kata BQ;
	BQ.Length = 10;
	BQ.TabKata = " ELSE_BLOCK";
	if(CompareKata(CKata,BQ)){
	return 69;
	}

	Kata BR;
	BR.Length = 7;
	BR.TabKata = " ELSE_IF";
	if(CompareKata(CKata,BR)){
	return 70;
	}

	Kata BS;
	BS.Length = 4;
	BS.TabKata = " LOOP";
	if(CompareKata(CKata,BS)){
	return 71;
	}

	Kata BT;
	BT.Length = 3;
	BT.TabKata = " FOR";
	if(CompareKata(CKata,BT)){
	return 72;
	}

	Kata BU;
	BU.Length = 9;
	BU.TabKata = " TO_DOWNTO";
	if(CompareKata(CKata,BU)){
	return 73;
	}

	Kata BV;
	BV.Length = 4;
	BV.TabKata = " STEP";
	if(CompareKata(CKata,BV)){
	return 74;
	}

	Kata BW;
	BW.Length = 6;
	BW.TabKata = " ASSIGN";
	if(CompareKata(CKata,BW)){
	return 75;
	}

	Kata BX;
	BX.Length = 8;
	BX.TabKata = " OP_ARITH";
	if(CompareKata(CKata,BX)){
	return 76;
	}

	Kata BY;
	BY.Length = 8;
	BY.TabKata = " OP_LOGIC";
	if(CompareKata(CKata,BY)){
	return 77;
	}

	Kata BZ;
	BZ.Length = 9;
	BZ.TabKata = " SYM_ARITH";
	if(CompareKata(CKata,BZ)){
	return 78;
	}

	Kata CA;
	CA.Length = 9;
	CA.TabKata = " SYM_LOGIC";
	if(CompareKata(CKata,CA)){
	return 79;
	}

  return 1;
}

void printkata(Kata C){
    int i;

    for( i = 1; i <= C.Length; i++){
        printf("%c" , C.TabKata[i]);
    }
    printf(" ");
}

void init_token(char *filename)
/*mengisi array token dengan program yang sudah diubah menjadi token*/
{
    int i;

    STARTKATA(filename);
    while(!EndKata){


        //printkata(CKata);
        //printf("max index : %d, %d \n",maxindex, list_of_input[maxindex-1]);


        ADVKATA();
    }

    /* Include $ (47) as last input */
    list_of_input[maxindex++] = 49;

}


/*
int main(){
    init_token("coba.pas");
    printf("\n");
    int i;
    for(i = 0 ; i < 100; i++){
        printf("%d ",baris[i]);

        // ';' will be 0

    }
}
*/
