#include <iostream>
#include <fstream>
#include <map>
using namespace std;

enum Choice {
    person,
    creature,
    eldrich
};

class Being{
public:
    Being();
    Being(map<std::string, std::string> init, std::string role);

    virtual void print();

    virtual void changeVal(std::string attr, int val);
    virtual void changeGender(std::string gender);

    std::string getType();
    std::string getRole();

    int get_num(std::string str);

protected:
    int life;
    int strength;
    int intelligence;
    std::string type;
    std::string role;
};

class Person : public Being{
public:
    Person();
    Person(map<std::string, std::string> init, std::string role);

    void print();
    void changeVal(std::string attr, int val);
    void changeGender(std::string gender);
protected:
    int fear;
    std::string gender;
    int terror;
};

class Creature : public Being{
public:
    Creature();
    Creature(map<std::string, std::string> init, std::string role);
    void print();
    void changeVal(std::string attr, int val);
protected:
    int disquiet;
    bool unnatural;
};

class EldrichHorror : public Creature{
public:
    EldrichHorror();
    EldrichHorror(map<std::string, std::string> init, std::string role);
    void print();
    void changeVal(std::string attr, int val);
protected:
    int traumatism;
};

class Roles {
public:
    Roles();
    void add_character(std::string role);
    void add_role();
    void print();
    void print_role_detailed(std::string name);
    void print_roster();
    void deleteRole(std::string name);
private:
    map<std::string, Being*> characters;
    map<std::string, map<std::string, std::string> > roles;
};

// class Individual {
// public:
//     Individual(Being* being, std::string name) {
//         this->being = being;
//         if (this->being->getType() == "person") {
//             cout << "What is the name: " << endl;
//             cin >> this->name;
//         } else if (this->being->getType() == "creature")
//         {
//             this->name = "Creature";
//         } else {
//             this->name = "Unknown";
//         }    
//     }
// private:
//     Being* being;
//     std::string name;
// };