#include <stdio.h>
#include <stdlib.h>
#define HASH_MULTIPLIER 65599

struct SubInfo {
  int sId;
  int stm;
  struct SubInfo *next;
};

struct SubInfo **table;

// HT_HashFunction function
// --------------------
// Returns a random integer between 0 and the hashSize that
// will be specified in the parameter and also depending on the
// sId factor.
//
// More information about hash functions:
// @see: https://en.wikipedia.org/wiki/Hash_function
//
// sId (int): the factor to generate random hash numbers
// hashSize (int): the upper limit (ceil) of the random number
//
// returns: (int) the random generated number
int HT_HashFunction(int sId, int hashSize);

// HT_Insert function
// --------------------
// Inserts a node in the specific list of the hash table.
//
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void HT_Insert(struct SubInfo **root, int hash_num, int hashSize);

// HT_Remove function
// --------------------
// Deletes a node from the specific list of the hash table field,
// depending on the provided sId.
//
// sId (int): the sId to be removed from the list
// hashSize (int): the upper limit (ceil) of the random number
//
// returns: (void)
void HT_Remove(int sId, int hashSize);

// HT_print function
// --------------------
// Function that is printing all the elements of the hash table.
//
// hashSize (int): the upper limit (ceil) of the random number
//
// returns: (void)
void HT_Print(int hashSize);

// HT_Free function
// --------------------
// Function that is realeasing all the list elements of the hash table.
//
// hashSize (int): the upper limit (ceil) of the random number
//
// returns: (void)
void HT_Free(int hashSize);