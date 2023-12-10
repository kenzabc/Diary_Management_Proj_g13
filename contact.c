//
// Created by kenza on 10/12/2023.
//

#include "contact.h"
#include "ctype.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void LowerCase(char *string){
    if (string == NULL) {
        return;
    }

    for (int i = 0; string[i] != '\0'; ++i) {
        string[i] = tolower(string[i]);
    }
}

void insertStringInSortedFile(const char *myString) {
    FILE *file = fopen("../contacts.txt", "r+");

    if (file != NULL) {
        char lines[100][100];
        int nbLines = 0;

        while (fgets(lines[nbLines], sizeof(lines[0]), file) != NULL) {
            nbLines++;
        }

        int insertIndex = 0;
        while (insertIndex < nbLines && strcmp(myString, lines[insertIndex]) > 0) {
            insertIndex++;
        }

        for (int i = nbLines; i > insertIndex; i--) {
            strcpy(lines[i], lines[i - 1]);
        }

        strcpy(lines[insertIndex], myString);
        nbLines++;

        rewind(file);

        for (int i = 0; i < nbLines; i++) {
            fprintf(file, "%s", lines[i]);
            if (i == insertIndex) {
                fprintf(file, "\n");
            }
        }
        fclose(file);
    } else {
        printf("We could not open the file contacts.txt\n");
    }
}
contact *createContact(char *firstName, char *lastName, int nbLevels){
    LowerCase(firstName);
    LowerCase(lastName);

    size_t totalLength = strlen(firstName) + strlen("_") + strlen(lastName) + 1;
    char fullName[totalLength];
    strcpy(fullName, lastName);
    strcat(fullName, "_");
    strcat(fullName, firstName);
    printf("New contact %s created\n", fullName);

    char *contactName = (char*)malloc(totalLength);
    strcpy(contactName, fullName);

    insertStringInSortedFile(fullName);

    contact *newContact = (contact*)malloc(sizeof (contact));
    newContact->name = contactName;
    newContact->myAppointments = NULL;
    newContact->nb_appointments=0;
    newContact->nb_levels = 4;
    newContact->next = (contact**)malloc(sizeof(contact*) *nbLevels);

    return newContact;
}

contact *initializeContact(char *fullname, int nbLevels){
    contact *Contact = (contact*)malloc(sizeof (contact));
    Contact->name = (char*)malloc(strlen(fullname) + 1);
    strcpy(Contact->name, fullname);
    Contact->nb_appointments=0;
    Contact->myAppointments = NULL;
    Contact->nb_levels = 4;
    Contact->next = (contact**)malloc(sizeof(contact*) *nbLevels);

    return Contact;
}

t_d_listcontact *createListContact(int maxLevels){
    t_d_listcontact *myList = (t_d_listcontact*)malloc(sizeof(t_d_listcontact));
    myList->maxLevels = maxLevels;

    myList->heads = (contact **)malloc(sizeof (contact *) * maxLevels);

    for(int i=0; i<maxLevels; i++){
        myList->heads[i] = NULL;
    }
    return myList;
}
void insertContact(t_d_listcontact *myList, contact *myContact){
    for (int i=0; i<myContact->nb_levels; i++){
        contact *tempContact = myList->heads[i];
        myList->heads[i] = myContact;
        myContact->next[i] = tempContact;
    }
}
void displayLevelContact(t_d_listcontact *myList, int level){
    if (myList->heads[level]!=NULL){
        contact *tempContact = myList->heads[level];
        printf("[list head_%d @- ]-->", level);
        while (tempContact != NULL) {
            printf("[ %s|@- ]-->", tempContact->name);
            tempContact = tempContact->next[level];
        }
        printf("NULL\n");
    } else {
        printf("No contacts");
    }
}

void displayAllLevelsContact(t_d_listcontact *myList){
    if (myList->heads[0]!=NULL) {
        for (int i = 0; i < myList->maxLevels; i++) {
            displayLevelContact(myList, i);
        }
    } else {
        printf("No contacts");
    }
}

void initializeContacts(t_d_listcontact *myList){
    FILE *file = fopen("../contacts.txt", "r+");

    if(file != NULL){
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            size_t newlineIndex = strcspn(line, "\n");
            line[newlineIndex] = '\0';
            contact *myContact = initializeContact(line, 5);
            insertContact(myList, myContact);
        }
        fclose(file);
    } else {
        printf("There is no contacts.");
    }
}

void displayContacts(t_d_listcontact *myList){
    contact *tempContact = myList->heads[0];
    if (tempContact != NULL){
        while(tempContact != NULL){
            printf("- %s\n", tempContact->name);
            tempContact = tempContact->next[0];
        }
    } else {
        printf("No contacts in the list\n");
    }
}
contact *setContactSelected(t_d_listcontact *myList, char* fullname){
    contact *tempContact = myList->heads[0];
    if (tempContact != NULL){
        while(tempContact != NULL){
            if (strcmp(tempContact->name, fullname) == 0) {
                return tempContact;
            }
            tempContact = tempContact->next[0];
        }
    }
    return NULL;
}