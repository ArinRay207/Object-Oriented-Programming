/*
    Each cricketer has name, date of birth and matches played. Cricketer may be a
    bowler or batsman. For a bowler, number of wickets taken, average economy is
    stored. For a batsman, total runs scored, average score is stored. A double
    wicket pair is formed taking a bowler and a batsman. An all-rounder is both a
    bowler and batsman. Support must be there to show the details of a cricketer,
    bowler, batsmen, all-rounder and the pair.
    Design the classes and implement.
*/

#include <iostream>
#include <string.h>
using namespace std;

class CRICKETER;
class BOWLER;
class BATSMAN;
class DOUBLE_WICKET_PAIR;
class ALL_ROUNDER;

class CRICKETER
{
    char name[31];
    char dob[11];
    int matches;

    public:
    // Setters: 
    void setCricketerData(char name[], char dob[], int matches)
    {
        strcpy(this->name, name);
        strcpy(this->dob, dob);
        this->matches = matches;
    }

    // Display:
    void displayCricketer()
    {
        cout << "Name:\t\t\t" << name << endl;
        cout << "DOB:\t\t\t" << dob << endl;
        cout << "Number of matches:\t" << matches << endl;  
    }
};

class BOWLER : virtual public CRICKETER
{
    int wickets;
    float average_economy;

    public: 
    // Setters:
    void setBowlerData(int wickets, float average_economy)
    {
        this->wickets = wickets;
        this->average_economy = average_economy;
    }

    void setData(char name[], char dob[], int matches, int wickets, float average_economy)
    {
        setCricketerData(name, dob, matches);
        setBowlerData(wickets, average_economy);
    }

    // Display
    void displayBowler()
    {
        cout << "Wickets:\t\t" << wickets << endl;
        cout << "Average Economy:\t" << average_economy << endl;
    }

    void display()
    {
        displayCricketer();
        displayBowler();
    }
};

class BATSMAN : virtual public CRICKETER
{
    int runs;
    float average_score;

    public: 
    // Constructor
    void setBatsmanData(int runs, float average_score)
    {
        this->runs = runs;
        this->average_score = average_score;
    }

    void setData(char name[], char dob[], int matches, int runs, float average_score)
    {
        setCricketerData(name, dob, matches);
        setBatsmanData(runs, average_score);
    }

    // Display:
    void displayBatsman()
    {
        cout << "Runs:\t\t\t" << runs << endl;
        cout << "Average Score:\t\t" << average_score << endl;
    }
        
    void display()
    {
        displayCricketer();
        displayBatsman();
    }
};

class DOUBLE_WICKET_PAIR
{
    BATSMAN bats;
    BOWLER bowl;

    public: 
    // Setters:
    void setDoubleWicketPairData(char batsName[], char batsDob[], int batsMatches, int runs, float average_score, char bowlName[], char bowlDob[], int bowlMatches, int wickets, float average_economy)
    {
        bats.setCricketerData(batsName, batsDob, batsMatches);
        bats.setBatsmanData(runs, average_score);
        bowl.setCricketerData(bowlName, bowlDob, bowlMatches);
        bowl.setBowlerData(wickets, average_economy);
    }

    // Display:
    void displayDWP()
    {
        cout << "BATSMAN: " << endl;
        cout << "======== " << endl;
        bats.display();
        cout << endl;
        cout << "BOWLER: " << endl; 
        cout << "======= " << endl; 
        bowl.display();
    }
};

class ALL_ROUNDER : public BATSMAN, public BOWLER
{
    public:
    // Setters: 
    void setAllRounderData(char name[], char dob[], int matches, int runs, float average_score, int wickets, float average_economy)
    {
        setCricketerData(name, dob, matches);
        setBatsmanData(runs, average_score);
        setBowlerData(wickets, average_economy);
    }

    // Display:
    void displayAllRounder()
    {
        displayCricketer();
        displayBatsman();
        displayBowler();
    }
};

int main()
{
    CRICKETER p1;
    BATSMAN p2;
    BOWLER p3;
    ALL_ROUNDER p4;
    DOUBLE_WICKET_PAIR p5;
    char name[31];
    char dob[11];
    int matches;
    cout << "CRICKETER:" << endl;
    cout << "==========" << endl;
    cout << "Enter Name: " ;
    cin >> name; 
    cout << "Enter Date Of Birth: ";
    cin >> dob;
    cout << "Enter Number of Matches played: ";
    cin >> matches;
    p1.setCricketerData(name, dob, matches);
    cout << endl;
    cout << "DISPLAYING CRICKETER:\n";
    cout << "=====================\n";
    p1.displayCricketer();
    cout << endl;

    int runs;
    float avgs;
    cout << "BATSMAN:" << endl;
    cout << "========" << endl;
    cout << "Enter Name: " ;
    cin >> name; 
    cout << "Enter Date Of Birth: ";
    cin >> dob;
    cout << "Enter Number of Matches played: ";
    cin >> matches;
    cout << "Enter Runs: ";
    cin >> runs;
    cout << "Enter Average Score: ";
    cin >> avgs;
    p2.setData(name, dob, matches, runs, avgs);
    cout << endl;
    cout << "DISPLAYING BATSMAN:\n";
    cout << "===================\n";
    p2.display();
    cout << endl;

    int wickets;
    float avge;
    cout << "BOWLER:" << endl;
    cout << "=======" << endl;
    cout << "Enter Name: " ;
    cin >> name; 
    cout << "Enter Date Of Birth: ";
    cin >> dob;
    cout << "Enter Number of Matches played: ";
    cin >> matches;
    cout << "Enter Wickets: ";
    cin >> wickets;
    cout << "Enter Average Economy: ";
    cin >> avge;
    p3.setData(name, dob, matches, wickets, avge);
    cout << endl;
    cout << "DISPLAYING BOWLER:\n";
    cout << "==================\n";
    p3.display();
    cout << endl;

    cout << "ALL ROUNDER:" << endl;
    cout << "============" << endl;
    cout << "Enter Name: " ;
    cin >> name; 
    cout << "Enter Date Of Birth: ";
    cin >> dob;
    cout << "Enter Number of Matches played: ";
    cin >> matches;
    cout << "Enter Runs: ";
    cin >> runs;
    cout << "Enter Average Score: ";
    cin >> avgs;
    cout << "Enter Wickets: ";
    cin >> wickets;
    cout << "Enter Average Economy: ";
    cin >> avge;
    p4.setAllRounderData(name, dob, matches, runs, avgs, wickets, avge);
    cout << endl;
    cout << "DISPLAYING ALL ROUNDER:\n";
    cout << "=======================\n";
    p4.displayAllRounder();
    cout << endl;

    char name1[31];
    char dob1[11];
    int matches1;
    cout << "DOUBLE WICKET PAIR:" << endl;
    cout << "===================" << endl;
    cout << "Enter Name of Batsman: " ;
    cin >> name; 
    cout << "Enter Date Of Birth of Batsman: ";
    cin >> dob;
    cout << "Enter Number of Matches played by Batsman: ";
    cin >> matches;
    cout << "Enter Runs scored by Batsman: ";
    cin >> runs;
    cout << "Enter Average Score of Batsman: ";
    cin >> avgs;
    cout << "Enter Name of Bowler: " ;
    cin >> name1; 
    cout << "Enter Date Of Birth of Bowler: ";
    cin >> dob1;
    cout << "Enter Number of Matches played by Bowler: ";
    cin >> matches1;
    cout << "Enter Wickets taken by Bowler: ";
    cin >> wickets;
    cout << "Enter Average Economy of Bowler: ";
    cin >> avge;
    p5.setDoubleWicketPairData(name, dob, matches, runs, avgs, name1, dob1, matches1, wickets, avge);
    cout << endl;
    cout << "DISPLAYING DOUBLE WICKET PAIR\n";
    cout << "=============================\n";
    p5.displayDWP();
    cout << endl;
} 
