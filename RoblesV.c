/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
																	Vance Gyan M. Robles, DLSU ID#12279560
*********************************************************************************************************/


#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#define MAX_LENGTH 33
#define MAX_PLAYERS 10
#define MAX_QUESTIONS 30
#define MAX_SENTENCE 151
#define TERMINATE MAX_LENGTH
#define ENTER 13
#define BACKSPACE 8

/* ================================ */
// Type Definitions
typedef char pwd[MAX_LENGTH];
typedef char string20[21];
typedef char string30[31];
typedef char string150[151];

// Structures
typedef struct {

	string20 topic;
	int questionNumber;
	string150 question;
	string30 choice1;
	string30 choice2;
	string30 choice3;
	string30 answer;

}questionData;

typedef struct {

	string20 name;
	int score;

}playerData;

/* ================================ */
// Function Prototypes
void adminPanel();
void playGame();
void viewScores();
void addRecord();
void editRecord();
void deleteRecord();
void importData();
void exportData();
int existingQNACheck();
void sortTopics();
int isInArray();

/* ================================ */
// Text Coloring Functions

//  This function changes the text color to a brighter white
void bold()
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hc, 0xF);
}

//  This function changes the text color to cyan
void cyan()
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hc, 0x3);
}

//  This function changes the text color to green
void green()
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hc, 0xA);
}

//  This function changes the text color to yellow
void yellow()
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hc, 0xE);
}

//  This function changes the text color to red
void red()
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hc, 0xC);
}

//  This function changes the text color to the default white
void reset()
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hc, 0x7);
}


/* ================================ */
// 'Main' Functions

// Base function for getting string inputs that include spaces
void getStrInput(char string[]){
	char ch;
	int i = 0;

	do {
		scanf("%c", &ch);
		if (ch != '\n'){
			string[i] = ch;
			i++;
			string[i] = '\0';
		}
	}while (i < MAX_SENTENCE && ch != '\n');
}

// String input function for strings and hide it the input with asterisks
void getPwdStrInput(char string[]){
	char ch;
	int i = 0;

	do {
		scanf("%c", &ch);
		if (ch != '\n'){
			printf("*");
			string[i] = ch;
			i++;
			string[i] = '\0';
		}
	}while (i < MAX_LENGTH && ch != '\n');
}

/*
// Prototype function for password functionality with hidden input using scanf
void passwordInput(){

	// Variable declarations
	int i;
    int active = 1;
    char input;

	pwd passwordInput;
	pwd correctPassword = "password69";

	while (active == 1){
		printf("Enter your password: ");
		getShortStrInput(passwordInput);

	}
}
*/

// Prototype function for password functionality with hidden input using getch
void passwordPrototype(questionData questions[MAX_QUESTIONS], playerData players[MAX_PLAYERS], int* totalQuestions){
	
	// Variable declarations

     int active = 1;
     char input;
     char exit = '\0';
     pwd passwordInput;
     pwd correctPassword = "password69";
     
     while (active == 1){
		
		int i = 0;
	     printf("Enter your password:\n");
	     
	     // For loop for getting password input
	     while (i < MAX_LENGTH)
	     {
	        // Gets user input and stores each character of the password into the 'passwordInput' string
			input = _getch();
	        passwordInput[i] = input;
	      
	      	// If the input is not the enter key, prints an asterisk and increments by 1

			// If the input is the enter key, the current index will be set to NULL and the loop will terminate
	        if (input == ENTER){
	        	passwordInput[i] = '\0';
	            i = TERMINATE;
			} 

			if (input == BACKSPACE){
	            passwordInput[i] = '\0';
				i--;
				input = '\0';

	           	putchar('\b');
				putchar('\0');
				putchar('\b');

			}
	    	
			else{
				printf("*");
				i++;
			}	
	    }
	    // passwordInput[i] = '\0';
	    
	    // Conditionals to check if inputted password is the same as the correct password
		// If the passwords are the same, the user will be redirected to the admin panel.
	    if (strcmp(passwordInput, correctPassword) == 0){
	    	green(); printf("\nWelcome!\n"); reset();
	    	Sleep(2000);
	    	system("cls");
	    	adminPanel(questions, players, totalQuestions);
	    	active = 0;
	    	
		}
		
		// If the passwords are not the same, the user will be given an option to either exit back to the main menu or try again.
		else{
			red(); printf("\nIncorrect Password!\nPress [1] to return to the Main Menu or press any key to try again.\n"); reset();
			
			exit = _getch();
			if (exit == '1'){
				
				system("cls");
				yellow(); printf("Returning to Main Menu"); 
				Sleep(500); printf(".");
				Sleep(500); printf(".");
				Sleep(500); printf(".");
				Sleep(300);
				reset();
				
				system("cls");
				active = 0;
			}
			
			else{
				system("cls");
			}

	
	
		}
	}
}

// Function that prints the main menu interface.
void displayMainMenu(){

	printf("+-----------------+\n");
	printf("|"); bold(); printf("    Main Menu    "); reset(); printf("|\n");
	printf("+=================+\n");
	printf("|                 |\n");
	printf("|"); green(); printf(" [1] Play        "); reset(); printf("|\n");
	printf("|"); yellow(); printf(" [2] Manage Data "); reset(); printf("|\n");
	printf("|"); red(); printf(" [3] Exit        "); reset(); printf("|\n");
	printf("|                 |\n");
	printf("+-----------------+\n");
	
}

// Function that prints the Admin menu interface.
void displayAdminMenu(){

	printf("+---------------------+\n");
	printf("|"); bold(); printf("     Manage Data     "); reset(); printf("|\n");
	printf("+=====================+\n");
	printf("|                     |\n");
	printf("|"); green(); printf(" [1] Add a Record    "); reset(); printf("|\n");
	printf("|"); yellow(); printf(" [2] Edit a Record   "); reset(); printf("|\n");
	printf("|"); red(); printf(" [3] Delete a Record "); reset(); printf("|\n");
	printf("|"); green(); printf(" [4] Import Data     "); reset(); printf("|\n");
	printf("|"); yellow(); printf(" [5] Export Data     "); reset(); printf("|\n");
	printf("|"); red(); printf(" [6] Exit            "); reset(); printf("|\n");
	printf("|                     |\n");
	printf("+---------------------+\n");

}

// Function that prints the Play menu interface.
void displayPlayMenu(){

	printf("+-----------------+\n");
	printf("|"); bold(); printf("     Welcome!    "); reset(); printf("|\n");
	printf("+=================+\n");
	printf("|                 |\n");
	printf("|"); green(); printf(" [1] Play Game   "); reset(); printf("|\n");
	printf("|"); yellow(); printf(" [2] View Scores "); reset(); printf("|\n");
	printf("|"); red(); printf(" [3] Exit        "); reset(); printf("|\n");
	printf("|                 |\n");
	printf("+-----------------+\n");

}

// Function that handles inputs for the Play menu
void playPanel(questionData questions[MAX_QUESTIONS], playerData players[MAX_PLAYERS]){
	
	char input;
	
	while (input != '3'){
		displayPlayMenu();
		cyan(); printf("\n[Press the number corresponding to your selection.]\n"); reset();
		input = _getch();
		
		switch(input){
			
			case '1':
				system("cls");
				printf("playGame();\n");
				
				break;
				
			case '2':
				system("cls");
				printf("viewScores(); \n");
				
				break;
				
			case '3': // If 'Exit' is chosen, the program is terminated through a return value in the main function.
				system("cls");
				
				break;
			
			default: 
				// If the input is not within the given parameters, 'invalid input' will be displayed and the main menu will be shown again.
				system("cls");
				red(); printf("\nInvalid input. Please select a valid option.\n"); reset();
				break;
				
		}
	}
	
}

// Function that handles inputs for the Manage Data menu
void adminPanel(questionData questions[MAX_QUESTIONS], playerData players[MAX_PLAYERS], int* totalQuestions){

	char input;
	
	while (input != '6'){
		displayAdminMenu();
		cyan(); printf("\n[Press the number corresponding to your selection.]\n"); reset();
		input = _getch();
		
		switch(input){
			
			case '1':
				system("cls");
				addRecord(questions, totalQuestions);
				// printf("Total Questions: %d \n", *totalQuestions);
				
				break;
				
			case '2':
				system("cls");
				editRecord(questions, totalQuestions);
				
				break;

			case '3':
				system("cls");
				deleteRecord();
				printf("deleteRecord(); \n");
				
				break;

			case '4':
				system("cls");
				printf("importData(); \n");
				
				break;

			case '5':
				system("cls");
				printf("exportData(); \n");
				
				break;
			
			case '6': // If 'Exit' is chosen, the program is terminated through a return value in the main function.
				system("cls");
				break;
			
			default: 
				// If the input is not within the given parameters, 'invalid input' will be displayed and the main menu will be shown again.
				system("cls");
				red(); printf("\nInvalid input. Please select a valid option.\n"); reset();
				break;
				
		}
	}
	
}

// Function that handles input for the addRecord function
void addRecord(questionData questions[MAX_QUESTIONS], int* totalQuestions){

	// The increment variable 'i' is initialized to the total number of questions, which at the start of the program is always set to 0
	int i = *totalQuestions;

	string150 tempQuestion;
	string30 tempAnswer;

	// The question and answer will be asked for first, the input will be taken using the getStrInput function.
	printf("Add a question: ");
	getStrInput(tempQuestion);

	printf("Add an answer: ");
	getStrInput(tempAnswer);

	// The questionDuplicate variable will serve as a true or false switch (bool) in order to check if the inputted question and answer pair already exists
	int questionDuplicate = existingQNACheck(questions, tempQuestion, tempAnswer);

	// If the question and answer pair is a duplicate, an error message will be printed and the user will return to the previous menu
	if (questionDuplicate){
		red(); printf("That question and answer already exists!\n"); reset();
	}

	// If the question and answer pair is valid;
	else{

		// The previous inputs will be copied from the temporary variable to their respective struct array child
		strcpy(questions[i].question, tempQuestion);
		strcpy(questions[i].answer, tempAnswer);

		// Continuation of input calls, this time the inputs are directly stored in the struct
		printf("Add a topic: ");
		getStrInput(questions[i].topic);

		printf("Add the first choice: ");
		getStrInput(questions[i].choice1);

		printf("Add the second choice: ");
		getStrInput(questions[i].choice2);

		printf("Add the third choice: ");
		getStrInput(questions[i].choice3);

		// The question number is automatically assigned as the current number of total questions plus one
		printf("Current input is Question #%d\n", *totalQuestions+1);
		questions[i].questionNumber = *totalQuestions + 1;

		// Once the add record is successful, the totalQuestions variable in main will be incremented by one
		*totalQuestions = *totalQuestions + 1;
	}
}

// This fucntion checks if a question-answer pair already exists within the struct
int existingQNACheck(questionData questions[MAX_QUESTIONS], string150 addedQn, string30 addedAns){

	int i;
	int matchQuestion = -1, matchAnswer = -2;

	// For loops will loop through all the questions in the struct to try and find if the input already exists
	for (i = 0; i < MAX_QUESTIONS; i++){
		if (strcmp(questions[i].question, addedQn) == 0){
			/* If the input already exists, its index will be stored in matchQuestion and the for loop will be terminated
			   through assigning the increment i to its maximum value preemptively*/
			matchQuestion = i;
			i = MAX_QUESTIONS;
		}
	}

	for (i = 0; i < MAX_QUESTIONS; i++){
		if (strcmp(questions[i].answer, addedAns) == 0){
			// Same concept as the for loop above
			matchAnswer = i;
			i = MAX_QUESTIONS;
		}
	}

	// If the question-answer pair belongs in the same struct array index, the function will return 1 (true)
	if (matchQuestion == matchAnswer){
		return 1;
	}

	// Else, it returns 0 (false)
	return 0;


}

// Function that handles editing individual question records
void editRecord(questionData questions[MAX_QUESTIONS],  int* totalQuestions){

	// Increment variables
	int i, j;

	// Variables for strings (for input and for storing/sorting topics)
	char input[20];
	int size = *totalQuestions;
	string20 topicsData[size];

	// Checking (bool) variables
	int isUnique, exists;

	// Copies all of the current topics into the topicsData array for local storage
	for (i = 0; i < size; i++){
		 strcpy(topicsData[i], questions[i].topic);
	}

	// Sorts the topics in alphabetical order (Bubble sort)
	sortTopics(topicsData, *totalQuestions);

	// If total questions is greater than 0, proceed
	if (*totalQuestions > 0){

		// The while loop will continue until the user enters '1', or a string that starts with '1'
		while (input[0] != '1'){

			yellow(); printf("Type the Topic to Edit\nEnter [1] to Go Back"); reset();
			green(); printf("\n\nAvailable Topics:\n"); reset();

			// This loop will scan the topicsData array for duplicate topics, if the topic is a duplicate and is already displayed, it will skip printing it
			for (i = 0; i < size; i++) {
			
				isUnique = 1;
			
				for (j = 0; j < i; j++) {
					if (strcmp(topicsData[i], topicsData[j]) == 0) {
						isUnique = 0;
					}
				}

				if (isUnique) {
					printf("%s\n", topicsData[i]);
				}
			}

			// Gets user input, will be case sensitive
			printf(">> ");
			scanf("%s", input);
			exists = 0;

			// This loop will scan the topicsData array if the input exists
			for (i = 0; i < *totalQuestions; i++){
				if (strcmp(input, topicsData[i]) == 0){
					exists = 1;
				}
			}

			// If the input exists, continue
			if (exists == 1){
				
				// Variable for question number input
				int numInput;
				
				// Variable for checking how many Questions a certain topic has
				int topicQns = 0;
				for (i = 0; i < *totalQuestions; i++){
					if (strcmp(input, questions[i].topic) == 0){
						topicQns++;
					}
				}
				int validNums[topicQns]; 

				int k = 0;

				printf("Question Numbers Associated with the Topic:\n"); 

				// Looks through the questions struct array for the question numbers associated with the inputted topic and stores them in the validNums array
				for (i = 0; i < *totalQuestions; i++){
					if (strcmp(input, questions[i].topic) == 0){
						printf("Question #[%d]\n", questions[i].questionNumber);
						validNums[k] = questions[i].questionNumber;
						k++;
					}
				}

				while (isInArray(validNums, numInput, topicQns) == 0){
					printf(">> ");
					scanf("%d", &numInput);
					if (isInArray(validNums, numInput, topicQns) == 0){
						red(); printf("Invalid Input!\n"); reset();
					}
				}

				int editInput;
				printf("Current Record:\n");
				printf("Question Number: %d\n", questions[numInput - 1].questionNumber);
				printf("[1] Topic: %s\n", questions[numInput - 1].topic);
				printf("[2] Question: %s\n", questions[numInput - 1].question);
				printf("[3] Choice 1: %s\n", questions[numInput - 1].choice1);
				printf("[4] Choice 2: %s\n", questions[numInput - 1].choice2);
				printf("[5] Choice 3: %s\n", questions[numInput - 1].choice3);
				printf("[6] Answer: %s\n", questions[numInput - 1].answer);

				while (editInput > 8 || editInput < 1){
					printf(">> ");
					scanf("%d", &editInput);
					switch(editInput){
						case 1:
							printf("Input New [Topic]: ");
							getStrInput(questions[numInput - 1].topic);
							break;
						case 2:
							printf("Input New [Question]: ");
							getStrInput(questions[numInput - 1].question);
							break;
						case 3:
							printf("Input New [Choice 1]: ");
							getStrInput(questions[numInput - 1].choice1);
							break;
						case 4:
							printf("Input New [Choice 2]: ");
							getStrInput(questions[numInput - 1].choice2);
							break;
						case 5:
							printf("Input New [Choice 3]: ");
							getStrInput(questions[numInput - 3].choice3);
							break;
						case 6:
							printf("Input New [Answer]: ");
							getStrInput(questions[numInput - 1].answer);
							break;
						default:
							break;
					}
					green(); printf("Changes Saved!"); reset();
				}


			}

			/* If it does not exist, prompt the user to enter a valid input again;
				second conditional is to prevent error message from appearing if user wants to exit */
			else if (exists == 0 && input[0] != '1'){
				red(); printf("Invalid Input!\n"); reset();
			}
		}
	}

	// If total questions are 0, an error message will be shown
	else{
		red(); printf("No questions found!\n"); reset();
	}
};

void deleteRecord(questionData questions[MAX_QUESTIONS]){

};

// Sorts a string array in alphabetical order, this function uses the Bubble sort algorithm butfor strings (uses strcpy instead of assignment operations)
void sortTopics(string20 topics[], int size){

	string20 temp;
	int i, j;

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (strcmp(topics[i], topics[j]) > 0) {
                strcpy(temp, topics[i]);
                strcpy(topics[i], topics[j]);
                strcpy(topics[j], temp);
            }
        }
    }

}

// Function that scans an integer array, returns 1 if int val is in array, returns 0 if not
int isInArray(int arr[], int val, int size){

	int i;
	for (i = 0; i < size; i++){
		if (arr[i] == val){
			return 1;
		}
	}
	return 0;

}

/* ================================ */

int main(){
	

	char input;
	int totalQuestions = 0, totalPlayers = 0;
	questionData questions[MAX_QUESTIONS];
	playerData players[MAX_PLAYERS];

	while (input != '3'){
		
		displayMainMenu();
		cyan(); printf("\n[Press the number corresponding to your selection.]\n"); reset();
		input = _getch();
		
		switch(input){
			
			case '1':
				system("cls");
				playPanel(questions, players);
		
				break;
				
			case '2':
				system("cls");
				passwordPrototype(questions, players, &totalQuestions);
				
				break;
				
			case '3': // If 'Exit' is chosen, the program is terminated through a return value in the main function.
				printf("Thank you for playing!");
				
				break;
			
			default: 
				// If the input is not within the given parameters, 'invalid input' will be displayed and the main menu will be shown again.
				system("cls");
				red(); printf("\nInvalid input! Please select a valid option.\n\n"); reset();
				break;
				
		}
	}
	
	
	

	return 0;
	
}



