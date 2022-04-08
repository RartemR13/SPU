#Factorial N.

#Read N.
get N 

:prepare_stack
	copy N
	in 1
	sub

	copy
	in 0

	cmp
	je cal_factorial
	jmp prepare_stack

:cal_factorial
	del

	:loop
		size
		in 1

		cmp
		je end_program

		mul
		jmp loop

:end_program
	out
	hlt
