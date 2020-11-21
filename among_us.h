/**************************************************
 *                                                *
 * file: among_us.h                               *
 *                                                *
 *                                                *
 * @Author  Antonios Peris                        *
 * @Version 20-10-2020                            *
 * @email   csdp1196@csd.uoc.gr                   *
 *                                                *
 * @brief   Header file for the needs of cs-240   *
 * project 2020, with the structures and function *
 * prototypes                                     * 
 *                                                *
 **************************************************
 */

#ifndef __AMONG_US_H_
#define __AMONG_US_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Structure defining a node of the players double linked list
 * tree
 */
struct Players
{
    int pid;                      /*Player's identifier*/
    int is_alien;                 /*Alien flag*/
    int evidence;                 /*Amount of evidence*/
    struct Players *prev;         /*Pointer to the previous node*/
    struct Players *next;         /*Pointer to the next node*/
    struct Tasks *tasks_head;     /*Pointer to the head of player's task list*/
    struct Tasks *tasks_sentinel; /*Pointer to the sentinel of player's task list*/
};

/**
 * Structure defining a node of the tasks sorted linked list
 */
struct Tasks
{
    int tid;                      /*Task's identifier*/
    int difficulty;               /*Task's difficulty*/
    struct Tasks *next;           /*Pointer to the next node*/  
};

struct Head_GL
{
    int tasks_count[3];           /*Count of tasks*/
    struct Tasks *head;           /*Pointer to the head of general list*/
};
struct Head_Completed_Task_Stack
{
    int count;                    /*Count of completed tasks*/
    struct Tasks *head;           /*Pointer to the top element of the stack*/
};

/* Global variable, pointer to the head of the players list */
struct Players *players_head;

/* Global variable, pointer to the head of the tasks list */
struct Head_GL *tasks_head;

/* Global variable, pointer to the top of the completed task's stack */
struct Head_Completed_Task_Stack *tasks_stack;

/* Global variable, counter of the total num of tasks in the general tasks list */
int Total_Tasks;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize();

/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien);

/**
 * @brief Insert task in the general task list
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid, int difficulty);

/**
 * @brief Distribute tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks();

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param difficulty The task's difficuly
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int difficulty);

/**
 * @brief Eject Player
 * 
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid);

/**
 * @brief Witness Eject Player
 *
 * @param pid_a The alien's pid
 * 
 * @param pid The crewmate's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid, int pid_a, int number_of_witnesses);

/**
 * @brief Sabbotage
 *
 * @param pid The player's id
 *
 * @param number_of_tasks The number of tasks to be popped
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabbotage(int pid, int number_of_tasks);

/**
 * @brief Vote
 *
 * @param pid The player's id
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid, int vote_evidence);

/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work();

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int Terminate();

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players();

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks();

/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack();

/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list();

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void);

/**
* Frees all memory allocated for the players & their task lists.
*/
void freePlayersAndTasks();

/**
* Frees all memory allocated for the general task list.
*/
void freeGenTasks();

/**
* Frees all memory allocated for the completed tasks stack.
*/
void freeCompletedTasks();

/**
* Finds the player with the least tasks and returns him.
*/
Players* findMinPlayer();

/**
* Finds the player with the highest number of tasks and returns him.
*/
Players* findMaxTasksPlayer();

/**
* Finds the player with the highest number of evidence and returns him.
*/
Players* findMaxEvidencePlayer();

/**
* Calculates and returns the length of a given task list pointed to by the head of the list.
* @param The head of the task list
* @param sentinel The sentinel of the task list
*/
int getTaskListLength(Tasks* head, Tasks* sentinel);

/*
* Merges the given task lists into one without breaking the sorting order.
* @param l1 The first sorted tasks list
* @param l2 The second sorted tasks list
* @return The new merged sorted task list
*/
Tasks* mergeSortedTaskLists(Tasks* l1, Tasks*l2);

/**
* Prints every player's pid along with his tasks.
*/
void printPlayerAndTasks();

/**
* Prints every player and his evidence along with his task list.
*/
void printDLLWithEvidenceAndTask();

/**
* Ejects the player with the given pid.
* @param pid The pid of the player to eject
* @return 1 if successful, 0 otherwise
*/
int eject(int pid);

// Sorted Singly Linked List Function Declarations(General Tasks List)

/**
 * @brief Checks if the General Tasks List is empty.
 * @return True if empty, false otherwise.
 */
bool isGenTaskListEmpty();

/**
 * Inserts a new Task with the passed parameters to the sorted General Tasks List without
 * breaking the sorting order.
 * @param pid The new task's tid
 * @param difficulty The new task's difficulty
 * @return 1 if successful, 0 otherwise
 */
int sortedInsertGenTaskList(int tid,int difficulty);

/**
 * Prints the tasks present in the General Tasks List.
 * @return 1 if successful, 0 if the list is empty.
 */
int printGenTasksList();

// End of Sorted Singly Linked List Function Declarations(General Tasks List)

// Sorted Singly Linked List w/ Sentinel Function Declarations(Tasks List)

/**
 *  Checks if a given tasks list is empty.
 * @param head The head of the given tasks list
 * @return True if it's empty or false otherwise.
 */ 
bool isTaskListEmpty(Tasks* head);

/**
 * Inserts a new task in the given tasks list with the passed attributes without 
 * breaking the sorting.
 * @param player The player whose tasks list will be used to insert new tasks
 * @param tid The new task's tid
 * @param difficulty The new task's difficulty
 * @return 1 if successful or 0 otherwise
 */ 
int sortedInsertTaskList(Players* player, int tid, int difficulty);

/**
 * Removes the given task from the player's tasks list.
 * @param player The player whose task list to traverse
 * @param task The task to delete
 * @return The deleted task
 */ 
Tasks* tasksDelete(Players* player, Tasks* task);

/**
 * Looks for a task in the player's list with a difficulty equal
 * to the passed value.
 * @param player The player whose task list the method will search
 * @param difficulty The difficulty of the task to look for
 * @return A task with the desired difficulty from the player's task list
 */ 
Tasks* taskLookup(Players* player, int difficulty);

/**
 * Prints the tasks of the given player's tasks list.
 * @param The player whose list to print
 * @return 1 if successful, 0 otherwise
 */ 
int printTasksList(Players* player);

// End of Sorted Singly Linked List w/ Sentinel Function Declarations(Tasks List)

// Beginning of Stack function declarations (Completed Tasks)

/**
 *  Checks if the completed tasks stack is empty.
 * @return True if it is empty, false otherwise
 */
bool isEmptyStack();

/**
 * Adds a new completed task to the completed tasks stack.
 * @param task The new finished task
 */ 
void push(Tasks* task);

/**
 * Removes the top task from the completed tasks stack.
 * @return The removed task
 */
Tasks* pop();

/**
 * @return The top task of the stack
 */ 
Tasks* top();

/**
 *  Prints the finished tasks from the completed tasks stack.
 * @return 1 if successful, 0 otherwise
 */ 
int printStack();

// End of Stack function declarations (completed tasks)

// Beginning of Circular Doubly Linked List w/ Sentinel (player list)

/**
 *  Checks if the players list is empty.
 * @return True if empty, false otherwise
 */ 
bool isDLLEmpty();

/**
 *  Inserts a new player to the players list with the
 * passed values.
 * @param pid The new player's pid
 * @param isAlien The new player's isAlien
 * @return 1 if successfull, 0 otherwise
 */ 
int dllInsert(int pid, int isAlien);

/**
 * Removes the player with the passed pid from the players list.
 * @param pid The pid of the player to remove
 * @return The deleted player
 */ 
Players* dllDelete(int pid);

/**
 * Searches for the player with the given pid and
 * returns him.
 * @param pid The pid of the player to look for
 * @return The player with the given pid
 */ 
Players* dllLookUp(int pid);

/**
 * Prints the players of the players list
 * @return 1 if successful, 0 if the list was empty.
 */ 
int printDLL();

/**
 * Prints the players of the players list
 * in reverse order.
 * @return 1 if successful, 0 if the list was empty.
 */ 
int printDLLReverse();

// End of Circular Doubly Linked list w/ Sentinel (player list)

#endif /* __AMONG_US_H_ */
