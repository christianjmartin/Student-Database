// ********************************
// Project 4 "Student Database"
// Christian Martin
// Professor Kidane
// 04/30/23
// ********************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    char *name;
    char *id;
    double gpa;
    int creditHours;
} Student;

typedef struct StudentNode
{
    Student *pStudent;
    struct StudentNode *pNext;
} StudentNode;

typedef struct
{
    StudentNode *pIDList;                // ID ordered
    StudentNode *pHonorRollList;         // GPA sorted (ascending)
    StudentNode *pAcademicProbationList; // GPA sorted (ascending)
    StudentNode *pFreshmanList;          // NAME sorted (ascending
    StudentNode *pSophomoreList;         // NAME sorted (ascending
    StudentNode *pJuniorList;            // NAME sorted (ascending
    StudentNode *pSeniorList;            // NAME sorted (ascending
} Database;

// free memory of list
void freeList(StudentNode **pHead)
{
    while (*pHead != NULL)
    {
        StudentNode *temp = *pHead;
        *pHead = (*pHead)->pNext;
        free(temp);
    }
}

// push back normally
void push_back(StudentNode *pHead, StudentNode *trash)
{
    if (pHead == NULL)
    {
        pHead = trash;
    }
    else
    {
        StudentNode *pCurrent = pHead;
        while (pCurrent->pNext != NULL)
        {
            pCurrent = pCurrent->pNext;
        }
        pCurrent->pNext = trash;
    }
}

// remove with no message
void removeInSilence(StudentNode **pHead, StudentNode **tempList, char ID[81])
{
    if (*pHead == NULL)
    {
        return;
    }
    StudentNode *pCurrent = *pHead;
    StudentNode *pPrev = NULL;
    while (pCurrent->pNext != NULL)
    {
        if (strcmp(pCurrent->pStudent->id, ID) == 0)
        {
            if (pPrev == NULL)
            {
                *pHead = pCurrent->pNext; // first node in list
            }
            else
            {
                pPrev->pNext = pCurrent->pNext; // middle node in list
            }
            push_back(*tempList, pCurrent); // put student in the trash
            return;
        }
        pPrev = pCurrent;
        pCurrent = pCurrent->pNext;
    }
    if (strcmp(pCurrent->pStudent->id, ID) == 0)
    {
        if (pPrev == NULL)
        { // only node in list
            *pHead = NULL;
        }
        else
        {
            pPrev->pNext = NULL; // last node in list
        }
        push_back(*tempList, pCurrent); // put student in the trash
        return;
    }
}

// remove with message
void removeStudent(StudentNode **pHead, StudentNode **tempList, char ID[81])
{
    if (*pHead == NULL)
    {
        printf("Sorry, there is no student in the database with the id %s.\n\n", ID);
        return;
    }
    StudentNode *pCurrent = *pHead;
    StudentNode *pPrev = NULL;
    while (pCurrent->pNext != NULL)
    {
        if (strcmp(pCurrent->pStudent->id, ID) == 0)
        {
            if (pPrev == NULL)
            {
                *pHead = pCurrent->pNext; // first node in list
            }
            else
            {
                pPrev->pNext = pCurrent->pNext; // middle node in list
            }
            push_back(*tempList, pCurrent); // put student in the trash
            return;
        }
        pPrev = pCurrent;
        pCurrent = pCurrent->pNext;
    }
    if (strcmp(pCurrent->pStudent->id, ID) == 0)
    {
        if (pPrev == NULL)
        { // only node in list
            *pHead = NULL;
        }
        else
        {
            pPrev->pNext = NULL; // last node in list
        }
        push_back(*tempList, pCurrent); // put student in the trash
        return;
    }
    printf("Sorry, there is no student in the database with the id %s.\n\n", ID);
}

// print student credentials
void printList(StudentNode *pHead)
{
    if (pHead == NULL)
    {
        printf("There are no students matching that criteria.\n\n");
        return;
    }
    while (pHead != NULL)
    {
        printf("%s:\n", pHead->pStudent->name);
        printf("\t ID - %s\n", pHead->pStudent->id);
        printf("\t GPA - %0.2f\n", pHead->pStudent->gpa);
        printf("\t Credit Hours - %d\n\n", pHead->pStudent->creditHours);
        pHead = pHead->pNext;
    }
}

// print 10 student creds
void print10(StudentNode *pHead)
{
    if (pHead == NULL)
    {
        printf("There are no students matching that criteria.\n\n");
        return;
    }
    int counter = 0;
    while (pHead != NULL)
    {
        if (counter == 10)
        {
            break;
        }
        printf("%s:\n", pHead->pStudent->name);
        printf("\t ID - %s\n", pHead->pStudent->id);
        printf("\t GPA - %0.2f\n", pHead->pStudent->gpa);
        printf("\t Credit Hours - %d\n\n", pHead->pStudent->creditHours);
        counter++;
        pHead = pHead->pNext;
    }
}

// finds student
void findID(StudentNode *pHead, char ID[81])
{
    if (pHead == NULL)
    {
        printf("Sorry, there is no student in the database with the id %s.\n\n", ID);
        return;
    }
    while (pHead != NULL)
    {
        if (strcmp(pHead->pStudent->id, ID) == 0)
        {
            printf("%s:\n", pHead->pStudent->name);
            printf("\t ID - %s\n", pHead->pStudent->id);
            printf("\t GPA - %0.2f\n", pHead->pStudent->gpa);
            printf("\t Credit Hours - %d\n\n", pHead->pStudent->creditHours);
            return;
        }
        pHead = pHead->pNext;
    }
    printf("Sorry, there is no student in the database with the id %s.\n\n", ID);
}

// insert ID ordered
void insert_idOrdered(StudentNode **pHead, Student *newStudent)
{
    StudentNode *newNode = (StudentNode *)malloc(sizeof(StudentNode));
    newNode->pStudent = newStudent;
    newNode->pNext = NULL;
    if (*pHead == NULL)
    {
        *pHead = newNode;
    }
    else
    {
        StudentNode *pCurrent = *pHead;
        StudentNode *pPrev = NULL;
        while ((pCurrent != NULL) && (strcmp(newNode->pStudent->id, pCurrent->pStudent->id) > 0))
        {
            pPrev = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        if (pPrev == NULL)
        {
            newNode->pNext = *pHead;
            *pHead = newNode;
        }
        else
        {
            newNode->pNext = pPrev->pNext;
            pPrev->pNext = newNode;
        }
    }
}

// insert GPA ordered
void insert_gpaOrdered(StudentNode **pHead, Student *newStudent)
{
    StudentNode *newNode = (StudentNode *)malloc(sizeof(StudentNode));
    newNode->pStudent = newStudent;
    newNode->pNext = NULL;
    if (*pHead == NULL)
    {
        *pHead = newNode;
    }
    else
    {
        StudentNode *pCurrent = *pHead;
        StudentNode *pPrev = NULL;
        while ((pCurrent != NULL) && (newNode->pStudent->gpa > pCurrent->pStudent->gpa))
        {
            pPrev = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        if (pPrev == NULL)
        {
            newNode->pNext = *pHead;
            *pHead = newNode;
        }
        else
        {
            newNode->pNext = pPrev->pNext;
            pPrev->pNext = newNode;
        }
    }
}

// insert name ordered
void insert_nameOrdered(StudentNode **pHead, Student *newStudent)
{
    StudentNode *newNode = (StudentNode *)malloc(sizeof(StudentNode));
    newNode->pStudent = newStudent;
    newNode->pNext = NULL;
    if (*pHead == NULL)
    {
        *pHead = newNode;
    }
    else
    {
        StudentNode *pCurrent = *pHead;
        StudentNode *pPrev = NULL;
        while ((pCurrent != NULL) && (strcmp(newNode->pStudent->name, pCurrent->pStudent->name) > 0))
        {
            pPrev = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        if (pPrev == NULL)
        {
            newNode->pNext = *pHead;
            *pHead = newNode;
        }
        else
        {
            newNode->pNext = pPrev->pNext;
            pPrev->pNext = newNode;
        }
    }
}

// empty database
void optionE()
{
    char inputStr[81];
    Database database;
    database.pIDList = NULL;
    database.pHonorRollList = NULL;
    database.pAcademicProbationList = NULL;
    database.pFreshmanList = NULL;
    database.pSophomoreList = NULL;
    database.pJuniorList = NULL;
    database.pSeniorList = NULL;
    StudentNode *tempList = NULL;

    while ("bruh")
    {
        char letterChoice = '\0';
        int numberChoice;
        while ("user is an idiot")
        {
            printf("\nEnter: \tC to create a new student and add them to the database,\n");
            printf("\tR to read from the database,\n");
            printf("\tD to delete a student from the database, or\n");
            printf("\tX to exit the program.\n");
            printf("Your choice --> ");
            scanf(" %c", &letterChoice);
            if ((letterChoice == 'C') || (letterChoice == 'R') || (letterChoice == 'D') || (letterChoice == 'X'))
            {
                break;
            }
            printf("Invalid option. Try again.");
        }

        if (letterChoice == 'C')
        {
            Student *newStudent = (Student *)malloc(sizeof(Student));

            printf("Enter the name of the new student: ");
            char stuName[81];
            scanf(" %[^\n]", stuName);
            newStudent->name = strdup(stuName);

            printf("Enter the ID of the new student: ");
            char stuID[81];
            scanf(" %[^\n]", stuID);
            newStudent->id = strdup(stuID);

            printf("Enter the GPA of the new student: ");
            double stuGPA;
            scanf(" %lf", &stuGPA);
            double tempGPA = stuGPA;
            newStudent->gpa = tempGPA;

            printf("Enter the credit hours of the new student: ");
            int stuHours;
            scanf(" %d", &stuHours);
            int tempHrs = stuHours;
            newStudent->creditHours = tempHrs;

            insert_idOrdered(&database.pIDList, newStudent);
            if (newStudent->gpa <= 2.00)
            {
                insert_gpaOrdered(&database.pAcademicProbationList, newStudent);
            }
            if (newStudent->gpa >= 3.50)
            {
                insert_gpaOrdered(&database.pHonorRollList, newStudent);
            }
            if (newStudent->creditHours <= 29)
            {
                insert_nameOrdered(&database.pFreshmanList, newStudent);
            }
            if ((newStudent->creditHours >= 30) && (newStudent->creditHours <= 59))
            {
                insert_nameOrdered(&database.pSophomoreList, newStudent);
            }
            if ((newStudent->creditHours >= 60) && (newStudent->creditHours <= 89))
            {
                insert_nameOrdered(&database.pJuniorList, newStudent);
            }
            if (newStudent->creditHours >= 90)
            {
                insert_nameOrdered(&database.pSeniorList, newStudent);
            }
            printf("Successfully added the following student to the database!\n");
            printf("%s:\n", newStudent->name);
            printf("\t ID - %s\n", newStudent->id);
            printf("\t GPA - %0.2f\n", newStudent->gpa);
            printf("\t Credit Hours - %d\n\n", newStudent->creditHours);
        }

        if (letterChoice == 'R')
        {
            printf("Select one of the following: \n");
            printf("\t1) Display the head (first 10 rows) of the database\n");
            printf("\t2) Display students on the honor roll, in order of their GPA\n");
            printf("\t3) Display students on academic probation, in order of their GPA\n");
            printf("\t4) Display freshmen students, in order of their name\n");
            printf("\t5) Display sophomore students, in order of their name\n");
            printf("\t6) Display junior students, in order of their name\n");
            printf("\t7) Display senior students, in order of their name\n");
            printf("\t8) Display the information of a particular student\n");
            while ("bruh")
            {
                printf("Your choice --> ");
                scanf(" %d", &numberChoice);
                if ((numberChoice > 0) && (numberChoice < 9))
                { // might have to just do 9 ors if takes decimals
                    break;
                }
                printf("Sorry, that input was invalid. Please try again.\n");
            }
            if (numberChoice == 1)
            {
                print10(database.pIDList);
                printf("\n");
            }
            if (numberChoice == 2)
            {
                printList(database.pHonorRollList);
                printf("\n");
            }
            if (numberChoice == 3)
            {
                printList(database.pAcademicProbationList);
                printf("\n");
            }
            if (numberChoice == 4)
            {
                printList(database.pFreshmanList);
                printf("\n");
            }
            if (numberChoice == 5)
            {
                printList(database.pSophomoreList);
                printf("\n");
            }
            if (numberChoice == 6)
            {
                printList(database.pJuniorList);
                printf("\n");
            }
            if (numberChoice == 7)
            {
                printList(database.pSeniorList);
                printf("\n");
            }
            if (numberChoice == 8)
            {
                printf("Enter the id of the student to find: ");
                char stuID[81];
                scanf(" %[^\n]", stuID);
                char *tempStr = strdup(stuID);
                findID(database.pIDList, tempStr);
                printf("\n");
            }
        }

        if (letterChoice == 'D')
        {
            printf("Enter the id of the student to be removed: ");
            char stuID[81];
            scanf(" %[^\n]", stuID);
            char *tempStr = strdup(stuID);
            removeStudent(&database.pIDList, &tempList, tempStr);
            removeInSilence(&database.pAcademicProbationList, &tempList, tempStr);
            removeInSilence(&database.pHonorRollList, &tempList, tempStr);
            removeInSilence(&database.pFreshmanList, &tempList, tempStr);
            removeInSilence(&database.pSophomoreList, &tempList, tempStr);
            removeInSilence(&database.pJuniorList, &tempList, tempStr);
            removeInSilence(&database.pSeniorList, &tempList, tempStr);
        }

        if (letterChoice == 'X')
        {
            freeList(&database.pIDList);
            freeList(&database.pAcademicProbationList);
            freeList(&database.pHonorRollList);
            freeList(&database.pFreshmanList);
            freeList(&database.pSophomoreList);
            freeList(&database.pJuniorList);
            freeList(&database.pSeniorList);
            freeList(&tempList);
            printf("\nThanks for playing!\n");
            printf("Exiting...\n");
            exit(0);
        }
    }
}

// filled database
void optionF()
{
    printf("Enter the name of the file you would like to use: ");
    char filename[81];
    scanf(" %[^\n]", filename);
    FILE *filePtr = fopen(filename, "r");
    if (filePtr == NULL)
    {
        printf("Error: could not open %s for reading\n", filename);
        exit(-1);
    }
    char inputStr[81];
    Database database;
    database.pIDList = NULL;
    database.pHonorRollList = NULL;
    database.pAcademicProbationList = NULL;
    database.pFreshmanList = NULL;
    database.pSophomoreList = NULL;
    database.pJuniorList = NULL;
    database.pSeniorList = NULL;
    StudentNode *tempList = NULL;

    while (fgets(inputStr, 81, filePtr))
    {
        if (strcmp(inputStr, "Name,ID,GPA,Credit Hours Taken\n") == 0)
        {
            continue;
        }
        Student *newStudent = (Student *)malloc(sizeof(Student));
        char *tempStr = strdup(inputStr);
        newStudent->name = strtok(tempStr, ",");
        newStudent->id = strtok(NULL, ",");
        newStudent->gpa = atof(strtok(NULL, ","));
        newStudent->creditHours = atoi(strtok(NULL, ","));

        insert_idOrdered(&database.pIDList, newStudent);
        if (newStudent->gpa <= 2.00)
        {
            insert_gpaOrdered(&database.pAcademicProbationList, newStudent);
        }
        if (newStudent->gpa >= 3.50)
        {
            insert_gpaOrdered(&database.pHonorRollList, newStudent);
        }
        if (newStudent->creditHours <= 29)
        {
            insert_nameOrdered(&database.pFreshmanList, newStudent);
        }
        if ((newStudent->creditHours >= 30) && (newStudent->creditHours <= 59))
        {
            insert_nameOrdered(&database.pSophomoreList, newStudent);
        }
        if ((newStudent->creditHours >= 60) && (newStudent->creditHours <= 89))
        {
            insert_nameOrdered(&database.pJuniorList, newStudent);
        }
        if (newStudent->creditHours >= 90)
        {
            insert_nameOrdered(&database.pSeniorList, newStudent);
        }
    }
    fclose(filePtr);

    while ("bruh")
    {
        char letterChoice = '\0';
        int numberChoice;
        while ("user is an idiot")
        {
            printf("\nEnter: \tC to create a new student and add them to the database,\n");
            printf("\tR to read from the database,\n");
            printf("\tD to delete a student from the database, or\n");
            printf("\tX to exit the program.\n");
            printf("Your choice --> ");
            scanf(" %c", &letterChoice);
            if ((letterChoice == 'C') || (letterChoice == 'R') || (letterChoice == 'D') || (letterChoice == 'X'))
            {
                break;
            }
            printf("Invalid option. Try again.");
        }

        if (letterChoice == 'C')
        {
            Student *newStudent = (Student *)malloc(sizeof(Student));

            printf("Enter the name of the new student: ");
            char stuName[81];
            scanf(" %[^\n]", stuName);
            newStudent->name = strdup(stuName);

            printf("Enter the ID of the new student: ");
            char stuID[81];
            scanf(" %[^\n]", stuID);
            newStudent->id = strdup(stuID);

            printf("Enter the GPA of the new student: ");
            double stuGPA;
            scanf(" %lf", &stuGPA);
            double tempGPA = stuGPA;
            newStudent->gpa = tempGPA;

            printf("Enter the credit hours of the new student: ");
            int stuHours;
            scanf(" %d", &stuHours);
            int tempHrs = stuHours;
            newStudent->creditHours = tempHrs;

            insert_idOrdered(&database.pIDList, newStudent);
            if (newStudent->gpa <= 2.00)
            {
                insert_gpaOrdered(&database.pAcademicProbationList, newStudent);
            }
            if (newStudent->gpa >= 3.50)
            {
                insert_gpaOrdered(&database.pHonorRollList, newStudent);
            }
            if (newStudent->creditHours <= 29)
            {
                insert_nameOrdered(&database.pFreshmanList, newStudent);
            }
            if ((newStudent->creditHours >= 30) && (newStudent->creditHours <= 59))
            {
                insert_nameOrdered(&database.pSophomoreList, newStudent);
            }
            if ((newStudent->creditHours >= 60) && (newStudent->creditHours <= 89))
            {
                insert_nameOrdered(&database.pJuniorList, newStudent);
            }
            if (newStudent->creditHours >= 90)
            {
                insert_nameOrdered(&database.pSeniorList, newStudent);
            }
            printf("Successfully added the following student to the database!\n");
            printf("%s:\n", newStudent->name);
            printf("\t ID - %s\n", newStudent->id);
            printf("\t GPA - %0.2f\n", newStudent->gpa);
            printf("\t Credit Hours - %d\n\n", newStudent->creditHours);
        }

        if (letterChoice == 'R')
        {
            printf("Select one of the following: \n");
            printf("\t1) Display the head (first 10 rows) of the database\n");
            printf("\t2) Display students on the honor roll, in order of their GPA\n");
            printf("\t3) Display students on academic probation, in order of their GPA\n");
            printf("\t4) Display freshmen students, in order of their name\n");
            printf("\t5) Display sophomore students, in order of their name\n");
            printf("\t6) Display junior students, in order of their name\n");
            printf("\t7) Display senior students, in order of their name\n");
            printf("\t8) Display the information of a particular student\n");
            while ("bruh")
            {
                printf("Your choice --> ");
                scanf(" %d", &numberChoice);
                if ((numberChoice > 0) && (numberChoice < 9))
                { // might have to just do 9 ors if takes decimals
                    break;
                }
                printf("Sorry, that input was invalid. Please try again.\n");
            }
            if (numberChoice == 1)
            {
                print10(database.pIDList);
                printf("\n");
            }
            if (numberChoice == 2)
            {
                printList(database.pHonorRollList);
                printf("\n");
            }
            if (numberChoice == 3)
            {
                printList(database.pAcademicProbationList);
                printf("\n");
            }
            if (numberChoice == 4)
            {
                printList(database.pFreshmanList);
                printf("\n");
            }
            if (numberChoice == 5)
            {
                printList(database.pSophomoreList);
                printf("\n");
            }
            if (numberChoice == 6)
            {
                printList(database.pJuniorList);
                printf("\n");
            }
            if (numberChoice == 7)
            {
                printList(database.pSeniorList);
                printf("\n");
            }
            if (numberChoice == 8)
            {
                printf("Enter the id of the student to find: ");
                char stuID[81];
                scanf(" %[^\n]", stuID);
                char *tempStr = strdup(stuID);
                findID(database.pIDList, tempStr);
                printf("\n");
            }
        }

        if (letterChoice == 'D')
        {
            printf("Enter the id of the student to be removed: ");
            char stuID[81];
            scanf(" %[^\n]", stuID);
            char *tempStr = strdup(stuID);
            removeStudent(&database.pIDList, &tempList, tempStr);
            removeInSilence(&database.pAcademicProbationList, &tempList, tempStr);
            removeInSilence(&database.pHonorRollList, &tempList, tempStr);
            removeInSilence(&database.pFreshmanList, &tempList, tempStr);
            removeInSilence(&database.pSophomoreList, &tempList, tempStr);
            removeInSilence(&database.pJuniorList, &tempList, tempStr);
            removeInSilence(&database.pSeniorList, &tempList, tempStr);
        }

        if (letterChoice == 'X')
        {
            freeList(&database.pIDList);
            freeList(&database.pAcademicProbationList);
            freeList(&database.pHonorRollList);
            freeList(&database.pFreshmanList);
            freeList(&database.pSophomoreList);
            freeList(&database.pJuniorList);
            freeList(&database.pSeniorList);
            freeList(&tempList);
            printf("\nThanks for playing!\n");
            printf("Exiting...\n");
            exit(0);
        }
    }
}

int main()
{
    StudentNode *pIDList = NULL;
    StudentNode *pHonorRollList = NULL;
    StudentNode *pAcademicProbationList = NULL;
    StudentNode *pFreshmanList = NULL;
    StudentNode *pSophomoreList = NULL;
    StudentNode *pJuniorList = NULL;
    StudentNode *pSeniorList = NULL;

    printf("CS 211, Spring 2023\n");
    printf("Program 4: Database of Students\n\n");

    printf("Enter E to start with an empty database, \n");
    printf("or F to start with a database that has information on students from a file.\n");
    char userChoice = '\0';
    while ("bruh")
    {
        printf("Your choice --> ");
        scanf(" %c", &userChoice);
        if ((userChoice == 'F') || (userChoice == 'E'))
        {
            break;
        }
        else
        {
            printf("Sorry, that input was invalid. Please try again.\n");
        }
    }
    switch (userChoice)
    {
    case 'F':
        optionF();
        break;
    case 'E':
        optionE();
        break;
    }

    return 0;
}