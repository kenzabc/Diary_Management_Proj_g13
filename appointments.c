//
// Created by kenza on 10/12/2023.
//

#include "appointments.h"
#include <stdlib.h>
#include <stdio.h>
#include "contact.h"
#include "string.h"

void insertAppointmentAtBeginning(appointment *myAppointment, char *owner) {
    char filename[100];
    sprintf(filename, "../knownContacts/%s.txt", owner);
    FILE *file = fopen(filename, "a+");

    if (file != NULL) {
        char lines[500][500];
        int nbLines = 0;
        while (fgets(lines[nbLines], sizeof(lines[0]), file) != NULL) {
            nbLines++;
        }

        fclose(file);
        file = fopen(filename, "w");

        if (file != NULL) {
            char myString[500];
            sprintf(myString, "%s %d/%d/%d %d %d %s", owner,myAppointment->DateDay, myAppointment->DateMonth, myAppointment->DateYear, myAppointment->TimeHour, myAppointment->LengthMinute, myAppointment->Purpose);

            fprintf(file, "%s\n", myString);

            for (int i = 0; i < nbLines; i++) {
                fprintf(file, "%s", lines[i]);
            }

            fclose(file);
        } else {
            printf("Nous n'avons pas pu réouvrir le fichier en mode 'w' pour l'écraser\n");
        }
    } else {
        printf("Nous n'avons pas pu ouvrir ou créer le fichier %s\n", filename);
    }
}


appointment *createAppointment(int day, int month, int year, int hour, int lengthMinute, char *purpose, char *owner){
    appointment *myAppointment = (appointment*)malloc(sizeof(appointment));
    myAppointment->DateDay = day;
    myAppointment->DateMonth = month;
    myAppointment->DateYear = year;
    myAppointment->TimeHour = hour;
    myAppointment->LengthMinute = lengthMinute;
    myAppointment->Purpose = purpose;

    insertAppointmentAtBeginning(myAppointment, owner);
    return myAppointment;
}
/*
void addAppointmentToContact(struct s_contact *myContact, appointment *newAppointment) {
    myContact->nb_appointments++;
    myContact->myAppointments = (appointment**)realloc(myContact->myAppointments, myContact->nb_appointments * sizeof(appointment*));
    myContact->myAppointments[myContact->nb_appointments - 1] = newAppointment;
}
void displayAppointments(struct s_contact *myContact) {
    printf("Appointments of %s:\n", myContact->name);
    if (myContact->nb_appointments >= 1) {
        for (int i = 0; i < myContact->nb_appointments; i++) {
            displayAppointment(&(myContact->myAppointments[i]));  // Pass the address
        }
    } else {
        printf("None\n");
    }
}
*/
void addAppointmentToContact(struct s_contact *myContact, appointment *newAppointment) {
    myContact->nb_appointments++;
    myContact->myAppointments = realloc(myContact->myAppointments, myContact->nb_appointments * sizeof(appointment*));
    myContact->myAppointments[myContact->nb_appointments - 1] = newAppointment;
}


void displayAppointment(appointment *myAppointment){
    printf("-> %d/%d/%d - %dh for %d min: %s\n", myAppointment->DateDay, myAppointment->DateMonth, myAppointment->DateYear, myAppointment->TimeHour, myAppointment->LengthMinute, myAppointment->Purpose);
}


void displayAppointments(struct s_contact *myContact){
    printf("Appointments of %s:\n", myContact->name);
    if (myContact->nb_appointments >= 1){
        for (int i=0; i<myContact->nb_appointments; i++){
            displayAppointment(myContact->myAppointments[i]);
        }
    } else {
        printf("None\n");
    }
}
void displayAppointmentsForAllContacts(t_d_listcontact *myList) {
    for (int i = 0; i < myList->maxLevels; i++) {
        contact *tempContact = myList->heads[i];
        while (tempContact != NULL) {
            displayAppointments(tempContact);
            tempContact = tempContact->next[i];
        }
    }
}



void displayFileAppointments(char* fullname){
    char filename[100];
    sprintf(filename, "../data/%s.txt", fullname);
    FILE *file = fopen(filename, "r");

    if (file != NULL){
        int i=1;
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            size_t newlineIndex = strcspn(line, "\n");
            line[newlineIndex] = '\0';
            printf("%d - %s\n", i, line);
            i++;
        }
        fclose(file);
    } else {
        printf("You have no appointments saved.\n");
    }
}
// UNTESTED
void deleteAppointment(struct s_contact *myContact, int appointmentIndex) {
    if (appointmentIndex >= 0 && appointmentIndex < myContact->nb_appointments) {
        free(myContact->myAppointments[appointmentIndex]);

        // Shift the remaining appointments to fill the gap
        for (int i = appointmentIndex; i < myContact->nb_appointments - 1; i++) {
            myContact->myAppointments[i] = myContact->myAppointments[i + 1];
        }

        // Decrease the count of appointments
        myContact->nb_appointments--;

        // Resize the array
        myContact->myAppointments = realloc(myContact->myAppointments, myContact->nb_appointments * sizeof(appointment*));

        printf("Appointment deleted successfully.\n");
    } else {
        printf("Invalid appointment index.\n");
    }
}
/*void saveAllAppointments(t_d_listcontact *myList) {
    for (int i = 0; i < myList->maxLevels; i++) {
        contact *tempContact = myList->heads[i];
        while (tempContact != NULL) {
            char filename[100];
            sprintf(filename, "../knownContacts/%s.txt", tempContact->name);
            FILE *file = fopen(filename, "w");

            if (file != NULL) {
                for (int j = 0; j < tempContact->nb_appointments; j++) {
                    fprintf(file, "%s %d/%d/%d %d %d %s\n",
                            tempContact->name,
                            tempContact->myAppointments[j]->DateDay,
                            tempContact->myAppointments[j]->DateMonth,
                            tempContact->myAppointments[j]->DateYear,
                            tempContact->myAppointments[j]->TimeHour,
                            tempContact->myAppointments[j]->LengthMinute,
                            tempContact->myAppointments[j]->Purpose);
                }
                fclose(file);
            } else {
                printf("Could not open or create the file %s\n", filename);
            }

            tempContact = tempContact->next[i];
        }
    }
}
*/
void saveAllAppointments(t_d_listcontact *myList) {
    for (int i = 0; i < myList->maxLevels; i++) {
        contact *tempContact = myList->heads[i];
        while (tempContact != NULL) {
            char filename[100];
            snprintf(filename, sizeof(filename), "../knownContacts/%s.txt", tempContact->name);
            FILE *file = fopen(filename, "w");

            if (file != NULL) {
                for (int j = 0; j < tempContact->nb_appointments; j++) {
                    fprintf(file, "%s %d/%d/%d %d %d %s\n",
                            tempContact->name,
                            tempContact->myAppointments[j]->DateDay,
                            tempContact->myAppointments[j]->DateMonth,
                            tempContact->myAppointments[j]->DateYear,
                            tempContact->myAppointments[j]->TimeHour,
                            tempContact->myAppointments[j]->LengthMinute,
                            tempContact->myAppointments[j]->Purpose);
                }
                fclose(file);
                printf("Appointments saved for %s.\n", tempContact->name);
            } else {
                printf("Could not open or create the file %s\n", filename);
            }

            tempContact = tempContact->next[i];
        }
    }
}

/*
void loadAppointmentsFromFile(t_d_listcontact *myList, const char *contactName) {
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "../knownContacts/%s.txt", contactName);

    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        char line[500];
        while (fgets(line, sizeof(line), file) != NULL) {
            char owner[50];
            int day, month, year, hour, length;
            char purpose[100];

            sscanf(line, "%s %d/%d/%d %d %d %[^\n]",
                   owner, &day, &month, &year, &hour, &length, purpose);

            LowerCase(owner);

            char fullName[100];
            snprintf(fullName, sizeof(fullName), "%s", owner);

            contact *myContact = setContactSelected(myList, fullName);

            if (myContact != NULL) {
                appointment *newAppointment = createAppointment(day, month, year, hour, length, purpose, fullName);
                addAppointmentToContact(myContact, newAppointment);
            }
        }

        fclose(file);
        printf("Appointments loaded successfully.\n");
    } else {
        printf("Could not open the file: %s\n", filepath);
    }
}*/
void loadAppointmentsFromFile(t_d_listcontact *myList, const char *contactName) {
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "../knownContacts/%s.txt", contactName);

    FILE *file = fopen(filepath, "r");
    if (file != NULL) {



        char line[500];
        while (fgets(line, sizeof(line), file) != NULL) {
            char owner[50];
            int day, month, year, hour, length;
            char purpose[100];

            sscanf(line, "%s %d/%d/%d %d %d %[^\n]",
                   owner, &day, &month, &year, &hour, &length, purpose);

            LowerCase(owner);

            char fullName[100];
            snprintf(fullName, sizeof(fullName), "%s", owner);

            contact *myContact = setContactSelected(myList, fullName);

            if (myContact != NULL) {
                appointment *newAppointment = createAppointment(day, month, year, hour, length, purpose, fullName);
                addAppointmentToContact(myContact, newAppointment);
            }
        }

        fclose(file);
        printf("Appointments loaded successfully for %s.\n", contactName);
    } else {
        printf("Could not open the file: %s\n", filepath);
    }
}

// Function to load appointments for all contacts
void loadAppointmentsForAllContacts(t_d_listcontact *myList) {
    for (int i = 0; i < myList->maxLevels; i++) {
        contact *tempContact = myList->heads[i];
        while (tempContact != NULL) {
            // Load appointments for each contact
            loadAppointmentsFromFile(myList, tempContact->name);
            tempContact = tempContact->next[i];
        }
    }
}

