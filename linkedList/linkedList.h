#include <stdio.h>
#include <stdlib.h>

#ifndef MG
#define MG 10
#endif

struct Subscription {
  int sId;
  struct Subscription *snext;
};

// Function: L_Insert
// --------------------
// Inserts a node on the head of the list.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_Insert(struct Subscription **root, int sId);

// Function: L_Remove
// --------------------
// Removes a node from the list.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_Remove(struct Subscription **root, int sId);

// Function: L_LookUp
// --------------------
// Search for a node in the list.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_LookUp(struct Subscription **root, int sId);

// Function: L_LookUp
// --------------------
// Function that is printing the list.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_Print(struct Subscription **root);

// Function: L_Free
// --------------------
// Function that is realeasing all the list from the memory.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_Free(struct Subscription **root);
