#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

// -----------------HELP FUNCTIONS --------------
int shortsPath_cmd(pnode head, int start, int endPoint);

int min(int distance[], int visited[], int length){
    int ans = -1;
    int count= 0;
    while (count < length){
        if ((distance[count] != INT_MAX) && (visited[count]==0)){
            if (ans == -1 || distance[count] < distance[ans]){
                ans = count;
            }
        }
        count++;
    }
    return ans;
}


int tsp(pnode head, int start, int arr[], int length){
    int count = 0;
    int currAns = INT_MAX;
    if (length == 1)
        return shortsPath_cmd(head, start, arr[length-1]);
    while (count < length){
        if (count != start){
            int *p = deletePlace(arr, length, count);
            if (shortsPath_cmd(head, start, arr[count]) != -1 && tsp(head, arr[count], p, length - 1) != -1 && tsp(head, arr[count], p, length - 1) + shortsPath_cmd(head, start, arr[count]) < currAns)
                currAns = tsp(head, arr[count], p, length - 1) + shortsPath_cmd(head, start, arr[count]);
            free(p);
        }
        count++;
    }
    if (currAns != INT_MAX)
        return currAns;
    return -1;
}

// ------------------------ FUNCTIONS--------------------


int TSP_cmd(pnode head){
    int length, count, current;
    int currAns = INT_MAX;
    scanf("%d", &length);
    int *arr = (int *)malloc(sizeof(int) * length);
    if (arr == NULL){
        printf("Error! couldn't allocate space.");
        exit(0);
    }
        
    count = 0;
    //Filling in the array with all nodes.
    while (count < length){
        scanf("%d", &current);
        arr[count] = current;
        count++;
    }
    count =0;
    // Goes through the array and checks if we can decrease the current distance
    while (count < length){
        int *pointer = deletePlace(arr, length, count);
        int temp = tsp(head, arr[count], pointer, length - 1);
        if (temp != -1 && currAns > temp){
            currAns = temp;
        }
        count++;
        free(pointer);
    }
    free(arr);
    if (currAns == INT_MAX){
        return -1;
    }
    return currAns;
}


int shortsPath_cmd(pnode head, int start, int endPoint){
    int currAns, count, ans;
    pnode temp = head;
    int max = temp ->node_num;
    while (temp != NULL){
        if (temp->node_num > max){
            max = temp->node_num;
        }
        temp = temp->next;
    }
    max++;
    int *visited = (int*)malloc(sizeof(int) * max);
    if (visited == NULL){
        printf("Error! couldn't allocate space.");
        exit(0);
    }
    count = 0;
    while (count < max){
        visited[count] = 0;
        if (findNode(head, count) == NULL)
            visited[count] = 1;
        count ++;
    }
    int *distance = (int*)malloc(sizeof(int) * max);
    if (distance == NULL){
        printf("Error! couldn't allocate space.");
        exit(0);
    }
    count = 0;
    //Makes all distances = max int (aka infinity)
    while (count < max){
        distance[count] = INT_MAX;
        count++;
    }
    // Distance from node to self
    distance[start] = 0;

    //While not all nodes have been visited and min distance isn't updated:
    while ((findEmpty(visited, max)== 0) && (currAns = min(distance, visited, max)) != -1){
        pnode temp = findNode(head, currAns);
        pedge tempedge = temp->edges;
        while (tempedge != NULL){
            if (visited[tempedge->endpoint->node_num]==0){
                //is a node's distance is max(meaning it hasn't been visited), and distance is bigger than new distance found, update distance
                if (distance[temp->node_num] != INT_MAX && distance[temp->node_num] + tempedge->weight < distance[tempedge->endpoint->node_num]){
                    distance[tempedge->endpoint->node_num] = distance[temp->node_num] + tempedge->weight;
                }
            }
            tempedge = tempedge->next;
        }
        //Node has been visited
        visited[currAns] = 1;
    }
    free(visited);

    if (distance[endPoint] != INT_MAX){
        ans = distance[endPoint];
        free(distance);
    }
    else{
        free(distance);
        ans = -1;
    }
    return ans;
}