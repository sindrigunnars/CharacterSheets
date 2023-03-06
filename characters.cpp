#include <iostream>
#include "characters.h"
#include <cstring>
#include <fstream>
#include <map>
using namespace std;

Being::Being(){
    this->life = rand() % 10 + 1; // 0-10 Always specified
    this->strength = rand() % 10 + 1; // 0-10 Always specified
    this->intelligence = rand() % 10 + 1; // 0-10 Always specified
}

Being::Being(map<std::string, std::string> init, std::string role) {
    this->life = get_num(init["life"]); // 0-10 Always specified
    this->strength = get_num(init["strength"]); // 0-10 Always specified
    this->intelligence = get_num(init["intelligence"]); // 0-10 Always specified
    this->role = role;
}

std::string Being::get_string() {
    std::string ret;
    ret += "\tLife: " + to_string(life);
    ret += "\n\tStrength: " + to_string(strength);
    ret += "\n\tIntelligence: " + to_string(intelligence);
    return ret;
}

void Being::changeVal(std::string attr, int val) {
    if (strcmp(attr.c_str(), "life") == 0) this->life = val;
    if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
    if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
}
void Being::changeGender(std::string gender){};

std::string Being::getType() {return type;}
std::string Being::getRole() {return role;}

int Being::get_num(std::string str) {
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

Person::Person() : Being::Being(){
    this->fear = rand() % 10;
    this->gender = "male";
    this->type = "person";
    this->terror = rand() % 4;
}

Person::Person(map<std::string, std::string> init, std::string role) : Being::Being(init, role) {
    this->fear = rand() % 10;
    this->gender = "male";
    this->type = "person";
    this->terror = rand() % 4;
}

std::string Person::get_string() {
    std::string ret = Being::get_string();
    ret += "\n\tFear: " + to_string(fear);
    ret += "\n\tTerror: " + to_string(terror);
    ret += "\n\tGender: " + gender;
    return ret;
}

void Person::changeVal(std::string attr, int val){
    if (strcmp(attr.c_str(), "life") == 0) this->life = val;
    if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
    if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
    if (strcmp(attr.c_str(), "terror") == 0) this->terror = val;
    if (strcmp(attr.c_str(), "fear") == 0) this->fear = val;
}

void Person::changeGender(std::string gender) {
    this->gender = gender;
}

Creature::Creature() : Being::Being(){
    this->disquiet = rand() % 10; // Always specified
    this->unnatural = false; // Always specified
    this->type = "creature";
}
Creature::Creature(map<std::string, std::string> init, std::string role) : Being::Being(init, role){
    this->disquiet = get_num(init["disquiet"]); // Always specified
    this->unnatural = get_num(init["nature"]); // Always specified
    this->type = "creature";

}

std::string Creature::get_string() {
    std::string ret = Being::get_string();
    ret += "\n\tDisquiet: " + to_string(disquiet);
    std::string genderstr = unnatural ? "unnatural" : "natural";
    ret += "\n\tNature: " + genderstr;
    return ret;
}

void Creature::changeVal(std::string attr, int val){
    if (strcmp(attr.c_str(), "life") == 0) this->life = val;
    if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
    if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
    if (strcmp(attr.c_str(), "disquiet") == 0) this->disquiet = val;
}

EldrichHorror::EldrichHorror() : Creature::Creature(){
    this->traumatism = rand() % 10; // Always specified
    this->disquiet = 10; // Hard
    this->unnatural = true; // Hard
}
EldrichHorror::EldrichHorror(map<std::string, std::string> init, std::string role) {
    this->life = get_num(init["life"]); // 0-10 Always specified
    this->strength = get_num(init["strength"]); // 0-10 Always specified
    this->intelligence = get_num(init["intelligence"]); // 0-10 Always specified
    this->traumatism = get_num(init["traumatism"]); // Always specified
    this->disquiet = 10; // Hard
    this->unnatural = true; // Hard
    this->role = role;

}

std::string EldrichHorror::get_string() {
    std::string ret = Being::get_string();
    ret += "\n\tDisquiet: " + to_string(disquiet);
    ret += "\n\tTraumatism: " + to_string(traumatism);
    return ret;
}

void EldrichHorror::changeVal(std::string attr, int val){
    if (strcmp(attr.c_str(), "life") == 0) this->life = val;
    if (strcmp(attr.c_str(), "strength") == 0) this->strength = val;
    if (strcmp(attr.c_str(), "intelligence") == 0) this->intelligence = val;
    if (strcmp(attr.c_str(), "traumatism") == 0) this->traumatism = val;
}

Roles::Roles() {
    fstream fin("roles.txt");
    Choice choice;
    std::string primary, secondary, role, type;

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
void Roles::add_character(std::string role) {
    std::string name, attr;
    Choice choice;
    int count;
    if (strcmp(roles[role]["type"].c_str(), "Person") == 0) {choice = person;}
    if (strcmp(roles[role]["type"].c_str(), "Creature") == 0) {choice = creature;}
    if (strcmp(roles[role]["type"].c_str(), "Eldritch") == 0) {choice = eldrich;}
    switch (choice) {
        case person:
            cout << "What is this persons name(No spaces)? ";
            cin >> name;
            characters[name] = new Person(roles[role], role);
            cout << "What is this persons gender? ";
            cin >> attr;
            characters[name]->changeGender(attr);
            break;
        case creature:
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
        case eldrich:
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
            cout << name << ": \n" << characters[name]->get_string() << endl;
            cout << "Type the lower case attribute (press q to stop, no spaces) ";
            cin >> attr;
            if (strcmp(attr.c_str(), "q") == 0) {break;}
            cout << "What value do you want to assign (single number between 1-10)? ";
            cin >> value;
            characters[name]->changeVal(attr, value);
        }
    }
    cout << name << ":\n" << characters[name]->get_string() << endl;
}
void Roles::add_role() {
    fstream fout("roles.txt", ios::app);
    std::string name, type, value, write;
    map<std::string, std::string> new_role;
    cout << "What is the name of the role (capitalized, no spaces)? ";
    cin >> name;
    cout << "What is the type (capitalized (Person/Creature/Eldritch))? ";
    cin >> type;
    new_role["type"] = type;
    write += name + " " + type;
    cout << "What is the life value (seperated by - if range, available range is 0-10)? ";
    cin >> value;
    new_role["life"] = value;
    write += "\nlife " + value;
    cout << "What is the strength value (seperated by - if range, available range is 0-10)? ";
    cin >> value;
    new_role["strength"] = value;
    write += "\nstrength " + value;
    cout << "What is the intelligence value (seperated by - if range, available range is 0-10)? ";
    cin >> value;
    new_role["intelligence"] = value;
    write += "\nintelligence " + value;
    if (strcmp(type.c_str(), "Creature") == 0) {
        cout << "Is the creature natural(natural/unnatural)? ";
        cin >> value;
        new_role["nature"] = value;
        write += "\n" + value;
        cout << "What is the disquiet value (seperated by - if range, available range is 0-10)? ";
        cin >> value;
        new_role["disquiet"] = value;
        write += "\ndisquiet " + value;
    }
    if (strcmp(type.c_str(), "Eldritch") == 0) {
        cout << "What is the traumatism value (seperated by - if range, available range is 0-10)? ";
        cin >> value;
        new_role["traumatism"] = value;
        write += "\traumatism " + value;
    }
    roles[name] = new_role;
    fout << write << "\n/\n";
}
void Roles::deleteRole(std::string name) {
        fstream temp("temp.txt", ios::out), fin("roles.txt");
        std::string line, role;
        while (getline(fin, line)) {
            role = line.substr(0, line.find(' '));
            if (strcmp(role.c_str(), name.c_str()) == 0) {
                while (strcmp(role.c_str(), "/") != 0) {
                    getline(fin, line);
                    role = line.substr(0, line.find(' '));
                }
                getline(fin, line);
            }
            if (fin.eof()) break;
            temp << line << endl;
        }
        fin.close();
        temp.close();
        remove("roles.txt");
        rename("temp.txt", "roles.txt");
        roles.erase(name);
}

void Roles::print() {
    for(const auto& elem : roles){
            cout <<  "\t" << elem.first << " - " << elem.second.at("type") << endl;
    }
}
void Roles::print_role_detailed(std::string name) {
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
void Roles::print_roster() {
    for(const auto& elem : characters) {
        cout << elem.first << " " << elem.second->getRole() << ":\n";
        cout << elem.second->get_string() << endl;
    }
}

void Roles::print_roster_to_file() {
    fstream fout("roster.txt", ios::out);
    for(const auto& elem : characters) {
        std::string printstr = elem.second->get_string();
        fout << elem.first << " " << elem.second->getRole() << ":" << endl << printstr << endl;
    }
    fout.close();
}