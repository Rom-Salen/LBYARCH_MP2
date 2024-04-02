;assembly part using x86-64

section .txt
bits 64
default rel ; to handle address relocation

global dotProductInit

dotProductInit:
	xor r10, r10

dotProduct:
	cmp r10, r8
	jge FINIS
	movsd xmm1, qword [rcx + r10 * 8]
	movsd xmm2, qword [rdx + r10 * 8]

	mulsd xmm2, xmm1
	addsd xmm0, xmm2
	inc r10
	jmp dotProduct

FINIS:
	ret
