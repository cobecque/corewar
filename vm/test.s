.name "test"
.comment "comment"

l:	sti r1,%:live,r1
	ld %:live,r1
	zjmp %:live

live:	ld %:l,r1
		live %1
		zjmp %:live
