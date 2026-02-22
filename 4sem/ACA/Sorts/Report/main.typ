#import "conf.typ" : conf
#import "@preview/lilaq:0.5.0" as lq
#show: conf.with(
  title: [Лабораторная работа №2],
  type: "referat",
  info: (
      author: (
        name: [Архипова Ивана Сергеевича],
        faculty: [КНиИТ],
        group: "251",
        sex: "male"
      ),
      inspector: (
        degree: "Cтарший преподаватель",
        name: "М. И. Сафрончик"
      )
  ),
  settings: (
    title_page: (
      enabled: true
    ),
    contents_page: (
      enabled: false
    )
  )
)

#let lengths = (50000, 100000, 500000, 1000000)
#let quick_sort_results = (8167, 16774, 93805, 196386)
#let merge_sort_results = (19251, 40859, 234569, 485121) 
#let pyramid_sort_results = (18237, 37171, 217471, 463740)
#show: lq.set-legend(position: bottom)
#align(center,
lq.diagram(
  title: [Время выполнения сортировок],
  xlabel: "Размер входных данных", 
  ylabel: "Количество тактов процессора",
  width: 15cm,
  height: 10cm,

lq.plot(lengths, quick_sort_results, label: [Быстрая сортировка]),
lq.plot(lengths, merge_sort_results, label: [Сортировка слиянием]),
lq.plot(lengths, pyramid_sort_results, label: [Пирамидальная сортировка]),
))
 
Как мы можем видеть, самой быстрой сортировкой оказалась быстрая сортировка, за ней идёт пирамидальная сортировка и сортировка слиянием.
