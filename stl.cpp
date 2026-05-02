#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> numbers;
    
    numbers.push_back(50);
    numbers.push_back(10);
    numbers.push_back(30);
    sort(numbers.begin(), numbers.end());
    for(int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << endl;
    }
    map<string, int> scores;
    scores["Ahmed"] = 95;
    scores["Moustafa"] = 80;
    scores["Sara"] = 88;
    for(auto& pair : scores) {
        cout << pair.first << " - " << pair.second << endl;
    }

    cout << scores["Ahmed"] << endl;
    system("pause");
    return 0;
}