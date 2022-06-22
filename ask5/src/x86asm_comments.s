# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	# data storage
N:	.long 1000	    # N = 1000
S:	.long 0		    # S = 0
Msg:	.ascii "The sum from 0 to %d is %d\n\0"	# stores a message in a string


	.section .text	# instructions
.globl main
main:	
	pushl %ebp	    # stores %ebp in the stack
	movl %esp, %ebp	# esp = ebp

 	# initialize
    movl N, %ebx	# ebx = N 

 	# compute sum
L1:
	addl %ebx, S	# S = ebx + S 
	decl %ebx       # ebx--
	cmpl $0, %ebx   # if(ebx==0)
	jng  L2	    	# jump L2
    movl $L1, %eax	# L1 = eax
    jmp *%eax   	# jump L1 = eax

L2:
	# print result
	pushl S	    	# push S to the stack
	pushl N	        # push N to the stack 
	pushl $Msg  	# push Msg to the stack
	call printf 	# call printf to print Msg , N , S
	popl %eax   	# removes the Msg from the stack
	popl %eax   	# removes the N from the stack
	popl %eax   	# removes the S frkm the stack

	# exit
	movl $0, %eax  	# eax = 0
    leave	    	# exit
 	ret             # return
