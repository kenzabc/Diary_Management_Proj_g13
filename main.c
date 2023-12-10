//
// Created by kenza on 10/12/2023.
//
#include "cell.h"
#include "list.h"
#include "stdio.h"
#include "timer.h"
#include "contact.h"
#include <string.h>
#include <stdlib.h>
#include "appointments.h"

int main() {
    t_d_listcontact *myList = createListContact(5);
    initializeContacts(myList);

    int option;
    char firstName[50], lastName[50];

    do {
        printf("\nDIARY MANAGEMENT APPLICATION MENU\n");
        printf("==================================\n");
        printf("1. Search for a contact\n");
        printf("2. View a contact's appointments\n");
        printf("3. Create a contact\n");
        printf("4. Create an appointment for a contact\n");
        printf("5. Delete an appointment\n");
        printf("6. Save all appointments to file\n");
        printf("7. Load appointments from file\n");
        printf("8. Exit\n");
        printf("==================================\n");

        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the first name: ");
                scanf("%s", firstName);

                printf("Enter the last name: ");
                scanf("%s", lastName);

                LowerCase(firstName);
                LowerCase(lastName);

                char fullName[100];
                snprintf(fullName, sizeof(fullName), "%s_%s", lastName, firstName);

                contact *searchedContact = setContactSelected(myList, fullName);
                if (searchedContact != NULL) {
                    printf("Contact found: %s\n", searchedContact->name);
                } else {
                    printf("Contact not found\n");
                }
                break;

            case 2:
                printf("Enter the first name: ");
                scanf("%s", firstName);

                printf("Enter the last name: ");
                scanf("%s", lastName);

                LowerCase(firstName);
                LowerCase(lastName);

                char viewFullName[100];
                snprintf(viewFullName, sizeof(viewFullName), "%s_%s", lastName, firstName);

                contact *viewContact = setContactSelected(myList, viewFullName);
                if (viewContact != NULL) {
                    displayAppointments(viewContact);
                } else {
                    printf("Contact not found\n");
                }
                break;

            case 3:
                printf("Enter the first name: ");
                scanf("%s", firstName);

                printf("Enter the last name: ");
                scanf("%s", lastName);

                LowerCase(firstName);
                LowerCase(lastName);

                char createFullName[100];
                snprintf(createFullName, sizeof(createFullName), "%s_%s", lastName, firstName);

                contact *newContact = createContact(firstName, lastName, 5);
                insertContact(myList, newContact);
                break;

            case 4:
                printf("Enter the first name: ");
                scanf("%s", firstName);

                printf("Enter the last name: ");
                scanf("%s", lastName);

                LowerCase(firstName);
                LowerCase(lastName);

                char appointmentFullName[100];
                snprintf(appointmentFullName, sizeof(appointmentFullName), "%s_%s", lastName, firstName);

                contact *appointmentContact = setContactSelected(myList, appointmentFullName);
                if (appointmentContact != NULL) {
                    int day, month, year, hour, length;
                    char purpose[100];

                    printf("Enter appointment details:\n");
                    printf("Day (1-31): ");
                    scanf("%d", &day);

                    printf("Month (1-12): ");
                    scanf("%d", &month);

                    printf("Year: ");
                    scanf("%d", &year);

                    printf("Hour (0-23): ");
                    scanf("%d", &hour);

                    printf("Length (minutes): ");
                    scanf("%d", &length);

                    printf("Purpose: ");
                    scanf("%s", purpose);

                    appointment *newAppointment = createAppointment(day, month, year, hour, length, purpose, appointmentFullName);
                    addAppointmentToContact(appointmentContact, newAppointment);
                    insertAppointmentAtBeginning(newAppointment, appointmentFullName);
                } else {
                    printf("Contact not found\n");
                }
                break;
            case 5:
                printf("Enter the first name: ");
                scanf("%s", firstName);

                printf("Enter the last name: ");
                scanf("%s", lastName);

                LowerCase(firstName);
                LowerCase(lastName);

                char deleteFullName[100];
                snprintf(deleteFullName, sizeof(deleteFullName), "%s_%s", lastName, firstName);

                contact *deleteContact = setContactSelected(myList, deleteFullName);
                if (deleteContact != NULL) {
                    printf("Appointments of %s:\n", deleteContact->name);
                    displayAppointments(deleteContact);

                    int appointmentIndex;
                    printf("Enter the index of the appointment to delete: ");
                    scanf("%d", &appointmentIndex);

                    deleteAppointment(deleteContact, appointmentIndex - 1);  // -1 because the displayed index starts from 1
                } else {
                    printf("Contact not found\n");
                }
                break;

            case 6:
                saveAllAppointments(myList);
                break;

            case 7:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid option. Please enter a valid option.\n");
        }
    } while (option != 7);

    return 0;
}
