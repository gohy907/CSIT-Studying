#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#show: codly-init
= Алгоритм Бойера-Мура

== Код программы

#codly(languages: codly-languages)
```cpp
std::map<char, int> compute_badchar(std::string &pattern) {
    std::map<char, int> badchar;
    int m = pattern.length();

    for (int i = 0; i < m; ++i) {
        badchar[pattern[i]] = i;
    }
    return badchar;
}

std::vector<size_t> compute_suffshift(std::string &s) {
    size_t n = s.length();
    std::vector<size_t> suffshift(n + 1, n); // O(n)

    std::string reverse_s = s;
    reverse(reverse_s.begin(), reverse_s.end());

    std::vector<size_t> z = z_func(reverse_s); // O(n)
    reverse(z.begin(), z.end());

    for (size_t i = 0; i < n - 1; ++i) { // O(n)
        size_t len = z[i];
        if (len > 0) {
            suffshift[n - 1 - len] = n - 1 - i;
        }
    }

    size_t j = 0;
    for (size_t k = n; k > 0; --k) {
        size_t i_idx = k - 1;

        if (z[i_idx] == i_idx + 1) {
            size_t shift = n - 1 - i_idx;
            while (j <= shift) {
                if (suffshift[j] == n) {
                    suffshift[j] = shift;
                }
                j++;
            }
        }
    }

    suffshift[n - 1] = 1;
    return suffshift;
}

void boyer_moure(std::string &input_string, std::string &substring) {
    int n = input_string.length();
    int m = substring.length();

    std::vector<size_t> suffshift = compute_suffshift(substring);
    std::map<char, int> badchar = compute_badchar(substring);

    int i = 0;
    int last_s = -1;
    int last_m = 0;

    while (i <= n - m) {
        int j = m - 1;
        int stop_index;
        if (i == last_s) {
            stop_index = last_m - 1;
        } else {
            stop_index = -1;
        }

        while (j > stop_index && substring[j] == input_string[i + j]) {
            --j;
        }

        if (j <= stop_index) {
            std::cout << i << std::endl;
            last_s = i + suffshift[0];
            last_m = m - suffshift[0];

            i += suffshift[0];

        } else {
            char mismatched_char = input_string[i + j];
            int bad_char_shift;
            if (badchar.count(mismatched_char)) {
                bad_char_shift = std::max(1, j - badchar[mismatched_char]);
            } else {
                bad_char_shift = j + 1;
            }

            int good_suffix_shift = suffshift[j];

            i += std::max(good_suffix_shift, bad_char_shift);

            last_s = -1;
            last_m = 0;
        }
    }
}
```

== Анализ сложности

Рассмотрим сначала функцию `compute_suffshift`:

$n$ --- длина входной строки.

Сначала вычисляем Z-функцию от исходной строки за $O(n)$ и разворачиваем её.

Далее внешний цикл имеет $n$ итераций.

Внутренний цикл `while` будет работать суммарно максимум $n$ итераций, потому что $j$ увеличивается на каждой итерации цикла, а $"shift"$ не может быть больше, чем $n$.

Тогда весь цикл будет иметь сложность $O(n) + O(n) = O(n)$, а вся функция $O(n) + O(n) = O(n)$.

Рассмотрим теперь функцию `compute_badchar`:

В ней мы в цикле с количеством итераций, равным длине входной строки, заполняем хэш-таблицу. Сложность: $O(n)$.

И наконец рассмотрим саму функцию `boyer_moure`:

$n$ --- длина входной строки, $m$ --- длина искомого шаблона.

Вызываем функциии `compute_badchar` и `compute_suffshift` от искомого шаблона, это выполняется за $O(m) + O(m) = O(m)$.

В цикле мы итерируемся $n - m$ раз, что аналогично сложности $O(n)$.

В каждой итерации внешнего цикла мы делаем сравнение символов из искомого шаблона и входной строки.
Рассмотрим два случая: когда это эти два символа совпали, и когда нет.

Если символы совпали, то обновляются переменные $"last_s"$ и $"last_m"$, которые показывают область тех символов, которые уже совпали.

Если дальше символы не совпадут, то шаблон подвинется по эвристике хорошего суффикса вправо, а внутренний цикл `while` остановится на индексе `stop_index`, дальше которого находится область символов, которые мы уже проверили, и которые уже совпаадают с текущими в шаблоне.

Таким образом при удачных сравнениях каждый символ исходной строки участвует в этих сравнениях ровно один раз.

Если же символ не совпал, то за каждую итерацию во внешнем цикле $i$ сдвинется минимум на 1, а итераций может быть не более $n$, значит и сравнений может быть не более, чем $n$.

Тогда весь цикл будет иметь сложность $O(n) + O(n) = O(n)$. А функция будет иметь сложность $O(n) + O(m)$.

