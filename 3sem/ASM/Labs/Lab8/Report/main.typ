#import "conf.typ": conf, intro, conclusion
#show: conf.with(
  title: [Лабораторная №8. Вариант 1202],
  type: "pract",
  info: (
    author: (
      name: [Архипова Ивана Сергеевича],
      faculty: [КНиИТ],
      group: "251",
      sex: "male",
    ),
    inspector: (
      degree: "Старший преподаватель",
      name: "Черноусова Е. М.",
    ),
  ),
  settings: (
    title_page: (
      enabled: true,
    ),
    contents_page: (
      enabled: false,
    ),
  ),
)

#let tracetable(caption, filename) = {
    set text(lang: "ru")
    figure(
        caption: caption,
       {
            let trace = csv(filename);

            set text(size: 8pt)

            table(columns: 13, 
                table.header(
                    table.cell(rowspan: 2, [Шаг]), table.cell(rowspan: 2, [Машинный код]),
                    table.cell(rowspan: 2, [Команда]), table.cell(colspan: 9, [Регистры]), [Флаги],
                    [AX], [BX], [CX], [DX], [SP], [DS], [SS], [CS], [IP], [CZSOPAID]
                ),
                ..trace.map(r => { 
                    r.at(2) = raw(lang: "tasm", r.at(2));
                    r
                }).flatten()
            )
        }
    )
}

= Текст программы с комментариями
```asm 
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
overflowError db 'Value is out of range', 0
pressAnyKey db 'Press any key to exit...', 0 
newLine db 0Dh, 0Ah, 0

STACKALLOC macro arg
    push R15
    mov R15, RSP        ; Здесь будет храниться указатель на старый стек
    sub RSP, 8*4        ; Освободим в стеке место под 4 обязательных аргумента 
    if arg              ; Если число аргумента макроса не ноль, то
        sub RSP, 8*arg  ; Освободим место и под них
    endif
    and SPL, 0F0h       ; Выровняем стек по 16-байтовой границе
endm

STACKFREE macro 
    mov RSP, R15        ; Занесём в регистр RSP значение, сохранённое в R15 
    pop R15             ; Извлечем из стека старое значение
endm

NULL_FIFTH_ARG macro
    mov qword ptr [RSP + 32], 0 ; Устанавливает пятый аргумент для функций WinAPI в 0
endm

.code

; Выводит новую строку на экран
PrintNL proc 
    push RAX
    lea RAX, newLine
    push RAX
    call PrintString
    pop RAX
    ret
PrintNL endp

; Выводит строку
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

; Чтение знакового числа из консоли
; Если в консоль ввели знаковое число, то оно запишется в RAX и R11 = 0 
; Иначе RAX не изменится и R11 = 1
ReadString proc uses RBX RCX RDX R8 R9
    local ReadStr[64]: byte,  ; Локальный переменные
          bytesRead: dword
    STACKALLOC 2

    mov RCX, hStdInput        ; Заполняем переменные
    lea RDX, readStr          ; для вызова ReadConsoleA
    mov R8, 64
    lea R9, bytesRead
    NULL_FIFTH_ARG
    call ReadConsoleA

    xor RCX, RCX
    mov ECX, bytesRead        ; Количество прочитанных байт
    sub ECX, 2                ; Вычитаем перенос строки и сдвиг каретки

    xor RBX, RBX
    mov R8, 1                 ; Степень 10

    stringloop:               ; Цикл записи цифр в строку
        dec RCX               ; Уменьшим счётчик RCX на 1
        cmp RCX, -1           ; Если прошли всю строку, то
        je scanningComplete   ; Выходим из цикла

        xor RAX, RAX          
        mov AL, readStr[RCX]  ; Получаем символ из строки 
        cmp AL, '-'           ; Если это не '-', 
        jne eval              ; то проверяем является ли символ числом в eval,
        neg RBX               ; иначе меняем знак у RBX 
        
        cmp RCX, 0            ; Если мы встретили минус на первом символе,
        je scanningComplete   ; то всё хорошо, заканчиваем цикл
        jmp error             ; Иначе это неправильно введённое число, ошибка

        eval:                 ; Проверяем является ли символ числом
            cmp AL, 30h       ; ASCII код числа должен находиться между 30h и 39h
            jl error          ; Если это не так, то это ошибка
            cmp AL, 39h
            jg error

            sub RAX, 30h      ; Если это всё-таки число, то умножаем его на соответствующую
            mul R8            ; степень 10 и прибавляем к RBX
            add RBX, RAX
            mov RAX, 10       ; Увеличим RAX в 10 раз для записи следующей цифры
            mul R8            ; в следующем разряде
            mov R8, RAX
            jmp stringloop    ; Затем продолжим выбирать цифры из строки

    scanningComplete:         ; Успешное завершение программы
        mov R10, 0            ; Ошибки нет, R10 = 0
        mov RAX, RBX          ; Заносим полученное число в RAX
        STACKFREE
        ret

    error:                    ; Произошла какая-то ошибка
        mov R10, 1            ; R10 = 1, RAX не перезаписываем
        STACKFREE
        ret

ReadString endp

; Выведет знаковое число в консоль
PrintNumber proc uses RAX RCX RDX R8 R9 R10 R11, num: QWORD 
    local numberStr[22]: byte     ; Локальный переменные
    STACKALLOC 1
    xor R8, R8                    ; Индекс символа в строке
    mov RAX, num
    cmp num, 0                    ; Сравниваем число с 0  
    jge positive                  ; Если оно меньше 0,
    mov numberStr[R8], '-'        ; то в строке сначала записываем '-'
    inc R8                        ; Пропускаем индекс 0, в нём уже '-'
    neg RAX                       ; Для упрощения работы сделаем RAX отрицательным

    positive:                     ; Если же число положительное, то всех предыдущих шагов делать не надо
    mov RBX, 10                   ; RBX = 10 для последующего деления
    xor RCX, RCX                  ; В RCX будем записывать длину строки

    divisionloop:                 ; Разбор числа на цифры
        xor RDX, RDX
        div RBX                   ; Делим RAX на RBX, остаток занесётся в RDX
        add RDX, 30h              ; Делаем RDX цифрой для вывода на экран
        push RDX                  ; И заносим в стек для дальнейшей записи в строку
        inc RCX                   ; Увеличиваем длину строки
        cmp RAX, 0                ; Если делимое не 0, 
        jne divisionloop          ; то продолжаем делить

    makeString:                   ; Записываем полученные ранее цифры из стека в строку
        pop RDX 
        mov numberStr[R8], DL 
        inc R8 
        loop makeString           ; Делаем так RCX раз 

    mov numberStr[R8], 0          ; Добавляем в конец строки нуль-терминатор

    lea RAX, numberStr            ; Выводим полученную строку на экран
    push RAX 
    call PrintString 
    STACKFREE
    ret 8 
PrintNumber endp

; Выводит сообщение о ожидании ввода одной клавишы
; И ждёт ввода одной клавишы
waitingForInput proc uses RAX RCX RDX R8 R9 R10 R11 
    local readStr: byte, bytesRead: dword ; Локальные переменные
    STACKALLOC 1

    lea RAX, pressAnyKey                  ; Выводим строку с сообщением       
    push RAX
    call PrintString

    mov RCX, hStdInput
    lea RDX, readStr
    mov R8, 1                             ; Читаем 1 байт с консоли
    lea R9, bytesRead
    NULL_FIFTH_ARG
    call ReadConsoleA

    STACKFREE
    ret

waitingForInput endp

; Проверяет находится ли число в диапазоне word'а. 
; Число должно находиться в RAX 
; Сделает R11 = 0, если число не выходит за пределы
; и R11 = 1 в противном случае
checkForOverflow proc 
    cmp RAX, 32767   ; Сравниваем число сначала по верхней границе,
    jg overflow     
    cmp RAX, -32768  ; а потом по нижней
    jl overflow 
    
    mov R11, 0       ; Если переполнения нет, то R11 = 0
    ret

    overflow: 
        mov R11, 1   ; Если переполнение есть, то R11 = 1
        ret
checkForOverflow endp

mainCRTStartup proc
    STACKALLOC 0

    mov RCX, STD_OUTPUT_HANDLE ; Получение дескрипторов для записи
    call GetStdHandle
    mov hStdOutput, RAX

    mov RCX, STD_INPUT_HANDLE ; Получение дескрипторов для чтения
    call GetStdHandle
    mov hStdInput, RAX

    lea RAX, aInput           ; Выводим строку 'a = '
    push RAX
    call PrintString

    call ReadString           ; Читаем с консоли число a
    mov RBX, RAX  
    cmp R10, 1                ; Если возникла ошибка, то
    je incorrect              ; обрабатываем её

    call checkForOverflow     ; Проверяем число на соответствие диапазону
    cmp R11, 1                ; Если превышает, то 
    je overflow               ; обрабатываем ошибку

    lea RAX, bInput           ; Выводим строку 'b = '
    push RAX                                         
    call PrintString                                 
                                                     
    call ReadString           ; Читаем с консоли число b
    cmp R10, 1                                       
    je incorrect              ; Если возникла ошибка, то
                              ; обрабатываем её
    call checkForOverflow                            
    cmp R11, 1                ; Проверяем число на сооответствие диапазону
    je overflow               ; Если превышает, то 
                              ; обрабатываем ошибку
    jmp correct 

    overflow:                  ; Обрабатываем переполнение 
        lea RAX, overflowError ; Выводим сообщение о переполнении
        push RAX 
        call PrintString 
        jmp exit               ; Выходим из программы

    incorrect:                 ; Обрабатываем ошибку записи
        lea RAX, invalidChar   ; Выводим сообщение об ошибке
        push RAX 
        call PrintString
        jmp exit               ; Выходим из программы

    correct:                   ; Если всё хорошо, то печатаем информацию в консоль
        push RAX               ; a находится в RBX  
        push RBX               ; b находится в RAX

        lea RAX, output1       ; Выводим первую часть строки вывода 
        push RAX
        call PrintString

        mov RAX, const         ; Выводим константу
        push RAX 
        call PrintNumber

        lea RAX, output2       ; Выводим вторую часть строки вывода
        push RAX 
        call PrintString

        pop RBX 
        pop RAX
        push RAX 
        push RBX

        sub const, RBX        ; Делаем арифметические действия
        add RAX, const
       
        push RAX
        call PrintNumber      ; Выводим получившееся число

        call PrintNL          ; Выводим новую строку

        lea RAX, max          ; Вывод строки с максимумом
        push RAX
        call PrintString

        pop RBX 
        pop RAX

        push RAX 
        push RBX
        sub RAX, RBX          ; Если RAX - RBX > 0, то RAX максимум
        cmp RAX, 0 
        pop RBX 
        pop RAX
        jg bgreater

        mov RAX, RBX         ; Иначе RBX максимум
        push RAX 
        call PrintNumber
        jmp exit

        bgreater: 
            push RAX 
            call PrintNumber

    exit: 
    call PrintNL
    call waitingForInput
    call ExitProcess
mainCRTStartup endp
end
```

= Скриншоты запуска

#figure(image("static/1.png"), caption: [Положительный ответ])
#figure(image("static/2.png"), caption: [Отрицательный ответ])
#figure(image("static/3.png"), caption: [A выходит за границы возможных значений])
#figure(image("static/4.png"), caption: [B выходит за границы возможных значений])
#figure(image("static/5.png"), caption: [Параметр, содержащий кроме цифр другие символы])
#figure(image("static/6.png"), caption: [Отрицательный параметр])
