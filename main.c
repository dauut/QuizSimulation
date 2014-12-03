//  Quiz simlation program.
//
//  main.c
//  asm_3
//
//  Created by Davut Ucar on 24/11/14.
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

#include "Header.h"

int main(){
    unsigned int N;     // number of person/people
    int i,select = 1;     // Selection initialized
    PERSON **person = NULL;
    FILE *fNames, *fSurnames;           // file pointer
    char answers[8];
    while (select != 0) {
        printf("1 - Generate people\n2 - Enter the answer key\n3 - Simulate quiz\n4 - List results\n0 - For Exit >> 0\n");
        scanf("%d",&select);

        switch (select) {
            case 1:
                printf("Please input numbers of people/person ? \n");
                scanf("%d",&N);
                person = generatePeople(N,person,fNames,fSurnames);
                break;
            case 2:
                i = 0;
                //Correct answers will input by user
                //1 is true 0 is false answers
                printf("Please enter the answers. 1 is TRUE and 0 FALSE\n");
                while(i < 8){
                    printf("Answer %d = \t",i+1);
                    scanf("%d",&answers[i]);
                    if((answers[i] == 0 || answers[i] == 1 ) && (answers[i+1] == 0)){ //answers validness control
                         i++;
                    }else{
                        printf("Please input 1 or 0 !!! \n");
                    }
                }
                printf("\n");
                for(i=0;i<8;i++){
                    printf("Answer %d: %d \n",i+1,answers[i]);
                }

                select = 2;
                break;
            case 3:
                person = simulateQuiz(person,answers,N);
                break;
            case 4:
                listResults(person, N);
                break;
            default:
                printf("\nPlease enter a suitable number!\n\n.");
                break;
        }
    }

    return 0;
}

