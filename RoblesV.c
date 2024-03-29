/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
																	Vance Gyan M. Robles, DLSU ID#12279560
*********************************************************************************************************/

/*
	Description: A program which simulates a quiz trivia game
	Programmed by: Vance Gyan M. Robles, Section S23B
	Last modified: 04/10/2023
	Version: 1.0a
*/


	/* TO DO:
		- PASS

	   Done:
	    - TEST SCRIPT
	    - FINAL SCREEN CLEANUP FOR MENU SELECTIONS
	   	- ADD CONFIRMATION FOR EDIT RECORD
	   	- PARAMETERS IN COMMENTS
	    - REMOVED UNUSED FUNCTIONS
	    - FIX QUESTION NUMBER REASSIGNMENT FOR EDIT RECORD
	    - REPLACED MANUAL DISPLAY TOPICS IN ADMIN FUCNTIONS WITH 'displayTopics()' FUNCTION
	   	- QUIZ GAME PROPER
		- RANDOMIZE QUESTIONS
		- ACCUMULATE SCORE
		- FIX AUTOMATIC NUMBERING v2 (SHOULD BE SEPARATE FOR EACH TOPIC, NOT UNIVERSAL) APPLICABLE TO MANUAL ADDING OF RECORD ONLY
		- FIX DELETE FUNCTION TO ACCOUNT FOR NEW NUMBERING
		- FIX EDIT FUNCTION TO ACCOUNT FOR NEW NUMBERING
		- IMPORT, EXPORT, VIEW SCORES


	*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
// #include <windows.h>

#define MAX_LENGTH 33
#define MAX_PLAYERS 50
#define MAX_QUESTIONS 50
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
struct questionData{

	string20 topic;
	int questionNumber;
	string150 question;
	string30 choice1;
	string30 choice2;
	string30 choice3;
	string30 answer;

};

struct playerData{

	string20 name;
	int score;

};

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
void sortQuestions();
int genRandInt();

/* ================================ */
// Text Coloring Functions

//  This function changes the text color to a brighter white
void bold()
{
	printf("\e[1;97m");
}

//  This function changes the text color to cyan
void cyan()
{
	printf("\033[0;36m");
}

//  This function changes the text color to green
void green()
{
	printf("\e[0;92m");
}

//  This function changes the text color to yellow
void yellow()
{
	printf("\033[1;33m");
}

//  This function changes the text color to red
void red()
{
	printf("\e[0;91m");
}

//  This function changes the text color to the default white
void reset()
{
	printf("\033[0m");
}


/* ================================ */
// 'Main' Functions

/* 
	Function that sorts an array of question structs based on topic, then question number, using bubble sort 
	Precondition: totalQuestions is greater than 1, all members of each questionData struct is filled and valid 
	@param questions is the struct questionData array for storing questions
	@param totalQuestions is the total number of questions currently being stored in the program
	@return void

*/
void sortQuestions(struct questionData questions[MAX_QUESTIONS], int totalQuestions) {
    int i, j, k, l;
	int size = totalQuestions;
    struct questionData temp;
    
    // First, sort based on topic in alphabetical order (increasing)
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
    
    
    i = 0; // i is reset to 0

	// Then, sort based on question number in increasing order (within each topic group)
    while (i < size) {

		// j is set to the index of the first element (start) of the current topic group
        j = i;

		// Then, finds the end of the current topic group through strcmp and assigns it to j
        while (j < size && strcmp(questions[i].topic, questions[j].topic) == 0) {
            j++;
        }
        // Sort the questions with the same topic from i to j-1
        for (k = i; k < j - 1; k++) {
            for (l = k + 1; l < j; l++) {
				// Compare the question numbers of the two questions within the same topic group
                if (questions[k].questionNumber > questions[l].questionNumber) {
                    // Swaps the two questions if the question number of the k-th question is greater than the question number of the l-th question
                    temp = questions[k];
                    questions[k] = questions[l];
                    questions[l] = temp;
                }
            }
        }
		
        i = j; // Moves the iteration to the next topic group by reassigning i to the end of the previous topic group
    }
}

/* 
	Function for password functionality with hidden input using getch, used to access the Admin Panel
	Precondition: correctPassword in main is a valid string and can be written using keyboard input
	@param questions is the struct questionData array for storing questions 
	@param players is the struct playerData array for storing player data (scores and names)
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@param *totalPlayers is the pointer to the variable in main storing the total number of players currently being stored in the program
	@param correctPassword is the string in main which stores the correct password to access the admin panel
	@return void
*/
void passwordScreen(struct questionData questions[MAX_QUESTIONS], struct playerData players[MAX_PLAYERS], int* totalQuestions, int* totalPlayers, pwd correctPassword){
	
	// Variable declarations

     int active = 1;
     char input;
     char exit = '\0';
     pwd passwordInput;
     
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
				putchar('\b');
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
	    	system("cls");
			green(); printf("        Welcome!\n\n"); reset();
	    	adminPanel(questions, players, totalQuestions, totalPlayers);
	    	active = 0;
	    	
		}
		
		// If the passwords are not the same, the user will be given an option to either exit back to the main menu or try again.
		else{
			red(); printf("\nIncorrect Password!\nPress [1] to return to the Main Menu or press any key to try again.\n"); reset();
			
			exit = _getch();
			if (exit == '1'){

				system("cls");
				active = 0;
			}
			
			else{
				system("cls");
			}

	
	
		}
	}
}

/*
	Function that prints the main menu interface.
	@return void
*/
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


/*
	Function that prints the Admin menu interface.
	@return void
*/
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


/*
	Function that prints the Play menu interface.
	@return void
*/
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

/* 
	Function that handles inputs for the 'Play' menu
	Precondition: All structs and members are valid, totalPlayers and totalQuestions are greater than or equal to 0
	@param questions is the struct questionData array for storing questions 
	@param players is the struct playerData array for storing player data (scores and names)
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@param *totalPlayers is the pointer to the variable in main storing the total number of players currently being stored in the program
	@return void
*/
void playPanel(struct questionData questions[MAX_QUESTIONS], struct playerData players[MAX_PLAYERS], int *totalPlayers, int *totalQuestions){
	
	char input;
	FILE *fp;

	// This block will open the scores.txt file and store all information into the playerData struct array
	int i = 0;

	fp = fopen("scores.txt", "r");

	// If scores.txt does not exist, it will be created
	if (fp == NULL){
		fp = fopen("scores.txt", "w");
		green(); printf("scores.txt has been created.\n"); reset();
		fclose(fp);
	}

	// Else, contents of the scores.txt file are read and stored into the players struct array
	else{
		while (
			fscanf(fp, " %[^\n]s", players[i].name) != EOF &&
			fscanf(fp, " %d", &players[i].score) != EOF 
			){

			// i will be the total number of player data read from the file	
			i++;
		}
		*totalPlayers = i; // totalPlayers will be equal to i
		fclose(fp);
	}
	
	while (input != '3'){
		displayPlayMenu();
		cyan(); printf("\n[Press the number corresponding to your selection.]\n"); reset();
		input = _getch();
		
		switch(input){
			
			case '1':
				system("cls");
			
				// The scores.txt file will be opened again but in append mode to add new score record if an instance of the game is played
				fp = fopen("scores.txt", "a");
				playGame(questions, players, totalPlayers, totalQuestions, fp);
				fclose(fp);

				break;
				
			case '2':
				system("cls");
				viewScores(players, totalPlayers);
				
				break;
				
			case '3': // If 'Exit' is chosen, program returns to the previous menu by terminating the while loop.
				system("cls");

				// The scores.txt file will be opened again but in write mode to update the scores.txt file with possible new scores
				fp = fopen("scores.txt", "w");
				for (i = 0; i < *totalPlayers; i++){
            		fprintf(fp, "%s%s", players[i].name, "\n");
            		fprintf(fp, "%d%s", players[i].score, "\n");
            		if (i != *totalPlayers - 1){
            			fprintf(fp, "%s", "\n");
            		}
            	}
				fclose(fp);
				break;
			
			default: 
				// If the input is not within the given parameters, 'invalid input' will be displayed and the main menu will be shown again.
				system("cls");
				red(); printf("\nInvalid input. Please select a valid option.\n"); reset();
				break;
				
		}
	}

	// Once the user exits out of this menu, the file will close and changes will be saved
	fclose(fp);
	
}

/*
	Function for generating a random integer between a set range
	Precondition: Parameters do not exceed the integer limit, parameter min is less than parameter max
	@param min is the lower bound of the range of possible random numbers to be generated (inclusive)
	@param max is the upper bound of the range of possible random numbers to be generated (inclusive)
	@return a random value between min and max inclusive
*/
int genRandInt(int min, int max){

    int temp;

	// If min is greater than max, swap
    if (min > max){
        temp = min;
        min = max;
        max = temp;
    }

	// The random number generator is seeded with the current time;
	srand(time(NULL)); 

	// The function returns a random number in the range [min, max]
    return min + rand() % (max - min + 1); 
}

/*
	Function for printing all currently available topics within the questionsData struct array, only shows each topic once
	Precondition: All structs and members are valid, and totalQuestions is greater than or equal to 0
	@param questions is the struct questionData array for storing questions 
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@return void
*/
void displayTopics(struct questionData questions[MAX_QUESTIONS], int *totalQuestions){

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

/* 
	Function that handles importing a records file for the playGame() function
	Precondition: questions struct array is empty, totalQuestions is equal to 0
	@param questions is the struct questionData array for storing questions 
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@return void
*/
void importQuestions(struct questionData questions[MAX_QUESTIONS], int *totalQuestions){

	// totalQuestions will be set to 0 at the start
	*totalQuestions = 0;
	
	// Increment variable
	int i, j;
	int tempQnNumber = 1;

	// File variable declaration
	FILE *fp;
	
	// Temp variable for handling topics
	string20 tempTopic;

	i = *totalQuestions;
	string30 filename;

	yellow(); printf("Please input the filename of the records file to start: "); reset();
	scanf("%s", filename);
	fp = fopen(filename, "r");

	if (fp == NULL){
		red(); printf("File not found!\n"); reset();
	}

	// If file exits, importing will start
	else{	
		// Scans the file for each number until the end of file is reached, then stores them into array data

		while (
			fscanf(fp, " %[^\n]s", tempTopic) != EOF &&
			fscanf(fp, " %d", &questions[i].questionNumber) != EOF &&
			fscanf(fp, " %[^\n]s", questions[i].question) != EOF &&
			fscanf(fp, " %[^\n]s", questions[i].choice1) != EOF &&
			fscanf(fp, " %[^\n]s", questions[i].choice2) != EOF &&
			fscanf(fp, " %[^\n]s", questions[i].choice3) != EOF &&
			fscanf(fp, " %[^\n]s", questions[i].answer) != EOF	
			){
				tempQnNumber = 1;
				for (j = 0; j < i; j++) {
					if (strcmp(tempTopic, questions[j].topic) == 0 && questions[j].questionNumber >= tempQnNumber) {
						tempQnNumber = questions[j].questionNumber + 1;
					}
				}
				// temporary adjustment to question number to ensure that new questions will have a higher number than existing ones
				if (tempQnNumber != 0) {
					questions[i].questionNumber = tempQnNumber;
				}
				strcpy(questions[i].topic, tempTopic);

				// i will be the total number of questions read from the file	
				i++;
			}
						
			// The total questions read from the file will be added to the tally of total questions
			*totalQuestions = i;

			// The struct array is sorted
			sortQuestions(questions, *totalQuestions);

			// After the loop is complete, prints a success message and exits the menu
			fclose(fp);
			system("cls");
			
			if (*totalQuestions > 0){
				green(); printf("Questions Found!\n"); reset();
			}
			else{
				red(); printf("No questions found in file!\n"); reset();
			}

	}
}

/* 
	Function that handles inputs for the 'Play' menu
	Precondition: All structs and members are valid, totalPlayers and totalQuestions are greater than or equal to 0, scores.txt has been initialized and opened
	@param questions is the struct questionData array for storing questions 
	@param players is the struct playerData array for storing player data (scores and names)
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@param *totalPlayers is the pointer to the variable in main storing the total number of players currently being stored in the program
	@param *fp is the FILE pointer to scores.txt
	@return void
*/
void playGame(struct questionData questions[MAX_QUESTIONS], struct playerData players[MAX_PLAYERS], int *totalPlayers, int *totalQuestions, FILE *fp){
	
	// Asks user to import questions from an exported (or created) text file
	importQuestions(questions, totalQuestions);

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
	// all current questions will be set to isAnswered = 0 (false) at the start
	for (j = 0; j < MAX_QUESTIONS; j++){
		isAnswered[j] = 0;
	}
	
	// array to store valid indexes of questions within a topic
	int validQns[MAX_QUESTIONS];

	// counting variables for answered questions, total questions in a topic, and total unanswered questions in a topic
	int totalAnswered = 0, totalTopic, totalTopicUnanswered;

	// if totalQuestions in main is 0, show an error message
	if (*totalQuestions < 1){
		printf("Please export or input records to a ");
		green(); printf(".txt"); reset();
		printf(" file to play.\n");
	}
	// else, continue
	else{

		printf("Total Questions: ");
		cyan(); printf("%d\n", *totalQuestions); reset();

		// asks player to input their name
		yellow(); printf("Enter Your Name: "); reset();
		scanf(" %[^\n]s", players[i].name);
		green(); printf("\nWelcome [%s]!\n", players[i].name); reset();

		// the loop will continue until the game is over (over == 1)
		while (over != 1){
			
			// initialized to 0
			exists = 0;

			// keeps asking user for topic input until a valid topic has been entered
			while (exists == 0){

				printf("Current Score: ");
				green(); printf("%d\n\n", score); reset();
				printf("Total Questions: ");
				yellow(); printf("%d\n", *totalQuestions); reset();
				printf("Questions Answered: ");
				yellow(); printf("%d\n", totalAnswered); reset();

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

			// printf("Total Questions Answered: %d\n", totalAnswered);

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

			//printf("Total Number of Questions in Topic: %d\n", totalTopic);
			
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
				printf("\n");
				//printf("Total Number of Unanswered in Topic: %d\n", totalTopicUnanswered);

				// current will be a random integer from 0 to (totalTopic - 1) inclusive;
				// this range will generate an index for accessing validQns
				// then, the corresponding value from validQns[current] will be used as the index for the question to be played
				current = genRandInt(0, totalTopic - 1);

				// if the randomly generated index is already answered, randomize will reroll until an unanswered question's index is found
				// since the randomizer is seeded with time, forcing it to roll a specific number can cause it to take a while
				while (isAnswered[validQns[current]] == 1){
					yellow(); printf("Randomizing...\r"); reset();
					current = genRandInt(0, totalTopic - 1);
				}
				//printf("Random Number: %d\n", validQns[current]);

				// prints the current question data and presents the user with a choice
				printf("%s\n[1] %s\n[2] %s\n[3] %s\n[4] End Game\n", questions[validQns[current]].question, questions[validQns[current]].choice1, 
						questions[validQns[current]].choice2, questions[validQns[current]].choice3);
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
						case '4': // Case for player quitting the game preemptively
							over = 1;

							// Displays player stats at the end of the game
							system("cls");
							red(); printf("Game Over!\n"); reset();
							printf("Player Name: ");
							yellow(); printf("%s\n", players[i].name); reset();
							printf("Final Score: ");
							green(); printf("%d\n\n", score); reset();

							players[i].score = score; // Saves the score to the players struct
							*totalPlayers = *totalPlayers + 1; // totalPlayers will be incremented once a session is complete

							// Appends the current score data to scores.txt
							fseek(fp, 0, SEEK_END);
							if (ftell(fp) == 0){
								fprintf(fp, "%s\n", players[i].name);
								fprintf(fp, "%d", players[i].score);
							}
							else{
								fprintf(fp, "\n\n%s\n", players[i].name);
								fprintf(fp, "%d", players[i].score);
							}

							cyan(); printf("[Press any key to return.]\n"); reset();
							getch();
							system("cls");
							

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

					// Displays player stats at the end of the game
					cyan(); printf("All questions answered.\n"); reset();
					printf("Player Name: ");
					yellow(); printf("%s\n", players[i].name); reset();
					printf("Final Score: ");
					green(); printf("%d\n", score); reset();

					players[i].score = score; // Saves the score to the players struct
					*totalPlayers = *totalPlayers + 1; // totalPlayers will be incremented once a session is complete

					// Appends the current score data to scores.txt
					fseek(fp, 0, SEEK_END);
					if (ftell(fp) == 0){
						fprintf(fp, "%s\n", players[i].name);
						fprintf(fp, "%d", players[i].score);
					}
					else{
						fprintf(fp, "\n\n%s\n", players[i].name);
						fprintf(fp, "%d", players[i].score);
					}

					cyan(); printf("[Press any key to return.]\n"); reset();
					getch();
					system("cls");
				}

				// user is redirected back to choosing a topic at the end if a condition for ending the game is not met
			}
		}
	}
}

/* 
	Function that sorts the playerData struct array based on scores in descending order
	Precondition: All structs and members are valid, totalPlayers are greater than or equal to 0
	@param players is the struct playerData array for storing player data (scores and names)
	@param totalPlayers is the number of total number of players currently being stored in the program 
	@return void
*/
void sortScores(struct playerData players[MAX_PLAYERS], int totalPlayers){

	int i, j;
    struct playerData temp;
    
    // Sorts based on score in descending order
    for (i = 0; i < totalPlayers - 1; i++) {
        for (j = i + 1; j < totalPlayers; j++) {
            if (players[j].score > players[i].score) {
                // Swap the two questions
                temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

}

/* 
	Function for the 'View Scores' option that displays all saved player scores 
	Precondition: All structs and members are valid, totalPlayers are greater than or equal to 0
	@param players is the struct playerData array for storing player data (scores and names)
	@param *totalPlayers is the pointer to the variable in main storing the total number of players currently being stored in the program
	@return void
*/
void viewScores(struct playerData players[MAX_PLAYERS], int* totalPlayers){

	int i;

	// Sorts scores in descending order
	sortScores(players, *totalPlayers);

	// Variables for rank calculation
	int rank = 1;
    int prevScore = players[0].score;

	printf("+======+======================+=======+\n");
	printf("|             Leaderboard             |\n");
	printf("+======+======================+=======+\n");
	printf("| Rank |         Name         | Score |\n");
	printf("+------+----------------------+-------+\n");
	for (i = 0; i < *totalPlayers; i++){

		// If current score is higher than previous score, rank is increased
		if (players[i].score < prevScore) {
            rank++;
        }

		printf("|%-6d|%-22s|%-7d|\n", rank, players[i].name, players[i].score);
		printf("+------+----------------------+-------+\n");

		// Previous score is set to the current score at the end of each instance of the loop
		prevScore = players[i].score;
	}
	printf("\n");
	cyan(); printf("[Press any key to return.]\n"); reset();
	getch();
	system("cls");

}

/* 
	Function that clears the questions array for when user exits the Manage Data menu
	Precondition: All structs and members are valid, totalQuestions are greater than or equal to 0
	@param questions is the struct questionData array for storing questions 
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@return void
*/
void clearRecords(struct questionData questions[MAX_QUESTIONS], int *totalQuestions){
	
	int i;

    // For loop will go through all records in the array and set all strings to null and question number to 0
    for(i = 0; i < *totalQuestions; i++){
        questions[i].topic[0] = '\0';
        questions[i].questionNumber = 0;
        questions[i].question[0] = '\0';
        questions[i].choice1[0] = '\0';
        questions[i].choice2[0] = '\0';
        questions[i].choice3[0] = '\0';
        questions[i].answer[0] = '\0';
    }

    // The totalQuestions value will be set to zero to indicate that the array is now empty
    *totalQuestions = 0;
}

/* 
	Function that handles inputs for the Manage Data menu 
	Precondition: All structs and members are valid, totalPlayers and totalQuestions are greater than or equal to 0
	@param questions is the struct questionData array for storing questions 
	@param players is the struct playerData array for storing player data (scores and names)
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@param *totalPlayers is the pointer to the variable in main storing the total number of players currently being stored in the program
	@return void
*/
void adminPanel(struct questionData questions[MAX_QUESTIONS], struct playerData players[MAX_PLAYERS], int* totalQuestions, int *totalPlayers){

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
			
			case '6': // If 'Exit' is chosen, the menu is exited by terminating the while loop.

				// Unsaved (non-exported) records will be cleared, and totalQuestions will be reset to 0
				clearRecords(questions, totalQuestions);

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

/* 
	Function that handles input for the addRecord function 
	Precondition: All structs and members are valid, totalQuestions are greater than or equal to 0
	@param questions is the struct questionData array for storing questions 
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@return void
*/
void addRecord(struct questionData questions[MAX_QUESTIONS], int* totalQuestions){

	// The increment variable 'i' is initialized to the total number of questions, which at the start of the program is always set to 0
	// Increment variable j is used in the for loop to store question numbers
	int i = *totalQuestions, j;

	// Variables for handling question number allocation
	int tempQnNumber = 1;

	string150 tempQuestion;
	string30 tempAnswer;
	string20 tempTopic;
	int questionDuplicate;

	char input[150];
	char confirmation;

	while (input[0] != '`'){
		
		yellow(); printf("\nEnter [`] To Go Back\n\n"); reset();

		// The question and answer will be asked for first
		printf("Add a Question: ");
		scanf(" %[^\n]s", input);
		strcpy(tempQuestion, input);

		// If input is not ` (exit), continue to ask for the next input.
		if (input[0] != '`'){
			printf("Add an Answer: ");
			scanf(" %[^\n]s", input);
			strcpy(tempAnswer, input);

			// If input is not ` (exit), continue to ask for the next input.
			if (input[0] != '`'){

				// The questionDuplicate variable will to check if the inputted question and answer pair already exists
				questionDuplicate = existingQNACheck(questions, tempQuestion, tempAnswer);

				// If the question and answer pair is a duplicate, an error message will be printed and the user will return to the previous menu
				if (questionDuplicate != -1){
					red(); printf("\nThat question and answer already exists! (Index: %d)\n", questionDuplicate); reset();
					printf("Topic: %s\n", questions[questionDuplicate].topic);
					printf("Question #%d\n", questions[questionDuplicate].questionNumber);
					printf("%s\n", questions[questionDuplicate].question);
					printf("%s\n", questions[questionDuplicate].choice1);
					printf("%s\n", questions[questionDuplicate].choice2);
					printf("%s\n", questions[questionDuplicate].choice3);
					printf("Answer: %s\n", questions[questionDuplicate].answer);

				}

				// Else, if the question and answer pair is valid;
				else{

					// The previous inputs will be copied from the temporary variable to their respective struct array child
					strcpy(questions[i].question, tempQuestion);
					strcpy(questions[i].answer, tempAnswer);

					// Continuation of input calls, this time the inputs are directly stored in the struct
					printf("Add a Topic: ");
					scanf(" %[^\n]s", input);
					strcpy(tempTopic, input);

					// If input is not ` (exit), continue to ask for the next input.
					if (input[0] != '`'){
						for (j = 0; j < *totalQuestions; j++){
							if (strcmp(tempTopic, questions[j].topic) == 0){
								tempQnNumber++;
							}
						}
						strcpy(questions[j].topic, tempTopic);
						questions[i].questionNumber = tempQnNumber;

						printf("Add the First Choice: ");
						scanf(" %[^\n]s", input);
						strcpy(questions[i].choice1, input);

						// If input is not ` (exit), continue to ask for the next input.
						if (input[0] != '`'){

							printf("Add the Second Choice: ");
							scanf(" %[^\n]s", input);
							strcpy(questions[i].choice2, input);

							// If input is not ` (exit), continue to ask for the next input.
							if (input[0] != '`'){

								printf("Add the Third Choice: ");
								scanf(" %[^\n]s", input);
								strcpy(questions[i].choice3, input);

								// If input is not ` (exit), continue to ask for confirmation to save the question.
								if (input[0] != '`'){
								
									printf("Current Input is Question #%d of Topic \"%s\"\n", tempQnNumber, tempTopic);
									yellow(); printf("Save the current input? (Y/N)\n"); reset();
									printf(">> ");
									scanf(" %c", &confirmation);
									if (confirmation == 'Y' || confirmation == 'y'){
										system("cls");
										green(); printf("Question Saved!"); reset();
										*totalQuestions = *totalQuestions + 1; // Once the add record is successful and confirmed, totalQuestions variable in main will be incremented by one
									}
									else{
										system("cls");
										red(); printf("Question Discarded."); reset(); // Else, the totalQuestions variable will remain unchanged
									}
								}
							}
						}
					}
				}
			}
		}

		// Clears the screen and displays a message if user opts to exit adding a record preemptively
		if (input[0] == '`'){
			system("cls");
			red(); printf("Question Discarded."); reset();
		}

		printf("\nTotal Questions: %d\n", *totalQuestions);
		input[0] = '`';
	}

	// The struct array is sorted at the end of the function
	sortQuestions(questions, *totalQuestions);

}

/*
	This fucntion checks if a question-answer pair already exists within the struct 
	Precondition: All structs and members are valid
	@param questions is the struct questionData array for storing questions 
	@param addenQn is the string corresponding to the current user 'Question' input (in addRecord)
	@param addenQn is the string corresponding to the current user 'Answer' input (in addRecord)
	@return the index of the record if the question-answer pair belongs in the same struct array index, return 0 if there are no matches found
*/
int existingQNACheck(struct questionData questions[MAX_QUESTIONS], string150 addedQn, string30 addedAns){

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

	// If the question-answer pair belongs in the same struct array index, the function will return the index (true)
	if (matchQuestion == matchAnswer){
		return matchAnswer;
	}

	// Else, it returns -1 (false, or does not exist)
	return -1;


}

/*
	Function that handles editing individual question records 
	Precondition: All structs and members are valid, totalQuestions are greater than or equal to 0
	@param questions is the struct questionData array for storing questions 
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@return void
*/
void editRecord(struct questionData questions[MAX_QUESTIONS],  int* totalQuestions){

	// Increment variables
	int i;

	// Variables for strings (for input and for storing/sorting topics)
	char input[20];
	string20 tempTopic;
	string150 tempQuestion;
	string30 tempChoice;
	string30 tempAnswer;

	// Checking (bool) variables
	int exists;

	// Buffer variables
	int buffer;
	char confirmation;

	// If total questions is greater than 0, proceed
	if (*totalQuestions > 0){

		// The while loop will continue until the user enters '1', or a string that starts with '1'
		while (input[0] != '1'){

			yellow(); printf("Type the Topic of the Question to Edit\nEnter [1] to Go Back\n"); reset();
			displayTopics(questions, totalQuestions);

			// Gets user input, will be case sensitive
			printf(">> ");
			scanf(" %[^\n]s", input);
			exists = 0;

			// This loop will scan the topics of the struct array if the input exists
			for (i = 0; i < *totalQuestions; i++){
				if (strcmp(input, questions[i].topic) == 0){
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

				yellow(); printf("\nInput [0] to Exit.\n"); reset();
				green(); printf("Question Numbers Associated with the Topic:\n"); reset();
				// Looks through the questions struct array for the question index associated with the inputted topic and stores them in the validNums array
				for (i = 0; i < *totalQuestions; i++){
					if (strcmp(input, questions[i].topic) == 0){
						printf("Question #[%d]: %s\n", questions[i].questionNumber, questions[i].question);
						validNums[k] = i;
						k++;
					}
				}

				// Continues asking for input until user enters a valid input
				while (numInput > topicQns || numInput < 0){
					printf("\n>> ");

					// scanf is buffered so that character misinputs will not result in an infinite loop
					buffer = scanf("%d", &numInput);
					if (buffer == 0) {
            			numInput = getchar(); // catches the character input
        			}

					// prints an error message if the selected number is out of range
					if (numInput > topicQns || numInput < 0){
						red(); printf("Invalid Input!\n"); reset();
					}
				}

				// If user does not select 'Exit', continue
				if (numInput != 0){
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

						// scanf is buffered so that character misinputs will not result in an infinite loop
						buffer = scanf("%d", &editInput);
						if (buffer == 0) {
							editInput = getchar(); // catches the character input
						}

						// once a change has been made (either saved or discarded), numInput will be set to -1 to reset the choice,
						// user will also be redirected back to topic selection, if an edit has been saved, the selection screen will adjust accordingly
						switch(editInput){
							case 1:
								printf("\n");
								printf("Input New [Topic]: ");
								scanf(" %[^\n]s", tempTopic);
								yellow(); printf("Do you want to save your current changes? (Y/N)"); reset();
								printf("\n>> ");
								scanf(" %c", &confirmation);

								if (confirmation == 'Y' || confirmation == 'y'){
									// Reassignment of question number if the topic was edited
									int tempQnNumber = 1;
									for (i = 0; i < *totalQuestions; i++){
										if (strcmp(tempTopic, questions[i].topic) == 0){
											tempQnNumber++;
										}
									}
									questions[validNums[numInput - 1]].questionNumber = tempQnNumber;
									strcpy(questions[ validNums[numInput - 1] ].topic, tempTopic);

									// Re-assignment of question numbers of other records in the topic to account for the gap if topic was changed
									topicQns = 0;
									for (i = 0; i < *totalQuestions; i++){
										if (strcmp(input, questions[i].topic) == 0){
											topicQns++;
										}
									}
									k = 0;
									for (i = 0; i < *totalQuestions; i++){
										if (strcmp(input, questions[i].topic) == 0){
											validNums[k] = i;
											k++;
										}
									}
									for (i = 0; i < topicQns; i++){
										questions[validNums[i]].questionNumber = i + 1;
									}
									
									system("cls");
									green(); printf("Changes Saved!\n\n"); reset();
									editInput = 7;
									numInput = -1;
									// input[0] = '1';
								}

								else{
									system("cls");
									red(); printf("Changes Discarded.\n\n"); reset();
									editInput = 7;
									numInput = -1;
								}
								
								break;

							case 2:
								printf("\n");
								printf("Input New [Question]: ");
								scanf(" %[^\n]s", tempQuestion);
								yellow(); printf("Do you want to save your current changes? (Y/N)"); reset();
								printf("\n>> ");
								scanf(" %c", &confirmation);

								if (confirmation == 'Y' || confirmation == 'y'){
									strcpy(questions[ validNums[numInput - 1] ].question, tempQuestion);
									system("cls");
									green(); printf("Changes Saved!\n\n"); reset();
									editInput = 7;
									numInput = -1;
									// input[0] = '1';
								}

								else{
									system("cls");
									red(); printf("Changes Discarded.\n\n"); reset();
									editInput = 7;
									numInput = -1;
								}

								break;

							case 3:
								printf("\n");
								printf("Input New [Choice 1]: ");
								scanf(" %[^\n]s", tempChoice);
								yellow(); printf("Do you want to save your current changes? (Y/N)"); reset();
								printf("\n>> ");
								scanf(" %c", &confirmation);

								if (confirmation == 'Y' || confirmation == 'y'){
									strcpy(questions[ validNums[numInput - 1] ].choice1, tempChoice);
									system("cls");
									green(); printf("Changes Saved!\n\n"); reset();
									editInput = 7;
									numInput = -1;
									// input[0] = '1';
								}

								else{
									system("cls");
									red(); printf("Changes Discarded.\n\n"); reset();
									editInput = 7;
									numInput = -1;
								}

								break;

							case 4:
								printf("\n");
								printf("Input New [Choice 2]: ");
								scanf(" %[^\n]s", tempChoice);
								yellow(); printf("Do you want to save your current changes? (Y/N)"); reset();
								printf("\n>> ");
								scanf(" %c", &confirmation);

								if (confirmation == 'Y' || confirmation == 'y'){
									strcpy(questions[ validNums[numInput - 1] ].choice2, tempChoice);
									system("cls");
									green(); printf("Changes Saved!\n\n"); reset();
									editInput = 7;
									numInput = -1;
									// input[0] = '1';
								}

								else{
									system("cls");
									red(); printf("Changes Discarded.\n\n"); reset();
									editInput = 7;
									numInput = -1;
								}

								break;

							case 5:
								printf("\n");
								printf("Input New [Choice 3]: ");
								scanf(" %[^\n]s", tempChoice);
								yellow(); printf("Do you want to save your current changes? (Y/N)"); reset();
								printf("\n>> ");
								scanf(" %c", &confirmation);

								if (confirmation == 'Y' || confirmation == 'y'){
									strcpy(questions[ validNums[numInput - 1] ].choice3, tempChoice);
									system("cls");
									green(); printf("Changes Saved!\n\n"); reset();
									editInput = 7;
									numInput = -1;
									// input[0] = '1';
								}

								else{
									system("cls");
									red(); printf("\nChanges Discarded.\n\n"); reset();
									editInput = 7;
									numInput = -1;
								}

								break;

							case 6:
								printf("\n");
								printf("Input New [Answer]: ");
								scanf(" %[^\n]s", tempAnswer);
								yellow(); printf("Do you want to save your current changes? (Y/N)"); reset();
								printf("\n>> ");
								scanf(" %c", &confirmation);

								if (confirmation == 'Y' || confirmation == 'y'){
									strcpy(questions[ validNums[numInput - 1] ].answer, tempAnswer);
									system("cls");
									green(); printf("Changes Saved!\n\n"); reset();
									editInput = 7;
									numInput = -1;
									// input[0] = '1';
								}

								else{
									system("cls");
									red(); printf("Changes Discarded.\n\n"); reset();
									editInput = 7;
									numInput = -1;
								}

								break;

							case 7:
								numInput = -1;
								system("cls");
								break;

							default:
								red(); printf("Invalid input!"); reset();
								printf("\n");
								break;
						}
					
					}

					// Re-sorts the questions array if needed
					sortQuestions(questions, *totalQuestions);
				}

				else{
					numInput = -1; // resets numInput value so loop will run for the next instance
					system("cls");
				}
			}

			/* If it does not exist, prompt the user to enter a valid input again;
				second conditional is to prevent error message from appearing if user wants to exit */
			else if (exists == 0 && input[0] != '1'){
				system("cls");
				red(); printf("Invalid Input!\n\n"); reset();
			}
			
			if (input[0] == '1')
				system("cls");
		}
	}

	// If total questions are 0, an error message will be shown
	else{
		red(); printf("No questions found!\n"); reset();
	}


}
/*
	Function that handles deleting individual question records 
	Precondition: All structs and members are valid, totalQuestions are greater than or equal to 0
	@param questions is the struct questionData array for storing questions 
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@return void
*/
void deleteRecord(struct questionData questions[MAX_QUESTIONS], int* totalQuestions){

	// Increment variables
	int i;

	// Variables for strings (for input and for storing/sorting topics)
	char input[20];

	// Checking (bool) variables
	int exists;

	// buffer variables
	int buffer;
	char delSure;

	// If total questions is greater than 0, proceed
	if (*totalQuestions > 0){

		// The while loop will continue until the user enters '1', or a string that starts with '1'
		while (input[0] != '1'){

			yellow(); printf("Type the Topic of the Question you wish to Delete\nEnter [1] to Go Back\n"); reset();
			displayTopics(questions, totalQuestions);

			// Gets user input, will be case sensitive
			printf("\n>> ");
			scanf(" %[^\n]s", input);

			if (input[0] == '1')
				system("cls");

			exists = 0;

			// This loop will scan the questions struct array for topics if the input exists
			for (i = 0; i < *totalQuestions; i++){
				if (strcmp(input, questions[i].topic) == 0){
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

				yellow(); printf("\nInput [0] to Exit.\n"); reset();
				printf("Question Numbers Associated with the Topic:\n"); 

				// Looks through the questions struct array for the question index associated with the inputted topic and stores them in the validNums array
				for (i = 0; i < *totalQuestions; i++){
					if (strcmp(input, questions[i].topic) == 0){
						printf("Question #[%d]: %s\n", questions[i].questionNumber, questions[i].question);
						validNums[k] = i;
						k++;
					}
				}

				// Continues asking for input until user enters a valid input
				while (numInput > topicQns || numInput < 0){
					printf("\n>> ");

					// scanf is buffered so that character misinputs will not result in an infinite loop
					buffer = scanf("%d", &numInput);
					if (buffer == 0) {
            			numInput = getchar(); // catches the character input
        			}

					// prints an error message if the selected number is out of range
					if (numInput > topicQns || numInput < 0){
						red(); printf("Invalid Input!\n"); reset();
					}
				}

				if (numInput != 0){
		
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
							
						else{ 
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
							
						system("cls");
						red(); printf("Successfully deleted.\n\n"); reset();
						numInput = -1;
						// input[0] = '1';
					}

					else{ // if user types 'N' or any other input deletion will be aborted
						system("cls");
						green(); printf("Deletion aborted.\n\n"); reset();
						numInput = -1;
						// input[0] = '1';
					}
		
				}

				else{
					system("cls");
					numInput = -1;
				}
			}

			/* If topic input not exist, prompt the user to enter a valid input again;
				second conditional is to prevent error message from appearing if user wants to exit */
			else if (exists == 0 && input[0] != '1'){
				system("cls");
				red(); printf("Invalid Input!\n\n"); reset();
			}


		}

	}

		// If total questions are 0, an error message will be shown
	else{
		red(); printf("No questions found!\n"); reset();
	}

}

/*
	Function for importing data from a file (either player data or questions)
	Precondition: All structs and members are valid, totalPlayers and totalQuestions are greater than or equal to 0, scores.txt has been initialized and opened
	@param questions is the struct questionData array for storing questions 
	@param players is the struct playerData array for storing player data (scores and names)
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@param *totalPlayers is the pointer to the variable in main storing the total number of players currently being stored in the program
	@return void
*/
void importData(struct questionData questions[MAX_QUESTIONS], int* totalQuestions, struct playerData players[MAX_PLAYERS], int *totalPlayers){

	// Increment variable
	int i;
	int j, k;
	int tempQnNumber = 1;

	// File variable declaration
	FILE *fp;
	FILE *fpd; // scores.txt

	fpd = fopen("scores.txt", "a");
	
	// Input variables
	char selection;
	char press;
	string30 input;
	string20 tempTopic;

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
					
					green(); printf("Enter File Name: "); reset();
					scanf(" %[^\n]s", input);

					// Reads from inputted txt file, stores into questions array;
					fp = fopen(input, "r");

					// If file does not exist, print error message and option to retry
					if (fp == NULL){
						red(); printf("\nFile not found!\n"); reset();
						yellow(); printf("Press [1] to return to the previous menu\nPress any key to try again\n"); reset();
						press = _getch();
						if (press == '1'){
							selection = '3';
							system("cls");
						}
							
						
					}

					// If file exits, importing will start
					else{
					
						// Scans the file for each number until the end of file is reached, then stores them into array data

						while (
								fscanf(fp, " %[^\n]s", tempTopic) != EOF &&
								fscanf(fp, " %d", &questions[i].questionNumber) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].question) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].choice1) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].choice2) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].choice3) != EOF &&
								fscanf(fp, " %[^\n]s", questions[i].answer) != EOF	
							){
								tempQnNumber = 1;
								for (j = 0; j < i; j++) {
									if (strcmp(tempTopic, questions[j].topic) == 0 && questions[j].questionNumber >= tempQnNumber) {
										tempQnNumber = questions[j].questionNumber + 1;
									}
								}
								// temporary adjustment to question number to ensure that new questions will have a higher number than existing ones
								if (tempQnNumber != 0) {
									questions[i].questionNumber = tempQnNumber;
								}
								strcpy(questions[i].topic, tempTopic);

								// i will be the total number of questions read from the file	
								i++;
						}
						
						// The total questions read from the file will be added to the tally of total questions
						*totalQuestions = i;

						// The struct array is sorted
						sortQuestions(questions, *totalQuestions);

						// After the loop is complete, prints a success message and exits the menu
						fclose(fp);
						system("cls");
						green(); printf("Import Complete!\n"); reset();
						press = '1';
						selection = '3';
						
					}
				}
				break;
			
			case '2':
				i = *totalPlayers;
				j = 0;
				while (press != '1'){
					
					green(); printf("Enter File Name: "); reset();
					scanf(" %[^\n]s", input);

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

							// i will be the total number of players after reading	
							i++;
							// j will be the number of scores read from the current file
							j++;
						}

						// Appends the current data to scores.txt
						fseek(fpd, 0, SEEK_END);
						for (k = *totalPlayers; k < i; k++){
							if (ftell(fpd) == 0){
								fprintf(fpd, "%s\n", players[k].name);
								fprintf(fpd, "%d", players[k].score);
							}
							else{
								fprintf(fpd, "\n\n%s\n", players[k].name);
								fprintf(fpd, "%d", players[k].score);
							}
						}
						// The total questions read from the file will be added to the tally of total questions
						*totalPlayers = i;

						// After the loop is complete, prints a success message and exits the menu

						// The struct array is sorted at the end of the function
						sortScores(players, *totalPlayers);

						fclose(fp);
						fclose(fpd);
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

/*
	Function for exporting data to a file (either player data or questions)
	Precondition: All structs and members are valid, totalPlayers and totalQuestions are greater than or equal to 0, scores.txt has been initialized and opened
	@param questions is the struct questionData array for storing questions 
	@param players is the struct playerData array for storing player data (scores and names)
	@param *totalQuestions is the pointer to the variable in main storing the total number of questions currently being stored in the program
	@param *totalPlayers is the pointer to the variable in main storing the total number of players currently being stored in the program
	@return void
*/
void exportData(struct questionData questions[MAX_QUESTIONS], int* totalQuestions, struct playerData players[MAX_PLAYERS], int *totalPlayers){

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
				if (*totalQuestions > 0){
					green(); printf("Enter File Name: "); reset();
					scanf(" %[^\n]s", input);
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
					system("cls");
					green(); printf("Export complete!\n"); reset();
					selection = '3';
				}
				else{
					system("cls");
					red(); printf("No questions found!\n"); reset();
				}
				break;
			
			case '2':
				if (*totalPlayers > 0){
					green(); printf("Enter File Name: "); reset();
					scanf(" %[^\n]s", input);
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
					system("cls");
					green(); printf("Export complete!\n"); reset();
					selection = '3';
				}
				else{
					system("cls");
					red(); printf("No players found!\n"); reset();
				}
				break;

			case '3':
				system("cls");
				break;
		}

	}

}


/* ================================ */

/*
	Main function
	@return 0
*/
int main(){
	
	system("cls");
	char input;
	int totalQuestions = 0, totalPlayers = 0;
	struct questionData questions[MAX_QUESTIONS];
	struct playerData players[MAX_PLAYERS];
	pwd correctPassword = "password69"; // correct password for admin panel

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
				passwordScreen(questions, players, &totalQuestions, &totalPlayers, correctPassword);
				
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



