#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string str, char del) {
    std::vector<std::string> splitted;

    if (str.find(del) == std::string::npos)
        return splitted;
    splitted.push_back(str.substr(0, str.find(del)));
    std::string str1;
    str1 = str.substr(str.find(del) + 1, str.size() - str.find(del));

    while (str1.find(del) != std::string::npos) {
        if (str1.substr(0, str1.find(del)) != "")
            splitted.push_back(str1.substr(0, str1.find(del)));
        str1 = str1.substr(str1.find(del) + 1, str1.size() - str1.find(del));
    }

    splitted.push_back(str1);
    return splitted;
}

struct Date {
        int day;
        int month;
        int year;
};

Date strToDate(std::string str) {
    std::vector<std::string> splitted = split(str, '.');
    Date date;
    date.day = stoi(splitted[0]);
    date.month = stoi(splitted[1]);
    date.year = stoi(splitted[2]);
    return date;
}

struct Employee {
        int id = 0;
        std::string surname;
        std::string job;
        Date date = strToDate("0.0.0000");
        int experience = 0;
        int salary = 0;
};

bool operator==(Employee emp1, Employee emp2) { return emp1.id == emp2.id; }

const std::string SURNAME = "SURNAME";
const std::string JOB = "JOB";
const std::string DATE_OF_BIRTH = "DATE_OF_BIRTH";
const std::string EXPERIENCE = "EXPERIENCE";
const std::string SALARY = "SALARY";
const std::string KEY = "KEY";
const std::vector<std::string> categories = {KEY,           SURNAME,    JOB,
                                             DATE_OF_BIRTH, EXPERIENCE, SALARY};

std::vector<std::string> readfrom(std::string file) {
    std::ifstream in(file);
    std::vector<std::string> lines;

    while (in.peek() != EOF) {
        std::string line;
        getline(in, line, '\n');
        lines.push_back(line);
    }
    return lines;
}

std::string dateToStr(Date date) {
    return std::to_string(date.day) + "." + std::to_string(date.month) + "." +
           std::to_string(date.year);
}

int getMaxSurLength(std::vector<std::vector<Employee>> hashTable) {
    int max = INT_MIN;
    for (int i = 0; i < hashTable.size(); ++i) {
        for (int j = 0; j < hashTable[i].size(); ++j) {
            int cur = hashTable[i][j].surname.size();
            if (cur > max) {
                max = cur;
            }
        }
    }
    return max;
}

int getMaxJobLength(std::vector<std::vector<Employee>> hashTable) {
    int max = INT_MIN;
    for (int i = 0; i < hashTable.size(); ++i) {
        for (int j = 0; j < hashTable[i].size(); ++j) {
            int cur = hashTable[i][j].job.size();
            if (cur > max) {
                max = cur;
            }
        }
    }
    return max;
}

int getMaxExpLength(std::vector<std::vector<Employee>> hashTable) {
    int max = INT_MIN;
    for (int i = 0; i < hashTable.size(); ++i) {
        for (int j = 0; j < hashTable[i].size(); ++j) {
            int cur = (int)std::to_string(hashTable[i][j].experience).length();
            if (cur > max) {
                max = cur;
            }
        }
    }
    return max;
}

int getMaxSalLength(std::vector<std::vector<Employee>> hashTable) {
    int max = INT_MIN;
    for (int i = 0; i < hashTable.size(); ++i) {
        for (int j = 0; j < hashTable[i].size(); ++j) {
            int cur = std::to_string(hashTable[i][j].salary).length();
            if (cur > max)
                max = cur;
        }
    }
    return max;
}

int getMaxDateLength(std::vector<std::vector<Employee>> hashTable) {
    int max = INT_MIN;
    for (int i = 0; i < hashTable.size(); ++i) {
        for (int j = 0; j < hashTable[i].size(); ++j) {
            int cur = (int)dateToStr(hashTable[i][j].date).length();
            if (cur > max)
                max = cur;
        }
    }
    return max;
}

std::string blank(int n) {
    std::string str = "";
    for (int i = 0; i < n; ++i)
        str += " ";
    return str;
}

void printHashTable(std::vector<std::vector<Employee>> hashTable) {
    int maxSurLength = getMaxSurLength(hashTable);
    int maxJobLength = getMaxJobLength(hashTable);
    int maxDateLength = getMaxDateLength(hashTable);
    int maxExpLength = getMaxExpLength(hashTable);
    int maxSalLength = getMaxSalLength(hashTable);

    std::vector<int> spaces = {
        (int)std::to_string(hashTable.size()).length() + 2,
        std::max(maxSurLength, (int)SURNAME.length()) + 1,
        std::max(maxJobLength, (int)JOB.length()) + 1,
        std::max(maxDateLength, (int)DATE_OF_BIRTH.length()) + 1,
        std::max(maxExpLength, (int)EXPERIENCE.length()) + 1,
        std::max(maxSalLength, (int)SALARY.length()) + 1};

    for (int i = 0; i < 6; ++i) {
        std::cout << std::left << std::setw(spaces[i]) << categories[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < hashTable.size(); ++i) {
        std::vector<Employee> employees = hashTable[i];
        if (employees.size() == 0) {
            continue;
        }
        for (int j = 0; j < employees.size(); ++j) {
            Employee employee = employees[j];
            std::cout << std::left << std::setw(spaces[0]) << i;
            std::cout << std::left << std::setw(spaces[1]) << employee.surname;
            std::cout << std::left << std::setw(spaces[2]) << employee.job;
            std::cout << std::left << std::setw(spaces[3])
                      << dateToStr(employee.date);
            std::cout << std::left << std::setw(spaces[4])
                      << employee.experience;
            std::cout << employee.salary << std::endl;
        }
    }
}

int h(double x, int M) {
    x = x * (sqrt(5) - 1) / 2;
    x = x - int(x);
    x = x * M;
    x = int(x);
    return x;
}

std::vector<std::vector<Employee>> createHashTable(std::vector<Employee> A,
                                                   int M) {
    std::vector<std::vector<Employee>> hashTable(M);
    for (int i = 0; i < A.size(); ++i) {
        int k = h(A[i].salary, M);
        hashTable[k].push_back(A[i]);
    }
    return hashTable;
}

std::vector<Employee>::iterator
findInHashTable(std::vector<std::vector<Employee>> &hashTable, Employee X) {
    int k = h(X.salary, hashTable.size());
    for (auto it = hashTable[k].begin(); it != hashTable[k].end(); ++it) {
        if ((*it) == X) {
            return it;
        }
    }
    return hashTable[k].end();
}

void deleteInHashTable(std::vector<std::vector<Employee>> hashTable,
                       Employee X) {
    int k = h(X.salary, hashTable.size());
    hashTable[k].erase(findInHashTable(hashTable, X));
}

int main() {

    std::vector<std::string> file = readfrom("unsorted_employees.txt");
    std::vector<Employee> employees;

    for (int i = 1; i < file.size(); ++i) {
        std::map<std::string, std::string> map;
        std::vector<std::string> splitted = split(file[i], ' ');

        Employee employee;
        employee.id = i;
        employee.surname = splitted[0];
        employee.job = splitted[1];
        employee.date = strToDate(splitted[2]);
        employee.experience = stoi(splitted[3]);
        employee.salary = stoi(splitted[4]);

        employees.push_back(employee);
    }

    std::vector<std::vector<Employee>> hashTable =
        createHashTable(employees, 64);
    printHashTable(hashTable);
}
