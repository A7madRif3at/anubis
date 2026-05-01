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
    virtual void introduce() {
    cout << "I am a person, my name is " << name << endl;
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
    void introduce() {
    cout << "I am a student, my name is " << name << " score: " << score << endl;
 }
};

class Teacher : public Person {
    private:
        string subject;
    public:
        Teacher(string n, string g, string sub) : Person(n, g){
            subject = sub;
        }

        string getSubject() {return subject; }
        void introduce() {
            cout << "I am a teacher, my name is " << name << " I teach: " << subject << endl;
        }
        

    };
    
    int main() {
    Student s1("Ahmed", "Male", 85.5);
    Teacher t1("Ahmed", "Male", "Math");
    s1.introduce();
    t1.introduce();
    cout << s1.getName() << " - " << s1.getScore() << endl;
    cout << t1.getName() << " - " << t1.getSubject() << endl;
    system("pause");
    return 0;
}