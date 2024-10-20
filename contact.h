#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

// #define MAX_CONTACTS 100

typedef struct Contact{
    char name[50];
    char phone[20];
    char email[50];
    char DOB[20];
    char note[50];
} Contact;

typedef struct {
    // Contact contacts[MAX_CONTACTS];
    Contact *contacts;
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveAndExit(AddressBook* AddressBook);
void loadContactsFromFile(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

void display(AddressBook* addressBook,int position);

void numberValidation1(AddressBook *addressBook, char *dup);
void numberValidation2(AddressBook *addressBook, char *dup);
void numberValidation3(AddressBook *addressBook, char *dup);
void emailValidation1(AddressBook *addressBook, char *dup);
void emailValidation2(AddressBook *addressBook, char *dup);

void nameSearch(AddressBook *addressBook);
int numberSearch(AddressBook *addressBook);
int emailSearch(AddressBook *addressBook);
int dobSearch(AddressBook *addressBook);

int duplicateName(AddressBook *addressBook);

void editName(AddressBook* addressBook, int position);
void editNumber(AddressBook* addressBook, int position);
void editEmail(AddressBook* addressBook, int position);
void editDOB(AddressBook* addressBook, int position);
void editNote(AddressBook* addressBook, int position);
void editOption(AddressBook* addressBook, int position);

void deleteOption(AddressBook* addressBook, int position);
void deletePerson(AddressBook* addressBook,  int position);

#endif
