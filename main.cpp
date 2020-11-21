using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <math.h>
#include "among_us.h"

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
    // players list init
    players_head = new Players;
    players_head->evidence = -1;
    players_head->is_alien = -1;
    players_head->pid = -1;
    players_head->next = NULL;
    players_head->prev = NULL;
    players_head->tasks_head = new Tasks;
	players_head->tasks_head->tid = -1;
	players_head->tasks_head->difficulty = -1;
    players_head->tasks_sentinel = new Tasks;
	players_head->tasks_sentinel->tid = -1;
	players_head->tasks_sentinel->difficulty = -1;

    // General Tasks List init
    tasks_head = new Head_GL;
    tasks_head->tasks_count[0] = 0;
    tasks_head->tasks_count[1] = 0;
    tasks_head->tasks_count[2] = 0;
    tasks_head->head = new Tasks;
	tasks_head->head->tid = -1;
	tasks_head->head->difficulty = -1;
	tasks_head->head->next = NULL;

    // Completed Tasks stack init
    tasks_stack = new Head_Completed_Task_Stack;
    tasks_stack->count = 0;
    tasks_stack->head = new Tasks;
	tasks_stack->head->tid = -1;
	tasks_stack->head->difficulty = -1;
	tasks_stack->head->next = NULL;

	Total_Tasks = 0;

	if (players_head == NULL || tasks_head == NULL || tasks_stack == NULL) return 0; // mem allocation failed

    return 1;
}

/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid,int is_alien) {
	if(dllInsert(pid, is_alien) == 0) return 0; // insertion failed
	cout << "P " << pid << " " << is_alien << endl;
	printDLL();
	cout << "DONE" << endl;
	return 1;
}

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
int insert_task(int tid,int difficulty) {
	if(sortedInsertGenTaskList(tid, difficulty) == 0) return 0; // insertion failed

	cout << "T " << tid << " " << difficulty << endl << "Tasks=";
	printGenTasksList();
	cout << "DONE"<<endl;
	return 1;
}

/**
 * @brief Distribute tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() { // O(m) : m is the total number of tasks to distribute
    if(isDLLEmpty() || isGenTaskListEmpty()) return 0;

    int tasksToAssign;
    Players* player = players_head->next; // start with the 1st player
    Tasks* task = tasks_head->head->next; // start with the 1st task

    // There's only one player and he's an impostor so exit
    if(player->is_alien == 1 && player->next == NULL) return 0;

	// round robin algo
    for(tasksToAssign = Total_Tasks; tasksToAssign > 0; tasksToAssign--) {
        if(player->is_alien == 1 || player == players_head) {
            tasksToAssign++;
            player = player->next; // go to the next player
            continue; // skip impostors and head
        }

        sortedInsertTaskList(player,task->tid,task->difficulty);
		
        player = player->next; // go to the next player
        task = task->next; // go to the next task to assign
    }

	// print output
	cout << "D" << endl;
	printPlayerAndTasks();
	cout << "DONE" << endl;
    return 1;
}

void printPlayerAndTasks() { 
	Players* player = players_head->next;
	while (player != players_head) {
		cout << "Player_" << player->pid << "=";
		printTasksList(player);
		player = player->next;
	}
}

void printDLLWithEvidenceAndTask() {
	Players* player = players_head->next;
	while (player != players_head) {
		cout << "Player_" << player->pid << "," << player->evidence << "> = ";
		printTasksList(player);
		player = player->next;
	}
}

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
int implement_task(int pid, int difficulty) {
	Players* playerImplementing = dllLookUp(pid);
	if (playerImplementing == NULL) return 0; // player not found

	Tasks* taskToImplement = taskLookup(playerImplementing,difficulty);
	if(taskToImplement == NULL) return 0; // no task found

	tasksDelete(playerImplementing,taskToImplement);

	cout << "I " << pid << " " << difficulty << endl;
	printPlayerAndTasks();
	cout << "DONE" << endl;
    return 1;
}

/**
 * @brief Eject Player
 * 
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid) {
	if(eject(pid) == 0) return 0;

	cout << "E " << pid << endl;
	printPlayerAndTasks();
	cout << "DONE" << endl;

    return 1;
}

int eject(int pid) {
	Players* playerToEject = dllLookUp(pid);
	if (playerToEject == NULL) return 0; // not found

	// make the last task's next pointer, point to NULL to prepare the list for merging
	Tasks* ejPlayerTask = playerToEject->tasks_head->next;
	while (ejPlayerTask->next != playerToEject->tasks_sentinel) ejPlayerTask = ejPlayerTask->next;
	ejPlayerTask->next = NULL;

	// retain access to the player's tasks even after he gets removed
	Tasks* ejectedPlayerTasksHead = playerToEject->tasks_head;

	dllDelete(pid); // remove player from the list
	delete(playerToEject); // free removed player's memory

	// find the player with the minimum number of tasks
	Players* minPlayer = findMinPlayer();
	if (minPlayer == NULL) return 0; // not found, list is empty

	// make the last task's next pointer, point to NULL to prepare the list for merging
	Tasks* current = minPlayer->tasks_head->next;
	while (current->next != minPlayer->tasks_sentinel) current = current->next;
	current->next = NULL;
	minPlayer->tasks_sentinel->next = NULL; // update sentinel

	// give the minPlayer the new merged task list
	minPlayer->tasks_head->next = mergeSortedTaskLists(minPlayer->tasks_head->next, ejectedPlayerTasksHead->next);

	// update the min player's new task list sentinel
	Tasks* currentNewList = minPlayer->tasks_head->next;
	while (currentNewList->next != NULL) currentNewList = currentNewList->next;

	// connect the sentinel & the last task
	currentNewList->next = minPlayer->tasks_sentinel;
	minPlayer->tasks_sentinel->next = currentNewList;

	return 1;
}

Players* findMinPlayer() {
	if (isDLLEmpty()) return NULL;
	Players* curPlayer = players_head->next;
	Players* minPlayer = NULL; // pointer to the min player
	int minNumOfTasks = 100000000; // track the min player's num of tasks (initialize with a high number so that the minPlayer can be found at least in the first iteration)
	int curNumOfTasks = 0; // track each player's num of tasks

	while (curPlayer != players_head) {

		if (curPlayer->is_alien == 1) { // skip impostors
			curPlayer = curPlayer->next;
			continue;
		}

		Tasks* currentT = curPlayer->tasks_head->next;
		while (currentT != curPlayer->tasks_sentinel) {
			currentT = currentT->next;
			curNumOfTasks++;
		}

		// Check if the current player has less tasks than the previous minPlayer
		if (curNumOfTasks < minNumOfTasks) {
			minNumOfTasks = curNumOfTasks;
			minPlayer = curPlayer;
			if (minNumOfTasks == 0) break; // if a player has been found without any tasks, break from the loop and return him. No point in looking further
		}

		curPlayer = curPlayer->next;
		curNumOfTasks = 0;
	}

	return minPlayer;
}

Tasks* mergeSortedTaskLists(Tasks* head1, Tasks* head2) { // Time Complexity O(N+m)
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;

	if (head1->difficulty <= head2->difficulty) {
		head1->next = mergeSortedTaskLists(head1->next, head2);
		return head1;
	}
	else {
		head2->next = mergeSortedTaskLists(head1, head2->next);
		return head2;
	}
}

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
int witness_eject(int pid, int pid_a, int number_of_witnesses){
	if(eject(pid) == 0) return 0; // player to eject doesn't exist
	Players* impostor = dllLookUp(pid_a); // find the alien who ejected the player
	if (impostor == NULL) return 0; // impostor not found
	impostor->evidence = impostor->evidence + number_of_witnesses; // update evidence

	// print output
	cout << endl << "W " << pid << " " << pid_a << " " << number_of_witnesses << endl;
	printDLLWithEvidenceAndTask();
	cout << "DONE" << endl;
    return 1;
}

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
int sabbotage(int pid, int number_of_tasks) {
	Players* player = dllLookUp(pid); // find the player

	// Sabotage fails
	if (player == NULL || isEmptyStack()) return 0;

	int firstAssigneePos = floor(number_of_tasks / 2); // the position of the player that will be assigned the first task

	// go to the player at the firstAssigneePos
	int i;
	for (i = 0; i < firstAssigneePos; i++) {
		player = player->prev;
	}

	// distribute tasks
	for (; number_of_tasks > 0; number_of_tasks--) {
		if (player->is_alien == 0) {
			Tasks* taskToDistribute = pop(); // remove a completed task from the stack
			sortedInsertTaskList(player, taskToDistribute->tid, taskToDistribute->difficulty);
			delete(taskToDistribute); // free memory
			if (isEmptyStack()) return 1; // no more tasks left in the stack
		}
		else { // player is an impostor
			number_of_tasks++; // make the loop run "again" since this iteration didn't find a player to distribute tasks to
		}
		player = player->next;
	}

	// print output
	cout << "S " << number_of_tasks << " " << pid << endl;
	printPlayerAndTasks();
	cout << "DONE" << endl;
    return 1;
}


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
int vote(int pid, int vote_evidence) {
	Players* suspect = dllLookUp(pid);
	if (suspect == NULL || isDLLEmpty()) return 0; // not found or list is empty

	suspect->evidence += vote_evidence; // increase evidence
	eject(findMaxEvidencePlayer()->pid); // eject the player with the highest number of evidence against him

	// print output
	cout << "V " << pid << " " << vote_evidence << endl;
	printDLLWithEvidenceAndTask();
	cout << "DONE" << endl;
    return 1;
}

Players* findMaxTasksPlayer() {
	if (isDLLEmpty()) return NULL;
	Players* curPlayer = players_head->next;
	Players* maxPlayer = NULL; // pointer to the player with the max number of tasks
	int maxNumOfTasks = -1; // track the max player's num of tasks (initialize with a low number so that the maxPlayer can be found at least in the first iteration)
	int curNumOfTasks = 0; // track each player's num of tasks

	while (curPlayer != players_head) {

		if (curPlayer->is_alien == 1) { // skip impostors
			curPlayer = curPlayer->next;
			continue;
		}

		Tasks* currentT = curPlayer->tasks_head->next;
		while (currentT != curPlayer->tasks_sentinel) {
			currentT = currentT->next;
			curNumOfTasks++;
		}

		// Check if the current player has less tasks than the previous minPlayer
		if (curNumOfTasks > maxNumOfTasks) {
			maxNumOfTasks = curNumOfTasks;
			maxPlayer = curPlayer;
		}

		curPlayer = curPlayer->next;
		curNumOfTasks = 0;
	}

	return maxPlayer;
}

Players* findMaxEvidencePlayer() {
	if (isDLLEmpty()) return NULL;
	Players* current = players_head->next;
	Players* maxEvPlayer = current;
	int maxEvidence = current->evidence;

	while (current != players_head) {
		if (current->evidence > maxEvidence) {
			maxEvPlayer = current;
			maxEvidence = current->evidence;
		}
		current = current->next;
	}

	return maxEvPlayer;
}

int getTaskListLength(Tasks* head, Tasks* sentinel) {
	Tasks* current = head->next;
	int length = 0;

	while(current != sentinel) {
		length++;
		current = current->next;
	}

	return length;
}

/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work() {
	if (isDLLEmpty()) return 0;
	Players* minPlayer = findMinPlayer();
	Players* maxPlayer = findMaxTasksPlayer();

	// Calculate the number of tasks to transfer from the min to the max player
	int tasksToGive = floor(getTaskListLength(maxPlayer->tasks_head, maxPlayer->tasks_sentinel) / 2);

	if (tasksToGive == 0) return 0; // max player either has 0 tasks or 1 task which cannot be given to the min player

	// give tasks
	for (; tasksToGive > 0; tasksToGive--) {
		Tasks* task = maxPlayer->tasks_head->next;
		sortedInsertTaskList(minPlayer, task->tid, task->difficulty);
		tasksDelete(maxPlayer, task);
	}

	// print output
	cout << "G" << endl;
	printPlayerAndTasks();
	cout << "DONE" << endl;

    return 1;
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int Terminate() {
	if (isDLLEmpty()) return 0;
	int crewmates = 0, impostors = 0;

	cout << "F" << endl;

	// Traverse the players list and count impostors and crewmates
	Players* current = players_head->next;
	while (current != players_head) {
		current->is_alien == 1 ? impostors++ : crewmates++; // use a ternary operator for counting
		current = current->next;
	}

	// Check who won the game
	if (impostors > crewmates) cout << "Aliens win." << endl; 
	else if (impostors == 0 || tasks_stack->count == Total_Tasks) cout << "Crewmates win." << endl; // no impostors left or all tasks have been implemented
	else return 0; // no termination condition has been met

	cout << "DONE" << endl;
    return 1;
}

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
	if (isDLLEmpty()) return 0;
	cout << "X" << endl;
	printDLL();
	cout << "DONE" << endl;
    return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
	if (isGenTaskListEmpty()) return 0;
	cout << "Y" << endl << "List_Tasks=";
	printGenTasksList();
	cout << "DONE" << endl;
    return 1;
}

/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack() {
	if (isEmptyStack()) return 0;

	cout << "Z" << endl << "Stack_Tasks=";
	printStack();
	cout << endl << "DONE"<<endl;
    return 1;
}

/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list() {
	if (isDLLEmpty()) return 0;

	cout << "U" << endl;
	printPlayerAndTasks();
	cout << "DONE" << endl;
    return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void) {
	// Operator delete (used by the following methods) is noexcept since C++11 so it could fail but due to OS issues. Source : https://stackoverflow.com/questions/29475395/c-can-operator-delete-fails-and-if-not-why
	freeCompletedTasks();
	freeGenTasks();
	freePlayersAndTasks();
    return 1;
}

void freePlayersAndTasks() {
	Players* player = players_head->next;
	Players* tempPlayer = NULL;
	Tasks* tempTask = NULL;

	while (player != players_head) {
		Tasks* task = player->tasks_head->next;
		tempPlayer = player->next;
		while (task != player->tasks_sentinel) {
			tempTask = task->next;
			delete(task);
			task = tempTask;
		}
		delete(player->tasks_head);
		delete(player->tasks_sentinel);
		delete(player);
		player = tempPlayer;
	}

	delete(players_head);
}

void freeGenTasks() {
	Tasks* task = tasks_head->head->next;
	Tasks* temp = NULL;
	
	while (task != NULL) {
		temp = task->next;
		delete(task);
		task = temp;
	}

	delete(temp);
	delete(task);
	delete(tasks_head->head);
	delete(tasks_head);
}

void freeCompletedTasks() {
	Tasks* task = tasks_stack->head->next;
	Tasks* temp = NULL;
	while (task != NULL) {
		temp = task->next;
		delete(task);
		task = temp;
	}
	delete(temp);
	delete(task);
	delete(tasks_stack->head);
	delete(tasks_stack);
}

// Beginning of General Tasks list implementation (Sorted singly linked list)

bool isGenTaskListEmpty() {
    return (tasks_head->head == NULL);
}

int sortedInsertGenTaskList(int tid, int difficulty) {
    // increment the list's difficulty counter
    if (difficulty == 1) tasks_head->tasks_count[0]++;
    else if (difficulty == 2) tasks_head->tasks_count[1]++;
    else tasks_head->tasks_count[2]++;

    Total_Tasks++; // increment the num of total tasks

    Tasks *node = new Tasks;
    if(node == NULL) return 0; // not enough memory exit

    // add data to the new node
    node->tid = tid;
    node->difficulty = difficulty;
    node->next = NULL;

    if(isGenTaskListEmpty()) {
        tasks_head->head = node;
        return 1;
    }

    // insert the new node without breaking the sorting of the list
    Tasks *curr = tasks_head->head;

    while(curr->next != NULL && curr->next->difficulty < difficulty) {
        curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
    return 1;
}

int printGenTasksList() {
	if (isGenTaskListEmpty()) return 0;
	Tasks* curr = tasks_head->head->next;

	do {
        cout << "<" << curr->tid << "," << curr->difficulty << ">";
        curr = curr->next;
    } while (curr != NULL);
	cout << endl;
	return 1;
}

// End of General Tasks list implementation (Sorted singly linked list)

// Beginning of Tasks List implementation (Sorted Singly Linked List w/sentinel)

bool isTaskListEmpty(Tasks* head) {
    return (head->next->tid == -1); // if the head is pointing to the sentinel (tid == -1), then the list is empty
}

int sortedInsertTaskList(Players* player, int tid, int difficulty) {
    Tasks* node = new Tasks; 
	if(node == NULL) return 0; // not enough memory

    // add data to the new node
    node->tid = tid;
    node->difficulty = difficulty;
    node->next = NULL;

    if (isTaskListEmpty(player->tasks_head)) { // if the list is empty, make the head and sentinel point to the new node
		player->tasks_head->next = node;
		player->tasks_sentinel->next = node;
		node->next = player->tasks_sentinel;
        return 1;
    }

    // check if the new node can be added to the end of the list
    if (player->tasks_sentinel->next->difficulty <= difficulty) {
		player->tasks_sentinel->next->next = node; // place new node at the end of the list
		player->tasks_sentinel->next = node; // update sentinel
		node->next = player->tasks_sentinel;
        return 1;
    }

    // insert the new node without breaking the sorting of the list
    Tasks* curr = player->tasks_head;

    while (curr->next->difficulty < difficulty) { 
        curr = curr->next;
    }

    node->next = curr->next;
    curr->next = node;
	return 1;
}

Tasks* tasksDelete(Players* player, Tasks* task) {
	Tasks* current = player->tasks_head->next; 
	Tasks* prev = player->tasks_head;

	while(current != task && current != player->tasks_sentinel) {
		prev = current; // update prev
		current = current->next; // update current
	}

	if (current != task) return NULL; // task not found

	if (current == player->tasks_sentinel->next) { // task for deletion is the last one
		player->tasks_sentinel->next = prev;// update sentinel
	}

	// remove the desired task from the list by updating the prev node's next field
	prev->next = current->next;

	// when we delete a task, it gets implemented by adding it to the stack
	push(current);

	return current;
}

Tasks* taskLookup(Players* player, int difficulty) {
	if(isTaskListEmpty(player->tasks_head) == true) return NULL;

	if(player->tasks_head->next->difficulty == difficulty) { // return the task at the beginning of the list
		return player->tasks_head->next;
	}

	if(player->tasks_sentinel->next->difficulty == difficulty) { // return the task at the end of the list
		return player->tasks_sentinel->next;
	}

	// find the first task with the desired difficulty and return it
	Tasks* current = player->tasks_head->next->next; // start from the second one since we already checked the first

	while(current != player->tasks_sentinel && current->difficulty != difficulty) {
		current = current->next;
	}

	if(current == player->tasks_sentinel) return NULL; // no task with desired difficulty found
	else return current; // task found
}

int printTasksList(Players* player) {
	if (player->is_alien == 1 || isTaskListEmpty(player->tasks_head)) {
		cout << "<>" << endl;
		return 1;
	}

	Tasks* task = player->tasks_head->next;
	while (task != player->tasks_sentinel) {
		cout << "<" << task->tid << "," << task->difficulty << ">";
		task = task->next;

		// used for formatting the output
		if (task == player->tasks_sentinel) { // prev task was the last one in the list
			cout << endl;
			break;
		}
		else cout << ",";
	}

	return 1;
}

// End of Tasks List implementation (Sorted Singly Linked List w/sentinel)

// Beginning of completed tasks stack implementation

bool isEmptyStack() {
    return (tasks_stack->head->next == NULL);
}

void push(Tasks* elem) {
    // update the size of the stack
    tasks_stack->count = tasks_stack->count++;

    if (isEmptyStack()) {
        elem->next = NULL;
        tasks_stack->head->next = elem;
        return;
    }

    // add element at the top
    elem->next = tasks_stack->head->next;
    tasks_stack->head->next = elem;
}

Tasks* pop() {
    if (isEmptyStack()) return NULL;
    Tasks* topEl = top();
    tasks_stack->head->next = topEl->next; // update stack's head
	tasks_stack->count = tasks_stack->count--; // update the count
	topEl->next = NULL; // remove pointer to the next element of the stack
    return topEl;
}

Tasks* top() {
    return tasks_stack->head->next;
}

int printStack() {
    if (isEmptyStack()) return 0;

    Tasks* curr = tasks_stack->head->next;
    while(curr != NULL) {
        cout << "<" << curr->tid << "," << curr->difficulty << ">";
        curr = curr->next;
    };

	return 1;
}

// End of completed tasks stack implementation

// Beginning of players list implementation (circular doubly linked list w/ Sentinel)

bool isDLLEmpty() {
	return (players_head->next == NULL);
}

int dllInsert(int pid, int isAlien) {
	Players* player = new Players; 
	if(player == NULL) return 0; // not enough memory, exit

	// initializations
    player->pid = pid;
	player->is_alien = isAlien;
	player->evidence = 0;
	player->prev = players_head;
	player->tasks_head = new Tasks;
	player->tasks_head->tid = -1;
	player->tasks_head->difficulty = -1;
	player->tasks_sentinel = new Tasks;
	player->tasks_sentinel->tid = -1;
	player->tasks_sentinel->difficulty = -1;
	player->tasks_head->next = player->tasks_sentinel;
	player->tasks_sentinel->next = player->tasks_head;

	// check if the list is empty
	if (isDLLEmpty()) {
		player->next = players_head;
		players_head->next = player;
		players_head->prev = player;
		return 1;
	}

	// insert the new player at the beginning of the list
	players_head->next->prev = player;
	player->next = players_head->next;
	players_head->next = player;
    return 1;
}

Players* dllDelete(int pid) {
	Players* player = dllLookUp(pid);
	if (player == NULL) return NULL; // player doesn't exist
	Players* prev = player->prev;
	Players* next = player->next;

	// connect the next and prev nodes before deleting the node between them
	prev->next = next;
	next->prev = prev;
	// "delete" the selected node
	player->next = NULL;
	player->prev = NULL;
	return player;
}

Players* dllLookUp(int pid) {
	if (isDLLEmpty()) return NULL;

	// check if the player we're looking for is the first one in the list
	if (players_head->next->pid == pid) return players_head->next;

	// check if the player we're looking for is the last one in the list
	if (players_head->prev->pid == pid) return players_head->prev;

	Players* currPlayer = players_head->next->next; // start from the 2nd element
	while (currPlayer != players_head && currPlayer->pid != pid) {
		currPlayer = currPlayer->next;
	}

	if (currPlayer == players_head) return NULL; // not found
	else return currPlayer;
}

int printDLL() {
	if (isDLLEmpty()) return 0;

	// traverse the list and print player info
	Players* currPlayer = players_head->next; // first player
	cout << "Players=";
	do
	{
		cout << "<" << currPlayer->pid << ":" << currPlayer->is_alien << ">";
		currPlayer = currPlayer->next;
	} while (currPlayer != players_head);
	cout << endl;

	return 1;
}

int printDLLReverse() {
	if (isDLLEmpty()) return 0;

	// traverse the list in reverse order and print player info
	Players* currPlayer = players_head->prev; // first player
	cout << "Players=";
	do
	{
		cout << "<" << currPlayer->pid << ":" << currPlayer->is_alien << ">";
		currPlayer = currPlayer->prev;
	} while (currPlayer != players_head);
	cout << endl;

	return 1;
}

// End of players list implementation (circular doubly linked list w/ Sentinel)

#define BUFFER_SIZE 1024 /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG
#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char **argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event='\0';

	/* Check command buff arguments */
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <input_file> <>\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if ((fin = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin))
	{

		DPRINT("\n>>> Event: %s", buff);

		switch (buff[0])
		{

		/* Comment */
		case '#':
			break;

		/* Register player
			 * P <pid><is_alien> */
		case 'P':
		{
			int pid;
			int is_alien;
			sscanf(buff, "%c %d %d", &event, &pid, &is_alien);
			DPRINT("%c %d %d\n", event, pid, is_alien);

			if (register_player(pid, is_alien))
			{
				DPRINT("P %d %d succeeded\n", pid, is_alien);
			}
			else
			{
				fprintf(stderr, "P %d %d failed\n", pid, is_alien);
			}

			break;
		}

		/* Insert task
			 * T <tid><difficulty>  */
		case 'T':
		{
			int tid, difficulty;

			sscanf(buff, "%c %d %d", &event, &tid, &difficulty);
			DPRINT("%c %d %d\n", event, tid, difficulty);

			if (insert_task(tid, difficulty))
			{
				DPRINT("%c %d %d succeded\n", event, tid, difficulty);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, tid, difficulty);
			}

			break;
		}

		/* Distribute Tasks
			 * D */
		case 'D':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (distribute_tasks())
			{
				cout<<"success";
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				cout << "error";
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Implement Task
			 * I <pid> <difficulty> */
		case 'I':
		{
			int pid,difficulty;

			sscanf(buff, "%c %d %d", &event, &pid,&difficulty);
			DPRINT("%c %d %d \n", event, pid,difficulty);

			if (implement_task(pid,difficulty))
			{
				DPRINT("%c %d %d succeeded\n", event, pid,difficulty);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid,difficulty);
			}

			break;
		}

		/* Eject Player
			 * E <pid>*/
		case 'E':
		{
			int pid;

			sscanf(buff, "%c %d", &event, &pid);
			DPRINT("%c %d\n", event, pid);

			if (eject_player(pid))
			{
				DPRINT("%c %d succeeded\n", event, pid);
			}
			else
			{
				fprintf(stderr, "%c %d failed\n", event, pid);
			}

			break;
		}

			/* Witness Ejection
                 * W <pid> <pid_a> <number_of_witnesses>
                 */
		case 'W':
		{
			int pid ,pid_a ,number_of_witnesses;

			sscanf(buff, "%c %d %d %d", &event, &pid ,&pid_a ,&number_of_witnesses);
			DPRINT("%c %d %d %d\n", event, pid ,pid_a ,number_of_witnesses);

			if (witness_eject(pid ,pid_a ,number_of_witnesses))
			{
				DPRINT("%c %d %d %d succeded\n", event, pid ,pid_a ,number_of_witnesses);
			}
			else
			{
				fprintf(stderr, "%c %d %d %d failed\n", event, pid ,pid_a ,number_of_witnesses);
			}

			break;
		}

		/* Sabbotage
			 * S <number_of_tasks><pid> */
		case 'S':
		{
			int pid,number_of_tasks;

			sscanf(buff, "%c %d %d\n", &event, &number_of_tasks,&pid);
			DPRINT("%c %d %d\n", event, number_of_tasks,pid);

			if (sabbotage(pid,number_of_tasks))
			{
				DPRINT("%c %d %d succeeded\n", event,  number_of_tasks,pid);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event,  number_of_tasks,pid);
			}

			break;
		}

		/* Vote
			 * V <pid> <vote_evidence> */
		case 'V':
		{
			int pid, vote_evidence;

			sscanf(buff, "%c %d %d\n", &event, &pid, &vote_evidence);
			DPRINT("%c %d %d\n", event, pid,vote_evidence);

			if (vote(pid,vote_evidence))
			{
				DPRINT("%c %d %d succeeded\n", event,  pid,vote_evidence);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event,  pid,vote_evidence);
			}

			break;
		}

		/* Give Away Work
			 * G */
		case 'G':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (give_work())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Terminate
			 * F */
		case 'F':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (Terminate())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Print Players
			 * X */
		case 'X':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_players())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Print Tasks
			 * Y */
		case 'Y':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_tasks())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Print Stack
			 * Z */
		case 'Z':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_stack())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Print Players & Tasks list
			 * F */
		case 'U':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_double_list())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Empty line */
		case '\n':
			break;

		/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
