#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include "textengine.h"
#include "filesystem.h"
#include "ui.h"

int main(){
    
    hideCmdCursor();
    
    headline = createnewline();
    currentline = headline;
    cursor = currentline->dummynode;

    // 0 for editor 1 for file browser
    int activeMode = 0; 
    char ch;

    while (1) {

        //Start with current mode
        if (activeMode == 0) {

            updateTerminalSize();
            scrollEditor(); //Doom scrolling
            editorVisual(); 

        }

        else if (activeMode == 1) { //File Browser Mode
            fileBrowserVisual(); 
        }
        

        ch = getch(); //Reading Inputs

        if (ch == 27){ //Shutdown - Esc
            break;
        }
        
        if (ch == 9){ //Switching modes - Tab

            if (activeMode==0){

                fileNumber = 0; //Move cursor to first file
                startView = 0;
                readFiles(); // List files
                activeMode = 1;
                
            } 
            else{
                activeMode=0;
            }
            continue;

        }

        //Editor Mode
        if (activeMode == 0){

            if (ch == 19){ //Save file - CTRL + S

                if(strlen(currentFileName)>0){ //Write to file if one is open
                    saveFile(currentFileName);
                }

                else{ //Create a file if a file is not open
                    
                    char newFileName[100];
                    getFileName(newFileName,100);
                    
                    if (strlen(newFileName)>0){
                        
                        strcpy(currentFileName, newFileName);
                        
                        if (strstr(currentFileName, ".txt") == NULL){ //Add .txt 
                            strcat(currentFileName, ".txt");
                        }
                    } 

                    else {
                        // Kullanıcı hiçbir şey yazmadan Enter'a bastıysa varsayılan bir isim ver
                        strcpy(currentFileName, "adsiz_dosya.txt");
                    }
                        
                    saveFile(currentFileName);
                } 
            }

            else if (ch == 13) { //Adding Newline - Enter
                addnewline();
            }

            else if (ch == 8) { //Deleting Nodes - Backspace
                deleteLetter();
            }

            else if (ch == 0 || ch == -32) { //Cursor Movement - Arrow Keys

                ch = getch();

                switch (ch) {
                    case 72: cursorToUp();    break;
                    case 80: cursorToDown();  break;
                    case 75: cursorToLeft();  break;
                    case 77: cursorToRight(); break;
                }
            }

            else{ 
                if (ch >= 32 && ch <= 126){ //Character Entry
                    letterEntry(ch);
                }
            }
        } 
        
        // File Browser Info
        else if (activeMode == 1){

            if (ch == 0 || ch == -32){ //Cursor Movement - Arrow Keys

                ch = getch();

                if (ch == 72){
                    fileCursorUp();
                }
                else if (ch == 80){
                    fileCursorDown();
                }

            }

            else if (ch == 13) { //Open file on editor or move to folder

                if (fileList[fileNumber].isFolder){ //Cursor on folder

                    if (chdir(fileList[fileNumber].unitName) == 0) {
                        fileNumber = 0;
                        startView = 0;
                        readFiles();
                    }
                } 
                else{ //Cursor on file

                    loadFile(fileList[fileNumber].unitName);
                    startLine = 0; //Move viewport to beginning
                    activeMode = 0;
                }
            }
        }
    }

    return 0;
}