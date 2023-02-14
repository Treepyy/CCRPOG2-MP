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
#define TERMINATE MAX_LENGTH
#define ENTER 13
#define BACKSPACE 127


typedef char pwd[MAX_LENGTH];

void adminPanel();

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

// Prototype function for password functionality with hidden input (does not support backspace)
void passwordPrototype(){
	
	// Variable declarations
     int i;
     int active = 1;
     char input;
     char exit = '\0';
     pwd passwordInput;
     pwd correctPassword = "password69";
     
     while (active == 1){
     	
	     printf("Enter your password: ");
	     
	     // For loop for getting password input
	     for(i = 0; i < MAX_LENGTH; i++)
	     {
	        // Gets user input and stores each character of the password into the 'passwordInput' string
			input = _getch();
	        passwordInput[i] = input;
	      
	      	// If the input is not the enter key, prints an asterisk and increments by 1
			if(input != ENTER){    
	            printf("*");
	            if (input == BACKSPACE){
	            	passwordInput[i] = '\0';
	           		putchar('\b');
	           		putchar(' ');
	           		putchar('\b');
				}
	    	}
	    	
	    	// If the input is the enter key, the current index will be set to NULL and the loop will terminate
	        else{
	        	passwordInput[i] = '\0';
	            i = TERMINATE;
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
	
	bold(); printf("|-----------------|\n"); reset();
	bold(); printf("|    Main Menu    |\n"); reset();
	bold(); printf("|                 |\n"); reset();
	bold(); printf("|"); reset();
	yellow(); printf("[1] Manage Data"); reset();
	bold(); printf("  |\n"); reset();
	bold(); printf("|"); reset();
	green(); printf("[2] Play"); reset();
	bold(); printf("         |\n"); reset();
	bold(); printf("|"); reset();
	red(); printf("[3] Exit"); reset();
	bold(); printf("         |\n"); reset();
	bold(); printf("|                 |\n"); reset();
	bold(); printf("|-----------------|\n"); reset();
	
}

void playGame(){
	
	char input;
	
	while (input != '3'){
		printf("MENU_PLAY_GAME\nEnter your selection\n >> ");
		scanf(" %c", &input);
		
		switch(input){
			
			case '1':
				printf("1\n");
				
				break;
				
			case '2':
				printf("2\n");
				
				break;
				
			case '3': // If 'Exit' is chosen, the program is terminated through a return value in the main function.
				printf("Exit\n");
				
				break;
			
			default: 
				// If the input is not within the given parameters, 'invalid input' will be displayed and the main menu will be shown again.
				printf("\nInvalid input. Please select a valid option.\n"); 
				break;
				
		}
	}
	
}

void adminPanel(){

	char input;
	
	while (input != '3'){
		printf("MENU_ADMIN_PANEL\nEnter your selection\n >> ");
		scanf(" %c", &input);
		
		switch(input){
			
			case '1':
				printf("1\n");
				
				break;
				
			case '2':
				printf("2\n");
				
				break;
				
			case '3': // If 'Exit' is chosen, the program is terminated through a return value in the main function.
				printf("Exit\n");
				
				break;
			
			default: 
				// If the input is not within the given parameters, 'invalid input' will be displayed and the main menu will be shown again.
				printf("\nInvalid input. Please select a valid option.\n"); 
				break;
				
		}
	}
	
}

int main(){
	
	char input;
	
	while (input != '3'){
		
		displayMainMenu();
		printf("\nEnter your selection\n >> ");
		scanf(" %c", &input);
		
		switch(input){
			
			case '1':
				system("cls");
				passwordPrototype();
				
				break;
				
			case '2':
				system("cls");
				playGame();
				
				break;
				
			case '3': // If 'Exit' is chosen, the program is terminated through a return value in the main function.
				printf("Thank you for playing!");
				
				break;
			
			default: 
				// If the input is not within the given parameters, 'invalid input' will be displayed and the main menu will be shown again.
				printf("\nInvalid input. Please select a valid option.\n"); 
				break;
				
		}
	}
	
	
	

	return 0;
	
}



