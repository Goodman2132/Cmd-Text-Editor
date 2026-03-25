#ifndef TEXTENGINE_H
#define TEXTENGINE_H

#include <stdio.h>
#include <stdlib.h>

//--------Structs----------
struct node{

    char letter; 
    struct node *prev;
    struct node *next;  

};
typedef struct node node_x;

struct line{
    
    node_x *dummynode;
    struct line *prevline;
    struct line *nextline;

};
typedef struct line line_x;

//Importing global variables
extern line_x *headline;
extern node_x *cursor;
extern line_x *currentline;

//Functions
node_x *createnewnode(char letter);
line_x *createnewline();
void letterEntry(char entry);
void cursorToLeft();
void cursorToRight();
int cursorPosition();
void cursorToUp();
void cursorToDown();
void mergeLines();
void deleteLetter();
void addnewline();
int getCurrentLineNumber();
void clearEditor();

#endif