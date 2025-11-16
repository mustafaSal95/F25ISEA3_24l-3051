//#include <iostream>
//#include <vector>
//#include <conio.h>
//using namespace std;
//
////function to separate comma separated words from a string into a vector of strings
//vector<string> separateWords(const string& str) {
//	vector<string> words;
//	string word;
//	for (char ch : str) {
//		if (ch == ',') {
//			if (!word.empty()) {
//				words.push_back(word);
//				word.clear();
//			}
//		} else {
//			word += ch;
//		}
//	}
//	if (!word.empty()) {
//		words.push_back(word);
//	}
//	return words;
//}
//
////function that takes a vector of strings and checks if each string is a palindrome
//void checkPalindromes(const vector<string>& words) {
//	for (const string& word : words) {
//		string reversedWord = word;
//		reverse(reversedWord.begin(), reversedWord.end());
//		if (word == reversedWord) {
//			cout << word << " is a palindrome." << endl;
//		} else {
//			cout << word << " is not a palindrome." << endl;
//		}
//	}
//}
////main function to test the above functions keeps running till user presses escape key
//int main() {
//	cout << "Press ESC to exit." << endl;
//
//	while (true) {
//		cout << "Enter comma separated words: ";
//		string input;
//		char ch;
//
//		// Read input character-by-character so ESC can be detected at any time.
//		while (true) {
//			ch = _getch(); // blocks until a key is pressed
//			if (ch == 27) { // ESC
//				return 0;
//			}
//			if (ch == '\r') { // Enter  ends the current input
//				cout << endl;
//				break;
//			}
//			
//			input.push_back(ch);
//			cout << ch;
//		}
//
//		// If user just pressed Enter with no content, prompt again
//		if (input.empty()) continue;
//
//		vector<string> words = separateWords(input);
//		checkPalindromes(words);
//	}
//	
//}
//
//
