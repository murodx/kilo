CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

SOURCES = $(wildcard *.c)
EXEC = kilo

# Основное правило: сборка всех .c файлов в исполняемый файл
$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

# Правило для очистки
clean:
	rm -f $(EXEC)

# Правило для проверки формата кода с clang-format
format:
	clang-format -n $(SOURCES)
	clang-format -i $(SOURCES)

# Правило для статического анализа с cppcheck
# cppcheck:
# 	cppcheck --enable=all --std=c99 --suppress=missingIncludeSystem $(SOURCES)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

# Правило для выполнения всех проверок
check: format cppcheck
