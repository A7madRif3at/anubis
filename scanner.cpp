#include <bits/stdc++.h>
using namespace std;

int main() {
    string ip;
    cout << "Enter target IP: ";
    cin >> ip;
    cout << "Target IP: " << ip << endl;
    

    time_t now = time(0);
    string timestamp = ctime(&now);

    // write to log 
    ofstream log("scan_log.txt");
    log << "=== Anubis Scan ===" <<endl;
    log << "Target: " << ip << endl;
    log << "Time: " << timestamp << endl;
    log << "Status: Pending" << endl;
    log.close();

    cout << "Scan logged for: " << ip << endl;
    system("pause");
    return 0;

}