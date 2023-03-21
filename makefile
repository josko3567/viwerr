STATIC=viwerr.a

CC = gcc
CFLAGS = -Wall -Wextra -Winline -Wpedantic -g\
	 -Wformat=2 -Wno-unused-parameter -Wshadow \
	 -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
	 -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -pipe \
	 -std=c99 -O3

LIBS = ./src
SRC = $(foreach D,$(LIBS),$(wildcard $(D)/*.c))   
OBJ = $(patsubst %.c,%.o,$(SRC))   

$(STATIC): $(OBJ)
	@echo "[Link (Static)]"
	@ar rcs $@ $^

%.o: %.c
	@echo [Compile] $<
	@$(CC) -lm -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(STATIC)

.PHONY: test
test: $(STATIC)
	$(CC) $(CFLAGS) test/test.c -o test/test.out $(STATIC)
	@echo "test/test.out started --->"
	@./test/test.out
	@echo "test/test.out ended <---"



