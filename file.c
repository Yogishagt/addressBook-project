#include <stdio.h>
#include "file.h"
// #include"contact.h"
#include<string.h>
#include<stdlib.h>
extern int count;
// function  to add contact to  the file from structure 
void saveContactsToFile(AddressBook *addressBook) {
    FILE  *file;
    file= fopen("file.csv", "w");
    // error handling of file  opening
    if(file ==NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(file, "%s,%s,%s,%s,%s,\n", addressBook->contacts[i].name,
        addressBook->contacts[i].phone, addressBook->contacts[i].email, 
        addressBook->contacts[i].DOB, addressBook->contacts[i].note);
    }
    fclose(file);
    free(addressBook->contacts);
}
// function  to read contacts from file to structure
void loadContactsFromFile(AddressBook *addressBook) {
    //allocate the dynamic  memory  for contacts
    addressBook->contacts=malloc(count * sizeof(Contact));
    FILE  *file;
    file = fopen("file.csv", "r");
    // error  handling of  file
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    addressBook->contactCount=0;
    char dup[200],*name,*email,*phone, *dob, *note;
    while((fscanf(file," %[^\n]",dup))==1){
        // reallocating  the memory for contacts
        if(addressBook->contactCount >=count){
            count = count + 100;
            addressBook->contacts=realloc(addressBook->contacts,count * sizeof(Contact));
            if((void *)addressBook->contacts==NULL){
                printf("Memory not allocated\n");
                return;
            }
        }
        // string tokenization 
        name=strtok(dup,",");
        phone=strtok(0, ",");
        email=strtok(0, ",");
        dob=strtok(0, ",");
        note=strtok(0, ",");
        // copying the  values to the structure
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);
        strcpy(addressBook->contacts[addressBook->contactCount].DOB, dob);
        strcpy(addressBook->contacts[addressBook->contactCount++].note, note);
    }
    fclose(file);
}
