CC = g++
SRC = src/main.cpp
OUTPUT = ffetch

SOL2_LDFLAGS := $(shell pkg-config --libs sol2)

$(OUTPUT): $(SRC)
	$(CC) -o $(OUTPUT) $(SRC) -Ofast -llua $(SOL2_LDFLAGS)

install:
	sudo mv $(OUTPUT) /usr/bin/ffetch

uninstall:
	sudo rm -rf /usr/bin/ffetch
