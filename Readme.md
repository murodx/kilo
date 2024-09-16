# Enhanced Kilo Text Editor

This project is an enhanced version of the Kilo text editor, written in C. It includes additional features and improvements over the original Kilo editor.

## Features

- **Basic Text Editing**: Edit text files with standard editing capabilities.
- **Search Functionality**: Search through your text files easily.
- **Syntax Highlighting**: Syntax highlighting for C programming language.
- **Line Wrapping and Scrolling**: Efficiently handle long lines and scrolling.

## File Structure

The project is organized into the following files for improved readability and maintenance:

- **`appendBuffer.c`**: Functions related to appending data to buffers.
- **`find.c`**: Functions for searching text within the editor.
- **`input.c`**: Handling of user input.
- **`kilo.h`**: Header file with definitions and declarations.
- **`output.c`**: Functions for output operations.
- **`rowOperations.c`**: Functions for row manipulation.
- **`terminal.c`**: Terminal-specific operations.
- **`editorOperations.c`**: General editor functions.
- **`init.c`**: Initialization functions.
- **`kilo.c`**: Main implementation file.
- **`Makefile`**: Build script for compiling the project.
- **`Readme.md`**: Documentation file.
- **`syntax.c`**: Syntax highlighting functions.

## Compilation

To compile the editor, use the provided `Makefile`. Run the following command in your terminal:

```bash
make
./kilo <filename>
```

## Acknowledgements

This project is based on the Kilo text editor, originally created by [**Salvatore Sanfilippo**](https://github.com/antirez/kilo). 

The original Kilo editor is available at [https://github.com/antirez/kilo](https://github.com/antirez/kilo).

## License

This project is based on the Kilo text editor, which is licensed under the BSD License. 

**Original License:**

Copyright (c) 2016, Salvatore Sanfilippo <antirez at gmail dot com>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

For more details, please refer to the original [Kilo repository](https://github.com/antirez/kilo).




