.name "testeur"
.comment "il test il test le testeur, le testuer du bois joli"

l2:		sti r1,%:first,%100
		and r1,%0,r1

first:
	live	%120
	zjmp	%:first
