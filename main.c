#include <stdio.h>
#include "contact.h"
#include<stdlib.h>

int main() 
{
    int choice;
	// creating a Addressbook  variable 
    AddressBook addressBook;
	// function  to add contact from file to array of sturcture 
	loadContactsFromFile(&addressBook);
    do 
    {
		// display  menu 
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. save\n");
	printf("Enter your choice: ");
	// reading  user choice 
	scanf("%d", &choice);
	switch (choice) 
	{
	    case 1:
		// funciton  to add contact 
		createContact(&addressBook);
		break;
	    case 2:
		// function calling  to search contact 
		searchContact(&addressBook);
		break;
	    case 3:
		// function calling to edit contact 
		editContact(&addressBook);
		break;
	    case 4:
		// function  calling to delete contact 
		deleteContact(&addressBook);
		break;
	    case 5:
		// function  calling to list all contacts 
		listContacts(&addressBook);
		break;
	    case 6:
		// function calling  to save contact 
			printf("Saving and Exiting...\n");
			saveAndExit(&addressBook);
			break;
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);
    return 0;
}
