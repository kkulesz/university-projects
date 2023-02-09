;%macro print 2
;	mov eax, 4 ;syscall for write
;	mov ebx, 1 ; file descriptor (stoout)
;	mov ecx, %1
;	mov edx, %2
;	int 80h
;%endmacro
;extern printf


section .data

grav 	dq 9.81
step	dq 0.0625	;1/16s

colR	db 0x00
colG	db 0x00
colB	db 0x00
colAl	db 0x00

section .text
	;weight of ball is 1kg in order to make it simple
global fun
fun:
	push rbp	;odkladamy wskaznik ramki maina
	mov rbp, rsp	;zapisujemy swoj
	
	;rdi	-pixelArray
	;rsi	-width	
	;rdx	-height	
	;rcx	-K		
	;r8 	-V
	;r9 	-alpha
	
	sub rsp, 8 ; tmp

; DEGREES TO RADIANS
	mov [rbp-8], r9
	fild QWORD [rbp-8]	;alpha
	fldpi			;PI
	fmul			;PI*alpha
	mov QWORD [rbp-8], 180
	fild QWORD [rbp-8]
	fdiv			;(PI*alpha)/180
	fstp QWORD [rbp-8]
	movsd xmm15, [rbp-8]

;================ CALC Vx and Vy

	movsd [rbp-8], xmm15
	fld QWORD [rbp-8]	;alpha
	fsin			;sin(alpha)
	mov [rbp-8], r8		;V
	fild QWORD [rbp-8]
	fmul			;sin(alpha) * V
	fstp QWORD [rbp-8]	;Vy = V*sin(alpha)
	movsd xmm14, [rbp-8]


	movsd [rbp-8], xmm15 
	fld QWORD [rbp-8]	;alpha
	fcos			;sin(alpha)
	mov[rbp-8], r8		;V
	fild QWORD [rbp-8]
	fmul			;sin(alpha) * V
	fstp QWORD [rbp-8]	;Vx = V*cos(alpha)
	movsd xmm8, [rbp-8]	
	movsd xmm9, xmm14


	mov r8, rsi
	mov r9, rdx		;(V) and (alpha) no longer needed
				;so I store width and height there
	mov rax, 4
	mul r8
	;mov r13, rax		; bytesPerRow = width*4	

;================CALC BEGIN
	mov QWORD [rbp-8], 0
	movsd xmm11, [rbp-8] ;y=0


	mov [rbp-8], r8
	fild QWORD [rbp-8]
	mov QWORD [rbp-8], 2
	fild QWORD [rbp-8]
	fdiv
	fstp QWORD [rbp-8]
	movsd xmm10, [rbp-8] ;x=width/2

;(x,y) = (width/2, 0)

	movsd xmm13, [step]	;time_step

	cvtsi2sd xmm12, rcx	;parameter K
	movsd [rbp-8], xmm12
	fld QWORD [rbp-8]
	mov QWORD [rbp-8], 1000	;========	
	fild QWORD [rbp-8]
	fdiv			; K = K/100
	fstp QWORD [rbp-8]
	movsd xmm12, [rbp-8]	;K is in range <0,1>

	movsd xmm15, [grav]
	movsd [rbp-8], xmm15
	fld QWORD [rbp-8]	;g
	movsd [rbp-8], xmm13
	fld QWORD [rbp-8]	;dt
	fmul
	fstp QWORD [rbp-8]	; dt*g
	movsd xmm14, [rbp-8]


	mov QWORD [rbp-8], 0	;xmm2 = 0.00
	movsd xmm2, [rbp-8]

	mov QWORD [rbp-8], 0
	fild QWORD [rbp-8]
	mov QWORD [rbp-8], 1
	fild QWORD [rbp-8]
	fsub
	fstp QWORD [rbp-8]
	movsd xmm3, [rbp-8]	;xmm3 = -1


	;xmm8	Vx
	;xmm9	Vy
	;xmm10	x
	;xmm11	y
	;xmm12	K
	;xmm13	dt
	;xmm14	g*dt
	
	;xmm2 = 0.00
	;xmm3 = -1.00
	;xmm3-7, xmm15 -------------tmp

	;r8	width
	;r9	height
	
	;r10	x
	;r11	y

	;r12	i
	;r13 	bytes per row
	;r14-r15 are free

	mov r12,0 ;i=0
loop:

;jmp skip_calc_Vx
;===========calc Vx
	;movsd xmm15, xmm8	;remember old value in order to check if should be moving after change

	movsd [rbp-8], xmm8
	fld QWORD [rbp-8]	; Vx
	fld st0			; Vx ; Vx	
	fld st0			; Vx ; Vx ; Vx
	fmul			; Vx^2 ; Vx
	movsd [rbp-8], xmm12	
	fld QWORD [rbp-8]	; K ; Vx^2 ; Vx
	fmul			; K*Vx^2 ; Vx
	movsd [rbp-8], xmm13	
	fld QWORD [rbp-8]	; dt ; K*Vx^2 ; Vx
	fmul			; K*Vx^2*dt ; Vx

	cvtsd2si r14, xmm8;<-----MOGĄ BYĆ ANOMALIE
	cmp r14, 0
	jl moving_left	; if Vx<0

	movsd [rbp-8], xmm3
	fld QWORD [rbp-8]	; -1 ; K*Vx^2*dt ; Vx
	fmul			; -K*Vx^2*dt ; Vx
moving_left:
	fadd			; Vx +/- K*Vx^2*dt

	fstp QWORD [rbp-8]
	movsd xmm8, [rbp-8]	; new Vx


skip_calc_Vx
;=========calc X
	movsd [rbp-8], xmm10
	fld QWORD [rbp-8]	; X
	movsd [rbp-8], xmm8
	fld QWORD [rbp-8]	; Vx ; X
	movsd [rbp-8], xmm13
	fld QWORD [rbp-8]	; dt ; Vx ; X
	fmul			; dt*Vx ; X
	fadd			; X + Vx*dt
	fstp QWORD [rbp-8]
	movsd xmm10, [rbp-8]


;===========calc Vy
	movsd [rbp-8], xmm9
	fld QWORD [rbp-8]	; Vy
	fld st0			; Vy ; Vy
	fld st0			; Vy ; Vy ; Vy
	fmul			; Vy^2 ; Vy
	movsd [rbp-8], xmm12
	fld QWORD [rbp-8]	; K ; Vy^2 ; Vy
	fmul			; K*Vy^2 ; Vy
	movsd [rbp-8], xmm13
	fld QWORD [rbp-8]	; dt ; K*Vy^2 ; Vy
	fmul			; K*Vy^2*dt ; Vy
	cvtsd2si r14, xmm9
	cmp r14, 0
	jl moving_down

	movsd  [rbp-8], xmm3 
	fld QWORD [rbp-8]	; -1 ; K*Vy^2*dt ; Vy
	fmul			; -1*K*Vy^2*dt ; Vy
moving_down:
	fadd			; Vy +/- K*Vy^2*dt

	movsd [rbp-8], xmm14 	; g*dt ; Vy +/- K*Vy^2*dt
	fld QWORD [rbp-8]
	fsub			; Vy +/- K*Vy^2*dt - g*dt

	fstp QWORD [rbp-8]
	movsd xmm9, [rbp-8]	; new Vy


;===========calc Y
	movsd [rbp-8], xmm11
	fld QWORD [rbp-8]	; Y
	movsd [rbp-8], xmm9
	fld QWORD [rbp-8]	; Vy ; Y
	movsd [rbp-8], xmm13
	fld QWORD [rbp-8]	; dt ; Vy ; Y
	fmul			; Vy*dt ; Y
	fadd			; Y + Vy*dt
	fstp QWORD [rbp-8]
	movsd xmm11, [rbp-8]
	cvtsd2si r14, xmm11
	cmp r14, 0
	jge no_bounce
;bounce	

	mov QWORD [rbp-8], 0
	movsd xmm11, [rbp-8]	; Y=0

	mov QWORD [rbp-8], 0
	fild QWORD [rbp-8]	; 0
	movsd [rbp-8], xmm9
	fld QWORD [rbp-8]	; Vy ; 0
	fsub			; 0-Vy = -Vy
	fstp QWORD [rbp-8]
	movsd xmm9, [rbp-8]
no_bounce:
	cvtsd2si r10, xmm10	;X
	cvtsd2si r11, xmm11	;Y

	cmp r10, r8
	jg skip_drawing_pixel
	cmp r10, 0
	jl skip_drawing_pixel

	cmp r11, r9
	jg skip_drawing_pixel
	cmp r11, 0
	jl skip_drawing_pixel
	
	mov rax, r9
	sub rax, 1
	sub rax, r11	;in order to draw from the bottom
	mul r8		
	add rax, r10
	mov r13, rax	;r13 = (H-y-1)*(W) + x

	mov al, [colR]
	mov [rdi + 4*r13], al
	mov al, [colG]
	mov [rdi + 4*r13+1], al
	mov al, [colB]
	mov [rdi + 4*r13+2], al
	mov al, [colAl]
	mov [rdi + 4*r13+3], al

skip_drawing_pixel:
	add r12, 1
	cmp r12, 4096 ;drawing 4096 pixels 
	jl loop ;while i<4096
	jmp end

end:
	mov rsp, rbp	;dealokujemy pamiec
	pop rbp		;pobieramy wskaznik ramki maina
	ret	
