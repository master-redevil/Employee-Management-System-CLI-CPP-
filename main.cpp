#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdlib>

using namespace std;

int main() {
    system("cls"); // Clear the console screen (Windows specific)

    cout << "Welcome To Employee Management System!" << endl;
    string command;

    // Commands: add, remove, list, exit
    string add_command[] = {"ADD", "NEW", "ADD EMPLOYEE", "INSERT EMPLOYEE", "CREATE EMPLOYEE", "REGISTER EMPLOYEE", "REGISTER"};
    string remove_command[] = {"REMOVE EMPLOYEE", "DELETE EMPLOYEE", "ERASE EMPLOYEE", "FIRE EMPLOYEE", "DISMISS EMPLOYEE", "TERMINATE EMPLOYEE", "REMOVE" , "DELETE", "ERASE", "FIRE", "DISMISS", "TERMINATE"};
    string list_command[] = {"LIST", "GET", "SHOW EMPLOYEES" , "DISPLAY EMPLOYEES", "VIEW EMPLOYEES" , "LIST EMPLOYEES" , "GET EMPLOYEES", "SHOW", "DISPLAY", "VIEW"};
    string exit_command[] = {"EXIT" , "QUIT" , "LEAVE" , "CLOSE" , "END" , "STOP"};
    string help_command[] = {"HELP", "COMMANDS", "SHOW COMMANDS", "LIST COMMANDS", "DISPLAY COMMANDS", "VIEW COMMANDS"};

     

    

    while (true) {
        cout << "=> ";
        getline(cin, command);
        transform(command.begin(), command.end(), command.begin(), ::toupper);
        if (find(add_command, add_command + sizeof(add_command)/sizeof(add_command[0]), command) != add_command + sizeof(add_command)/sizeof(add_command[0])) {
            // Code to add an employee
            cout << "Adding an employee..." << endl;
        } else if (find(remove_command, remove_command + sizeof(remove_command)/sizeof(remove_command[0]), command) != remove_command + sizeof(remove_command)/sizeof(remove_command[0])) {
            // Code to remove an employee
            cout << "Removing an employee..." << endl;
        } else if (find(list_command, list_command + sizeof(list_command)/sizeof(list_command[0]), command) != list_command + sizeof(list_command)/sizeof(list_command[0])) {
            // Code to list all employees
            cout << "Listing all employees..." << endl;
        } else if (find(help_command, help_command + sizeof(help_command)/sizeof(help_command[0]), command) != help_command + sizeof(help_command)/sizeof(help_command[0])) {
            cout << "Available commands:" << endl;
            cout << "Add Employee: Add Employee" << endl;
            cout << "Remove Employee: Remove Employee" << endl;
            cout << "List Employees: List Employees" << endl;
            cout << "Show Help: Help" << endl;
            cout << "Exit System: Exit" << endl;
        } else if (find(exit_command, exit_command + sizeof(exit_command)/sizeof(exit_command[0]), command) != exit_command + sizeof(exit_command)/sizeof(exit_command[0])) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
    return 0;
}