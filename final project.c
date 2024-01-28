
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

void addStudent(struct student** head, int rollnumber, const char* name, float cgpa, char gender) {
    for (struct student* current = *head; current != NULL; current = current->next) {
        if (current->rollnumber == rollnumber) {
            printf("Roll number %d already exists. Please enter another roll.\n", rollnumber);
            return;
        }
    }

    do {
        printf("Enter gender (M/F): ");
        scanf(" %c", &gender);

        if (gender == 'M' || gender == 'm') {
            boycount++;
            break;
        } else if (gender == 'F' || gender == 'f') {
            girlcount++;
            break;
        } else {
            printf("Error: Invalid gender. Please enter 'M' for male or 'F' for female.\n");
            printf("Please try again.\n");
        }
    } while (1);

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

void findStudentsByFirstName(struct student* head, const char* firstName) {
    printf("\nStudents with the first name %s:\n", firstName);
    int found = 0;
    while (head != NULL) {
        if (strncmp(head->name, firstName, strlen(firstName)) == 0) {
            printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", head->rollnumber, head->name, head->cgpa, head->gender);
            found = 1;
        }
        head = head->next;
    }
    if (!found) {
        printf("No students with the first name %s found.\n", firstName);
    }
}

int countStudents(struct student* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

void deleteStudent(struct student** head, int rollnumber) {
    struct student* current = *head;
    struct student* prev = NULL;

    while (current != NULL) {
        if (current->rollnumber == rollnumber) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Student with roll number %d deleted successfully.\n", rollnumber);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Student with roll number %d not found.\n", rollnumber);
}

void updateStudent(struct student* head, int rollnumber) {
    while (head != NULL) {
        if (head->rollnumber == rollnumber) {
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
        head = head->next;
    }
    printf("Student with roll number %d not found.\n", rollnumber);
}

void determineWaiver(struct student* head) {
    while (head != NULL) {
        printf("Student %s is %s for waiver.\n", head->name, (head->cgpa > 4.0) ? "eligible" : "not eligible");
        head = head->next;
    }
}

void printGenderCounts() {
    printf("\nCount of Students:\n");
    printf("Boys: %d\n", boycount);
    printf("Girls: %d\n", girlcount);
}

void printStudents(struct student* head) {
    printf("\nList of Students:\n");
    while (head != NULL) {
        printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", head->rollnumber, head->name, head->cgpa, head->gender);
        head = head->next;
    }
}

void freeList(struct student* head) {
    while (head != NULL) {
        struct student* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct student* head = NULL;
    int rollnumber, choice;
    char name[111], firstName[111], gender;
    float cgpa;

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Find Students by First Name\n");
        printf("4. Count of Students\n");
        printf("5. Delete Student\n");
        printf("6. Update Student\n");
        printf("7. Store CGPA and check if they can get Waiver or not\n");
        printf("8. Print Gender Counts\n");
        printf("9. Print Students\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student data:\n");
                printf("Name: ");
                scanf("%s", name);
                printf("Roll Number: ");
                scanf("%d", &rollnumber);
                printf("CGPA: ");
                scanf("%f", &cgpa);

                addStudent(&head, rollnumber, name, cgpa, gender);
                break;

            case 2:
                printf("Enter roll number to find: ");
                scanf("%d", &rollnumber);
                findStudentByRollNumber(head, rollnumber);
                break;

            case 3:
                printf("Enter first name to find: ");
                scanf("%s", firstName);
                findStudentsByFirstName(head, firstName);
                break;

            case 4:
                printf("Total number of students: %d\n", countStudents(head));
                break;

            case 5:
                printf("Enter roll number to delete: ");
                scanf("%d", &rollnumber);
                deleteStudent(&head, rollnumber);
                break;

            case 6:
                printf("Enter roll number to update: ");
                scanf("%d", &rollnumber);
                updateStudent(head, rollnumber);
                break;

            case 7:
                determineWaiver(head);
                break;

            case 8:
                printGenderCounts();
                break;

            case 9:
                printStudents(head);
                break;

            case 10:
                freeList(head);
                printf("Program exited.\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 10);

    return 0;
}

