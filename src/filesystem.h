#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "textengine.h" 
#include "UI.h"

#define maxFileCount 100

//Bak
typedef struct fileInformation{
    char unitName[100];
    int isFolder;
} fileInfo;

//------Importing Global Variables-------
extern fileInfo fileList[maxFileCount];
extern int fileCount;
extern int fileNumber;
extern char currentFileName[100];
extern int startView;
extern int viewLimit; 

//------Exporting Functions--------
void readFiles();
void loadFile(char *filename);
void saveFile(char *filename);
void fileCursorDown();
void fileCursorUp();

#endif