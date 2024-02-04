 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNumber;
    char name[50];
    float cgpa;
    char gender;
    struct Student *next;
};

int boysCount = 0;
int girlsCount = 0;

void addStudent(struct Student **head, int rollNumber, const char *name, float cgpa, char gender) {
    while (1) {
        int isDuplicate = 0;
        for (struct Student *current = *head; current != NULL; current = current->next) {
            if (current->rollNumber == rollNumber) {
                printf("Error: Roll number %d already exists. Please enter a unique roll number.\n", rollNumber);
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            break;
        }


        printf("Enter a new roll number: ");
        if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
            printf("Invalid input. Roll number must be a positive integer.\n");
            while (getchar() != '\n');
        }
    }



    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }


    newStudent->rollNumber = rollNumber;
    strncpy(newStudent->name, name, sizeof(newStudent->name) - 1);
    newStudent->name[sizeof(newStudent->name) - 1] = '\0';
    newStudent->cgpa = cgpa;
    newStudent->gender = gender;


    if (gender == 'M' || gender == 'm') {
        boysCount++;
    } else if (gender == 'F' || gender == 'f') {
        girlsCount++;
    }


    newStudent->next = *head;
    *head = newStudent;

    printf("Student added successfully.\n");
}

void findStudentByRollNumber(struct Student *head, int rollNumber) {
    while (head != NULL) {
        if (head->rollNumber == rollNumber) {
            printf("\nStudent found:\n");
            printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", head->rollNumber, head->name, head->cgpa, head->gender);
            return;
        }
        head = head->next;
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

int countStudents(struct Student *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

void deleteStudent(struct Student **head, int rollNumber) {
    struct Student *current = *head;
    struct Student *prev = NULL;

    while (current != NULL) {
        if (current->rollNumber == rollNumber) {

            if (current->gender == 'M' || current->gender == 'm') {
                if (boysCount > 0) {
                    boysCount--;
                }
            } else if (current->gender == 'F' || current->gender == 'f') {
                if (girlsCount > 0) {
                    girlsCount--;
                }
            }


            if (prev == NULL) {
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

void updateStudent(struct Student **head, int rollNumber) {
    int found = 0;
    struct Student *current = *head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            found = 1;
            int choice;
            printf("\nUpdate Menu:\n");
            printf("1. Update Name\n");
            printf("2. Update CGPA\n");
            printf("3. Update Gender\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");

            if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                while (getchar() != '\n');
                continue;
            }

            switch (choice) {
                case 1:
                    printf("Enter new name: ");
                    scanf("%s", current->name);
                    break;
                case 2:
                    do {
                        printf("Enter new CGPA: ");
                        if (scanf("%f", &current->cgpa) != 1 || current->cgpa < 1 || current->cgpa > 4) {
                            printf("Invalid input. CGPA should be between 1 and 4.\n");
                            while (getchar() != '\n');
                        } else {
                            break;
                        }
                    } while (1);
                    break;
                case 3:
                    do {
                        printf("Enter new gender (M/F): ");
                        scanf(" %c", &current->gender);
                        if (current->gender != 'M' && current->gender != 'm' && current->gender != 'F' && current->gender != 'f') {
                            printf("Invalid input. Please enter 'M' or 'F'.\n");
                            while (getchar() != '\n');
                        } else {
                            break;
                        }
                    } while (1);
                    break;
                case 4:
                    return;
            }
        }
        current = current->next;
    }
    if (!found) {
        printf("Student with roll number %d not found.\n", rollNumber);
    } else {
        printf("Updated %d successfully\n", rollNumber);
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

int main() {
    struct Student *head = NULL;

    int rollNumber, choice;
    char name[50], gender;
    float cgpa;

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Count of Students\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Print Gender Counts\n");
        printf("7. Print Students\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                do {
                    printf("Enter student data:\n");
                    printf("Roll Number: ");
                    if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                        printf("Invalid input. Roll number must be a positive integer.\n");
                        while (getchar() != '\n');
                    } else {
                        break;
                    }
                } while (1);

                printf("Name: ");
                scanf("%s", name);
                do {
                    printf("CGPA: ");
                    if (scanf("%f", &cgpa) != 1 || cgpa < 0 || cgpa > 4) {
                        printf("Invalid input. CGPA should be between 0 and 4.\n");
                        while (getchar() != '\n');
                    } else {
                        break;
                    }
                } while (1);

                do {
                    printf("Gender (M/F): ");
                    scanf(" %c", &gender);
                    if (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
                        printf("Invalid input. Gender should be 'M' or 'F'.\n");
                        while (getchar() != '\n');
                    } else {
                        break;
                    }
                } while (1);

                addStudent(&head, rollNumber, name, cgpa, gender);
                break;

            case 2:
                printf("Enter roll number to find: ");
                if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                    printf("Invalid input. Roll number must be a positive integer.\n");
                    break;
                }
                findStudentByRollNumber(head, rollNumber);
                break;

    case 3:
                printf("Total number of students: %d\n", countStudents(head));
                break;

            case 4:
                printf("Enter roll number to delete: ");
                if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                    printf("Invalid input. Roll number must be a positive integer.\n");
                    break;
                }
                deleteStudent(&head, rollNumber);
                break;

            case 5:
                printf("Enter roll number to update: ");
                if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                    printf("Invalid input. Roll number must be a positive integer.\n");
                    break;
                }
                updateStudent(&head, rollNumber);
                break;

            case 6:
                printGenderCounts();
                break;

            case 7:
                printStudents(head);
                break;

            case 8:
                freeList(head);
                printf("Program exited.\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a valid option (1 to 8).\n");
        }

    } while (1);

    return 0;
}
