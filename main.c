#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"


int main(){
    char choice;
    int answer1, answer2;
    pnode head = NULL;
    while(scanf("%c", &choice)!=EOF){
        switch(choice) {
            case 'A':
                int getH;
                deleteGraph_cmd(&head);
                scanf("%d", &getH);
                head = getHead(getH);
                break;
            case 'n':
                build_graph_cmd(&head);
                break;
            case 'B':
                insert_node_cmd(&head);
                break;
            case 'D':
                int num = -1;
                scanf("%d", &num);
                delete_node_cmd(&head, num);
                break;
            case 'S':
                int start, endPoint;
                scanf("%d %d", &start, &endPoint);
                answer1 = shortsPath_cmd(head, start, endPoint);
                printf("Dijsktra shortest path: %d \n", answer1);
                break;
            case 'T':
                answer2 = TSP_cmd(head);
                printf("TSP shortest path: %d \n", answer2);
                break;
            default:
                break;
        }
    }
    deleteGraph_cmd(&head);
    return 0;
}