.comment    "Undeniably the best bot in the whole of bocal"
.name       "Repeta"

start_cor:
	st				r1, :slatb
	ld				%151068160,r1
	st				r1, :start_cor
	ld				%506,r2
	ld				%100,r3
	live			%0
	fork            %:cor_second_set
cor_first_set:
	ld				%34144757,r4
	st				r4,r5
	ld				%50921567,r6
	st				r6,r7
	st				r6,r12
	st				r6,r13
	st				r6,r14
	st				r6,r15
	st				r4,r8
	st				r4,r9
	st				r4,r10
	ld				%167685120,r11
	ld				%4,r1
	sub             r16, r16, r16
	zjmp            %:finish2
cor_second_set:
	ld		%190055681,r4
	ld		%190055937,r5
	ld		%190057473,r6
	ld		%190057729,r12
	ld		%190057985,r13
	ld		%190058241,r14
	ld		%190056193,r15
	ld		%190056449,r7
	ld		%190056705,r8
	ld		%190056961,r9
	ld		%151087617,r10
	ld		%151035392,r11
	ld		%0, r1

	zjmp	%:finish2
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	fork	%:vol1
slatb:
	fork	%:vol2
	live	%77
	live	%77
	live	%77
reconnect:
	zjmp	%:alter
	fork	%:vol1
	fork	%:vol2
	fork	%:cor_first_set
	fork	%:cor_second_set
	live	%77
	live	%77
	live	%77
alter:
	ld		:slatb,r5
	st		r5,6
lslds:
	live	%1
	st		r16, :start_cor
	ld		%0,r6
	ld		%0,r7
	ld		%0,r8
	ld		%0,r11
	ld		%0,r12
	ld		%0,r13
	ld		%0,r14
	ld		%0,r15
	and		r1,r1,r16
	zjmp	%:vol2
vol1:
	fork	%:vol3
	ld		%190055684, r5
	ld		%190055684, r9
	ld		%190056708, r10
	ld		%10, r4
	sub		r16, r16, r16
	zjmp	%:finish
vol2:
	fork	%:vol4
	ld		%84149761, r5
	ld		%151259145, r10
	st		r5, r9
	ld		%12, r4
	sub		r16, r16, r16
	zjmp	%:finish
vol3:
	ld		%0000, r7
	st		r5, r9
	ld		%32768000, r10
	ld		%16, r4
	sub		r16, r16, r16
	zjmp	%:finish
vol4:
	live	%1
	ld		%151587073, r5
	st		r5, r9
	st		r9, r10
	ld		%511, r4
	sub		r16, r16, r16
	zjmp	%:finish
finish:
	ld		%495, r8
	add		r16, r16, r16
	sti		r10, r8, r4
	zjmp	%500
	fork	%:vol1
	fork	%:vol2
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
	live	%77
finish2:
	sti		r4,r1,%505
	zjmp	%499
