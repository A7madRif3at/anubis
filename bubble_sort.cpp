#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int size) {
    for(int j = 0; j < size; j++) {
        for(int i = 0; i < size - 1; i++) {
            if(arr[i] > arr[i+1]) {
                swap(&arr[i], &arr[i+1]);
            }
        }
    }
}

int main() {
    cout << "Program started" << endl;
    int numbers[5] = {50, 10, 40, 20, 30};
    bubbleSort(numbers, 5);
    for(int i = 0; i < 5; i++) {
        cout << numbers[i] << endl;
    }
    return 0;
}