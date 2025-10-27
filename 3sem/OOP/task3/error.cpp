#include <exception>
#include <string>

class Error : public std::exception {
    public:
        virtual std::string what() { return "ОШИБКА: Неизвестная ошибка"; };
};

class ExceptionBadNumberInput : public Error {
    public:
        std::string what() {
            return "ОШИБКА: Ошибка ввода, ожидалось число в формате 12.34";
        };
};

class MemoryException : public Error {
    public:
        std::string what() { return "ОШИБКА: Ошибка памяти"; }
};

class FileException : public Error {
    public:
        std::string what() { return "ОШИБКА: Ошибка файла"; }
};

class ExceptionDivisionByZero : public Error {
    public:
        std::string what() { return "ОШИБКА: Деление на ноль"; }
};
