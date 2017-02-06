CC		= gcc
CFLAGS	= -Wall -Wpedantic -Wextra -ansi -std=c99 -g
LIB		=
HDR		= treeops.h input.h
SRC		= $(HDR:.h=.c) main.c
OBJ		= $(SRC:.c=.o)
EXE		= wordify

all: $(EXE) Makefile

$(EXE): $(OBJ) $(HDR) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB) 

.PHONY:
clean:
	rm -f $(OBJ)

.PHONY:
clobber: clean
	rm -f $(EXE) tags
	
$(OBJ): $(HDR)
