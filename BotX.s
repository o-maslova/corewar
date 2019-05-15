.name		"BotX"
.comment	"I'm Joulupukki"

live:
		live %1
		fork %-10
		live %1
		fork %-10
		live %1
		fork %-10
		live %1
		fork %-10
		live %1
		fork %-10
		live %1
		fork %-10
		live %1
		fork %-10
		live %1
		fork %-10
		live %1
		fork %-10

x:
		 zjmp %:live
	    ld %25, r4
	    st r4, -500
	    st r4, -500
		st r4, -500
	    st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
	    st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
	    st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
		st r4, -500
	    zjmp %:x
