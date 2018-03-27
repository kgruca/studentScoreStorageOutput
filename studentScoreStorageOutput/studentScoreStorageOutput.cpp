#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

const int MAXARRSIZE = 1024;

int intro();
void loadDataHand(std::string[], int[]);
std::string inputPath();
void openInput(std::ifstream &, std::string);
int loadDataFile(std::string[], int[], std::ifstream &);
int lowScore(int[], int);
int highScore(int[], int);
double averageScore(int[], int);
std::string outputPath();
void openOutput(std::ofstream &, std::string);
void output(std::string[], int[], std::ofstream &, int, int, int, double);

int main() {
	std::string studentNames[MAXARRSIZE];
	std::string inputLoc, outputLoc;
	int studentScores[MAXARRSIZE];
	int handOrFile, numInFile, lowestScore, highestScore;
	double avgScore;
	std::ifstream inputFile;
	std::ofstream outputFile;

	handOrFile = intro();

	if (handOrFile == 1) {
		loadDataHand(studentNames, studentScores);
	}
	else if (handOrFile == 2) {
		inputLoc = inputPath();

		openInput(inputFile, inputLoc);

		numInFile = loadDataFile(studentNames, studentScores, inputFile);
	}

	lowestScore = lowScore(studentScores, numInFile);

	highestScore = highScore(studentScores, numInFile);

	avgScore = averageScore(studentScores, numInFile);

	outputLoc = outputPath();

	openOutput(outputFile, outputLoc);

	output(studentNames, studentScores, outputFile, numInFile, lowestScore, highestScore, avgScore);

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

	while (numScores < 1 || numScores > MAXARRSIZE) {
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

std::string inputPath() {
	std::string inputLocation;

	std::cout << "You have chosen the option of uploading a file with student data/scores." << std::endl;
	std::cout << "It should be in the following format: the first line should contain the" << std::endl;
	std::cout << "number of test scores. The second line should be an individual" << std::endl;
	std::cout << "student's first and last name, and the third will hold their score." << std::endl;
	std::cout << "The alternating student name and score pattern should repeat until all" << std::endl;
	std::cout << "names and grades have been filled." << std::endl;

	std::cout << std::endl;

	std::cout << "First, please enter the path to the file that contains test score data:" << std::endl;

	std::cin >> inputLocation;

	return inputLocation;
}

void openInput(std::ifstream &inFile, std::string name) {
	inFile.open(name.c_str());

	while (inFile.fail()) {
		std::cout << "\n\nERROR: Cannot open file. Please provide the correct path: ";
		std::cin >> name;
		inFile.open(name.c_str());
	}
}

int loadDataFile(std::string arr1[], int arr2[], std::ifstream &inFile) {
	std::string studentName;
	int numTestScores, testScore;

	inFile >> numTestScores;
	inFile.ignore();

	if (numTestScores > MAXARRSIZE) {
		std::cout << "I'm sorry, but only up to " << MAXARRSIZE << " test scores may be uploaded!" << std::endl;
		numTestScores = MAXARRSIZE;
	}

	std::cout << std::endl;

	for (int i = 0; i < numTestScores; i++) {
		getline(inFile, studentName);

		arr1[i] = studentName;

		inFile >> testScore;
		inFile.ignore();

		while (testScore < 0 || testScore > 100) {
			std::cout << std::endl;

			std::cout << "The score for " << studentName << " is invalid. Please enter a valid test grade: ";
			std::cin >> testScore;
		}

		arr2[i] = testScore;
	}

	inFile.close();
	std::cout << std::endl << std::endl;

	return numTestScores;
}

int lowScore(int arr[], int num) {
	int lowestScore = arr[0];

	for (int i = 0; i < num; i++) {
		if (arr[i] < lowestScore) {
			lowestScore = arr[i];
		}
	}

	return lowestScore;
}

int highScore(int arr[], int num) {
	int highScore = arr[0];

	for (int i = 0; i < num; i++) {
		if (arr[i] > highScore) {
			highScore = arr[i];
		}
	}

	return highScore;
}

double averageScore(int arr[], int num) {
	int total = 0;
	double average;

	for (int i = 0; i < num; i++) {
		total += arr[i];
	}

	average = (double)total / num;

	return average;
}

std::string outputPath() {
	std::string outputLocation;

	std::cout << "Now, I will create an output file for the data you have provided." << std::endl;
	std::cout << "Please enter the name/path of this file, so it can be saved: ";
	std::cin >> outputLocation;

	std::cout << std::endl << std::endl;

	return outputLocation;
}

void openOutput(std::ofstream &outFile, std::string name) {
	outFile.open(name.c_str());

	while (outFile.fail()) {
		std::cout << "\n\nERROR: Cannot save file to specified location. Please provide the correct path: ";
		std::cin >> name;
		outFile.open(name.c_str());

		std::cout << std::endl << std::endl;
	}
}

void output(std::string arr1[], int arr2[], std::ofstream &outputFile, int num, int low, int high, double avg) {
	std::cout << "\tNumber of scores = " << num << std::endl;
	outputFile << "\tNumber of scores = " << num << std::endl;
	std::cout << "\tLowest score = " << low << std::endl;
	outputFile << "\tLowest score = " << low << std::endl;
	std::cout << "\tHighest score = " << high << std::endl;
	outputFile << "\tHighest score = " << high << std::endl;
	std::cout << "\tMean score = " << std::setprecision(2) << std::fixed << avg << std::endl;
	outputFile << "\tMean score = " << std::setprecision(2) << std::fixed << avg << std::endl;

	std::cout << std::endl;
	outputFile << std::endl;

	std::cout << "\tName\t\tScore\tIsLowest\tIsHighest\t>=Mean" << std::endl;
	outputFile << "\tName\t\tScore\tIsLowest\tIsHighest\t>=Mean" << std::endl;
	std::cout << "\t--------------------------------------------------------------" << std::endl;
	outputFile << "\t--------------------------------------------------------------" << std::endl;

	for (int i = 0; i < num; i++) {
		std::cout << "\t" << arr1[i] << "\t" << arr2[i];
		outputFile << "\t" << arr1[i] << "\t" << arr2[i];
		if (arr2[i] == low) {
			std::cout << "\tY";
			outputFile << "\tY";
		}
		else {
			std::cout << "\tN";
			outputFile << "\tN";
		}
		if (arr2[i] == high) {
			std::cout << "\t\tY";
			outputFile << "\t\tY";
		}
		else {
			std::cout << "\t\tN";
			outputFile << "\t\tN";
		}
		if (arr2[i] >= avg) {
			std::cout << "\t\tY";
			outputFile << "\t\tY";
		}
		else {
			std::cout << "\t\tN";
			outputFile << "\t\tN";
		}
		std::cout << std::endl;
		outputFile << std::endl;
	}

	std::cout << std::endl << std::endl;
}