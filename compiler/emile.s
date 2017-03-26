.name "E1000"
.comment "destruction"

l2:		sti r1, %:live, %1 # Deplace le numero de joueur sur r1
		and r1, %0, r1 # fait passer le carry à 1




wall:
	live	%1
	st		r1, -24 # numéro de joeur
	st		r1, -33
	st		r1, -42
	st		r1, -51
	st		r1, -60
	st		r1, -69
	st		r1, -78
	st		r1, -87
	st		r1, -96
	st		r1, -105
	st		r1, -114
	st		r1, -123
	st		r1, -132
	st		r1, -141
	st		r1, -150
	st		r1, -159
	st		r1, -168
	st		r1, -177
	st		r1, -186
	st		r1, -195
	st		r1, -204
	st		r1, -213
	st		r1, -222
	st		r1, -231
	st		r1, -240
	st		r1, -249
	st		r1, -258
	st		r1, -267
	st		r1, -276
	st		r1, -285
	st		r1, -294
	st		r1, -303
	st		r1, -312
	st		r1, -321
	st		r1, -330
	st		r1, -339
	st		r1, -348
	st		r1, -357
	st		r1, -366
	st		r1, -375
	st		r1, -384
	st		r1, -393
	st		r1, -402
	st		r1, -411
	st		r1, -420
	st		r1, -429
	st		r1, -438
	st		r1, -447
	st		r1, -456
	st		r1, -465
	st		r1, -474
	st		r1, -483
	st		r1, -492
	st		r1, -501
	st		r1, -510
	zjmp	%:wall

live:	live %1 # dit live avec %1
		zjmp %:live # saute à la ligne d'avant



.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1


		ld %1, r2		# met un dans r2 (nombres de boucles)
		ld %1, r15		# met un dans r15 (valeur fixe)
while:  sti r3,r2, %end #r3 = valeur de sti, r2 = nombres de boucles
		add r15, r2, r3
		sti r3,r2, %end #r3 = valeur de sti, r2 = nombres de boucles
		add r15, r2, r3
		and r1, %0, r1
		zjmp %:while

#While (r2 < 10)
forks:
add	r2, r3, r2		#increment r2
xor	r2, %15, r4		#if (r4) {carry = 0}
live2:
	live 	%4
zjmp	%:endwhile		#if (carry)
fork	%:forks
ld	%0, r4			#carry = 1
zjmp	%:forks
#EndWhile

while: 

live:	live %1
		zjmp %:live
end:
