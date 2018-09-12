/* Processed by ecpg (10.1) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "generator.pgc"
//
///\todo avg, min, max, console input, suchthat-and predicates, >/<, 
//  having, test on multiple queries, EMF (if psbl)
///\file main.pgc (Need the .pgc extension!) 
//
///\author Kakde, Vishwajeet
//
///\cite Lecture Notes And PGC Sample Code by Professor Samuel Kim
//
///\brief This program takes an MF query as input. Refer readme for sample input file format.
///\brief The program then generates a program called main.c, which can then execute the MF query 
///\brief on "sales" table in a postgres DB
/*
 * Steps to run this program : 
 *  1. Log in to your PostgreSQL server (local/remote).
 *  2. In this program, find "DATABASE CONNECTION STRING" and "TABLE DETAILS", 
 *     modify [dbname], [tableName], [username], [password] to your details.
 *  3. Preprocessor - $ ecpg -I [postgres bin dir] main.pgc 
                      // looks like C:\Program Files\PostgreSQL\10\bin on Windows
 *  4. Compile      - $ gcc -c -I [postgres include dir] main.c 
                      // looks like C:\Program Files\PostgreSQL\10\include on Windows  
 *  5. Link         - $ gcc -L /usr/include/postgresql/ -lecpg -o main main.o
                      // looks like C:\Program Files\PostgreSQL\10\lib on Windows
 *  6. Execute      - $ main.exe
 */
//

//----------------------------------------------------------------------
// C includes
//----------------------------------------------------------------------
#include	<stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <ctype.h>
#include    <stdlib.h>

//----------------------------------------------------------------------
// HOST VARIABLES definitions
//----------------------------------------------------------------------
/* exec sql begin declare section */
 
		
		
	    
	    
		 
		
		 
	

#line 49 "generator.pgc"
 struct { 
#line 42 "generator.pgc"
 char * cust ;
 
#line 43 "generator.pgc"
 char * prod ;
 
#line 44 "generator.pgc"
 short dd ;
 
#line 45 "generator.pgc"
 short mm ;
 
#line 46 "generator.pgc"
 short yy ;
 
#line 47 "generator.pgc"
 char * state ;
 
#line 48 "generator.pgc"
 long quant ;
 } sale_rec ;
/* exec sql end declare section */
#line 50 "generator.pgc"


#line 1 "C:/Program Files/PostgreSQL/10/include/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#ifndef PGDLLIMPORT
#if  defined(WIN32) || defined(__CYGWIN__)
#define PGDLLIMPORT __declspec (dllimport)
#else
#define PGDLLIMPORT
#endif							/* __CYGWIN__ */
#endif							/* PGDLLIMPORT */

#define SQLERRMC_LEN	150

#ifdef __cplusplus
extern "C"
{
#endif

struct sqlca_t
{
	char		sqlcaid[8];
	long		sqlabc;
	long		sqlcode;
	struct
	{
		int			sqlerrml;
		char		sqlerrmc[SQLERRMC_LEN];
	}			sqlerrm;
	char		sqlerrp[8];
	long		sqlerrd[6];
	/* Element 0: empty						*/
	/* 1: OID of processed tuple if applicable			*/
	/* 2: number of rows processed				*/
	/* after an INSERT, UPDATE or				*/
	/* DELETE statement					*/
	/* 3: empty						*/
	/* 4: empty						*/
	/* 5: empty						*/
	char		sqlwarn[8];
	/* Element 0: set to 'W' if at least one other is 'W'	*/
	/* 1: if 'W' at least one character string		*/
	/* value was truncated when it was			*/
	/* stored into a host variable.             */

	/*
	 * 2: if 'W' a (hopefully) non-fatal notice occurred
	 */	/* 3: empty */
	/* 4: empty						*/
	/* 5: empty						*/
	/* 6: empty						*/
	/* 7: empty						*/

	char		sqlstate[5];
};

struct sqlca_t *ECPGget_sqlca(void);

#ifndef POSTGRES_ECPG_INTERNAL
#define sqlca (*ECPGget_sqlca())
#endif

#ifdef __cplusplus
}
#endif

#endif

#line 51 "generator.pgc"


//----------------------------------------------------------------------
// C VARIABLES definitions
//----------------------------------------------------------------------
/// \remark These variables do not interact with SQL. Used internally by C.
struct Pair_IntInt {
    int iFirst;
    int iSecond;
};

struct Pair_ChararrayInt {
    char iFirst[30];   
    int iSecond;     
};

struct Pair_ChararrayChararray {
    char sFirst[30];   
    char sSecond[30];     
};

struct informationSchema_tables {
    char sTbl_name[30];
    long lTbl_numRows;
    long lTbl_numColumns;
    struct Pair_ChararrayChararray col_nameDataType[20];
}stInformationSchema_sales;

struct predicate {
    char LHS[20];
    char condition[3]; // '>', '<', '>=', '<=', '<>' or '='
    char RHS[20];
};

struct mfstruct {
    char Cust[1200][21];
    bool Cust_Active;
    char Prod[1200][21];
    bool Prod_Active;
    int Day[1200];
    bool Day_Active;
    int Month[1200];
    bool Month_Active;
    int Year[1200];
    bool Year_Active;
    char State[1200][3];
    bool State_Active;
    double Aggregates[1200][10];
    int count_avgAggregates[1200][10];
    int count_Aggregates;
}stMfstruct;

struct mfstruct_config {
    int numRows;

    char cNumGroupingVariables;
    char sGV0[10][20];
    int size_sGV0;
    char sGVN[10][20];
    int size_sGVN;
    char select[10][20];
    int size_select;
    // struct predicate stPredicates[5];
    char suchThatPredicates[10][30];
    int size_suchThatPredicates;
    int suchThatPredicates_AND[10][2];
    int size_suchThatPredicates_AND;
    int suchThatPredicates_OR[10][2];
    int size_suchThatPredicates_OR;
    char havingPredicates[10][30];
    int size_havingPredicates;
    int havingPredicates_AND[10][2];
    int size_havingPredicates_AND;
    int havingPredicates_OR[10][2];
    int size_havingPredicates_OR;
}stMfstruct_config;

//----------------------------------------------------------------------
// C FUNCTIONS definitions
//----------------------------------------------------------------------
///\brief This function prints the MF Config structure
void printMfStructConfig (){
    printf("\n# of grouping variables: %c", stMfstruct_config.cNumGroupingVariables);
    printf("\n\nGV0 variables(%d): \n", stMfstruct_config.size_sGV0);
    for(int i=0; i<stMfstruct_config.size_sGV0; i++){
        puts(stMfstruct_config.sGV0[i]);
    }
    printf("\nGVn variables(%d): \n", stMfstruct_config.size_sGVN);
    for(int i=0; i<stMfstruct_config.size_sGVN; i++){
        puts(stMfstruct_config.sGVN[i]);
    }
    printf("\nSELECT variables(%d): \n", stMfstruct_config.size_select);
    for(int i=0; i<stMfstruct_config.size_select; i++){
        puts(stMfstruct_config.select[i]);
    }
    printf("\nSUCH THAT Predicates(%d): \n", stMfstruct_config.size_suchThatPredicates);
    for(int i=0; i<stMfstruct_config.size_suchThatPredicates; i++){
        puts(stMfstruct_config.suchThatPredicates[i]);
    }
    printf("\nHAVING Predicates(%d): \n", stMfstruct_config.size_havingPredicates);
    for(int i=0; i<stMfstruct_config.size_havingPredicates; i++){
        puts(stMfstruct_config.havingPredicates[i]);
    }
}

///\brief This function parses input file and translates into an MF Config structure
void parseInputFileContents(char sFileContents[512]){
    int line=1;
    stMfstruct_config.size_sGV0 = 1;
    stMfstruct_config.size_sGVN = 1;
    stMfstruct_config.size_select = 1;
    stMfstruct_config.size_suchThatPredicates = 1;
    stMfstruct_config.size_suchThatPredicates_AND = 0;
    stMfstruct_config.size_suchThatPredicates_OR = 0;
    stMfstruct_config.size_havingPredicates = 0;
    stMfstruct_config.size_havingPredicates_AND = 0;
    stMfstruct_config.size_havingPredicates_OR = 0;

    for(int i=0; sFileContents[i]!='\0'; i++){
        if(sFileContents[i]==' '){  // ignore spaces
            continue;
        }
        if(sFileContents[i]=='\n'){
            line++;
            continue;
        }
        if(line==1){
            stMfstruct_config.cNumGroupingVariables = sFileContents[i];
        }
        if(line==2){
            int gv0 = 0;
            int j=0;
            while(sFileContents[i]!='\n' && sFileContents[i]!='\0'){
                if(sFileContents[i]==' '){  // ignore spaces
                    i++;
                    continue;
                }
                if(sFileContents[i]==',' && sFileContents[i]!='\0'){  // 
                    gv0++;
                    i++;
                    j=0;
                    stMfstruct_config.size_sGV0++;
                    continue;
                }
                stMfstruct_config.sGV0[gv0][j++] = sFileContents[i++];                                
            }
            line++;
            i++;
        }
        if(line==3){
            int gvn = 0;
            int j=0;
            while(sFileContents[i]!='\n' && sFileContents[i]!='\0'){
                if(sFileContents[i]==' '){  // ignore spaces
                    i++;
                    continue;
                }
                if(sFileContents[i]==',' && sFileContents[i]!='\0'){  // 
                    gvn++;
                    i++;
                    j=0;
                    stMfstruct_config.size_sGVN++;
                    continue;
                }
                stMfstruct_config.sGVN[gvn][j++] = sFileContents[i++];
            }
            line++;
            i++;
        }
        if(line==4){
            int sel = 0;
            int j=0;
            while(sFileContents[i]!='\n' && sFileContents[i]!='\0'){
                if(sFileContents[i]==' '){  // ignore spaces
                    i++;
                    continue;
                }
                if(sFileContents[i]==',' && sFileContents[i]!='\0'){  // 
                    sel++;
                    i++;
                    j=0;
                    stMfstruct_config.size_select++;
                    continue;
                }
                stMfstruct_config.select[sel][j++] = sFileContents[i++];
            }
            line++;
            i++;
        }
        if(line==5){
            int pr = 0, pr_AND = 0, pr_OR = 0;
            int j=0;
            while(sFileContents[i]!='\n' && sFileContents[i]!='\0'){
                if(sFileContents[i]==' '){  // ignore spaces
                    i++;
                    continue;
                }
                if(sFileContents[i]==',' && sFileContents[i]!='\0'){  // 
                    pr++;
                    i++;
                    j=0;
                    stMfstruct_config.size_suchThatPredicates++;
                    continue;
                }
                if(sFileContents[i]=='a' && sFileContents[i+1]=='n' && sFileContents[i+2]=='d' && sFileContents[i]!='\0'){  // 
                    stMfstruct_config.suchThatPredicates_AND[pr_AND][0] = pr;
                    stMfstruct_config.suchThatPredicates_AND[pr_AND][1] = pr+1;
                    stMfstruct_config.size_suchThatPredicates_AND++;

                    pr++;
                    pr_AND++;
                    i+=3;
                    j=0;
                    stMfstruct_config.size_suchThatPredicates++;
                    continue;
                }
                if(sFileContents[i]=='o' && sFileContents[i+1]=='r' && sFileContents[i]!='\0'){  // 
                    stMfstruct_config.suchThatPredicates_OR[pr_OR][0] = pr;
                    stMfstruct_config.suchThatPredicates_OR[pr_OR][1] = pr+1;
                    stMfstruct_config.size_suchThatPredicates_OR++;
                    
                    pr++;
                    pr_OR++;
                    i+=2;
                    j=0;
                    stMfstruct_config.size_suchThatPredicates++;
                    continue;
                }
                stMfstruct_config.suchThatPredicates[pr][j++] = sFileContents[i++];
            }
            line++;
            i++;
        }
        if(line==6){
            int pr = 0, pr_AND = 0, pr_OR = 0;
            int j=0;
            while(sFileContents[i]!='\n' && sFileContents[i]!='\0'){
                if(sFileContents[i]==' '){  // ignore spaces
                    i++;
                    continue;
                }
                if(sFileContents[i]==',' && sFileContents[i]!='\0'){  // 
                    pr++;
                    i++;
                    j=0;
                    stMfstruct_config.size_havingPredicates++;
                    continue;
                }
                if(sFileContents[i]=='a' && sFileContents[i+1]=='n' && sFileContents[i+2]=='d' && sFileContents[i]!='\0'){  // 
                    stMfstruct_config.havingPredicates_AND[pr_AND][0] = pr;
                    stMfstruct_config.havingPredicates_AND[pr_AND][1] = pr+1;
                    stMfstruct_config.size_havingPredicates_AND++;

                    pr++;
                    pr_AND++;
                    i+=3;
                    j=0;
                    stMfstruct_config.size_havingPredicates++;
                    continue;
                }
                if(sFileContents[i]=='o' && sFileContents[i+1]=='r' && sFileContents[i]!='\0'){  // 
                    stMfstruct_config.havingPredicates_OR[pr_OR][0] = pr;
                    stMfstruct_config.havingPredicates_OR[pr_OR][1] = pr+1;
                    stMfstruct_config.size_havingPredicates_OR++;
                    
                    pr++;
                    pr_OR++;
                    i+=2;
                    j=0;
                    stMfstruct_config.size_havingPredicates++;
                    continue;
                }
                stMfstruct_config.havingPredicates[pr][j++] = sFileContents[i++];
            }
            line++;
            i++;
        }
    }
}

///\brief This function prints the MF Structure
void printMfStruct(){
    printf("\nCust_Active: %d", stMfstruct.Cust_Active);
    printf("\nProd_Active: %d", stMfstruct.Prod_Active);
    printf("\nDay_Active: %d", stMfstruct.Day_Active);
    printf("\nMonth_Active: %d", stMfstruct.Month_Active);
    printf("\nYear_Active: %d", stMfstruct.Year_Active);
    printf("\nState_Active: %d", stMfstruct.State_Active);
    printf("\ncount_Aggregates: %d", stMfstruct.count_Aggregates);
    printf("\n\n");
}

///\brief This function checks if a given character is a isDigit
///\param c Character to be tested by isDigit()
bool isDigit(char c){
    if(c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9'){
        return true;
    }
    return false;
}

///\brief This function initializes the MF Structure
void redefineMfStruct(){
    // set gv0
    for(int i=0; i<stMfstruct_config.size_sGV0; i++){
        if(stMfstruct_config.sGV0[i][0]=='c' || stMfstruct_config.sGV0[i][0]=='C'){
            stMfstruct.Cust_Active=true;
        }
        if(stMfstruct_config.sGV0[i][0]=='p' || stMfstruct_config.sGV0[i][0]=='P'){
            stMfstruct.Prod_Active=true;
        }
        if(stMfstruct_config.sGV0[i][0]=='d' || stMfstruct_config.sGV0[i][0]=='D'){
            stMfstruct.Day_Active=true;
        }
        if(stMfstruct_config.sGV0[i][0]=='m' || stMfstruct_config.sGV0[i][0]=='M'){
            stMfstruct.Month_Active=true;
        }
        if(stMfstruct_config.sGV0[i][0]=='y' || stMfstruct_config.sGV0[i][0]=='Y'){
            stMfstruct.Year_Active=true;
        }
        if(stMfstruct_config.sGV0[i][0]=='s' || stMfstruct_config.sGV0[i][0]=='S'){
            stMfstruct.State_Active=true;
        }
    }

    // set count of aggregates
    for(int i=0; i<stMfstruct_config.size_select; i++){
        if(isDigit(stMfstruct_config.select[i][0])){
            stMfstruct.count_Aggregates+=1;
        }
    }

    // print
    // printf("\n\nMf struct initialized. Printing ...");
    // printMfStruct();
}

///\brief This function parses a sub-grouping variable GVn and determines the aggregate condition
///\param str Sub-grouping variable GVn, of the format as 1_sum_quant
int whichAggregate(char str[20]){
    if(strstr(str, "sum") != NULL) {
        return 1;
    }
    if(strstr(str, "count") != NULL) {
        return 2;
    }
    if(strstr(str, "avg") != NULL) {
        return 3;
    }
    if(strstr(str, "min") != NULL) {
        return 4;
    }
    if(strstr(str, "max") != NULL) {
        return 5;
    }
}

///\brief This function tests if the current scanned DB row satisfies every SUCH that predicate for a given grouping variable
bool checkSuchThatPredicates (int size_selectPredicates, struct predicate selectPredicates[10], int mfRowNumber) {
    // check against all predicates
    for(int j=0; j<size_selectPredicates; j++){
        if(strcmp(selectPredicates[j].RHS, "cust")==0){
            // does this row of mf structure satisfy the such that predicate
            if(strcmp(stMfstruct.Cust[mfRowNumber], sale_rec.cust)!=0){
                return false;
            }
        }
        if(strcmp(selectPredicates[j].RHS, "prod")==0){
            // does this row of mf structure satisfy the such that predicate
            if(strcmp(stMfstruct.Prod[mfRowNumber], sale_rec.prod)!=0){
                return false;
            }
        }
        if(strcmp(selectPredicates[j].RHS, "day")==0){
            // does this row of mf structure satisfy the such that predicate
            if(stMfstruct.Day[mfRowNumber] != sale_rec.dd){
                return false;
            }
        }
        if(strcmp(selectPredicates[j].RHS, "month")==0){
            // does this row of mf structure satisfy the such that predicate
            if(stMfstruct.Month[mfRowNumber] != sale_rec.mm){
                return false;
            }
        }
        if(strcmp(selectPredicates[j].RHS, "year")==0){
            // does this row of mf structure satisfy the such that predicate
            if(stMfstruct.Year[mfRowNumber] != sale_rec.yy){
                return false;
            }
        }
        if(strcmp(selectPredicates[j].RHS, "state")==0){
            // does this row of mf structure satisfy the such that predicate
            if(strcmp(stMfstruct.State[mfRowNumber], sale_rec.state)!=0){
                return false;
            }
        }
        if(strstr(selectPredicates[j].LHS, "cust")!=NULL && (selectPredicates[j].RHS[0]=='\"' || isDigit(selectPredicates[j].RHS[0]))){
            if(strstr(selectPredicates[j].RHS, sale_rec.cust)==NULL){
                return false;
            }
        }
        if(strstr(selectPredicates[j].LHS, "prod")!=NULL && (selectPredicates[j].RHS[0]=='\"' || isDigit(selectPredicates[j].RHS[0]))){
            if(strstr(selectPredicates[j].RHS, sale_rec.prod)==NULL){
                return false;
            }
        }
        if(strstr(selectPredicates[j].LHS, "day")!=NULL && (selectPredicates[j].RHS[0]=='\"' || !isalpha(selectPredicates[j].RHS[0]))){
            if(atoi(selectPredicates[j].RHS) != sale_rec.dd){
                return false;
            }
        }
        if(strstr(selectPredicates[j].LHS, "month")!=NULL && (selectPredicates[j].RHS[0]=='\"' || !isalpha(selectPredicates[j].RHS[0]))){
            if(atoi(selectPredicates[j].RHS) != sale_rec.mm){
                return false;
            }
        }
        if(strstr(selectPredicates[j].LHS, "year")!=NULL && (selectPredicates[j].RHS[0]=='\"' || !isalpha(selectPredicates[j].RHS[0]))){
            if(atoi(selectPredicates[j].RHS) != sale_rec.yy){
                return false;
            }
        }
        if(strstr(selectPredicates[j].LHS, "state")!=NULL && (selectPredicates[j].RHS[0]=='\"' || isDigit(selectPredicates[j].RHS[0]))){
            if(strstr(selectPredicates[j].RHS, sale_rec.state)==NULL){
                return false;
            }
        }
    }
    return true;
}

///\brief This function adds a new row to the MF structure and initializes aggregate values
///\remark This function is invoked during first scan of the DB table
void addRow(){
    if(stMfstruct.Cust_Active){
        strcpy(stMfstruct.Cust[stMfstruct_config.numRows], sale_rec.cust);
    }
    if(stMfstruct.Prod_Active){
        strcpy(stMfstruct.Prod[stMfstruct_config.numRows], sale_rec.prod);
    }
    if(stMfstruct.Day_Active){
        stMfstruct.Day[stMfstruct_config.numRows] = sale_rec.dd;
    }
    if(stMfstruct.Month_Active){
        stMfstruct.Month[stMfstruct_config.numRows] = sale_rec.mm;
    }
    if(stMfstruct.Year_Active){
        stMfstruct.Year[stMfstruct_config.numRows] = sale_rec.yy;
    }
    if(stMfstruct.State_Active){
        strcpy(stMfstruct.State[stMfstruct_config.numRows], sale_rec.state);
    }

    // initialize all aggregates to 0 for now
    for(int i=0; i<stMfstruct.count_Aggregates; i++){
        if(whichAggregate(stMfstruct_config.sGVN[i])==4){       //min
            stMfstruct.Aggregates[stMfstruct_config.numRows][i] = 999999;
        }    
        else if(whichAggregate(stMfstruct_config.sGVN[i])==5){       //max
            stMfstruct.Aggregates[stMfstruct_config.numRows][i] = -999999;
        }    
        else{
            stMfstruct.Aggregates[stMfstruct_config.numRows][i] = 0;
            stMfstruct.count_avgAggregates[stMfstruct_config.numRows][i] = 0;
        }
    }
}

///\brief This function computes aggregate functions
void processAggregate(int scanNumber){
    struct predicate allPredicates[10];
    struct predicate selectPredicates[10];
    for(int j=0; j<stMfstruct_config.size_suchThatPredicates; j++){
        int LHS_index = 0, condition_index=0, RHS_index=0;
        // deduce LHS, condition and RHS
        for(int k=0; stMfstruct_config.suchThatPredicates[j][k]!='\n' && stMfstruct_config.suchThatPredicates[j][k]!='\0' && k<30; k++){
            while(stMfstruct_config.suchThatPredicates[j][k]!='=' && stMfstruct_config.suchThatPredicates[j][k]!='<' && stMfstruct_config.suchThatPredicates[j][k]!='>' && stMfstruct_config.suchThatPredicates[j][k]!='\0' && stMfstruct_config.suchThatPredicates[j][k]!='\n'){
                if(stMfstruct_config.suchThatPredicates[j][k]==' '){  // ignore spaces
                    k++;
                    continue;
                }
                else{
                    allPredicates[j].LHS[LHS_index++]=stMfstruct_config.suchThatPredicates[j][k];
                    k++;
                }
            }
            allPredicates[j].LHS[LHS_index]='\0';
            if(stMfstruct_config.suchThatPredicates[j][k]!='='){
                k++;
            }
            else{
                allPredicates[j].condition[0]=stMfstruct_config.suchThatPredicates[j][k++];
                allPredicates[j].condition[1]='\0';
            }

            while((isDigit(stMfstruct_config.suchThatPredicates[j][k]) || isalpha(stMfstruct_config.suchThatPredicates[j][k]) || stMfstruct_config.suchThatPredicates[j][k]=='\"') && stMfstruct_config.suchThatPredicates[j][k]!='\r' && stMfstruct_config.suchThatPredicates[j][k]!='\0' && k<30 && stMfstruct_config.suchThatPredicates[j][k]!='\n'){
                if(stMfstruct_config.suchThatPredicates[j][k]==' '){  // ignore spaces
                    k++;
                }
                else{
                    allPredicates[j].RHS[RHS_index++]=stMfstruct_config.suchThatPredicates[j][k];
                    k++;
                }
            }
            allPredicates[j].RHS[RHS_index]='\0';
        }
    }

    // filter for predicates that apply to current grouping variable
    int size_selectPredicates=0;
    for(int i=0; i<stMfstruct_config.size_suchThatPredicates; i++){
        if((allPredicates[i].LHS[0]-'0') == scanNumber){
            selectPredicates[size_selectPredicates++]=allPredicates[i];
        }
    }

    // finally, process the aggregates
    if(whichAggregate(stMfstruct_config.sGVN[scanNumber-1])==1){ // sum

        // loop through mf structure Data
        for(int i=0; i<stMfstruct_config.numRows; i++){
            // if all SUCH THAT predicates satisfy, update aggregate value
            if(checkSuchThatPredicates(size_selectPredicates, selectPredicates, i)){
                stMfstruct.Aggregates[i][scanNumber-1]+=sale_rec.quant;
            }
        }
    }

    if(whichAggregate(stMfstruct_config.sGVN[scanNumber-1])==2){ // count

        // loop through mf structure Data
        for(int i=0; i<stMfstruct_config.numRows; i++){
            // if all SUCH THAT predicates satisfy, update aggregate value
            if(checkSuchThatPredicates(size_selectPredicates, selectPredicates, i)){
                stMfstruct.Aggregates[i][scanNumber-1]+=1;
            }
        }
    }

    if(whichAggregate(stMfstruct_config.sGVN[scanNumber-1])==3){ // avg
        // loop through mf structure Data - compute sum and count
        for(int i=0; i<stMfstruct_config.numRows; i++){
            // if all SUCH THAT predicates satisfy, update aggregate value
            if(checkSuchThatPredicates(size_selectPredicates, selectPredicates, i)){
                stMfstruct.Aggregates[i][scanNumber-1]+=(double)sale_rec.quant;
                stMfstruct.count_avgAggregates[i][scanNumber-1]+=1;
            }
        }

        // loop through mf structure Data - computer avg as sum/count
        for(int i=0; i<stMfstruct_config.numRows; i++){
            // if all SUCH THAT predicates satisfy, update aggregate value
            if(checkSuchThatPredicates(size_selectPredicates, selectPredicates, i)){
                stMfstruct.Aggregates[i][scanNumber-1]=(double)stMfstruct.Aggregates[i][scanNumber-1]/stMfstruct.count_avgAggregates[i][scanNumber-1];
            }
        }
    }

    if(whichAggregate(stMfstruct_config.sGVN[scanNumber-1])==4){ // min

        // loop through mf structure Data
        for(int i=0; i<stMfstruct_config.numRows; i++){
            // if all SUCH THAT predicates satisfy, update aggregate value
            if(checkSuchThatPredicates(size_selectPredicates, selectPredicates, i)){
                if(sale_rec.quant<stMfstruct.Aggregates[i][scanNumber-1]){
                    stMfstruct.Aggregates[i][scanNumber-1]=sale_rec.quant;
                }
            }
        }
    }

    if(whichAggregate(stMfstruct_config.sGVN[scanNumber-1])==5){ // max

        // loop through mf structure Data
        for(int i=0; i<stMfstruct_config.numRows; i++){
            // if all SUCH THAT predicates satisfy, update aggregate value
            if(checkSuchThatPredicates(size_selectPredicates, selectPredicates, i)){
                if(sale_rec.quant>stMfstruct.Aggregates[i][scanNumber-1]){
                    stMfstruct.Aggregates[i][scanNumber-1]=sale_rec.quant;
                }
            }
        }
    }
}

///\brief This function checks if a scanned DB row exists in the MF structure
bool checkRowExists(){
    for(int i=0; i<stMfstruct_config.numRows; i++){
        if(stMfstruct.Cust_Active==false || strcmp(stMfstruct.Cust[i], sale_rec.cust)==0){
            if(stMfstruct.Prod_Active==false || strcmp(stMfstruct.Prod[i], sale_rec.prod)==0){
                if(stMfstruct.Day_Active==false || stMfstruct.Day[i] == sale_rec.dd){
                    if(stMfstruct.Month_Active==false || stMfstruct.Month[i] == sale_rec.mm){
                        if(stMfstruct.Year_Active==false || stMfstruct.Year[i] == sale_rec.yy){
                            if(stMfstruct.State_Active==false || strcmp(stMfstruct.State[i], sale_rec.state) == 0){
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

///\brief This function functions every scanned DB table's row. 
///\brief If row not found, add row. If row found, update aggregates if SUCH THAT predicates satisfy.
void processRow(int scanNumber){
    // bool rowExists=false;
    bool rowExists = checkRowExists();

    // if not exists, add row
    if(!rowExists){
        addRow();
        stMfstruct_config.numRows++;
    }         

    //process aggregates
    if(scanNumber>0){
        processAggregate(scanNumber);
    }
}

///\brief This function prints the MF structure
void printMfStructData(){
    printf("\n");
    for(int i=0; i<stMfstruct_config.numRows; i++){
        if(stMfstruct.Cust_Active){
            printf("%s\t", stMfstruct.Cust[i]);
        }
        if(stMfstruct.Prod_Active){
            printf("%s\t", stMfstruct.Prod[i]);
        }
        if(stMfstruct.Day_Active){
            printf("%d  ", stMfstruct.Day[i]);
        }
        if(stMfstruct.Month_Active){
            printf("%d\t", stMfstruct.Month[i]);
        }
        if(stMfstruct.Year_Active){
            printf("  %d  ", stMfstruct.Year[i]);
        }
        if(stMfstruct.State_Active){
            printf("  %s  ", stMfstruct.State[i]);
        }
        for(int j=0; j<stMfstruct.count_Aggregates; j++){
            if(whichAggregate(stMfstruct_config.sGVN[j])==3) // avg
                printf("%0.2f\t\t", stMfstruct.Aggregates[i][j]);
            else
                printf("%0.0f\t\t", stMfstruct.Aggregates[i][j]);
        }
        printf("\n");
    }
}

//----------------------------------------------------------------------
int main(int argc, char* argv[])
//----------------------------------------------------------------------
{
   //----------------------------------------------------------------------
   // DATABASE CONNECTION
   //----------------------------------------------------------------------
   /// \remark DATABASE CONNECTION STRING
   // EXEC SQL CONNECT TO [dbname] USER [username] IDENTIFIED BY [password];
   { ECPGconnect(__LINE__, 0, "test" , "postgres" , "privateaxs" , NULL, 0); }
#line 715 "generator.pgc"

   /* exec sql whenever sqlerror  sqlprint ; */
#line 716 "generator.pgc"


   // init mfstruct_config
   stMfstruct_config.numRows=0;

   // init mf_Struct
   stMfstruct.Cust_Active=false;
   stMfstruct.Prod_Active=false;
   stMfstruct.Month_Active=false;
   stMfstruct.Year_Active=false;
   stMfstruct.State_Active=false;
   stMfstruct.count_Aggregates=0;
   //for(int i=0; i<10; i++)
   // stMfstruct.Aggregates_count[i]=0;
   
   // Prompt for user input options
   char cInputChoice;
   printf("Welcome to MF/EMF QPE. Select an option to enter input query: \n1.File\n2.Console\n");
   fflush(stdin);
   printf("\nEnter choice (1/2): ");
   scanf(" %c", &cInputChoice);  
   fflush(stdin);
   
   if(cInputChoice=='1'){
       /// \cite https://stackoverflow.com/a/6282396/2535979
       // get file name
       printf("Enter input file name: \n");
       char sFileName[20];
       scanf("%[^\n]s", sFileName);

        // read file contents
        /// \cite https://stackoverflow.com/a/3463793/2535979
       char sFileContents[512];
       FILE *file;
       size_t nread;
       
       file = fopen(sFileName, "r");
       if (file) {
           while ((nread = fread(sFileContents, 1, sizeof sFileContents, file)) > 0)
           if (ferror(file)) {
               printf("\nError reading file!\n");
           }
           fclose(file);
       }

       printf("\nFile read complete. Size: %ld", (long)strlen(sFileContents));
       printf("\n\nContents: \n");
       puts(sFileContents);

       parseInputFileContents(sFileContents);

       printMfStructConfig();
   }

   else if(cInputChoice=='2'){
       // not supported
       printf("\nConsole input not supported at this point. Please restart program and select file-input option");
       exit(0);
   }

   // redefine mf_Struct
   redefineMfStruct();

   //----------------------------------------------------------------------
   // SCAN RECORDS
   //----------------------------------------------------------------------
   // TABLE DETAILS
   // EXEC SQL DECLARE mycursor CURSOR FOR SELECT * FROM [tableName];
   /* declare mycursor cursor for select * from sales */
#line 784 "generator.pgc"

   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set transaction read only", ECPGt_EOIT, ECPGt_EORT);
#line 785 "generator.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 785 "generator.pgc"


   // run n+1 scans (where n = # of grouping variables) 
   for(int i=0; i<=stMfstruct_config.size_sGVN; i++){
       // Open cursor
       { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare mycursor cursor for select * from sales", ECPGt_EOIT, ECPGt_EORT);
#line 790 "generator.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 790 "generator.pgc"

       // Fetch Data
       { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 792 "generator.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 792 "generator.pgc"
 //fetch the first row
       while (sqlca.sqlcode == 0) {
          processRow(i);
          { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 795 "generator.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 795 "generator.pgc"
 //fetch the rest rows
       }
       // Close cursor
       { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close mycursor", ECPGt_EOIT, ECPGt_EORT);
#line 798 "generator.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 798 "generator.pgc"

   }

   // print mf struct after final scan
   printf("\n\nResult -- \n\n");
    // print row names
   for(int i=0; i<stMfstruct_config.size_select; i++){
        printf("%s\t", stMfstruct_config.select[i]);
   }
    // print rows   
   printMfStructData();

   return 0;
}