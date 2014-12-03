//
//  Header.h
//  asm_3
//
//  Created by Davut Ucar on 03/12/14.
//
//  Copyright (c) 2014 Davut Ucar. All rights reserved.
//
//  Name:               Davut Ucar
//  Student no:         10011050
//  Date:               03.12.2014
//  E-Mail:             davutucar@gmail.com
//  Compiler used:      GCC
//  IDE:                Xcode 6.1.1
//  Operating System    Mac OS Yosemite


#ifndef asm_3_Header_h
#define asm_3_Header_h

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


union PersonData{
    long int score;
    unsigned char randomAnswers[8];
};              //unions for score and answers

typedef struct{
    char *name;
    char *surname;
    int dateOfBith;
    union PersonData data;
    
}PERSON;        //person type struct

const int lineSize = 100;

//generate people for testing
PERSON** generatePeople(int N, PERSON **person, FILE *f1, FILE *f2){
    int i,j;        //iterators
    int randResult, randResult2;     //random buffer
    char **name, **surname;      //name and surname buffers
    int bYear, test, bMonth,bDay;
    char **controlMatrix;
    
    //It is impossible to generate people more than 2500
    //Control the count
    if(N >2500){
        printf("Too many people to generate uniquely\n");
        return EXIT_FAILURE;
    }
    
    name = (char **)malloc(sizeof(char*) * 50); //allocation for name buffer
    for(i=0;i<50;i++){
        name[i]=(char*)malloc(sizeof(char));
    }
    
    controlMatrix = (char **)calloc(sizeof(char*), 50); //allocation for name-surname similarity matrix
    for(i=0;i<50;i++){
        controlMatrix[i]=(char*)calloc(sizeof(char), 50);
    }
    
    surname = (char **)malloc(sizeof(char*) * 50); //allocation for surname buffer
    for(i=0;i<50;i++){
        surname[i]=(char*)malloc(sizeof(char));
    }
    
    person = malloc(sizeof(PERSON *) * N);  //allocation for person type
    
    //allocation for people
    for (i = 0; i < N; i++) {
        person[i] = malloc(sizeof(PERSON));
    }
    
    srand(time(NULL));
    
    f1 = fopen("names.txt", "rb");  //openning file for reading name
    if(f1 == NULL){
        printf("Failed to open the file...\n");
        return EXIT_FAILURE;
    }
    for(i=0;i<50;i++){
        fgets(name[i],lineSize,f1);     //getting names from file
    }
    fclose(f1);     //closed file
    
    f2 = fopen("surnames.txt", "rb");   //openning file for reading surname
    if(f2 == NULL){
        printf("Failed to open the file...\n");
        return EXIT_FAILURE;
    }
    for(i = 0; i < 50;i++){
        
        fgets(surname[i], lineSize, f2);
    }
    fclose(f2);
    
    for(j = 0; j < N; j++){
        test = 1;
        
        while(test){
            
            randResult = rand() % 50;
            person[j]->name = name[randResult];
            randResult2 = rand() % 50;
            person[j]->surname = surname[randResult2];
            if(controlMatrix[randResult][randResult2]){     //if name and surname are same then
                test = 1;                                   //reassign name and surname
            }else{
                test = 0;
            }
        }
        bYear = 18 + (rand() % 22);
        bMonth = 1 + rand() % 12;
        bDay = 1 + rand() %30;
        person[j]->dateOfBith = (2014 - bYear) * 10000 + (bMonth * 100) + bDay; //it will generate date like YYYYMMDD
        
//        printf("%d. person's\n Name is: %s Surname is: %s Date of birth as a YYYY MM DD: %d\n\n", j+1, person[j]->name, person[j]->surname, person[j]->dateOfBith );
        
    }
    printf("\nPeople generated.\n\n");
    return person; //returning all person data
}

PERSON** simulateQuiz(PERSON **person, char answers[],int N){
    int i,j=0,totalBuffer = 0;
    
    union PersonData *data;
    printf("Simulation had just started...\n\n");
    srand(time(NULL));
    data = malloc(sizeof(union PersonData) * N);
    
    for(i=0;i<N;i++){
        person[i]->data.score = 0;
        j = 0;
        while(j<8){         //generating random answers for person[i]
            person[i]->data.randomAnswers[j] = rand() % 2;
            
            if(person[i]->data.randomAnswers[j] == answers[j]){      //if answer is correct 16 points will add to totalscore
                totalBuffer = totalBuffer + 16;
            }
            j++;
            
        }
        person[i]->data.score = totalBuffer;        //total score for person[i]
        totalBuffer = 0;
    }
    printf("\n\nSimulation process is over. \n\n");
    return person;      //returning all person data
    
}

int listResults(PERSON **person, int N){
    int select1=0;
    printf("Please select...\n");
    //sort type
    while(select1<1 || select1>3){
        printf("\t1 - Order by surname\n\t2 - Order by birthday\n\t3 - Order by score\n");
        scanf("%d",&select1);
    }
    switch(select1){
        case 1:
            
            listResultOrderedByName(person,N);
            
            break;
            
        case 2:
            listResultOrderedByDateOfBirth(person,N);
            break;
        case 3:
            
            listResultOrderedByScore(person, N);
            
            break;
        default:
            printf("\nPlease enter a suitable number!\n\n.");
            break;
    }
    
    return 0;
}

int listResultOrderedByName(PERSON** person, int N){
    
    int j,i;
    //char name_tmp[20];
    PERSON *tmpPerson;
    tmpPerson =(PERSON*)malloc(sizeof(PERSON));
    //strcmp function is compare two string and return the on of these -1,0,1
    //accordingly result of comparing, it will copy name via strcpy function
    for(i=0; i<N*N; i++){
        for(j = 0 ;j < N-1; j++){
            if(strcmp(person[j+1]->surname, person[j]->surname) < 0){
                //selection sort
                tmpPerson = person[j+1];
                person[j+1] = person[j];
                person[j] = tmpPerson;
            }
            
        }
        
    }
    listShow(person, N);
    
    return 0;
}

int listResultOrderedByDateOfBirth(PERSON **person, int N){
    int tmp;
    int i,j;
    PERSON *tmpPerson;
    tmpPerson = (PERSON*)malloc(sizeof(PERSON));
    
    for (i=0; i<N; i++) {
        for (j=i+1; j<N; j++) {
            //selection sort birthdays
            if (person[i]->dateOfBith > person[j]->dateOfBith){
                tmpPerson = person[i];
                person[i] = person[j];
                person[j] = tmpPerson;
                
            }
        }
    }
    
    listShow(person, N);
    
    printf("\n");
    return 0;
}
int listResultOrderedByScore(PERSON **person, int N){
    long int tmp;
    int i,j;
    PERSON *tmpPerson;
    tmpPerson = (PERSON*)malloc(sizeof(PERSON));
    
    for (i=0; i<N; i++) {
        for (j=i+1; j<N; j++) {
            //selection sort scores
            if (person[i]->data.score > person[j]->data.score){
                tmpPerson = person[i];
                person[i] = person[j];
                person[j] = tmpPerson;
                
            }
        }
    }
    
    listShow(person, N);
    return 0;
    
}

int listShow(PERSON **person, int N){
    
    int i;
    
    for (i=0; i<N; i++) {
        printf("%d. person's\n Name is: %s Surname is: %s Date of birth as a YYYY MM DD: %d\n\n", i+1, person[i]->name, person[i]->surname, person[i]->dateOfBith );
        printf("Score = %ld\n\n", person[i]->data.score);
    }
    
    return 0;
    
}





#endif
