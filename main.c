#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
};

void addBook();
void viewBooks();
void searchBook();
void deleteBook();

int main() {
    int choice;

    while (1) {
        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook();
                break;

            case 2:
                viewBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                deleteBook();
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addBook() {
    FILE *fp;
    struct Book b;

    fp = fopen("books.csv", "a");

    if (fp == NULL) {
        printf("File could not be opened!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Title: ");
    scanf(" %[^\n]", b.title);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fprintf(fp, "%d,%s,%s,%d\n",
            b.id,
            b.title,
            b.author,
            b.quantity);

    fclose(fp);

    printf("Book added successfully!\n");
}

void viewBooks() {
    FILE *fp;
    char line[300];

    fp = fopen("books.csv", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== BOOK RECORDS =====\n");

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void searchBook() {
    FILE *fp;
    char line[300];
    int searchId;
    int found = 0;

    fp = fopen("books.csv", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &searchId);

    while (fgets(line, sizeof(line), fp)) {
        int id;

        sscanf(line, "%d,", &id);

        if (id == searchId) {
            printf("\nBook Found:\n");
            printf("%s", line);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }

    fclose(fp);
}

void deleteBook() {
    FILE *fp, *temp;
    char line[300];
    int deleteId;
    int found = 0;

    fp = fopen("books.csv", "r");
    temp = fopen("temp.csv", "w");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &deleteId);

    while (fgets(line, sizeof(line), fp)) {
        int id;

        sscanf(line, "%d,", &id);

        if (id == deleteId) {
            found = 1;
            continue;
        }

        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("books.csv");
    rename("temp.csv", "books.csv");

    if (found) {
        printf("Book deleted successfully!\n");
    } else {
        printf("Book not found!\n");
    }
}
