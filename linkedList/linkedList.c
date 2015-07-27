#include "linkedList.h"

// Simple Linked List implementation.
// We perform the insertions on the head of the list.

void L_Insert(struct Subscription **root, int sId) {
  struct Subscription *temp;

  temp = (struct Subscription *) malloc(sizeof(struct Subscription));

  if(temp == NULL) {
    printf("Error allocating memory.\n");
    exit(0);
  } else {
    temp -> sId = sId;
    temp -> snext = *root;
    *root = temp;
  }
}

void L_Remove(struct Subscription **root, int sId) {
  struct Subscription *iterator, *temp;

  for(temp = NULL, iterator = *root; (iterator != NULL) && (iterator -> sId != sId); temp = iterator, iterator = iterator -> snext);

  if(!iterator) {
    printf("The sId couldn't be deleted.\n");
  } else {
    if(temp == NULL) {
      *root = iterator -> snext;
    } else {
      temp -> snext = iterator -> snext;
    }

    free(iterator);
    printf("\nThe sId deleted successfuly.\n");
  }
}

void L_LookUp(struct Subscription **root, int sId) {
  struct Subscription *temp;
  int found;

  temp = *root;
  found = 0;
  while(temp != NULL) {
    if(temp -> sId == sId) {
      found = 1;
      break;
    }
    temp = temp -> snext;
  }
  if(found == 1) {
    printf("\nThe sId %d couldn't be found.\n", sId);
  } else {
    printf("\nThe sId wasn't found.\n");
  }

}

void L_Print(struct Subscription **root) {
  struct Subscription *temp;

  for(temp = *root; temp != NULL; temp = temp -> snext) {
    printf("sId: %d\n", temp -> sId);
  }
}

void L_Free(struct Subscription **root) {
  struct Subscription *temp1, *temp2;

  if(*root != NULL) {
    for(temp2 = *root, temp1 = temp2 -> snext; (temp1 != NULL); temp2 = temp1, temp1 = temp1 -> snext) {
      free(temp2);
    }
    free(temp2);
    *root = NULL;
  }
}
