#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Question {
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
        cout << "\nEnter Question: ";
        getline(cin, q.text);
        cout << "Enter Topic: ";
        getline(cin, q.topic);
        cout << "Enter Marks: ";
        cin >> q.marks;
        cin.ignore();
        cout << "Difficulty (Easy/Medium/Hard): ";
        getline(cin, q.difficulty);
        questions.push_back(q);
        saveQuestions();
        cout << "\nQuestion Added Successfully!\n";
    }
    void viewQuestions() {
        if (questions.empty()) {
            cout << "\nNo Questions Available!\n";
            return;
        }
        cout << "\n========== QUESTION BANK ==========\n";
        for (int i = 0; i < questions.size(); i++) {
            cout << "\nQuestion " << i + 1 << endl;
            cout << "Question   : " << questions[i].text << endl;
            cout << "Topic      : " << questions[i].topic << endl;
            cout << "Marks      : " << questions[i].marks << endl;
            cout << "Difficulty : " << questions[i].difficulty << endl;
        }
        cout << "\n===================================\n";
    }
    // Search questions by topic
void searchByTopic() {
        if (questions.empty()) {
            cout << "\nNo Questions Available!\n";
            return;
        }
        string searchTopic;
        cin.ignore();
        cout << "\nEnter Topic to Search: ";
        getline(cin, searchTopic);
        bool found = false;
        cout << "\n===== SEARCH RESULTS =====\n";
        for (int i = 0; i < questions.size(); i++) {
            if (questions[i].topic == searchTopic) {
                cout << "\nQuestion: " << questions[i].text << endl;
                cout << "Marks: " << questions[i].marks << endl;
                cout << "Difficulty: " << questions[i].difficulty << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "\nNo Questions Found for Topic: "
                 << searchTopic << endl;
        }
    }
    // Delete question
    void deleteQuestion() {
        if (questions.empty()) {
            cout << "\nNo Questions Available to Delete!\n";
            return;
        }
        viewQuestions();
        int number;
        cout << "\nEnter Question Number to Delete: ";
        cin >> number;
        if (number >= 1 && number <= questions.size()) {
            questions.erase(questions.begin() + number - 1);
            saveQuestions();
            cout << "\nQuestion Deleted Successfully!\n";
        }
        else {
            cout << "\nInvalid Question Number!\n";
        }
    }
    // Generate question paper
    void generatePaper(int totalMarks) {
        if (questions.empty()) {
            cout << "\nNo Questions Available!\n";
            return;
        }
        int collected = 0;
        vector<Question> paper;
        for (auto q : questions) {
            if (collected + q.marks <= totalMarks) {
                paper.push_back(q);
                collected += q.marks;
            }
            if (collected == totalMarks)
                break;
        }
        ofstream file("QuestionPaper.txt");
        file << "========================================\n";
        file << "            QUESTION PAPER\n";
        file << "========================================\n\n";
        file << "Maximum Marks: " << totalMarks << "\n\n";
        file << "Instructions:\n";
        file << "1. Answer all questions.\n";
        file << "2. Marks are indicated against each question.\n\n";
        int num = 1;
        for (auto &q : paper) {
            file << num++ << ") "
                 << q.text
                 << " ["
                 << q.marks
                 << " Marks]\n";
            file << "   Topic: "
                 << q.topic
                 << " | Difficulty: "
                 << q.difficulty
                 << "\n\n";
        }
        file << "========================================\n";
        file << "Total Marks: " << collected << endl;
        file << "========================================\n";
        file.close();
        cout << "\nQuestion Paper Generated Successfully!\n";
        cout << "File Name: QuestionPaper.txt\n";
        if (collected < totalMarks) {
            cout << "\nNote: Could only generate "
                 << collected
                 << " marks out of "
                 << totalMarks
                 << " marks.\n";
        }    }
    // Save question bank to file
    void saveQuestions() {
        ofstream file("QuestionBank.txt");
        for (auto &q : questions) {
            file << q.text << endl;
            file << q.topic << endl;
            file << q.marks << endl;
            file << q.difficulty << endl;
        }
        file.close();
    }
    // Load questions when program starts
    void loadQuestions() {
        ifstream file("QuestionBank.txt");
        if (!file) {
            return;
        }
        Question q;
        while (getline(file, q.text)) {
            getline(file, q.topic);
            file >> q.marks;
            file.ignore();
            getline(file, q.difficulty);
            questions.push_back(q);
        }
        file.close();
    }
};


int main() {
    QuestionBank qb;
    qb.loadQuestions();
    int choice;
    while (true) {
        cout << "\n====================================\n";
        cout << "       QUESTION PAPER BUILDER\n";
        cout << "====================================\n";
        cout << "1. Add Question\n";
        cout << "2. View All Questions\n";
        cout << "3. Search Question by Topic\n";
        cout << "4. Delete Question\n";
        cout << "5. Generate Question Paper\n";
        cout << "6. Exit\n";
        cout << "====================================\n";
        cout << "Enter Choice: ";
        cin >> choice;
        if (choice == 1) {
            qb.addQuestion();
        }
        else if (choice == 2) {
            qb.viewQuestions();
        }
        else if (choice == 3) {
            qb.searchByTopic();
        }
        else if (choice == 4) {
            qb.deleteQuestion();
        }
        else if (choice == 5) {
            int total;
            cout << "\nEnter Total Marks for the Question Paper: ";
            cin >> total;
            qb.generatePaper(total);
        }else if (choice == 6) {

            cout << "\nThank You!\n";
            cout << "Exiting Question Paper Builder...\n";

            break;
        }else {

            cout << "\nInvalid Input! Try Again.\n";
        }
    }

    return 0;
}