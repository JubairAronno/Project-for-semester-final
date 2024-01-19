
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int rollnumber;
    char name[111];
    float cgpa;
    char gender;
    struct student* next;
};

int boycount = 0;
int girlcount = 0;

void addstudent(struct student** head, int rollnumber, const char* name, float cgpa, char gender) {
    for (struct student* current = *head; current != NULL; current = current->next) {
        if (current->rollnumber == rollnumber) {
            printf("Roll number %d already exists. Please enter another roll.\n", rollnumber);
            return;
        }
    }

    struct student* newstudent = (struct student*)malloc(sizeof(struct student));

    if (newstudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newstudent->rollnumber = rollnumber;
    strncpy(newstudent->name, name, sizeof(newstudent->name) - 1);
    newstudent->name[sizeof(newstudent->name) - 1] = '\0';
    newstudent->cgpa = cgpa;
    newstudent->gender = gender;

    if (gender == 'MALE' || gender == 'male') {
        boycount++;
    } else if (gender == 'FEMALE' || gender == 'female') {
        girlcount++;
    }

    newstudent->next = *head;
    *head = newstudent;

    printf("Student added.\n");
}

void findStudentByRollNumber(struct student* head, int rollnumber) {
    while (head != NULL) {
        if (head->rollnumber == rollnumber) {
            printf("\nStudent found:\n");
            printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", head->rollnumber, head->name, head->cgpa, head->gender);
            return;
        }
        head = head->next;
    }
    printf("Student with roll number %d not found.\n", rollnumber);
}