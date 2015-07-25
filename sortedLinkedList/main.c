// Simple Linked List with sorted elements.
// We perform the insertions to ensure that the elements are sorted.
// Using SL as convention naming to Sorted List.

#include <stdio.h>
#include <stdlib.h>
#define MG 64

struct SubInfo {
  int sId;
  int stm;
  int sgp[MG];
  struct SubInfo *next;
};

// void SL_Insert (struct SubInfo **head);
// void printing (struct node **head);
// void free_nodes (struct node **head);

// SL_Insert function
// --------------------
// Inserts a node in the list. Ensures that the insertions
// is depending on the stm field of the structure to ensure
// that the list will be sorted.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
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

// SL_Delete function
// --------------------
// Deletes a node from the list depending on the provided stm.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
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

// SL_Print function
// --------------------
// Search for a node in the list.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
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

// SL_Print function
// --------------------
// Function that is printing the list.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
void SL_Print(struct SubInfo **root) {
  struct SubInfo *temp;

  for(temp = *root; (temp != NULL); temp = temp->next) {
    printf(" stm = %d ", temp->stm);
    printf(" sId = %d \n", temp->sId);
  }
}

// SL_Free function
// --------------------
// Function that is realeasing all the list from the memory.
// 
// **root: the head of the list (typeof struct SubInfo)
//
// returns: (void)
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

int main() {
  struct SubInfo *head;
  int choice;
  head = NULL;

  printf("Please select one of the following functionalities:\n");
  printf("0. Exit.\n");
  printf("1. Insert a node.\n");
  printf("2. Delete a node.\n");
  printf("3. Searching for a node.\n");
  printf("4. Print the list.\n");
  scanf("%d", &choice);

  while(choice != 0) {
    if(choice == 1) {
      SL_Insert(&head);
    } else if(choice == 2) {
      SL_Remove(&head);
    } else if(choice == 3) {
      SL_LookUp(&head);
    } else if(choice == 4) {
      SL_Print(&head);
    } else {
      printf("The functionality is not supported. Please another option.\n");
    }

    printf("Please select one of the following functionalities:\n");
    printf("0. Exit.\n");
    printf("1. Insert a node.\n");
    printf("2. Delete a node.\n");
    printf("3. Searching for a node.\n");
    printf("4. Print the list.\n");
    scanf("%d", &choice);
  }

  SL_Free(&head);
  return 0;
}
