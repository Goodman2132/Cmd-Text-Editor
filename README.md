# Cmd Text Editor

## Features

- Built-In File Browser: Navigate through directories, list files and folders, open files and folders via File Browser directly within the editor.
- Saving System: Save changes to existing files or create new one with a naming prompt.
- Viewport and Scrolling: Scroll through big texts or directories easily with a viewport engine thats responsive to terminal size.
- Basic UI: Low level UI that uses Windows API calls for screen updates and cursor movement.

## File Structure

- Text Engine: Handles character inputs with node and line elements of Doubly Linked List and responsible for cursor movement.
- File System: Scans through directories , lists them , saves and loads existing files.
- UI : Renders user interface and file context for user.
- Main: Brings all functions and operations and starts the editor. 

##Controls
- Tab : Switch between editor mode and file browser mode.
- Arrow Keys : Horizontal and vertical cursor movement.
- Enter : Add a newline in editor mode or open file/folder in file browser mode.
- CTRL + S : Save the changes in current file or create a new one with prompt.
- ESC : Close the program.
