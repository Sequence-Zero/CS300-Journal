#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Course { //Structure to hold course information
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

struct Node { //Instantiating Node object
    Course course;
    Node* left;
    Node* right;

    explicit Node(const Course& newCourse) : course(newCourse), left(nullptr), right(nullptr) {}
};

class BinarySearchTree { //BST Class
private:
    Node* root;

    void insert(Node*& node, const Course& course) { //Private mutator method to insert course
        if (node == nullptr) {
            node = new Node(course);
            return;
        }

        if (course.courseNumber < node->course.courseNumber) { //if current course key is less than root
            insert(node->left, course); //insert left child
        } else {
            insert(node->right, course); //else if key is greater, insert as right child
        }
    }

    Course* search(Node* node, const string& courseNumber) const { //Private accessor method to provide search functionality
        if (node == nullptr) { //if tree is empty
            return nullptr;
        }

        if (courseNumber == node->course.courseNumber) { //If course number matches the requested key
            return &node->course; //returns the matching node
        }

        if (courseNumber < node->course.courseNumber) { //if provided search key is less than current course
            return search(node->left, courseNumber); //returns left node and course number
        }

        return search(node->right, courseNumber); //else return right node if greater key
    }

    void inOrder(Node* node) const {  //Private accessor method for returning courses in order
        if (node == nullptr) { //if null
            return;
        }

        inOrder(node->left); //go as far left as possible
        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl; //then print current node
        inOrder(node->right); //then go right
    }

    void clearTree(Node* node) { //tree cleanup destructor helper
        if (node == nullptr) {
            return;
        }

        clearTree(node->left); //recursive call to left
        clearTree(node->right); //recursive call to right
        delete node; 
    }

public:
    BinarySearchTree() : root(nullptr) {} //Instantiating tree with null root

    ~BinarySearchTree() { 
        clearTree(root); //destructor
    }

    void clear() {  
        clearTree(root);
        root = nullptr; //empties tree for reuse
    }

    void insert(const Course& course) { //member function to insert
        insert(root, course);
    }

    Course* search(const string& courseNumber) const { //member function to call search using course number
        return search(root, courseNumber);
    }

    void printCourseList() const { //member function to print course list via inOrder call
        inOrder(root);
    }

    bool isEmpty() const { 
        return root == nullptr;
    }
};


string toUpperCase(const string& input) { //String function to translate lower case input
    string result = input;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char ch) { return static_cast<char>(toupper(ch)); });
    return result;
}

vector<string> splitCsvLine(const string& line) { //Vector function to split CSV file lines
    vector<string> tokens;
    string token;
    stringstream ss(line);

    while (getline(ss, token, ',')) { //while loop to identify and compartmentalize csv data based on commas found
        tokens.push_back(token);
    }

    return tokens;
}

bool loadCourses(const string& fileName, BinarySearchTree& bst) {
    ifstream inputFile(fileName); //reading csv file

    if (!inputFile.is_open()) { //error handling for parsing input file
        cout << "Error: could not open file \"" << fileName << "\"." << endl;
        return false;
    }

    bst.clear(); //clears current structure to make room for new query

    string line;
    while (getline(inputFile, line)) { 
        if (line.empty()) {
            continue;
        }

    vector<string> tokens = splitCsvLine(line); //call to splitcsv
    if (tokens.size() < 2) {
        continue;
    }

    Course course;
    course.courseNumber = toUpperCase(tokens[0]); //initializing course data
    course.courseTitle = tokens[1];

    
    if (!course.courseTitle.empty() && course.courseTitle.back() == '\r') {
        course.courseTitle.pop_back();
    }

    for (size_t i = 2; i < tokens.size(); ++i) {
        string prerequisite = toUpperCase(tokens[i]); // Get prereqs

        if (!prerequisite.empty() && prerequisite.back() == '\r') {
            prerequisite.pop_back(); //Clean up line ending
        }

        if (!prerequisite.empty()) {
            course.prerequisites.push_back(prerequisite); //add prereqs
        }
    }

    bst.insert(course);
}

    inputFile.close();
    cout << "Courses loaded successfully." << endl;
    return true;
}

void printCourseInformation(BinarySearchTree& bst, const string& userInput) {
    string courseNumber = toUpperCase(userInput); //Printing course number by user input id
    Course* course = bst.search(courseNumber); //calling search on bst

    if (course == nullptr) {
        cout << "Course " << courseNumber << " not found." << endl; //if course id not found, throws error
        return;
    }

    cout << course->courseNumber << ", " << course->courseTitle << endl; //else courseid and course number are printed

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl; //if no prereq's exist
        return;
    }

    cout << "Prerequisites: "; //else if prereqs exist
    for (size_t i = 0; i < course->prerequisites.size(); ++i) { //loop to print prereqs
        cout << course->prerequisites[i];
        if (i + 1 < course->prerequisites.size()) {
            cout << ", ";
        }
    }
    cout << endl;
}

int getMenuChoice() {
    int choice;

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main() {
    BinarySearchTree bst;
    bool dataLoaded = false;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        choice = getMenuChoice();

        switch (choice) {
            case 1: {
                string fileName;
                cout << "Enter the file name: ";
                getline(cin, fileName);
                dataLoaded = loadCourses(fileName, bst);
                break;
            }
            case 2:
                if (!dataLoaded || bst.isEmpty()) {
                    cout << "Please load the course data file first." << endl;
                } else {
                    cout << "Here is a sample schedule:" << endl;
                    bst.printCourseList();
                }
                break;
            case 3:
                if (!dataLoaded || bst.isEmpty()) {
                    cout << "Please load the course data file first." << endl;
                } else {
                    string courseNumber;
                    cout << "What course do you want to know about? ";
                    getline(cin, courseNumber);
                    printCourseInformation(bst, courseNumber);
                }
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    return 0;
}
