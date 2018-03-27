#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

// global const for max array size
const int MAXARRSIZE = 1024;

// function prototypes
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

// main()
int main() {
	// string array to hold student names
	std::string studentNames[MAXARRSIZE];
	// int array to hold student scores
	int studentScores[MAXARRSIZE];
	// strings to hold input and output file locations
	std::string inputLoc, outputLoc;
	/* ints to hold user decision on how to give data to the program, the amount of
	name and test score pairs in the inpout file, the lowest test score in the
	int array and the highest score in the int array */
	int handOrFile, numInFile, lowestScore, highestScore;
	// double to hold the average of the test scores in the int array
	double avgScore;
	// ifstream object for input file
	std::ifstream inputFile;
	// ofstream object for output file
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

/* inform user of program's functionality, return result of wether they want to enter data manually
or upload a file with data. Send response back to main in the form of an int and store in handOrFile
variable */
int intro() {
	// int to hold user response (manually enter data or upload file)
	int userResponse;

	std::cout << "\n   Hello! I will help you keep track of your students' test scores." << std::endl;
	std::cout << "   Please follow instructions as they appear on the prompt." << std::endl;

	std::cout << "   First, please let me know whether you would like to input student data" << std::endl;
	std::cout << "   by hand or by uploading a file. Type 1 if by hand or 2 if through a file: ";

	std::cin >> userResponse;

	std::cout << std::endl;

	while (userResponse < 1 || userResponse > 2) {
		std::cout << "   Please provide a valid response, and type 1 whether you would like to" << std::endl;
		std::cout << "   input student data by hand or 2 if you would prefer to upload it: ";

		std::cin >> userResponse;

		std::cout << std::endl;
	}

	return userResponse;
}

/* if user selects to input data manually, then this function will guide them through it*/
void loadDataHand(std::string arr1[], int arr2[]) {
	// int to hold the number of test scores that will be entered
	int numScores;
	// string to hold student's name
	std::string name;
	// int to hold student's test score
	int grade;

	std::cout << "   Thank you. First, please let me know how many test scores there are: ";
	std::cin >> numScores;

	std::cout << std::endl;

	while (numScores < 1 || numScores > MAXARRSIZE) {
		std::cout << "   Sorry, I can only accept a min value of 1 and max value of 1024." << std::endl;
		std::cout << "   Please let me know how many test scores there will be today: ";

		std::cin >> numScores;

		std::cout << std::endl << std::endl;
	}

	for (int i = 0; i < numScores; i++) {
		std::cout << "   Please enter student " << i + 1 << "'s full name in the format" << std::endl;
		std::cout << "   firstname lastname: ";

		std::cin.ignore();
		std::getline(std::cin, name);

		arr1[i] = name;

		std::cout << std::endl;

		std::cout << "   Thanks! Now, please enter their test grade: ";
		std::cin >> grade;

		while (grade < 0 || grade > 100) {
			std::cout << std::endl;

			std::cout << "   Please enter a valid test grade: ";
			std::cin >> grade;
		}

		arr2[i] = grade;

		std::cout << std::endl << std::endl;
	}
}
/* if user selects to upload data through a file, get the location of the file and return it to main
so the path may be stored and used in inputLoc */
std::string inputPath() {
	// string to hold the input file's path
	std::string inputLocation;

	std::cout << "   You have chosen the option of uploading a file with student data/scores." << std::endl;
	std::cout << "   It should be in the following format: the first line should contain the" << std::endl;
	std::cout << "   number of test scores. The second line should be an individual" << std::endl;
	std::cout << "   student's first and last name, and the third will hold their score." << std::endl;
	std::cout << "   The alternating student name and score pattern should repeat until all" << std::endl;
	std::cout << "   names and grades have been filled." << std::endl;

	std::cout << std::endl;

	std::cout << "   First, please enter the path to the file:";

	std::cin >> inputLocation;

	return inputLocation;
}

/* open the input file and catch any errors*/
void openInput(std::ifstream &inFile, std::string name) {
	inFile.open(name.c_str());

	while (inFile.fail()) {
		std::cout << "\n\n   ERROR: Cannot open file. Please provide the correct path: ";
		std::cin >> name;
		inFile.open(name.c_str());
	}
}

/* read data from input file into the appropriate arrays, and return the number of
test scores to main */
int loadDataFile(std::string arr1[], int arr2[], std::ifstream &inFile) {
	// string variable will hold the student name from every other line in the input file
	std::string studentName;
	// ints to hold the total number of scores in the file, and to hold the test scores
	int numTestScores, testScore;

	inFile >> numTestScores;
	inFile.ignore();

	if (numTestScores > MAXARRSIZE) {
		std::cout << "   I'm sorry, but only up to " << MAXARRSIZE << " test scores may be uploaded!" << std::endl;
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

			std::cout << "   The score for " << studentName << " is invalid. Please enter a valid test grade: ";
			std::cin >> testScore;
			std::cin.ignore();
		}

		arr2[i] = testScore;
	}

	inFile.close();
	std::cout << std::endl << std::endl;

	return numTestScores;
}

/* find lowest test score now stored in the int array */
int lowScore(int arr[], int num) {
	// set the low score to equal the first element in int array
	int lowestScore = arr[0];

	for (int i = 0; i < num; i++) {
		if (arr[i] < lowestScore) {
			lowestScore = arr[i];
		}
	}

	return lowestScore;
}

/* find highest test score now stored in the int array */
int highScore(int arr[], int num) {
	// set the high score to equal the first element in int array
	int highScore = arr[0];

	for (int i = 0; i < num; i++) {
		if (arr[i] > highScore) {
			highScore = arr[i];
		}
	}

	return highScore;
}

/* find average test score of the int array */
double averageScore(int arr[], int num) {
	// int variable to hold the total of all test scores
	int total = 0;
	// double to store the calculated average
	double average;

	for (int i = 0; i < num; i++) {
		total += arr[i];
	}

	average = (double)total / num;

	return average;
}

/* inform user that data will be analyzed and the analysis will be stored in an output file.
ask the user where they would like to store the analysis */
std::string outputPath() {
	// string variable to hold output path
	std::string outputLocation;

	std::cout << "   Now, I will create an output file for the data you have provided." << std::endl;
	std::cout << "   Please enter the name/path of this file, so it can be saved: ";
	std::cin >> outputLocation;

	std::cout << std::endl << std::endl;

	return outputLocation;
}

/* open the new output file */
void openOutput(std::ofstream &outFile, std::string name) {
	outFile.open(name.c_str());

	while (outFile.fail()) {
		std::cout << "\n\n   ERROR: Cannot save file to specified location. Please provide the correct path: ";
		std::cin >> name;
		outFile.open(name.c_str());

		std::cout << std::endl << std::endl;
	}
}

/* display the output in console output as well save it to the output file */
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

	outputFile.close();

	std::cout << std::endl << std::endl;
}