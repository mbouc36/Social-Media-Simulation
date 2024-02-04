#ifndef __A3_FUNCTIONS_H__
#define __A3_FUNCTIONS_H__
#include "a3_nodes.h"

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password);

/*
   Function that searches if the user is available in the database 
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username);


/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username);


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend);

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name);

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text);

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text);

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number);

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user);


/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user);

/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns. 
*/
void display_all_posts(user_t *users);

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users);

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu();


/* 

   Function that reads users from the text file.
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users);



// handles actions for the pop up menu
void handle_menu(user_t *users);

//handles actions for the posts menu
void handle_user_posts(user_t *user);

//handles action for the friends menu
void handle_friends_menu(user_t *user, user_t *users);

// print menu once logged in
void print_logging_menu(user_t *user);

//handle actions once logged in
void handle_log_menu(user_t *user, user_t *users);

//updates friends posts
void intalize_friends(user_t *user, user_t *users);

#endif