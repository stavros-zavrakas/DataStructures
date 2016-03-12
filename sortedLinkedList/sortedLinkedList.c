// Simple Linked List with sorted elements.
// We perform the insertions to ensure that the elements are sorted.
// Using SL as convention naming to Sorted List.

#include "sortedLinkedList.h"

void SL_Insert(struct SubInfo **root, int sId, int stm) {
  struct SubInfo *temp1, *temp2, *iterator;

  if(*root == NULL) {
    iterator = (struct SubInfo *) malloc(sizeof(struct SubInfo));

    if(iterator == NULL) {
      printf("Error allocating memory.\n");
      exit(0);
    }

    iterator->sId = sId;
    iterator->stm = stm;
    iterator->next = NULL;
    *root = iterator;
  } else {
    temp1 = (struct SubInfo *) malloc(sizeof(struct SubInfo));
    temp1->stm = stm;
    temp1->sId = sId;
    for(temp2 = NULL, iterator = *root; (iterator != NULL) && (iterator->stm < stm); temp2 = iterator, iterator = iterator->next);

    if(temp2 == NULL) {
      temp1->next = iterator;
      *root = temp1;
    } else {
      temp1->next = iterator;
      temp2->next = temp1;
    }
  }

  #if SGP_AS_STRUCT
    for(i = 0; i < MG; i++) {
      iterator->sgp[i] = NULL;
    }
  #endif
}

void SL_Remove(struct SubInfo **root, int stm) {
  struct SubInfo *iterator, *temp;

  for(temp = NULL, iterator = *root; (iterator != NULL) && (iterator->stm < stm); temp = iterator, iterator = iterator->next);

  if((iterator == NULL) || (iterator->stm > stm)) {
    printf("\nThe stm couldn't be deleted.\n");
  } else {
    if(temp == NULL) {
      *root = iterator->next;
    } else {
      temp->next = iterator->next;
    }
    free(iterator);
  }
}

void SL_LookUp(struct SubInfo **root, int stm) {
  struct SubInfo *temp;

  for(temp = *root; (temp != NULL) && (temp->stm < stm); temp = temp->next);

  if((temp == NULL) || (temp->stm > stm)) {
    printf("\nThe stm %d couldn't be found.\n", stm);
  } else {
    printf("\nThe stm %d found.\n", stm);
  }
}

void SL_Print(struct SubInfo **root) {
  struct SubInfo *temp;

  printf("\nSUBSCRIBERLIST = ");
  for(temp = *root; (temp != NULL); temp = temp->next) {
    printf("<%d>", temp->sId);
  }
}

void SL_Free(struct SubInfo **root) {
  struct SubInfo *temp1, *temp2;

  if(*root != NULL) {
    for(temp2 = *root, temp1 = temp2->next; (temp1 != NULL); temp2 = temp1, temp1 = temp1->next) {
      free(temp2);
    }

    free(temp2);
    *root = NULL;
  }
}
