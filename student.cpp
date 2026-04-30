#include <iostream>
using namespace std;

class Student {
private:
    string name;
    string gender;
    float score;
    int readingLevel;

public:
    Student(string n, string g, float s, int r) {
        name = n;
        gender = g;
        score = s;
        readingLevel = r;
    }    // constructor and methods go here

    string getName() { return name; }
    string getGender() { return gender; }
    float getScore() { return score; }
    int getReadingLevel() { return readingLevel; }
};

int main() {
    Student s1("Ahmed", "Male", 85.5, 7);
    cout << s1.getName() << endl;
    cout << s1.getScore() << endl;
    system("pause");
    return 0;
}