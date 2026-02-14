#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <sqlite3.h>
#include <limits>
#include <iomanip>

using namespace std;

//Defining Functions

// Function to clear the console screen {clears the console and displays the welcome message}
void clearscreen() {
    system("cls");
    cout << "Welcome To Employee Management System!" << endl;
}

// Function to display available commands {displays the list of available commands to the user}
void display_help() {
    cout << "Available commands:" << endl;
    cout << "Add Employee: Add Employee" << endl;
    cout << "Remove Employee: Remove Employee" << endl;
    cout << "List Employees: List Employees" << endl;
    cout << "Show Help: Help" << endl;
    cout << "Exit System: Exit" << endl;
}
//function end {displays the list of available commands to the user}

// Function to display all employees in a formatted table
void display_employees(sqlite3* db) {
    cout << "Listing all employees..." << endl;
    // Display employees in a formatted table
    const char* sql_list = "SELECT id, first_name, last_name, employee_position, email, contact_number, gender, age FROM employees;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_list, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << left << setw(5) << "ID" << setw(15) << "First Name" << setw(15) << "Last Name" << setw(20) << "Position" << setw(35) << "Email" << setw(15) << "Contact" << setw(10) << "Gender" << setw(5) << "Age" << endl;
        cout << string(120, '-') << endl;

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* first_name = (const char*)sqlite3_column_text(stmt, 1);
            const char* last_name = (const char*)sqlite3_column_text(stmt, 2);
            const char* position = (const char*)sqlite3_column_text(stmt, 3);
            const char* email = (const char*)sqlite3_column_text(stmt, 4);
            const char* contact_number = (const char*)sqlite3_column_text(stmt, 5);
            const char* gender = (const char*)sqlite3_column_text(stmt, 6);
            int age = sqlite3_column_int(stmt, 7);

            cout << left << setw(5) << id << setw(15) << first_name << setw(15) << last_name << setw(20) << position << setw(35) << email << setw(15) << contact_number << setw(10) << gender << setw(5) << age << endl;
        }
    }
    sqlite3_finalize(stmt);
}
//function end {display employees in a formatted table}

//bool function to check if command in array of commands
bool matches(const string& cmd, string arr[], size_t size) {
    return find(arr, arr + size, cmd) != arr + size;
}


int main() {


    sqlite3* db;
    int exit = sqlite3_open("employees.db", &db);
    if (exit) {
        cerr << "Error opening DB: " << sqlite3_errmsg(db) << endl;
        return 1;
    }
        const char* sql = 
        "CREATE TABLE IF NOT EXISTS employees ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "employee_position TEXT NOT NULL,"
        "email TEXT NOT NULL UNIQUE,"
        "contact_number TEXT NOT NULL,"
        "gender TEXT NOT NULL CHECK(gender IN ('Male', 'Female', 'Other')),"
        "age INTEGER"
        ");";

    char* errMsg = nullptr;

    exit = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (exit != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    
    clearscreen();
    
    string command;

    // Commands: add, remove, list, exit
    string add_command[] = {"ADD", "NEW", "ADD EMPLOYEE", "INSERT EMPLOYEE", "CREATE EMPLOYEE", "REGISTER EMPLOYEE", "REGISTER"};
    string remove_command[] = {"REMOVE EMPLOYEE", "DELETE EMPLOYEE", "ERASE EMPLOYEE", "FIRE EMPLOYEE", "DISMISS EMPLOYEE", "TERMINATE EMPLOYEE", "REMOVE" , "DELETE", "ERASE", "FIRE", "DISMISS", "TERMINATE"};
    string list_command[] = {"LIST", "GET", "SHOW EMPLOYEES" , "DISPLAY EMPLOYEES", "VIEW EMPLOYEES" , "LIST EMPLOYEES" , "GET EMPLOYEES", "SHOW", "DISPLAY", "VIEW"};
    string exit_command[] = {"EXIT" , "QUIT" , "LEAVE" , "CLOSE" , "END" , "STOP"};
    string help_command[] = {"HELP", "COMMANDS", "SHOW COMMANDS", "LIST COMMANDS", "DISPLAY COMMANDS", "VIEW COMMANDS"};
    

    while (true) { // Main command loop
        cout << "=> ";
        getline(cin, command);
            transform(command.begin(), command.end(), command.begin(), ::toupper);

            if (matches(command, add_command, sizeof(add_command)/sizeof(add_command[0]))) {
            cout << "Adding an employee..." << endl;
            string first_name, last_name, position, email, contact, gender;
            int age;

            cout << "First Name: ";
            getline(cin, first_name);

            cout << "Last Name: ";
            getline(cin, last_name);

            cout << "Position: ";
            getline(cin, position);

            cout << "Email: ";
            cin >> email;

            cout << "Contact Number: ";
            cin >> contact;

            cout << "Gender (Male/Female/Other): ";
            cin >> gender;

            cout << "Age: ";
            cin >> age;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            const char* sql_insert =
                "INSERT INTO employees "
                "(first_name, last_name, employee_position, email, contact_number, gender, age) "
                "VALUES (?, ?, ?, ?, ?, ?, ?);";

            sqlite3_stmt* stmt;
            if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr) != SQLITE_OK) {
                cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
            } else {
                sqlite3_bind_text(stmt, 1, first_name.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 2, last_name.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 3, position.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 4, email.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 5, contact.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 6, gender.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_int(stmt, 7, age);

                if (sqlite3_step(stmt) != SQLITE_DONE) {
                    cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
                } else {
                    clearscreen();
                    cout << "Employee added successfully." << endl;
                    cout << "ID: " << sqlite3_last_insert_rowid(db) << endl;
                }
                sqlite3_finalize(stmt);
            }

        } else if (matches(command, remove_command, sizeof(remove_command)/sizeof(remove_command[0]))) {
            cout << "Removing an employee..." << endl;
            int id;
            cout << "Enter Employee ID to remove: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Are you sure you want to remove employee with ID " << id << "? (yes/no): ";
            string confirmation;
            getline(cin, confirmation);
            
            transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::toupper);
            if (confirmation == "YES") {
                const char* sql_delete = "DELETE FROM employees WHERE id = ?;";
                sqlite3_stmt* stmt;
                if (sqlite3_prepare_v2(db, sql_delete, -1, &stmt, nullptr) != SQLITE_OK) {
                    cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
                } else {
                    sqlite3_bind_int(stmt, 1, id);
                    if (sqlite3_step(stmt) != SQLITE_DONE) {
                        cerr << "Delete failed: " << sqlite3_errmsg(db) << endl;
                    } else {
                        clearscreen();
                        cout << "Employee removed successfully." << endl;
                    }
                    sqlite3_finalize(stmt);
                }
            } else {
                cout << "Removal cancelled." << endl;
            }

        } else if (matches(command, list_command, sizeof(list_command)/sizeof(list_command[0]))) {
            clearscreen();
            cout << "Listing all employees..." << endl;
            // Display employees in a formatted table
            display_employees(db);
            
        } else if (matches(command, help_command, sizeof(help_command)/sizeof(help_command[0]))) {
            clearscreen();
            display_help();

        } else if (matches(command, exit_command, sizeof(exit_command)/sizeof(exit_command[0]))) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;

        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
    sqlite3_close(db);
    return 0;
}