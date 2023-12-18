// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Simon Belkin
// SNHU Online CS 300
// Hash Implementation of Course and Pre-Requisite Data Structure

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

// Definition of the Course class
class Course {
public:
    std::string courseNumber;           // Stores the course number
    std::string courseName;             // Stores the course name
    std::vector<std::string> prerequisites; // Stores a list of prerequisites

    Course() = default; // Default constructor
    Course(std::string number, std::string name, std::vector<std::string> prereqs)
        : courseNumber(number), courseName(name), prerequisites(prereqs) {} // Constructor that initializes the course with given details
};

// Hash table to store courses with the course number as the key
std::unordered_map<std::string, Course> courses;

// Function to load courses from a file
void loadCoursesFromFile(const std::string& fileName) {
    std::ifstream file(fileName); // Open the file
    if (!file) { // Check if the file opening failed
        std::cout << "File not found\n";
        exit(1); // Exit the program if the file is not found
    }

    std::string line;
    while (getline(file, line)) { // Read each line from the file
        // Parse the line to create a Course object
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;
        while (getline(ss, item, ',')) { // Tokenize the line based on commas
            tokens.push_back(item);
        }

        if (tokens.size() < 2) { // Check for formatting errors
            std::cout << "Formatting error in line\n";
            continue; // Skip to the next line if a formatting error is found
        }

        // Extract prerequisites if any
        std::vector<std::string> prerequisites(tokens.begin() + 2, tokens.end());
        Course course(tokens[0], tokens[1], prerequisites); // Create a Course object
        courses[tokens[0]] = course; // Add the course to the hash table
    }
    file.close(); // Close the file
}

// Function to print information about a specific course
void printCourseInformation(const std::string& courseNumber) {
    if (courses.find(courseNumber) != courses.end()) { // Check if the course exists
        Course& course = courses[courseNumber]; // Retrieve the course
        std::cout << course.courseNumber << ", " << course.courseName << "\n";
        std::cout << "Prerequisites: ";
        for (const auto& p : course.prerequisites) { // Print all prerequisites
            std::cout << p << " ";
        }
        std::cout << "\n";
    }
}

// Function to print a sorted list of all courses
void printSortedCourseList() {
    std::vector<Course> courseList;
    for (const auto& pair : courses) { // Copy courses to a vector
        courseList.push_back(pair.second);
    }

    // Sort the courses by their course number
    std::sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    // Print the sorted list of courses
    for (const auto& course : courseList) {
        std::cout << course.courseNumber << ", " << course.courseName << "\n";
    }
}

// Function for the main menu of the program
void mainMenu() {
    std::string courseNumber; // Variable to store user input for course number
    while (true) { // Loop to keep the menu running
        // Display menu options
        std::cout << "1. Load Data Structure.\n";
        std::cout << "2. Print Course List.\n";
        std::cout << "3. Print Course.\n";
        std::cout << "9. Exit\n";
        std::cout << "What would you like to do? ";

        int choice; // Variable to store the user's menu choice
        std::cin >> choice; // Read the user's choice
        switch (choice) { // Handle the choice using a switch statement
        case 1:
            loadCoursesFromFile("input.txt");  // Load courses from file
            break;
        case 2:
            printSortedCourseList(); // Print the sorted list of courses
            break;
        case 3:
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber; // Read the course number from the user
            printCourseInformation(courseNumber); // Print information about the specified course
            break;
        case 9:
            std::cout << "Thank you for using the course planner!\n";
            return; // Exit the menu loop
        default:
            std::cout << choice << " is not a valid option.\n"; // Handle invalid choices
        }
    }
}

// Main function where program execution begins
int main() {
    mainMenu(); // Call the main menu function
    return 0;
}
