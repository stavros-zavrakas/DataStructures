#include "hashTable.h"

int HT_HashFunction(int sId, int hashSize) {
  int i;
  int hash = 0;

  for(i = 0; i < sId; i++) {
    hash = hash * HASH_MULTIPLIER + hashSize;
  }

  hash = abs(hash) % hashSize;

  return hash;
}

void HT_Insert(struct SubInfo **root, int hash_num, int hashSize) {
  struct SubInfo *temp = *root;
  int i;

  if(table[hash_num] == NULL) {
    // The list of that specific field of the hash table is still empty
    table[hash_num] = temp;
    temp->next = NULL;
  } else {
    // The list of that specific field of the hash table has already some items.
    temp->next = table[hash_num];
    table[hash_num] = *root;
  }
}

void HT_Remove(int sId, int hashSize) {
  int i, deleted = 0;
  struct SubInfo *temp1, *temp2, *temp3;

  // Iterate over the hast table
  for(i = 0; i < hashSize; i++) {
    if(table[i] != NULL) {
      temp1 = table[i];
      temp2 = NULL;

      // Iterate over the list to find the node
      while(temp1 != NULL) {
        if(temp1->sId == sId) {
          if(temp1 == table[i]) {
            // The element is first in the list
            temp2 = table[i]->next;
            table[i] = temp2;
            free(temp1);
            deleted = 1;
            break;
          } else if(temp1->next == NULL) {
            // The element is last in the list
            free(temp1);
            temp2->next = NULL;
            deleted = 1;
            break;
          } else {
            // The element is in the middle of the list
            temp3 = temp1->next;
            free(temp1);
            temp2->next = temp3;
            deleted = 1;
            break;
          }
        }
        temp2 = temp1;
        temp1 = temp1->next;
      }

    }

    if(deleted == 1) {
      printf("The sId: %d deleted successfully.\n", sId);
      break;
    }
  }

  if(deleted == 0) {
    printf("Unable to find and delete the sId: %d.\n", sId);
  }

}

void HT_Print(int hashSize) {
  struct SubInfo *iterator;
  int i;

  for(i = 0; i < hashSize; i++) {
    if(table[i] != NULL) {
      iterator = table[i];
      printf("\nHash table element: %d\n", i);
      while(iterator != NULL) {
        printf("\tsId: %d, stm: %d\n", iterator->sId, iterator->stm);
        iterator = iterator->next;
      }
    }
  }
  printf("\n");
}

void HT_Free(int hashSize) {
  struct SubInfo *iterator, *temp;
  int i;

  for(i = 0; i < hashSize; i++) {
    if(table[i] != NULL) {
      iterator = table[i];
      while(iterator != NULL) {
        temp = iterator;
        iterator = iterator->next;
        free(temp);
      }
    }
  }
}
