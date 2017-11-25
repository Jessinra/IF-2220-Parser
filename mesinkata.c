#include "mesinkata.h"
#include "mesinkar.h"
#include <stdio.h>
#include "boolean.h"
#include <stdlib.h>

boolean EndKata;
Kata CKata;
int list_of_input[9999];
int maxindex = 0;
int baris[9999];
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
        list_of_input[maxindex++] = 10;
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
    Kata integer;
    (integer).Length = 7;
    (integer).TabKata = " integer" ;
    if(CompareKata(CKata,integer)){
        return 2;
    }

    Kata real;
    (real).Length = 4;
    (real).TabKata = " real" ;
    if(CompareKata(CKata,real)){
        return 3;
    }

    Kata chars;
    (chars).Length = 4;
    (chars).TabKata = " char" ;
    if(CompareKata(CKata,chars)){
        return 4;
    }

    Kata null;
    null.Length = 1;
    null.TabKata = " 0" ;
    if(CompareKata(CKata,null)){
        return 5;
    }

    Kata begin;
    begin.Length = 5;
    begin.TabKata = " begin" ;
    if(CompareKata(CKata,begin)){
        return 6;
    }

    Kata end;
    end.Length = 3;
    end.TabKata = " end" ;
    if(CompareKata(CKata,end)){
        return 7;
    }

    Kata titik;
    titik.Length = 1;
    titik.TabKata = " ." ;
    if(CompareKata(CKata,titik)){
        return 8;
    }

    Kata program;
    program.Length = 7;
    program.TabKata = " program" ;
    if(CompareKata(CKata,program)){
        return 9;
    }

    Kata titikkoma;
    titikkoma.Length = 1;
    titikkoma.TabKata = " ;" ;
    if(CompareKata(CKata,titikkoma)){
        return 10;
    }

    Kata var;
    var.Length = 3;
    var.TabKata = " var" ;
    if(CompareKata(CKata,var)){
        return 11;
    }

    Kata titikdua;
    titikdua.Length = 1;
    titikdua.TabKata = " :" ;
    if(CompareKata(CKata,titikdua)){
        return 12;
    }

    Kata array;
    array.Length = 5;
    array.TabKata = " array" ;
    if(CompareKata(CKata,array)){
        return 13;
    }

    Kata of;
    of.Length = 2;
    of.TabKata = " of" ;
    if(CompareKata(CKata,of)){
        return 14;
    }

    Kata kukir;
    kukir.Length = 1;
    kukir.TabKata = " [" ;
    if(CompareKata(CKata,kukir)){
        return 15;
    }

    Kata doubledot;
    doubledot.Length = 2;
    doubledot.TabKata = " .." ;
    if(CompareKata(CKata,doubledot)){
        return 16;
    }

    Kata kukan;
    kukan.Length = 1;
    kukan.TabKata = " ]" ;
    if(CompareKata(CKata,kukan)){
        return 17;
    }

    Kata coma;
    coma.Length = 1;
    coma.TabKata = " ," ;
    if(CompareKata(CKata,coma)){
        return 18;
    }

    Kata input;
    input.Length = 5;
    input.TabKata = " input" ;
    if(CompareKata(CKata,input)){
        return 19;
    }

    Kata leftpar;
    leftpar.Length = 1;
    leftpar.TabKata = " (" ;
    if(CompareKata(CKata,leftpar)){
        return 20;
    }

    Kata rightpar;
    rightpar.Length = 1;
    rightpar.TabKata = " )" ;
    if(CompareKata(CKata,rightpar)){
        return 21;
    }

    Kata output;
    output.Length = 6;
    output.TabKata = " output" ;
    if(CompareKata(CKata,output)){
        return 22;
    }

    Kata ifs;
    ifs.Length = 2;
    ifs.TabKata = " if" ;
    if(CompareKata(CKata,ifs)){
        return 23;
    }

    Kata then;
    then.Length = 4;
    then.TabKata = " then" ;
    if(CompareKata(CKata,then)){
        return 24;
    }

    Kata elses;
    elses.Length = 4;
    elses.TabKata = " else" ;
    if(CompareKata(CKata,elses)){
        return 25;
    }

    Kata whiles;
    whiles.Length = 5;
    whiles.TabKata = " while" ;
    if(CompareKata(CKata,whiles)){
        return 26;
    }

    Kata does;
    does.Length = 2;
    does.TabKata = " do" ;
    if(CompareKata(CKata,does)){
        return 27;
    }

    Kata repeat;
    repeat.Length = 6;
    repeat.TabKata = " repeat" ;
    if(CompareKata(CKata,repeat)){
        return 28;
    }

    Kata until;
    until.Length = 5;
    until.TabKata = " until" ;
    if(CompareKata(CKata,until)){
        return 29;
    }

    Kata fors;
    fors.Length = 3;
    fors.TabKata = " for" ;
    if(CompareKata(CKata,fors)){
        return 30;
    }

    Kata Eq;
    Eq.Length = 1;
    Eq.TabKata = " =" ;
    if(CompareKata(CKata,Eq)){
        return 31;
    }

    Kata to;
    to.Length = 2;
    to.TabKata = " to" ;
    if(CompareKata(CKata,to)){
        return 32;
    }

    Kata downto;
    downto.Length = 6;
    downto.TabKata = " downto" ;
    if(CompareKata(CKata,downto)){
        return 33;
    }

    Kata step;
    step.Length = 4;
    step.TabKata = " step" ;
    if(CompareKata(CKata,step)){
        return 34;
    }

    Kata assign;
    assign.Length = 2;
    assign.TabKata = " :=" ;
    if(CompareKata(CKata,assign)){
        return 35;
    }

    Kata plus;
    plus.Length = 1;
    plus.TabKata = " +" ;
    if(CompareKata(CKata,plus)){
        return 36;
    }

    Kata min;
    min.Length = 1;
    min.TabKata = " -" ;
    if(CompareKata(CKata,min)){
        return 37;
    }

    Kata star;
    star.Length = 1;
    star.TabKata = " *" ;
    if(CompareKata(CKata,star)){
        return 38;
    }

    Kata divs;
    divs.Length = 1;
    divs.TabKata = " /" ;
    if(CompareKata(CKata,divs)){
        return 39;
    }

    Kata div;
    div.Length = 3;
    div.TabKata = " div" ;
    if(CompareKata(CKata,div)){
        return 40;
    }

    Kata mod;
    mod.Length = 3;
    mod.TabKata = " mod" ;
    if(CompareKata(CKata,mod)){
        return 41;
    }

    Kata less;
    less.Length = 1;
    less.TabKata = " <" ;
    if(CompareKata(CKata,less)){
        return 42;
    }

    Kata more;
    more.Length = 1;
    more.TabKata = " >" ;
    if(CompareKata(CKata,more)){
        return 43;
    }

    Kata moreEq;
    moreEq.Length = 2;
    moreEq.TabKata = " >=" ;
    if(CompareKata(CKata,moreEq)){
        return 44;
    }

    Kata lessEq;
    lessEq.Length = 2;
    lessEq.TabKata = " <=" ;
    if(CompareKata(CKata,lessEq)){
        return 45;
    }

    Kata notEq;
    notEq.Length = 2;
    notEq.TabKata = " <>" ;
    if(CompareKata(CKata,notEq)){
        return 46;
    }

    Kata dollar;
    dollar.Length = 1;
    dollar.TabKata = " $" ;
    if(CompareKata(CKata,dollar)){
        return 47;
    }

    Kata S;
    S.Length = 1;
    S.TabKata = " S" ;
    if(CompareKata(CKata,S)){
        return 48;
    }

    Kata VAR_CONST;
    VAR_CONST.Length = 9;
    VAR_CONST.TabKata = " VAR_CONST" ;
    if(CompareKata(CKata,VAR_CONST)){
        return 49;
    }

    Kata VAR;
    VAR.Length = 3;
    VAR.TabKata = " VAR" ;
    if(CompareKata(CKata,VAR)){
        return 50;
    }

    Kata CONST;
    CONST.Length = 5;
    CONST.TabKata = " CONST" ;
    if(CompareKata(CKata,CONST)){
        return 51;
    }

    Kata VAR_TYPE;
    VAR_TYPE.Length = 8;
    VAR_TYPE.TabKata = " VAR_TYPE" ;
    if(CompareKata(CKata,VAR_TYPE)){
        return 52;
    }

    Kata NUM;
    NUM.Length = 3;
    NUM.TabKata = " NUM" ;
    if(CompareKata(CKata,NUM)){
        return 53;
    }

    Kata START;
    START.Length = 5;
    START.TabKata = " START" ;
    if(CompareKata(CKata,START)){
        return 54;
    }

    Kata PROGRAM_DEFINITION;
    PROGRAM_DEFINITION.Length = 18;
    PROGRAM_DEFINITION.TabKata = " PROGRAM_DEFINITION" ;
    if(CompareKata(CKata,PROGRAM_DEFINITION)){
        return 55;
    }

    Kata DICTIONARY;
    DICTIONARY.Length = 10;
    DICTIONARY.TabKata = " DICTIONARY" ;
    if(CompareKata(CKata,DICTIONARY)){
        return 56;
    }

    Kata VAR_DECLARE;
    VAR_DECLARE.Length = 11;
    VAR_DECLARE.TabKata = " VAR_DECLARE" ;
    if(CompareKata(CKata,VAR_DECLARE)){
        return 57;
    }

    Kata ARRAY_DECLARE;
    ARRAY_DECLARE.Length = 13;
    ARRAY_DECLARE.TabKata = " ARRAY_DECLARE" ;
    if(CompareKata(CKata,ARRAY_DECLARE)){
        return 58;
    }

    Kata ARRAY_DIMENSION;
    ARRAY_DIMENSION.Length = 15;
    ARRAY_DIMENSION.TabKata = " ARRAY_DIMENSION" ;
    if(CompareKata(CKata,ARRAY_DIMENSION)){
        return 59;
    }

    Kata BLOCK;
    BLOCK.Length = 5;
    BLOCK.TabKata = " BLOCK" ;
    if(CompareKata(CKata,BLOCK)){
        return 60;
    }

    Kata ALGORITHM;
    ALGORITHM.Length = 9;
    ALGORITHM.TabKata = " ALGORITHM" ;
    if(CompareKata(CKata,ALGORITHM)){
        return 61;
    }

    Kata IO;
    IO.Length = 2;
    IO.TabKata = " IO" ;
    if(CompareKata(CKata,IO)){
        return 62;
    }

    Kata COND;
    COND.Length = 4;
    COND.TabKata = " COND" ;
    if(CompareKata(CKata,COND)){
        return 63;
    }

    Kata IF;
    IF.Length = 2;
    IF.TabKata = " IF" ;
    if(CompareKata(CKata,IF)){
        return 64;
    }

    Kata ELSE_BLOCK;
    ELSE_BLOCK.Length = 10;
    ELSE_BLOCK.TabKata = " ELSE_BLOCK" ;
    if(CompareKata(CKata,ELSE_BLOCK)){
        return 65;
    }

    Kata ELSE_IF;
    ELSE_IF.Length = 7;
    ELSE_IF.TabKata = " ELSE_IF" ;
    if(CompareKata(CKata,ELSE_IF)){
        return 66;
    }

    Kata LOOP;
    LOOP.Length = 4;
    LOOP.TabKata = " LOOP" ;
    if(CompareKata(CKata,LOOP)){
        return 67;
    }

    Kata FOR;
    FOR.Length = 3;
    FOR.TabKata = " FOR" ;
    if(CompareKata(CKata,FOR)){
        return 68;
    }

    Kata TO_DOWNTO;
    TO_DOWNTO.Length = 9;
    TO_DOWNTO.TabKata = " TO_DOWNTO" ;
    if(CompareKata(CKata,TO_DOWNTO)){
        return 69;
    }

    Kata STEP;
    STEP.Length = 4;
    STEP.TabKata = " STEP" ;
    if(CompareKata(CKata,STEP)){
        return 70;
    }

    Kata ASSIGN;
    ASSIGN.Length = 6;
    ASSIGN.TabKata = " ASSIGN" ;
    if(CompareKata(CKata,ASSIGN)){
        return 71;
    }

    Kata OP_ARITH;
    OP_ARITH.Length = 8;
    OP_ARITH.TabKata = " OP_ARITH" ;
    if(CompareKata(CKata,OP_ARITH)){
        return 72;
    }

    Kata OP_LOGIC;
    OP_LOGIC.Length = 8;
    OP_LOGIC.TabKata = " OP_LOGIC" ;
    if(CompareKata(CKata,OP_LOGIC)){
        return 73;
    }

    Kata SYM_ARITH;
    SYM_ARITH.Length = 9;
    SYM_ARITH.TabKata = " SYM_ARITH" ;
    if(CompareKata(CKata,SYM_ARITH)){
            return 74;
    }

    Kata SYM_LOGIC;
    (SYM_LOGIC).Length = 9;
    (SYM_LOGIC).TabKata = " SYM_LOGIC" ;
    if(CompareKata(CKata,SYM_LOGIC)){
            return 75;
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

    /*
    for(i = 0; i < maxindex; i++){
        //printf("%d " ,list_of_input[i]);
    }
    */
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
