#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a3_functions.h"
#include "a3_nodes.h"

int main()
{

    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    //intialize all friends posts
    for (user_t *current = users; current != NULL ; current = current->next){
        intalize_friends(current, users);
    }
    printf("\n********************************************\n");
    printf("       Welcome to Text-Based Facebook");
    printf("\n********************************************\n");

    _Bool done = false;

    while (!done){
        print_menu();
        handle_menu(users);
        

    }

}