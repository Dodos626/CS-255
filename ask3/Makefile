
###################################################
#
# file: Makefile
#
# @Author:   Iacovos G. Kolokasis
# @Version:  10-02-2021
# @email:    kolokasis@csd.uoc.gr
#
# Makefile
#
####################################################

clean: sudoku
	rm sudoku.exe
	rm sudoku.o
	rm grid.o
sudoku: sudoku.o grid.o
	@gcc -Wall -ansi -g -pedantic sudoku.o grid.o -o sudoku.exe
	
	

sudoku.o: src/sudoku.c src/sudoku.h
	@gcc -Wall -g -ansi -pedantic -c src/sudoku.c

grid.o: src/grid.c src/grid.h
	@gcc -Wall -g -ansi -pedantic -c src/grid.c


test_all:	sudoku
	
	
	./sudoku.exe <puzzles/s.1
	./sudoku.exe <puzzles/s.2
	./sudoku.exe <puzzles/s.3
	./sudoku.exe <puzzles/s.4
	./sudoku.exe <puzzles/s.5
	./sudoku.exe <puzzles/s.6
	./sudoku.exe <puzzles/s.7
	./sudoku.exe <puzzles/s.8
	./sudoku.exe <puzzles/s.9
	./sudoku.exe <puzzles/s.10
	./sudoku.exe <puzzles/s.11
	./sudoku.exe <puzzles/s.12
	./sudoku.exe <puzzles/s.13
	./sudoku.exe <puzzles/s.14
	./sudoku.exe <puzzles/s.15
	./sudoku.exe <puzzles/s.16
	./sudoku.exe <puzzles/s.17
	./sudoku.exe <puzzles/s.18

	
	@rm sudoku.exe
test : sudoku
	./sudoku.exe <puzzles/s.11
	@rm sudoku.exe
## Do not touch here
turnin: undoTurnin
	-git tag assignment4
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment4"; then \
		git tag -d assignment4 && git push origin :refs/tags/assignment4; \
		fi
