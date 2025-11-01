CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

TARGET = resize.out
SRC = resize.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
