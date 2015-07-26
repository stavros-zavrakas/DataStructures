#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 1000000
#define HASH_MULTIPLIER 65599
#define MG 5

struct Info {
  int iId;
  int itm;
  int igp[MG];
  struct Info *ilc;
  struct Info *irc;
  struct Info *ip;
};
typedef struct Info * Info;

struct Subscription {
  int sId;
  struct Subscription *snext;
};

struct SubInfo {
  int sId;
  int stm;
  struct TreeInfo *tgp[MG];
  struct TreeInfo *sgp[MG];
  struct SubInfo *snext;
};

struct TreeInfo {
  int tId;
  int ttm;
  struct TreeInfo *tlc;
  struct TreeInfo *trc;
  struct TreeInfo *tp;
  struct TreeInfo *next;
};

struct Group {
  int gId;
  struct Subscription *ggsub;
  struct Info *gtree;
};

struct SubInfo **table;

// Binary tree function prototypes
void BT_Insert(struct Info **, int, int, int);
void BT_Print(struct Info **);

// Hash table function prototypes
int HT_HashFunction(int sId, int hashSize);
void HT_Insert(struct SubInfo **temp1, int hash_num, int hashSize);
void HT_Remove(int sId, int hashSize);
void HT_Print(int hashSize);
void HT_Free(int hashSize);

// Linked list function prototypes
void L_Insert(struct Subscription **, int);
void L_Remove(struct Subscription **, int);
void L_LookUp(struct Subscription **, int);
void L_Print(struct Subscription **);
void L_Free(struct Subscription **);

int main(int argc, char** argv) {
  FILE *fp = NULL;
  char *token, *search = " ";
  char line[LINE_LENGTH], event;
  int itm, iId, stm, sId;
  int gId;
  int i, j, m;
  int hashNum, hashSize, p;
  int gId_sgp[MG];
  struct Group G[MG];
  struct SubInfo *temp;
  struct SubInfo *tempSI = NULL, *tempSI2 = NULL;
  struct Subscription *tempS = NULL;

  if(argc < 4) {
    printf("\n Usage: %s <m> <p> <input-file>\n", argv[0]);
    return(EXIT_FAILURE);
  }

  hashSize = atoi(argv[1]);
  p = atoi(argv[2]);
  if((hashSize <= 0) || (p <= 0)) {
    printf("The program can not run without invalid hash table arguments.\n");
    return(EXIT_FAILURE);
  }

  table = malloc(hashSize * sizeof(struct SubInfo*));
  for(i = 0; i < hashSize; i++) {
    table[i] = NULL;
  }

  // Open input file
  if((fp = fopen(argv[3], "r")) == NULL)
  {
    printf("\n Could not open file: %s\n", argv[2]);
    return(EXIT_FAILURE);
  }

  // Read input file line-by-line and handle the events
  while(fgets(line, LINE_LENGTH, fp) != NULL) {
    // Uncomment the line below when in debug mode
    //printf("\n Event: %s ", line);

    switch(line[0]) {
    // Insert_Info event
    case 'I':
      sscanf(line, "%c %d %d", &event, &itm, &iId);

      token = strtok(line, search);
      token = strtok(NULL, search);
      token = strtok(NULL, search);
      while((gId = atoi(token = strtok(NULL, search))) != -1) {
        BT_Insert(&G[gId].gtree, itm, iId, gId);
      }

      printf("\nI <%d><%d> DONE", itm, iId);
      for(i = 0; i < MG; i++) {
        if(G[i].gtree != NULL) {
          printf("\n\tGROUPID = <%d>, INFOLIST = ", i);
          BT_Print(&G[i].gtree);
        }
      }
      printf("\n");

      break;

    // Subscriber_Registration event
    case 'S':
      sscanf(line, "%c %d %d", &event, &stm, &sId);

      token = strtok(line, search);
      token = strtok(NULL, search);
      token = strtok(NULL, search);

      for(i = 0; i < MG; i++) {
        gId_sgp[i] = -1;
      }

      while((gId = atoi(token = strtok(NULL, search))) != -1) {
        L_Insert(&G[gId].ggsub, sId);
        gId_sgp[gId] = gId;
      }

      // Insert the sId that we just read into the hash table
      temp = (struct SubInfo *) malloc(sizeof(struct SubInfo));
      temp->sId = sId;
      temp->stm = stm;
      hashNum = HT_HashFunction(temp->sId, hashSize);
      HT_Insert(&temp, hashNum, hashSize);

      // Insert the gIds to the sgp array
      for(i = 0; i < hashSize; i++) {
        if(table[i] != NULL) {
          tempSI = table[i];
          while(tempSI != NULL) {
            if(tempSI->stm == stm) {
              for(j = 0; j < MG; j++) {
                if(gId_sgp[j] != -1) {
                  tempSI->sgp[gId_sgp[j]] = NULL;
                }
                else {
                  tempSI->sgp[j] = 1;
                }
              }
            }
            tempSI = tempSI->snext;
          }
        }
      }

      // Print the data just after the data insertion
      printf("\nS<%d><%d>  ", stm, sId);
      for(i = 0; i < MG; i++) {
        if(gId_sgp[i] != -1) {
          printf("<%d>", gId_sgp[i]);
        }
      }
      printf(" DONE");

      HT_Print(hashSize);

      for(i = 0; i < MG; i++) {
        if(G[i].ggsub != NULL) {
          printf("\tGROUPID = <%d>, ", i);
          L_Print(&G[i].ggsub);
        }
      }
      break;

    // Prune event
    // @todo: not implemented yet
    case 'R':
      sscanf(line, "%c %d", &event, &itm);
      break;

    // Consume event
    // @todo: not implemented yet
    case 'C':
      sscanf(line, "%c %d", &event, &sId);
      break;

    // Delete_Subsciber event
    case 'D':
      sscanf(line, "%c %d", &event, &sId);

      HT_Remove(sId, hashSize);
      for(i = 0; i < MG; i++) {
        if(G[i].ggsub != NULL) {
          L_Remove(&G[i].ggsub, sId);
        }
      }

      printf("D<%d> DONE", sId);
      HT_Print(hashSize);
      for(i = 0; i < MG; i++) {
        if(G[i].ggsub != NULL) {
          printf("\tGROUPID = <%d>, ", i);
          L_Print(&G[i].ggsub);
        }
      }
      printf("\n");
      break;

    // Print event
    case 'P':
      sscanf(line, "%c", &event);

      printf("\nP DONE\n");
      for(i = 0; i < MG; i++) {
        if((G[i].gtree != NULL) || (G[i].ggsub != NULL)) {
          printf("\tGROUPID = <%d>, ", i);
        }
        if(G[i].gtree != NULL) {
          printf("INFOLIST = ");
          BT_Print(&G[i].gtree);
        }
        if(G[i].ggsub != NULL) {
          printf(", ");
          L_Print(&G[i].ggsub);
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

// Binary tree function implementations.

// Insert on double linked binary tree
void BT_Insert(Info *pt, int itm, int iId, int gId) {
  Info t;
  t = *pt;
  if(t == NULL) {
    t = (struct Info *) malloc(sizeof(struct Info));
    t->itm = itm;
    t->iId = iId;
    t->ip = NULL;
    t->ilc = NULL;
    t->irc = NULL;
  } else {
    if(itm < t->itm) {
      BT_Insert(&(t->ilc), itm, iId, gId);
    } else {
      BT_Insert(&(t->irc), itm, iId, gId);
    }
  }
  *pt = t;
}

// Print the binary tree (inorder)
void BT_Print(Info *pt) {
  struct Info *t;
  t = *pt;

  if(t != NULL) {
    BT_Print(&t->ilc);
    printf("<%d>", t->iId);
    BT_Print(&t->irc);
  }
}

// Hash table function implementations.

// Generates a random hash number
int HT_HashFunction(int sId, int hashSize) {
  int i;
  int hash = 0;

  for(i = 0; i < sId; i++) {
    hash = hash * HASH_MULTIPLIER + hashSize;
  }

  hash = abs(hash) % hashSize;
  return hash;

}

// Insert a node in the hash table
void HT_Insert(struct SubInfo **root, int hash_num, int hashSize) {
  struct SubInfo *temp = *root;
  int i;

  if(table[hash_num] == NULL) {
    // The list of that specific field of the hash table is still empty
    table[hash_num] = temp;
    temp->snext = NULL;
  } else {
    // The list of that specific field of the hash table has already some items.
    temp->snext = table[hash_num];
    table[hash_num] = *root;
  }
}

// Delete a node from the hash table
void HT_Remove(int sId, int hashSize) {
  int i, deleted = 0;
  struct SubInfo *iterator, *temp1, *temp2;

  for(i = 0; i < hashSize; i++) {
    if(table[i] != NULL) {
      iterator = table[i];
      temp1 = NULL;
      while(iterator != NULL) {
        if(iterator->sId == sId) {
          if(iterator == table[i]) {
            temp1 = table[i]->snext;
            table[i] = temp1;
            free(iterator);
            deleted = 1;
            break;
          } else if(iterator->snext == NULL) {
            free(iterator);
            temp1->snext = NULL;
            deleted = 1;
            break;
          } else {
            temp2 = iterator->snext;
            free(iterator);
            temp1->snext = temp2;
            deleted = 1;
            break;
          }
        }
        temp1 = iterator;
        iterator = iterator->snext;
      }
    }

    if(deleted == 1) {
      break;
    }
  }
}

// Print hash table data
void HT_Print(int hashSize) {
  struct SubInfo *iterator;
  int i;

  printf("\n\tSUBSCRIBERLIST = ");
  for(i = 0; i < hashSize; i++) {
    if(table[i] != NULL) {
      iterator = table[i];
      while(iterator != NULL) {
        printf("<%d>", iterator->sId);
        iterator = iterator->snext;
      }
    }
  }
  printf("\n");
}

// Free the hash table memory
void HT_Free(int hashSize) {
  struct SubInfo *temp1, *temp2;
  int i;

  for(i = 0; i < hashSize; i++) {
    if(table[i] != NULL) {
      temp1 = table[i];
      while(temp1 != NULL) {
        temp2 = temp1;
        temp1 = temp1->snext;
        free(temp2);
      }
    }
  }

}

// Linked list function implementations.

// Insert a node to the list
void L_Insert(struct Subscription **root, int sId) {
  struct Subscription *temp;

  temp = (struct Subscription *) malloc(sizeof(struct Subscription));

  if(temp == NULL) {
    printf("Error allocating memory.\n");
    exit(0);
  } else {
    temp->sId = sId;
    temp->snext = *root;
    *root = temp;
  }
}

// Remove a node from the list
void L_Remove(struct Subscription **root, int sId) {
  struct Subscription *iterator = NULL, *temp1 = NULL, *temp2 = NULL;

  iterator = *root;
  temp1 = NULL;
  while(iterator != NULL) {
    if(iterator->sId == sId) {
      if(iterator == *root) {
        temp2 = *root;
        if(temp2->snext == NULL) {
          *root = NULL;
          break;
        } else {
          *root = iterator->snext;
          free(iterator);
          break;
        }
      } else {
        temp1->snext = iterator->snext;
        iterator->snext = NULL;
        free(iterator);
        break;
      }
    }
    temp1 = iterator;
    iterator = iterator->snext;
  }
}

// LookUp a node in the list
void L_LookUp(struct Subscription **root, int sId) {
  struct Subscription *iterator;
  int found;

  iterator = *root;
  found = 0;
  while(iterator != NULL) {
    if(iterator->sId == sId) {
      found = 1;
      break;
    }
    iterator = iterator->snext;
  }

  if(found == 1) {
    printf("sId: %d found.\n", sId);
  } else {
    printf("Unable to find sId: %d\n", sId);
  }
}

// Print the elements of the list
void L_Print(struct Subscription **root) {
  struct Subscription *iterator;
  printf("SUBLIST = ");
  for(iterator = *root; iterator != NULL; iterator = iterator->snext) {
    printf("<%d>", iterator->sId);
  }
  printf("\n");
}

// Free the memory of the list
void L_Free(struct Subscription **root) {
  struct Subscription *iterator, *temp;

  if(*root != NULL) {
    for(temp = *root, iterator = temp->snext; (iterator != NULL); temp = iterator, iterator = iterator->snext) {
      free(temp);
    }
    free(temp);
    *root = NULL;
  }
}
