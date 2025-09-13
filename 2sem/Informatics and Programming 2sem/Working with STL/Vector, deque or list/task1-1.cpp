//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//template <typename Type>
//void displayVec(std::vector<Type> vec) {
//	std::cout << std::endl;
//	for (int i = 0; i < vec.size(); ++i) {
//		std::cout << "[" << i << "] = " << vec[i] << std::endl;
//	}
//}
//
//template <typename Type>
//std::vector<Type> createVec() {
//	int size;
//	std::cout << "Input size: ";
//	std::cin >> size;
//
//	std::vector<int> vec;
//	vec.reserve(size);
//
//	for (int i = 0; i < size; ++i) {
//		std::cout << "[" << i << "] = ";
//		Type x;
//		std::cin >> x;
//		vec.push_back(x);
//	}
//
//	return vec;
//}
//
//bool isOdd(int num) {
//	return num % 2 != 0;
//}
//
//std::vector<int> removeOdds(std::vector<int> vec) {
//	std::vector<int>::iterator it = remove_if(vec.begin(), vec.end(), isOdd);
//	vec.erase(it, vec.end());
//	return vec;
//}
//
//int main() {
//	std::vector<int> vec = createVec<int>();
//	std::vector<int> vecNoOdds = removeOdds(vec);
//	displayVec(vecNoOdds);
//
//}
//
