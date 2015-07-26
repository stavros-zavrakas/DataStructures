#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 1000000
#define MG 10

struct Info {
  int iId;
  int itm;
  int igp[MG];
  struct Info *iprev;
  struct Info *inext;
};

struct Subscription {
  int sId;
  struct Subscription *snext;
};

struct Group {
  int gId;
  struct Subscription *ggsub;
  struct Info *gfirst;
  struct Info *glast;
};

struct SubInfo {
  int sId;
  int stm;
  struct Info *sgp[MG];
  struct SubInfo *next;
};

// Function prototypes of a double list typeof struct Info
void DL_Insert(struct Info **, struct Info **, int, int, int);
void DL_Remove(struct Info **, struct Info **, int);
void DL_LookUp(struct Info **, int);
void DL_Print(struct Info **);
void DL_Free(struct Info **);

// Function prototypes of a double list typeof struct Subscription
void L_Insert(struct Subscription **, int);
void L_Remove(struct Subscription **, int);
void L_LookUp(struct Subscription **, int);
void L_Print(struct Subscription **);
void L_Free(struct Subscription **);

// Function prototypes of a double list typeof struct SubInfo
void SL_Insert(struct SubInfo **, int, int);
void SL_Remove(struct SubInfo **, int);
void SL_LookUp(struct SubInfo **, int);
void SL_Print(struct SubInfo **);
void SL_Free(struct SubInfo **);

int main(int argc, char** argv) {
  FILE *fp = NULL;
  char *token, *search = " ";
  char line[LINE_LENGTH], event;
  int itm, iId, stm, sId;
  int gId, i, j;
  int tempIgp[MG], gId_sgp[MG];
  struct Group G[MG];
  struct SubInfo *head = NULL;

  struct Info *temp1 = NULL, *temp2 = NULL;
  struct SubInfo *tempSI = NULL, *tempSI2 = NULL;
  struct Subscription *tempS = NULL;

  if(argc < 2) {
    printf("\n Usage: %s <input-file>\n", argv[0]);
    return(EXIT_FAILURE);
  } else if((fp = fopen(argv[1], "r")) == NULL) {
    printf("\n Could not open file: %s\n", argv[1]);
    return(EXIT_FAILURE);
  }

  // Initialize the groups
  for(i = 0; i < MG; i++) {
    G[i].gId = i;
    G[i].gfirst = NULL;
    G[i].glast = NULL;
    G[i].ggsub = NULL;
  }

  // Read input file line-by-line and handle the events
  while(fgets(line, LINE_LENGTH, fp) != NULL) {
    // Uncomment the line below when in debug mode
    //printf("\n Event: %s ", line);

    switch(line[0]) {
    // Insert_Info event
    case 'I':
      sscanf(line, "%c %d %d", &event, &itm, &iId);
      // printf("\nEvent : %c itm : %d iId : %d ",event,itm,iId);
      token = strtok(line, search);
      token = strtok(NULL, search);
      token = strtok(NULL, search);

      for(i = 0; i < MG; i++) {
        tempIgp[i] = -1;
      }

      while((gId = atoi(token = strtok(NULL, search))) != -1) {
        // printf ("gId : %d ",gId);
        DL_Insert(&G[gId].gfirst, &G[gId].glast, itm, iId, gId);

        // Keeping all the gid that we read in a temp array
        tempIgp[gId] = gId;
      }

      // Insert all the gid that we read above into the temp igp array
      for(i = 0; i < MG; i++) {
        if(tempIgp[i] != -1) {
          temp1 = G[tempIgp[i]].gfirst;
          while(temp1 != NULL) {
            if(temp1->itm == itm) {
              for(j = 0; j < MG; j++) {
                if(tempIgp[j] != -1) {
                  temp1->igp[j] = tempIgp[j];
                }
              }
            }
            temp1 = temp1->inext;
          }
        }
      }

      // Print after the insertion
      printf("I<%d> <%d> DONE\n", itm, iId);
      for(i = 0; i < MG; i++) {
        if(G[i].gfirst != NULL) {
          printf("GROUPID = <%d> ", i);
          DL_Print(&G[i].gfirst);
          printf("\n");
          // L_Print (&G[i].ggsub);
        }
      }
      printf("\n");

      break;

    // Subscriber_Registration event
    case 'S':
      sscanf(line, "%c %d %d", &event, &stm, &sId);
      // printf("\nEvent : %c stm : %d sId : %d ",event,stm,sId);

      token = strtok(line, search);
      token = strtok(NULL, search);
      token = strtok(NULL, search);
      printf("\n");
      for(i = 0; i < MG; i++) {
        gId_sgp[i] = -1;
      }

      // Inserting the sid that we read from the file in the Subscription list.
      // We use an array to keep the gid that are useful to initialise the sgp.
      while((gId = atoi(token = strtok(NULL, search))) != -1) {
        L_Insert(&G[gId].ggsub, sId);
        gId_sgp[gId] = gId;
      }

      // Insert the sId that we read into the SubInfo list.
      SL_Insert(&head, sId, stm);

      // Insertions on the sgp array.
      for(tempSI = head; tempSI != NULL; tempSI = tempSI->next) {
        if(tempSI->stm == stm) {
          for(i = 0; i < MG; i++) {
            if(gId_sgp[i] != -1) {
              tempSI->sgp[gId_sgp[i]] = NULL;
            } else {
              tempSI->sgp[i] = 1;
            }
          }
        }
      }

      // Print the data after the insertions.
      printf("S<%d><%d>  ", stm, sId);
      for(i = 0; i < MG; i++) {
        if(gId_sgp[i] != -1) {
          printf("<%d>", gId_sgp[i]);
        }
      }
      printf(" DONE");

      SL_Print(&head);
      for(i = 0; i < MG; i++) {
        if(G[i].ggsub != NULL) {
          printf("GROUPID = <%d>, ", i);
          printf("SUBLIST = ");
          for(tempS = G[i].ggsub; tempS != NULL; tempS = tempS->snext) {
            printf("<%d>", tempS->sId);
          }
          printf("\n");
        }
      }
      printf("\n");
      break;

    // Consume event
    case 'C':
      sscanf(line, "%c %d", &event, &sId);
      // printf("\nEvent : %c sId : %d",event,sId);

      // Implementation of the consume functionality.
      // If we find the sid in the list, we are looking on the respective sgp
      // and in every group that sgp is interested to consume.
      printf("C<%d> DONE\n", sId);
      for(tempSI = head; tempSI != NULL; tempSI = tempSI->next) {
        // Node scanning (single list).
        if(tempSI->sId == sId) {
          // sId found and we are consuming it.
          for(i = 0; i < MG; i++) {
            // Iterating over sgp
            if(tempSI->sgp[i] == NULL) {
              // Interested for that gId
              tempSI->sgp[i] = G[i].gfirst;
              temp2 = G[i].gfirst;
              if(G[i].gfirst != NULL) {
                printf("GROUPID=<%d>, ", i);
                DL_Print(&G[i].gfirst);
              }
              tempSI->sgp[i] = temp2;
              printf(", NEWSGP=<%d>\n", G[i].glast->iId); // tempSI->sgp[i]->iId);
            }
          }
        }
      }
      printf("\n");
      break;

    // Delete_Subsciber event
    case 'D':
      sscanf(line, "%c %d", &event, &sId);
      // printf("\nEvent : %c sId : %d",event,sId);

      // Delete the sId form the Subscription list of every Group
      tempS = NULL;
      SL_Remove(&head, sId);
      for(i = 0; i < MG; i++) {
        if(G[i].ggsub != NULL) {
          L_Remove(&G[i].ggsub, sId);
        }
      }

      // Delete the sId from the SubInfo list
      printf("D<%d> DONE", sId);
      SL_Print(&head);
      for(i = 0; i < MG; i++) {
        if(G[i].ggsub != NULL) {
          printf("\nGROUPID = <%d>, ", i);
          L_Print(&G[i].ggsub);
        }
      }
      printf("\n");
      break;

    // Print event
    case 'P':
      sscanf(line, "%c", &event);
      // printf("\nEvent : %c ",event);

      // Print everything.
      printf("P DONE\n");
      for(i = 0; i < MG; i++) {
        if((G[i].gfirst != NULL) || (G[i].ggsub != NULL)) {
          printf("GROUPID = <%d>, ", i);
        }
        if(G[i].gfirst != NULL) {
          DL_Print(&G[i].gfirst);
        }
        if(G[i].ggsub != NULL) {
          printf(", ");
          L_Print(&G[i].ggsub);
          printf("\n");
        }

      }
      if(head != NULL) {
        printf("\nSUBSCRIBERLIST=");
        for(tempSI = head; tempSI != NULL; tempSI = tempSI->next) {
          printf("<%d>", tempSI->sId);
        }
        printf("\n");

        for(tempSI = head; tempSI != NULL; tempSI = tempSI->next) {
          printf("SUBSCRIBERID=<%d>, GROUPLIST=", tempSI->sId);

          for(i = 0; i < MG; i++) {
            if(tempSI->sgp[i] != 1) {
              printf("<%d>", i);
            }
          }
          printf("\n");
        }
      }
      break;

    default:
      // Uncomment the line below when in debug mode
      // printf("\n Ignoring line: %s", line);

      break;
    }
  }
  printf("\n");

  return (EXIT_SUCCESS);
}

// Double list functionalities
// typeof struct Info
void DL_Insert(struct Info **root, struct Info **last, int itm, int iId, int gId) {

  int i;
  struct Info *temp, *temp1, *temp2 = NULL;
  temp = (struct Info *) malloc(sizeof(struct Info));

  if(temp == NULL) {
    printf("Error allocating memory..\n");
    exit(0);
  }

  temp->iId = iId;
  temp->itm = itm;
  for(i = 0; i < MG; i++) {
    temp->igp[i] = -1;
  }

  if(*root == NULL) {
    temp->inext = NULL;
    temp->iprev = NULL;
    *root = temp;
    *last = temp;
  } else {
    for(temp2 = NULL, temp1 = *root; (temp1 != NULL) && (temp1->itm < itm); temp2 = temp1, temp1 = temp1->inext);

    if(temp1 == NULL) {
      temp->inext = NULL;
      temp->iprev = temp2;
      temp2->inext = temp;
      *last = temp;
    } else if(temp2 == NULL) {
      temp->inext = temp1;
      temp->iprev = NULL;
      temp1->iprev = temp;
      *root = temp;
    } else {
      temp->inext = temp1;
      temp->iprev = temp2;
      temp2->inext = temp;
      temp1->iprev = temp;
    }
  }
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
        temp2 = *root;
        if(temp2->inext == NULL) {
          free(temp2);
          *root = NULL;
          break;
        } else {
          temp2 = temp1->inext;
          temp2->iprev = NULL;
          *root = temp2;
          free(temp1);
          break;
        }
      } else if(temp1->inext == NULL) {
        temp2 = temp1->iprev;
        temp2->inext = NULL;
        *last = temp2;
        free(temp1);
        break;
      } else {
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
    printf("\nThe imt couldn't be deleted\n");
  } else {
    printf("\nThe deletion was succesful\n");
  }
}

void DL_LookUp(struct Info **root, int itm) {
  struct Info *temp;

  for(temp = *root; (temp != NULL) && (temp->itm < itm); temp = temp->inext);

  if((temp == NULL) || (temp->itm > itm)) {
    printf("\nThe itm %d didn't found!\n", itm);
  }
  else {
    printf("\nThe itm %d found!\n", itm);
  }
}

void DL_Print(struct Info **root) {
  struct Info *temp;
  int i;

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

// Simple linked list functionalities
// typeof struct Subscription
void L_Insert(struct Subscription **root, int sId) {
  struct Subscription *temp;

  temp = (struct Subscription *) malloc(sizeof(struct Subscription));

  if(temp == NULL) {
    printf("Error allocating memory..\n");
    exit(0);
  }
  else {
    temp->sId = sId;
    temp->snext = *root;
    *root = temp;
  }
}

void L_Remove(struct Subscription **root, int sId) {
  struct Subscription *temp1 = NULL, *temp2 = NULL, *temp3 = NULL;

  temp1 = *root;
  temp2 = NULL;
  while(temp1 != NULL) {
    if(temp1->sId == sId) {
      if(temp1 == *root) {
        temp3 = *root;
        if(temp3->snext == NULL) {
          *root = NULL;
          break;
        } else {
          *root = temp1->snext;
          free(temp1);
          break;
        }
      } else {
        temp2->snext = temp1->snext;
        temp1->snext = NULL;
        free(temp1);
        break;
      }
    }

    temp2 = temp1;
    temp1 = temp1->snext;
  }
}

void L_LookUp(struct Subscription **root, int sId) {
  struct Subscription *temp;
  int found;

  temp = *root;
  found = 0;
  while(temp != NULL) {
    if(temp->sId == sId) {
      found = 1;
      break;
    }
    temp = temp->snext;
  }

  if(found == 1) {
    printf("The sId: %d found!\n", sId);
  } else {
    printf("The sId wasn't found\n");
  }
}

void L_Print(struct Subscription **root) {
  struct Subscription *temp;
  printf("SUBLIST = ");
  for(temp = *root; temp != NULL; temp = temp->snext) {
    printf("<%d>", temp->sId);
  }
}

void L_Free(struct Subscription **root) {
  struct Subscription *temp1, *temp2;

  if(*root != NULL) {
    for(temp2 = *root, temp1 = temp2->snext; (temp1 != NULL); temp2 = temp1, temp1 = temp1->snext) {
      free(temp2);
    }
    free(temp2);
    *root = NULL;
  }
}

// Sorted linked list functionalities
// typeof struct SubInfo
void SL_Insert(struct SubInfo **root, int sId, int stm) {
  struct SubInfo *temp, *temp1, *temp2;
  int i;

  if(*root == NULL) {
    //printf ("Eimai miden o malakas\n");
    temp1 = (struct SubInfo *) malloc(sizeof(struct SubInfo));
    if(temp1 == NULL)
    {
      printf("Error allocating memory..\n");
      exit(0);
    }

    temp1->sId = sId;
    temp1->stm = stm;
    temp1->next = NULL;
    *root = temp1;
    for(i = 0; i < MG; i++) {
      temp1->sgp[i] = NULL;
    }
  } else {
    //printf ("Den eimai miden o malakas\n");
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

    for(i = 0; i < MG; i++) {
      temp->sgp[i] = NULL;
    }
  }
}

void SL_Remove(struct SubInfo **root, int sId) {
  struct SubInfo *temp1, *temp2;

  for(temp2 = NULL, temp1 = *root; (temp1 != NULL) && (temp1->sId < sId); temp2 = temp1, temp1 = temp1->next);

  if((temp1 == NULL) || (temp1->sId > sId)) {
    printf("\nThe amt couldn't be deleted\n");
  } else {
    if(temp2 == NULL) {
      *root = temp1->next;
    } else {
      temp2->next = temp1->next;
    }

    free(temp1);
  }
}


void SL_LookUp(struct SubInfo **root, int stm) {
  struct SubInfo *temp;

  for(temp = *root; (temp != NULL) && (temp->stm < stm); temp = temp->next);

  if((temp == NULL) || (temp->stm > stm)) {
    printf("\nThe stm %d didn't found!\n", stm);
  } else {
    printf("\nThe stm %d found!\n", stm);
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
