#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    do
    {
        printf("\n=====================================");
        printf("\n     STUDENT MANAGEMENT SYSTEM");
        printf("\n=====================================");
        printf("\n1. Add Student");
        printf("\n2. Display All Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using the system.\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 6);

    return 0;
}

void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    if(fp == NULL)
    {
        printf("\nUnable to open file.\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("\nStudent Record Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;
    int count = 0;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n=================================================");
    printf("\nRoll No\t\tName\t\t\tMarks");
    printf("\n=================================================\n");

    while(fread(&s, sizeof(struct Student), 1, fp) == 1)
    {
        printf("%d\t\t%-20s\t%.2f\n",
               s.roll,
               s.name,
               s.marks);
        count++;
    }

    if(count == 0)
    {
        printf("No Records Found!\n");
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(struct Student), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            printf("\nRecord Found");
            printf("\n---------------------");
            printf("\nRoll Number : %d", s.roll);
            printf("\nName        : %s", s.name);
            printf("\nMarks       : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nStudent Not Found!\n");
    }

    fclose(fp);
}

void updateStudent()
{
    FILE *fp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen("students.dat", "rb+");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(struct Student), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(struct Student), SEEK_CUR);

            fwrite(&s, sizeof(struct Student), 1, fp);

            found = 1;

            printf("\nRecord Updated Successfully!\n");
            break;
        }
    }

    if(found == 0)
    {
        printf("\nStudent Not Found!\n");
    }

    fclose(fp);
}

void deleteStudent()
{
    FILE *fp;
    FILE *temp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if(temp == NULL)
    {
        printf("\nUnable to create temporary file.\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(struct Student), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
    {
        printf("\nRecord Deleted Successfully!\n");
    }
    else
    {
        printf("\nStudent Not Found!\n");
    }
}
