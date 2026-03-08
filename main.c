#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
struct Book
{
    int ID;
    char Title[100];
    char Author[100];
    int Issue;          
    char RegNo[100];      
};
struct Book library[MAX];
int count = 0;
void loadData();
void saveData();
void addBook();
void displayBooks();
void issueBook();
void returnBook();
void searchBook();
void issuedBooks();
int main()
{
    int choice;
    loadData();
    while (1)
    {
        printf("\n   Library Book Tracking System   \n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Search Book\n");
        printf("6. Show Issued Books\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        printf("%d\n", choice); 
        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
            issueBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            searchBook();
            break;
        case 6:
            issuedBooks();
            break;
        case 7:
            saveData();
            printf("Data saved. Exiting.\n");
            exit(0);
        default:
            printf("Invalid choice! Please enter a number between 1 and 7.\n");
        }
    }
    return 0;
}
void addBook()
{
    if (count >= MAX)
    {
        printf("Library storage full.\n");
        return;
    }
    printf("Enter Book ID: ");
    scanf("%d", &library[count].ID);
    printf("%d\n", library[count].ID); 
    printf("Enter Book Title: ");
    scanf(" %s", library[count].Title);
    printf("%s\n", library[count].Title);
    printf("Enter Author Name: ");
    scanf(" %s", library[count].Author);
    printf("%s\n", library[count].Author);
    library[count].Issue = 0;
    strcpy(library[count].RegNo, "-");
    count++;
    printf("Book added successfully.\n");
}
void displayBooks()
{
    if (count == 0)
    {
        printf("No books available.\n");
        return;
    }
    printf("\nID\tTitle\t\tAuthor\t\tStatus\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d\t%s\t\t%s\t\t",
               library[i].ID,
               library[i].Title,
               library[i].Author);
        if (library[i].Issue)
            printf("Issued to %s\n", library[i].RegNo);
        else
            printf("Available\n");
    }
}
void issueBook()
{
    int id;
    char reg[100];
    printf("Enter Book ID to issue: ");
    scanf("%d", &id);
    printf("%d\n", id); 
    for (int i = 0; i < count; i++)
    {
        if (library[i].ID == id)
        {
            if (library[i].Issue)
            {
                printf("Book already issued.\n");
                return;
            }
            printf("Enter Student Registration Number: ");
            scanf(" %s", reg);
            printf("%s\n", reg);
            library[i].Issue = 1;
            strcpy(library[i].RegNo, reg);
            printf("Book issued successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}
void returnBook()
{
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);
    printf("%d\n", id); 
    for (int i = 0; i < count; i++)
    {
        if (library[i].ID == id)
        {
            if (!library[i].Issue)
            {
                printf("Book is already available.\n");
                return;
            }
            library[i].Issue = 0;
            strcpy(library[i].RegNo, "-");
            printf("Book returned successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}
void searchBook()
{
    int choice;
    int id;
    char keyword[100];
    printf("Search Book Options:\n");
    printf("1. Search by ID\n");
    printf("2. Search by Title Keyword\n");
    printf("Enter your choice for search (1-2): ");
    scanf("%d", &choice);
    printf("%d\n", choice); 
    if (choice == 1)
    {
        printf("Enter Book ID to search: ");
        scanf("%d", &id);
        printf("%d\n", id);
        for (int i = 0; i < count; i++)
        {
            if (library[i].ID == id)
            {
                printf("Book Found:\n");
                printf("%d %s %s\n",
                       library[i].ID,
                       library[i].Title,
                       library[i].Author);
                return;
            }
        }
        printf("Book not found.\n");
    }
    else if (choice == 2)
    {
        printf("Enter title keyword to search: ");
        scanf(" %s", keyword);
        printf("%s\n", keyword); 
        for (int i = 0; i < count; i++)
        {
            if (strstr(library[i].Title, keyword))
            {
                printf("%d %s %s\n",
                       library[i].ID,
                       library[i].Title,
                       library[i].Author);
            }
        }
    }
    else
    {
        printf("Invalid search choice.\n");
    }
}
void issuedBooks()
{
    printf("\nCurrently Issued Books:\n");
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (library[i].Issue)
        {
            printf("%d %s issued to %s\n",
                   library[i].ID,
                   library[i].Title,
                   library[i].RegNo);
            found = 1;
        }
    }
    if (found == 0)
        printf("No books currently issued.\n");
}
void saveData()
{
    FILE *fp = fopen("books.txt", "wb");
    if (fp == NULL)
    {
        printf("File error.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(library, sizeof(struct Book), count, fp);
    fclose(fp);
}
void loadData()
{
    FILE *fp = fopen("books.txt", "rb");
    if (fp == NULL)
        return;
    fread(&count, sizeof(int), 1, fp);
    fread(library, sizeof(struct Book), count, fp);
    fclose(fp);
}
