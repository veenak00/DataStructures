/* 
Name: Veena Kotha
Cruz ID: vkotha
Class: 12M 
Date: 6/1/19
Description:  The name of this file is Dictionary.c.
	-The role of this file for this project is to create a Dictionary 
    and make any changes to the dictionary, including adding entries, 
    deleting entries, and more using a hash table.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Dictionary.h"

const int tableSize = 101;

typedef struct NodeObj{
	char* key;
	char* value;
	struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

Node newNode(char* k, char* v){
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
 	N->key = k;
 	N->value = v;
 	N->next = NULL;
 	return(N);
}

void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL ){
		free(*pN);
		*pN = NULL;
	}
}

typedef struct DictionaryObj{
	Node *table;

	int numItems;
} DictionaryObj;

Dictionary newDictionary(void){
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	D->table = calloc(tableSize, sizeof(Node));
	assert(D->table != NULL);
	D->numItems = 0;
	return D;
}

void freeDictionary(Dictionary* d1){
	if( d1!=NULL && *d1!=NULL ){
		//if( !isEmpty(*d1) ) popAll(*d1);
		if( !isEmpty(*d1) ) makeEmpty(*d1);
			free(*d1);

			free((*d1)->table);

			*d1 = NULL;
 		}
}

unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);
	if ( shift == 0 )
		return value;
	return (value << shift) | (value >> (sizeInBits - shift));
}

unsigned int pre_hash(char* input) {
	unsigned int result = 0xBAE86554;
	while (*input) {
		result ^= *input++;
		result = rotate_left(result, 5);
	}
	return result;
}

int hash(char* key){
	return pre_hash(key)%tableSize;
}

void printDictionary(FILE* out, Dictionary dSample){
	Node N;
	if(dSample==NULL){
		fprintf(stderr,
			"Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for(int index=0; index<tableSize; index++){
		N = dSample->table[index];
		while(N != NULL){ 	
		//for(N=dSample->table[index]; N!=NULL; N=N->next){ 
			fprintf(out, "%s %s\n", N->key, N->value);
			N = N->next;
		}
	}
}

int isEmpty(Dictionary D){
    if(D->numItems>0){ 
    	return 0;
    }
    else{
      	return 1; 
    }
}

int size(Dictionary D){
	return D->numItems;
}

char* lookup(Dictionary D, char* k){
	Node N = D->table[hash(k)];
	while(N != NULL){
		int check = strcmp(k, N->key);
  		if(check == 0){
  			return N->value; 
  		}
  		N = N->next; 
	}
	return NULL;
}

void insert(Dictionary D, char* k, char* v){
	if(lookup(D,k) == NULL){
		Node N;
		if(D->numItems == 0){  //enters if going to add first element
        	D->table[hash(k)] = newNode(k, v);
        	D->numItems++;
        }
        else{
        	N = newNode(k, v);

        	N->next = D->table[hash(k)]; 
        	D->table[hash(k)] = N; 
        	D->numItems++;
        }
	}
    else{ 
        fprintf(stderr, "Dictionary Error: calling insert() on a duplicate key\n");
		exit(EXIT_FAILURE);
    }
}

void delete(Dictionary D, char* k){
    if(lookup(D,k) != NULL){
    	Node M = D->table[hash(k)];
        if(strcmp(M->key,k)==0){
            D->table[hash(k)] = M->next;  //skip to the node after M
            D->numItems--;
        }

        else if(strcmp(M->next->key,k) == 0){
        	M->next = NULL;
        }
       
        else{
            while(strcmp(M->next->key, k) != 0){ 
                M = M->next;  //keep moving forward until the next node is equal to what you want to delete
            }
            M = M->next;
            Node mTemp = M; //save what the node after the one you want to delete into mTemp
            M->next = mTemp->next; 
            D->numItems--;
            //free(&D->table[hash(k)]);
            free(&M);
        }
    }
    else{
        fprintf(stderr, "Dictionary Error: calling delete() on a non existent key\n");
		exit(EXIT_FAILURE);
    }
}

void makeEmpty(Dictionary D){
	for(int index=0; index<tableSize; index++){
		D->table[index] = NULL;
	}
	D->numItems = 0; 
}