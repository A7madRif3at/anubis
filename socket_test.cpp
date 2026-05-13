#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

bool isPortOpen(string ip, int port) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Set timeout to 1 second
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

int main() {
    string ip = "8.8.8.8";
    int ports[] = {53, 80, 443, 22, 25};
    
    for(int i = 0; i < 5; i++) {
        if(isPortOpen(ip, ports[i])) {
            cout << "Port " << ports[i] << " is OPEN" << endl;
        } else {
            cout << "Port " << ports[i] << " is CLOSED" << endl;
        }
    }
    
    system("pause");
    return 0;
}