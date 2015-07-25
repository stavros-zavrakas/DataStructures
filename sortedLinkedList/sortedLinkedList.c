// Simple Linked List with sorted elements.
// We perform the insertions to ensure that the elements are sorted.
// Using SL as convention naming to Sorted List.

#include "sortedLinkedList.h"

void SL_Insert(struct SubInfo **root) {
  struct SubInfo *temp, *temp1, *temp2;
  int sId, stm;
  printf("Please provide the sId:\n");
  scanf("%d", &sId);
  printf("Please provide the stm:\n");
  scanf("%d", &stm);
  printf("\nAdding the new node with id: %d and time: %d.\n", sId, stm);
  if(*root == NULL) {
    temp1 = (struct SubInfo *) malloc(sizeof(struct SubInfo));

    if(temp1 == NULL) {
      printf("Error allocating memory.\n");
      exit(0);
    }

    temp1->sId = sId;
    temp1->stm = stm;
    temp1->next = NULL;
    *root = temp1;
  } else {
    temp = (struct SubInfo *) malloc(sizeof(struct SubInfo));
    temp->stm = stm;
    temp->sId = sId;
    for(temp2 = NULL, temp1 = *root; (temp1 != NULL) && (temp1->stm < stm); temp2 = temp1, temp1 = temp1->next);

    if(temp2 == NULL) {
      temp->next = temp1;
      *root = temp;
    } else {
      temp->next = temp1;
      temp2->next = temp;
    }
  }
  printf("\nThe new node added: (sID: %d, stm: %d).\n", sId, stm);
}

void SL_Remove(struct SubInfo **root) {
  struct SubInfo *temp1, *temp2;
  int stm;

  printf("Please provide the stm that you want to delete:\n");
  scanf("%d", &stm);

  for(temp2 = NULL, temp1 = *root; (temp1 != NULL) && (temp1->stm < stm); temp2 = temp1, temp1 = temp1->next);

  if((temp1 == NULL) || (temp1->stm > stm)) {
    printf("\nThe stm couldn't be deleted.\n");
  } else {
    printf("\nThe stm deleted successfuly.\n");
    if(temp2 == NULL) {
      *root = temp1->next;
    } else {
      temp2->next = temp1->next;
    }
    free(temp1);
  }
}

void SL_LookUp(struct SubInfo **root) {
  struct SubInfo *temp;
  int stm;

  printf("Please provide the stm that you want to search for: ");
  scanf("%d", &stm);
  for(temp = *root; (temp != NULL) && (temp->stm < stm); temp = temp->next);

  if((temp == NULL) || (temp->stm > stm)) {
    printf("\nThe stm %d couldn't be found.\n", stm);
  } else {
    printf("\nThe stm %d found.\n", stm);
  }
}

void SL_Print(struct SubInfo **root) {
  struct SubInfo *temp;

  for(temp = *root; (temp != NULL); temp = temp->next) {
    printf(" stm = %d ", temp->stm);
    printf(" sId = %d \n", temp->sId);
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
