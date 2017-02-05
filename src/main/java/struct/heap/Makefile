# for heapsort.c
# AUTHOR: JIAHONG FONG
# DATE: Wednesday 16 November  01:26:05 AEDT 2016


CC  		= gcc
CFLAGS  	= -Wextra -Wall -Wpedantic -ansi -std=c99 -pg
HDR		= heap.h
SRC		= $(HDR:.h=.c) heapsort.c
OBJ		= $(SRC:.c=.o)
EXE		= heapsort

.PHONY:
$(EXE): $(OBJ) $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

$(OBJ): $(HDR)

.PHONY:
clean:
	rm -rf $(OBJ) gmon.out

.PHONY:
clobber: clean
	rm -f $(EXE)
