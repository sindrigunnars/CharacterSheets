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
    Being(){
        this->life = rand() % 10 + 1; // 0-10 Always specified
        this->strength = rand() % 10 + 1; // 0-10 Always specified
        this->intelligence = rand() % 10 + 1; // 0-10 Always specified
    }

    Being(map<string, string> init, string role) {
        this->life = get_num(init["life"]); // 0-10 Always specified
        this->strength = get_num(init["strength"]); // 0-10 Always specified
        this->intelligence = get_num(init["intelligence"]); // 0-10 Always specified
        this->role = role;
    }

    virtual void print(){
        cout << "life: " << life << ", " << "str: " << strength << ", " << "int: " << intelligence;
    }

    virtual void changeVal(string attr, int val) {
        if (strcmp(attr.c_str(), "life") == 0) this->life = val;
        if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
        if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
    }
    virtual void changeGender(string gender){};

    string getType() {return type;}
    string getRole() {return role;}

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
    string role;
};

class Person : public Being{
public:
    Person() : Being::Being(){
        this->fear = rand() % 10;
        this->gender = "male";
        this->type = "person";
        this->terror = rand() % 4;
    };
    Person(map<string, string> init, string role) : Being::Being(init, role) {
        this->fear = rand() % 10;
        this->gender = "male";
        this->type = "person";
        this->terror = rand() % 4;
    };
    void print() {
        Being::print();
        cout << ", " << "fear: " << fear << ", " << "gender: " << gender << ", " << "terr: " <<  terror;
    }
    void changeVal(string attr, int val){
        if (strcmp(attr.c_str(), "life") == 0) this->life = val;
        if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
        if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
        if (strcmp(attr.c_str(), "terror") == 0) this->terror = val;
        if (strcmp(attr.c_str(), "fear") == 0) this->fear = val;
    }

    void changeGender(string gender) {
        this->gender = gender;
    }
protected:
    int fear;
    string gender;
    int terror;
};

class Creature : public Being{
public:
    Creature() : Being::Being(){
        this->disquiet = rand() % 10; // Always specified
        this->unnatural = false; // Always specified
        this->type = "creature";
    }
    Creature(map<string, string> init, string role) : Being::Being(init, role){
        this->disquiet = get_num(init["disquiet"]); // Always specified
        this->unnatural = get_num(init["nature"]); // Always specified
        this->type = "creature";

    }
    void print() {
        Being::print();
        cout << ", " << "disq: " <<  disquiet << ", " <<  (unnatural ? "unnatural" : "natural");
    }
    void changeVal(string attr, int val){
        if (strcmp(attr.c_str(), "life") == 0) this->life = val;
        if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
        if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
        if (strcmp(attr.c_str(), "disquiet") == 0) this->disquiet = val;
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
    EldrichHorror(map<string, string> init, string role){
        this->life = get_num(init["life"]); // 0-10 Always specified
        this->strength = get_num(init["strength"]); // 0-10 Always specified
        this->intelligence = get_num(init["intelligence"]); // 0-10 Always specified
        this->traumatism = get_num(init["traumatism"]); // Always specified
        this->disquiet = 10; // Hard
        this->unnatural = true; // Hard
        this->role = role;

    }
    void print() {
        Creature::print();
        cout << ", " << "traumatism: " << traumatism;
        this->type = "eldritch";
    }
    void changeVal(string attr, int val){
        if (strcmp(attr.c_str(), "life") == 0) this->life = val;
        if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
        if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
        if (strcmp(attr.c_str(), "traumatism") == 0) this->traumatism = val;
    }
protected:
    int traumatism;
};

class Roles {
public:
    Roles() {
        fstream fin("roles.txt");
        Choice choice;
        string primary, secondary, role, type;

        fin >> role >> type;
        roles[role]["type"] = type;
        while (fin >> primary) {
            fin >> secondary;
            if (strcmp(primary.c_str(), "/") == 0) {
                primary = secondary;
                fin >> secondary;
                if (fin.eof()) {break;}
                role = primary;
                type = secondary;
                roles[role]["type"] = type;
            } else if(strcmp(primary.c_str(), "unnatural") == 0 || strcmp(primary.c_str(), "natural") == 0) {
                roles[role]["nature"] = primary;
                primary = secondary;
                fin >> secondary;
                roles[role][primary] = secondary;
            } else {
                roles[role][primary] = secondary;
            }
        }
        fin.close();
    }
    void add_character(string role) {
        string name, attr;
        Choice choice;
        int count;
        if (strcmp(roles[role]["type"].c_str(), "Person") == 0) {choice = person;}
        if (strcmp(roles[role]["type"].c_str(), "Creature") == 0) {choice = creature;}
        if (strcmp(roles[role]["type"].c_str(), "Eldritch") == 0) {choice = eldrich;}
        switch (choice) {
            case 0:
                cout << "What is this persons name? ";
                cin >> name;
                characters[name] = new Person(roles[role], role);
                cout << "What is this persons gender? ";
                cin >> attr;
                characters[name]->changeGender(attr);
                break;
            case 1:
                count = 0;
                for (const auto& elem : characters) {
                    if (strcmp(elem.second->getRole().c_str(), role.c_str()) == 0) count++;
                }
                name += role + to_string(count);
                characters[name] = new Creature(roles[role], role);
                cout << "Do you want to edit the name (y/n)? ";
                cin >> attr;
                if (strcmp(attr.c_str(), "y") == 0) {
                    characters.erase(name);
                    cout << "Please enter new name: ";
                    cin >> name;
                    characters.erase(name);
                    characters[name] = new Creature(roles[role], role);
                }
                break;
            case 2:
                count = 0;
                for (const auto& elem : characters) {
                    if (strcmp(elem.second->getRole().c_str(), role.c_str()) == 0) count++;
                }
                name += role + to_string(count);
                characters[name] = new EldrichHorror(roles[role], role);
                break;
        }
        cout << "Do you want to edit any attributes (y/n)? ";
        cin >> attr;
        if (strcmp(attr.c_str(), "y") == 0) {
            int value;
            while (true) {
                cout << name << ": \t";
                characters[name]->print();
                cout << endl;
                cout << "Type the lower case attribute (press q to stop) ";
                cin >> attr;
                if (strcmp(attr.c_str(), "q") == 0) {break;}
                cout << "What value do you want to assign? ";
                cin >> value;
                characters[name]->changeVal(attr, value);
            }
        }
        characters[name]->print();
        cout << endl;
    }
    void add_role() {
        fstream fout("roles.txt", ios::app);
        string name, type, value, write;
        map<string, string> new_role;
        cout << "What is the name of the role (capitalized)? ";
        cin >> name;
        cout << "What is the type (capitalized (Person/Creature/Eldritch))? ";
        cin >> type;
        new_role["type"] = type;
        write += "\n" + name + " " + type;
        cout << "What is the life value (seperated by - if range)? ";
        cin >> value;
        new_role["life"] = value;
        write += "\nlife " + value;
        cout << "What is the strength value (seperated by - if range)? ";
        cin >> value;
        new_role["strength"] = value;
        write += "\nstrength " + value;
        cout << "What is the intelligence value (seperated by - if range)? ";
        cin >> value;
        new_role["intelligence"] = value;
        write += "\nintelligence " + value;
        if (strcmp(type.c_str(), "Creature") == 0) {
            cout << "Is the creature natural(natural/unnatural)? ";
            cin >> value;
            new_role["nature"] = value;
            write += "\n" + value;
            cout << "What is the disquiet value (seperated by - if range)? ";
            cin >> value;
            new_role["disquiet"] = value;
            write += "\ndisquiet " + value;
        }
        if (strcmp(type.c_str(), "Eldritch") == 0) {
            cout << "What is the traumatism value (seperated by - if range)? ";
            cin >> value;
            new_role["traumatism"] = value;
            write += "\traumatism " + value;
        }
        roles[name] = new_role;
        fout << write << "\n/";
    }
    void print() {
        for(const auto& elem : roles){
                cout <<  "\t" << elem.first << endl;
        }
    }
    void print_role_detailed(string name) {
        cout << name << ": " << endl;
        for(const auto& elem : roles){
            if (strcmp(elem.first.c_str(), name.c_str()) == 0) {
                for (const auto& elems : elem.second) {
                    if (strcmp(elems.first.c_str(), "type") != 0) {
                        cout << "\t" << elems.first << ": " << elems.second << endl;
                    }
                }
            }
        }
    }
    void print_roster() {
        for(const auto& elem : characters) {
            cout << elem.first << ":\n\t";
            elem.second->print();
            cout << endl;
        }
    }
private:
    map<string, Being*> characters;
    map<string, map<string, string> > roles;
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