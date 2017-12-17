.name "test"
.comment "comment"

l:	sti r1,%0,r1
	ld %1,r1

live:	live %1
		zjmp %:live
