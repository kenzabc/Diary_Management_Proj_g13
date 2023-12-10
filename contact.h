//
// Created by kenza on 10/12/2023.
//

#ifndef DIARY_MANAGEMENT_PROJ_G13_CONTACT_H
#define DIARY_MANAGEMENT_PROJ_G13_CONTACT_H
#include "appointments.h"

typedef struct s_contact
{
    char *name;
    appointment **myAppointments;
    int nb_levels;
    int nb_appointments;
    struct s_contact **next;
} contact;
typedef struct s_d_listcontact
{
    int maxLevels;
    contact **heads;
} t_d_listcontact;
void LowerCase(char *string);
void insertStringInSortedFile(const char *myString);
contact *createContact(char *firstName, char *LastName, int nbLevels);
contact *initializeContact(char *fullname, int nbLevels);
t_d_listcontact *createListContact(int maxLevels);
void insertContact(t_d_listcontact *myList, contact *myContact);

void displayContacts(t_d_listcontact *myList);

void displayLevelContact(t_d_listcontact *myList, int level);
void displayAllLevelsContact(t_d_listcontact *myList);

contact *setContactSelected(t_d_listcontact *myList, char* fullname);

void initializeContacts(t_d_listcontact *myList);
#endif //DIARY_MANAGEMENT_PROJ_G13_CONTACT_H
