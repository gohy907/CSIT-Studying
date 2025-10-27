#pragma once
#include <exception>
#include <string>

class Error : public std::exception {};

class ExceptionBadNumberInput : public Error {};

class MemoryException : public Error {};

class FileException : public Error {};
