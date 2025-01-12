#include <iostream>  
#include <cstring>   
#include <fstream>   
#include <conio.h>  
#include <iomanip> 
using namespace std;

// Define a structure to store student details
struct Student {
    char id[20];
    char name[20];
    char blood_group[5];
    char department[20];
    char contact[20];
    char parent_contact[20];
};

// Function to add a student to the file
void add_student(const Student& student, const char* filename) {
    FILE* file = fopen(filename, "a"); // Open file in append mode
    if (file != nullptr) {
        // Write student data to file in CSV format
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", student.id, student.name, student.blood_group, student.department, student.contact, student.parent_contact);
        fclose(file); // Close the file
    } else {
        cerr << "Unable to open file\n"; // Error message if file cannot be opened
    }
}

// Function to load student data from the file into an array
int load_data(Student* students, const char* filename) {
    FILE* file = fopen(filename, "r"); // Open file in read mode
    if (file == nullptr) {
        return 0; // Return 0 if file cannot be opened
    }

    int count = 0; // Initialize student count
    // Read student data from file line by line
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", students[count].id, students[count].name, students[count].blood_group, students[count].department, students[count].contact, students[count].parent_contact) != EOF) {
        count++; // Increment count for each student
    }

    fclose(file); // Close the file
    return count; // Return the number of students loaded
}

// Function to search for a student by ID
Student* search_by_id(Student* students, int count, const char* id) {
    for (int i = 0; i < count; ++i) { // Iterate through the student array
        if (strcmp(students[i].id, id) == 0) { // Check if IDs match
            return &students[i]; // Return pointer to the matching student
        }
    }
    return nullptr; // Return nullptr if no match is found
}

// Function to search for a student by blood group
Student* search_by_blood_group(Student* students, int count, const char* blood_group) {
    for (int i = 0; i < count; ++i) { // Iterate through the student array
        if (strcmp(students[i].blood_group, blood_group) == 0) { // Check if blood groups match
            return &students[i]; // Return pointer to the matching student
        }
    }
    return nullptr; // Return nullptr if no match is found
}

// Function to delete a student by ID
void delete_student(Student* students, int& count, const char* id, const char* filename) {
    int index = -1;
    // Find the student with the given ID
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].id, id) == 0) {
            index = i; // Save the index of the matching student
            break;
        }
    }

    if (index != -1) {
        // Shift all subsequent students one position left to overwrite the deleted student
        for (int i = index; i < count - 1; ++i) {
            students[i] = students[i + 1];
        }
        count--; // Decrease student count

        // Rewrite the updated student list back to the file
        FILE* file = fopen(filename, "w"); // Open file in write mode
        for (int i = 0; i < count; ++i) {
            fprintf(file, "%s,%s,%s,%s,%s,%s\n", students[i].id, students[i].name, students[i].blood_group, students[i].department, students[i].contact, students[i].parent_contact);
        }
        fclose(file); // Close the file
    } else {
        cout << "Student not found\n"; // Error message if student not found
    }
}

// Function to confirm a user's action
bool confirm_action(const char* action) {
    char choice;
    cout << action << " (Yes/No) [y/n]: ";
    cin >> choice;
    return choice == 'Y' || choice == 'y'; // Return true if user confirms
}

// Function to register a new user
void register_user(const char* filename) {
    char username[20];
    char password[20];

    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";

    int i = 0;
    char ch;
    // Get password character by character, masking it with '*'
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && i > 0) { // Handle backspace
            cout << "\b \b";
            i--;
        } else if (ch != '\b') {
            cout << '*'; // Mask password character
            password[i++] = ch;
        }
    }
    password[i] = '\0'; // Null-terminate the password

    ofstream file(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << username << " " << password << "\n"; // Write username and password to file
        file.close(); // Close the file
    } else {
        cerr << "Unable to open file\n"; // Error message if file cannot be opened
    }
    cout << "\nUser registered successfully!\n";
}

// Function to login a user
bool login(const char* filename) {
    char username[20];
    char password[20];

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";

    int i = 0;
    char ch;
    // Get password character by character, masking it with '*'
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && i > 0) { // Handle backspace
            cout << "\b \b";
            i--;
        } else if (ch != '\b') {
            cout << '*'; // Mask password character
            password[i++] = ch;
        }
    }
    password[i] = '\0'; // Null-terminate the password

    ifstream file(filename); // Open file in read mode
    if (!file) {
        cerr << "Unable to open file\n"; // Error message if file cannot be opened
        return false;
    }

    char stored_username[20];
    char stored_password[20];
    // Check if entered credentials match any stored credentials
    while (file >> stored_username >> stored_password) {
        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
            return true; // Return true if credentials match
        }
    }
    return false; // Return false if no match is found
}

// Function to print a welcome message
void print_welcome_message() {
    const string message = "Welcome to Student Solution";
    int width = 80; // Width for centering
    int padding = (width - message.length()) / 2; // Calculate padding
    cout << string(padding, ' ') << message << endl;
    cout << endl;
}

// Function to print a centered message
void print_centered_message(const string& message) {
    int width = 80; // Width for centering
    int padding = (width - message.length()) / 2; // Calculate padding
    cout << string(padding, ' ') << message << endl;
}

// Function to confirm exit
bool confirm_exit() {
    char choice;
    cout << "Are you sure you want to exit? (Yes/No) [y/n]: ";
    cin >> choice;
    return choice == 'Y' || choice == 'y'; // Return true if user confirms exit
}

// Function to validate a blood group
bool is_valid_blood_group(const char* blood_group) {
    // List of valid blood groups
    const char* valid_blood_groups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    for (const char* valid_group : valid_blood_groups) { // Iterate through valid blood groups
        if (strcmp(blood_group, valid_group) == 0) {
            return true; // Return true if valid
        }
    }
    return false; // Return false if invalid
}

int main() {
    // File names for storing student and user data
    const char* student_filename = "students.txt";
    const char* user_filename = "users.txt";

    int choice;

    // Prompt user for initial choice
    cout << "Please select an option to continue:\n";
    cout << "1. Register\n2. Login\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        print_centered_message("** Registration Menu **");
        cout << "In order to register, please provide a unique username and password.\n";
        register_user(user_filename); // Call register function
        cout << endl;
    } else if (choice == 2) {
        print_centered_message("** Login Menu **");
        cout << "Please enter your username and password to login.\n";
        if (!login(user_filename)) { // Call login function
            cout << "\nInvalid username or password!\n";
            return 1; // Exit program if login fails
        }
        cout << endl;
        cout << "User Login Success!" << endl;
        cout << endl;
    } else {
        cout << "Invalid choice. Exiting the system.\n";
        return 1; // Exit program if invalid choice
    }

    print_welcome_message(); // Print welcome message
    print_centered_message("** Main Menu **");

    Student students[100]; // Array to store student data
    int student_count = load_data(students, student_filename); // Load student data from file

    // Main menu loop
    while (true) {
        cout << "\n1. Add Student\n2. Search Student by ID\n3. Search Students by Blood Group\n4. Delete Student\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) { // Add a new student
            Student student;
            cout << "Enter Student ID: ";
            cin >> student.id;
            cin.ignore(); // Ignore newline character
            cout << "Enter Name: ";
            cin.getline(student.name, 20); // Input name
            cout << "Enter Blood Group: ";
            cin.getline(student.blood_group, 5); // Input blood group
            cout << "Enter Department: ";
            cin.getline(student.department, 20); // Input department
            cout << "Enter Student Contact: ";
            cin.getline(student.contact, 20); // Input contact
            cout << "Enter Parent Contact: ";
            cin.getline(student.parent_contact, 20); // Input parent contact
            add_student(student, student_filename); // Add student to file
            student_count = load_data(students, student_filename); // Reload student data
            cout << "Student added successfully!\n";
        } else if (choice == 2) { // Search student by ID
            char id[20];
            cout << "Enter Student ID to search: ";
            cin >> id;
            Student* found_student = search_by_id(students, student_count, id); // Search for student
            if (found_student != nullptr) {
                cout << "Student found:\n";
                cout << "ID: " << found_student->id << "\n";
                cout << "Name: " << found_student->name << "\n";
                cout << "Blood Group: " << found_student->blood_group << "\n";
                cout << "Parent Contact: " << found_student->parent_contact << "\n";
                cout << "Department: " << found_student->department << "\n";
            } else {
                cout << "Student not found\n";
            }
        } else if (choice == 3) { // Search students by blood group
            char blood_group[5];
            cout << "Enter Blood Group to search: ";
            cin >> blood_group;
            if (!is_valid_blood_group(blood_group)) { // Validate blood group
                cout << "Error: Invalid blood group entered!\n";
            } else {
                Student* found_student = search_by_blood_group(students, student_count, blood_group); // Search for student
                if (found_student != nullptr) {
                    cout << "Student found:\n";
                    cout << "ID: " << found_student->id << "\n";
                    cout << "Name: " << found_student->name << "\n";
                    cout << "Blood Group: " << found_student->blood_group << "\n";
                    cout << "Parent Contact: " << found_student->parent_contact << "\n";
                    cout << "Department: " << found_student->department << "\n";
                } else {
                    cout << "No student found with that blood group\n";
                }
            }
        } else if (choice == 4) { // Delete a student
            char id[20];
            cout << "Enter Student ID to delete: ";
            cin >> id;
            if (confirm_action("Are you sure you want to delete the student")) { // Confirm deletion
                delete_student(students, student_count, id, student_filename); // Delete student
            }
        } else if (choice == 5) { // Exit the system
            if (confirm_exit()) { // Confirm exit
                cout << "Exiting the system. Goodbye!\n";
                break;
            }
        } else {
            cout << "Invalid choice. Please try again.\n"; // Invalid menu choice
        }
    }
    return 0;
}
