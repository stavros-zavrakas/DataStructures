#include "doubleLinkedList.h"

void DL_Insert(struct Info **root, struct Info **last, int itm, int iId) {
  struct Info *temp, *temp1, *temp2 = NULL;
  temp = (struct Info *) malloc(sizeof(struct Info));

  if(temp == NULL) {
    printf("Error allocating memory.\n");
    exit(0);
  }

  temp->iId = iId;
  temp->itm = itm;
  if(*root == NULL) {
    // The list is empty and we initializing it.
    temp->inext = NULL;
    temp->iprev = NULL;
    *root = temp;
    *last = temp;
  } else {
    // Find the position that we have to insert the node.
    for(temp2 = NULL, temp1 = *root; (temp1 != NULL) && (temp1->itm < itm); temp2 = temp1, temp1 = temp1->inext);

    if(temp1 == NULL) {
      // Inserting in the tail of the list.
      temp->inext = NULL;
      temp->iprev = temp2;
      temp2->inext = temp;
      *last = temp;
    } else if(temp2 == NULL) {
      // Inserting in the head of the list.
      temp->inext = temp1;
      temp->iprev = NULL;
      temp1->iprev = temp;
      *root = temp;
    } else {
      // Insert somewhere in the middle of the list.
      temp->inext = temp1;
      temp->iprev = temp2;
      temp2->inext = temp;
      temp1->iprev = temp;
    }
  }

  printf("\nThe new node added: (iID: %d, itm: %d)\n", iId, itm);
}

void DL_Remove(struct Info **root, struct Info **last, int itm) {
  struct Info *temp1, *temp2, *temp3;
  int found;
  found = 0;
  temp1 = *root;

  while(temp1 != NULL) {
    if(temp1->itm == itm) {
      found = 1;
      if(temp1 == *root) {
        // It is the first element in the list.
        temp2 = *root;
        if(temp2->inext == NULL) {
          // It is the only element in the list.
          free(temp2);
          *root = NULL;
          break;
        } else {
          // It is not the first element and the list contains other elements as well.
          temp2 = temp1->inext;
          temp2->iprev = NULL;
          *root = temp2;
          free(temp1);
          break;
        }
      } else if(temp1->inext == NULL) {
        // It is the last element in the list.
        temp2 = temp1->iprev;
        temp2->inext = NULL;
        *last = temp2;
        free(temp1);
        break;
      } else {
        // It is somewhere in the middle of the list.
        temp2 = temp1->iprev;
        temp3 = temp1->inext;
        temp2->inext = temp3;
        temp3->iprev = temp2;
        free(temp1);
        break;
      }
    }
    temp1 = temp1->inext;
  }

  if(found == 0) {
    printf("\nThe imt couldn't be deleted.\n");
  } else {
    printf("\nThe itm deleted successfuly.\n");
  }
}

void DL_LookUp(struct Info **root, int itm) {
  struct Info *temp;

  for(temp = *root; (temp != NULL) && (temp->itm < itm); temp = temp->inext);

  if((temp == NULL) || (temp->itm > itm)) {
    printf("\nThe itm %d couldn't be found.\n", itm);
  }
  else {
    printf("\nThe itm %d found.\n", itm);
  }
}

void DL_Print(struct Info **root) {
  struct Info *temp;

  for(temp = *root; (temp != NULL); temp = temp->inext) {
    if(temp == *root) {
      printf("INFOLIST = ");
    }

    printf("<%d>", temp->iId);
  }
}

void DL_Free(struct Info **root) {
  struct Info *temp1, *temp2;

  if(*root != NULL) {
    for(temp2 = *root, temp1 = temp2->inext; (temp1 != NULL); temp2 = temp1, temp1 = temp1->inext) {
      free(temp2);
    }
    free(temp2);
    *root = NULL;
  }
}
