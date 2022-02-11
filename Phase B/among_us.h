/**************************************************
 *                                                *
 * file: among_us.h                               *
 *                                                *
 *                                                *
 * @Author  Skerdi Basha                          *
 * @Version 1-12-2020                             *
 * @email   sbash@csd.uoc.gr                      *
 *                                                *
 * @brief   Header file for the needs of CS-240   *
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
 * Structure defining a node of the players double linked tree
 * tree
 */
struct Player
{
    int pid;                        /*Player's identifier*/
    int is_alien;                   /*Alien flag*/
    int evidence;                   /*Amount of evidence*/
    struct Player *parrent;         /*Pointer to the parent node*/
    struct Player *lc;              /*Pointer to the left child node*/
    struct Player *rc;              /*Pointer to the right child node*/
    struct Task *tasks;             /*Pointer to the head of player's task tree*/
};

/**
 * Structure defining a node of the tasks sorted tree
 */
struct Task
{
    int tid;                        /*Task's identifier*/
    int difficulty;                 /*Task's difficulty*/
    int lcnt;                       /*Node's left child's node counter*/
    struct Task *lc;                /*Pointer to the left child node*/
    struct Task *rc;                /*Pointer to the right child node*/ 
};

struct HT_Task
{
    int tid;                        /*Task's identifier*/
    int difficulty;                 /*Task's difficulty*/
    struct HT_Task *next;           /*Pointer to the next node*/
};

struct General_Tasks_HT
{
    int count;                      /*Count of tasks*/
    struct HT_Task **tasks;         /*General tasks hash table*/
};

struct Completed_Tasks_PQ
{
    int size;                       /*Count of completed tasks*/
    struct HT_Task* tasks;         /*Completed tasks priority queue*/
};

unsigned int max_tasks_g; /* Max number of tasks */
unsigned int max_tid_g;   /* Max task tid */

/* Primes for your universal hashing implementation */
extern unsigned int primes_g[650];

/* Integer variables used to create a set of hash functions using global hashing at the beginning of the program */
extern unsigned int p;
extern unsigned int a;
extern unsigned int b;

/* Global variable, pointer to the head of the players tree */
struct Player *players_tree;

/* Global variable, pointer to the sentinel of the players tree */
struct Player* players_sentinel;

/* Global variable, pointer to the head of the tasks tree */
struct General_Tasks_HT* general_tasks_ht;

/* Global variable, pointer to the top of the completed task's priority queue */
struct Completed_Tasks_PQ* completed_tasks_pq;

/* Beginning of function declarations by Stelios Papamichail csd4020 */

// Player BST declarations
Player* dlBSTInsert(int pid, int is_alien, int evidence);
Player* dlBSTDelete(int pid);
Player* dlBSTGuardLookUp(int pid);
void printDLBSTInOrder(Player* node);
Player* FindInorderSuccessor(Player* node);
Player* FindInorderPredecessor(Player* node);
Player* bstFindMin();
Player* bstFindMax();

// Player Task BST declarations
Task* playerTaskInsert(Task* root, int tid, int difficulty);
Task* playerTaskDelete(Task* root, int tid);
Task* playerTaskLookUp(Task* root, int tid);
void printPlayerTasks(Task* root);
Task* playerTaskSuccessor(Task* root, Task* node);
Task* playerTaskPredecessor(Task* root, Task* node);
Task* playerGetParentTask(Task* root, Task* child);
void updateParentPathLcCount(Task* root, Task* node, bool insertedNode);

// Task HashTable declarations
HT_Task* hashInsert(int tid, int difficulty);
HT_Task* hashLookUp(int tid);
HT_Task* hashDelete(int tid);
int h(int key);
int findPrime();
HT_Task* getParentHTTask(int tid);
void printHT();

// Completed Task Priority Queue declarations
int pqInsert(int tid, int difficulty);
bool isEmptyPQ();
void pqDeleteMax();
void heapify();
HT_Task pqFindMax();
void printPQ();

// Event helper functions
extern int htRow;
void updateChainIfNeeded();
void distributeTasks(Player* player);
void printPlayerAndTasks(Player* node);
Task* sortedListTaskInsert(Task* list, Task* task);
Task* treeToSortedList(Task* node, Task* list);
Task* mergeSortedTaskLists(Task* head1, Task* head2);
Task* sortedListToBST(Task* tree);
int updateBSTLCnt(Task* node);
void printPlayerAndTasksWithEvidence(Player* node);
int eject(int pid_1, int pid_2);
int countCrewmatesOrAliens(Player* node, int cnt, int cntAliens);
void printPlayerEventX(Player* node);
Player* findMostEvidencePlayer(Player* node, Player* maxPlayer);

/* End of function declarations by Stelios Papamichail csd4020 */

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize();

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien);

/**
 * @brief Insert Task in the general task hash table
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
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks();

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param tid The task's tid
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int tid);

/**
 * @brief Eject Player
 * 
 * @param pid_1 The ejected player's id
 *
 * @param pid_2 The crewmates id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid_1, int pid_2);

/**
 * @brief Witness Eject Player
 *
 * @param pid_1 The ejected player's id
 * 
 * @param pid_2 The crewmate's pid
 *
 * @param pid_a The alien's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses);

/**
 * @brief Sabotage
 *
 * @param number_of_tasks The number of tasks to be sabotaged
 *
 * @param pid The player's id
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabotage(int number_of_tasks, int pid);

/**
 * @brief Vote
 *
 * @param pid_1 The suspicious player's id
 *
 * @param pid_2 The crewmate's pid
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid_1, int pid_2, int vote_evidence);

/**
 * @brief Give Away Work
 *
 * @param pid_1 The existing crewmate's id
 *
 * @param pid_2 The new crewmate's pid
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work(int pid_1, int pid_2);

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
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq();

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree();

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void);

#endif /* __AMONG_US_H_ */