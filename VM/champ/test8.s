.name "coucou"
.comment "ca va"


#1 recup une chaine a changer dans r2
#2 poser la chaine a changer a l'endroit du test
#3 test carry (plusieur choses ?)
#4 test jump pour comparer

l:	live	%1
	ld		%12111,r1
	st		r1,8
	ld		45,r2
	live	%0
	zjmp	%:l
