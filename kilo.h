#ifndef KILO_H
#define KILO_H
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE
#include <ctype.h> // Подключение функций для проверки символов (например, iscntrl)
#include <errno.h> // Подключение библиотеки для работы с кодами ошибок
#include <fcntl.h>
#include <stdio.h> // Подключение стандартной библиотеки ввода-вывода
#include <stdlib.h> // Подключение стандартных функций C (например, exit)
#include <string.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <sys/types.h>
#include <termios.h> // Подключение библиотеки для работы с настройками терминала
#include <unistd.h> // Подключение POSIX API для работы с системными вызовами (например, read, tcgetattr)
#include <time.h>

#define KILO_VERSION "0.0.1"
#define KILO_TAB_STOP 8
#define KILO_QUIT_TIMES 3

#define CTRL_KEY(k) ((k) & 0x1f)

enum editorKey {
  BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

enum editorHighlight {
  HL_NORMAL = 0,
  HL_COMMENT,
  HL_MLCOMMENT,
  HL_KEYWORD1,
  HL_KEYWORD2,
  HL_STRING,
  HL_NUMBER,
  HL_MATCH
};


#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

/*** data ***/

struct editorSyntax {
  char *filetype;
  char **filematch;
  char **keywords;
  char *singleline_comment_start;
  char *multiline_comment_start;
  char *multiline_comment_end;
  int flags;
};

typedef struct erow {
  int idx;
  int size;
  int rsize;
  char *chars;
  char *render;
  unsigned char *hl;
  int hl_open_comment;
} erow;

struct editorConfig {
  int cx, cy;
  int rx;
  int rowoff;
  int coloff;
  struct termios
      orig_termios; // Переменная для хранения исходных настроек терминала
  int screenrows;
  int screencols;
  int numrows;
  erow *row;
  int dirty;
  char *filename;
  char statusmsg[80];
  struct editorSyntax *syntax;
  time_t statusmsg_time;
};
extern struct editorConfig E;
extern char *C_HL_extensions[];
extern char *C_HL_keywords[];
extern struct editorSyntax HLDB[];
extern const unsigned int HLDB_ENTRIES;


/*** prototypes ***/

void editorSetStatusMessage(const char *fmt, ...);
void editorRefreshScreen();
char *editorPrompt(char *prompt, void (*callback)(char *, int));


/*** terminal ***/
void die(const char *s);
void disableRawMode();
void enableRawMode();
int editorReadKey();
int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);

/*** syntax highlighting ***/
int is_separator(int c);
void editorUpdateSyntax(erow *row);
int editorSyntaxToColor(int hl);
void editorSelectSyntaxHighlight();

/***row operations */
int editorRowCxToRx(erow *row, int cx);
int editorRowRxToCx(erow *row, int rx);
void editorUpdateRow(erow *row);
void editorInsertRow(int at, char *s, size_t len);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);

/*** editor operations ***/
void editorInsertChar(int c);
void editorInsertNewLine();
void editorDelChar();
char *editorRowsToString(int *buflen);
void editorOpen(char *filename);
void editorSave();

/*** find ***/
void editorFindCallback(char *query, int key);
void editorFind();

/***append buffer */
struct abuf {
  char *b;
  int len;
};

#define ABUF_INIT                                                              \
  { NULL, 0 }

void abAppend(struct abuf *ab, const char *s, int len);
void abFree(struct abuf *ab);

/*** output */
void editorScroll();
void editorDrawRows(struct abuf *ab);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);
void editorRefreshScreen();
void editorSetStatusMessage(const char *fmt, ...);

/*** Input */
char *editorPrompt(char *prompt, void (*callback)(char *, int));
void editorMoveCursor(int key);
void editorProcessKeypress();

/*** init ***/

void initEditor();
#endif // KILO_H