#ifndef UI_H
#define UI_H

#include <windows.h>
#include "textengine.h" 
#include "filesystem.h"

extern int startView;
extern int browserDisplayLimit;
extern int startLine;
extern int fileNumber;
extern int fileCount;

// Fonksiyonlar
void updateTerminalSize();
int getTerminalHeight();
void hideCmdCursor();
void editorVisual();
void fileBrowserVisual();
void scrollEditor();
void getFileName(char *fileName , int maxLength);

#endif