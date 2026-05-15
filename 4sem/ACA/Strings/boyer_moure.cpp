#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<size_t> z_func(std::string &str) {
    size_t n = str.size();
    std::vector<size_t> arr(n, 0);

    for (size_t i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            if (r - i + 1 < arr[i - l])
                arr[i] = r - i + 1;
            else
                arr[i] = arr[i - l];
        }

        while (i + arr[i] < n && str[arr[i]] == str[i + arr[i]]) {
            ++arr[i];
        }

        if (i + arr[i] - 1 > r) {
            l = i;
            r = i + arr[i] - 1;
        }
    }
    return arr;
}

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
    std::vector<size_t> suffshift(n + 1, n);

    std::string reverse_s = s;
    reverse(reverse_s.begin(), reverse_s.end());

    std::vector<size_t> z = z_func(reverse_s);
    reverse(z.begin(), z.end());

    for (size_t i = 0; i < n - 1; ++i) {
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

    while (j < n) {
        if (suffshift[j] == n) {
            suffshift[j] = n;
        }
        j++;
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

int main() {
    std::string input_string;
    std::string substring;
    std::cin >> input_string;
    std::cin >> substring;
    boyer_moure(input_string, substring);
}
