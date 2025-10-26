.model small
.stack 100h

.data
Hello db 'Arkhipov Ivan, 251 group$'

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

print_nl PROC; Процедура вывода новой строки
    push AX
    mov AH, 2h 
    mov DL, 0Ah 
    int 21h
    pop AX
    ret
print_nl ENDP

print_str PROC; Процедура вывода строки на экран
    push AX
    mov AH,09h
    mov DX,offset Hello 
    int 21h 
    pop AX
    ret
print_str ENDP

start:
    mov AX, @data
    mov DS, AX

    call print_str
    call print_nl

    mov AX, 65535
    mov BX, 10
    xor CX, CX

    divloop:
        xor DX, DX
        div word ptr BX; Делим DX:AX на BX
        push DX; Остаток от деления заносим в стек
        inc CX; Прибавляем 1 к количеству разрядов
        cmp AX, 0; Сравниваем частное с нулём
        jne divloop; Если частное не равно нулю, продолжаем делить

    stackloop:
        pop DX; Достаём остатки из стека и печатаем их
        call print
        loop stackloop

    mov AX, 4C00h
    int 21h

end start
