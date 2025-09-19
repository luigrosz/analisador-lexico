CC = gcc
CFLAGS = -Wall

TARGET = analisador

SRCS = main.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) entrada.txt saida.txt
