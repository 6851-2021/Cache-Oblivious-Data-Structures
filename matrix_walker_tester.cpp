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
int test_move(int n, int m) {
    T *matrix = new T(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) {
            matrix->set(i, j, i + 2*j);
        }
    }

    matrix->teleport(n-1, m-1);
    if (matrix->get() != n+2*m-3) {
        fprintf(stderr, "Failed test_move: teleport\n");
        return -1;
    }

    matrix->move_up();
    if (matrix->get() != n+2*m-4) {
        fprintf(stderr, "Failed move up\n");
        return -1;
    }

    matrix->move_left();
    if (matrix->get() !=  n+2*m-6) {
        fprintf(stderr, "Failed move left\n");
        return -1;
    }

    matrix->move_down();
    if (matrix->get() !=  n+2*m-5) {
        fprintf(stderr, "Failed move down\n");
        return -1;
    }

    matrix->move_right();
    if (matrix->get() !=  n+2*m-3) {
        fprintf(stderr, "Failed move right\n");
        return -1;
    }

    fprintf(stderr, "Success move test\n");
    return 0;
}

template <typename T>
int test_teleport(int n, int m) {
    T *matrix = new T(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) {
            matrix->set(i, j, i+j);
        }
    }

    for (int i = n-1; i > 0; i--){
        for (int j = 0; j < m; j++) {
            matrix->teleport(i, j);
            if (verify(i, j, matrix->get(), i+j)) {
                return -1;
            }
        }
    }
    fprintf(stderr, "Success teleport test\n");
    return 0;
}

int main() {
    fprintf(stderr, "----- naive_matrix_walker tests -----\n");
    test_teleport<naive_matrix_walker>(100, 100);
    test_teleport<naive_matrix_walker>(500, 100);
    test_teleport<naive_matrix_walker>(1234, 700);

    test_move<naive_matrix_walker>(100, 100);
    test_move<naive_matrix_walker>(570, 240);
    test_move<naive_matrix_walker>(100, 1500);


    fprintf(stderr, "----- co_matrix_walker tests -----\n");
    test_teleport<co_matrix_walker>(100, 100);
    test_teleport<co_matrix_walker>(500, 100);
    test_teleport<co_matrix_walker>(1234, 700);

    test_move<co_matrix_walker>(100, 100);
    test_move<co_matrix_walker>(570, 240);
    test_move<co_matrix_walker>(100, 1500);

    return 0;
}
