#include <iostream>
#include <fstream>
#include <new>
#include <stdexcept>

using namespace std;

struct IntArray {
    int* data;
    size_t size;
    size_t capacity;

    IntArray() : data(nullptr), size(0), capacity(0) {}

    IntArray(int v) : data(nullptr), size(0), capacity(0) {
        if (v > 0) {
            data = new(nothrow) int[v];
            if (!data) throw bad_alloc();
            capacity = (size_t)v;
        }
    }

    IntArray(size_t n) : data(nullptr), size(0), capacity(n) {
        if (n > 0) {
            data = new(nothrow) int[n];
            if (!data) throw bad_alloc();
            for (size_t i = 0; i < n; i++) {
                data[i] = 0;
            }
            size = n;
        }
    }

    ~IntArray() {
        delete[] data;
    }

    size_t getSize() const noexcept {
        return size;
    }

    void add(int value) {
        if (size >= capacity) {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            int* new_data = new(nothrow) int[new_capacity];
            if (!new_data) throw bad_alloc();

            for (size_t i = 0; i < size; i++) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

    int get(size_t index) const noexcept {
        if (index < size) {
            return data[index];
        }
        return 0;
    }

    int at(size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    int last() const {
        if (size == 0) {
            throw out_of_range("Array is empty");
        }
        return data[size - 1];
    }

    int& operator[](size_t index) {
        return data[index];
    }

    const int& operator[](size_t index) const {
        return data[index];
    }
};

struct IntMatrix {
    size_t m, n;
    IntArray a;

    IntMatrix(size_t mm, size_t nn) : m(mm), n(nn), a(mm * nn) {}

    int& at(size_t r, size_t c) {
        return a[r * n + c];
    }

    const int& at(size_t r, size_t c) const {
        return a[r * n + c];
    }

    size_t rowCount() const noexcept { return m; }
    size_t colCount() const noexcept { return n; }

    void print() const {
        for (size_t r = 0; r < m; r++) {
            for (size_t c = 0; c < n; c++) {
                cout << at(r, c);
                if (c + 1 < n) cout << ' ';
            }
            cout << '\n';
        }
    }
};

int main(int argc, char** argv)
{
    if (argc != 2)
        return 1;

    ifstream fin(argv[1]);
    if (!fin)
        return 1;

    int m, n;
    if (!(fin >> m >> n) || m <= 0 || n<= 0)
        return 1;

    long long size = 1LL * m * n;
    IntMatrix* mat = nullptr;

    try {
        mat = new IntMatrix((size_t)m, (size_t)n);
    } catch (...) {
        return 2;
    }

    for (long long i = 0; i < size; i++) {
        if (!(fin >> mat->a[(size_t)i])) {
            delete mat;
            return 1;
        }
    }

    int cmd, p1, p2;

    while (cin >> cmd) {

        if (!(cin >> p1 >> p2)) {
            delete mat;
            return 3;
        }

        if (cmd == 1) {
            if (p1 < 0 || p1 > (int)mat->m) {
                delete mat;
                return 3;
            }

            size_t newM = mat->m + 1;
            IntMatrix* nw = nullptr;
            try {
                nw = new IntMatrix(newM, mat->n);
            } catch (...) {
                delete mat;
                return 2;
            }

            for (size_t r = 0; r < newM; r++) {
                for (size_t c = 0; c < mat->n; c++) {
                    if (r == (size_t)p1) {
                        nw->at(r, c) = p2;
                    } else {
                        size_t oldr = (r < (size_t)p1 ? r : r - 1);
                        nw->at(r, c) = mat->at(oldr, c);
                    }
                }
            }

            delete mat;
            mat = nw;
        }

        else if (cmd == 2) {
if (p1 < 0 || p1 > (int)mat->n) {
                delete mat;
                return 3;
            }

            size_t newN = mat->n + 1;
            IntMatrix* nw = nullptr;
            try {
                nw = new IntMatrix(mat->m, newN);
            } catch (...) {
                delete mat;
                return 2;
            }

            for (size_t r = 0; r < mat->m; r++) {
                for (size_t c = 0; c < newN; c++) {
                    if (c == (size_t)p1) {
                        nw->at(r, c) = p2;
                    } else {
                        size_t oldc = (c < (size_t)p1 ? c : c - 1);
                        nw->at(r, c) = mat->at(r, oldc);
                    }
                }
            }

            delete mat;
            mat = nw;
        }

        else if (cmd == 3) {
            if (p1 < 0 || p1 > (int)mat->m) {
                delete mat;
                return 3;
            }
            if (p2 < 0 || p2 > (int)mat->n) {
                delete mat;
                return 3;
            }

            size_t newM = mat->m + 1;
            size_t newN = mat->n + 1;

            IntMatrix* nw = nullptr;
            try {
                nw = new IntMatrix(newM, newN);
            } catch (...) {
                delete mat;
                return 2;
            }

            for (size_t r = 0; r < newM; r++) {
                for (size_t c = 0; c < newN; c++) {
                    if (r == (size_t)p1 || c == (size_t)p2) {
                        nw->at(r, c) = 0;
                    } else {
                        size_t oldr = (r < (size_t)p1 ? r : r - 1);
                        size_t oldc = (c < (size_t)p2 ? c : c - 1);
                        nw->at(r, c) = mat->at(oldr, oldc);
                    }
                }
            }

            delete mat;
            mat = nw;
        }

        else {
            delete mat;
            return 3;
        }

        mat->print();
    }

    delete mat;
    return 0;
}