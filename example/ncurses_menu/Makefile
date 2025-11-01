CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

TARGET = menu.out
SRC = menu.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
