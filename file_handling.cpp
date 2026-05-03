#include <bits/stdc++.h>
using namespace std;

int main() {
    ofstream file("anubis_log.txt"); 
    file << "Target: 192.168.1.1" << endl;
    file << "Port: 80" << endl;
    file << "Status: open" << endl;
    file.close();

    ifstream readFile("anubis_log.txt");
    string line;

    while(getline(readFile, line)) {
        cout << line << endl;
    }
    readFile.close();

    cout << "Log written." << endl;
    system("pause");
    return 0;
}