#include <iostream>
#include <fstream>
#include <new>

using namespace std;

void printMatrix(int rows, int cols, const int* a)
{
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cout << a[r * cols + c];
            if (c + 1 < cols) cout << ' ';
        }
        cout << '\n';
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return 1;

    ifstream fin(argv[1]);
    if (!fin)
        return 1;

    int m, n;
    if (!(fin >> m >> n) || m < 0 || n < 0)
        return 1;

    long long size = 1LL * m * n;
    int* a = nullptr;

    try {
        if (size > 0)
            a = new int[size];
    }
    catch (bad_alloc&) {
        return 2;
    }

    for (long long i = 0; i < size; ++i) {
        if (!(fin >> a[i])) {
            delete[] a;
            return 1;
        }
    }

    int cmd, p1, p2;

    while (cin >> cmd) {
        if (!(cin >> p1 >> p2)) {
            delete[] a;
            return 3;   
        }

        if (cmd == 1) {
            if (p1 < 0 || p1 > m) {
                delete[] a;
                return 3;
            }

            int insertRow = p1;     
            int newM      = m + 1;
            long long newSize = 1LL * newM * n;

            int* b = nullptr;
            try {
                if (newSize > 0)
                    b = new int[newSize];
            }
            catch (bad_alloc&) {
                delete[] a;
                return 2;
            }

            for (int r = 0; r < newM; ++r) {
                for (int c = 0; c < n; ++c) {
                    if (r == insertRow) {
                        b[r * n + c] = p2;
                    } else {
                        int oldR = (r < insertRow) ? r : r - 1;
                        b[r * n + c] = a[oldR * n + c];
                    }
                }
            }

            delete[] a;
            a = b;
            m = newM;
        }
        else if (cmd == 2) {
            if (p1 < 0 || p1 > n) {
                delete[] a;
                return 3;
            }

            int insertCol = p1;    
            int newN      = n + 1;
            long long newSize = 1LL * m * newN;

            int* b = nullptr;
            try {
                if (newSize > 0)
                    b = new int[newSize];
            }
            catch (bad_alloc&) {
                delete[] a;
                return 2;
            }

            for (int r = 0; r < m; ++r) {
                for (int c = 0; c < newN; ++c) {
                    if (c == insertCol) {
                        b[r * newN + c] = p2;
                    } else {
                        int oldC = (c < insertCol) ? c : c - 1;
                        b[r * newN + c] = a[r * n + oldC];
                    }
                }
            }

            delete[] a;
            a = b;
            n = newN;
        }
        else if (cmd == 3) {
            if (p1 < 0 || p1 > m || p2 < 0 || p2 > n) {
                delete[] a;
                return 3;
            }

            int insertRow = p1;
            int insertCol = p2;
            int newM      = m + 1;
            int newN      = n + 1;
            long long newSize = 1LL * newM * newN;

            int* b = nullptr;
            try {
                if (newSize > 0)
                    b = new int[newSize];
            }
            catch (bad_alloc&) {
                delete[] a;
                return 2;
            }

            for (int r = 0; r < newM; ++r) {
                for (int c = 0; c < newN; ++c) {
                    if (r == insertRow || c == insertCol) {
                        b[r * newN + c] = 0;
                    } else {
                        int oldR = (r < insertRow) ? r : r - 1;
                        int oldC = (c < insertCol) ? c : c - 1;
                        b[r * newN + c] = a[oldR * n + oldC];
                    }
                }
            }

            delete[] a;
            a = b;
            m = newM;
            n = newN;
        }
        else {
            delete[] a;
            return 3;
        }

        printMatrix(m, n, a);
    }

    delete[] a;
    return 0;
}
