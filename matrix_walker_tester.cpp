#include "matrix_walker.h"
#include "stdio.h"

int verify(int i, int j, int res, int expected) {
    if (res != expected) {
        fprintf(stderr, "Failed test at index (%d, %d) got %d instead of %d\n", i, j, res, expected);
        return -1;
    }
    return 0;
}

template <typename T>
int test_get() {
    int n = 100;
    int m = 100;
    T matrix = new T(n, m)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            matrix.set(i, j, i*j)
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            if (verify(i, j, m.get(i, j), i*j) < 0) {
                return -1
            }
        }
    }
    fprintf(stderr, "Success square get test")
    return 0
}

template <typename T>
int test_teleport() {
    int n = 100;
    int m = 100;
    T matrix = new T(n, m)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            matrix.set(i, j, i+j);
        }
    }

    for (int i = n-1; i > 0; i-=10){
        for (int j = 0; j < m; j+=10) {
            teleport(i, j);
            if (verify(i, j, matrix.get(i, j), i+j)) {
                return -1
            }
        }
    }
    fprintf(stderr, "Success teleport test")
    return 0
}


int main() {
    test_get<naive_matrix_walker>();
    test_teleport<naive_matrix_walker>();

    test_get<co_matrix_walker>();
    test_teleport<co_matrix_walker>();
    return 0;
}
