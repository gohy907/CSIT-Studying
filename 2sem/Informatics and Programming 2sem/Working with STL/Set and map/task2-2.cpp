#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

bool isNumber(std::string num) {
	for (int i = 0; i < num.size(); ++i) {
		if (48 <= num[i] && num[i] <= 57) return false;
	}
	return true;
}

int main() {
	std::ifstream in("input.txt");
	
	std::map<std::string, int> numbersMap;
	std::set<std::string> numbers;
	while (in.peek() != EOF) {
		std::string str;
		in >> str;
		if (isNumber(str)) {
			++numbersMap[str];
			numbers.insert(str);
		}
	}
	in.close();
	 
	std::cout << "Enter k: ";
	int k;
	std::cin >> k;

	for (std::set<std::string>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
		if (numbersMap[*it] == k) std::cout << *it << std::endl;
	}
}