.model small
.stack 100h
.186

.data
; name db 'Arkhipov Ivan, 251 group$'
simple db 10 dup (0)
result db 5 dup (''), '$'

.code

print PROC; Процедура вывода значения в DL на экран
    push AX
    push DX
    add DL, '0'
    mov AH, 02h
    int 21h
    pop DX
    pop AX
    ret
print ENDP

print_str PROC; Процедура вывода строки на экран
    push AX
    mov AH,09h
    mov DX,offset result 
    int 21h 
    pop AX
    ret
print_str ENDP

start:
	mov AX, @data
	mov DS, AX

	mov CX, 0
	mov AL, 0
	store:
		add AL, 2
		mov BX, CX
		mov simple[BX], AL

        inc CX
        cmp CX, 10
		jne store

	;
	;
	; mov CX, 0
	;
	;
	; rows:
	; 	mov BX, CX
	; 	mov AX, simple[BX]
	; 	call print
	; 	cols:
	;
	; 	inc CX
	; 	cmp CX, 2
	; 	jne rows 
	mov AX, 4C00h
	int 21h
end start
