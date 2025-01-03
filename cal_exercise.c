//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute)!=EOF) 
	{
    	exercise_list_size++;
    	
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    
	printf("The list of exercises: \n");
    
	for(i=0;i<=exercise_list_size;i++)
    {	
    	if(i!=exercise_list_size)
    		printf("%d. %s (%d kcal burned per min.)\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
		
		else
			printf("%i. Exit\n",i+1);
	}

    // ToCode: to enter the exercise to be chosen with exit option
	
	printf("Choose (1-%i):",exercise_list_size+1);
    scanf("%i",&choice);
    
    if(choice==exercise_list_size+1)
    {
    	printf("Exiting exercise selection. \n");
    	return;
	}
    
    else if(choice<1||choice>exercise_list_size+1)
    {
		printf("[Error] \nInvalid option. \n");
        
        return;
	}
 
    // To enter the duration of the exercise
    
	else //choice==1~exercise_list_size+1
    {	
		printf("Enter the duration of the exercise (in min.): ");
    	scanf("%d", &duration);
	}
	
	// choice*duration=total calories
	int calories_burned = exercise_list[choice-1].calories_burned_per_minute * duration;
	
    // ToCode: to enter the selected exercise and total calcories burned in the health data
    
	Exercise selected_exercise=exercise_list[choice-1];		//selected_exercise={"exercise_name",calories_burned_per_minute}
	
	health_data->exercises[health_data->exercise_count]=selected_exercise;	//health_data->exercise[choice-1]={"exercise_name",calories_burned_per_minute}
	health_data->exercises[health_data->exercise_count].calories_burned_per_minute = calories_burned; //Overwrite with calories_burned
	health_data->exercise_count++;								//Increase the number of exercises intaked by 1
	health_data->total_calories_burned+=calories_burned;
    
}
