#include <iostream>
#include <string>
#include <fstream>

const int MAXARRSIZE = 1024;

int intro();
void loadDataHand(std::string[], int[]);

int main() {
	std::string studentNames[MAXARRSIZE];
	int studentScores[MAXARRSIZE];
	std::ifstream inputFile;
	std::ofstream outputFile;
	int handOrFile;

	handOrFile = intro();

	if (handOrFile == 1) {
		loadDataHand(studentNames, studentScores);
	}
	else if (handOrFile == 2) {

	}

	system("pause");
	return 0;
}

int intro() {
	int userResponse;

	std::cout << "Hello! I will help you keep track of your students' test scores." << std::endl;
	std::cout << "Please follow instructions as they appear on the prompt." << std::endl;

	std::cout << "First, please let me know whether you would like to input student data" << std::endl;
	std::cout << "by hand or by uploading a file. Type 1 if by hand or 2 if through a file: ";

	std::cin >> userResponse;

	std::cout << std::endl;

	while (userResponse < 1 || userResponse > 2) {
		std::cout << "Please provide a valid response, and type 1 whether you would like to" << std::endl;
		std::cout << "input student data by hand or 2 if you would prefer to upload it: ";

		std::cin >> userResponse;

		std::cout << std::endl;
	}

	return userResponse;
}

void loadDataHand(std::string arr1[], int arr2[]) {
	int numScores;
	std::string name;
	int grade;

	std::cout << "Thank you. First, please let me know how many test scores there are: ";
	std::cin >> numScores;

	std::cout << std::endl;

	while (numScores < 1 || numScores > 1024) {
		std::cout << "Sorry, I can only accept a min value of 1 and max value of 1024." << std::endl;
		std::cout << "Please let me know how many test scores there will be today: ";

		std::cin >> numScores;

		std::cout << std::endl << std::endl;
	}

	for (int i = 0; i < numScores; i++) {
		std::cout << "Please enter student " << i + 1 << "'s full name in the format" << std::endl;
		std::cout << "firstname lastname: ";

		std::cin.ignore();
		std::getline(std::cin, name);

		arr1[i] = name;

		std::cout << std::endl;

		std::cout << "Thanks! Now, please enter their test grade: ";
		std::cin >> grade;

		while (grade < 0 || grade > 100) {
			std::cout << std::endl;

			std::cout << "Please enter a valid test grade: ";
			std::cin >> grade;
		}

		arr2[i] = grade;

		std::cout << std::endl << std::endl;
	}
}