#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a3_functions.h"
#include "a3_nodes.h"
#include <stdbool.h>
#include <assert.h>

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   // malloc
   user_t *new_user = malloc(sizeof(user_t));
   assert(new_user != NULL);

   // Initialize
   strcat(new_user->username, username);
   strcat(new_user->password, password);
   new_user->friends = NULL;
   new_user->next = NULL;
   new_user->posts = NULL;

   // add at location in link list
   user_t *current = users;
   if (users == NULL)
   {
      return new_user;
   }

   _Bool first = false;

   while (current->next != NULL)
   {

      for (int index = 0; strcmp(&(current->username[index]), &(username[index])) <= 0 && strcmp(&(username[index]), &(current->next->username[index])) <= 0; index++)
      {
         if (strcmp(&(current->username[index]), &(username[index])) < 0 && strcmp(&(username[index]), &(current->next->username[index])) < 0)
         {
            new_user->next = current->next;
            current->next = new_user;

            return users;
         }
      }
      // if first
      for (int i = 0; !first && strcmp(&(current->username[i]), &(username[i])) >= 0; i++)
      {
         if (strcmp(&(current->username[0]), &(username[0])) > 0)
         {
            new_user->next = current;
            users = new_user;
            return users;
         }
      }

      first = true;
      current = current->next;
   }

   // if only one other user in users
   if (current->next == NULL)
   {
      // if current user should be first
      for (int i = 0; strcmp(&(current->username[i]), &(username[i])) <= 0; i++)
      {
         if (strcmp(&(current->username[i]), &(username[i])) < 0)
         {
            current->next = new_user;
            return users;
         }
      }
      // if new user should be first
      new_user->next = current;
      users = new_user;
      return users;
   }
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{

   assert(users != NULL);
   user_t *current = users;

   for (int i = 0; current != NULL; i++, current = current->next)
   {
      if (strcmp(current->username, username) == 0)
      {
         return current;
      }
   }
   return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new_friend = malloc(sizeof(friend_t));
   strcat(new_friend->username, username);

   new_friend->next = NULL;

   return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   assert(user != NULL);

   friend_t *new_friend = create_friend(friend);

   friend_t *friends = user->friends;

   if (friends == NULL)
   {
      user->friends = new_friend;
      return;
   }

   _Bool first = false;

   while (friends->next != NULL)
   {

      for (int index = 0; strcmp(&(friends->username[index]), &(friend[index])) <= 0 && strcmp(&(friend[index]), &(friends->next->username[index])) <= 0; index++)
      {
         // if new friend fits between current and next
         if (strcmp(&(friends->username[index]), &(friend[index])) < 0 && strcmp(&(friend[index]), &(friends->next->username[index])) < 0)
         {

            friend_t *temp = friends->next;
            friends->next = new_friend;
            new_friend->next = temp;
            return;
         }
      }

      // if new friend is at beginning of link list
      for (int i = 0; !first && strcmp(&(friends->username[i]), &(friend[i])) >= 0; i++)
      {
         if (strcmp(&(friends->username[0]), &(friend[0])) > 0)
         {
            new_friend->next = friends;
            user->friends = new_friend;
            return;
         }
      }
      first = true;
      friends = friends->next;
   }

   // if theres only one friend in link list currently
   if (friends->next == NULL)
   {
      // if current friend has should be first
      for (int i = 0; strcmp(&(friends->username[i]), &(friend[i])) <= 0; i++)
      {
         if (strcmp(&(friends->username[i]), &(friend[i])) < 0)
         {
            friends->next = new_friend;
            return;
         }
      }
      // if new friend should be first
      new_friend->next = friends;
      user->friends = new_friend;
   }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   friend_t *friends = user->friends;

   // for first
   if (strcmp(friends->username, friend_name) == 0)
   {
      friend_t *temp = user->friends;
      user->friends = friends->next;
      free(temp);
      temp = NULL;
      return true;
   }

   for (int i = 0; friends->next != NULL; i++, friends = friends->next)
   {
      if (strcmp(friends->next->username, friend_name) == 0)
      {
         friend_t *temp = friends->next;
         friends->next = friends->next->next;
         free(temp);
         temp = NULL;
         return true;
      }
   }

   return false;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new_post = malloc(sizeof(post_t));
   assert(new_post != NULL);

   strcat(new_post->content, text);
   new_post->next = NULL;

   return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   post_t *new_post = create_post(text);

   if (user->posts == NULL)
   {
      user->posts = new_post;
   }
   else
   {
      new_post->next = user->posts;
      user->posts = new_post;
   }
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   post_t *posts = user->posts;

   if (number == 1)
   {
      posts = posts->next;
      user->posts = posts;
      return true;
   }

   for (int i = 1; posts->next != NULL && i <= number; i++, posts = posts->next)
   {
      if (i + 1 == number)
      {
         posts->next = posts->next->next;
         return true;
      }
   }

   return false;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   post_t *posts = user->posts;

   if (posts == NULL)
   {
      printf("\nNo posts available for %s.", user->username);
   }

   for (int i = 1; posts != NULL; posts = posts->next, i++)
   {
      printf("\n%d- %s: %s\n", i, user->username, posts->content);
   }
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   friend_t *friends = user->friends;
   if (user->friends == NULL)
   {
      printf("No friends available for %s", user->username);
   }

   for (int i = 1; friends != NULL; friends = friends->next, i++)
   {
      printf("%d- %s\n", i, friends->username);
   }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   user_t *current = users;

   for (int n = 0; current != NULL; n++, current = current->next)
   {
      if (n == 2)
      {
         n = 0;
         char input;

         printf("\nWould you like to display posts from the next 2 users? (Y/N) :");
         scanf(" %c", &input);
         while (input != 'N' && input != 'n' && input != 'Y' && input != 'y')
         {
            printf("Invalid input");
            printf("\nWould you like to display posts from the next 2 users? (Y/N) :");
            scanf(" %c", &input);
         }

         if (input == 'N' || input == 'n')
         {
            return;
         }
      }
      display_user_posts(current);
   }
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   for (; users != NULL;)
   {
      post_t *posts = users->posts;
      friend_t *friends = users->friends;
      // delete all user posts
      for (; posts != NULL;)
      {
         post_t *p_temp = posts;
         posts = posts->next;
         free(p_temp);
         p_temp = NULL;
      }

      // delete all user friends
      for (; friends != NULL;)
      {
         friend_t *f_temp = friends;
         friends = friends->next;
         free(f_temp);
         f_temp = NULL;
      }

      user_t *temp = users;
      users = users->next;
      free(temp);
      temp = NULL;
   }
   exit(0);
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("\n********************************************\n");
   printf("                   Main Menu");
   printf("\n********************************************\n");
   printf("1. Register a new User\n");
   printf("2. Login with exitising user's information\n");
   printf("3. Exit\n");
}

void print_logging_menu(user_t *user)
{
   printf("\n********************************************\n");
   printf("            Welcome %s:", user->username);
   printf("\n********************************************\n");
   printf("1. Manage user's profile (change password)\n");
   printf("2. Manage a user's posts (display/add/remove)\n");
   printf("3. Manage a user's friends (display/add/remove)\n");
   printf("4. Display All Posts\n");
   printf("5. Logout\n");
}

void handle_menu(user_t *users)
{
   int integer;

   printf("\nEnter a choice: ");
   scanf("%d", &integer);

   while (0 > integer || integer > 3)
   {
      printf("\nInvalid choice. Please try again.\n");
      print_menu();
      printf("\nEnter a choice: ");
      scanf("%d", &integer);
   }

   switch (integer)
   {
   // new user
   case 1:
      printf("\nEnter a username: ");
      char username[20];
      scanf("%s", username);

      user_t *new_user = find_user(users, username);
      //if user already exsts
      if (new_user != NULL)
      {
         printf("\nUser already exists\n");
         break;
      }
      printf("\nEnter a password up to 15 characters: ");
      char pass[15];
      scanf("%s", pass);
      add_user(users, username, pass);
      printf("\n***** User Added! *****\n");

      break;

   // change pass
   case 2:
   {
      printf("\nEnter a username: ");
      char l_username[20];
      scanf("%s", l_username);
      user_t *l_user = find_user(users, l_username);

      if (l_user == NULL)
      {
         printf("\n--------------------------------------------\n");
         printf("                User not found.");
         printf("\n--------------------------------------------\n");
         break;
      }

      char l_pass[15];
      printf("\nEnter the user's password: ");
      scanf("%s", l_pass);
      if (strcmp(l_pass, l_user->password) == 0)
      {
         handle_log_menu(l_user, users);
      }
      else
      {
         printf("Incorrect Password");
      }
      break;
   }

   case 3:
      printf("\n********************************************\n");
      printf("    Thank you for using Text-Based Facebook\n");
      printf("                   Goodbye!");
      printf("\n********************************************\n");
      teardown(users);
      break;
   }
}

void handle_log_menu(user_t *user, user_t *users)
{
   int integer;
   _Bool exit = false;
   intalize_friends(user, users); //updates all friends posts
   
   while (!exit)
   {
      print_logging_menu(user);
      printf("\nEnter a choice: ");
      scanf("%d", &integer);

      while (0 > integer || integer > 5)
      {
         printf("\nInvalid choice. Please try again.\n");
         print_logging_menu(user);
         printf("\nEnter a choice: ");
         scanf("%d", &integer);
      }

      switch (integer)
      {
      // change pass
      case 1:
      {
         printf("\nEnter a new password up to 15 characters: ");
         char pass[15];
         scanf("%s", pass);
         strcpy(user->password, pass);
         printf("\n***** Password changed! *****\n");
         break;
      }
      // manage user's posts
      case 2:
         handle_user_posts(user);
         break;

      case 3:
         handle_friends_menu(user, users);
         break;

      case 4:
         display_all_posts(users);
         break;

      case 5:
         exit = true;
         return;
         break;
      }
   }
}

void handle_user_posts(user_t *user)
{
   _Bool exit = false;

   while (!exit)
   {
      // print posts
      printf("\n--------------------------------------------\n");
      printf("         %s's Posts\n", user->username);
      display_user_posts(user);
      printf("\n--------------------------------------------\n");

      // options for actions
      printf("1. Add a new user post\n");
      printf("2. Remove a users post\n");
      printf("3. Return to main menu\n");

      int post_select;

      printf("\nEnter a choice: ");
      scanf("%d", &post_select);

      while (post_select < 0 || post_select > 3)
      {
         printf("\nInvalid choice. Please try again.\n");
         printf("Enter a choice: ");
         scanf("%d", &post_select);
      }

      switch (post_select)
      {
      case 1:
      {
         char content[250];
         printf("\nEnter post content up to 250 characters: ");
         // scanf("%249s", content);
         int c;
         while ((c = getchar()) != '\n' && c != EOF)
         {
         } // Clear input buffer

         fgets(content, 249, stdin);
         add_post(user, content);
         printf("\nPost added to profile.\n");
         break;
      }

      case 2:
      {
         int post_num;
         printf("Which post do you want to delete? ");
         scanf("%d", &post_num);
         _Bool deleted = delete_post(user, post_num);

         if (deleted)
         {
            printf("\nPost %d was deleted successfully\n", post_num);
         }
         else
         {
            printf("\nInvalid post number\n");
         }
         break;
      }

      case 3:
         exit = true;
         return;
      }
   }
}

void intalize_friends(user_t *user, user_t *users)
{
   friend_t *friends = user->friends;

   // iterate through friends link list till desired friend reached
   for (; friends != NULL; friends = friends->next)
   {
      user_t *friend = find_user(users, friends->username);
      friends->posts = &(friend->posts);
   }
}

void handle_friends_menu(user_t *user, user_t *users)
{
   _Bool exit = false;
   while (!exit)
   {
      printf("\n--------------------------------------------\n");
      printf("         %s's friends", user->username);
      printf("\n--------------------------------------------\n");

      printf("1. Display all user's friends\n");
      printf("2. Add a new friend\n");
      printf("3. Delete a friend\n");
      printf("4. Display a friend's posts\n");
      printf("5. Return to main menu\n");

      printf("\nYour choice: ");
      int friends_input;
      scanf("%d", &friends_input);

      switch (friends_input)
      {
      case 1:
         printf("\nList of %s's friends\n", user->username);
         display_user_friends(user);
         break;

      case 2:
      {
         char new_friend[30];
         printf("\nEnter a new friend's name: ");
         scanf("%s", new_friend);
         user_t *user_friend = find_user(users, new_friend);
         if (user_friend == NULL)
         {
            printf("\n--------------------------------------------\n");
            printf("                User not found.");
            printf("\n--------------------------------------------\n");
            return;
         }
         add_friend(user, new_friend);
         intalize_friends(user, users);
         printf("Friend added to the list");
         break;
      }

      case 3:
      {
         printf("\nList of Dumbeldore's friends: \n");
         display_user_friends(user);
         printf("\nEnter a friends name to delete: ");
         char del_friend[30];
         scanf("%s", del_friend);
         _Bool deleted = delete_friend(user, del_friend);

         if (deleted == false)
         {
            printf("Invalid friend's name");
         }
         printf("\nList of Dumbeldore's friends: \n");
         display_user_friends(user);

         break;
      }

      case 4:
      {
         display_user_friends(user);
         printf("\nEnter the username of the desired friend: ");
         char p_username[30];
         scanf("%s", p_username);

         for (friend_t *friend = user->friends; friend != NULL; friend = friend->next)
         {
            if (strcmp(p_username, friend->username) == 0)
            {
               post_t *posts = *(friend->posts);
               for (int i = 1; posts != NULL; posts = posts->next, i++)
               {
                  printf("\n%d- %s: %s\n", i, friend->username, posts->content);
               }
            }
         }
      }
      case 5:
         exit = true;
         return;
      }
   }
}


user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
