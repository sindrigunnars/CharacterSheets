#include "characters.h"
#include <cstring>
#include <chrono>
#include <map>

int main() {
    srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    Roles<Being*> roles;
    string input = "";
    cout << "Welcome!! ";
    do {
        cout << "What would you like to do?\n\tPress 1: See roles\n\tPress 2: See specific role \n\tPress 3: Add to roster \n\tPress 4: Print roster \n\tPress 5: Add role \n\tPress 6: Remove role\n\tPress q: Quit \n\tChoice: ";
        cin >> input;
        if (strcmp(input.c_str(), "1") == 0) {
            cout << "Roles:" << endl;
            roles.print();
            cout << endl;
        }else if (strcmp(input.c_str(), "2") == 0) {
            cout << "Type in the role name (capitalized): ";
            cin >> input;
            cout << "Stats for ";
            roles.print_role_detailed(input);
            cout << endl;
        }else if (strcmp(input.c_str(), "3") == 0) {
            cout << "What role does this character have? ";
            cin >> input;
            roles.add_character(input);
        }else if (strcmp(input.c_str(), "4") == 0) {
            cout << "1. Print to screen\n2. Print to file ";
            cin >> input;
            if (strcmp(input.c_str(), "1") == 0) {
                roles.print_roster();
            } else if (strcmp(input.c_str(), "2") == 0) {
                roles.print_roster_to_file();
            }
        }else if (strcmp(input.c_str(), "5") == 0) {
            roles.add_role();
        }else if (strcmp(input.c_str(), "6") == 0) {
            cout << "Type in the role name (capitalized): ";
            cin >> input;
            roles.deleteRole(input);
        }
    } while(strcmp(input.c_str(), "q") != 0);
    return 0;
}