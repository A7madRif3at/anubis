#include <iostream>
using namespace std;

template <typename T>
T findMax(T a, T b) {
    return a > b ? a : b;
}



int main() {
    cout << findMax(3, 7) << endl;
    cout << findMax(3.5, 2.1) << endl;
    cout << findMax('a', 'z') << endl;
    system("pause");
    return 0;
}