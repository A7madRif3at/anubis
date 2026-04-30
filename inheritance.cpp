#include <iostream>
using namespace std;

class Person {
    protected:
        string name;
        string gender;
public:
    Person(string n, string g) {
        name = n;  
        gender = g;
    }
    string getName() { return name; }
    string getGender() { return gender; }
};

class Student : public Person {
private:
    float score;
public:
    Student(string n, string g, float s) : Person(n, g){
    score = s;
    }
    float getScore() { return score; }
};

class Teacher : public Person {
    private:
        string subject;
    public:
        Teacher(string n, string g, string sub) : Person(n, g){
            subject = sub;
        }
        string getSubject() {return subject; }

    };
    
    int main() {
    Student s1("Ahmed", "Male", 85.5);
    Teacher t1("Ahmed", "Male", "Math");
    cout << s1.getName() << " - " << s1.getScore() << endl;
    cout << t1.getName() << " - " << t1.getSubject() << endl;
    system("pause");
    return 0;
}