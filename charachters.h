#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Being{
public:
    Being(){
        this->life = rand() % 10 + 1; // 0-10 Always specified
        this->strength = rand() % 10 + 1; // 0-10 Always specified
        this->intelligence = rand() % 10 + 1; // 0-10 Always specified
    }

    Being(map<string, string> init) {
        this->life = get_num(init["life"]); // 0-10 Always specified
        this->strength = get_num(init["strength"]); // 0-10 Always specified
        this->intelligence = get_num(init["intelligence"]); // 0-10 Always specified
    }

    virtual void print(){
        cout << "life: " << life << ", " << "str: " << strength << ", " << "int: " << intelligence;
    }

    string getType() {return type;}

    int get_num(string str) {
        int upper, lower, i;
        if (strcmp(str.c_str(), "unnatural") == 0) {return 1;}
        else if (strcmp(str.c_str(), "natural") == 0) {return 0;}
        if (str.length() < 2) {
            return stoi(str);
        }
        for (i = 0; i < str.length(); i++) {
            if (strcmp(str.substr(i, 1).c_str(), "-") == 0) {break;}
        }
        upper = stoi(str.substr(i+1,str.length()));
        lower = stoi(str.substr(0,i));
        return lower + rand() % (upper-lower);
    }
    
protected:
    int life;
    int strength;
    int intelligence;
    string type;
};

class Person : public Being{
public:
    Person() : Being::Being(){
        this->fear = rand() % 10;
        this->gender = "male";
        this->type = "person";
        this->terror = rand() % 4;
    };
    Person(map<string, string> init) : Being::Being(init) {
        this->fear = rand() % 10;
        this->gender = "male";
        this->type = "person";
        this->terror = rand() % 4;
    };
    void print() {
        Being::print();
        cout << ", " << "fear: " << fear << ", " << "gender: " << gender << ", " << "terr: " <<  terror;
    }
protected:
    int fear;
    string gender;
    int terror;
};

// class Investigator : public Person{
// public:
//     Investigator() : Person::Person(){
//         this->terror = rand() % 3;
//     };
//     void print() {
//         Person::print();
//         cout << ", " << "terr: " <<  terror;
//     }
// protected:
//     int terror;
// };

class Creature : public Being{
public:
    Creature() : Being::Being(){
        this->disquiet = rand() % 10; // Always specified
        this->unnatural = false; // Always specified
        this->type = "creature";
    }
    Creature(map<string, string> init) : Being::Being(init){
        // this->life = get_num(init["life"]); // 0-10 Always specified
        // this->strength = get_num(init["strength"]); // 0-10 Always specified
        // this->intelligence = get_num(init["intelligence"]); // 0-10 Always specified
        this->disquiet = get_num(init["disquiet"]); // Always specified
        this->unnatural = get_num(init["nature"]); // Always specified
        this->type = "creature";

    }
    void print() {
        Being::print();
        cout << ", " << "disq: " <<  disquiet << ", " << "unnatural: " <<  (unnatural ? "true" : "false");
    }
protected:
    int disquiet;
    bool unnatural;
};

class EldrichHorror : public Creature{
public:
    EldrichHorror() : Creature::Creature(){
        this->traumatism = rand() % 10; // Always specified
        this->disquiet = 10; // Hard
        this->unnatural = true; // Hard
    }
    EldrichHorror(map<string, string> init){
        this->life = get_num(init["life"]); // 0-10 Always specified
        this->strength = get_num(init["strength"]); // 0-10 Always specified
        this->intelligence = get_num(init["intelligence"]); // 0-10 Always specified
        this->traumatism = get_num(init["traumatism"]); // Always specified
        this->disquiet = 10; // Hard
        this->unnatural = true; // Hard

    }
protected:
    int traumatism;
};

class Characters {
public:
    void add_character(int choice, map<string, string> init, string name) {
        switch (choice) {
            case 0:
                characters[name] = new Person(init);
                break;
            case 1:
                characters[name] = new Creature(init);
                break;
            case 2:
                characters[name] = new EldrichHorror(init);
                break;
        }
    }
    void print() {
        for(const auto& elem : characters){
                cout << elem.first << endl << "\t";
                elem.second->print();
                cout << endl;
        }
    }
private:
    map<string, Being*> characters;
};

// class Individual {
// public:
//     Individual(Being* being, string name) {
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
//     string name;
// };