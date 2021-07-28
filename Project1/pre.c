#include <stdio.h>
#define MAX_STUDENTS 50
//Structure to store student name and grade.
struct Person
{
    char name[50];
    float gpa;
};

int main()
{
	//Declares an array of people with max amount being 50
    struct Person arr_person[MAX_STUDENTS];
    
    //Iterator for the while loop. Breaks out if EOF is read or i gets to 50
    int i = 0;
    while(scanf("%s %f", arr_person[i].name, &arr_person[i].gpa) != EOF && i < 50)
    {
    	//Iterates i up one.
        i++;
    }
    
    //If statement to let the user know why they were pushed out of the user input loop
    if(i == 50)
    {
        printf("Reached MAX amount of students(50).\n");
    }
    
    //Gets size of the person array.
    size_t n = sizeof(arr_person)/sizeof(arr_person[0]);
    //Loops through array
    for(int j = 0; j < n; j++)
    {
    	//If the persons gpa is above a 2.0 it prints the students name.
        if(arr_person[j].gpa > 2.0)
        {
            printf("%s\n", arr_person[j].name);
        }
    }

    //Closes program
    return 0;
}
