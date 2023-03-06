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
#define MAX_SENTENCE 129
#define TERMINATE MAX_LENGTH
#define ENTER 13
#define BACKSPACE 127

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

// String input function for strings with shorter length
void getShortStrInput(char string[]){
	char ch;
	int i = 0;

	do {
		scanf("%c", &ch);
		if (ch != '\n'){
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
void passwordPrototype(){
	
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

			if (input == 8){
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
	    	adminPanel();
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
void playPanel(){
	
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
void adminPanel(){

	char input;
	
	while (input != '6'){
		displayAdminMenu();
		cyan(); printf("\n[Press the number corresponding to your selection.]\n"); reset();
		input = _getch();
		
		switch(input){
			
			case '1':
				system("cls");
				printf("addRecord(); \n");
				
				break;
				
			case '2':
				system("cls");
				printf("editRecord(); \n");
				
				break;

			case '3':
				system("cls");
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

/* ================================ */

int main(){
	

	char input;
	questionData questions[MAX_QUESTIONS];
	playerData players[MAX_PLAYERS];

	while (input != '3'){
		
		displayMainMenu();
		cyan(); printf("\n[Press the number corresponding to your selection.]\n"); reset();
		input = _getch();
		
		switch(input){
			
			case '1':
				system("cls");
				playPanel();
		
				break;
				
			case '2':
				system("cls");
				passwordPrototype();
				
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



