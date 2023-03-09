#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
using namespace std;

enum Choice {
    person,
    creature,
    eldrich
};

template <class T>
class Roles {
public:
    Roles() {
        fstream fin("roles.txt");
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
    void add_character(std::string role) {
        std::string name, attr;
        Choice choice;
        int count;
        for (const auto& elem : roles) {
            if (strcmp(elem.first.c_str(), role.c_str()) == 0) {
                if (strcmp(roles[role]["type"].c_str(), "Person") == 0) {choice = person;}
                if (strcmp(roles[role]["type"].c_str(), "Creature") == 0) {choice = creature;}
                if (strcmp(roles[role]["type"].c_str(), "Eldritch") == 0) {choice = eldrich;}
                switch (choice) {
                    case person:
                        cout << "What is this persons name (No spaces)? ";
                        cin >> name;
                        characters[name] = new Person(roles[role], role);
                        cout << "What is this persons gender? ";
                        cin >> attr;
                        characters[name]->changeGender(attr);
                        cout << "Is this person an investigator (y/n)? ";
                        cin >> attr;
                        if (strcmp(attr.c_str(), "y") == 0) {characters[name]->make_investigator();}
                        break;
                    case creature:
                        count = 1;
                        for (const auto& elem : characters) {
                            if (strcmp(elem.second->getRole().c_str(), role.c_str()) == 0) count++;
                        }
                        name += role + to_string(count);
                        characters[name] = new Creature(roles[role], role);
                        cout << "Do you want to edit the name (y/n)? ";
                        cin >> attr;
                        if (strcmp(attr.c_str(), "y") == 0) {
                            characters.erase(name);
                            cout << "Please enter new name (No spaces): ";
                            cin >> name;
                            characters.erase(name);
                            characters[name] = new Creature(roles[role], role);
                        }
                        break;
                    case eldrich:
                        count = 1;
                        for (const auto& elem : characters) {
                            if (strcmp(elem.second->getRole().c_str(), role.c_str()) == 0) count++;
                        }
                        name += role + to_string(count);
                        characters[name] = new EldrichHorror(roles[role], role);
                        cout << "Do you want to edit the name (y/n)? ";
                        cin >> attr;
                        if (strcmp(attr.c_str(), "y") == 0) {
                            characters.erase(name);
                            cout << "Please enter new name (No spaces): ";
                            cin >> name;
                            characters.erase(name);
                            characters[name] = new EldrichHorror(roles[role], role);
                        }
                        break;
                }
                cout << "Do you want to edit any attributes (y/n)? ";
                cin >> attr;
                if (strcmp(attr.c_str(), "y") == 0) {
                    change_attribute(name);
                }
                cout << name << ":\n" << characters[name]->get_string() << endl;
                break;
            }
        }
    }

    void change_attribute(std::string name) {
        for (const auto& elem : characters) {
            if (strcmp(elem.first.c_str(), name.c_str()) == 0) {
                int value;
                std::string attr;
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
        }
    }

    void add_role() {
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
            roles[name] = new_role;
            fout << write << "\n/\n";
        }
        if (strcmp(type.c_str(), "Eldritch") == 0) {
            cout << "What is the traumatism value (seperated by - if range, available range is 0-10)? ";
            cin >> value;
            new_role["traumatism"] = value;
            write += "\ntraumatism " + value;
            roles[name] = new_role;
            fout << write << "\n/\n";
        }
        if (strcmp(type.c_str(), "Person") == 0) {
            roles[name] = new_role;
            fout << write << "\n/\n";
        }
    }

    void print() {
        for(const auto& elem : roles){
                cout <<  "\t" << elem.first << " - " << elem.second.at("type") << endl;
        }
    }
    void print_role_detailed(std::string name) {
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
            cout << elem.first << " " << elem.second->getRole() << ":\n";
            cout << elem.second->get_string() << endl;
        }
    }
    void print_roster_to_file() {
        fstream fout("roster.txt", ios::out);
        for(const auto& elem : characters) {
            std::string printstr = elem.second->get_string();
            fout << elem.first << " " << elem.second->getRole() << ":" << endl << printstr << endl;
        }
        fout.close();
    }
    void deleteRole(std::string name) {
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
private:
    map<std::string, T> characters;
    map<std::string, map<std::string, std::string> > roles;
};