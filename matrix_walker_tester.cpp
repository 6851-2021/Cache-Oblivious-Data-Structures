#include "matrix_walker.h"
#include "stdio.h"

int verify(int i, int j, int res, int expected) {
    if (res != expected) {
        fprintf(stderr, "Failed test at index (%d, %d) got %d instead of %d\n", i, j, res, expected);
        return -1;
    }
    return 0;
}

// template <typename T>
// int test_get() {
//     int n = 100;
//     int m = 100;
//     T matrix = new T(n, m);
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++) {
//             matrix.set(i, j, i * j);
//         }
//     }

//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < m; j++) {
//             if (verify(i, j, m.get(i, j), i*j) < 0) {
//                 return -1;
//             }
//         }
//     }
//     fprintf(stderr, "Success square get test");
//     return 0;
// }

template <typename T>
int test_teleport(int n) {
    T *matrix = new T(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            matrix->set(i, j, i+j);
        }
    }

    for (int i = n-1; i >= 0; i--){
        for (int j = 0; j < n; j++) {
            matrix->teleport(i, j);
            if (verify(i, j, matrix->get(), i+j)) {
                return -1;
            }
        }
    }
    fprintf(stderr, "Success teleport test\n");
    return 0;
}

template <typename T>
int test_move(int n) {
    T *matrix = new T(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            matrix->set(i, j, i+j);
        }
    }

    matrix->teleport(n - 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        if((n - i) & 1) {
            for (int j = 0; j < n; j++) {
                if (verify(i, j, matrix->get(), i+j)) {
                    return -1;
                }
                matrix->move_right();
            }
        } else {
            for (int j = n - 1; j >= 0; j--) {
                if (verify(i, j, matrix->get(), i+j)) {
                    return -1;
                }
                matrix->move_left();
            }
        }
        matrix->move_up();
    }

    matrix->teleport(0, 0);
    for (int i = 0; i < n; i++)
    {
        if(!(i & 1)) {
            for (int j = 0; j < n; j++) {
                if (verify(i, j, matrix->get(), i+j)) {
                    return -1;
                }
                matrix->move_right();
            }
        } else {
            for (int j = n - 1; j >= 0; j--) {
                if (verify(i, j, matrix->get(), i+j)) {
                    return -1;
                }
                matrix->move_left();
            }
        }
        matrix->move_down();
    }
    fprintf(stderr, "Success move test\n");
    return 0;
}

int main() {
    test_teleport<naive_matrix_walker>(100);
    test_teleport<co_matrix_walker>(100);

    test_teleport<naive_matrix_walker>(500);
    test_teleport<co_matrix_walker>(500);
    
    test_teleport<naive_matrix_walker>(1234);
    test_teleport<co_matrix_walker>(1234);

    test_move<naive_matrix_walker>(100);
    test_move<co_matrix_walker>(100);

    test_move<naive_matrix_walker>(500);
    test_move<co_matrix_walker>(500);
    
    test_move<naive_matrix_walker>(1234);
    test_move<co_matrix_walker>(1234);
    return 0;
}
