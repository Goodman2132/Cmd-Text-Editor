#include "textengine.h" 
#include <stdlib.h>     

//--------Global Variables---------
line_x *headline = NULL;
node_x *cursor = NULL;
line_x *currentline = NULL;

//------ Creating Elements --------
node_x *createnewnode(char letter){

    node_x *newnode=malloc(sizeof(node_x));
    newnode->letter = letter;
    newnode->prev=NULL;
    newnode->next=NULL;

    return newnode;
}

line_x *createnewline(){

    line_x *newline = malloc(sizeof(line_x));
    newline->dummynode=createnewnode('\0');
    newline->nextline=NULL;
    newline->prevline=NULL;

    return newline;
}

//-------- Key Operations --------

//Input
void letterEntry(char entry){

    node_x *newnode = createnewnode(entry);

    newnode->next=cursor->next;
    newnode->prev=cursor;

    if(cursor->next != NULL){
        cursor->next->prev=newnode;
    }
        
    cursor->next=newnode;
    cursor=newnode;
}

//Arrow Functions
void cursorToLeft(){

    if(cursor!=currentline->dummynode){
        cursor=cursor->prev;
    }
}

void cursorToRight(){

    if(cursor->next!=NULL){
        cursor=cursor->next;
    }
}

int cursorPosition(){
    
    int count=0;
    node_x *temp=currentline->dummynode;
    while(temp!=cursor){
        temp=temp->next;
        count++;
    }
    return count;

}

void cursorToUp(){

    int cursorposition = cursorPosition();

    if(currentline->prevline!=NULL){
        currentline=currentline->prevline;
    }
    else{
        return;
    }

    cursor=currentline->dummynode;
    int temp=0;
    while(temp!=cursorposition){

        if(cursor->next==NULL){//Going to end of the line
            break;
        }

        cursor=cursor->next;
        temp++;
    }

    return;
}

void cursorToDown(){
    
    int cursorposition=cursorPosition();

    if(currentline->nextline!=NULL){
        currentline=currentline->nextline;
    }
    else{
        return;
    }

    cursor=currentline->dummynode;
    int temp=0;
    while(temp!=cursorposition){
        
        if(cursor->next==NULL){
            break;
        }
        
        cursor=cursor->next;
        temp++;
    }
    
}

//Backspace Operations
void mergeLines() {

    if (currentline->prevline==NULL){
        return;
    }

    line_x *deletedLine=currentline;
    line_x *upperLine=currentline->prevline;
    node_x *upperLast=upperLine->dummynode;

    while (upperLast->next != NULL) {
        upperLast=upperLast->next;
    }

    //Connecting nodes
    if (deletedLine->dummynode->next!=NULL) {
        upperLast->next=deletedLine->dummynode->next;
        deletedLine->dummynode->next->prev=upperLast;
    }

    //Connecting Lines
    upperLine->nextline=deletedLine->nextline;
    if (deletedLine->nextline!=NULL) {
        deletedLine->nextline->prevline=upperLine;
    }

    cursor = upperLast; 
    currentline = upperLine;

    free(deletedLine->dummynode);
    free(deletedLine);
}

void deleteLetter(){

    if(cursor==currentline->dummynode){
        if(currentline->prevline!=NULL){
            mergeLines();
            return;
        }
    }

    node_x *deletednode=cursor;
    node_x *targetcursor=cursor->prev;

    if(targetcursor==NULL){
        return;
    }
    //connecting right to left
    if(cursor->next!=NULL){
        cursor->next->prev=cursor->prev;
    }
    //connecting left to right
    if(cursor->prev!=NULL){
        cursor->prev->next=cursor->next;
    }

    cursor = targetcursor;
    free(deletednode);
}

//Enter
void addnewline(){

    line_x *newline = createnewline();

    //Arranging lines
    newline->prevline=currentline;
    newline->nextline=currentline->nextline;
    if(currentline->nextline!=NULL){
        currentline->nextline->prevline=newline;
    }
    currentline->nextline=newline;
    
    //Arranging nodes
    if(cursor->next!=NULL){//a|b    
        newline->dummynode->next=cursor->next;
        cursor->next->prev=newline->dummynode;
        cursor->next=NULL;//(?)
    }

    currentline=newline;
    cursor=currentline->dummynode;

    return;
}

int getCurrentLineNumber(){
    
    int count=0;
    line_x *temp=headline;
    while (temp!=NULL && temp!=currentline) {
        temp=temp->nextline;
        count++;
    }

    return count;
}

//Clearing Editor 
void clearEditor() {

    line_x *currentLine = headline;
    line_x *nextLine;

    while (currentLine != NULL) {
        
        node_x *currentNode = currentLine->dummynode;
        node_x *nextNode;

        //Freeing nodes
        while (currentNode != NULL) {
            nextNode = currentNode->next; 
            free(currentNode);            
            currentNode = nextNode;      
        }

        //Freeing Lines
        nextLine = currentLine->nextline;
        free(currentLine); 
        currentLine = nextLine;
    }

    //Resetting editor 
    headline = createnewline(); 
    currentline = headline;
    cursor = currentline->dummynode;
}