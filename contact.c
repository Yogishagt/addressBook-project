#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// global variable to count number of contents
int count=100;
// list  of contacts
void listContacts(AddressBook *addressBook) 
{
    printf("Name:\t\t    Phone Number:\t Email:\t\t\t  Date of Birth:\t Note:\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%-20s",addressBook->contacts[i].name);
        printf("%-20s",addressBook->contacts[i].phone);
        printf("%-28s",addressBook->contacts[i].email);
        printf("%-20s",addressBook->contacts[i].DOB);
        printf("%-20s\n",addressBook->contacts[i].note);
    }
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
// display content
void display(AddressBook* addressBook,int position){
    printf("Name:\t\t    Phone Number:\t Email:\t\t\t  Date of Birth:\t Note:\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("%-19s %-19s %-25s %-19s %-19s\n",addressBook->contacts[position].name,addressBook->contacts[position].phone,
    addressBook->contacts[position].email,addressBook->contacts[position].DOB,addressBook->contacts[position].note);
}
// number validation for 10 digits
void numberValidation1(AddressBook *addressBook, char *duplicate){
    while(1){
        // checking number contain 10 digits or not
        if(strlen(duplicate)>10 ||  strlen(duplicate)<10){
            printf("please enter a valid phone number:");
            scanf("%s",duplicate);
        }
        else{
            break;
        }
    }
}
// number validation for 10 characters (0 - 9)
void numberValidation2(AddressBook *addressBook, char *duplicate){
    int  flag=0;
    while(1){      
        for(int i=0;i<10;i++){
        if(duplicate[i]>='0'  && duplicate[i]<='9')
            flag=0;
        else{
            printf("please enter a valid phone number:");
            scanf("%s",duplicate);
            flag=1;
            break;
        }
        }
        if(flag==0)
            break;
    }
    // numberValidation1 function calling to revalidate new  number
    numberValidation1(addressBook,duplicate);
}
// number validation to check  if number already exist in the address book
void numberValidation3(AddressBook *addressBook, char *duplicate){
    while(1){
        int flag=0;
        int i=0;
        for( i=0;i<addressBook->contactCount;i++){
            if(strcmp(addressBook->contacts[i].phone,duplicate)){
                flag=0;
            }
            else{
                printf("phone number already exist:\n");
                printf("please enter a valid phone number:");
                scanf("%s",duplicate);
                flag=1;
                break;
            }
        }
        if(flag==0)
            break;
    }
    // numberValidation1 and numberValidation2 function calling to revalidate new  number
    numberValidation1(addressBook,duplicate);
    numberValidation2(addressBook,duplicate);
}
// email  validation to check if entered mail contains  @ and .com
void emailValidation1(AddressBook *addressBook, char *duplicate){
    while(1){
        // checking entered mail contain @.com
        char *dup1=strstr(duplicate,"@");
        if(dup1==NULL){
            printf("please enter a valid Email: ");
            scanf("%s",duplicate);
        }
        else if(*(++dup1) == '.'){
            printf("please enter a valid Email: ");
            scanf("%s",duplicate);
        }
        else if(strstr(duplicate,".com")==NULL){
            printf("please enter a valid Email: ");
            scanf("%s",duplicate);
        }
        else if(strcmp(strstr(duplicate,".com"),".com")){ 
            printf("please enter a valid Email: ");
            scanf("%s",duplicate);
        }
        else{
            // check  for valid email
            if(duplicate[0]>='A' && duplicate[0]<='Z' || duplicate[0]=='@'){
                printf("please enter a valid Email: ");
                scanf("%s",duplicate);
            }else{
                strcpy(addressBook->contacts[addressBook->contactCount].email, duplicate);
                break;
            }
        }
    }
}
// email validation to check if already  exist in the address book
void emailValidation2(AddressBook *addressBook, char *duplicate){
    while(1){
        int flag=0;
        int i=0;
        for( i=0;i<addressBook->contactCount;i++){
            if(strcmp(addressBook->contacts[i].email,duplicate)){
                flag=0;
            }
            else{
                printf("Email already exist:\n");
                printf("please enter a valid Email:");
                scanf("%s",duplicate);
                flag=1;
                break;
            }
        }
        if(flag==0)
            break;
    }
    // revalidating the new  email
    emailValidation1(addressBook,duplicate);
}
// Date of birth validation
void dobValidation(AddressBook  *addressBook, char *duplicate){
    int value=0,dig=0;
    while(1){
        // check for valid date
        int flag=0;
        value=0;
        for(int i=0;i<10;i++){
            if(duplicate[i]=='-'){
                printf("Enter valid Data of Birth:");
                scanf("%s",duplicate);
                flag=1;
                break;
            }
            else if(duplicate[i]!='/'){
                dig=duplicate[i]-'0';
                value=value*10+dig;
                flag=0;
            }
            if(i==2){
                if(value>=32 || value<=0){
                    printf("Enter valid Data of Birth:");
                    scanf("%s",duplicate);
                    flag=1;
                    break;
                }
                else
                    flag=0;

                value=0;
            }
            else if(i==5){
                if(value>=13 || value<=0){
                    printf("Enter valid Data of Birth:");
                    scanf("%s",duplicate);
                    flag=1;
                    break;
                }else
                    flag=0;

                value=0;
            }
            else if(i==9){
                if(value>=2025 || value<=1900){
                    printf("Enter valid Data of Birth:");
                    scanf("%s",duplicate);
                    flag=1;
                    break;
                }
                else
                    flag=0;

                value=0;
            }
        }
        if(flag==0)
            break;
    }
}
// creating the function to add contacts to  the contact list
void createContact(AddressBook *addressBook)
{
    // resizeing the addressbook if  it is full
    if(addressBook->contactCount >= count){
        count = count + 100;
        addressBook->contacts=realloc(addressBook->contacts,count  * sizeof(Contact));

        if((void *)addressBook->contacts==NULL){
                printf("Memory not allocated\n");
                return;
        }
    }
    // adding the name to  the contact
    printf("Enter name: ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
    char duplicate[20];
    printf("Enter phone number: ");
    scanf("%s",duplicate);
    numberValidation1(addressBook,duplicate);
    numberValidation2(addressBook,duplicate);
    numberValidation3(addressBook,duplicate);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, duplicate);
    
    // adding  the email to the contact
    printf("Enter Email: ");
    scanf("%s",duplicate);
    emailValidation1(addressBook,duplicate);
    emailValidation2(addressBook,duplicate);

    // adding  the date  of birth to the contact
    printf("Enter Date of birth: ");
    scanf("%s",duplicate);
    dobValidation(addressBook,duplicate);
    strcpy(addressBook->contacts[addressBook->contactCount].DOB, duplicate);

    // adding some addtional  information to the contact
    printf("Enter Note: ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].note);
    // incresing  the contact count
    addressBook->contactCount++;
}
// name search  function to check  if the name is in the contact list
void nameSearch(AddressBook *addressBook){
    int flag=0;
    char duplicate[50];
    printf("Enter a name : ");
    scanf(" %[^\n]",duplicate);
    printf("Name:\t\t    Phone Number:\t Email:\t\t\t  Date of Birth:\t Note:\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    int position;
    for(int i=0;i<addressBook->contactCount;i++){
        if(!strcmp(addressBook->contacts[i].name,duplicate)){
            position=i; 
            printf("%-19s %-19s %-25s %-19s %-19s\n",addressBook->contacts[position].name,addressBook->contacts[position].phone,
            addressBook->contacts[position].email,addressBook->contacts[position].DOB,addressBook->contacts[position].note);
            flag=1;
        }
    }
    if(flag==0){
        printf("Name not found!");
    }
}
// phone number search  function to check  if the phone number is in the contact list
int numberSearch(AddressBook *addressBook){
    int flag=0,i=0;
    char duplicate[50];
    printf("Enter phone number: ");
    scanf(" %[^\n]",duplicate);
    numberValidation2(addressBook,duplicate);
    flag=0;
    for(i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone,duplicate)){
            flag=1;
        }
        else{
            display(addressBook,i);
            flag=0;
            break;
                
        }
    }
    if(flag==1){
        printf("phone number not found!");
    }
    // returning the  index of the contact
    return i;
}
// email  search  function to check  if the email is in the contact list
int emailSearch(AddressBook *addressBook){
    int flag=0,i=0;
    char duplicate[50];
    printf("Enter Email: ");
    scanf(" %[^\n]",duplicate);
    emailValidation1(addressBook,duplicate);
    flag=0;
    for(i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].email,duplicate)){
            flag=1;
        }
        else{
            display(addressBook,i);
            flag=0;
            break;
                
        }
    }
    if(flag==1){
        printf("Email not found!");
    }
    // returning the  index of the contact
    return i;
}
// function to search date  of birth
int dobSearch(AddressBook *addressBook){
    int flag=0,i,cnt=0;
    char duplicate[50];
    printf("Enter Date of birth: ");
    scanf(" %[^\n]",duplicate);
    dobValidation(addressBook,duplicate);
    flag=0;
    for(i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].DOB,duplicate)){
            flag=1;
        }
        else{
            display(addressBook,i);
            flag=0; 
            cnt++;  
        }
    }
    if(flag==1 && cnt==0){
        printf("Date of birth not found!");
    }
    // returning the  index of the contact
    return i;
}
// function to search contact 
void searchContact(AddressBook *addressBook) 
{
    int i;
    printf("Enter a option\n1. Name \n2. Phone\n3. Email\n4. Date of Birth\nEnter  your choice: ");
    scanf("%d",&i);
    switch (i)
    {
    case 1:
        nameSearch(addressBook);
        break;
    case 2:
        numberSearch(addressBook);
        break;
    case 3:
        emailSearch(addressBook);
        break;
    case 4:
         dobSearch(addressBook);
        break;
    default:
        printf("Invalid input");
        break;
    }
}
// function to check duplicate names of  contacts
int duplicateName(AddressBook *addressBook){
    int dupName[100],flag=0,count=0;
    char duplicate[50];
    printf("Enter a name: ");
    scanf(" %[^\n]",duplicate);
    printf("Name:\t\t    Phone Number:\t Email:\t\t\t  Date of Birth:\t Note:\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    int position;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].name,duplicate)){
            flag=1;
        }
        else{
            position=i;
            printf("%-19s %-19s %-25s %-19s %-19s\n",addressBook->contacts[position].name,addressBook->contacts[position].phone,
            addressBook->contacts[position].email,addressBook->contacts[position].DOB,addressBook->contacts[position].note);
            flag=0;
            dupName[count++]=i;
        }
    }
    if(flag==1 && count==0){
        printf("Name not fount\n");
        return -1;
    }
    if(count==1){
        return dupName[0];
    }
    // giving a option for user to  select duplicate name
    if(count>1){
        printf("which contact do you want to edit\n");
        for(int i=1;i<=count;i++){
            printf("%d\n",i);
        }
        printf("Enter a choice:\n");
        scanf("%d",&count);
        return dupName[count-1];
    }
}
// function to edit name  of contact
void editName(AddressBook* addressBook, int position){
    char duplicate[50];
    printf("Enter new name: ");
    scanf(" %[^\n]",duplicate);
    strcpy(addressBook->contacts[position].name,duplicate);
    display(addressBook,position);
}
// function  to edit phone number of contact
void editNumber(AddressBook* addressBook, int position){
    char duplicate[50];
    printf("Enter new Phone number: ");
    scanf("%s",duplicate);
    numberValidation1(addressBook,duplicate);
    numberValidation2(addressBook,duplicate);
    numberValidation3(addressBook,duplicate);
    strcpy(addressBook->contacts[position].phone,duplicate);
    display(addressBook,position);
}
// function  to edit email of contact
void editEmail(AddressBook* addressBook, int position){
    char duplicate[50];
    printf("Enter new Email: ");
    scanf("%s",duplicate);
    emailValidation2(addressBook,duplicate);
    strcpy(addressBook->contacts[position].email,duplicate);
    display(addressBook,position);
}
// function  to edit date  of birth of contact
void editDOB(AddressBook* addressBook, int position){
    char duplicate[50];
    printf("Enter new Date of birth: ");
    scanf("%s",duplicate);
    dobValidation(addressBook,duplicate);
    strcpy(addressBook->contacts[position].DOB,duplicate);
    display(addressBook,position);
}
// function to edit note 
void editNote(AddressBook* addressBook, int position){
    printf("Enter new Note: ");
    scanf(" %[^\n]",addressBook->contacts[position].note);
    display(addressBook,position);
}  
// function to select  contact to edit
void editOption(AddressBook* addressBook,int position){
    int i=0;
    printf("what do you want to edit\n1. name\n2. Phone number\n3. Email\n4. Date of birth\n5. Note\nEnetr your  choice: ");
    scanf("%d",&i);
    switch(i){
        case 1:
            editName(addressBook,position);
            break;
        case 2:
            editNumber(addressBook,position);
            break;
        case 3:
            editEmail(addressBook,position);
            break;
        case 4:
            editDOB(addressBook,position);
            break;
        case 5:
            editNote(addressBook,position);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}
// function to edit  contact
void editContact(AddressBook *addressBook)
{
    printf("what do you want to edit\n1. name\n2. Phone number\n3. Email\nEnter  your  choice: ");
    int position=0,i=0;
    scanf("%d",&i);
    switch(i){
        case 1:
            position=duplicateName(addressBook);
            if(position!=-1){
                editOption(addressBook, position);
            }
            break;
        case 2:
            position=numberSearch(addressBook);
            editOption(addressBook, position);
            break;
        case 3:
            position=emailSearch(addressBook);
            editOption(addressBook, position);
            break;
        default:
            printf("Invalid choice!");
            break;
    }      
}
// function to delete  contact
void deletePerson(AddressBook* addressBook,int position){
    for(int j=position;j<addressBook->contactCount;j++){
        addressBook->contacts[j]=addressBook->contacts[j+1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully\n");
}
// function to delete  contact by index 
void deleteOption(AddressBook* addressBook, int position){
    if(position!=-1){
        deletePerson(addressBook,position);
    }
}
// function  to delete  contact by name /  number / email / dob
void deleteContact(AddressBook *addressBook)
{
    int i,position;
    printf("Enter a option\n1. Name \n2. Phone\n3. Email\nEnter  your choice: ");
    scanf("%d",&i);
    switch (i)
    {
    case 1:
        position=duplicateName(addressBook);
        deleteOption(addressBook,position);
        break;
    case 2:
        position=numberSearch(addressBook);
        deleteOption(addressBook,position);
        break;
    case 3:
        position=emailSearch(addressBook);
        deleteOption(addressBook,position);
        break;   
    default:
        printf("Invalid input");
        break;
    }
}