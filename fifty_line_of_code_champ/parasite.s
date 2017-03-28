.name "parasite"
.comment "humm ton code a l'aire d'avoir un gout delicieux ...."

begin:
	sti		r1, %:live1, %1
	st		r1, r2
	st		r1, r3
	st		r1, r4
	st		r1, r5
	st		r1, r6
	st		r1, r7
	st		r1, r8
	st		r1, r9
	st		r1, r10
	st		r1, r11
	st		r1, r12
	st		r1, r13
	st		r1, r14
	ld		55576833, r1
	st		r1, :begin
	fork	%:begin_coromp
	ldi		:live1, %1, r1
	sti		r2, %:live2, %1
	sti		r2, %:live3, %1
	sti		r2, %:live4, %1
	sti		r2, %:live5, %1
	st		r1, -20
	st		r1, -19
	st		r1, -18
	st		r1, -17

live1:
	live	%1
	fork	%:live1	
	st      r2, -350
	st      r2, -359
	st      r2, -368
	st      r2, -377
	st      r2, -386
	st      r2, -395
	st      r2, -204
	st      r2, -213
	st      r2, -222
	st      r2, -231
	st      r2, -240
	st      r2, -249
	st      r2, -258
	st      r2, -267
	st      r2, -276
	st      r2, -285
	st      r2, -294
	st      r2, -303

live4:
	live	%1;
	fork	%:live1
	st      r2, -410
	st      r2, -420
	st      r2, -468
	st      r2, -477
	st      r2, -486
	st      r2, -495
	st      r2, -404
	st      r2, -413
	st      r2, -422
	st      r2, -431
	st      r2, -440
	st      r2, -449
	st      r2, -458
	st      r2, -467
	st      r2, -476
	st      r2, -485
	st      r2, -494

live3:
	live	%1;
	fork	%:live1
	st      r2, -210
	st      r2, -220
	st      r2, -268
	st      r2, -277
	st      r2, -286
	st      r2, -295
	st      r2, -204
	st      r2, -213
	st      r2, -222
	st      r2, -231
	st      r2, -240
	st      r2, -249
	st      r2, -258
	st      r2, -267
	st      r2, -276
	st      r2, -285
	st      r2, -294
	st      r2, -303


live2:
	live	%1
	fork	%:live1
	st      r2, 150
	st      r2, 159
	st      r2, 168
	st      r2, 177
	st      r2, 186
	st      r2, 195
	st      r2, 204
	st      r2, 213
	st      r2, 222
	st      r2, 231
	st      r2, 240
	st      r2, 249
	st      r2, 258
	st      r2, 267
	st      r2, 276

live4:
	live	%1
	fork	%:live1

live5:
	live	%1	
	and		%0, %0, r5
	zjmp	%:live5

begin_coromp:
	ld		%57675809,r15 
	st		r15,496
	ld		%57675809,r15 
	st		r15,489
	ld		%57675809,r15 
	st		r15,482
	ld		%4194959340,r16
	ld		%57675809,r15 
	st		r15,467
	st		r16,466
	and		r14,%0,r14
	zjmp	%445
