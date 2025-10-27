#include "complexNumber.h"
#include "error.h"
#include "list.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

// Возвращает true, если комплексное число находится в первой четверти
// координатной плоскости, включая границы, и false в обратном случае
bool isInFirstQuarter(complexNumber num) {
    return (0 <= sin(num.angle()) && sin(num.angle()) <= 1) &&
           (0 <= cos(num.angle()) && cos(num.angle()) <= 1);
}

void checkForEOF() {
    if (std::cin.eof()) {
        exit(0);
    }
}

bool isValidFloat(std::string &str) {
    try {
        double num = std::stod(str);
    } catch (std::invalid_argument &error) {
        checkForEOF();
        return false;
    }

    return true;
}

bool isValidSize(std::string &str) {
    try {
        int num = std::stoull(str);
    } catch (std::invalid_argument &error) {
        checkForEOF();
        return false;
    }
    return true;
}

// Возвращает true, если введённые данные верны и запишет в num новый
// complexNumber Возвращает false иначе
complexNumber getComplexNumberFromUser() {
    std::string rStr;
    std::string phiStr;

    std::cout << "Введите радиус: ";
    std::getline(std::cin, rStr);

    if (!isValidFloat(rStr)) {
        throw ExceptionBadNumberInput();
    }

    std::cout << "Введите угол: ";
    std::getline(std::cin, phiStr);
    if (!isValidFloat(phiStr)) {
        throw ExceptionBadNumberInput();
    }

    complexNumber num = complexNumber(std::stod(rStr), std::stod(phiStr));
    return num;
}

size_t getIndexFromUser() {
    std::cout << "Введите индекс: ";
    std::string indexStr;
    std::getline(std::cin, indexStr);
    checkForEOF();
    size_t index = std::stoull(indexStr);
    return index;
}
// Возвращает true, если радиус complexNumber < 2
// Возвращает false иначе
bool isRadiusLess2(complexNumber &num) { return num.radius() < 2; }

// Добавит 0.5 радиан к углу всех complexNumber
// Если выполняется condition
void List::addIf(bool condition(complexNumber &num)) {
    for (int i = 0; i < length(); ++i) {
        complexNumber &num1 = (*this)[i];
        if (condition(num1)) {
            num1.setAngle(num1.angle() + 0.5);
        }
    }
}

// Возвращает true, если радиус complexNumber > 1
// Возвращает false иначе
bool isRadiusMore1(complexNumber &num) { return num.radius() > 1; }

// Поделит угол всех complexNumber на 2 и добавит их в конец List
// если выполняется condition
void List::halfAngleIf(bool condition(complexNumber &num)) {
    List tmp = List();

    for (int i = 0; i < length(); ++i) {
        complexNumber &num1 = (*this)[i];
        if (condition(num1)) {
            tmp.push(num1);
        }
    }

    for (int i = 0; i < tmp.length(); ++i) {
        tmp[i].setAngle(tmp[i].angle() / 2);
        push(tmp[i]);
    }
}

int main() {
    List list = List();
    while (true) {
        try {
            std::cout << "0: Выйти" << std::endl;
            std::cout << "1: Вывести список" << std::endl;
            std::cout << "2: Добавить в конец списка число" << std::endl;
            std::cout << "3: Добавить число в какое-то место списка"
                      << std::endl;
            std::cout << "4: Удалить из списка число" << std::endl;
            std::cout << "5: Найти число" << std::endl;
            std::cout << "6: Вывести число из списка" << std::endl;
            std::cout << "7: Вывести число из списка в алгебраической форме"
                      << std::endl;
            std::cout << "8: Прибавить ко всем числам, с радиусом меньше 2, "
                         "0.5 к углу"
                      << std::endl;
            std::cout << "9: Сделать копии чисел из списка, у которых радиус "
                         "больше 1, уменьшить вдвое их угол и "
                         "добавить в конец списка"
                      << std::endl;

            std::cout << "Выберите действие: ";

            std::string optionStr;
            std::getline(std::cin, optionStr);
            checkForEOF();
            std::cout << std::endl;

            int option;
            if (isValidSize(optionStr)) {
                option = std::stoi(optionStr);
            } else {
                std::cout << "ОШИБКА: Ожидалось число от 0 до 9" << std::endl;
                continue;
            }

            if (option == 0) {
                break;
            } else if (option < 0 || option > 9) {
                std::cout << "ОШИБКА: Ожидалось число от 0 до 9" << std::endl;
            }

            switch (option) {
            case 1: {
                list.print();
                break;
            }
            case 2: {
                list.push(getComplexNumberFromUser());
                break;
            }
            case 3: {
                size_t index = getIndexFromUser();
                list.insert(index, getComplexNumberFromUser());
                break;
            }
            case 4: {
                size_t index = getIndexFromUser();
                list.remove(index);
                break;
            }
            case 5: {
                complexNumber num = getComplexNumberFromUser();
                size_t index = list.find(num);
                if (index == list.length()) {
                    std::cout << "ОШИБКА: Число не найдено" << std::endl;
                } else {
                    std::cout << index << std::endl;
                }
                break;
            }
            case 6: {
                size_t index = getIndexFromUser();
                list[index].print();
                std::cout << std::endl;
                break;
            }
            case 7: {
                size_t index = getIndexFromUser();
                complexNumber num = list[index];
                std::cout << "(" << num.getRe() << ", " << num.getIm() << ")"
                          << std::endl;
            } break;
            case 8: {
                list.addIf(isRadiusLess2);
                break;
            }
            case 9: {
                list.halfAngleIf(isRadiusMore1);
            }
            }

            std::cout << std::endl;
        } catch (double) {
            std::cerr << "ОШИБКА: Ввод дробного числа из неверного диапазона"
                      << std::endl;
        } catch (Error &error) {
            std::cerr << error.what() << std::endl;
        } catch (std::invalid_argument &error) {
            checkForEOF();
            std::cerr << error.what() << std::endl;
        } catch (std::out_of_range &error) {
            std::cerr << error.what() << std::endl;
        }
    }
}
