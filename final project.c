
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

void findStudentsByFirstName(struct Student *head, const char *firstName) {
    printf("\nStudents with the first name %s:\n", firstName);
    int found = 0;
    while (head != NULL) {
        if (strncmp(head->name, firstName, strlen(firstName)) == 0) {
            printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", head->rollNumber, head->name, head->cgpa, head->gender);
            found = 1;
        }
        head = head->next;
    }
    if (!found) {
        printf("No students with the first name %s found.\n", firstName);
    }
}


int countStudents(struct Student *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

s
void deleteStudent(struct Student **head, int rollNumber) {
    struct Student *current = *head;
    struct Student *prev = NULL;

    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            if (prev == NULL) {
                // If the student to be deleted is the first in the list
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Student with roll number %d deleted successfully.\n", rollNumber);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Student with roll number %d not found.\n", rollNumber);
}


void updateStudent(struct Student *head, int rollNumber) {
    while (head != NULL) {
        if (head->rollNumber == rollNumber) {
            int choice;
            printf("\nUpdate Menu:\n");
            printf("1. Update Name\n");
            printf("2. Update CGPA\n");
            printf("3. Update Gender\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new name: ");
                    scanf("%s", head->name);
                    break;
                case 2:
                    printf("Enter new CGPA: ");
                    scanf("%f", &head->cgpa);
                    break;
                case 3:
                   printf("Enter new gender (M/F): ");
                    scanf(" %c", &head->gender);
                    break;
                case 4:
                  return;
                default:
                  printf("Invalid choice. Please enter a valid option.\n");
          }
       }
        head = head->next;   }
    printf("Student with roll number %d not found.\n", rollNumber);
}
void determineWaiver(struct Student *head) {
    while (head != NULL) {
        printf("Student %s is %s for waiver.\n", head->name, (head->cgpa > 4.0) ? "eligible" : "not eligible");
        head = head->next;
    }
}
void printGenderCounts() {
printf("\nCount of Students:\n");
printf("Boys: %d\n", boysCount);
printf("Girls: %d\n", girlsCount);
}
void printStudents(struct Student *head) {
    printf("\nList of Students:\n");
    while (head != NULL) {
        printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", head->rollNumber, head->name, head->cgpa, head->gender);
        head = head->next;
}
}
void freeList(struct Student *head) {
while (head != NULL) {
struct Student *temp = head;
head = head->next;
free(temp);
}
}
