/* 
    Employee has unique emp-id, name, designation and basic pay. An employee is
    either a permanent one or contractual. For permanent employee salary is
    computed as basic pay+ hra (30% of basic pay) + da (80% of basic pay). For
    contractual employee it is basic pay + allowance (it is different for different
    contractual employee). An employee pointer may point to either of the two
    categories and accordingly the salary has to be created.
    Design the classes and implement. 
*/
  
using namespace std;
#include<bits/stdc++.h>

class EMPLOYEE
{
	int emp_id;
	char name[31];
	double basic_pay;
	public: 
	void set_data(int emp_id, char name[], double basic_pay)
    {
		this->emp_id = emp_id;
		strcpy(this->name, name);
		this->basic_pay = basic_pay;
	}

	virtual double cal_salary() = 0;
	
    double get_basic_pay()
    { 
        return basic_pay;
    }
};
   
   
   
class PERMANENT_EMPLOYEE : public EMPLOYEE
{
	double hra;
    double da;
    
    public:
    PERMANENT_EMPLOYEE(int emp_id, char name[], double basic_pay)
    {
        set_data(emp_id,name,basic_pay);
        hra = get_basic_pay() * 0.3;
        da = get_basic_pay() * 0.8;
    }

    double cal_salary()
    {
        return get_basic_pay() + hra + da;
    }
};

class CONTRACTUAL_EMPLOYEE:public EMPLOYEE
{
    double allowance;
    
    public:
    CONTRACTUAL_EMPLOYEE(int emp_id, char name[], double basic_pay, double money)
    {
        set_data(emp_id, name, basic_pay);
        allowance = money;
    }

    double cal_salary()
    {
        return get_basic_pay() + allowance;
    }
};

int main()
{
    EMPLOYEE* e;

    int emp_id;
    char name[11];
    double basic_pay;
    cout << endl;
    cout << "PERMANENT EMPLOYEE" << endl;
    cout << "==================" << endl;
    cout << "Enter Employee ID: ";
    cin >> emp_id;
    cout << "Enter Employee Name: ";
    cin >> name;
    cout << "Enter Basic Pay: ";
    cin >> basic_pay;
    PERMANENT_EMPLOYEE pe(emp_id, name, basic_pay);
    e = &pe;
    cout << "The calculted salary is: " << e->cal_salary() << endl << endl;

    double allowance;
    cout << "CONTRACTUAL EMPLOYEE" << endl;
    cout << "====================" << endl;
    cout << "Enter Employee ID: ";
    cin >> emp_id;
    cout << "Enter Employee Name: ";
    cin >> name;
    cout << "Enter Basic Pay: ";
    cin >> basic_pay;
    cout << "Enter Allowance: ";
    cin >> allowance;
    CONTRACTUAL_EMPLOYEE ce(emp_id, name, basic_pay, allowance);
    e = &ce;
    cout << "The calculted salary is: " << e->cal_salary() << endl << endl;
    return 0;
}