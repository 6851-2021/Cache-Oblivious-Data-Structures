#include<bits/stdc++.h>
using namespace std;

int func() {
    int sm = 0;
    const int n = (1 << 28);
    int *a = (int *)malloc(n * sizeof(int));
    a[0] = 0;
    a[1] = 1;
    for (int i = 2; i < n; ++i)
    {
        a[i] = a[i - 1] + a[i - 2];
    }
    for (int i = 1; i < n; ++i) {
        a[i] = a[i - 1] * a[i];
        sm += a[i];
    }
    free(a);
    return sm;
}

int main() {
    int sm = 0;
    while (true)
    {
        sm += func();
    }
    cout << sm << endl;
}