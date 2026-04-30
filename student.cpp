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
    void setScore(float s) { score = s; }
    void setReadingLevel(int r) { readingLevel = r; }
};

int main() {
    Student s1("Ahmed", "Male", 85.5, 7);
    cout << s1.getScore() << endl;  // before
    s1.setScore(95.0);
    cout << s1.getName() << endl;
    cout << s1.getScore() << endl;  // after
    system("pause");
    return 0;
}