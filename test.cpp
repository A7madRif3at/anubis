#include <bits/stdc++.h>
using namespace std;

string detectService(string ip, int port){
    string cmd = "curl -I -- connect_timeout 1 " + ip + ":" + to_string(port) + " 2>&1 | findstr server";
    
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
    cout << "Target IP: " << ip << endl;

    time_t now= time(0);
    string timestamp = ctime(&now);
    timestamp.pop_back();

    string command = "curl -s http://ip-api.com/line/" + ip + "?fields=country,city,isp";
    system(command.c_str());

    ofstream log("scan_log.txt");
    log << "=== Anubis Scan ===" << endl;
    log << "Target: " << ip << endl;
    log << "Time: " << timestamp << endl;
    log << "GeoIP Lookup: " << endl;
    cout << "Scan logged for: " << ip <<endl;
    
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
                string service = detectService(ip, port);
            
            cout << "port" << port << " open - " << endl;
            log << "Port " << port << " open - " << endl;
            }
         
        }

        ofstream csv("scan_results.json", ios::app);
        csv << timestamp << "," << ip << ",Poland,Warsaw,EDGECAST,Scanned" << endl;
        csv.close();
        ofstream jsonFile("scan_results.json", ios::app);
        jsonFile << "{" << endl;
        jsonFile << " \"timestamp\": \"" << timestamp << "\"," << endl;
        jsonFile << " \"target\": \"" << ip << "\"," << endl;
        jsonFile << " \"country\": \"Poland\"," << endl;
        jsonFile << " \"city\": \"Warsaw\"," << endl;
        jsonFile << " \"isp\": \"EDGECAST\"," << endl;
        jsonFile << " \"status\": \"Scanned\"" << endl;
        jsonFile << "}" << endl;
        jsonFile.close();

        ifstream readJson("scan_results.json");
        string existingContent= "";
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
        if(existingContent.empty()) {
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
        log << "Status: Scan completed for " << ip << endl;
        log.close();
        system("pause");
        return 0;
}