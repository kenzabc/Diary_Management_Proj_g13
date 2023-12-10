//
// Created by kenza on 10/12/2023.
//

#ifndef DIARY_MANAGEMENT_PROJ_G13_APPOINTMENTS_H
#define DIARY_MANAGEMENT_PROJ_G13_APPOINTMENTS_H
struct s_contact;
struct s_d_listcontact;


typedef struct s_appointment{
    int DateDay;
    int DateMonth;
    int DateYear;
    int TimeHour;
    int TimeMinute;
    int LengthMinute;
    char *Purpose;
} appointment;
void insertAppointmentAtBeginning(appointment *myAppointment, char *owner);
appointment *createAppointment(int day, int month, int year, int hour, int lengthMinute, char *purpose, char *owner);
void addAppointmentToContact(struct s_contact *myContact, appointment *newAppointment);
void displayAppointment(appointment *myAppointment);
void displayAppointments(struct s_contact *myContact);
void displayAppointmentsForAllContacts(struct s_d_listcontact*myList);
void displayFileAppointments(char* fullname);
void deleteAppointment(struct s_contact *myContact, int appointmentIndex);
void saveAllAppointments(struct s_d_listcontact *myList);
void loadAppointmentsFromFile(struct s_d_listcontact*myList, const char *contactName);
void loadAppointmentsForAllContacts(struct s_d_listcontact *myList);

#endif //DIARY_MANAGEMENT_PROJ_G13_APPOINTMENTS_H
