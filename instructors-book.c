// NAME: Daniil
// Belousov
// ID 2491827

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

// creating the node where we will stor the information about instructors
struct Node{
    char fname[30];
    char lname[30];
    char title[30];
    char email[50];
    int pnum;
    char rnum[30];
    struct Node *next;

};
// creating the list that will sore the nodes, not using the tail pointer beacuse no need), but we do need thecount for the search function
struct InstBook
{
	struct Node *head;
	int count;
};
typedef struct InstBook *List;

struct InstBook *initialiseInstructorBook(char []);

void PrintInstructors(List);
void InsertInstructor(List);
void SearchInstructor(List, char []);
struct InstBook *CurrentSemesterInstructors(List, List);

int main(int argc,char *argv[]){

    List Instructors, CurrentInstructors;
    int i, choice;
    char name[15];
    char file[30];
    strcpy(file,argv[1]);                   //copping the file name from the input

    Instructors=initialiseInstructorBook(argv[1]);                      // setting the main list of instructors, all with the function
    CurrentInstructors =(struct InstBook *)malloc(sizeof(struct InstBook));     // creaing the list of the current instructors
        if (CurrentInstructors == NULL)
            printf("Out of memory!\n");
        else{
            CurrentInstructors->head = (struct Node *) malloc(sizeof(struct Node));
            if (CurrentInstructors->head == NULL)
                printf("Out of memory!\n");

            CurrentInstructors->head->next = NULL;
            CurrentInstructors->count = 0;
        }
    //creating the menu
    do{
        printf("\n----- MENU-----\n1. Add Instructor\n2. Print Instructor\n3. Search Instructor\n4. Create Current Semester Instructors List \n5. Print Current Semester Instructors List \n6. Exit\n");
        printf("\nEnter your option: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                InsertInstructor(Instructors);
                break;
            case 2:
                printf("Instructor in your database: \n-----------------------\n");
                PrintInstructors(Instructors);
                break;
            case 3:
                printf("\nEnter the name of the instructor you want to search: ");
                scanf("%s", name);
                printf("\n");
                SearchInstructor(Instructors, name);
                break;
            case 4:
                printf("\n");
                CurrentInstructors=CurrentSemesterInstructors(Instructors, CurrentInstructors);
                break;
            case 5:
                if (CurrentInstructors->head->next==NULL)
                    printf("Please coose your instructros first!");
                else {
                    printf("Results\n---------------------");
                    PrintInstructors(CurrentInstructors);
                }
                break;
            case 6: // creating the 6th case which leaves the programm, it is empty, but otherwise if we input 6, to leave the program, it will output the default statement
                break;
            default:
                printf("No such command, plese choose from the listed options\n");
                break;

        }

    }while(choice!=6);


    // setting the lists(memmoery) free after we are done
    free(Instructors);
    free(CurrentInstructors);
    return 0;
}




struct InstBook *initialiseInstructorBook(char filename[]){

    int checkpoint1, flag, i,checkpoint2;
    char inputuser[30];

    List Instructors;
    FILE *inFile;
    //oppening the file and saking the user to reenter the file name if the file from the command line does not exist otherwise printing that everything is fine
    inFile=fopen(filename, "r");
    if (inFile==NULL){
        printf("This file does not exist, please enter again: ");
        while (checkpoint1!=1){
            fflush(stdin);
            scanf("%s", inputuser);
            inFile = fopen(inputuser, "r");
            if (inFile == NULL){
                printf("This file does not exist, please enter again: ");
            }
            else
                checkpoint1=1;
        }
    }
    else
        printf("\nThe instructors.txt file has been loaded successfully\n");

    Instructors =(struct InstBook *)malloc(sizeof(struct InstBook));
	if (Instructors == NULL)
		printf("Out of memory!\n");
    else{
        Instructors->head = (struct Node *) malloc(sizeof(struct Node));
        if (Instructors->head == NULL)
            printf("Out of memory!\n");

        Instructors->head->next = NULL;
        Instructors->count = 0;
    }
    // building the current instructures list by string concatenation
    char line[100];
    while (fgets(line, 100, inFile)){      // getting the stracture filled with the data from the file by the usage of strings
        struct Node *temp, *insert,*p;
        temp=(struct Node*)malloc(sizeof(struct Node));
        insert=(struct Node*)malloc(sizeof(struct Node));
        temp->next=NULL;
        char *token;
        token = strtok(line, ";");      // recording cutting a the string in peaces and assigning to the coresponding structure parts
        int flag=1;
        while( token != NULL )
        {
            checkpoint2=0;
            if(flag==1)
                strcpy(temp->fname,token);
            else if(flag==2)
                strcpy(temp->lname,token);
            else if(flag==3)
                strcpy(temp->title,token);
            else if(flag==4)
                strcpy(temp->email,token);
            else if(flag==5)
                temp->pnum=atoi(token);
            else{
                if(token[strlen(token)-1]=='\n')
                    token[strlen(token)-1]='\0';
                strcpy(temp->rnum,token);
            }
            token = strtok(NULL, ";");
            flag++;

        }
        Instructors->count++;  // counting the number of instructors in the list
        p=Instructors->head;  // assighning the other pointer to the lists head and by going through it, inserting the instructors information in the alphabetic order
        if(p->next==NULL){
            p->next=temp;
        }
        else{
            while(p->next!=NULL && checkpoint2==0){
                if(strcmp(p->next->fname,temp->fname)>0){
                    temp->next=p->next;
                    p->next=temp;
                    checkpoint2=1;
                }
                else
                    p=p->next;
            }
            if(p->next==NULL && checkpoint2==0)
                p->next=temp;

        }
        if(flag>6){
            flag=1;
            i++;
        }
    }


    return Instructors;
};





void InsertInstructor (List Instructors){
    fflush(stdin);
    struct Node *temp, *p;
    int checkpoint2=0;
    temp=(struct Node*)malloc(sizeof(struct Node));  // allocating memmoery for the node and then filling it with the user input
    if (temp==NULL){
        printf("Could not allocate memory");
        exit(214);
        }
    printf("Enter instructor name: ");
    gets(temp->fname);

    printf("Enter instructor surname: ");
    gets(temp->lname);
    printf("Enter instructor title: ");
    gets(temp->title);
    printf("Enter instructor email: ");
    gets(temp->email);
    printf("Enter instructor phone number: ");
    scanf("%d",&temp->pnum);
    fflush(stdin);
    printf("Enter instructor room number: ");
    gets(temp->rnum);
    printf("\nThe instructor has been added!!\n");
    p=Instructors->head;   //insering the node in the correct place
        if(p->next==NULL){
            p->next=temp;
        }
        else{
            while(p->next!=NULL && checkpoint2==0){
                if(strcmp(p->next->fname,temp->fname)>0){
                    temp->next=p->next;
                    p->next=temp;
                    checkpoint2=1;
                }
                else
                    p=p->next;
            }
            if(p->next==NULL && checkpoint2==0)
                p->next=temp;

        }
    Instructors->count++;// as we insert we also increment the instructors count
}




void SearchInstructor(List Instructors, char name[15]){
    struct Node *low, *high,*point;
    int low1, high1,i, point1,check=0,n=1;
    high1=Instructors->count;
    low1=1;
    low=Instructors->head->next;

    do{
        point1=(low1+high1)/2;
        point=Instructors->head;
        high=Instructors->head;
        for(i=0;i<high1;i++)
            high=high->next;
        for(i=0;i<point1;i++)
            point=point->next;
        if(strcmp(point->fname,name)==0){
            printf("Results\n---------------------\n");
            printf("Instructor name: %s\n", point->fname);
            printf("Instructor surname: %s\n", point->lname);
            printf("Instructor title: %s\n", point->title);
            printf("Instructor email: %s\n", point->email);
            printf("Instructor phone number: %d\n", point->pnum);
            printf("Instructor room number: %s\n", point->rnum);
            check=1;
        }
        else if (strcmp(point->fname,name)>0)
            high1--;
        else{
            low1=point1+1;
            low=point->next;
        }
        n++;
    }while((low1<=high1)&&check==0);

    if(check==0)
        printf("Instructor not found!!!\n");


}


struct InstBook *CurrentSemesterInstructors(List Instructors, List CurrentInstructors){
    struct Node *temp,*p,*k;
    char name[20];
    int check =0, check2=0;
    p=(struct Node*)malloc(sizeof(struct Node)); // creating the node that will store the informatio form the instructors list and then be assighned to the current list of instructors
    if(p==NULL)
        printf("couldnt allocate memory");
    p->next=NULL;
    temp= Instructors->head;
    fflush(stdin);
    printf("Enter instructor name you want to add to your current semester list: ");
    scanf("%s",name);
    // ittirating through the instructors list and if we find the match to the users input, adding the instructor to the current list otherwise outputing that there is no such instructor
    while((temp->next!=NULL)&& check==0){
        if (strcmp(temp->next->fname,name)==0){
            check=1;
            k=temp->next;
            temp->next=temp->next->next;
            strcpy(p->fname,k->fname);
            strcpy(p->lname,k->lname);
            strcpy(p->title,k->title);
            strcpy(p->email,k->email);
            p->pnum=k->pnum;
            strcpy(p->rnum,k->rnum);
            }
        else
            temp=temp->next;
    }
    Instructors->count--;  // decrementing the instructors count
    k=CurrentInstructors->head;
    if (check==1){
        if(CurrentInstructors->head->next==NULL)
            CurrentInstructors->head->next=p;
        else{
            while(k->next!=NULL && check2==0){
                if(strcmp(k->next->fname,p->fname)>0){
                    p->next=k->next;
                    k->next=p;
                    check2=1;
                }
                else
                    k=k->next;
            }
            if(k->next==NULL && check2==0)
                k->next=p;

        }
        printf("%s has been moved to current semester list\n",p->fname);
    }
    else
        printf("Instructor not found!!!\n");

    return CurrentInstructors;
}


void PrintInstructors(List Instructors)
{   //creating the pointer that will itterate through the list and output the inside
	struct Node *p;

    p = Instructors->head->next;
    while (p!= NULL)
    {
        printf("\n");
        printf("Instructor name: %s\n", p->fname);
        printf("Instructor surname: %s\n", p->lname);
        printf("Instructor title: %s\n", p->title);
        printf("Instructor email: %s\n", p->email);
        printf("Instructor phone number: %d\n", p->pnum);
        printf("Instructor room number: %s\n", p->rnum);

        p = p->next;
    }
}


