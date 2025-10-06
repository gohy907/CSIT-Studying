stak segment stack 'stack'     
db 256 dup (?)                
stak ends                    

data segment 'data'  
Hello db 'Arkhipov Ivan, 251 group$'
data ends             

code segment 'code' 
assume CS:code,DS:data,SS:stak

print PROC FAR; Процедура вывода значения в DL на экран
push AX
mov AH, 02h
int 21h 
pop AX
ret
print ENDP

print_nl PROC FAR; Процедура вывода новой строки
push AX
mov AH, 2h 
mov DL, 0Ah 
int 21h
pop AX
ret
print_nl ENDP

print_str PROC FAR; Процедура вывода строки на экран
push AX
mov AX,data
mov DS,AX 
mov AH,09h
mov DX,offset Hello 
int 21h 
pop AX
ret
print_str ENDP

printA_B PROC FAR; Процедура вывода значений регистров AX и BX на экран
mov DL, AL

add DL, '0'
call print

mov DL, 0h
call print

mov DL, BL
add DL, '0'
call print

ret
printA_B ENDP

start:  
call print_str
call print_nl

mov AX, 9h
mov BX, 1h
call printA_B

push AX

mov AH, 2h 
mov DL, 0Ah
int 21h

pop AX

xchg AX, BX
call printA_B

mov AX,4C00h               
int 21h                   
code ends                

end start               
