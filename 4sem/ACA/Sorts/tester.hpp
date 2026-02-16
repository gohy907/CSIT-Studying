#include <ctime>
#include <fstream>
#include <vector>

namespace tester {

class Tester {
    public:
        void test(void (*sort)(std::vector<int> &));

    private:
        int randFromRange(int start, int end);
        void out_vector(std::ofstream &stream, std::vector<int> &numbers);
        std::clock_t benchmark(void (*sort)(std::vector<int> &),
                               std::vector<int> &numbers);
        void validate(std::vector<int> &initial_numbers,
                      std::vector<int> &numbers);
        void test_with_parameters(void (*sort)(std::vector<int> &),
                                  int number_of_tests, size_t length, int min,
                                  int max, bool critical);
};
} // namespace tester
