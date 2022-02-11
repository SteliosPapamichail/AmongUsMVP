/***************************************************************
 *                                                             *
 * file: main.cpp                                              *
 *                                                             *
 * @Author  Skerdi Basha                         		   	   *
 * @Version 1-12-2020                             			   *
 * @email   sbash@csd.uoc.gr                                   *
 *                                                             *
 * @brief   Main function and implemetantion of among_us.h     *
 *          for the needs of CS-240 project 2020               *
 *                                                             *
 ***************************************************************
 */

#include <stddef.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

#include "among_us.h"

unsigned int primes_g[650] = { 
                                 179,    181,    191,    193,    197,    199,    211,    223,    227,    229, 
                                 233,    239,    241,    251,    257,    263,    269,    271,    277,    281, 
                                 283,    293,    307,    311,    313,    317,    331,    337,    347,    349, 
                                 353,    359,    367,    373,    379,    383,    389,    397,    401,    409, 
                                 419,    421,    431,    433,    439,    443,    449,    457,    461,    463, 
                                 467,    479,    487,    491,    499,    503,    509,    521,    523,    541, 
                                 547,    557,    563,    569,    571,    577,    587,    593,    599,    601, 
                                 607,    613,    617,    619,    631,    641,    643,    647,    653,    659, 
                                 661,    673,    677,    683,    691,    701,    709,    719,    727,    733, 
                                 739,    743,    751,    757,    761,    769,    773,    787,    797,    809, 
                                 811,    821,    823,    827,    829,    839,    853,    857,    859,    863, 
                                 877,    881,    883,    887,    907,    911,    919,    929,    937,    941, 
                                 947,    953,    967,    971,    977,    983,    991,    997,   1009,   1013, 
                                1019,   1021,   1031,   1033,   1039,   1049,   1051,   1061,   1063,   1069, 
                                1087,   1091,   1093,   1097,   1103,   1109,   1117,   1123,   1129,   1151, 
                                1153,   1163,   1171,   1181,   1187,   1193,   1201,   1213,   1217,   1223, 
                                1229,   1231,   1237,   1249,   1259,   1277,   1279,   1283,   1289,   1291, 
                                1297,   1301,   1303,   1307,   1319,   1321,   1327,   1361,   1367,   1373, 
                                1381,   1399,   1409,   1423,   1427,   1429,   1433,   1439,   1447,   1451, 
                                1453,   1459,   1471,   1481,   1483,   1487,   1489,   1493,   1499,   1511, 
                                1523,   1531,   1543,   1549,   1553,   1559,   1567,   1571,   1579,   1583, 
                                1597,   1601,   1607,   1609,   1613,   1619,   1621,   1627,   1637,   1657, 
                                1663,   1667,   1669,   1693,   1697,   1699,   1709,   1721,   1723,   1733, 
                                1741,   1747,   1753,   1759,   1777,   1783,   1787,   1789,   1801,   1811, 
                                1823,   1831,   1847,   1861,   1867,   1871,   1873,   1877,   1879,   1889, 
                                1901,   1907,   1913,   1931,   1933,   1949,   1951,   1973,   1979,   1987, 
                                1993,   1997,   1999,   2003,   2011,   2017,   2027,   2029,   2039,   2053, 
                                2063,   2069,   2081,   2083,   2087,   2089,   2099,   2111,   2113,   2129, 
                                2131,   2137,   2141,   2143,   2153,   2161,   2179,   2203,   2207,   2213, 
                                2221,   2237,   2239,   2243,   2251,   2267,   2269,   2273,   2281,   2287, 
                                2293,   2297,   2309,   2311,   2333,   2339,   2341,   2347,   2351,   2357, 
                                2371,   2377,   2381,   2383,   2389,   2393,   2399,   2411,   2417,   2423, 
                                2437,   2441,   2447,   2459,   2467,   2473,   2477,   2503,   2521,   2531, 
                                2539,   2543,   2549,   2551,   2557,   2579,   2591,   2593,   2609,   2617, 
                                2621,   2633,   2647,   2657,   2659,   2663,   2671,   2677,   2683,   2687, 
                                2689,   2693,   2699,   2707,   2711,   2713,   2719,   2729,   2731,   2741, 
                                2749,   2753,   2767,   2777,   2789,   2791,   2797,   2801,   2803,   2819, 
                                2833,   2837,   2843,   2851,   2857,   2861,   2879,   2887,   2897,   2903, 
                                2909,   2917,   2927,   2939,   2953,   2957,   2963,   2969,   2971,   2999, 
                                3001,   3011,   3019,   3023,   3037,   3041,   3049,   3061,   3067,   3079, 
                                3083,   3089,   3109,   3119,   3121,   3137,   3163,   3167,   3169,   3181, 
                                3187,   3191,   3203,   3209,   3217,   3221,   3229,   3251,   3253,   3257, 
                                3259,   3271,   3299,   3301,   3307,   3313,   3319,   3323,   3329,   3331, 
                                3343,   3347,   3359,   3361,   3371,   3373,   3389,   3391,   3407,   3413, 
                                3433,   3449,   3457,   3461,   3463,   3467,   3469,   3491,   3499,   3511, 
                                3517,   3527,   3529,   3533,   3539,   3541,   3547,   3557,   3559,   3571, 
                                3581,   3583,   3593,   3607,   3613,   3617,   3623,   3631,   3637,   3643, 
                                3659,   3671,   3673,   3677,   3691,   3697,   3701,   3709,   3719,   3727, 
                                3733,   3739,   3761,   3767,   3769,   3779,   3793,   3797,   3803,   3821, 
                                3823,   3833,   3847,   3851,   3853,   3863,   3877,   3881,   3889,   3907, 
                                3911,   3917,   3919,   3923,   3929,   3931,   3943,   3947,   3967,   3989, 
                                4001,   4003,   4007,   4013,   4019,   4021,   4027,   4049,   4051,   4057, 
                                4073,   4079,   4091,   4093,   4099,   4111,   4127,   4129,   4133,   4139, 
                                4153,   4157,   4159,   4177,   4201,   4211,   4217,   4219,   4229,   4231, 
                                4241,   4243,   4253,   4259,   4261,   4271,   4273,   4283,   4289,   4297, 
                                4327,   4337,   4339,   4349,   4357,   4363,   4373,   4391,   4397,   4409, 
                                4421,   4423,   4441,   4447,   4451,   4457,   4463,   4481,   4483,   4493, 
                                4507,   4513,   4517,   4519,   4523,   4547,   4549,   4561,   4567,   4583, 
                                4591,   4597,   4603,   4621,   4637,   4639,   4643,   4649,   4651,   4657, 
                                4663,   4673,   4679,   4691,   4703,   4721,   4723,   4729,   4733,   4751, 
                                4759,   4783,   4787,   4789,   4793,   4799,   4801,   4813,   4817,   4831, 
                                4861,   4871,   4877,   4889,   4903,   4909,   4919,   4931,   4933,   4937, 
                                4943,   4951,   4957,   4967,   4969,   4973,   4987,   4993,   4999,   5003, 
                                5009,   5011,   5021,   5023,   5039,   5051,   5059,   5077,   5081,   5087, 
                                5099,   5101,   5107,   5113,   5119,   5147,   5153,   5167,   5171,   5179, 
                            };

unsigned int p;
unsigned int a;
unsigned int b;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
	// Players tree & sentinel node initializations
	players_sentinel = new Player;
	if (players_sentinel == NULL) return 0; // mem alloc failed
	players_sentinel->evidence = -1;
	players_sentinel->is_alien = -1;
	players_sentinel->pid = -1;
	players_sentinel->parrent = NULL;
	players_sentinel->lc = NULL;
	players_sentinel->rc = NULL;
	players_sentinel->tasks = NULL;
	players_tree = new Player;
	if (players_tree == NULL) return 0; // mem alloc failed
	players_tree->pid = -1;
	players_tree->evidence = -1;
	players_tree->is_alien = -1;
	players_tree->parrent = NULL;
	players_tree->tasks = new Task;
	if (players_tree->tasks == NULL) return 0; // mem alloc failed
	players_tree->tasks->tid = -1;
	players_tree->tasks->difficulty = -1;
	players_tree->tasks->lc = NULL;
	players_tree->tasks->rc = NULL;
	players_tree->tasks->lcnt = 0;
	players_tree->lc = players_sentinel;
	players_tree->rc = players_sentinel;
	
	// Hash related initializations
	// The max_tasks_g & max_tid_g fields will be initialized by main at first
	p = findPrime();
	// calculate a & b randomly. val will belong in [0...p-1]
	srand(time(0)); // initialize random number generator
	a = rand() % p;
	b = rand() % p;
	general_tasks_ht = new General_Tasks_HT;
	if (general_tasks_ht == NULL) return 0; // mem alloc failed
	general_tasks_ht->count = 0;
	general_tasks_ht->tasks = new HT_Task*[max_tasks_g];
	if (general_tasks_ht->tasks == NULL) return 0; // mem alloc failed
	unsigned int i;
	for (i = 0; i < max_tasks_g; i++) {
		general_tasks_ht->tasks[i] = NULL;
	}

	// Priority queue initializations
	completed_tasks_pq = new Completed_Tasks_PQ;
	if (completed_tasks_pq == NULL) return 0; // mem alloc failed
	completed_tasks_pq->size = 0;
	completed_tasks_pq->tasks = new HT_Task;
	if (completed_tasks_pq->tasks == NULL) return 0; // mem alloc failed
    return 1;
}

/**
 * @brief Register Player
 *
 * @param pid The player's id
 * @see cref="www.google.com"
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien) {
	players_tree = dlBSTInsert(pid,is_alien,0);
	cout << "Players=";
	printDLBSTInOrder(players_tree);
	cout << endl <<  "DONE" << endl;
    return 1;
}

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
int insert_task(int tid, int difficulty) {
	hashInsert(tid, difficulty);
	printHT();
	cout << "DONE" << endl;
    return 1;
}

HT_Task* chain;
int htRow;

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() { // O(n) : n=numOfTasks

	if (general_tasks_ht->count > 0) {
		htRow = 0;
		chain = general_tasks_ht->tasks[0];
		distributeTasks(players_tree);
		printPlayerAndTasks(players_tree);
		cout << "DONE" << endl;
		return 1;
	}
	else {
		return 0;
	}
}

/**
* @brief Helper function for D event which iterates over the hash table's rows (chains) when needed.
*/
void updateChainIfNeeded() {
	while (chain == NULL && htRow < (max_tasks_g-1)) { // current chain has no tasks but there are more to distribute
		htRow++;
		chain = general_tasks_ht->tasks[htRow]; // go to the next chain
	}
}

/**
* @brief Recursively distributes all the tasks from the HT to the players based on In Order traversal.
* @param player The current node to traverse in order.
*/
void distributeTasks(Player* player) {

	if (player->lc != players_sentinel) { // has LC
		distributeTasks(player->lc);
	}

	if (!player->is_alien) { // give task if the player isn't an alien
		updateChainIfNeeded();
		if (chain == NULL) return;
		player->tasks = playerTaskInsert(player->tasks, chain->tid, chain->difficulty); // give the first task of the chain
		//chain = hashDelete(chain->tid); // delete the first task
		chain = chain->next;
	}

	if (player->rc != players_sentinel) { // has RC
		distributeTasks(player->rc);
	}

	if (player == bstFindMax()) { // if we are at the right most player, we want to start traversing the tree again from the top
		distributeTasks(players_tree);
	}
}

// Prints players and their task tree
void printPlayerAndTasks(Player* node) {
	if (node == players_sentinel) return;
	printPlayerAndTasks(node->lc);
	cout << "Player" << node->pid << " = ";
	printPlayerTasks(node->tasks);
	cout << endl;
	printPlayerAndTasks(node->rc);
	return;
}

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
int implement_task(int pid, int tid) {
	Player* player = dlBSTGuardLookUp(pid);
	if (player == NULL) return 0; // player not found

	Task* taskToDel = playerTaskLookUp(player->tasks, tid);
	if (taskToDel == NULL) return 0; // task not found

	player->tasks = playerTaskDelete(player->tasks, tid); // task found, remove it and update the task list (also adds the task to the pq)
	
	Task* implementedTask = playerTaskLookUp(player->tasks, tid); // check if the task was implemented
	if (implementedTask != NULL) return 0; // task was not implemented (pq was full)

	printPlayerAndTasks(players_tree);
	cout << "DONE" << endl;
    return 1;
}

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
int eject_player(int pid_1, int pid_2) {
	int ejectionRes = eject(pid_1, pid_2);
	if (ejectionRes == 0) return 0;

	printPlayerAndTasks(players_tree);
	cout << "DONE" << endl;
    return 1;
}

/**
* @brief Recursively updates the lcnt field of the necessary nodes
* of the given BST.
* @param node The tree whose nodes' lcnt field could be updated
*/
int updateBSTLCnt(Task* node) {
	node->lcnt = 0;

	if (node->lc != NULL) { // has left child/subtree
		node->lcnt += 1 + updateBSTLCnt(node->lc);
	}

	if (node->rc != NULL) { // has right child/subtree
		updateBSTLCnt(node->rc);
	}

	return node->lcnt;
}

/**
* @brief Recursively converts the given sorted linked list into a
* BST with a height of logN.
* @param head The head of the sorted linked list
* @return The BST with a height of logN and all the tasks of the given list
* sorted based in In order traversal.
*/
Task* sortedListToBST(Task* head) { // O(n)
	// base case
	if (head == NULL) return NULL;
	else if (head->rc == NULL) return head; // only one node

	// use floyd's hair and tortoise approach to find the middle node of the list
	// src: https://en.wikipedia.org/wiki/Cycle_detection#Floyd.27s_Tortoise_and_Hare
	Task* slow = head; // tortoise : moves one index each time
	Task* fast = head; // hair : moves two indices each time

	// move pointers accross the list
	while (fast->rc != NULL) {
		slow = slow->rc;
		fast = fast->rc;
		if (fast->rc != NULL) fast = fast->rc; // if there is another element, the fast pointer should move to it
	}

	// get the node that's before the slow/middle node
	Task* tmp = head;
	while (tmp->rc != slow) {
		tmp = tmp->rc;
	}

	// cut out the part of the list that starts with the middle node
	tmp->rc = NULL;

	// make the middle(slow ptr) node the root
	Task* root = new Task;
	root->tid = slow->tid;
	root->difficulty = slow->difficulty;
	root->lc = NULL;
	root->rc = NULL;
	root->lcnt = 0;

	// keep track of the right part of the list (after the middle node)
	Task* rightPart = slow->rc;
	// cut out the middle node from the right part of the list
	slow->rc = NULL;
	
	// create the left subtree of the root recursively
	root->lc = sortedListToBST(head);
	
	// create the right subtree of the root recursively
	root->rc = sortedListToBST(rightPart);

	return root;
}

/**
* @brief Inserts a task in the given sorted linked list
* without breaking the sort order. IMPORTANT: The rc pointer
* is used to traverse through the list since the given list will be
* a sorted linked list produced from a sorted BST.
* @param list The task list in which the task will be added
* @param task The task to add to the given list
* @return The list with the newly added task
*/
Task* sortedListTaskInsert(Task* list, Task* task) {
	Task* node = new Task;
	if (node == NULL) return list; // mem alloc failed

	if (list == NULL) { // empty list
		node->tid = task->tid;
		node->difficulty = task->difficulty;
		node->lc = NULL;
		node->rc = NULL;
		node->lcnt = 0;
		return node;
	}

	// insert the new node without breaking the sorting of the list
	Task* curr = list;

	while (curr->rc != NULL && curr->rc->tid < task->tid) {
		curr = curr->rc;
	}

	node->tid = task->tid;
	node->difficulty = task->difficulty;
	node->lcnt = 0;
	node->lc = NULL;
	node->rc = curr->rc;
	curr->rc = node;

	return list;
}

/**
* @brief Recursively converts the given sorted BST into a sorted linked list
* using In order traversal.
* @param node The tree/subtree whose nodes to add to the list
* @param list The sorted linked list in which to add the BST's tasks
* @return The final sorted linked list with all the nodes of the initial BST.
*/
Task* treeToSortedList(Task* node, Task* list) { // O(n) : n num of elements of the tree

	if (node->lc != NULL) { // has lc
		list = treeToSortedList(node->lc, list);
	}

	// add task to list
	list = sortedListTaskInsert(list, node);

	if (node->rc != NULL) { // has rc
		list = treeToSortedList(node->rc, list);
	}

	return list;
}

/**
* @brief Merges the two given sorted linked lists into one
* sorted linked list using recursion.
* @param head1 The head of the first list
* @param head2 The head of the second list
* @return The final sorted linked list
*/
Task* mergeSortedTaskLists(Task* head1, Task* head2) { // Time Complexity O(N+m)
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;

	if (head1->tid <= head2->tid) {
		head1->rc = mergeSortedTaskLists(head1->rc, head2);
		return head1;
	}
	else {
		head2->rc = mergeSortedTaskLists(head1, head2->rc);
		return head2;
	}
}

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
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses){
	int ejectionRes = eject(pid_1, pid_2);
	if (ejectionRes == 0) return 0; // failed

	Player* alien = dlBSTGuardLookUp(pid_a); // find the alien
	if (alien == NULL) return 0; // alient not found

	// increase alien's evidence
	alien->evidence += number_of_witnesses;

	printPlayerAndTasksWithEvidence(players_tree);
	cout << "DONE" << endl;
    return 1;
}

/**
* @brief Ejects the player with pid_1 and merges his task list with the player
* with pid_2.
* @param pid_1 The pid of the player to be ejected
* @param pid_2 The pid of the player who will get the ejected player's tasks.
* @return 1 if successful, 0 otherwise
*/
int eject(int pid_1, int pid_2) {
	Player* playerToEject = dlBSTGuardLookUp(pid_1);
	if (playerToEject == NULL) return 0; // player doesn't exist
	Task* ejectedPlayerTaskList = playerToEject->tasks; // store the to-be-deleted player's tasks

	Player* pl2 = dlBSTGuardLookUp(pid_2); // find second player
	if (pl2 == NULL) return 0; // player not found

	players_tree = dlBSTDelete(pid_1); // delete player

	Task* player2TaskList = pl2->tasks; // store second players tasks
	if (ejectedPlayerTaskList == NULL || player2TaskList == NULL) {
		if (player2TaskList == NULL) {
			pl2->tasks = ejectedPlayerTaskList;
			return 1;
		}
		else { // no need to do anything
			return 1;
		}
	}

	// converts task BSTs to sorted linked lists
	Task* list1 = treeToSortedList(ejectedPlayerTaskList, NULL);
	Task* list2 = treeToSortedList(player2TaskList, NULL);
	// merge the two sorted lists
	Task* mergedList = mergeSortedTaskLists(list1, list2);
	// update second player's tasks tree with the new one
	pl2->tasks = sortedListToBST(mergedList);
	updateBSTLCnt(pl2->tasks);
	return 1;
}

// Prints players along with their evidence and task tree
void printPlayerAndTasksWithEvidence(Player* node) {
	if (node == players_sentinel) return;
	printPlayerAndTasksWithEvidence(node->lc);
	cout << "<Player_" << node->pid << "," << node->evidence << "> = ";
	printPlayerTasks(node->tasks);
	cout << endl;
	printPlayerAndTasksWithEvidence(node->rc);
	return;
}

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
int sabotage(int number_of_tasks, int pid) {
	if (number_of_tasks > max_tasks_g || number_of_tasks > completed_tasks_pq->size) return 0;
	Player* player = dlBSTGuardLookUp(pid);
	if (player == NULL) return 0; // not found
	int startingNodeIndex = floor(number_of_tasks / 2);

	// find the starting node
	Player* p = player;
	for (startingNodeIndex; startingNodeIndex > 0; startingNodeIndex--) {
		p = FindInorderPredecessor(p);
		if (startingNodeIndex == 1 && p->is_alien == 1) { // we've reached the appropriate node, check if it's an alien and repeat the process until we find a crewmate
			startingNodeIndex++;
		}
	}

	for (number_of_tasks; number_of_tasks > 0; number_of_tasks--) {
		if (p->is_alien == 1) { // if p is an alien, skip him and re-run the loop
			p = FindInorderSuccessor(p);
			number_of_tasks++;
			continue;
		}

		// remove task from pq and give it to p
		HT_Task htTaskToGive = pqFindMax(); // get the task that will be removed from the pq
		pqDeleteMax(); // remove it from the pq
		p->tasks = playerTaskInsert(p->tasks, htTaskToGive.tid, htTaskToGive.difficulty); // give task to player
		p = FindInorderSuccessor(p);
	}
	printPlayerAndTasks(players_tree);
    return 1;
}

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
int vote(int pid_1, int pid_2, int vote_evidence) {
	Player* suspect = dlBSTGuardLookUp(pid_1); // find the suspect player
	if (suspect == NULL) return 0; // not found
	suspect->evidence += vote_evidence; // increase evidence
	Player* maxEvidPlayer = findMostEvidencePlayer(players_tree, suspect); // find the player with the most evidence against him
	if (maxEvidPlayer == NULL) return 0;
	int result = eject(maxEvidPlayer->pid, pid_2);// eject him
	if (result == 0) return 0; // ejection failed
	printPlayerAndTasksWithEvidence(players_tree);
	cout << "DONE" << endl;
    return 1;
}

/**
* @brief Recursively traverses the players tree using In order traversal
* and finds the player with the most evidence against him.
* @param node The starting node to traverse
* @param maxPlayer The player with the most evidence so far
* @return The player with the most evidence or null if none found
*/
Player* findMostEvidencePlayer(Player* node, Player* maxPlayer) {
	if (node->lc != players_sentinel) {
		maxPlayer = findMostEvidencePlayer(node->lc, maxPlayer);
	}

	// update max evidence player if the condition is met
	if (node->evidence >= maxPlayer->evidence) maxPlayer = node;

	if (node->rc != players_sentinel) {
		maxPlayer = findMostEvidencePlayer(node->rc, maxPlayer);
	}

	return maxPlayer; // update this
}

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
int give_work(int pid_1, int pid_2) { 
	Player* playerToAdd = dlBSTGuardLookUp(pid_1);
	if (playerToAdd != NULL) return 0; // player exists already
	Player* newPlayer = dlBSTInsert(pid_1, 0, 0); // create new player
	if (newPlayer == NULL) return 0; // instertion failed

	Player* p2 = dlBSTGuardLookUp(pid_2); // look up second player
	if (p2 == NULL) return 0; // p2 doesnt exist

	//TODO:sp split p2's tree into two Trees in O(h) time and give one to the new player
	return 0;

    //return 1;
}

// under dev
void split(Task* root, int k) { // askisi 2.c (3o set askiseon)
	if (root == NULL) return;


}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int Terminate() {
	int aliens = countCrewmatesOrAliens(players_tree, 0, 1);
	int crewmates = countCrewmatesOrAliens(players_tree, 0, 0);

	// aliens win condition
	if (aliens > crewmates) {
		cout << "Aliens win." << endl << "DONE" << endl;
		return 1;
	}

	// players win condition
	if (aliens == 0 || completed_tasks_pq->size == max_tasks_g) {
		cout << "Crewmates win." << endl << "DONE" << endl;
		return 1;
	}

    return 0;
}

/**
* @brief Counts how many crewmates or aliens exist in the players tree using In order traversal.
* @param node The starting node to traverse
* @param cnt The starting count (should be 0)
* @param cntAliens 1 for counting aliens, 0 for counting crewmates
* @return The total count of crewmates or aliens
*/
int countCrewmatesOrAliens(Player* node, int cnt, int cntAliens) {
	if (node->lc != players_sentinel) {
		cnt += countCrewmatesOrAliens(node->lc, cnt, cntAliens);
	}

	if (cntAliens == 0 && node->is_alien == 0) cnt++; // count crewmates
	
	if (cntAliens == 1 && node->is_alien == 1) cnt++; // count aliens

	if (node->rc != players_sentinel) {
		cnt += countCrewmatesOrAliens(node->rc, cnt, cntAliens);
	}

	return cnt;
}

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
	cout << "Players = ";
	printPlayerEventX(players_tree);
	cout << endl << "DONE" << endl;
    return 1;
}

// prints the players tree for the X event
void printPlayerEventX(Player* node) {
	if (node == players_sentinel) return;
	printPlayerEventX(node->lc);
	cout << "<" << node->pid << ":" << node->is_alien << ">";
	printPlayerEventX(node->rc);
	return;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
	//printHT();
	//cout << "DONE" << endl;
    return 1;
}

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq() {
	if (completed_tasks_pq->size == 0) return 1;
	cout << "Completed Tasks = ";
	printPQ();
	cout << "DONE" << endl;
    return 1;
}

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree() {
	printPlayerAndTasks(players_tree);
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
    return 1;
}

/* Beginning of doubly linked BST (Players Tree) function definitions */

/**
* @brief Inserts a new player in the players tree with the given
* data.
* @param pid The pid of the new player to be inserted
* @param is_alien The isAlien value of the new player to be inserted (0==false , 1==true)
* @param evidence The evidence of the new player to be inserted
* @return The newly inserted player
*/
Player* dlBSTInsert(int pid, int is_alien, int evidence) {
	Player* curr = players_tree;
	Player* prev = players_tree->parrent;

	if (players_tree->pid == players_sentinel->pid) { // tree is empty
		curr->pid = pid;
		curr->evidence = evidence;
		curr->is_alien = is_alien;
		curr->parrent = NULL;
		curr->lc = players_sentinel;
		curr->rc = players_sentinel;
		curr->tasks = NULL;
		return players_tree;
	}

	// check if node with such pid exists
	while (curr != players_sentinel) {
		prev = curr;
		if (pid < curr->pid) curr = curr->lc;
		else curr = curr->rc;
	}

	// reached a leaf, create new node
	Player* newNode = new Player;
	newNode->pid = pid;
	newNode->is_alien = is_alien;
	newNode->evidence = evidence;
	newNode->lc = players_sentinel;
	newNode->rc = players_sentinel;
	newNode->tasks = NULL;
	newNode->parrent = prev;

	if (prev == NULL) return newNode;
	else if (pid < prev->pid) prev->lc = newNode;
	else prev->rc = newNode;

	return players_tree;
}

/**
* @brief Deletes the player with the given pid from the players tree.
* @param pid The pid of the player to be deleted
* @return The players tree without the deleted player or NULL if there's no such player
*/
Player* dlBSTDelete(int pid) {
	// base case, tree is empty
	if (players_tree->pid == players_sentinel->pid) return NULL;

	// Get the node to act upon
	Player* curr = dlBSTGuardLookUp(pid);
	if (curr == NULL) return players_tree; // no such node found, return the initial tree

	// node is a leaf or has just one child
	if (curr->lc == players_sentinel || curr->rc == players_sentinel) {
		if (curr->lc == players_sentinel && curr->rc == players_sentinel) { // is a leaf
			// update parent's child nodes
			if (curr->parrent->lc == curr) curr->parrent->lc = players_sentinel;
			else curr->parrent->rc = players_sentinel;
		}
		else { // has one child
			if (curr->lc != players_sentinel) { // has left child
				// copy contents of its child to the current node and delete the child node
				curr->pid = curr->lc->pid;
				curr->is_alien = curr->lc->is_alien;
				curr->evidence = curr->lc->evidence;
				curr->tasks = curr->lc->tasks;
				Player* newLC = curr->lc->lc;
				Player* newRC = curr->lc->rc;
				curr->lc = newLC;
				curr->rc = newRC;
			}
			else { // has right child
				// copy contents of its child to the current node and delete the child node
				curr->pid = curr->rc->pid;
				curr->is_alien = curr->rc->is_alien;
				curr->evidence = curr->rc->evidence;
				curr->tasks = curr->rc->tasks;
				Player* newLC = curr->rc->lc;
				Player* newRC = curr->rc->rc;
				curr->lc = newLC;
				curr->rc = newRC;
			}
		}
	}
	else { // node has two children and needs to be "replaced" by its successor
		Player* successor = FindInorderSuccessor(curr);
		// copy data from the successor to the current node and delete the successor
		curr->pid = successor->pid;
		curr->is_alien = successor->is_alien;
		curr->evidence = successor->evidence;
		curr->tasks = successor->tasks;
		// the successor will have at most 1 child, find it
		Player* succChild;
		if (successor->lc != players_sentinel) succChild = successor->lc;
		else succChild = successor->rc;

		// Connect the successor's parent with the successor's child
		if (successor->parrent->lc == successor) { // successor is the left child of his parent
			successor->parrent->lc = succChild;
		}
		else { // successor is the right child of his parent
			successor->parrent->rc = succChild;
		}
	}

	return players_tree;
}

/**
* @brief Finds the successor of the given node in the players tree.
* @param node The player whose successor to find
* @return The successor of the given node or NULL if not found
*/
Player* FindInorderSuccessor(Player* node) {
	// base cases
	if (node == bstFindMax()) { // if we are the end, the in order successor is the first element In order
		return bstFindMin();
	}

	if (node == players_sentinel || node == NULL) return NULL;

	Player* curr;
	if (node->rc != players_sentinel) { // if there's a right subtree, the successor lies there
		curr = node->rc;

		while (curr->lc != players_sentinel) {
			curr = curr->lc;
		}
		return curr;
	}
	else if (node->parrent != NULL) { // try to find the successor through the parent nodes
		curr = node;
		while (curr->pid <= node->pid && curr != NULL) {
			curr = node->parrent;
		}
		if (curr != NULL) return curr;
		else return NULL;
	}
	else {
		return NULL;
	}
}

/**
* @brief Finds the predecessor of the given node in the players tree.
* @param node The player whose predecessor to find
* @return The predecessor of the given node or NULL if not found
*/
Player* FindInorderPredecessor(Player* node) {
	// base cases
	if (node == bstFindMin()) { // if we are the first element, the in order predecessir is the last element In order
		return bstFindMax();
	}

	if (node == players_sentinel || node == NULL) return NULL;

	Player* curr;
	if (node->lc != players_sentinel) { // if there's a left subtree, the predecessor lies there
		curr = node->lc;

		while (curr->rc != players_sentinel) {
			curr = curr->rc;
		}
		return curr;
	}
	else if (node->parrent != NULL) { // try to find the predecessor through the parent nodes
		curr = node;
		while (curr->pid >= node->pid && curr != NULL) {
			curr = node->parrent;
		}
		if (curr != NULL) return curr;
		else return NULL;
	}
	else {
		return NULL;
	}
}

/**
* @brief Finds the player with the given pid in the players tree.
* @param pid The pid of the player to look for
* @return The player with the given pid or NULL if there's no such player
*/
Player* dlBSTGuardLookUp(int pid) {
	players_sentinel->pid = pid; // place data in the sentinel node
	Player* curr = players_tree;

	while (curr->pid != pid) {
		if (pid < curr->pid) curr = curr->lc;
		else curr = curr->rc;
	}

	// restore sentinel's pid
	players_sentinel->pid = -1;

	if (curr != players_sentinel) return curr;
	else return NULL;
}

/**
* @brief Finds the maximum element
* @param root The tree to search
* @return The maximum element
*/
Player* bstFindMin() {
	Player* curr = players_tree;
	if (curr == NULL || curr == players_sentinel) return NULL;

	while (curr->lc != players_sentinel) curr = curr->lc;
	return curr;
};

/**
* @brief Finds the minimum element
* @param root The tree to search
* @return The minimum element
*/
Player* bstFindMax() {
	Player* curr = players_tree;
	if (curr == NULL || curr == players_sentinel) return NULL;

	while (curr->rc != players_sentinel) curr = curr->rc;
	return curr;
};

/**
* @brief Prints the players of the list using in order traversal.
*/
void printDLBSTInOrder(Player* node) {
	if (node == players_sentinel) return;
	printDLBSTInOrder(node->lc);
	cout << "<"<< node->pid <<":"<<node->is_alien<<">";
	printDLBSTInOrder(node->rc);
	return;
}

/* End of doubly linked BST (Players Tree) function definitions */

/* Beginning of BST (Player tasks tree) function definitions */

/**
* @brief Inserts a new task in the given player tasks list with the
* passed attributes.
* @param root The root of the tree to which the new task will be added
* @param tid The tid of the new task
* @param difficulty The difficulty of the new task
* @return The tree with the newly added task
*/
Task* playerTaskInsert(Task* root, int tid, int difficulty) {
	Task* curr = root;
	Task* prev = NULL;

	if (curr == NULL) { // tree is empty
		Task* newTask = new Task;
		newTask->tid = tid;
		newTask->difficulty = difficulty;
		newTask->lcnt = 0;
		newTask->lc = NULL;
		newTask->rc = NULL;
		return newTask;
	}

	// check if node with such tid exists
	while (curr != NULL) {
		if (curr->tid == tid) { // node found, update data
			curr->difficulty = difficulty;
			return root;
		}
		prev = curr;
		if (tid < curr->tid) curr = curr->lc;
		else curr = curr->rc;
	}

	// reached a leaf, create new node
	Task* newNode = new Task;
	newNode->tid = tid;
	newNode->difficulty = difficulty;
	newNode->lc = NULL;
	newNode->rc = NULL;
	newNode->lcnt = 0;

	if (prev == NULL) return newNode; // we're at the root
	else if (tid < prev->tid) {
		prev->lc = newNode;
		updateParentPathLcCount(root, newNode, true);
	}
	else prev->rc = newNode;

	return root;
};

/**
* @brief Deletes the task with the given tid in the given player tasks list
* and adds it to the completed tasks priority queue.
* @param root The root of the tree from which the task will be deleted
* @param tid The tid of the task to delete
* @return The task list without removed task (if found)
*/
Task* playerTaskDelete(Task* root, int tid) {
	// base case, tree is empty
	if (root == NULL) return NULL;

	// Get the node to act upon
	Task* curr = playerTaskLookUp(root, tid);
	if (curr == NULL) return root; // no such node found
	Task* parent = playerGetParentTask(root, curr); // get the parent node

	int pqInsertionRes = pqInsert(curr->tid, curr->difficulty); // add the removed task to the completed stack
	if (pqInsertionRes == 0) return root; // pq is full so don't implement the task

	// node is a leaf or has just one child
	if (curr->lc == NULL || curr->rc == NULL) {
		if (curr->lc == NULL && curr->rc == NULL) { // is a leaf
			// update parent's child nodes
			if (parent != NULL) {
				if (parent->lc == curr) {
					updateParentPathLcCount(root, curr, false);
					parent->lc = NULL;
				}
				else parent->rc = NULL;
			}
			else { // curr is the only node of the task tree
				root = NULL;
			}
			//delete(curr);
		}
		else { // has one child
			if (curr->lc != NULL) { // has left child
				// copy contents of its child to the current node and delete the child node
				curr->tid = curr->lc->tid;
				curr->difficulty = curr->lc->difficulty;
				Task* newLC = curr->lc->lc;
				Task* newRC = curr->lc->rc;
				curr->lc = newLC;
				curr->rc = newRC;
				updateParentPathLcCount(root, curr->lc, false);
				//delete(curr->lc);
			}
			else { // has right child
				// copy contents of its child to the current node and delete the child node
				curr->tid = curr->rc->tid;
				curr->difficulty = curr->rc->difficulty;
				Task* newLC = curr->rc->lc;
				Task* newRC = curr->rc->rc;
				curr->lc = newLC;
				curr->rc = newRC;
				//delete(curr->rc);
			}
		}
	}
	else { // node has two children and needs to be "replaced" by its successor
		Task* successor = playerTaskSuccessor(root, curr);
		Task* succParent = playerGetParentTask(root, successor);
		// copy data from the successor to the current node and delete the successor
		curr->tid = successor->tid;
		curr->difficulty = successor->difficulty;
		// the successor will have at most 1 child, find it
		Task* succChild;
		if (successor->lc != NULL) succChild = successor->lc;
		else succChild = successor->rc;

		// Connect the successor's parent with the successor's child
		Task* successorParent = playerGetParentTask(root, successor);
		if (successorParent->lc == successor) { // successor is the left child of his parent
			successorParent->lc = succChild;
		}
		else { // successor is the right child of his parent
			successorParent->rc = succChild;
		}

		// if the successor is a left child, update lc counts
		if (succParent->lc == successor) updateParentPathLcCount(root, successor, false);

		// delete the successor
		//delete(successor);
	}

	return root;
};

/**
* @brief Finds the successor of the given task in the given task tree.
* @param root The root of the tree in which to look for the successor
* @param node The node who's successor to find
* @return The successor node or NULL if there's none
*/
Task* playerTaskSuccessor(Task* root, Task* node) {
	// base case
	if (node == NULL) return NULL;

	Task* curr;
	Task* parent = playerGetParentTask(root, node);
	if (node->rc != NULL) { // if there's a right subtree, the successor lies there
		curr = node->rc;

		while (curr->lc != NULL) {
			curr = curr->lc;
		}
		return curr;
	}
	else if (parent != NULL) { // try to find the successor through the parent nodes
		curr = node;
		while (curr->tid <= node->tid && curr != NULL) {
			curr = playerGetParentTask(root, node);
		}
		if (curr != NULL) return curr;
		else return NULL;
	}
	else {
		return NULL;
	}
};

/**
* @brief Finds the predecessor of the given task in the given task tree.
* @param root The root of the tree in which to look for the predecessor
* @param node The node who's predecessor to find
* @return The predecessor node or NULL if there's none
*/
Task* playerTaskPredecessor(Task* root, Task* node) {
	// base case
	if (node == NULL) return NULL;

	Task* curr;
	Task* parent = playerGetParentTask(root, node);
	if (node->lc != NULL) { // if there's a left subtree, the predecessor lies there
		curr = node->lc;

		while (curr->rc != NULL) {
			curr = curr->rc;
		}
		return curr;
	}
	else if (parent != NULL) { // try to find the predecessor through the parent nodes
		curr = node;
		while (curr->tid >= node->tid && curr != NULL) {
			curr = playerGetParentTask(root, node);
		}
		if (curr != NULL) return curr;
		else return NULL;
	}
	else {
		return NULL;
	}
};

/**
* @brief Helper function which finds the parent task of the given
* node.
* @param root The tree in which to look for the task's parent
* @param child The child node whose parent to find
* @return The parent of the given task or NULL if none was found
*/
Task* playerGetParentTask(Task* root, Task* child) {
	if (root == NULL || child == NULL) return NULL;

	Task* curr = root;
	while (curr != NULL && curr->lc != child && curr->rc != child) {
		if (child->tid < curr->tid) curr = curr->lc;
		else curr = curr->rc;
	}

	if (curr == NULL) return NULL;
	else return curr;
};

/**
* @brief Searches for a task with the given tid in the given tree.
* @param root The tree to search
* @param tid The tid of the task to look for
* @return The task with the given tid or NULL if not found
*/
Task* playerTaskLookUp(Task* root, int tid) {
	Task* curr = root;

	while (curr != NULL && curr->tid != tid) {
		if (tid < curr->tid) curr = curr->lc;
		else curr = curr->rc;
	}

	if (curr != NULL) return curr;
	else return NULL;
};

/**
* @brief Helper function that updates the lcnt field of the necessary nodes
* in the path from the given task towards the root.
* @param root The tree to traverse
* @param node The node whose parent path to traverse and update if needed.
* @param insertedNode Used to incerease or decrease the lcnt field.
* 1 if the function is called after an insertion or 0 if it's called after a deletion.
* Precondition: Should only be called when a task is added or deleted as a left child of a node.
*/
void updateParentPathLcCount(Task* root, Task* node, bool insertedNode) { // O(logn)
	Task* curr = playerGetParentTask(root, node);
	while (curr != NULL) { // haven't reached the root's parent
		if (insertedNode) curr->lcnt += 1;
		else curr->lcnt -= 1;
		curr = playerGetParentTask(root, curr);
	}
}

/**
* Prints the tasks of the given tree based on the In order traversal.
* @param root The tree to traverse
*/
void printPlayerTasks(Task* root) {
	if (root == NULL) return;
	printPlayerTasks(root->lc);
	cout << "<" << root->tid << "," << root->difficulty << ">,";
	printPlayerTasks(root->rc);
	return;
};

/* End of BST (Player tasks tree) function definitions */

/* Beginning of general task Hash Table function definitions */

/**
* @brief Hash function 
* @param key The key (tid) for which to calculate the hash value
* @return The hash value for the given key indicating its position in the hash table
*/
int h(int key) {
	return (((a * key + b) % p) % max_tasks_g);
}

/**
* @brief Finds the lowest prime number from the primes_g array 
* which is large enough to hold all the possible keys that we want to store (max_tasks_g).
* @return The prime number found
*/
int findPrime() {
	unsigned int i;
	// find a prime that's >= to the hash table's size
	for (i = 0; i < max_tasks_g; i++) {
		if (primes_g[i] >= max_tid_g) return primes_g[i];
	}
	return -1; // unreachable basically (used to silence compilation warnings)
}

/**
* @brief Inserts a new Task in the hash table with the given values (if there's room).
* @param tid The tid of the new task to insert
* @param difficulty The difficulty of the new task to insert
* @return The newly added task
*/
HT_Task* hashInsert(int tid, int difficulty) {
	if (general_tasks_ht->count == max_tasks_g) return NULL; // hash table is full

	int pos = h(tid); // get the hash value for the given tid

	HT_Task* firstEl = general_tasks_ht->tasks[pos]; // retrieve the list in which the new task will be placed
	// create new task with the given values
	HT_Task* newTask = new HT_Task;
	newTask->tid = tid;
	newTask->difficulty = difficulty;
	newTask->next = NULL;

	// place the new task at the beginning of the list
	general_tasks_ht->tasks[pos] = newTask;
	if(firstEl != NULL) newTask->next = firstEl;
	// increase tasks count
	general_tasks_ht->count += 1;
	
	return newTask;
}

/**
* @brief Searches for a task with the given tid in the hash table.
* @param tid The tid of the task to look for
* @return The task with the given tid or NULL if none was found.
*/
HT_Task* hashLookUp(int tid) {
	HT_Task** table = general_tasks_ht->tasks; // get the hash table of tasks
	int pos = h(tid); // get the hash value for the given tid
	HT_Task* task = table[pos]; // retrieve the list in which the task with the given tid could be
	// look for the task in the chain
	while (task != NULL && task->tid != tid) task = task->next;
	if (task == NULL) return NULL;
	else return task;
}

/**
* @brief Searches for the parent task of the task with the given tid.
* @param tid The tid of the task whose parent to look for.
* @return The parent task or NULL if none was found.
*/
HT_Task* getParentHTTask(int tid) {
	HT_Task** table = general_tasks_ht->tasks; // get the hash table of tasks
	int pos = h(tid); // get the hash value for the given tid
	HT_Task* task = table[pos]; // retrieve the list in which the task with the given tid could be
	// look for the task's parent in the list
	while (task != NULL && task->next->tid != tid) task = task->next;
	if (task == NULL) return NULL;
	else return task;
}

/**
* @brief Deletes the task with the given tid from the hash table.
* @param tid The tid of the task to delete
* @return The new list without the removed task
*/
HT_Task* hashDelete(int tid) {
	if (general_tasks_ht->count == 0) return NULL; // hash table is empty

	int pos = h(tid);
	HT_Task* curr = hashLookUp(tid);
	if (curr == NULL) return NULL; // task not found

	HT_Task* tskToReturn = NULL;

	// get the parent task in order to connect it with the task that's after the task to be deleted
	HT_Task* parent = NULL;
	if (curr != general_tasks_ht->tasks[pos]) { // if the task to be deleted isn't the first task
		parent = getParentHTTask(tid);
		HT_Task* nextTask = curr->next;
		tskToReturn = curr;
		//delete(curr);
		parent->next = nextTask;
	}
	else { // task to be deleted is the first task
		tskToReturn = general_tasks_ht->tasks[pos];
		general_tasks_ht->tasks[pos] = curr->next;
	}

	// decrease tasks count
	general_tasks_ht->count -= 1;
	return tskToReturn;
}

/**
* Prints the hash table.
*/
void printHT() {
	unsigned int i;
	// iterate over the [max_tasks_g] rows of the hash table
	for (i = 0; i < max_tasks_g; i++) {
		cout << "Index " << i << ": ";

		// iterate over the tasks of the list at the i-th position
		HT_Task* curr = general_tasks_ht->tasks[i]; // pointer to the head of the list at that position

		if (curr == NULL) { // if list is empty
			cout << endl;
			continue;
		}

		while (curr != NULL) {
			cout << "<" << curr->tid << "," << curr->difficulty << ">";
			curr = curr->next;
			if (curr != NULL) cout << ",";
		}
		cout << endl;
	}
}

/* End of general task Hash Table function definitions */

/* Beginning of Priority Queue function definitions */

/**
* @brief Checks whether the priority queue containing completed tasks is empty.
* @return True if it's empty and false otherwise
*/
bool isEmptyPQ() {
	return (completed_tasks_pq->size == 0);
}

/**
* @brief Inserts a new task with the given values in the priority queue of completed tasks.
* @param tid The tid of the new task to insert
* @param difficulty The difficulty of the new task to insert
* @return 0 if unsuccessful and 1 otherwise
*/
int pqInsert(int tid, int difficulty) { // O(h)
	if (completed_tasks_pq->size == max_tasks_g) return 0;

	/* Pointer to a node in a path of the tree. Points to the position where the new node will be inserted*/
	int m = completed_tasks_pq->size;
	HT_Task task;
	task.tid = 0;
	task.difficulty = 0;
	task.next = NULL;
	completed_tasks_pq->tasks[m] = task;

	while (m > 0 && difficulty >= completed_tasks_pq->tasks[(int)floor((m - 1) / 2)].difficulty) { // (int) floor((m - 1) / 2) = parent's index
		// copy contents of m's parent to m
		completed_tasks_pq->tasks[m].tid = completed_tasks_pq->tasks[(int)floor((m - 1) / 2)].tid;
		completed_tasks_pq->tasks[m].difficulty = completed_tasks_pq->tasks[(int)floor((m - 1) / 2)].difficulty;
		m = floor((m - 1) / 2);
	}
	// insert new data
	completed_tasks_pq->tasks[m].tid = tid;
	completed_tasks_pq->tasks[m].difficulty = difficulty;
	completed_tasks_pq->size += 1; // increase pq size
	return 1;
}

/**
* @brief Recursively "heapifies" the given (sub)tree in order to
* preserve the characteristics of the max priority queue.
* @param i the index of the root of the given subtree
* Important: Should be called after each deletion of max.
*/
void heapify(int i) { // TimeComplexity: O(h)
	int size = completed_tasks_pq->size;
	HT_Task* tasks = completed_tasks_pq->tasks;
	int max = i; // max priority task should be at index 0 (root)
	int l = 2 * i + 1; // lc
	int r = 2 * i + 2; // rc

	if (l < size && tasks[l].difficulty > tasks[max].difficulty) { // i node has lc
		max = l;
	}

	if (r < size && tasks[r].difficulty > tasks[max].difficulty) { // i node has rc
		max = r;
	}

	// if max difficulty task isn't at the root of the (sub)tree
	if (max != i) {
		// swap task nodes
		HT_Task tmp = tasks[i];
		completed_tasks_pq->tasks[i] = tasks[max];
		completed_tasks_pq->tasks[max] = tmp;

		// repeat heapify for the affected subtree
		heapify(max);
	}
}

/**
* @brief Deletes the max priority/difficulty node (root).
*/
void pqDeleteMax() { // O(h) : (O(1) + O(heapify)) = O(h)
	if (isEmptyPQ()) return;
	int size = completed_tasks_pq->size;

	HT_Task root = completed_tasks_pq->tasks[0]; //task to return
	HT_Task lastTask = completed_tasks_pq->tasks[size - 1]; // last node

	// replace root with the last task in the pq
	completed_tasks_pq->tasks[0] = lastTask;
	completed_tasks_pq->tasks[size - 1].tid = -1;
	completed_tasks_pq->tasks[size - 1].difficulty = -1;
	completed_tasks_pq->size -= 1;

	// call heapify starting from the root
	heapify(0);
}

/**
* @brief Finds the max priority/difficulty node (root).
* @return The max priority/difficulty node
*/
HT_Task pqFindMax() { // O(1)
	return completed_tasks_pq->tasks[0];
}

/**
* @brief Prints the contents of the max priority queue in descending order of priority.
*/
void printPQ() { // O(n)
	if (isEmptyPQ()) return;
	int i;
	for (i = 0; i < completed_tasks_pq->size; i++) {
		cout << "<" << completed_tasks_pq->tasks[i].tid << "," << completed_tasks_pq->tasks[i].difficulty << ">";
	}
	cout << endl;
}

/* End of Priority Queue function definitions */

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

	// Read max enemy soldiers' number
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_tasks_g);
	DPRINT("Max number of tasks: %d\n", max_tasks_g)

	// Read max enemy soldiers' ID
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_tid_g);
	DPRINT("Max task tid: %d\n", max_tid_g)

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

		/* Register Player
		 * P <pid> <is_alien> */
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

		/* Insert Task
		 * T <tid> <difficulty>  */
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
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Implement Task
		 * I <pid> <tid> */
		case 'I':
		{
			int pid, tid;

			sscanf(buff, "%c %d %d", &event, &pid, &tid);
			DPRINT("%c %d %d \n", event, pid, tid);

			if (implement_task(pid, tid))
			{
				DPRINT("%c %d %d succeeded\n", event, pid, tid);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid, tid);
			}

			break;
		}

		/* Eject Player
		 * E <pid_1> <pid_2>*/
		case 'E':
		{
			int pid_1, pid_2;

			sscanf(buff, "%c %d %d", &event, &pid_1, &pid_2);
			DPRINT("%c %d %d\n", event, pid_1, pid_2);

			if (eject_player(pid_1, pid_2))
			{
				DPRINT("%c %d %d succeeded\n", event, pid_1, pid_2);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid_1, pid_2);
			}

			break;
		}

		/* Witness Ejection
		 * W <pid> <pid_a> <number_of_witnesses>
		 */
		case 'W':
		{
			int pid_1, pid_2 ,pid_a ,number_of_witnesses;

			sscanf(buff, "%c %d %d %d %d", &event, &pid_1, &pid_2, &pid_a, &number_of_witnesses);
			DPRINT("%c %d %d %d %d\n", event, pid_1, pid_2, pid_a, number_of_witnesses);

			if (witness_eject(pid_1, pid_2, pid_a, number_of_witnesses))
			{
				DPRINT("%c %d %d %d %d succeded\n", event, pid_1, pid_2, pid_a, number_of_witnesses);
			}
			else
			{
				fprintf(stderr, "%c %d %d %d %d failed\n", event, pid_1, pid_2, pid_a, number_of_witnesses);
			}

			break;
		}

		/* Sabotage
		 * S <number_of_tasks> <pid> */
		case 'S':
		{
			int number_of_tasks, pid;

			sscanf(buff, "%c %d %d\n", &event, &number_of_tasks, &pid);
			DPRINT("%c %d %d\n", event, number_of_tasks, pid);

			if (sabotage(number_of_tasks, pid))
			{
				DPRINT("%c %d %d succeeded\n", event, number_of_tasks, pid);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, number_of_tasks, pid);
			}

			break;
		}

		/* Vote
		 * V <pid_1> <pid_2> <vote_evidence> */
		case 'V':
		{
			int pid_1, pid_2, vote_evidence;

			sscanf(buff, "%c %d %d %d\n", &event, &pid_1, &pid_2, &vote_evidence);
			DPRINT("%c %d %d %d\n", event, pid_1, pid_2, vote_evidence);

			if (vote(pid_1, pid_2, vote_evidence))
			{
				DPRINT("%c %d %d %d succeeded\n", event, pid_1, pid_2, vote_evidence);
			}
			else
			{
				fprintf(stderr, "%c %d %d %d failed\n", event, pid_1, pid_2, vote_evidence);
			}

			break;
		}

		/* Give Away Work
		 * G <pid_1> <pid_2> */
		case 'G':
		{
			int pid_1, pid_2;

			sscanf(buff, "%c %d %d", &event, &pid_1, &pid_2);
			DPRINT("%c %d %d\n", event, pid_1, pid_2);

			if (give_work(pid_1, pid_2))
			{
				DPRINT("%c %d %d succeeded\n", event, pid_1, pid_2);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid_1, pid_2);
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

		/* Print Priority Queue
		 * Z */
		case 'Z':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_pq())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Players & Tasks tree
		 * F */
		case 'U':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_double_tree())
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
