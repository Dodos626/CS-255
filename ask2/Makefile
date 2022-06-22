string : main.c mystring_ptrs.c mystring.h
	@gcc mystring_ptrs.c -c -ansi -pedantic -Wall -o f1
	@gcc main.c -c -ansi -pedantic -Wall  -o f2
	@gcc f1 f2
	@rm f1
	@rm f2
	@./a.out

array: main.c mystring_ars.c mystring.h
	@gcc mystring_ars.c -c -ansi -pedantic -Wall -o f1
	@gcc main.c -c -ansi -pedantic -Wall  -o f2
	@gcc f1 f2
	@rm f1
	@rm f2
	@./a.out