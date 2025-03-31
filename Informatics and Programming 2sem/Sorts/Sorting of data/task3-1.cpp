#include <fstream>
#include <vector>
#include <map>
#include <string>	
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

std::vector<std::string> split(std::string str, char del) {
	std::vector<std::string> splitted;

	if (str.find(del) == std::string::npos) return splitted;
	splitted.push_back(str.substr(0, str.find(del)));
	std::string str1;
	str1 = str.substr(str.find(del) + 1, str.size() - str.find(del));

	while (str1.find(del) != std::string::npos) {
		if (str1.substr(0, str1.find(del)) != "") splitted.push_back(str1.substr(0, str1.find(del)));
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

bool operator < (Employee emp1, Employee emp2) {
	return emp1.salary < emp2.salary;
}

bool operator == (Employee emp1, Employee emp2) {
	return emp1.salary == emp2.salary;
}

bool operator > (Employee emp1, Employee emp2) {
	return emp1.salary > emp2.salary;
}

const std::string SURNAME = "SURNAME";
const std::string JOB = "JOB";
const std::string DATE_OF_BIRTH = "DATE_OF_BIRTH";
const std::string EXPERIENCE = "EXPERIENCE";
const std::string SALARY = "SALARY";
const std::vector<std::string> categories = { SURNAME, JOB, DATE_OF_BIRTH, EXPERIENCE, SALARY };

std::vector<std::string> readfrom(std::string file){
	std::ifstream in(file);
	std::vector<std::string> lines;
	
	while (in.peek() != EOF) {
		std::string line;
		getline(in, line, '\n');
		lines.push_back(line);
	}
	return lines;
}

std::vector<Employee> quicksortBySalary(std::vector<Employee> employees, int l, int r) {
	int i = l;
	int j = r;
	Employee p = employees[(l + r)/2];

	while (i <= j) {
		while (employees[i] < p) ++i;
		while (employees[j] > p) --j;
		
		if (i <= j) {
			Employee tmp = employees[i];
			employees[i] = employees[j];
			employees[j] = tmp;
			--j;
			++i;
		}
	}

	if (j - l > 0) employees = quicksortBySalary(employees, l, j);
	if (r - i > 0) employees = quicksortBySalary(employees, i, r);

	return employees;
}

std::string dateToStr(Date date) {
	return std::to_string(date.day) + "." + std::to_string(date.month) + "." + std::to_string(date.year);
}

int getMaxSurLength(std::vector<Employee> employees) {
	int max = (int)employees[0].surname.length();
	for (int i = 1; i < employees.size(); ++i) {
		int cur = (int)employees[i].surname.size();
		if (cur > max) max = cur;
	}
	return max;
}

int getMaxJobLength(std::vector<Employee> employees) {
	int max = (int)employees[0].job.length();
	for (int i = 1; i < employees.size(); ++i) {
		int cur = (int)employees[i].job.length();
		if (cur > max) max = cur;
	}
	return max;
}

int getMaxExpLength(std::vector<Employee> employees) {
	int max = (int)std::to_string(employees[0].experience).length();
	for (int i = 1; i < employees.size(); ++i) {
		int cur = (int)std::to_string(employees[i].experience).length();
		if (cur > max) max = cur;
	}
	return max;
}

int getMaxSalLength(std::vector<Employee> employees) {
	int max = (int)std::to_string(employees[0].salary).length();
	for (int i = 1; i < employees.size(); ++i) {
		int cur = (int)std::to_string(employees[i].salary).length();
		if (cur > max) max = cur;
	}
	return max;
}

int getMaxDateLength(std::vector<Employee> employees) {
	int max = (int)dateToStr(employees[0].date).length();
	for (int i = 1; i < employees.size(); ++i) {
		int cur = (int)dateToStr(employees[i].date).length();
		if (cur > max) max = cur;
	}
	return max;
}

std::string blank(int n) {
	std::string str = "";
	for (int i = 0; i < n; ++i) str += " ";
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
								std::max(maxDateLength,(int)DATE_OF_BIRTH.length()) + 1,
								std::max(maxExpLength, (int)EXPERIENCE.length()) + 1,
								std::max(maxSalLength, (int)SALARY.length()) + 1
							  };

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
	
	std::vector<Employee> employeesSorted = quicksortBySalary(employees, 0, employees.size() - 1);

	std::vector<int> spaces = { getMaxSurLength(employeesSorted), getMaxJobLength(employeesSorted), 10, getMaxExpLength(employeesSorted) };
	printIntoFile("output.txt", employeesSorted);
}