#include "kilo.h"

struct editorConfig E;
char *C_HL_extensions[] = {".c", ".h", ".cpp", NULL};
char *C_HL_keywords[] = {"switch",    "if",      "while",   "for",    "break",
                         "continue",  "return",  "else",    "struct", "union",
                         "typedef",   "static",  "enum",    "class",  "case",
                         "int|",      "long|",   "double|", "float|", "char|",
                         "unsigned|", "signed|", "void|",   NULL};
struct editorSyntax HLDB[] = {
    {"c", C_HL_extensions, C_HL_keywords, "//", "/*", "*/",
     HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS},
};
const unsigned int HLDB_ENTRIES = sizeof(HLDB) / sizeof(HLDB[0]);

int main(int argc, char *argv[]) {
  enableRawMode(); // Включение "сырого" режима
  initEditor();
  if (argc >= 2) {
    editorOpen(argv[1]);
  }
  editorSetStatusMessage("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}
