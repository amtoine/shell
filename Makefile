ANSI_COLOR_CODES_REMOTE = "https://gist.githubusercontent.com/RabaDabaDoba/145049536f815903c79944599c6f952a"
ANSI_COLOR_CODES_VERSION = "fb1503af3caaf4d1188f3f9b6c356b219d6a06eb"

CC = gcc
CFLAGS = "-std=gnu17"
BIN = build/shell

.PHONY: deps
deps:
	curl -fLo "ANSI-color-codes.h" "$(ANSI_COLOR_CODES_REMOTE)/raw/$(ANSI_COLOR_CODES_VERSION)/ANSI-color-codes.h"

.PHONY: build
build: log.c shell.c
	$(CC) $(CFLAGS) $^ -o $(BIN)

.PHONY: run
run: $(BIN)
	./$(BIN)
