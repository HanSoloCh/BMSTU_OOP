#include <iostream>
#include <vector>

#include "../imp/iterator.hpp"
#include "../imp/reverse_iterator.hpp"
#include "../imp/vector.hpp"

int main() {
    {
        Vector<int> vec{1, 2, 3, 4};
        std::cout << "Арифметические операции:\n";
        std::cout << vec;
    }
    {
        std::cout << "Конструкторы:\n";
        std::vector<double> vec_d{1.2, 3.4};
        Vector<int> vec_i(vec_d);
        std::cout << vec_i;
    }
    {
        std::cout << "Унарный минус:\n";
        Vector<int> vec{1, 2, 3};
        std::cout << -vec;
    }
    {
        std::cout << "Итераторы:\n";
        Vector<int> vec{1, 2, 3, 4};
        for (auto it = vec.rbegin(); it < vec.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        for (auto it = vec.begin(); it < vec.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}