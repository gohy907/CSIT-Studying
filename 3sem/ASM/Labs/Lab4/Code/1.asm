.model small
.stack 100h
.186

.data
hello db 'Arkhipov Ivan, 251$'
string db 5 dup (' '), '$'
simple dw 20 dup (0)

.code

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

    mov DX, offset hello
    call print_str
    call print_nl

	mov CX, 2
    xor SI, SI
    xor AX, AX
	store_1:
        mov AL, 2 

        store_2:
            cmp CX, 1 
            je store_squares

            mov simple[SI], AX
            jmp end_store 

            store_squares: 
            push AX
            mul AL
            mov word ptr simple[SI], AX
            pop AX

            end_store:
            add SI, 2 
            add AL, 2 ; Так как заполняем в памяти два байта, смещаем указатель на два
            cmp SI, 20; Т.е. проверяем, что записано 10 чисел (20 байтов)
            je store_2_end

            cmp SI, 40; Т.е. проверяем, что записано 20 чисел (40 байтов)
            je store_2_end

            jmp store_2

        store_2_end:

		loop store_1

    mov CX, 20 
    xor SI, SI
	print_loop:
        cmp CX, 10 
        jne not_print_nl
        call print_nl 

        not_print_nl:
        push CX
        push SI
        xor AX, AX
            mov AX, simple[SI]
            mov CX, 5
            mov SI, offset string
            call format_str

            pop SI
            pop CX
            
            mov DX, offset string
            call print_str
            add SI, 2
        loop print_loop
	mov AX, 4C00h
	int 21h
end start
