# Quiz Application with User Authentication and Admin Panel

## Overview
This is a C++ console-based quiz application that allows users to register, log in, and participate in timed quizzes. The application also includes an admin panel where administrators can manage quiz questions, view existing questions, and add new ones.

## Features
- User Authentication: Users can register and log in with a username and password.
- Admin Panel: Administrators can add, view, and manage quiz questions.
- Timed Quizzes: Each question has a time limit, and users receive feedback on their answers.
- Leaderboard: The application tracks and displays the top scores of users.

## How to Run
1. Compile the Code: Use a C++ compiler (e.g., g++) to compile the code.
   ```bash
   g++ -o quiz_app main.cpp
   ```
2. Run the Executable:
   ```bash
   ./quiz_app
   ```
3. Follow the On-Screen Instructions: Register, log in, and enjoy the quiz!

## File Structure
- `main.cpp`: The main program file containing the implementation of the quiz application.
- `users.txt`: Stores registered usernames and passwords.
- `questions.txt`: Stores quiz questions and their corresponding answers.
- `scores.txt`: Stores user scores and their respective usernames.

## Technologies Used
- C++: Core programming language used for developing the application.
- File Handling: Used for storing user data, questions, and scores.
- Object-Oriented Programming (OOP): Applied for structuring the code and managing quiz functionalities.
