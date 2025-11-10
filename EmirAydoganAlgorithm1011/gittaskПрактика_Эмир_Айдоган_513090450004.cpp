#include <iostream>

struct IntArray {
    int* a;
    size_t k, cap;

    IntArray() {
        k = 0;
        cap = 2;
        a = new(std::nothrow) int[cap];
    }

    ~IntArray() {
        delete[] a;
    }

    bool add(int x) {
        if (k == cap) {
            size_t new_cap = cap * 2;
            int* b = new(std::nothrow) int[new_cap];
            if (!b) return false;
            for (size_t i = 0; i < k; ++i)
                b[i] = a[i];
            delete[] a;
            a = b;
            cap = new_cap;
        }
        a[k++] = x;
        return true;
    }

    int get(size_t i) const {
        return a[i];
    }

    int last() const {
        return a[k - 1];
    }

    size_t size() const {
        return k;
    }
};

int main() {
    IntArray arr;
    int next;

    while (std::cin >> next) {
        if (!arr.add(next)) return 2;
    }

    if (!std::cin.eof()) return 1;
    if (arr.size() == 0) return 0;

    int last = arr.last();
    if (last == 0) return 0;

    size_t count = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr.get(i) % last == 0)
            count++;
    }

    std::cout << count << "\n";
    return 0;
}