#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1000000
#define MG 10
#define SGP_AS_STRUCT TRUE

#include "../../doubleLinkedList/doubleLinkedList.h"
#include "../../linkedList/linkedList.h"
#include "../../sortedLinkedList/sortedLinkedList.h"

struct Group {
  int gId;
  struct Subscription *ggsub;
  struct Info *gfirst;
  struct Info *glast;
};

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
        DL_Insert(&G[gId].gfirst, &G[gId].glast, itm, iId);

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
