CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

TARGET = ncurses_exit_test.out
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	@echo "Running valgrind memory leak check..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all clean test
