// Simple Linked List.
// We perform the insertions on the head of the list.

#include <stdio.h>
#include <stdlib.h>
#define MG 64

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
void L_Insert(struct Subscription **root) {
  struct Subscription *temp;
  int sId;

  printf("Please provide the sId:\n");
  scanf("%d", &sId);

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

// Function: L_Remove
// --------------------
// Removes a node from the list.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_Remove(struct Subscription **root) {
  struct Subscription *temp1, *temp2;
  int sId;

  printf("Please provide the sId:\n");
  scanf("%d", &sId);

  for(temp2 = NULL, temp1 = *root; (temp1 != NULL) && (temp1 -> sId != sId); temp2 = temp1, temp1 = temp1 -> snext);

  if(!temp1) {
    printf("The sId couldn't be deleted.\n");
  } else {
    if(temp2 == NULL) {
      *root = temp1 -> snext;
    } else {
      temp2 -> snext = temp1 -> snext;
    }

    free(temp1);
    printf("\nThe sId deleted successfuly.\n");
  }
}

// Function: L_LookUp
// --------------------
// Search for a node in the list.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_LookUp(struct Subscription **root) {
  struct Subscription *temp;
  int sId, found;

  printf("Please provide the sId that you want to search for: ");
  scanf("%d", &sId);

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

// Function: L_LookUp
// --------------------
// Function that is printing the list.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
void L_Print(struct Subscription **root) {
  struct Subscription *temp;

  for(temp = *root; temp != NULL; temp = temp -> snext) {
    printf("sId: %d\n", temp -> sId);
  }
}

// Function: L_Free
// --------------------
// Function that is realeasing all the list from the memory.
// 
// **root: the head of the list (typeof struct Subscription)
//
// returns: (void)
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

int main() {
  struct Subscription *gsub;
  int choice;
  gsub = NULL;

  printf("Please select one of the following functionalities:\n");
  printf("0. Exit.\n");
  printf("1. Insert a node.\n");
  printf("2. Delete a node.\n");
  printf("3. Searching for a node.\n");
  printf("4. Print the list.\n");
  scanf("%d", &choice);

  while(choice != 0) {
    if(choice == 1) {
      L_Insert(&gsub);
    } else if(choice == 2) {
      L_Remove(&gsub);
    } else if(choice == 3) {
      L_LookUp(&gsub);
    } else if(choice == 4) {
      L_Print(&gsub);
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

  L_Free(&gsub);
  return 0;
}
