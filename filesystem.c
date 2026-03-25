#include "filesystem.h"
#include "textengine.h"
#include "UI.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

//------Global Variables---------
fileInfo fileList[maxFileCount];
int fileCount=0;
int fileNumber=0;
char currentFileName[100]=""; 

//--------File Operations--------
void readFiles(){ //Reading files to list files 

    DIR *directory;
    struct dirent *dir;
    struct stat st;

    
    directory = opendir(".");
    fileCount = 0;

    if (directory){

        while ((dir=readdir(directory))!= NULL && fileCount<maxFileCount){

            if (strcmp(dir->d_name, ".")==0){ //Skip current folder
                continue;
            }

            strcpy(fileList[fileCount].unitName,dir->d_name);//Copying the name to the fileList array

            if (stat(dir->d_name, &st)==0){
                fileList[fileCount].isFolder = S_ISDIR(st.st_mode); //Checking if folder
            }
            
            fileCount++;
        }

        closedir(directory);
    }
}

void loadFile(char *filename){

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return;

    //Copying current file name
    strcpy(currentFileName, filename);

    clearEditor();
    char c;

    //Printing opened file to the editor till EOF
    while((c = fgetc(fp))!=EOF){

        if(c == '\r'){ //Useless
            continue;
        }
        else if(c == '\n'){ //Newline
            addnewline();
        } 
        else{
            letterEntry(c); //Adding character
        }
    }
    fclose(fp);

    //Moving cursor to beginning
    cursor=headline->dummynode;
    currentline=headline;
}

void saveFile(char *filename){

    if (filename==NULL || strlen(filename)==0){ //Given incorrect filename
        return;
    }

    FILE *fp=fopen(filename, "w"); // Write if exist else create

    if (fp==NULL){
        printf("NULL Error!\n");
        return;
    }

    line_x *templine=headline;

    while (templine!=NULL){

        node_x *tempnode=templine->dummynode->next;
        
        //Copying node elements
        while (tempnode!=NULL) {
            fputc(tempnode->letter, fp);
            tempnode=tempnode->next;
        }

        //If next line exists : \n 
        if (templine->nextline!=NULL){
            fputc('\n', fp);
        }
        
        templine=templine->nextline;
    }

    fclose(fp);
}

//------Browsing Through Files------
void fileCursorDown(){
    
    if(fileNumber<fileCount-1){ //If not in last file

        fileNumber++;

        if (fileNumber>=startView+browserDisplayLimit) {
            startView++; //Moving viewport to see current file
        }
    }

    else{ //Move cursor to beginning if not in last file
        fileNumber=0; 
        startView=0;
    }
}

void fileCursorUp(){

    if (fileNumber > 0){ //If not in first file

        fileNumber--;

        if (fileNumber<startView){
            startView--;
        }
    }

    else{
        fileNumber = fileCount - 1;
        startView = fileCount - browserDisplayLimit; //Moving viewport to last file

        if(startView < 0){
            startView = 0; 
        }
    }
}