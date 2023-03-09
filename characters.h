#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
using namespace std;

// enum Choice {
//     person,
//     creature,
//     eldrich
// };

class Being{
public:
    Being();
    Being(map<std::string, std::string> init, std::string role);
    virtual void changeVal(std::string attr, int val);
    virtual void changeGender(std::string gender);
    virtual std::string get_string();

    std::string getType();
    std::string getRole();
    void make_investigator();
    int get_num(std::string str);

protected:
    int life;
    int strength;
    int intelligence;
    std::string type;
    std::string role;
    bool is_investigator;
};

class Person : public Being{
public:
    Person();
    Person(map<std::string, std::string> init, std::string role);
    std::string get_string();
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
    std::string get_string();
    void changeVal(std::string attr, int val);
protected:
    int disquiet;
    bool unnatural;
};

class EldrichHorror : public Creature{
public:
    EldrichHorror();
    EldrichHorror(map<std::string, std::string> init, std::string role);
    std::string get_string();
    void changeVal(std::string attr, int val);
protected:
    int traumatism;
};

#include "roles.inl"