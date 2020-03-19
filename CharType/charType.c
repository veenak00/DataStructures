/*Name: Veena Kotha
Cruz ID: vkotha
Class: 12M 
Date: 5/7/19
Description:  The name of this file is charType.c.
	-The role of this file for this project is to print out the amount of 
	alphabetical characters, digits, punctuation, and spaces in aan input file.
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>
#define MAX_STRING_LENGTH 100

void extract_chars(char* s, char* a, char* d, char* p, char* w){
    int index=0, a_alphaCount=0, d_digCount=0, p_puncCount=0, w_spaceCount=0;
    while(s[index]!='\0' && index<MAX_STRING_LENGTH){
        if(isalpha((int)s[index])){
        	a[a_alphaCount] = s[index];
        	a_alphaCount++;
        }
        if(isdigit((int)s[index])){
        	d[d_digCount] = s[index];
        	d_digCount++;
        }

        if(ispunct((int)s[index])){
        	p[p_puncCount] = s[index];
        	p_puncCount++;
        }
        index++;
    }
    int i=0;
    while(s[i]!='\0' && i<MAX_STRING_LENGTH){
        if(isspace((int)s[i])) w[w_spaceCount++] = s[i];
            i++;

    }
    a[a_alphaCount] = '\0';
    d[d_digCount] = '\0';
    p[p_puncCount] = '\0';
    w[w_spaceCount] = '\0';
}

int main(int argc, char* argv[]){
	FILE* in;                                
    FILE* out;                                 
    char* alpha;     
    char* num;
    char* punctuation;
    char* whitespace;
    char* line;
    int numLine = 1;

   // check command line for correct number of arguments 
    if( argc != 3 ){
        printf("Usage: %s input-file output-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // open input file for reading 
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
   // open output file for writing 
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

   // allocate strings word and capsWord from heap memory  
    alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
    num = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
    punctuation = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
    whitespace = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
    line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
    assert(line!=NULL && alpha!=NULL && num!=NULL && punctuation!=NULL && whitespace!=NULL);
 
    while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
        extract_chars(line, alpha, num, punctuation, whitespace);
        fprintf(out, "line %d contains:\n", numLine);
        fprintf(out, "%d alphabetical characters: %s\n", (int) strlen(alpha), alpha);
        fprintf(out, "%d numeric characters: %s\n", (int) strlen(num), num);
        fprintf(out, "%d punctuation characters: %s\n", (int) strlen(punctuation), punctuation);
        fprintf(out, "%d whitespace characters: %s\n", (int) strlen(whitespace), whitespace);
    	numLine++;
    }

   // free heap memory associated with string variables word
    free(line);
    free(alpha);
    free(num);
    free(punctuation);
    free(whitespace);
   
   // close input and output files 
    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
	