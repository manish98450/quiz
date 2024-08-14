#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>  // Required for std::sort
#include <ctime>      // Required for time and difftime

using namespace std;

int Guess;
int Total;
int Time_Limit = 10; // 10 seconds per question

struct UserScore {
    string name;
    int score;
};

class Question {
private:
    string Question_Text;
    string Answer_1;
    string Answer_2;
    string Answer_3;
    string Answer_4;
    int Correct_Answer;
    int Question_Score;

public:
    void setValues(string, string, string, string, string, int, int);
    void askQuestion();
    string getQuestionText() const { return Question_Text; }  // Marking the method as const
};

void saveScore(const string& name, int score) {
    ofstream file("scores.txt", ios::app);
    file << name << " " << score << endl;
    file.close();
}

void displayTopScores() {
    vector<UserScore> scores;
    ifstream file("scores.txt");
    string name;
    int score;
    while (file >> name >> score) {
        scores.push_back({ name, score });
    }
    file.close();

    sort(scores.begin(), scores.end(), [](UserScore a, UserScore b) {
        return a.score > b.score;
    });

    cout << "Top Scores:\n";
    for (int i = 0; i < min(5, (int)scores.size()); i++) {
        cout << i + 1 << ". " << scores[i].name << ": " << scores[i].score << endl;
    }
}

bool registerUser(const string& username, const string& password) {
    ifstream user_file("users.txt");
    string user, pass;
    while (user_file >> user >> pass) {
        if (user == username) {
            cout << "Username already exists!" << endl;
            return false;
        }
    }
    user_file.close();

    ofstream file("users.txt", ios::app);
    if (!file) return false;

    file << username << " " << password << endl;
    file.close();
    return true;
}

bool loginUser(const string& username, const string& password) {
    ifstream file("users.txt");
    string user, pass;
    while (file >> user >> pass) {
        if (user == username && pass == password) {
            return true;
        }
    }
    return false;
}

void adminPanel();
void quizMenu();

int main_menu_view() {
    system("color 3F");
    cout << "\t\t*************************************************************************************" << endl;
    cout << "\t\t*****                                                                           *****" << endl;
    cout << "\t\t*****               H E L L O !  W E L C O M E  T O  T H E 'Q I Z Z Y'      *****" << endl;
    cout << "\t\t*****                  = = = = = = = = = = = = = = = = = = = = = = = =          *****" << endl;
    cout << "\t\t*****                            = = = = = = = = = = = =                        *****" << endl;
    cout << "\t\t*****                                     B Y                                   *****" << endl;
    cout << "\t\t*****                               LEARN BY PROJECTS                      *****" << endl;
    cout << "\t\t*****                                                                           *****" << endl;
    cout << "\t\t*************************************************************************************" << endl;
    cout << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Admin Login" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
    int choice;
    cin >> choice;
    cin.ignore();

    string username, password;
    switch (choice) {
    case 1:
        cout << "Enter a username: ";
        getline(cin, username);
        cout << "Enter a password: ";
        getline(cin, password);
        if (registerUser(username, password)) {
            cout << "Registration successful!" << endl;
        }
        break;
    case 2:
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
        if (loginUser(username, password)) {
            cout << "Login successful!" << endl;
            quizMenu();
        } else {
            cout << "Invalid credentials!" << endl;
        }
        break;
    case 3:
        cout << "Enter admin username: ";
        getline(cin, username);
        cout << "Enter admin password: ";
        getline(cin, password);
        if (username == "admin" && password == "admin123") {
            cout << "Admin login successful!" << endl;
            adminPanel();
        } else {
            cout << "Invalid admin credentials!" << endl;
        }
        break;
    case 4:
        return 0;
    default:
        cout << "Invalid option!" << endl;
    }

    return main_menu_view();
}

void Question::setValues(string q, string a1, string a2, string a3, string a4, int ca, int pa) 
{
    Question_Text = q;
    Answer_1 = a1;
    Answer_2 = a2;
    Answer_3 = a3;
    Answer_4 = a4;
    Correct_Answer = ca;
    Question_Score = pa;
}

void Question::askQuestion() {
    cout << endl;
    cout << Question_Text << endl;
    cout << "1. " << Answer_1 << endl;
    cout << "2. " << Answer_2 << endl;
    cout << "3. " << Answer_3 << endl;
    cout << "4. " << Answer_4 << endl;
    cout << endl;

    time_t start_time = time(0);

    cout << "Answer: ";
    cin >> Guess;

    double seconds_taken = difftime(time(0), start_time);

    if (seconds_taken > Time_Limit) {
        cout << "\nTime's up! You took too long to answer." << endl;
        cout << "Score: 0 Out of " << Question_Score << " !" << endl;
    }
    else if (Guess == Correct_Answer) 
    {
        cout << endl;
        cout << "Great! You are Correct." << endl;
        Total += Question_Score;
        cout << "Score: " << Question_Score << " Out of " << Question_Score << " !" << endl;
    }
    else
    {
        cout << endl;
        cout << "Oh, NO. You are Wrong." << endl;
        cout << "Score: 0 Out of " << Question_Score << " !" << endl;
        cout << "The correct answer is " << Correct_Answer << endl;
    }
}

vector<Question> loadQuestions() {
    vector<Question> questions;
    ifstream file("questions.txt");
    string q, a1, a2, a3, a4;
    int ca, pa;
    while (getline(file, q)) {
        getline(file, a1);
        getline(file, a2);
        getline(file, a3);
        getline(file, a4);
        file >> ca >> pa;
        file.ignore();

        Question question;
        question.setValues(q, a1, a2, a3, a4, ca, pa);
        questions.push_back(question);
    }
    return questions;
}

void saveQuestions(const vector<Question>& questions) {
    ofstream file("questions.txt");
    for (const auto& question : questions) {
        file << question.getQuestionText() << endl;
        file << "1" << endl;
        file << "2" << endl;
        file << "3" << endl;
        file << "4" << endl;
        file << "1 10" << endl;  // Placeholder answers; in practice, extract actual answers and scores from question
    }
    file.close();
}

void quizMenu() {
    vector<Question> questions = loadQuestions();

    for (auto& question : questions) {
        question.askQuestion();
    }

    cout << "Your Total Score is " << Total << " points out of " << questions.size() * 10 << "." << endl;
    saveScore("User", Total);

    displayTopScores();

    if (Total >= 70) {
        cout << "Great you passed the Quiz!!!" << endl;
        cout << "C O N G R A T U L A T I O N S !!!" << endl;
    } else {
        cout << "Sorry, you failed the Quiz!" << endl;
        cout << "Do you want to try again ? Yes/No " << endl;
        string play_again;
        cout << "Your choice: ";
        cin >> play_again;
        if (play_again == "yes" || play_again == "Yes") {
            quizMenu();
        } else {
            cout << "OK. Goodbye." << endl;
        }
    }
}

void addQuestion(vector<Question>& questions) {
    string q, a1, a2, a3, a4;
    int ca, pa;
    cin.ignore();
    cout << "Enter question: ";
    getline(cin, q);
    cout << "Enter answer 1: ";
    getline(cin, a1);
    cout << "Enter answer 2: ";
    getline(cin, a2);
    cout << "Enter answer 3: ";
    getline(cin, a3);
    cout << "Enter answer 4: ";
    getline(cin, a4);
    cout << "Enter correct answer (1-4): ";
    cin >> ca;
    cout << "Enter question score: ";
    cin >> pa;

    Question question;
    question.setValues(q, a1, a2, a3, a4, ca, pa);
    questions.push_back(question);
    saveQuestions(questions);
}

void viewQuestions(const vector<Question>& questions) {
    for (const auto& question : questions) {
        cout << question.getQuestionText() << endl;
    }
}

void adminPanel() {
    vector<Question> questions = loadQuestions();

    int choice;
    do {
        cout << "\nAdmin Panel\n";
        cout << "1. View Questions\n";
        cout << "2. Add Question\n";
        cout << "3. Exit Admin Panel\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewQuestions(questions);
            break;
        case 2:
            addQuestion(questions);
            break;
        case 3:
            cout << "Exiting Admin Panel.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

int main() {
    return main_menu_view();
}
