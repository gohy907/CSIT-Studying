; Подключение внешних функций WinAPI
extrn ExitProcess :proc,
      MessageBoxW :proc

.data
caption dw 0418h,043Dh,0444h,043Eh,0; Строка "Инфо", записанная в кодировке UNICODE
message dw 0418h, 0432h, 0430h, 043Dh, ' ', 
           0410h, 0440h, 0445h, 0438h, 043Fh, 043Eh, 0432h, 0; Строка "Иван Архипов", записанная в кодировке UNICODE

.code
mainCRTStartup proc
  ; Выравнивание стека по 16 байтовой границе
  ; 32 байта для параметров MessageBoxW + 8 байтов для установки смещения
  sub RSP, 8*5

  ; Передача параметров для MessageBoxW
  xor RCX, RCX; RCX = 0
  lea RDX, message; В RDX записываем адрес строки message
  lea R8, caption; В R8 записываем адрес строки caption
  xor R9, R9; R9 = 0

  call MessageBoxW; Вызываем функцию, отображаующую окно

  xor RCX, RCX; RCX = 0, код выхода
  call ExitProcess; Завершаем программу с кодом выхода 0
mainCRTStartup endp
end
