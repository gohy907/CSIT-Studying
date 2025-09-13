//#include <vector>
//#include <iostream>
//#include <map>
//#include <set>
//
//bool notInAnyNumber(std::set<int> s, int el) {
//	for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it) {
//		if (el == *it % 10 || el == *it / 10) return false;
//	}
//	return true;
//}
//
//int main() {
//	int size;
//	std::cout << "Enter size: ";
//	std::cin >> size;
//
//	std::set<int> digits;
//	std::set<int> nums;
//	std::cout << std::endl << "Enter sequence: " << std::endl;
//	for (int i = 0; i < size; ++i) {
//		int el;
//		std::cin >> el;
//		if (el >= 100) continue;
//		if (el >= 10) nums.insert(el);
//		else digits.insert(el);
//	}
//	std::cout << std::endl;
//
//	std::map<int, bool> digitsMap;
//	for (std::set<int>::iterator it = digits.begin(); it != digits.end(); ++it) {
//		digitsMap[*it] = notInAnyNumber(nums, *it);
//	}
//
//	for (std::set<int>::iterator it = digits.begin(); it != digits.end(); ++it) {
//		if (digitsMap[*it]) std::cout << *it << std::endl;
//	}
//
//}