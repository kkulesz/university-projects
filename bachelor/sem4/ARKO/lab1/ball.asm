
	.data
input:		.asciiz "input.bmp"
output:		.asciiz "output.bmp"

#https://galera.ii.pw.edu.pl/~zsz/arko/materialy/bmp/bmp_file_format.html

start_prompt:	.asciiz "Hi!\n"
first_prompt:	.asciiz "Enter x velocity value:\n"
second_prompt:	.asciiz "Enter y velocity value:\n"
third_prompt:	.asciiz "Enter velocity kept percantage value:\n"
fail_prompt:	.asciiz "Error\n"



RED:		.byte 0x55
GREEN:		.byte 0x55
BLUE:		.byte 0x55


#all integers are <16,16>
GRAV_ACC:	.word 0x000a0000 # 10m/s^2
#time step is 1/16s, so every time it is just >4


	.text
	.globl main
	
main:
	lw $t8, GRAV_ACC

	jal start
	#j skipCalc
	
	# s0 Vx
	# s1 Vy
	# s2 Energy kept
	# s3 X
	# s4 Y
	# s5 dVy = G * dt G>4
	# s6 dX = Vx * dt Vx>4
	
	# t0 zmienna i
	
	# t7 dt
	# t8 G
	# t9 heap address to ball cords
	
	
	li $v0, 9
	li $a0, 16382 #2048 points * 8 bytes
	syscall
	addu $t9, $v0, $zero
	
	
	#Start coordinate
	li $s3, 0 # X
	sll $s3, $s3, 16
	li $s4, 0 # Y
	sll $s4, $s4, 16

	#consts
	srl $s5, $t8, 4 # dVy = G*dt
	srl $s6, $s0, 4 # dX = Vx*dt
		
	li $t0, 0 # i=0
calc_loop:	
	#store cords
	sw $s3, ($t9)
	addiu $t9, $t9, 4
	sw $s4, ($t9)
	addiu $t9, $t9, 4
	
	
	add $s3, $s3, $s6 	# X = X + dX
	
	sub $s1, $s1, $s5 	# Vy = Vy - dVy
	sra $t6, $s1, 4 	# dY = Vy*dt  dV>4
	addu $s4, $s4, $t6 	# Y = Y + dY
	
	bgez $s4, noBounce

	addu $s4, $zero, $zero  #Y = 0
	
	subu $s1, $zero , $s1 	# Vy = -Vy
	multu $s1, $s2
	mflo $s1
	divu $s1, $s1, 100	# Vy = Vy*Ek

noBounce:
	
	addu $t0, $t0, 1 	# ++i
	blt $t0, 2048, calc_loop 	# while i<2048
	
	
	#j exit
	
skipCalc:
# open input file
	li $v0, 13
	la $a0, input
	li $a1, 0 #read
	li $a2, 0
	syscall
	addu $s0, $v0, $zero
	bltz $s0, failure #descriptor
	

# allocate heap for header
	li $v0, 9
	li $a0, 54
	syscall
	addu $s7, $v0, $zero #s7 address of data on heap
	
	
# load header
	li $v0, 14
	addu $a0, $s0, $zero #descriptor
	addu $a1, $s7, $zero #address
	li $a2, 54
	syscall
	bltz $v0, failure
	
# Size of pixel array
	addiu $a0, $s7, 5
	jal littleToBigEndian
	subiu $s2, $v0, 54
	
# Allocate heap for pixel array
	li	$v0, 9
	addu	$a0, $s2, $zero
	syscall
	addu	$s3, $v0, $zero
	
# Load pixel array
	li	$v0, 14
	addu	$a0, $s0, $zero
	addu	$a1, $s3, $zero #address
	addu	$a2, $s2, $zero
	syscall
	bltz $v0, failure
# close input file
	li	$v0, 16
	addu	$a0, $s0, $zero
	syscall
	#s0 is free now




# width in pixels
	addiu	$a0, $s7, 21#21
	jal	littleToBigEndian
	addu	$s4, $v0, $zero
# height in pixels
	addiu	$a0, $s7, 25#25
	jal	littleToBigEndian
	addu	$s5, $v0, $zero
	
	
	
	
######padding
	mul $t7, $s4, 3 	# szer * 3
	andi $t7, $t7, 3 	# sizeof(szer) mod 4
	beqz $t7, noPadding
	sub $t7, $zero, $t7 	
	addi $t7, $t7, 4 	# t7 = 4 - t7




# 54 - size of header 
# s7 - address of header
#
# s2 - size of pixel array 
# s3 - address of pixel array
#
# s4 - width in pixels
# s5 - height in pixels
noPadding:
	subiu $t9, $t9, 16384 # beggining of ball cords

	addu $t3, $s3, $zero
	addiu $t3, $t3, 68 #first pixel which displays, don't know why


	mul $s6, $s4, 3 #width * 3
	addu $s6, $s6, $t7 # padding
	#s6 - width + padding bytes


	li $t0, 0 # i=0
draw_loop:
	lw $t1, ($t9) # X
	lw $t2, 4($t9)# Y
	addiu $t9, $t9, 8
	
	srl $t1, $t1, 16
	srl $t2, $t2, 16	

	bge $t1, $s4, notInBitmap
	bltz $t1, notInBitmap
	
	bge $t2, $s5, notInBitmap
	bltz $t2, notInBitmap

	mul $t4, $t1, 3
	addu $t4, $t4, $t3 #width

	mul $t5, $s6, $t2 # height

	addu $t4, $t4, $t5 # 

	lb $t8, BLUE
	sb $t8, 0($t4)
	lb $t8, GREEN
	sb $t8, 1($t4)
	lb $t8, RED
	sb $t8, 2($t4)

notInBitmap:
	addiu $t0, $t0, 1 #++i
	blt $t0, 2048, draw_loop #while( i < 2048)




# open output file
	li $v0, 13
	la $a0, output
	li $a1, 1 #write
	li $a2, 0
	syscall
	addu $s1, $v0, $zero
	bltz $s1, failure #descriptor
	
# write header
	li $v0, 15
	addu $a0, $s1, $zero #descriptor
	addu $a1, $s7, $zero #address
	li $a2, 54
	syscall
	bltz $v0, failure


# write pixel array
	li	$v0, 15
	addu	$a0, $s1, $zero #descriptor
	addu	$a1, $s3, $zero #address
	addu	$a2, $s2, $zero	#size
	syscall

# close output file
	li	$v0, 16
	addu	$a0, $s1, $zero
	syscall


################
#PROCEDURES
################
exit:
	li $v0, 10
	syscall
	


failure:
	la $a0, fail_prompt
	li $v0, 4
	syscall
	j exit

	
	
	
start:
	la $a0, start_prompt
	li $v0, 4
	syscall
	
	#get x velocity
	la $a0, first_prompt
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sll $s0, $v0, 16
	
	#get y velocity
	la $a0, second_prompt
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sll $s1, $v0, 16
	
	#get velocity loss
	la $a0, third_prompt
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	addu $s2, $v0, $zero
	#sll $s2, $v0, 16
	
	jr $ra
	

littleToBigEndian:
	li $v0, 0
	li $a1, 4 # i=4
convertByte:
	sll $v0, $v0, 8 #shift to left
	lbu $a2, ($a0)
	addu $v0, $v0, $a2
	subi $a0, $a0, 1 #point next
	subi $a1, $a1, 1 #--i
	bnez $a1, convertByte
	jr $ra
