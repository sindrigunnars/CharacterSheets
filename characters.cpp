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