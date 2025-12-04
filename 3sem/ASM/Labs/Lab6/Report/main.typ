#import "conf.typ": conf, intro, conclusion
#show: conf.with(
  title: [Лабораторная №6],
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
```

= Скриншот запуска

#figure(image("static/screenshot.jpg"), caption: [Программа])
