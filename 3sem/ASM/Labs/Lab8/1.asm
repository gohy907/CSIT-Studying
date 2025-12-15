; Подключение внешних функций WinAPI
extrn ExitProcess:proc
extrn MessageBoxW:proc
extrn GetStdHandle: proc
extrn WriteConsoleA: proc
extrn ReadConsoleA: proc
extrn lstrlenA: proc

.data
STD_OUTPUT_HANDLE = -11
STD_INPUT_HANDLE  = -10
hStdInput qword ?
hStdOutput qword ?
sum dw ?
aInput db 'a = ', 0
a db ' ', 0
bInput db 'b = ', 0 
b db ?
abInput db 'a + b = ', 0 
invalidChar db 'Invalid character', 0 
pressAnyKey db 'Press any key to exit...', 0 

STACKALLOC macro arg
    push R15
    mov R15, RSP
    sub RSP, 8*4
    if arg
        sub RSP, 8*arg
    endif
    and SPL, 0F0h
endm

STACKFREE macro 
    mov RSP, R15
    pop R15
endm

NULL_FIFTH_ARG macro
    mov qword ptr [RSP + 32], 0
endm

.code

; адрес строки должен находиться в RAX
PrintString proc uses RAX RCX RDX R8 R9, string: QWORD  
    local bytesWritten: qword 
    STACKALLOC 1

    mov RCX, string      ; lpString (адрес строки)
    call lstrlenA        ; RAX = длина
    
    mov RCX, hStdOutput  ; hConsole
    mov RDX, string      ; lpBuffer (адрес выводимой строки строки)
    mov R8, RAX          ; nNumberOfChars (длина выводимой строки)
    lea R9, bytesWritten ; lpNumberOfCharsWritten
    NULL_FIFTH_ARG       ; lpReserved (0)
    call WriteConsoleA   ; вывод
    
    STACKFREE
    ret 8
PrintString endp

mainCRTStartup proc
    STACKALLOC

    ; Получение дескрипторов для записи
    mov RCX, STD_OUTPUT_HANDLE
    call GetStdHandle
    mov hStdOutput, RAX


    ; Получение дескрипторов для чтения
    mov RCX, STD_INPUT_HANDLE
    call GetStdHandle
    mov hStdInput, RAX


    lea RAX, aInput
    STACKALLOC
    mov [RSP], RAX
    call PrintString
    STACKFREE


    lea RAX, bInput
    STACKALLOC
    mov [RSP], RAX
    call PrintString
    STACKFREE

    ; lea RAX, a
    ; call inputStr

    ; lea RAX, a
    ; call printStr
    ;
    ; mov RCX, STD_OUTPUT_HANDLE
    ; call GetStdHandle
    ; mov hStdOutput, RAX
    ;
    ; mov RCX, hStdInput
    ; lea RDX, input
    ; mov R8D, 255
    ; lea R9, read
    ; mov qword ptr [rsp+32], 0
    ; call ReadConsoleA
    call ExitProcess
mainCRTStartup endp
end

