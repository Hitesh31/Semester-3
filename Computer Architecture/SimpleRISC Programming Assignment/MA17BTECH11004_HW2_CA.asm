.main:
    	movu r0, 59999  @value at r0=59999 
    	mov r1, 0	@decisive value for factorian number
    	mov r2, 0	@decisive value for dudeney number
    	mov r3, 0	@this will store a factorian of a number
    	mov r8, r0	@value at r8= value at r0
    	mov r9, r0	@value at r9= value at r0
    	mov r11, 0	@this will store dudeney of a number
.loop1:
        	mod r4, r8,10	@take last digit of number
        	b .factorial	@compute factorial
    		.break:
			add r3, r3,r6	@add individual factorial of digits
			div r8, r8,10	@divide r8 by 10 to move to next significant bit
    		cmp r8, 0		@if number become zero go to compare
    		beq .breakk
    		b .loop1
.factorial:				@computer factorial
			mov r5, r4
			mov r6, 1
			mov r7, 1
			.loop:
				cmp r7, r5
				bgt .break
				mul r6, r6, r7
				add r7, r7, 1
				b .loop  
.increase:				@if it is factorial put r1 to 1
	mov r1, 1
    .print r1
    b .dudeney
.breakk:
	cmp r0, r3
	beq .increase 
    .print r1
.dudeney:				@for dudeney
	.loop2:				@computing sum of each digit
		mod r10, r9,10
		add r11, r11,r10
		div r9, r9,10
		cmp r9,0
		beq .cube
		b .loop2
.increase2:				@increase r2 if dudeney
	mov r2, 1
	.print r2
	b .end
.cube:					@computing cube
	mov r12, r11
	mul r11, r11,r12
	mul r11, r11,r12
	cmp r0,r11			@compare r0 and dudeney of it
	beq .increase2
	.print r2
.end:
	@MA17BTECH11004 - Hitesh Kumar
