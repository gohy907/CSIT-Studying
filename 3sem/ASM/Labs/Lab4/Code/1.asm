.model small
.stack 100h
.186

.data
hello db 'aboba$'
aboba db 'abobization$'
string db 5 dup (' '), '$'
simple db 10 dup (0)

.code

; Процедура вывода цифры на экран
; Цифра должна находиться в регистре DL
print PROC
    push AX
    push DX

    add DL, '0'
    mov AH, 02h
    int 21h

    pop DX
    pop AX
    ret
print ENDP

; Процедура вывода строки на экран
; Адрес строки должен находиться в регистре DX
print_str PROC
    push AX

    mov AH,09h
    int 21h 

    pop AX
    ret
print_str ENDP

; Процедура заполнения строки пробелами
; Ссылка на строку должна находиться в регистре SI, а её длина в регистре CX
; CX > 0
clear_str PROC
    push CX

    clear_loop:
        mov byte ptr [SI], ' '
        inc SI
        loop clear_loop

    pop CX
    ret              
clear_str ENDP

; Процедура создания строки фиксированной ширины с числом в конце
; Ссылка на строку должна находиться в регистре SI, её длина в регистре CX,
; а само число в AX
format_str PROC
    push BX 
    push DX

    mov BX, 10     
    mov DX, SI
    call clear_str

    dec SI
    format_loop:
        xor DX, DX
        div BX; Остаток от деления помещается в DL
        add DL, '0'   
        mov byte ptr [SI], DL; В байт строки заносится DL
        dec SI; Индекс смещается вправо, цифры записываются с конца
        cmp AX, 0
        jne format_loop

    pop DX 
    pop BX
    ret 
format_str ENDP

; Процедура вывода новой строки
print_nl PROC
    push AX
    mov AH, 2h 
    mov DL, 0Ah 
    int 21h
    pop AX
    ret
print_nl ENDP

start:
	mov AX, @data
	mov DS, AX

	xor CX, CX
	mov AL, 2
	store:
		mov BX, CX
		mov simple[BX], AL
        add AL, 2
	    inc CX 
	    cmp CX, 10
		jne store

    mov CX, 2 
	rows:
        xor SI, SI
        push CX
	    cols:
            cmp CX, 1 
            push CX
	        je squares

              
            xor AX, AX
            mov AL, simple[SI]
            push CX
            push SI

            mov CX, 5
            mov SI, offset string
            call format_str

            pop SI
            pop CX
            jmp end_cols

            squares:
            xor AX, AX
            mov AL, simple[SI]
            mul AL

            push CX
            push SI

            mov CX, 5
            mov SI, offset string
            call format_str

            pop SI
            pop CX

            end_cols:
            pop CX
            
            mov DX, offset string
            call print_str
            inc SI
            cmp SI, 10
            jne cols
        call print_nl
        pop CX
        loop rows
	mov AX, 4C00h
	int 21h
end start
