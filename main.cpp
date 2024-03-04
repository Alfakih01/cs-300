#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define a structure to hold course information
struct Course {
    string number;
    string title;
    vector<string> prerequisites;
};

// Function declarations
void loadCourses(map<string, Course>& courses);
void printCourseList(const map<string, Course>& courses);
void printCourse(const map<string, Course>& courses, const string& courseNumber);
void displayMenu();
bool isValidCourseNumber(const string& courseNumber);

int main() {
    map<string, Course> courses;
    bool running = true;
    bool dataLoaded = false;

    cout << "Welcome to the course planner." << endl;

    while (running) {
        displayMenu();
        string input;
        cout << "What would you like to do? ";
        getline(cin, input);

        if (input.empty() || !isdigit(input[0])) {
            cout << input << " is not a valid option." << endl;
            continue;
        }

        int option = stoi(input);
        switch (option) {
            case 1:
                loadCourses(courses);
                dataLoaded = true;
                cout << "Here is a sample schedule:" << endl;
                break;
            case 2:
                if (!dataLoaded) {
                    cout << "Please load data structure first." << endl;
                    break;
                }
                printCourseList(courses);
                break;
            case 3:
                if (!dataLoaded) {
                    cout << "Please load data structure first." << endl;
                    break;
                }
                cout << "What course do you want to know about? ";
                getline(cin, input);
                if (!isValidCourseNumber(input)) {
                    cout << input << " is not a valid course number." << endl;
                    break;
                }
                printCourse(courses, input);
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                running = false;
                break;
            default:
                cout << input << " is not a valid option." << endl;
                break;
        }
    }

    return 0;
}

void loadCourses(map<string, Course>& courses) {
    string filePath = "/Users/ameen/Desktop/cs-300/week 7/ABCU_Advising_Program_Input.txt"; // Hardcoded file path

    ifstream file(filePath); 
    if (!file.is_open()) {
        cout << "Failed to open file: " << filePath << endl; 
        return;
    }

    string line;
    int count = 0; // Debug: count the number of courses loaded
    while (getline(file, line)) {
        stringstream ss(line);
        string number, title, prerequisite;
        getline(ss, number, ',');
        getline(ss, title, ',');
        Course course{number, title};
        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }
        courses[number] = course;
        count++; // Debug: increment the count
    }

    cout << "Courses loaded successfully. Total courses loaded: " << count << endl; // Debug: print the count
}


void printCourseList(const map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No courses loaded to display." << endl; // Debug: check if courses map is empty
        return;
    }

    cout << "Here is a sample schedule:" << endl;
    for (const auto& pair : courses) {
        cout << pair.second.number << ", " << pair.second.title << endl; // Debug: print the course number and title
        // Debug: print prerequisites
        cout << "Prerequisites: ";
        for (const string& prereq : pair.second.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    }
}


void printCourse(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.number << ", " << it->second.title << endl;
        if (!it->second.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const string& prereq : it->second.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        } else {
            cout << "No prerequisites" << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}


void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

bool isValidCourseNumber(const string& courseNumber) {

    return true; 
}

