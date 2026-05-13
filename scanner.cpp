#include <bits/stdc++.h>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

bool isPortOpen(string ip, int port) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    int timeout = 1000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server.sin_addr);
    
    bool isOpen = (connect(sock, (sockaddr*)&server, sizeof(server)) == 0);
    
    closesocket(sock);
    WSACleanup();
    
    return isOpen;
}

string detectService(string ip, int port){
    string cmd = "curl -I --connect-timeout 1 " + ip + ":" + to_string(port) + " 2>&1 | findstr Server";
    FILE* pipe = popen(cmd.c_str(), "r");
    char buffer[256];
    string result = "Unknown";
    if(fgets(buffer, 256, pipe)) {
        result = string(buffer);
    }
    pclose(pipe);
    return result;
}

int main() {
    string ip;
    cout << "Enter target IP: ";
    cin >> ip;
    
    time_t now = time(0);
    string timestamp = ctime(&now);
    timestamp.pop_back();

    // GeoIP lookup
    string command = "curl -s http://ip-api.com/line/" + ip + "?fields=country,city,isp";
    system(command.c_str());
    
    // Write to log
    ofstream log("scan_log.txt");
    log << "=== Anubis Scan ===" << endl;
    log << "Target: " << ip << endl;
    log << "Time: " << timestamp << endl;
    log << "GeoIP Lookup: " << endl;

    FILE* pipe = popen(command.c_str(), "r");
    char buffer[256];
    while(fgets(buffer, 256, pipe)) {
        log << buffer;
    }
    
    // Port scanning with raw sockets
    int ports[] = {21, 22, 23, 25, 53, 80, 443, 445, 3389};
    for(int i = 0; i < 9; i++){
        int port = ports[i];
        if(isPortOpen(ip, port)) {
            string service = detectService(ip, port);
            cout << "Port " << port << " is OPEN - " << service << endl;
            log << "Port " << port << " is OPEN - " << service << endl;
        }
    }
    
    // CSV output
    ofstream csv("scan_result.csv", ios::app);
    csv << timestamp << "," << ip << ",Poland,Warsaw,EDGECAST,Scanned" << endl;
    csv.close();

    // JSON output - read-modify-write
    ifstream readJson("scan_results.json");
    string existingContent = "";
    string line;
    while(getline(readJson, line)) {
        existingContent += line + "\n";
    }
    readJson.close();

    string newScan = "{\n";
    newScan += "  \"timestamp\": \"" + timestamp + "\",\n";
    newScan += "  \"target\": \"" + ip + "\",\n";
    newScan += "  \"country\": \"Poland\",\n";
    newScan += "  \"city\": \"Warsaw\",\n";
    newScan += "  \"isp\": \"EDGECAST\",\n";
    newScan += "  \"status\": \"Scanned\"\n";
    newScan += "}";
    
    string finalJson;
    if(existingContent.empty() || existingContent == "[\n]\n") {
        finalJson = "[\n" + newScan + "\n]";
    } else {
        size_t pos = existingContent.rfind("]");
        existingContent = existingContent.substr(0, pos);
        finalJson = existingContent + ",\n" + newScan + "\n]";
    }
    
    ofstream writeJson("scan_results.json");
    writeJson << finalJson;
    writeJson.close();

    pclose(pipe);
    log << "Status: Pending" << endl;
    log.close();
    system("pause");
    return 0;
}