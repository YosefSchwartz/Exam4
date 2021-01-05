#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SUM_CHILDREN 26
#define CONST_TO_CELL 97

/**
This FreqNode contain:
word - represent the word until this node from root
c - the char that associated with this node
count - sum of words
children[] - pointer array to each son
*/
typedef struct FreqNode {
    char *word;
    char c;
    int count;
    struct FreqNode *children [26];
} FreqNode;

void printAtoZ(struct FreqNode *r){
    if((r->count) > 0){
        for(int i=1;i<strlen(r->word);i++){
            printf("%c",r->word[i]);
        }
        printf(" %d\n",r->count);
    }
    
    for(int j=0;j<SUM_CHILDREN;j++){
        if((r->children[j])!=NULL){      
            printAtoZ((r->children[j]));
        }
    } 
    free(r->word);
    free(r);
}

void printZtoA(struct FreqNode *r){ 
    for(int j=SUM_CHILDREN-1;j>=0;j--){
        if((r->children[j])!=NULL){      
            printZtoA((r->children[j]));
        }
    } 
    if((r->count) > 0){
        for(int i=1;i<strlen(r->word);i++){
            printf("%c",r->word[i]);
        }
        printf(" %d\n",r->count);
    }
    free(r->word);
    free(r);
}

struct FreqNode* newNode(char ch, char *getWord) 
{ 
struct FreqNode* node = (struct FreqNode*)malloc(sizeof(struct FreqNode));

size_t len = strlen(getWord);
node->word = malloc(len + 1 );
strcpy(node->word, getWord);
node->word[len] = ch;
node->count = 0;
node->c = ch;
return node; 
}

int main(int argc, char* argcv[]){
    char let;
    struct FreqNode* root = newNode('#',""); 
    struct FreqNode* curr = root;

    while((let = fgetc(stdin))!=-1){
        if(isalpha(let) > 0){
            let = tolower(let);
            int cellIndex = let - CONST_TO_CELL;
            if(curr->children[cellIndex] == NULL){
                struct FreqNode* node = newNode(let,curr->word); 
                curr->children[cellIndex] = node;
                curr = node;
            }
            else{
                curr = (curr->children[cellIndex]);
            }      
        }
        else{
            if(curr!=root){
                curr->count++;
                curr = root;               
            }
        }
    }
    free(curr->word);
    free(curr);
    
    if(argc == 1){
        for(int i=0;i<SUM_CHILDREN;i++){
            if(root->children[i]!=NULL){
                printAtoZ(root->children[i]);
            }
        }
    }
    else if(*argcv[1] == 'r') {
         for(int i=SUM_CHILDREN-1;i>=0;i--){
            if(root->children[i]!=NULL){
                printZtoA(root->children[i]);
            }
        } 
    }
    else{
        printf("Invalid sign!");
    }
    free(root->word);
    return 0;
}