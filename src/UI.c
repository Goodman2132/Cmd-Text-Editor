#define EDITOR_UPPER_INFO  3 //Upper margin for Info 
#define EDITOR_LOWER_LINE  1 //Lower margin
#define BROWSER_UPPER_INFO  4 
#define BROWSER_LOWER_LINE  2 


#include "ui.h"
#include "filesystem.h"
#include "textengine.h"
#include <stdio.h>
#include <windows.h>

//-----Global Variables------
int startView = 0; //Viewport upper limit
int browserDisplayLimit = 15; 
int startLine = 0; 
int editorDisplayLimit = 15; 

//-----Terminal Misc-----------
int getTerminalHeight(){

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int height;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    return height;
}

void hideCmdCursor(){

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(hOut, &cursorInfo);

}

void showCmdCursor(){

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = TRUE; 
    SetConsoleCursorInfo(hOut, &cursorInfo);

}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//----------UI and Scroll--------------
void updateTerminalSize(){

    int terminalHeight = getTerminalHeight();
    
    editorDisplayLimit = terminalHeight - (EDITOR_UPPER_INFO +EDITOR_LOWER_LINE); 

    if (editorDisplayLimit < 1) {
        editorDisplayLimit = 1; //Display at least 1 line
    }
    
    browserDisplayLimit = terminalHeight - (BROWSER_UPPER_INFO + BROWSER_LOWER_LINE); 

    if (browserDisplayLimit < 1){ //Display at least 1 file
        browserDisplayLimit = 1; 
    }
}

void editorVisual(){
    
    line_x *templine=headline;
    int lineCount=0;

    system("cls"); //Clear Screen
    printf("Editor Mode\n");
    printf("CMD Text Engine | Tab: File Browser | Esc: Shutdown\n");
    printf("--------------------------------------------------\n");

    
    while (templine!=NULL && lineCount<startLine){ //Skip the lines above viewport
        templine=templine->nextline;
        lineCount++;
    }

    //Printing nodes
    int printedLines=0;
    while (templine!=NULL && printedLines<editorDisplayLimit){
        node_x *tempnode=templine->dummynode;
        
        if (tempnode==cursor){
            printf("|"); //If in beginning print cursor first
        } 
        tempnode = tempnode->next;

        while (tempnode!=NULL) {
            printf("%c", tempnode->letter);
            if (cursor==tempnode){
               printf("|"); //Print cursor
            }
            tempnode=tempnode->next;
        }
        printf("\n");
        templine=templine->nextline;
        printedLines++;
    }

}

void fileBrowserVisual() {
    
    system("cls");
    printf("File Browser Mode\n");
    printf("Arrow Keys : Up and Down | Enter : Open File / Move to Folder | Tab : Return to Editor\n");
    printf("-----------------------------------\n\n");

    for (int i = startView; i < startView + browserDisplayLimit && i < fileCount; i++){ //Print files | Dont exceed file count or viewport
  
        if (i == fileNumber) {
            printf(" -> "); //Cursor
        }

        printf("%s\n", fileList[i].unitName);
    }
    
    printf("\n-----------------------------------\n");
}

void scrollEditor(){

    int currentLineNo = getCurrentLineNumber();
    int terminalHeight = getTerminalHeight();
    int displayLimit = terminalHeight - (EDITOR_UPPER_INFO +EDITOR_LOWER_LINE); //For toolbox

    if (currentLineNo < startLine){ //When cursor moves above viewport
        startLine = currentLineNo;
    }
    
    else if (currentLineNo>=startLine+displayLimit){ //When cursor moves under viewport
        startLine = currentLineNo - displayLimit + 1;
    }
    
}

void getFileName(char* fileName, int maxLength){

    int terminalHeight = getTerminalHeight();
    
    fflush(stdin); //Clearing for ghost inputs

    gotoxy(0, terminalHeight - 2); //Move Cmd cursor
    
    printf("--------------------------------------------------\n");
    printf(" Enter file name: ");
    
    showCmdCursor();

    fgets(fileName, maxLength, stdin);
    fileName[strcspn(fileName, "\n")] = 0; // \n temizle

    hideCmdCursor();

}


