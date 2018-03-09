.name "la vrai tsundere"
.comment "I will catch you Oni-san"

init:
	sti	r1, %:init, %72
	sti	r1, %:init, %78
	sti	r1, %:init, %86
	sti	r1, %:init, %94
	sti	r1, %:wall_live, %1
	sti	r1, %:wall, %1
	sti	r1, %:bomb, %1
	sti	r1, %:torp_fork, %1
	sti	r1, %:torp_init, %1
	sti	r1, %:torp, %35
	ld	%1, r1
	live	%15
	fork	%:torp_init
	live	%15
	fork	%:bomb
	live	%15
	lfork	%2148

wall_live:
	live	%15

wall_prep:
	ld	%655334, r2
	ld	%16777216, r3
	ld	%16, r4
	ld	%50499584, r5
	ld	%16845056, r6
	ld	%2415919104, r7
	ld	%201327362, r8

wall:
	live	%15
	st	r2, -150
	st	r3, -159
	st	r4, -168
	st	r5, -177
	st	r6, -186
	st	r7, -195
	st	r8, -204
	st	r1, -188
	st	r1, -209
	st	r2, -223
	st	r3, -232
	st	r4, -241
	st	r5, -250
	st	r6, -259
	st	r7, -268
	st	r8, -277
	st	r1, -261
	st	r1, -282
	st	r2, -296
	st	r3, -305
	st	r4, -314
	st	r5, -323
	st	r6, -332
	st	r7, -341
	st	r8, -350
	st	r1, -334
	st	r1, -355
	st	r2, -369
	st	r3, -378
	st	r4, -387
	st	r5, -396
	st	r6, -405
	st	r7, -414
	st	r8, -423
	st	r1, -407
	st	r1, -428
	st	r8, -326
	st	r7, -327
	st	r6, -328
	st	r5, -329
	st	r4, -330
	st	r3, -331
	st	r2, -332
	st	r1, -356
	st	r1, -345
	st	r8, -343
	st	r7, -344
	st	r6, -345
	st	r5, -346
	st	r4, -347
	st	r3, -348
	st	r2, -349
	st	r1, -373
	st	r1, -362

wall_jump:
	ld	%0, r16
	zjmp	%:wall

bomb:
	live	%15;
	fork	%:wall_prep
	live	%15;
	ld	%0, r16
	zjmp	%:bomb

torp_fork:
	live	%15
	fork	%500

torp_init:
	live	%15
	ld	%0, r2
	ld	%4, r3
	ld	%96, r5

torp:
	ldi	%:torp_fork, r2, r4
	sti	r4, %400, r2
	add	r2, r3, r2
	ldi	%:torp_fork, r2, r4
	sti	r4, %383, r2
	add	r2, r3, r2
	live	%15
	xor	r5, r2, r15
	zjmp	%360

jump:
	ld	%0, r15
	zjmp	%:torp
