#include <iostream>

double mean(const int* begin, size_t k) {
    if (k == 0) return 0.0;
    int sum = 0;
    for (size_t i = 0; i < k; ++i) {
        sum += begin[i];
    }
    return static_cast<double>(sum) / k;
}

double mean(const int* begin, const int* end) {
    if (begin == end) return 0.0;
    int sum = 0;
    size_t count = 0;
    for (const int* p = begin; p < end; ++p) {
        sum += *p;
        ++count;
    }
    return static_cast<double>(sum) / count;
}

int main() {
    int a[5] = {5, 10, 15};

    double m1 = mean(a, 3);              
    double m2 = mean(a, a + 3);          

    int* b = a + 2;
    int* e = a + 5;
    double m3 = mean(b, e);              

    std::cout << "m1 = " << m1 << "\n";
    std::cout << "m2 = " << m2 << "\n";
    std::cout << "m3 = " << m3 << "\n";

    return 0;
}
