#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
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

bool isLeap(int y) { return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0); }

const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int dateToDays(Date date) {

  int days = date.day;

  for (int m = 1; m < date.month; ++m) {
    days += daysInMonth[m];
  }

  for (int y = 0; y < date.year; ++y) {
    if (isLeap(y)) {
      days += 366;
    } else {
      days += 365;
    }
  }

  if (date.month > 2 && isLeap(date.year)) {
    days += 1;
  }

  return days;
}

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

bool operator<(Date date1, Date date2) {
  return date1.year < date2.year ||
         (date1.year == date2.year && date1.month < date2.month) ||
         (date1.year == date2.year && date1.month == date2.month &&
          date1.day < date2.day);
}

bool operator==(Employee emp1, Employee emp2) {
  return emp1.salary == emp2.salary;
}

bool operator>(Date date1, Date date2) {
  return date1.year > date2.year ||
         (date1.year == date2.year && date1.month > date2.month) ||
         (date1.year == date2.year && date1.month == date2.month &&
          date1.day > date2.day);
}

const std::string SURNAME = "SURNAME";
const std::string JOB = "JOB";
const std::string DATE_OF_BIRTH = "DATE_OF_BIRTH";
const std::string EXPERIENCE = "EXPERIENCE";
const std::string SALARY = "SALARY";
const std::vector<std::string> categories = {SURNAME, JOB, DATE_OF_BIRTH,
                                             EXPERIENCE, SALARY};

std::vector<std::string> readfrom(std::string file) {
  std::ifstream in(file);
  std::vector<std::string> lines;
  std::string line;

  while (getline(in, line)) {
    lines.push_back(line);
  }
  return lines;
}

std::vector<Employee> countingSortDates(std::vector<Employee> employees) {
  std::vector<Employee> sorted;

  Date max_date = {0, 0, 0};
  Date min_date = {31, 12, INT_MAX};
  int n = employees.size();
  if (n <= 1) {
    return employees;
  }
  for (int i = 0; i < n; ++i) {
    Employee emp = employees[i];
    if (emp.date < min_date)
      min_date = emp.date;
    if (emp.date > max_date)
      max_date = emp.date;
  }

  int min_days = dateToDays(min_date);
  int max_days = dateToDays(max_date);
  int range = max_days - min_days + 1;
  std::vector<int> count(range);

  int temp = min_days;
  while (temp <= max_days) {
    for (int i = 0; i < n; i++) {
      if (dateToDays(employees[i].date) == temp) {
        count[temp - min_days]++;
      }
    }
    temp++;
  }
  for (int i = min_days; i <= max_days; ++i) {
    if (i == max_days) {
      int b = 0;
    }
    if (count[i - min_days]) {
      for (int j = count[i - min_days]; j > 0; --j) {
        for (int k = 0; k < employees.size(); ++k) {
          if (dateToDays(employees[k].date) == i) {
            sorted.push_back(employees[k]);
            employees.erase(employees.begin() + k);
            break;
          }
        }
      }
    }
  }
  return sorted;
}

std::string dateToStr(Date date) {
  return std::to_string(date.day) + "." + std::to_string(date.month) + "." +
         std::to_string(date.year);
}

int getMaxSurLength(std::vector<Employee> employees) {
  int max = (int)employees[0].surname.length();
  for (int i = 1; i < employees.size(); ++i) {
    int cur = (int)employees[i].surname.size();
    if (cur > max)
      max = cur;
  }
  return max;
}

int getMaxJobLength(std::vector<Employee> employees) {
  int max = (int)employees[0].job.length();
  for (int i = 1; i < employees.size(); ++i) {
    int cur = (int)employees[i].job.length();
    if (cur > max)
      max = cur;
  }
  return max;
}

int getMaxExpLength(std::vector<Employee> employees) {
  int max = (int)std::to_string(employees[0].experience).length();
  for (int i = 1; i < employees.size(); ++i) {
    int cur = (int)std::to_string(employees[i].experience).length();
    if (cur > max)
      max = cur;
  }
  return max;
}

int getMaxSalLength(std::vector<Employee> employees) {
  int max = (int)std::to_string(employees[0].salary).length();
  for (int i = 1; i < employees.size(); ++i) {
    int cur = (int)std::to_string(employees[i].salary).length();
    if (cur > max)
      max = cur;
  }
  return max;
}

int getMaxDateLength(std::vector<Employee> employees) {
  int max = (int)dateToStr(employees[0].date).length();
  for (int i = 1; i < employees.size(); ++i) {
    int cur = (int)dateToStr(employees[i].date).length();
    if (cur > max)
      max = cur;
  }
  return max;
}

std::string blank(int n) {
  std::string str = "";
  for (int i = 0; i < n; ++i)
    str += " ";
  return str;
}

void printIntoFile(std::string file, std::vector<Employee> employees) {
  std::ofstream of(file);

  int maxSurLength = getMaxSurLength(employees);
  int maxJobLength = getMaxJobLength(employees);
  int maxDateLength = getMaxDateLength(employees);
  int maxExpLength = getMaxExpLength(employees);
  int maxSalLength = getMaxSalLength(employees);

  std::vector<int> spaces = {
      std::max(maxSurLength, (int)SURNAME.length()) + 1,
      std::max(maxJobLength, (int)JOB.length()) + 1,
      std::max(maxDateLength, (int)DATE_OF_BIRTH.length()) + 1,
      std::max(maxExpLength, (int)EXPERIENCE.length()) + 1,
      std::max(maxSalLength, (int)SALARY.length()) + 1};

  for (int i = 0; i < 5; ++i) {
    of << std::left << std::setw(spaces[i]) << categories[i];
  }
  of << std::endl;

  for (int i = 0; i < employees.size(); ++i) {
    Employee employee = employees[i];
    of << std::left << std::setw(spaces[0]) << employee.surname;
    of << std::left << std::setw(spaces[1]) << employee.job;
    of << std::left << std::setw(spaces[2]) << dateToStr(employee.date);
    of << std::left << std::setw(spaces[3]) << employee.experience;
    of << employee.salary << std::endl;
  }
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

  std::vector<Employee> employeesSorted = countingSortDates(employees);

  std::vector<int> spaces = {getMaxSurLength(employeesSorted),
                             getMaxJobLength(employeesSorted), 10,
                             getMaxExpLength(employeesSorted)};
  printIntoFile("output.txt", employeesSorted);
}
