.model small
.stack 100h
.186
.code
start:
mov ax,@data
mov ds,ax
 
mov ax,0b900h;Используя сегментный регистр ES,              
mov es,ax    ;организуем запись данных в видеопамять        
             ;по адресу В900h:0000h (страница 1)            
MOV AH,0Fh
INT 10h 

mov AH, 00h; Устанавливаем видеорежим 
int 10h

mov AH, 05h; Устанавливаем первую страницу активной
mov AL, 01h
int 10h

call B10DISPLAY

mov AH, 00h 
int 16h; Ожидание нажатия клавиши

mov ax,4C00h; Завершение программы
int 21h

; Заносит символы с их атрибутами в видеопамять
B10DISPLAY proc
pusha

mov AL, 65; ASCII-код символа A
mov AH, 9h; Атрибут светло-синего цвета
mov DI, 820; Начальная позиция 5:10, DI = ((5 * 80) + 10) * 2 = 820

xor CH, CH
rows:
    inc CH
    xor CL, CL
    letters:
        mov ES:word ptr[DI], AX
        add DI, 2
        inc CL
        cmp CL, CH
        jne letters

    inc AL 
    inc AH
    add DI, 160; Прибавляем к индексу 160 байт (80 символов)

    xor BX, BX; Нужно учесть символы, которые мы уже напечатали
    mov BL, CH; и вычесть их количество из смещения индекса
    add BL, BL
    sub DI, BX
              

    cmp CH, 6
    jne rows

popa
ret
B10DISPLAY endp

end start              
