#include <stdio.h>
#include <stdlib.h>
#include "streaming_service.h"

//R Event
int SL_LookUp_For_User(int uid) 
{
    struct user *curr=fuser;
    while(curr!=NULL) 
    {
        if (curr->uid == uid) 
        {
            return 1;
        }
        curr=curr->next;
    }
    return 0;
}

int SL_Insert_For_User(int uid)
{
    if(fuser==NULL)
    {
        return EXIT_FAILURE;
    }
    if(SL_LookUp_For_User(uid)==0)                                      //if the user doesn't exist, create it
    {
        struct user *t;
        t = (struct user *)malloc(sizeof(struct user));
        if (t == NULL) 
        {
            return EXIT_FAILURE;
        }
        t->uid = uid;
        t->suggestedHead=NULL;
        t->suggestedTail=NULL;
        t->watchHistory=NULL;
        t->next = fuser;
        fuser = t;  
    }
    else
    {
        return EXIT_FAILURE; 
    }
    return EXIT_SUCCESS;
}

//U Event

//it's the same with the SL_LookUp_For_User, but it returns the user instead a integer
struct user* SL_LookUp_For_User_RUser(int uid) 
{
    struct user *curr = fuser;
    while(curr!=NULL) 
    {
        if (curr->uid == uid) 
        {
            return curr;
        }
        curr=curr->next;
    }
    return NULL;
}

void SL_Delete_For_User(int uid) 
{
    struct user *curr = fuser;
    
    if(curr->uid==-1) 
    {
        return;                                             //if it doesn't exist the user with uid -1 (guard node)
    }
    
    if(curr->uid == uid)                                    //if the first node, is the node that we want to delete
    {
        fuser=curr->next;
        free(curr);
    }
    
    while(curr->next != NULL && curr->next->uid != uid) 
    {
        curr=curr->next;
    }

    if(curr->next != NULL && curr->next->uid==uid)             //we must save it first in a temp variable and then delete it
    {
        struct user *temp = curr->next;
        curr->next=curr->next->next;
        free(temp);
    }
}

void SL_Print_For_User(struct user *head)
{
   
    struct user *p = head;
    printf("   Users = ");
    while(p->uid!=-1)                                           //don't print the guard user, -1
    {
        printf("%d", p->uid);
        p = p->next;
        if(p->uid!=-1)                                          //if it's not the last node, print a ","
        {
            printf(",");
        }
    }
    printf("\n");
}

void Delete_All_From_WatchHistory(struct user* user) 
{
    while(user->watchHistory != NULL) 
    {
        struct movie* temp = user->watchHistory;
        user->watchHistory = temp->next;
        free(temp);
    }
}

//A event
void SL_Insert_NMovie(int mid, movieCategory_t category, int year)
{
    struct new_movie *t, *new;
    t=(struct new_movie*)malloc(sizeof(struct new_movie));        //create a new node
    if(t == NULL) 
    {
        return;
    }

    t->info.mid=mid;
    t->category=category;
    t->info.year=year;
    t->next=NULL;

    if(nmovie==NULL)                                                //if it's empty
    {
        nmovie=t;
    } 
    else 
    {
        if(mid < nmovie->info.mid) 
        {
            t->next=nmovie;
            nmovie=t;
        } 
        else 
        {
            new=nmovie;
            while(new->next!= NULL && mid > new->next->info.mid)    //put it in order
            {
                new=new->next;
            }
            t->next=new->next;
            new->next=t;
        }
    }
}

void SL_Print_NMovie(struct new_movie *head)
{
    struct new_movie *p = head;
    printf("   New movies = ");
    while(p != NULL)
    {
        printf("<%u,%d,%u>", p->info.mid, p->category, p->info.year);
        p = p->next;
        if(p!=NULL)
        {
            printf(",");
        }
    }
    printf("\n");
}

//D event
void SL_Insert_Movie(int mid, int year, movieCategory_t category) 
{
    struct movie *t, *new;
    t = (struct movie*)malloc(sizeof(struct movie));                
    if(t == NULL) 
    {
        return;
    }

    t->info.mid = mid;
    t->info.year = year;
    t->next = NULL;

    if(movieCategories[category] == NULL)              
    {
        movieCategories[category] = t;
    } 
    else 
    {
        new = movieCategories[category];
        while(new->next != NULL) 
        {
            new = new->next;
        }
        new->next = t;
    }
}

void SL_Traverse(struct new_movie *n) {
    struct new_movie *p = n;
    int i=1 ,j=1, k=1, y=1, u=1, l=1;                                    //counter of the elements of each list 
    int categories=0;

    // Traverse the new movie list
    while(p != NULL) 
    {
        SL_Insert_Movie(p->info.mid, p->info.year, p->category);        // Insert the movie to the right category list
        p = p->next;
    }
    
    // Print all the categories with all the movies
    for(categories = 0; categories < 6; ++categories) 
    {
        switch(categories)
        {
            case 0:
                printf("    HORROR: ");
                struct movie *currh = movieCategories[categories];
                while (currh != NULL)                               //print all the list
                {
                    printf("<%u,%d>", currh->info.mid, i);
                    i++;
                    currh = currh->next;
                    if (currh != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 1: 
                printf("    SCIFI: ");
                struct movie *currs = movieCategories[categories];
                while (currs != NULL) 
                {
                    printf("<%u,%d>", currs->info.mid, j);
                    j++;
                    currs = currs->next;
                    if (currs != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 2:
                printf("    DRAMA: ");
                struct movie *currd = movieCategories[categories];
                while (currd != NULL) 
                {
                    printf("<%u,%d>", currd->info.mid, k);
                    k++;
                    currd = currd->next;
                    if (currd != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 3:
                printf("    ROMANCE: ");
                struct movie *currr = movieCategories[categories];
                while (currr != NULL) 
                {
                    printf("<%u,%d>", currr->info.mid, u);
                    u++;
                    currr = currr->next;
                    if (currr != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 4: 
                printf("    DOCUMENTARY: ");
                struct movie *currdo = movieCategories[categories];
                while (currdo != NULL) 
                {
                    printf("<%u,%d>", currdo->info.mid, l);
                    l++;
                    currdo = currdo->next;
                    if (currdo != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 5:
                printf("    COMEDY: ");
                struct movie *currc = movieCategories[categories];
                while (currc != NULL) 
                {
                    printf("<%u,%d>", currc->info.mid, y);
                    y++;
                    currc = currc->next;
                    if (currc != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            default: 
                printf("ERROR....");
                break; 
        }
        printf("\n");
    }
}

//W event
struct movie* Search_Movie_In_Category(unsigned mid) 
{
    struct movie *currh=movieCategories[1], *currs=movieCategories[2], *currd=movieCategories[3], *currr=movieCategories[4], *currdo=movieCategories[5], *currc=movieCategories[6]; //all the category lists
    int categories=0;
    for(categories = 0; categories < 6; ++categories) 
    {
        switch(categories){
            case 0:
                while (currh != NULL) 
                {
                    if (currh->info.mid == mid) 
                    {
                        return currh;                                               // Movie doesn't exist
                    }
                    currh = currh->next;                
                }
                break;
            case 1: 
                while (currs != NULL) 
                {
                    if (currs->info.mid == mid)
                    {
                        return currs; 
                    }
                    currs = currs->next;                
                }
                break;
            case 2:
                while (currd != NULL) 
                {
                    if (currd->info.mid == mid) 
                    {
                        return currd; 
                    }
                    currd = currd->next;                
                }
                break;
            case 3:
                while (currr != NULL) 
                {
                    if (currr->info.mid == mid) 
                    {
                        return currr; 
                    }
                    currr = currr->next;                
                }
                break;
            case  4: 
                while (currdo != NULL) 
                {
                    if (currdo->info.mid == mid) 
                    {
                        return currdo;
                    }
                    currdo = currdo->next;                  
                }
                break;
            case 5:
                while (currc != NULL) 
                {
                    if (currc->info.mid == mid) 
                    {
                        return currc; 
                    }
                    currc = currc->next;    
                }
                break; 
        }
    }
    return NULL;                                                // Movie doesn't exist
}

struct user* Search_User(int uid)                               // Function to search for a user in the user list
{
    struct user* curr = fuser;
    while(curr != NULL) 
    {
        if(curr->uid == uid) 
        {
            return curr;                                        // User have been found
        }
        curr = curr->next;
    }
    return NULL;                                                // User doesn't exist
}

void Insert_Movie_To_WatchHistory(struct user* user, struct movie_info movieInfo) // Add a movie to the watch history stack of a user
{
    struct movie* newMovie = (struct movie*)malloc(sizeof(struct movie));
    if(newMovie == NULL) 
    {
        exit(EXIT_FAILURE);
    }
    newMovie->info = movieInfo;
    newMovie->next = NULL;

    newMovie->next = user->watchHistory;                                // Push the new movie to the watch history stack
    user->watchHistory = newMovie;
}

void Seach_U_M(int uid, unsigned mid)
{
     struct movie* Found_The_Movie = Search_Movie_In_Category(mid);

    if(Found_The_Movie != NULL) 
    {
        struct user* Found_The_User = Search_User(uid);

        if(Found_The_User != NULL) 
        {
            //If user found insert the movie to the user's watch history
            Insert_Movie_To_WatchHistory(Found_The_User, Found_The_Movie->info);
            printf("   User %d Watch History = ", uid);
            watch_H=Found_The_User->watchHistory;
            while(watch_H!=NULL)
            {
                printf("<%u>",watch_H->info.mid);
                watch_H=watch_H->next;
                if(watch_H!=NULL)
                {
                    printf(",");
                }
            }
            
        } 
        else 
        {
            printf("   USER NOT FOUND");
        }
    } 
    else 
    {
        printf("   MOVIE NOT FOUND");
    }
}

//T Event
void print_Category_Elements(int i)
{
    printf("   Category list = ");
    struct movie *curr = movieCategories[i];
    while(curr != NULL) 
    {
        printf("<%u>", curr->info.mid);
        curr = curr->next;
        if(curr != NULL) 
        {
            printf(",");
        }
    }
    printf("\n");
}
   
void SL_Delete_From_Category(unsigned mid) 
{
    struct movie* temp = NULL;
    int i;
    for(i = 0; i < 6; ++i) {
        struct movie* curr = movieCategories[i];

        while(curr != NULL) {
            if(curr->info.mid == mid) 
            {
                if(temp == NULL) 
                {
                    // The movie is the first node in the category
                    movieCategories[i] = curr->next;
                } 
                else 
                {
                    temp->next = curr->next;
                }
                free(curr);
                
                //print the movie and which category list
                if(i==0)
                {
                    printf("   %d removed from horror category list.\n", mid);
                    print_Category_Elements(i);
                }
                else if(i==1)
                {
                    printf("   %d removed from scifi category list.\n", mid);
                    print_Category_Elements(i);
                }
                else if(i==2)
                {
                    printf("   %d removed from drama category list.\n", mid);
                    print_Category_Elements(i);
                }
                else if(i==3)
                {                
                    printf("   %d removed from romance category list.\n", mid);
                    print_Category_Elements(i);
                }
                else if(i==4)
                {
                    printf("   %d removed from documentary category list.\n", mid);
                    print_Category_Elements(i);
                }
                else if(i==5)
                {
                    printf("   %d removed from comedy category list.\n", mid);
                    print_Category_Elements(i);
                }
                return;
            }
            temp = curr;
            curr = curr->next;
        }
        // temp for the next category
        temp = NULL;
    }
}

//M Event
void print_Movies()
{
    int i=1, j=1, k=1, y=1, l=1, u=1;
    int categories=0;
    for(categories = 0; categories < 6; ++categories) 
    {
        switch(categories)
        {
            case 0:
                printf("    HORROR: ");
                struct movie *currh = movieCategories[categories];
                while (currh != NULL) 
                {
                    printf("<%u,%d>", currh->info.mid, i);
                    i++;
                    currh = currh->next;
                    if (currh != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 1: 
                printf("    SCIFI: ");
                struct movie *currs = movieCategories[categories];
                while (currs != NULL) 
                {
                    printf("<%u,%d>", currs->info.mid, j);
                    j++;
                    currs = currs->next;
                    if (currs != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 2:
                printf("    DRAMA: ");
                struct movie *currd = movieCategories[categories];
                while (currd != NULL) 
                {
                    printf("<%u,%d>", currd->info.mid, k);
                    k++;
                    currd = currd->next;
                    if (currd != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 3:
                printf("    ROMANCE: ");
                struct movie *currr = movieCategories[categories];
                while (currr != NULL) 
                {
                    printf("<%u,%d>", currr->info.mid, y);
                    y++;
                    currr = currr->next;
                    if (currr != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 4: 
                printf("    DOCUMENTARY: ");
                struct movie *currdo = movieCategories[categories];
                while (currdo != NULL) 
                {
                    printf("<%u,%d>", currdo->info.mid, u);
                    u++;
                    currdo = currdo->next;
                    if (currdo != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            case 5:
                printf("    COMEDY: ");
                struct movie *currc = movieCategories[categories];
                while (currc != NULL) 
                {
                    printf("<%u,%d>", currc->info.mid, l);
                    l++;
                    currc = currc->next;
                    if (currc != NULL) 
                    {
                        printf(",");
                    }
                }
                break;
            default: 
                printf("ERROR....");
                break; 
        }
        printf("\n");
    }
}

//P event
void Watch_History_Of_All_User()
{
    if(fuser == NULL)
    {
        return;
    }

    struct user *u=fuser;
    while(u->uid !=-1)
    {
        printf("   %d:\n   Watch History: ", u->uid);

        struct movie *w=watch_H; 
        w=u->watchHistory;

        while(w != NULL)
        {
            printf("<%u>", w->info.mid);
            w = w->next;

            if (w != NULL)
            {
                printf(",");
            }
        }

        printf("\n");  

        u = u->next;                             //next user
    }
}

/*
 * Register User - Event R
 * 
 * Adds user with ID uid to
 * users list, as long as no
 * other user with the same uid
 * already exists.
 *
 * Returns 0 on success, -1 on
 * failure (user ID already exists,
 * malloc or other error)
 */
int register_user(int uid)
{ 
     
    printf("R %d\n",uid);
    SL_Insert_For_User(uid);
    SL_Print_For_User(fuser);
    printf("DONE\n");
    printf("\n");
    return EXIT_SUCCESS;
}

/*
 * Unregister User - Event U
 *
 * Removes user with ID uid from
 * users list, as long as such a
 * user exists, after clearing the
 * user's suggested movie list and
 * watch history stack
 */
void unregister_user(int uid)
{
    printf("U %d\n", uid);
    Delete_All_From_WatchHistory(SL_LookUp_For_User_RUser(uid));
    SL_Delete_For_User(uid);
    SL_Print_For_User(fuser);
    printf("DONE\n\n");
}

/*
 * Add new movie - Event A
 *
 * Adds movie with ID mid, category
 * category and release year year
 * to new movies list. The new movies
 * list must remain sorted (increasing
 * order based on movie ID) after every
 * insertion.
 *
 * Returns 0 on success, -1 on failure
 */
int add_new_movie(unsigned mid, movieCategory_t category, unsigned year)
{
    printf("A %u %d %u\n",mid,category,year);
    SL_Insert_NMovie(mid,category,year);
    SL_Print_NMovie(nmovie);
    printf("DONE\n\n");
    return EXIT_SUCCESS;
}

/*
 * Distribute new movies - Event D
 *
 * Distributes movies from the new movies
 * list to the per-category sorted movie
 * lists of the category list array. The new
 * movies list should be empty after this
 * event. This event must be implemented in
 * O(n) time complexity, where n is the size
 * of the new movies list
 */
void distribute_new_movies(void)
{
    printf("D\n");
    printf("Categorized Movies:\n");
    SL_Traverse(nmovie);
    struct new_movie *tmp;
    while (nmovie != NULL) {
        tmp = nmovie;
        nmovie = nmovie->next;
        free(tmp);
    }
    nmovie = NULL;

    printf("DONE\n\n");
}

/*
 * User watches movie - Event W
 *
 * Adds a new struct movie with information
 * corresponding to those of the movie with ID
 * mid to the top of the watch history stack
 * of user uid.
 *
 * Returns 0 on success, -1 on failure
 * (user/movie does not exist, malloc error)
 */
int watch_movie(int uid, unsigned mid)
{
   printf("W\n");
   Seach_U_M(uid, mid);
   printf("\nDONE\n\n");
}

/*
 * Suggest movies to user - Event S
 *
 * For each user in the users list with
 * id != uid, pops a struct movie from the
 * user's watch history stack, and adds a
 * struct suggested_movie to user uid's
 * suggested movies list in alternating
 * fashion, once from user uid's suggestedHead
 * pointer and following next pointers, and
 * once from user uid's suggestedTail pointer
 * and following prev pointers. This event
 * should be implemented with time complexity
 * O(n), where n is the size of the users list
 *
 * Returns 0 on success, -1 on failure
 */
int suggest_movies(int uid)
{
      if(fuser == NULL) return -1;

    struct user *target = NULL;
    struct user *u = fuser;  // Ξεκινάμε από sentinel

    // Βρίσκουμε τον χρήστη με uid
    while(u->uid != -1) {
        if(u->uid == uid) {
            target = u;
            break;
        }
        u = u->next;
    }

    if(target == NULL) {
        printf("User %d not found!\n", uid);
        return -1;
    }

    int count = 0;
    u = fuser;  // Διατρέχουμε όλους τους χρήστες για suggestions
    while(u->uid != -1) {
        if(u->uid != uid && u->watchHistory != NULL) {

            // Παίρνουμε πρώτο movie από watchHistory
            struct movie *m = u->watchHistory;
            u->watchHistory = m->next;
            m->next = NULL;

            // Δημιουργία node για suggested list
            struct suggested_movie *s = malloc(sizeof(struct suggested_movie));
            s->info = m->info;
            s->prev = s->next = NULL;
            free(m);

            // Εναλλαγή head/tail
            if(!target->suggestedHead) {
                target->suggestedHead = target->suggestedTail = s;
            } else if(count % 2 == 0) {
                s->next = target->suggestedHead;
                target->suggestedHead->prev = s;
                target->suggestedHead = s;
            } else {
                s->prev = target->suggestedTail;
                target->suggestedTail->next = s;
                target->suggestedTail = s;
            }

            count++;
        }

        u = u->next;
    }

    // Εκτύπωση suggested list
    printf("S %d\n", uid);
    printf("User %d Suggested Movies = ", uid);
    struct suggested_movie *p = target->suggestedHead;
    while(p != NULL) {
        printf("<%u>", p->info.mid);
        if(p->next != NULL) printf(",");
        p = p->next;
    }
    printf("\nDONE\n\n");

    return 0;
}

/*
 * Filtered movie search - Event F
 *
 * User uid asks to be suggested movies
 * belonging to either category1 or category2
 * and with release year >= year. The resulting
 * suggested movies list must be sorted with
 * increasing order based on movie ID (as the
 * two category lists). This event should be
 * implemented with time complexity O(n + m),
 * where n, m are the sizes of the two category lists
 *
 * Returns 0 on success, -1 on failure
 */
int filtered_movie_search(int uid, movieCategory_t category1, movieCategory_t category2, unsigned year)
{
    if(fuser == NULL) return -1;

    struct user *target = NULL;
    struct user *u = fuser;

    // Βρίσκουμε τον user
    while(u->uid != -1) {
        if(u->uid == uid) {
            target = u;
            break;
        }
        u = u->next;
    }

    if(target == NULL) {
        printf("User %d not found!\n", uid);
        return -1;
    }

    // Καθαρίζουμε την προηγούμενη suggested list
    struct suggested_movie *tmp = target->suggestedHead;
    while(tmp) {
        struct suggested_movie *next = tmp->next;
        free(tmp);
        tmp = next;
    }
    target->suggestedHead = target->suggestedTail = NULL;

    // Pointers για τις δύο category lists
    struct movie *p1 = movieCategories[category1];
    struct movie *p2 = movieCategories[category2];

    struct suggested_movie *last = NULL;

    // Merge δύο sorted lists με year filter
    while(p1 != NULL || p2 != NULL) {
        struct movie *m = NULL;

        if(p1 && p2) {
            if(p1->info.mid <= p2->info.mid) {
                m = p1; p1 = p1->next;
            } else {
                m = p2; p2 = p2->next;
            }
        } else if(p1) {
            m = p1; p1 = p1->next;
        } else if(p2) {
            m = p2; p2 = p2->next;
        }

        if(m->info.year >= year) {
            struct suggested_movie *s = malloc(sizeof(struct suggested_movie));
            s->info = m->info;
            s->next = NULL;
            s->prev = last;

            if(last) last->next = s;
            else target->suggestedHead = s;  // πρώτη εισαγωγή

            last = s;
        }
    }

    target->suggestedTail = last;

    // Εκτύπωση για έλεγχο
    printf("F %d\n", uid);
    printf("User %d Suggested Movies = ", uid);
    tmp = target->suggestedHead;
    while(tmp) {
        printf("<%u>", tmp->info.mid);
        if(tmp->next) printf(",");
        tmp = tmp->next;
    }
    printf("\nDONE\n\n");

    return 0;
}

/*
 * Take off movie - Event T
 *
 * Movie mid is taken off the service. It is removed
 * from every user's suggested list -if present- and
 * from the corresponding category list.
 */
void take_off_movie(unsigned mid)
{
    printf("T %u\n", mid);

    if(fuser == NULL) {
        printf("DONE\n\n");
        return;
    }

    //Αφαίρεση από suggested lists όλων των χρηστών
    struct user *u = fuser;                                                        
    while(u->uid != -1) {
        struct suggested_movie *s = u->suggestedHead;
        while(s) {
            struct suggested_movie *next = s->next;
            if(s->info.mid == mid) {
                printf("   %u removed from user %d suggested list.\n", mid, u->uid);

                if(s->prev) s->prev->next = s->next;
                else u->suggestedHead = s->next;

                if(s->next) s->next->prev = s->prev;
                else u->suggestedTail = s->prev;

                free(s);
            }
            s = next;
        }
        u = u->next;
    }

    //Αφαίρεση από category lists
    SL_Delete_From_Category(mid);

    printf("DONE\n\n");
}



/*
 * Print movies - Event M
 *
 * Prints information on movies in
 * per-category lists
 */
void print_movies(void)
{
    printf("M\n");
    printf("Categorized Movies:\n");
    print_Movies();
    printf("DONE\n\n");
}

/*
 * Print users - Event P
 *
 * Prints information on users in
 * users list
 */
void print_users(void)
{
    printf("P\n");
    printf("Users:\n");
    Watch_History_Of_All_User();
    printf("DONE\n\n");
}