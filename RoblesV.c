/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
																	Vance Gyan M. Robles, DLSU ID#12279560
*********************************************************************************************************/

	/* TO DO:
		- CLEANUP
		- REPLACE MANUAL DISPLAY TOPICS IN ADMIN FUCNTIONS WITH 'displayTopics()' FUNCTION
		- OPTIMIZE RANDOMIZER
		- TEST SCRIPT
		- PARAMETERS IN COMMENTS

	   Done:
	   	- QUIZ GAME PROPER
		- RANDOMIZE QUESTIONS
		- ACCUMULATE SCORE
		- FIX AUTOMATIC NUMBERING v2 (SHOULD BE SEPARATE FOR EACH TOPIC, NOT UNIVERSAL) APPLICABLE TO MANUAL ADDING OF RECORD ONLY
		- FIX DELETE FUNCTION TO ACCOUNT FOR NEW NUMBERING
		- FIX EDIT FUNCTION TO ACCOUNT FOR NEW NUMBERING
		- IMPORT, EXPORT, VIEW SCORES


	*/

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
int getHighest();
void sortQuestions();
int genRandInt();

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


// Function that scans through an integer array and returns the highest integer
int getHighest(int arr[], int size){

	// Variable declarations
	int i;
	int max = 0;

	for (i = 0; i < size; i++){
		if(arr[i] > arr[max]){
			max = i;
		}
	}

	return arr[max];
}

// Function that sorts an array of question structs based on topic, then question number, using bubble sort
void sortQuestions(questionData questions[MAX_QUESTIONS], int totalQuestions) {
    int i, j, k, l;
	int size = totalQuestions;
    questionData temp;
    
    // Sort based on topic in alphabetical order
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (strcmp(questions[i].topic, questions[j].topic) > 0) {
                // Swaps the two questions
                temp = questions[i];
                questions[i] = questions[j];
                questions[j] = temp;
            }
        }
    }
    
    // Sort based on question number in increasing order (within each topic group)
    i = 0;
    while (i < size) {
        j = i;
        while (j < size && strcmp(questions[i].topic, questions[j].topic) == 0) {
            j++;
        }
        // Sort the questions with the same topic from i to j-1
        for (k = i; k < j - 1; k++) {
            for (l = k + 1; l < j; l++) {
                if (questions[k].questionNumber > questions[l].questionNumber) {
                    // Swaps the two questions
                    temp = questions[k];
                    questions[k] = questions[l];
                    questions[l] = temp;
                }
            }
        }
        i = j;
    }
}

// Prototype function for password functionality with hidden input using getch
void passwordPrototype(questionData questions[MAX_QUESTIONS], playerData players[MAX_PLAYERS], int* totalQuestions, int* totalPlayers){
	
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
	    	adminPanel(questions, players, totalQuestions, totalPlayers);
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
void playPanel(questionData questions[MAX_QUESTIONS], playerData players[MAX_PLAYERS], int *totalPlayers, int *totalQuestions){
	
	char input;
	
	while (input != '3'){
		displayPlayMenu();
		cyan(); printf("\n[Press the number corresponding to your selection.]\n"); reset();
		input = _getch();
		
		switch(input){
			
			case '1':
				system("cls");
				playGame(questions, players, totalPlayers, totalQuestions);
				
				break;
				
			case '2':
				system("cls");
				viewScores(players, totalPlayers);
				
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

// Function for generating a random integer between a set range
int genRandInt(int min, int max){

	// The random number generator is seeded with the current time;
	srand(time(NULL)); 

	// The function returns a random number in the range [min, max]
    return min + rand() % (max - min + 1); 
}

void displayTopics(questionData questions[MAX_QUESTIONS], int *totalQuestions){

	int i, j, isUnique;
	int size = *totalQuestions;

	green(); printf("Available Topics:\n"); reset();
	for (i = 0; i < size; i++) {
			
		isUnique = 1;
			
		for (j = 0; j < i; j++) {
			if (strcmp(questions[i].topic, questions[j].topic) == 0) {
				isUnique = 0;
			}
		}

		if (isUnique) {
			printf("%s\n", questions[i].topic);
		}
	}


}

// Function for playing the quiz game
void playGame(questionData questions[MAX_QUESTIONS], playerData players[MAX_PLAYERS], int *totalPlayers, int *totalQuestions){
	
	// increment variables
	int i = *totalPlayers, j;

	// variable for score, for determining game over, and to store randomly generated int
	int score = 0, over = 0, current;

	// variable for checking if inputted topic exists
	int exists;

	// variable for user input of topic
	string20 input;

	// variable for user input of answer choice, and temporary storage of user's answer string
	char choice;
	string30 tempAns;

	// array of bool ints to determine if a question at a certain index has already been answered
	int isAnswered[MAX_QUESTIONS];
	// all current questions will be set to isAnswered[j] = 0 (false) at the start
	for (j = 0; j < *totalQuestions; j++){
		isAnswered[j] = 0;
	}
	
	// array to store valid indexes of questions within a topic
	int validQns[MAX_QUESTIONS];
	// counting variables for answered questions, total questions in a topic, and total unanswered questions in a topic
	int totalAnswered = 0, totalTopic, totalTopicUnanswered;

	// if totalQuestions in main is 0, show an error message
	if (*totalQuestions < 1){
		red(); printf("No questions found!\n"); reset();
	}
	// else, continue
	else{

		green(); printf("Questions found!\n"); reset();
		// asks player to input their name
		yellow(); printf("Enter Your Name: "); reset();
		scanf(" %[^\n]s", players[i].name);
		green(); printf("Welcome [%s]!\n", players[i].name); reset();

		//*totalPlayers = *totalPlayers + 1;

		// the loop will continue until the game is over (over == 1)
		while (over != 1){
			
			// initialized to 0
			exists = 0;

			// keeps asking user for topic input until a valid topic has been entered
			while (exists == 0){

				printf("Current Score: ");
				green(); printf("%d\n", score);
				yellow(); printf("\nType the Topic to Answer From\n"); reset();
				displayTopics(questions, totalQuestions);

				printf("\nSelect a Topic\n");
				printf(">> ");
				scanf(" %[^\n]s", input);
			
				// scans the topic of all questions, if input has been found within the struct array, exists will be set to 1 and loop will terminate
				for (j = 0; j < *totalQuestions; j++){
					if (strcmp(input, questions[j].topic) == 0){
						exists = 1;
					}
				}

				// else, prints an error message
				if (exists == 0){
					system("cls");
					red(); fprintf(stderr, "Invalid topic!\n"); reset();
				}
			}

			printf("Total Questions Answered: %d\n", totalAnswered);

			// total topics will be initialized to 0
			totalTopic = 0;

			// the struct array will be scanned for topics which matches the input;
			// if found, the index of the struct with that topic will be stored in validQns, and totalTopic will be incremented
			for (j = 0; j < *totalQuestions; j++){
				if (strcmp(input, questions[j].topic) == 0){
					validQns[totalTopic] = j;
					totalTopic++;
				}
			}
			printf("Total Number of Questions in Topic: %d\n", totalTopic);
			
			// total unanswered questions in a certain topic will be initialized to 0;
			// if the corresponding isAnswered value of a valid question is 0, total unanswered will be incremented
			totalTopicUnanswered = 0;
			for (j = 0; j < totalTopic; j++){
				if (isAnswered[validQns[j]] == 0){
					totalTopicUnanswered++;
				}
			}

			// if total unanswered questions reaches 0, an error message will be shown and the user will be redirected to choose another topic
			if (totalTopicUnanswered == 0){
				system("cls");
				red(); printf("No more unanswered questions in this topic!\nPlease select another topic.\n"); reset();
			}

			// else, continue;
			else{
				printf("Total Number of Unanswered in Topic: %d\n", totalTopicUnanswered);

				// current will be a random integer from 0 to (totalTopic - 1) inclusive;
				// this range will generate an index for accessing validQns
				// then, the corresponding value from validQns[current] will be used as the index for the question to be played
				current = genRandInt(0, totalTopic - 1);

				// if the randomly generated index is already answered, randomize will reroll until an unanswered question's index is found
				while (isAnswered[validQns[current]] == 1){
					current = genRandInt(0, totalTopic - 1);
				}
				printf("Random Number: %d\n", validQns[current]);
				// prints the current question data and presents the user with a choice
				printf("%s\n[1] %s\n[2] %s\n[3] %s\n[4] Quit\n", questions[validQns[current]].question, questions[validQns[current]].choice1, questions[validQns[current]].choice2, questions[validQns[current]].choice3);
				printf(">> ");

				// choice will be set to '0' as a buffer
				choice = '0';

				// continually asks user for input until a valid input has been chosen (from '1' to '4')
				// '1' will be choice1 and so on, '4' will be an option to quit the game from the current question
				while (choice > '4' || choice < '1'){
					scanf(" %c", &choice);
					switch (choice){
						case '1':
							strcpy(tempAns, questions[validQns[current]].choice1);
							break;
						case '2':
							strcpy(tempAns, questions[validQns[current]].choice2);
							break;
						case '3':
							strcpy(tempAns, questions[validQns[current]].choice3);
							break;
						case '4':
							over = 1;
							system("cls");
							printf("Final Score: ");
							green(); printf("%d\n", score); reset();
							players[i].score = score;
							*totalPlayers = *totalPlayers + 1; // totalPlayers will be incremented once a session is complete
							break;
						default:
							red(); printf("Invalid Input!"); reset();
							break;
					}
				}

				// if tempAns matches the .answer of the currennt question, score will be incremented
				if (strcmp(tempAns, questions[validQns[current]].answer) == 0){
					system("cls");
					green(); printf("Correct Answer!\n"); reset();
					score++;
				}

				// else, prints a fail message
				else{
					if (over != 1){
						system("cls");
						red(); printf("Incorrect Answer!\n"); reset();
					}
						
				}

				// the current question's isAnswered value will be set to 1 (true) so that it will not be chosen for the next time
				isAnswered[validQns[current]] = 1;

				// value for total answered question will be incremented
				totalAnswered++;

				// if the total number of answered questions is equal to the total number of questions,
				// the game will automatically be over and the final score will be displayed
				if (totalAnswered == *totalQuestions){
					over = 1;
					printf("All questions answered.\nFinal Score: %d\n", score);
					players[i].score = score;
					*totalPlayers = *totalPlayers + 1; // totalPlayers will be incremented once a session is complete
				}

				// user is redirected back to choosing a topic at the end if the condition for ending the game is not met
			}
		}
	}



}

// Function that sorts the playerData struct array based on scores
void sortScores(playerData players[MAX_PLAYERS], int size){

	int i, j;
    playerData temp;
    
    // Sorts based on score in descending order
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (players[j].score > players[i].score) {
                // Swap the two questions
                temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

}

// Function for the 'View Scores' option that displays all saved player scores
void viewScores(playerData players[MAX_PLAYERS], int* totalPlayers){

	int i;
	sortScores(players, *totalPlayers);
	printf("+======+======================+=======+\n");
	printf("|             Leaderboard             |\n");
	printf("+======+======================+=======+\n");
	printf("| Rank |         Name         | Score |\n");
	printf("+------+----------------------+-------+\n");
	for (i = 0; i < *totalPlayers; i++){
		printf("|%-6d|%-22s|%-7d|\n", i + 1, players[i].name, players[i].score);
		printf("+------+----------------------+-------+\n");
	}
	printf("\n");

}

// Function that handles inputs for the Manage Data menu
void adminPanel(questionData questions[MAX_QUESTIONS], playerData players[MAX_PLAYERS], int* totalQuestions, int *totalPlayers){

	char input;
	int j;
	
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
				deleteRecord(questions, totalQuestions);
				
				break;

			case '4':
				system("cls");
				importData(questions, totalQuestions, players, totalPlayers);
				
				break;

			case '5':
				system("cls");
				exportData(questions, totalQuestions, players, totalPlayers);
				
				break;
			
			case '6': // If 'Exit' is chosen, the program is terminated through a return value in the main function.
				system("cls");
				break;
			
			case '7': // Prints the entire questions struct (debugging)
				for (j = 0; j < *totalQuestions; j++){
					printf("%s\n", questions[j].topic);
					printf("%d\n", questions[j].questionNumber);
					printf("%s\n", questions[j].question);
					printf("%s\n", questions[j].choice1);
					printf("%s\n", questions[j].choice2);
					printf("%s\n", questions[j].choice3);
					printf("%s\n", questions[j].answer);
					
					printf("\n");
				}
				printf("Total Questions: %d\n", *totalQuestions);

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
	// Increment variable j is used in the for loop to store question numbers
	int i = *totalQuestions, j;

	// Variables for handling question number allocation
	int tempQnNumber = 1;
	// int highest;

	/*
	int currentQnNumbers[i];
	for (j = 0; j < *totalQuestions; j++){
		// This loop will store all current question numbers to the local array
		currentQnNumbers[j] = questions[j].questionNumber;
	}*/

	string150 tempQuestion;
	string30 tempAnswer;
	string20 tempTopic;

	// The question and answer will be asked for first, the input will be taken using the getStrInput function.
	printf("Add a question: ");
	scanf(" %[^\n]s", tempQuestion);

	printf("Add an answer: ");
	scanf(" %[^\n]s", tempAnswer);

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
		scanf(" %[^\n]s", tempTopic);
		for (j = 0; j < *totalQuestions; j++){
			if (strcmp(tempTopic, questions[j].topic) == 0){
				tempQnNumber++;
			}
		}
		strcpy(questions[j].topic, tempTopic);
		questions[i].questionNumber = tempQnNumber;

		printf("Add the first choice: ");
		scanf(" %[^\n]s", questions[i].choice1);

		printf("Add the second choice: ");
		scanf(" %[^\n]s", questions[i].choice2);

		printf("Add the third choice: ");
		scanf(" %[^\n]s", questions[i].choice3);
		/*
		// UNUSED:: The question number is automatically assigned;
		if (*totalQuestions > 0){ // If there are more than 0 questions
			// Question number for the added record will be the HIGHEST existing question number + 1
			highest = getHighest(currentQnNumbers, *totalQuestions);
			tempQnNumber = highest + 1;
		}
		else if (*totalQuestions == 0){
			// Else, the question number will be 1
			tempQnNumber = 1;
		}*/
		
		printf("Current input is Question #%d of topic \"%s\"\n", tempQnNumber, tempTopic);
		

		// Once the add record is successful, the totalQuestions variable in main will be incremented by one
		*totalQuestions = *totalQuestions + 1;
		printf("\nTotal Questions: %d\n", *totalQuestions);
	}

	// The struct array is sorted at the end of the function
	sortQuestions(questions, *totalQuestions);
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
			scanf(" %[^\n]s", input);
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

				printf("\nQuestion Numbers Associated with the Topic:\n"); 

				// Looks through the questions struct array for the question index associated with the inputted topic and stores them in the validNums array
				for (i = 0; i < *totalQuestions; i++){
					if (strcmp(input, questions[i].topic) == 0){
						printf("Question #[%d]: %s\n", questions[i].questionNumber, questions[i].question);
						validNums[k] = i;
						k++;
					}
				}

				// Continues asking for input until user enters a valid input
				while (numInput > topicQns || numInput < 1){
					printf("\n>> ");
					scanf("%d", &numInput);
					if (numInput > topicQns || numInput < 1){
						red(); printf("Invalid Input!\n"); reset();
					}
				}

				// Displays the current saved record
				// The index to be edited is defined as validNums[numInput - 1]
				int editInput = 0;
				green(); printf("\nCurrent Record:\n"); reset();
				printf("Question Number: %d\n", questions[ validNums[numInput - 1] ].questionNumber);
				printf("[1] Topic: %s\n", questions[ validNums[numInput - 1] ].topic);
				printf("[2] Question: %s\n", questions[ validNums[numInput - 1] ].question);
				printf("[3] Choice 1: %s\n", questions[ validNums[numInput - 1] ].choice1);
				printf("[4] Choice 2: %s\n", questions[ validNums[numInput - 1] ].choice2);
				printf("[5] Choice 3: %s\n", questions[ validNums[numInput - 1] ].choice3);
				printf("[6] Answer: %s\n", questions[ validNums[numInput - 1] ].answer);
				printf("[7] Exit\n");

				// While loop continues until user exits OR until user makes a change
				while (editInput != 7){
					printf("\n>> ");
					scanf("%d", &editInput);
					printf("\n");
					switch(editInput){
						case 1:
							printf("Input New [Topic]: ");
							scanf(" %[^\n]s", questions[ validNums[numInput - 1] ].topic);
							green(); printf("\nChanges Saved!\n"); reset();
							editInput = 7;
							input[0] = '1';
							break;
						case 2:
							printf("Input New [Question]: ");
							scanf(" %[^\n]s", questions[ validNums[numInput - 1] ].question);
							green(); printf("\nChanges Saved!\n"); reset();
							editInput = 7;
							input[0] = '1';
							break;
						case 3:
							printf("Input New [Choice 1]: ");
							scanf(" %[^\n]s", questions[ validNums[numInput - 1] ].choice1);
							green(); printf("\nChanges Saved!\n"); reset();
							editInput = 7;
							input[0] = '1';
							break;
						case 4:
							printf("Input New [Choice 2]: ");
							scanf(" %[^\n]s", questions[ validNums[numInput - 1] ].choice2);
							green(); printf("\nChanges Saved!\n"); reset();
							editInput = 7;
							input[0] = '1';
							break;
						case 5:
							printf("Input New [Choice 3]: ");
							scanf(" %[^\n]s", questions[ validNums[numInput - 1] ].choice3);
							green(); printf("\nChanges Saved!\n"); reset();
							editInput = 7;
							input[0] = '1';
							break;
						case 6:
							printf("Input New [Answer]: ");
							scanf(" %[^\n]s", questions[ validNums[numInput - 1] ].answer);
							green(); printf("\nChanges Saved!\n"); reset();
							editInput = 7;
							input[0] = '1';
							break;
						case 7:
							break;
						default:
							red(); printf("Invalid input!"); reset();
							break;
					}
				
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
}

void deleteRecord(questionData questions[MAX_QUESTIONS], int* totalQuestions){

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

			yellow(); printf("Type the Topic of the Question you wish to Delete\nEnter [1] to Go Back"); reset();
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
			printf("\n>> ");
			scanf(" %[^\n]s", input);
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

				printf("\nQuestion Numbers Associated with the Topic:\n"); 

				// Looks through the questions struct array for the question index associated with the inputted topic and stores them in the validNums array
				for (i = 0; i < *totalQuestions; i++){
					if (strcmp(input, questions[i].topic) == 0){
						printf("Question #[%d]: %s\n", questions[i].questionNumber, questions[i].question);
						validNums[k] = i;
						k++;
					}
				}

				// Continues asking for input until user enters a valid input
				while (numInput > topicQns || numInput < 1){
					printf("\n>> ");
					scanf("%d", &numInput);
					if (numInput > topicQns || numInput < 1){
						red(); printf("Invalid Input!\n"); reset();
					}
				}

				char delSure;
				while (delSure != 'Y' && delSure != 'y' && delSure != 'N' && delSure != 'n'){
					red(); printf("Are you sure you want to DELETE this question? Y/N (This action cannot be undone)\n"); reset();
					scanf(" %c", &delSure);
					if (delSure == 'Y' || delSure == 'y'){ // if user inputs 'Y' the deletion will continue
						
						/* If total questions are greater than one, the questions struct array will shift by 1 backwards 
						   until the gap left by the deleted record are all filled */
						
						if (*totalQuestions > 1){
							// Starting increment of the for loop will be index of the item to be deleted in the array
							for (i = validNums[numInput - 1]; i < *totalQuestions; i++){  

	            				 // assign arr[i+1] to arr[i] using strcpy and equivalnce for the question number
								 // if current iteration is within the range of topics;
								if (strcmp(questions[i].topic, input) == 0){
									// if iteration has reached the end of the topics, qn number will be set to 1
									if (strcmp(questions[i+1].topic, input) != 0 ){
										questions[i].questionNumber = 1;
									}
									// else, continue with shifting to the left but also subtract 1 to fill in for the deleted number
									else{
										questions[i].questionNumber = questions[i+1].questionNumber - 1; 
									}
								}
								// if current iteration is not within the range of topics, question number will just shift to the left
								else{
									questions[i].questionNumber = questions[i+1].questionNumber; 
								}
									
								// for the rest of the struct elements, all will shift to the left
								strcpy(questions[i].topic, questions[i+1].topic); 
								strcpy(questions[i].question, questions[i+1].question);
								strcpy(questions[i].choice1, questions[i+1].choice1);
								strcpy(questions[i].choice2, questions[i+1].choice2);
								strcpy(questions[i].choice3, questions[i+1].choice3);
								strcpy(questions[i].answer, questions[i+1].answer);
	       					 }  
						}
						
						/* Else, if there is only one question, and the user wants to delete it, all elements will be returned to null
						   by copying all elements of the index next to it. */
						   
						else{ // Bug 01: question number can underflow to 0
								i = numInput - 1;
								questions[i].questionNumber = questions[i+1].questionNumber;
								strcpy(questions[i].topic, questions[i+1].topic); 
								strcpy(questions[i].question, questions[i+1].question);
								strcpy(questions[i].choice1, questions[i+1].choice1);
								strcpy(questions[i].choice2, questions[i+1].choice2);
								strcpy(questions[i].choice3, questions[i+1].choice3);
								strcpy(questions[i].answer, questions[i+1].answer);
							
						}
						// Total questions will be decremented by 1 after deletion.
						*totalQuestions = *totalQuestions - 1;
						
						yellow(); printf("Succesfully deleted.\n"); reset();
						input[0] = '1';
					}
					else{ // if user types 'N' or any other input deletion will be aborted
						green(); printf("Deletion aborted.\n"); reset();
						input[0] = '1';
					}
				}
			}

			/* If topic input not exist, prompt the user to enter a valid input again;
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

}

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

// Function for importing data from a file (either player data or questions)
void importData(questionData questions[MAX_QUESTIONS], int* totalQuestions, playerData players[MAX_PLAYERS], int *totalPlayers){

	// Increment variable
	int i;
	//int j;

	// File variable declaration
	FILE *fp;
	
	// Input variables
	char selection;
	char press;
	string30 input;

	while (selection != '3'){

		yellow(); printf("Select Which Data to Import\n"); reset();
		printf("[1] Questions Data\n");
		printf("[2] Player Data\n");
		printf("[3] Exit\n");

		selection = _getch();
		if (selection > '3' || selection < '1'){
			system("cls");
			red(); printf("Invalid input!\n\n"); reset();
		}

		switch(selection){

			case '1':
				i = *totalQuestions;
				while (press != '1'){
					
					green(); printf("Enter File Name (exclude .txt): "); reset();
					scanf(" %[^\n]s", input);
					strcat(input, ".txt");
					// Reads from inputted txt file, stores into questions array;
					fp = fopen(input, "r");

					// If file does not exist, print error message and option to retry
					if (fp == NULL){
						red(); printf("\nFile not found!\n"); reset();
						yellow(); printf("Press [1] to return to the previous menu\nPress any key to try again\n"); reset();
						press = _getch();
						
					}

					// If file exits, importing will start
					else{
					
						// Scans the file for each number until the end of file is reached, then stores them into array data
						while (
								fscanf(fp, " %[^\n]s", questions[i].topic) != EOF &&
								fscanf(fp, " %d", &questions[i].questionNumber) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].question) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].choice1) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].choice2) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].choice3) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].answer) != EOF	
							){

							// i will be the total number of questions read from the file	
							i++;
						}
						
						// The total questions read from the file will be added to the tally of total questions
						*totalQuestions = *totalQuestions + i;

						// After the loop is complete, prints a success message and exits the menu

						// The struct array is sorted at the end of the function
						sortQuestions(questions, *totalQuestions);

						fclose(fp);
						green(); printf("Import Complete!\n"); reset();
						press = '1';
						selection = '3';
						
					}
				}
				break;
			
			case '2':
				i = *totalPlayers;
				while (press != '1'){
					
					green(); printf("Enter File Name (exclude .txt): "); reset();
					scanf(" %[^\n]s", input);
					strcat(input, ".txt");
					// Reads from inputted txt file, stores into questions array;
					fp = fopen(input, "r");

					// If file does not exist, print error message and option to retry
					if (fp == NULL){
						red(); printf("\nFile not found!\n"); reset();
						yellow(); printf("Press [1] to return to the previous menu\nPress any key to try again\n"); reset();
						press = _getch();
						
					}

					// If file exits, importing will start
					else{
					
						// Scans the file for each number until the end of file is reached, then stores them into array data
						while (
								fscanf(fp, " %[^\n]s", players[i].name) != EOF &&
								fscanf(fp, " %d", &players[i].score) != EOF 
							){

							// i will be the total number of questions read from the file	
							i++;
						}
						
						// The total questions read from the file will be added to the tally of total questions
						*totalPlayers = *totalPlayers + i;

						// After the loop is complete, prints a success message and exits the menu

						// The struct array is sorted at the end of the function
						sortScores(players, *totalPlayers);

						fclose(fp);
						green(); printf("Import Complete!\n"); reset();
						press = '1';
						selection = '3';
						
					}
				}
			
				break;

			case '3':
				system("cls");
				break;
		}

	}
}

// Function for exporting data to a file (either player data or questions)
void exportData(questionData questions[MAX_QUESTIONS], int* totalQuestions, playerData players[MAX_PLAYERS], int *totalPlayers){

	// Increment variable
	int i;
	//int j;

	// File variable declaration
	FILE *fp;
	
	// Input variables
	char selection;
	string30 input;

	while (selection != '3'){

		yellow(); printf("Select Which Data to Export\n"); reset();
		printf("[1] Questions Data\n");
		printf("[2] Player Data\n");
		printf("[3] Exit\n");

		selection = _getch();
		if (selection > '3' || selection < '1'){
			system("cls");
			red(); printf("Invalid input!\n\n"); reset();
		}

		switch(selection){

			case '1':
				green(); printf("Enter File Name (exclude .txt): "); reset();
	            scanf(" %[^\n]s", input);
            	strcat(input, ".txt");
            	// Stores struct array info into the given text file;
            	fp = fopen(input, "w");
            	for (i = 0; i < *totalQuestions; i++){
            		fprintf(fp, "%s%s", questions[i].topic, "\n");
            		fprintf(fp, "%d%s", questions[i].questionNumber, "\n");
            		fprintf(fp, "%s%s", questions[i].question, "\n");
            		fprintf(fp, "%s%s", questions[i].choice1, "\n");
            		fprintf(fp, "%s%s", questions[i].choice2, "\n");
            		fprintf(fp, "%s%s", questions[i].choice3, "\n");
            		fprintf(fp, "%s%s", questions[i].answer, "\n");
            		if (i != *totalQuestions - 1){
            			fprintf(fp, "%s", "\n");
            		}
            	}

            	fclose(fp);
            	green(); printf("Export complete!\n"); reset();
            	selection = '3';
				break;
			
			case '2':
				green(); printf("Enter File Name (exclude .txt): "); reset();
	            scanf(" %[^\n]s", input);
            	strcat(input, ".txt");
            	// Stores struct array info into the given text file;
            	fp = fopen(input, "w");
            	for (i = 0; i < *totalPlayers; i++){
            		fprintf(fp, "%s%s", players[i].name, "\n");
            		fprintf(fp, "%d%s", players[i].score, "\n");
            		if (i != *totalPlayers - 1){
            			fprintf(fp, "%s", "\n");
            		}
            	}

            	fclose(fp);
            	green(); printf("Export complete!\n"); reset();
            	selection = '3';
				break;

			case '3':
				system("cls");
				break;
		}

	}

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
				playPanel(questions, players, &totalPlayers, &totalQuestions);
		
				break;
				
			case '2':
				system("cls");
				passwordPrototype(questions, players, &totalQuestions, &totalPlayers);
				
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



