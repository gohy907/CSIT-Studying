#include <functional>
#include <vector>
#include <iostream>
#include <numeric>

template <typename Type>
void displayVec(std::vector<Type> vec) {
	std::cout << std::endl;
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << "[" << i << "] = " << vec[i] << std::endl;
	}
}

int main() {
	int n;
	std::cout << "Input n: ";
	std::cin >> n;

	std::vector<long long> vec(n);
	vec[0] = 1;
	for (std::vector<long long>::iterator it = vec.begin()+1; it != vec.end(); ++it) {
		*it = 2;
	}

	std::vector<long long> result(n);
	std::partial_sum(vec.begin(), vec.end(), result.begin(), std::multiplies<long long>());

	std::cout << std::endl;
	for (int i = 0; i < n; ++i) {
		std::cout << "2 ^ " << i << " = " << result[i] << std::endl;
	}
}