.name "test"
.comment "test asm"

ld	%0, r1
sti	r1, %142, r1
st r1, 4
sti	r1, %928, r1
live %4294967295
live %0
