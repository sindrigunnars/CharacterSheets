#include "charachters.h"
#include <map>
enum Choice {
    person,
    creature,
    eldrich
};

int main() {
    srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    fstream fin("roles.txt");
    Characters chars;
    Choice choice;

    string primary, secondary, role, type;
    map<string, map<string, string> > roles;

    fin >> role >> type;
    while (fin >> primary) {
        fin >> secondary;
        if (strcmp(primary.c_str(), "/") == 0) {
            if (strcmp(type.c_str(), "Person") == 0) {choice = person;}
            if (strcmp(type.c_str(), "Creature") == 0) {choice = creature;}
            if (strcmp(type.c_str(), "Eldritch") == 0) {choice = eldrich;}
            chars.add_character(choice, roles[role], role);
            primary = secondary;
            fin >> secondary;
            role = primary;
            type = secondary;
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
    chars.print();
    return 0;
}