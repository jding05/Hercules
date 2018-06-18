.name "sding"
.comment "Jeff alive"

l2:		fork %1
		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
