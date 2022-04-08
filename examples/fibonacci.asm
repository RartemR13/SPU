get
call fibonacci
out
hlt

:fibonacci
	swp

	copy
	in 1
	cmp
	jle return

	copy
	in 1
	sub
	call fibonacci

	swp
	in 2
	sub
	call fibonacci
	add

	:return
		swp
		ret