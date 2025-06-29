CC = gcc

SRC_DIR = src

CFLAGS = -Wall -Wextra -std=c99

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/shell.c $(SRC_DIR)/filesystem.c

TARGET = ArquivosSO
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
clean:
	rm -f $(TARGET)