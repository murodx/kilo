#include "kilo.h"
// Функция для вывода сообщения об ошибке и завершения программы
void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s); // Вывод системного сообщения об ошибке
  exit(1); // Завершение программы с кодом ошибки 1
}

// Функция для восстановления исходных настроек терминала при завершении
// программы
void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
    die("tcsetattr"); // Восстановление исходных настроек, выход из программы
                      // при ошибке
}

// Функция включения "сырого" режима ввода в терминале
void enableRawMode() {
  tcgetattr(
      STDIN_FILENO,
      &E.orig_termios); // Сохранение текущих настроек терминала в orig_termios
  atexit(disableRawMode); // Регистрация функции disableRawMode для вызова при
                          // завершении программы

  struct termios raw =
      E.orig_termios; // Копирование текущих настроек в структуру raw

  // Настройки для "сырого" режима
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP |
                   IXON); // Отключение некоторых флагов ввода
  raw.c_oflag &= ~(OPOST); // Отключение флагов вывода
  raw.c_cflag |= (CS8); // Установка флага для 8-битного символа
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // Отключение флагов режима

  raw.c_cc[VMIN] = 0; // Минимальное количество символов для чтения
  raw.c_cc[VTIME] = 1; // Таймаут ожидания ввода (в десятых долях секунды)

  // Применение новых настроек терминала
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr");
}

int editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN)
      die("read");
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1)
      return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
      return '\x1b';

    if (seq[0] == '[') {
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1)
          return '\x1b';
        if (seq[2] == '~') {
          switch (seq[1]) {
          case '1':
            return HOME_KEY;
          case '3':
            return DEL_KEY;
          case '4':
            return END_KEY;
          case '5':
            return PAGE_UP;
          case '6':
            return PAGE_DOWN;
          case '7':
            return HOME_KEY;
          case '8':
            return END_KEY;
          }
        }
      } else {
        switch (seq[1]) {
        case 'A':
          return ARROW_UP;
        case 'B':
          return ARROW_DOWN;
        case 'C':
          return ARROW_RIGHT;
        case 'D':
          return ARROW_LEFT;
        case 'H':
          return HOME_KEY;
        case 'F':
          return END_KEY;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
      case 'H':
        return HOME_KEY;
      case 'F':
        return END_KEY;
      }
    }
    return '\x1b';
  } else {
    return c;
  }
}
int getCursorPosition(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;
  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
    return 1;

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1)
      break;
    if (buf[i] == 'R')
      break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[')
    return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
    return -1;

  return 0;
}

int getWindowSize(int *rows, int *cols) {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
      return -1;
    return getCursorPosition(rows, cols);
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}