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
aInput db 'a = ', 0
bInput db 'b = ', 0 
const dq 2C69h
output1 db 'F = ', 0
output2 db ' - a + b = ', 0
max db 'max(a, b) = ', 0
invalidChar db 'Invalid character', 0 
pressAnyKey db 'Press any key to exit...', 0 
newLine db 0Dh, 0Ah, 0

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

PrintNL proc 
    lea RAX, newLine
    push RAX
    call PrintString
    ret
PrintNL endp

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

ReadString proc uses RBX RCX RDX R8 R9
    local ReadStr[64]: byte,
          bytesRead: dword
    STACKALLOC 2
    mov RCX, hStdInput
    lea RDX, readStr
    mov R8, 64
    lea R9, bytesRead
    NULL_FIFTH_ARG
    call ReadConsoleA
    xor RCX, RCX
    mov ECX, bytesRead
    sub ECX, 2

    xor RBX, RBX
    mov R8, 1

    stringloop:
        dec RCX
        cmp RCX, -1
        je scanningComplete

        xor RAX, RAX
        mov AL, readStr[RCX]
        cmp AL, '-'
        jne eval
        neg RBX

        cmp RCX, 0 
        je scanningComplete 
        jmp error

    eval:
        cmp AL, 30h
        jl error
        cmp AL, 39h
        jg error

        sub RAX, 30h
        mul R8
        add RBX, RAX
        mov RAX, 10
        mul R8
        mov R8, RAX
        jmp stringloop
        


    scanningComplete:
        mov R10, 0
        mov RAX, RBX
        STACKFREE
        ret


    error:
        mov R10, 1
        STACKFREE
        ret

ReadString endp

PrintNumber proc uses RAX RCX RDX R8 R9 R10 R11, num: QWORD 
    local numberStr[22]: byte 
    STACKALLOC 1
    xor R8, R8 
    mov RAX, num
    cmp num, 0
    jge positive
    mov numberStr[R8], '-'
    inc R8
    neg RAX

    positive:
    mov RBX, 10
    xor RCX, RCX

    divisionloop:
        xor RDX, RDX
        div RBX
        add RDX, 30h
        push RDX
        inc RCX
        cmp RAX, 0 
        jne divisionloop 

    stack:
        pop RDX 
        mov numberStr[R8], DL 
        inc R8 
        loop stack 

    mov numberStr[R8], 0 
    lea RAX, numberStr
    push RAX 
    call PrintString 
    STACKFREE
    ret 8 
PrintNumber endp

waitingForInput proc uses RAX RCX RDX R8 R9 R10 R11 
    local readStr: byte, bytesRead: dword
    STACKALLOC 1

    lea RAX, pressAnyKey
    push RAX
    call PrintString

    mov RCX, hStdInput
    lea RDX, readStr
    mov R8, 1
    lea R9, bytesRead
    NULL_FIFTH_ARG
    call ReadConsoleA

    STACKFREE
    ret

waitingForInput endp

mainCRTStartup proc
    STACKALLOC 0

    ; Получение дескрипторов для записи
    mov RCX, STD_OUTPUT_HANDLE
    call GetStdHandle
    mov hStdOutput, RAX


    ; Получение дескрипторов для чтения
    mov RCX, STD_INPUT_HANDLE
    call GetStdHandle
    mov hStdInput, RAX

    lea RAX, aInput
    push RAX
    call PrintString

    call ReadString
    mov RBX, RAX
    cmp R10, 1
    je incorrect

    lea RAX, bInput
    push RAX
    call PrintString

    call ReadString
    cmp R10, 1
    je incorrect
    jne correct

    incorrect:
        lea RAX, invalidChar
        push RAX 
        call PrintString
        jmp exit

    correct:
        push RAX 
        push RBX

        lea RAX, output1 
        push RAX
        call PrintString

        mov RAX, const
        push RAX 
        call PrintNumber

        lea RAX, output2
        push RAX 
        call PrintString

        pop RBX 
        pop RAX

        sub const, RBX
        add RAX, const
        
        push RAX
        call PrintNumber

    exit: 
    call PrintNL
    call waitingForInput
    call ExitProcess
mainCRTStartup endp
end

