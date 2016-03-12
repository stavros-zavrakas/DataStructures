#include <stdio.h>
#include <stdlib.h>

#ifndef MG
#define MG 10
#endif

struct Info {
  int iId;
  int itm;
  int igp[MG];
  struct Info *iprev;
  struct Info *inext;
};

// Function: DL_Insert
// --------------------
// Inserts a node in the list. Ensures that the insertions
// is depending on the stm field of the structure to ensure
// that the list will be sorted.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void DL_Insert(struct Info **root, struct Info **last, int itm, int iId);

// DL_Remove function
// --------------------
// Deletes a node from the list depending on the provided itm.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void DL_Remove(struct Info **root, struct Info **last, int itm);

// DL_LookUp function
// --------------------
// Search for a node in the list.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void DL_LookUp(struct Info **root, int itm);

// DL_Print function
// --------------------
// Function that is printing the list.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void DL_Print(struct Info **root);

// DL_Free function
// --------------------
// Function that is realeasing all the list from the memory.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void DL_Free(struct Info **root);
