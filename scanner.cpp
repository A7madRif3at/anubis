#include <bits/stdc++.h>
using namespace std;



int main() {
    string ip;
    cout << "Enter target IP: ";
    cin >> ip;
    cout << "Target IP: " << ip << endl;
    

    time_t now = time(0);
    string timestamp = ctime(&now);
    // GeoIP lookup
    string command = "curl -s http://ip-api.com/line/" + ip + "?fields=country,city,isp";
    system(command.c_str());
    
    // write to log 
    ofstream log("scan_log.txt");
    log << "=== Anubis Scan ===" <<endl;
    log << "Target: " << ip << endl;
    log << "Time: " << timestamp << endl;
    log << "GeoIP Lookup: " << endl;
    cout << "Scan logged for: " << ip << endl;

    FILE* pipe = popen(command.c_str(), "r");
    char buffer[256];
    while(fgets(buffer, 256, pipe)) {
        log << buffer;
    }
    int ports[] = {21, 22, 23, 25, 53, 80, 443, 445, 3389};

    for(int i = 0; i < 9; i++){
        int port = ports[i];
        string testCommand = "curl -s --connect-timeout 1 " + ip + ":" + to_string(port);
        int result = system(testCommand.c_str());
        if(result == 0) {
            cout << "Port" << port << "is open" << endl;
            log << "Port" << port << "is open" << endl;
        }
        }
    


    pclose(pipe);
    log << "Status: Pending" << endl;
    log.close();
    system("pause");

    return 0;

}