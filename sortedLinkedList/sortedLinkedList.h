#include <stdio.h>
#include <stdlib.h>
#define MG 64

struct SubInfo {
  int sId;
  int stm;
  int sgp[MG];
  struct SubInfo *next;
};

// SL_Insert function
// --------------------
// Inserts a node in the list. Ensures that the insertions
// is depending on the stm field of the structure to ensure
// that the list will be sorted.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void SL_Insert(struct SubInfo **root, int sId, int stm);

// SL_Remove function
// --------------------
// Deletes a node from the list depending on the provided stm.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void SL_Remove(struct SubInfo **root, int stm);

// SL_LookUp function
// --------------------
// Search for a node in the list.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void SL_LookUp(struct SubInfo **root, int stm);

// SL_Print function
// --------------------
// Function that is printing the list.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void SL_Print(struct SubInfo **root);

// SL_Free function
// --------------------
// Function that is realeasing all the list from the memory.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void SL_Free(struct SubInfo **root);
