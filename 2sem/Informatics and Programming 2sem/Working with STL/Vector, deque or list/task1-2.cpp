//#include <algorithm>
//#include <iostream>
//#include <vector>
//
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
//int firstMinIt(std::vector<int> vec) {
//	int index = 0;
//	int min = vec[index];
//	for (int i = 0; i < vec.size(); ++i) {
//		if (min > vec[i]) {
//			min = vec[i];
//			index = i;
//		}
//	}
//
//	return index;
//}
//
////std::vector<int>::iterator enterInSorted(std::vector<int> vec, int el) {
////	if (el <= *(vec.begin())) return vec.begin();
////							
////	for (std::vector<int>::iterator it = vec.begin(); it != vec.end() - 1; ++it) {
////		std::cout << *it << " " << * (it + 1);
////		if (*it <= el && el <= *(it + 1)) {
////			return it+1;
////		}
////	}
////
////	return vec.end();
////}
//
//std::vector<int>::iterator enterInSorted(std::vector<int>& vec, int el) {
//	if (vec.empty() || el <= *(vec.begin())) return vec.begin();
//
//	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
//		if (it + 1 == vec.end() || (*it <= el && el <= *(it + 1))) {
//			return it + 1;
//		}
//	}
//
//	return vec.end();
//}
//
//int main() {
//	std::vector<int> vec = createVec<int>();
//	std::vector<int> vecNoOdds = removeOdds(vec);
//	displayVec(vecNoOdds);
//	
//	std::vector<int> vecRotated = vec;
//	std::vector<int>::iterator min = min_element(vecRotated.begin(), vecRotated.end());
//	std::rotate(vecRotated.begin(), min, vecRotated.end());
//	displayVec(vecRotated);
//	
//	std::vector<int> vecSorted = vec;
//	sort(vecSorted.begin(), vecSorted.end());
//	displayVec(vecSorted);
//
//	int el;
//	std::cout << std::endl << "Enter new element: ";
//	std::cin >> el;
//
//	std::vector<int> vecSorted1 = vecSorted;
//	std::vector<int>::iterator m = enterInSorted(vecSorted1, el);
//	vecSorted1.insert(m, el);
//	displayVec(vecSorted1);
//}
//
