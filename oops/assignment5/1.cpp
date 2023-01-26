/*
    There are number of students. For every student roll (unique), name is to be
    stored. For each subject, subject code and name is to be stored. A student can
    opt for number of subjects. System should be able to maintain student list,
    subject list and will be able to answer: i) which student has selected which
    subjects and ii) for a subjects who are the students.
    Design the classes and implement. For list consider memory data structure.
*/

#include <iostream>
#include <string.h>
using namespace std;

class STUDENT;
class STUDENT_SUB;
class SUBJECT;
class SUBJECT_STUD;
class SYSTEM;
class MANAGER;

class STUDENT
{
    char name[31];
    int roll; 
    public:
    void setStudData(int r, char n[31])
    {
        roll = r;
        strcpy(name, n);
    }

    int getRoll()
    {
        return roll;
    }

    char *getName()
    {
        return name;
    }

    void display()
    {
        cout << "Roll: " << roll << '\t' << "Name: " << name << endl;
    }
};

class SUBJECT
{
    int code;
    char name[31];
    public: 
    void setSubData(int c, char n[])
    {
        code = c;
        strcpy(name, n);
    }

    int getCode()
    {
        return code;
    }

    char *getName()
    {
        return name;
    }

    void display()
    {
        cout << "Code: " << code << '\t' << "Name: " << name << endl;
    }
}; 

class STUDENT_SUB : public STUDENT
{
    SUBJECT sub[5];
    int count;
    public:
    void setData(int r, char stud_n[])
    {
        count = 0;
        setStudData(r, stud_n);    
    }

    bool addSub(int c, char n[])
    {
        for (int i = 0; i < count; i++)
        {
            if (c == sub[i].getCode())
            {
                cout << "Student already studies the subject.\n";
                return 0;
            }
        }
        sub[count++].setSubData(c, n);
        return 1;
    }

    void showSub()
    {
        cout << "NAME: " << getName() << "\tRoll: " << getRoll() << endl;
        if (!count)
        {
            cout << "The student has not selected any subject yet.\n";
            return;
        }
        cout << "The subjects selected by the student are: " << endl;
        for (int i = 0; i < count; i++)
        {
            cout << i + 1 << ") "; 
            sub[i].display();
        }
    }
};

class SUBJECT_STUD : public SUBJECT
{
    STUDENT stud[50]; 
    int count;
    public:
    void setData(int c, char n[])
    {
        count = 0;
        setSubData(c, n);
    }

    void addStud(int r, char stud_n[])
    {
        for (int i = 0; i < count; i++)
        {
            if (r == stud[i].getRoll())
            {
                cout << "Student already studies the subject.\n";
                return;
            }
        }
        stud[count++].setStudData(r, stud_n);
    }

    void showStud()
    {
        cout << "NAME: " << getName() << "\tCODE: " << getCode() << endl;
        if (!count)
        {
            cout << "There are no students who have selected this subject yet.\n";
            return;
        }
        cout << "The students studying the subject are: " << endl;
        for (int i = 0; i < count; i++)
        {
            cout << i + 1 << ") "; 
            stud[i].display();
        }
    }
};

class SYSTEM
{
    STUDENT_SUB stud_list[1000];
    static int stud_count;
    SUBJECT_STUD sub_list[30];
    static int sub_count;
    public:
    void allocateSub(int r, int c)
    {
        int stud_ind, sub_ind;
        for (stud_ind = 0; stud_ind < stud_count; stud_ind++)
        {
            if (stud_list[stud_ind].getRoll() == r)
            {
                break;
            }
        }

        if (stud_ind == stud_count) 
        {
            cout << "ERROR: Roll Number not found.\n";
            return;
        }

        for (sub_ind = 0; sub_ind < sub_count; sub_ind++)
        {
            if (sub_list[sub_ind].getCode() == c)
            {
                break;
            }
        }

        if (sub_ind == sub_count)
        {
            cout << "ERROR: Subject Code not found.\n";
            return;
        }

        if (!stud_list[stud_ind].addSub(c, sub_list[sub_ind].getName())) return;
        sub_list[sub_ind].addStud(r, stud_list[stud_ind].getName());
    }

    void addSub(int c, char n[])
    {
        for (int i = 0; i < sub_count; i++)
        {
            if (sub_list[i].getCode() == c)
            {
                cout << "Subject with subject code exists already.\n";
                return;
            }
        }
        sub_list[sub_count++].setData(c, n);
    }

    void addStud(int r, char n[])
    {
        for (int i = 0; i < stud_count; i++)
        {
            if (stud_list[i].getRoll() == r)
            {
                cout << "Student with given roll number exists already.\n";
                return;
            }
        }
        stud_list[stud_count++].setData(r, n);
    }

    void showSubs(int roll)
    {
        for (int i = 0; i < stud_count; i++)
        {
            if (stud_list[i].getRoll() == roll)
            {
                stud_list[i].showSub();
                return;
            }
        }
        cout << "ERROR: roll number not found.\n";
        return;
    }

    void showStuds(int code)
    {
        for (int i = 0; i < sub_count; i++)
        {
            if (sub_list[i].getCode() == code)
            {
                return sub_list[i].showStud();
            }
        }
        cout << "ERROR: subject code not found.\n";
    }
};

class MANAGER
{
    SYSTEM s;
    public:
    void addStudent()
    {
        int r;
        char n[31];
        cout << "Enter Roll Number: ";
        cin >> r;
        cout << "Enter Student Name: ";
        cin >> n;
        s.addStud(r, n);
    }

    void addSubject()
    {
        int c;
        char n[31];
        cout << "Enter Subject Code: ";
        cin >> c;
        cout << "Enter Subject Name: ";
        cin >> n;
        s.addSub(c, n);
    }

    void allocateSubject()
    {
        int r, c;
        cout << "Enter Student's Roll Number: ";
        cin >> r;
        cout << "Enter Subject Code Number: ";
        cin >> c;
        s.allocateSub(r, c);
    }

    void showStudents()
    {
        int c;
        cout << "Enter Subject Code Number: ";
        cin >> c;
        s.showStuds(c);
    }

    void showSubjects()
    {
        int r;
        cout << "Enter Student's Roll Number: ";
        cin >> r;
        s.showSubs(r);
    }
};

int SYSTEM :: stud_count = 0;
int SYSTEM :: sub_count = 0;

int main()
{
    MANAGER m;
    while(1)
    {
        int c;
        cout << "Enter: " << endl;
        cout << "1) 1 to add a student to the system." << endl;
        cout << "2) 2 to add a subject to the system." << endl;
        cout << "3) 3 to allocate a subject to a student." << endl;
        cout << "4) 4 to show the subjects allocated to a student." << endl;
        cout << "5) 5 to show the students studying a subject." << endl;
        cout << "6) 6 to exit." << endl;
        cin >> c;
        if (c == 6) 
        {
            break;
        }
        switch(c)
        {
            case 1: m.addStudent();         break;
            case 2: m.addSubject();         break;
            case 3: m.allocateSubject();    break;
            case 4: m.showSubjects();       break;
            case 5: m.showStudents();       break;
            default:                        break;
        }
    }
    return 0;
}