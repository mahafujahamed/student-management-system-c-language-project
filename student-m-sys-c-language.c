
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <unistd.h> // For usleep function


#define SELECTED_COLOR "\x1B[32m"
#define EXIT_COLOR "\x1B[31m"
#define RESET_COLOR "\x1B[0m"



void printStringSlowly( char *str, int delayInMicroseconds) {
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        putchar(str[i]);
        fflush(stdout); // Flush the output to ensure immediate printing

        usleep(delayInMicroseconds);
    }
}


typedef struct node{
    int id;
    char name[100];
    double mark;
    struct node *next;
    struct node *prev;
} node;

node *start = NULL, *last = NULL,*newnode,*temp,*n;
node* search(int i){
   node *p = start;
   while(p!=NULL){
       if(p->id==i){
           break;
        }
        p = p->next;
    }
    return p;
}


void add(int i, char n[],double t){

      if(search(i)!=NULL){
        printf("\n ID ALREADY ADDED!\n");
        return ;
    }
    node *newNode=(node *)malloc(sizeof(node));
    newNode->id = i;
    strcpy(newNode->name, n);
    newNode->mark = t;

    newNode->prev=NULL;
    newNode->next=NULL;

    if(start==NULL && last==NULL)
    {

        start=newNode;
        last=newNode;
    }
    else
    {
        last->next=newNode;
        newNode->prev=last;
        last=newNode;
    }

        printf("\n\"%s\"  added.\n", n);

}

void rmv(int i){
     node *tmp = search(i);

    if(tmp==NULL){
        printf("\nTask doesn't exist!\n");
        return ;
    }
    if(tmp==start && tmp==last){
        start = NULL;
        last = NULL;
    }
    else if(tmp==start){
        tmp->next->prev = NULL;
        start =tmp->next;
    }
    else if(tmp==last){
        tmp->prev->next = NULL;
        last = tmp->prev;
    }
    else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    printf("\n\"%s\" student removed.\n", tmp->name);
    free(tmp);
}

void display()
{
    n=start;
    if(n==NULL)
    {
        printf("\033[1;31mlist empty\033[0m\n");
    }
    else
    {
        while(n!=NULL)
        {
            printf("\033[1;33m %d \033[0m",n->id);
            printf("\033[1;34m %s \033[0m",n->name);
            printf("\033[1;35m %.2lf \033[0m\n",n->mark);

            n=n->next;

        }
        printf("\n");
    }
    printf("Press Enter to continue..\n");
    char x;
    x=getch();
}

// Function to insert a node at the end of the list with a mark and a name

void insertNode(struct node** start, int id,double mark, const char* name) {

    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->id =id;
    newNode->mark = mark;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (*start == NULL) {
        *start = newNode;
    } else {
        struct node* current = *start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


// Function to find and store multiple highest marks

void hight_mark(struct node* start) {
    if (start == NULL) {
        printf("The list is empty.\n");
         printf("Press Enter to continue..\n");
    char x;
    x=getch();
        return;
    }

    double highestMark = start->mark;
    struct node* highestMarksList = NULL;

    while (start != NULL) {
        if (start->mark > highestMark) {
            highestMark = start->mark;
            highestMarksList = NULL; // Reset the list
        }

        if (start->mark == highestMark) {
            insertNode(&highestMarksList,start->id, start->mark,start->name);
        }

        start= start->next;
    }

 // Print the multiple highest marks

    printf("highest marks: \n");
    struct node* current = highestMarksList;
    while (current != NULL) {

        printf("\x1B[32m%id  %s  %.2lf\x1B[0m\n",current->id, current->name,current->mark);


//printf("%.2lf ", current->mark);
        current = current->next;
    }
    printf("\n");
     printf("Press Enter to continue..\n");
    char x;
    x=getch();
}
void clearScreen() {
    // In C, you can use system("cls") for Windows and "clear" for Linux/macOS
    system("cls");
}

void printNewLine(int n) {
    for (int i = 0; i < n; i++) {
        printf("\n");
    }
}

//function to display specific student,number,mark

void searchAndDisplayStudent(int id) {
    node* student = search(id);

    if (student != NULL) {
        printf("\n\x1B[32mStudent Found:\x1B[0m\n");
        printf("ID: %d\n", student->id);
        printf("Name: %s\n", student->name);
        printf("Mark: %.2lf\n", student->mark);
    } else {
        printf("\n\x1B[31mStudent with ID %d not found.\x1B[0m\n",id);
    }

    printf("Press Enter to continue..\n");
    char x;
    x = getch();
}

//main figer

void displayMenu(int selectedOption) {
    clearScreen();

    const char *color = (selectedOption == 6) ? EXIT_COLOR : RESET_COLOR;

       system("COLOR");

     printf("\033[1;31m********\n");
        printf(" *        STUDENT PLAN    *\n");
        printf("********\033[0m\n");

    //printf("\n\n\n");
    printNewLine(3);

    printf("%s%s", (selectedOption == 0 ? SELECTED_COLOR : RESET_COLOR),
           (selectedOption == 0 ? "-->  " : "     "));
    printf("1.Add a student:\n\n");

    printf("%s%s", (selectedOption == 1 ? SELECTED_COLOR : RESET_COLOR),
           (selectedOption == 1 ? "-->  " : "     "));
    printf("2.Remove a student:\n\n");

    printf("%s%s", (selectedOption == 2 ? SELECTED_COLOR : RESET_COLOR),
           (selectedOption == 2 ? "-->  " : "     "));
    printf("3.Display students:\n\n");

    printf("%s%s", (selectedOption == 3 ? SELECTED_COLOR : RESET_COLOR),
           (selectedOption == 3 ? "-->  " : "     "));
    printf("4.Display highest marks:\n\n");

    printf("%s%s", (selectedOption == 4 ? SELECTED_COLOR : RESET_COLOR),
           (selectedOption == 4 ? "-->  " : "     "));
    printf("5.Search a student:\n\n");

    printf("%s%s", (selectedOption == 5 ? EXIT_COLOR : RESET_COLOR),
           (selectedOption == 5 ? "-->  " : "     "));
    printf("6.Exit:\n\n%s", RESET_COLOR);
}

//control section and key section

void StartMainMenu()
{
    const int numOptions = 6;
    int selectedOption = 0;
    char key;

    do
    {
          displayMenu(selectedOption);

        key = getch();  // Get a single character without waiting for Enter

        switch (key)
        {
        case 72:  // Up Arrow
            selectedOption = (selectedOption - 1 + numOptions) % numOptions;

            break;
        case 80:  // Down Arrow
            selectedOption = (selectedOption + 1) % numOptions;
            break;
        }
    }

    while (key != 13);  // Enter key



    switch (selectedOption)
    {
     case 0:{
          int i;
          double t;
            char n[100];
             printf("\nSTUDENT ID: ");
            scanf("%d", &i);
            getchar();
            printf("\nNAME: ");
            scanf("%[^\n]%*c", n);
            printf("\nMARK: ");
            scanf("%lf", &t);
            add(i,n,t);
            printStringSlowly("\033[1;32mAdded Successfully\033[0m\n",50000);
            printf("\n");
            break;
     }
        case 1:
           {
                 int i;
            printf("\nSTUDENT ID: ");
            scanf("%d", &i);
            rmv(i);
             printStringSlowly("\033[1;31mDeleted Successfully\033[0m\n",50000);
            printf("\n");
            break;
           }
        case 2:
            display();

            break;
        case 3:
            hight_mark(start);
            printf("\n");
            break;


case 4:
            {int id;
        printf("\033[1;31mEnter the student ID to search:\033[0m  ");
        scanf("%d", &id);
        searchAndDisplayStudent(id);
        break;
            }
            case 5:
            exit(1);
            break;
        default:
            printStringSlowly("\x1B[32mInvalid!!!\033[0m\n",50000);
            break;
    }
}
//function to write the studebt data in a file
void saveDataToFile() {
    FILE* file = fopen("student_data.txt", "w");


    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }


    node* current = start;

    while (current != NULL) {
        fprintf(file, "%d %s %.2lf\n", current->id, current->name, current->mark);
        current = current->next;
    }


    fclose(file);



}

/*void loadDataFromFile() {
    FILE* file = fopen("student_data.txt", "a");


    if (file == NULL) {
        printf("No data file found. Starting with an empty list.\n");
        return;
    }

    int id, mark;
    char name[100];

    while (fscanf(file, "%d %s %lf", &id, name, &mark) == 3) {
        add(id, name, mark);
    }


    fclose(file);


}*/
//function to write the student hight marks

void saveHighestMarksToFile() {
    FILE* file = fopen("highest_marks.txt", "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    double highestMark = 0.0;
    node* current = start;

    // Find the highest mark
    while (current != NULL) {
        if (current->mark > highestMark) {
            highestMark = current->mark;
        }
        current = current->next;
    }

    // Rewind the list to the beginning
    current = start;

    // Save records with the highest mark to the file
    while (current != NULL) {
        if (current->mark == highestMark) {
            fprintf(file, "%d %s %.2lf\n",current->id, current->name, current->mark);
        }
        current = current->next;
    }

    fclose(file);
}

/*void loadHighestMarksFromFile() {
    FILE* file = fopen("highest_marks.txt", "a");

    if (file == NULL) {
        printf("No data file found. Starting with an empty list.\n");
        return;
    }
    int id;
    char name[100];
    double mark;

    while (fscanf(file, "%d %s %lf",&id, name, &mark) == 3) {
        add(id, name, mark); // You can set any arbitrary ID since you are only loading the name and mark.
    }

    fclose(file);
}*/


int main() {
   // loadDataFromFile();
    //loadHighestMarksFromFile();

    while (1) {
        StartMainMenu();
        saveDataToFile();// Save data to file after each operation.
        saveHighestMarksToFile();
    }

    return 0;
}
