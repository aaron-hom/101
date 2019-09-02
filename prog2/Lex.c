//Lex.c
//Aaron Hom
//pa2
//Takes in an input file, sorts lines in alphabetical order, prints to out file

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 500

int main(int argc, char* argv[]){
  int numLines = -1;
  FILE *in, *out;
  char words[MAX_LEN];

  if(argc != 3){ //error message if wrong number of arguments
    printf("Wrong number of arguments");
    exit(1);
  }

  in = fopen(argv[1], "r"); //files for reading and writing
  out = fopen(argv[2], "w");

  if(in == NULL){
    printf("File for reading not found"); //error checking
    exit(1);
  }
  if(out == NULL){
    printf("File for writing not found");
    exit(1);
  }

  while(fgets(words, MAX_LEN, in) != NULL){ //counts strings 
    numLines++;
  }

  rewind(in); //set back to start

  char line[numLines][MAX_LEN];
  int tempNumLines = 0;

  while(fgets(words, MAX_LEN, in) != NULL){ //copies lines of in file
    strcpy(line[tempNumLines++], words);
  }

  List A = newList(); //creates new list
  append(A, 0); //inserts first element in list
 
  for(int i = 1; i < numLines+1 ; i++){ //places strings in their appropriate place
    char *tempLine = line[i];
    int j = i-2;
    moveBack(A);
    while(j >= 0 && strcmp(tempLine, line[get(A)]) <= 0){
      j--;
      movePrev(A);
    }
    if(index(A) >= 0){
      insertAfter(A, i);
    }else{
      prepend(A, i);
    }
  }
  moveFront(A);

  while(index(A) >= 0){ //prints out ordered strings from out file
    fprintf(out, "%s\n", line[get(A)]);
    moveNext(A);
  }

  fclose(in); //closes files for reading and writing
  fclose(out);

  freeList(&A); //frees memory
  return(0);
}
