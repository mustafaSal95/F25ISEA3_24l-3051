//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//#include <cctype>
//
//using namespace std;
//
//// --- Constants ---
//const int MAX_MISTAKES = 7;
//const string WORDS_FILE = "words.txt";
//
//// --- Function Definitions ---
//
//// Clears the console screen in a simple, cross-platform way.
//void clearScreen() {
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
//}
//
//// Displays the main menu options.
//void showMenu() {
//    cout << "--- HANGMAN ---" << endl;
//    cout << "1. Play Game" << endl;
//    cout << "2. Add a new Word" << endl;
//    cout << "3. Exit" << endl;
//    cout << "-----------------" << endl;
//    cout << "Choose an option: ";
//}
//
//// Checks if a file exists.
//bool fileExists(const string& filename) {
//    ifstream file(filename);
//    return file.good();
//}
//
//// Helper function to validate word input
//bool isValidWord(const string& word) {
//    if (word.empty()) {
//        return false;
//    }
//    for (int i = 0; i < word.length(); ++i) {
//        if (!isalpha(word[i])) {
//            return false;
//        }
//    }
//    return true;
//}
//
//// Appends a new word, entered by the user, to the words file.
//void addWord() {
//    clearScreen();
//    ofstream file(WORDS_FILE, ios::app);
//
//    if (!file.is_open()) {
//        cout << "Error: Could not open " << WORDS_FILE << " for writing." << endl;
//        cout << "Press Enter to return to menu." << endl;
//        cin.get();
//        return;
//    }
//
//    string newWord;
//    bool valid = false;
//
//    while (!valid) {
//        cout << "Enter a new word to add (letters only, no spaces): ";
//        cin >> newWord;
//        cin.ignore(1000, '\n');
//
//        if (isValidWord(newWord)) {
//            valid = true;
//        }
//        else {
//            cout << "Invalid word. Please enter letters only and no spaces." << endl;
//        }
//    }
//
//    file << newWord << endl;
//    file.close();
//
//    cout << "'" << newWord << "' has been added to the word list." << endl;
//    cout << "Press Enter to return to menu." << endl;
//    cin.get();
//}
//
//// Checks if the words file exists. If not, creates it and prompts
//// the user to add the first word.
//void setupWordsFile() {
//    if (!fileExists(WORDS_FILE)) {
//        cout << "Welcome! The word file '" << WORDS_FILE << "' was not found." << endl;
//        cout << "Creating it now..." << endl;
//
//        ofstream file(WORDS_FILE);
//        file.close();
//
//        cout << "File created. Please add at least one word to start:" << endl;
//        cin.get();
//        addWord();
//    }
//}
//
//// Reads all words from the file and returns one at random.
//string getRandomWord() {
//    vector<string> words;
//    ifstream file(WORDS_FILE);
//
//    if (!file.is_open()) {
//        return "ERROR";
//    }
//
//    string word;
//    while (file >> word) {
//        words.push_back(word);
//    }
//    file.close();
//
//    if (words.empty()) {
//        return "ERROR";
//    }
//
//    int index = rand() % words.size();
//    return words[index];
//}
//
//// Checks if the player has won by seeing if any blanks are left.
//bool checkWin(const string& guessedWord) {
//    for (int i = 0; i < guessedWord.length(); ++i) {
//        if (guessedWord[i] == '_') {
//            return false;
//        }
//    }
//    return true;
//}
//
//// Contains the main loop for playing a single round of Hangman.
//void playGame() {
//    clearScreen();
//    string secretWord = getRandomWord();
//
//    if (secretWord == "ERROR") {
//        cout << "Error: Could not read a word from the file." << endl;
//        cout << "Please add some words using the menu." << endl;
//        cout << "Press Enter to return to menu." << endl;
//        cin.get();
//        return;
//    }
//
//    string guessedWord(secretWord.length(), '_');
//    int mistakesLeft = MAX_MISTAKES;
//    string guessedLetters = "";
//
//    bool gameWon = false;
//    bool gameLost = false;
//
//    while (!gameWon && !gameLost) {
//        clearScreen();
//        cout << "--- HANGMAN ---" << endl;
//        cout << "Mistakes remaining: " << mistakesLeft << endl << endl;
//
//        cout << "Word: ";
//        for (int i = 0; i < guessedWord.length(); ++i) {
//            cout << guessedWord[i] << " ";
//        }
//        cout << endl << endl;
//
//        cout << "Guessed letters: " << guessedLetters << endl;
//        cout << "Enter your guess (a single letter): ";
//
//        string input;
//        char guess;
//        bool validGuess = false;
//
//        while (!validGuess) {
//            cin >> input;
//            cin.ignore(1000, '\n');
//
//            // Check for two conditions:
//            // 1. Is it a single character?
//            // 2. Is that character a letter?
//            if (input.length() == 1 && isalpha(input[0])) {
//                guess = tolower(input[0]);
//                validGuess = true;
//            }
//            else {
//                cout << "Invalid guess. Please enter a single letter: ";
//            }
//        }
//
//        bool alreadyGuessed = false;
//        for (int i = 0; i < guessedLetters.length(); ++i) {
//            if (guessedLetters[i] == guess) {
//                alreadyGuessed = true;
//                break;
//            }
//        }
//
//        if (alreadyGuessed) {
//            cout << "You already guessed that letter! Try again." << endl;
//            cout << "Press Enter to continue." << endl;
//            cin.get();
//            continue;
//        }
//
//        guessedLetters += guess;
//        guessedLetters += " ";
//
//        bool found = false;
//        for (int i = 0; i < secretWord.length(); ++i) {
//            if (tolower(secretWord[i]) == guess) {
//                guessedWord[i] = secretWord[i];
//                found = true;
//            }
//        }
//
//        if (found) {
//            cout << "Good guess!" << endl;
//        }
//        else {
//            cout << "Sorry, that letter isn't in the word." << endl;
//            mistakesLeft--;
//            cout << "You have " << mistakesLeft << " mistakes left." << endl;
//        }
//
//        cout << "Press Enter to continue." << endl;
//        cin.get();
//
//        gameWon = checkWin(guessedWord);
//        if (mistakesLeft == 0) {
//            gameLost = true;
//        }
//    }
//
//    clearScreen();
//    if (gameWon) {
//        cout << "Congratulations! You won!" << endl;
//    }
//    else {
//        cout << "You lose! Better luck next time." << endl;
//    }
//
//    cout << "The word was: " << secretWord << endl;
//    cout << "Press Enter to return to the main menu." << endl;
//    cin.get();
//}
//
//// --- Main Function ---
//
//int main() {
//    srand(static_cast<unsigned int>(time(0)));
//    setupWordsFile();
//
//    bool running = true;
//    while (running) {
//        clearScreen();
//        showMenu();
//
//        int choice;
//        cin >> choice;
//
//      
//        // If cin failed (e.g., user entered 'a' instead of a number)
//        if (cin.fail()) {
//            cin.clear(); // 1. Clear the error state from cin
//            cin.ignore(1000, '\n'); // 2. Clear the bad input (the 'a') from the buffer
//            choice = -1; // 3. Set a default invalid choice to trigger the 'else' block
//        }
//        else {
//            
//            cin.ignore(1000, '\n');
//        }
//      
//
//        if (choice == 1) {
//            playGame();
//        }
//        else if (choice == 2) {
//            addWord();
//        }
//        else if (choice == 3) {
//            running = false;
//            cout << "Goodbye! Thanks for playing." << endl;
//        }
//        else {
//            
//            cout << "Invalid choice. Please press Enter to try again." << endl;
//            cin.get();
//        }
//    }
//
//    return 0;
//}