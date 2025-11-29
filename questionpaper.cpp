#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct Question {    // Structure to store each question                  
    string text;
    string topic;
    int marks;
    string difficulty;
};
class QuestionBank {
private:
    vector<Question> questions;

public:
    void addQuestion() {
        Question q;
        cin.ignore();

        cout << "Enter Question: ";
        getline(cin, q.text);

        cout << "Enter Topic: ";
        getline(cin, q.topic);

        cout << "Enter Marks: ";
        cin >> q.marks;
        cin.ignore();

        cout << "Difficulty (Easy/Medium/Hard): ";
        getline(cin, q.difficulty);

        questions.push_back(q);
        cout << "\nQuestion Added Successfully!\n";
    }
    void generatePaper(int totalMarks) {               // Generate question paper
        int collected = 0;
        vector<Question> paper;
        for (auto q : questions) {
            if (collected + q.marks <= totalMarks) {
                paper.push_back(q);
                collected += q.marks;
            }
            if (collected == totalMarks) break;
        }
        ofstream file("QuestionPaper.txt");
        file << "******** QUESTION PAPER ********\n\n";
        int num = 1;
        for (auto &q : paper) {
            file << num++ << ") " << q.text << " [" << q.marks << " Marks]\n";
        }
        file << "\nTotal Marks: " << collected;
        file.close();
        cout << "\nQuestion Paper Generated Successfully (QuestionPaper.txt)\n";
    }
};
int main() {
    QuestionBank qb;
    int choice;
    while (true) {
        cout << "\n===== QUESTION PAPER BUILDER =====\n";
        cout << "1. Add Question\n";
        cout << "2. Generate Question Paper\n";
        cout << "3. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
        if (choice == 1) {
            qb.addQuestion();
        }
        else if (choice == 2) {
            int total;
            cout << "Enter Total Marks for the Question Paper: ";
            cin >> total;
            qb.generatePaper(total);
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid Input! Try Again.\n";
        }
    }

    return 0;
}
