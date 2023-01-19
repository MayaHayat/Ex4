#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void addNewEdge(pnode start, pnode endPoint, int weight);
void removeExiting(pnode n);
void removeEdgesBetweenNodes(pnode NODE, pnode n);


//------------------HELP FUNCTIONS-------------


pnode createNewNodeNext(int num, pnode next){
    pnode newNode = (pnode) malloc(sizeof(node));
    if(newNode == NULL){
        printf("Error! Couldn't allocate space");
        return NULL;
    }   
    newNode ->node_num = num;
    newNode->next = next;
    newNode ->edges = NULL;
    return newNode;
}

pedge createNewEdge(int weight, pnode endPoint, pedge nextEdge){
    pedge newEdge = (pedge)malloc(sizeof(edge));
    if (newEdge == NULL){
        printf("couldn't allocate space!");
        return NULL;
    }
    newEdge->next = nextEdge;
    newEdge->endpoint = endPoint;
    newEdge->weight = weight;

    return newEdge;
}


void addNewEdge(pnode start, pnode endPoint, int weight){
    if (start !=NULL && endPoint != NULL){
        pedge new_edge = createNewEdge(weight, endPoint, NULL);
        pedge iteratingEdge = start->edges;
        while (iteratingEdge != NULL && iteratingEdge->next !=NULL){
            iteratingEdge = iteratingEdge->next;
        }
        if (iteratingEdge == NULL){
            start->edges = new_edge;
            return;
        }
        iteratingEdge->next = new_edge;
    }
}

pnode findNode(pnode find, int num){
    while (find && find->node_num != num){
        find = find->next;
    }
    if (find == NULL){
        return NULL;
    }
    return find;
}

void removeOneEdgeEntring(pnode first, pnode second){
    pedge *previous = &first->edges;
    pedge p = first->edges;
    while (p != NULL){
    if (p->endpoint == second){
            *previous = p->next;
            free(p);
            p = *previous;
        }
    else{
        previous = &(p->next);
        p = p->next;            
        }
    }
}

void removeExiting(pnode n){
    pedge current = n->edges;
    while (current){
        //Removes all edges going out from node.
        pedge temp = current;
        current = current->next;
        free(temp);
    }
}

void removeEdgesBetweenNodes(pnode first, pnode second){
    if (first == NULL){
        return;
    }
    while (first != NULL) {
        removeOneEdgeEntring(first, second);
        first = first->next;
    }
    removeExiting(second);
}


void printGraph_cmd(pnode head) {
    pnode iterating = head;
    pedge currentEdge = NULL;

    while(iterating != NULL) {
        printf("NodeNum:  %d { Edges:\t ,", iterating->node_num);
        currentEdge = NULL;
        currentEdge = iterating->edges;
        while(currentEdge != NULL) {
            printf("endPoint = %d, weight = %d , ", currentEdge->endpoint->node_num, currentEdge->weight);
            currentEdge = currentEdge->next;
        }
        printf("}\n");
        iterating = iterating->next;
    }
    printf("\n");
}

int *deletePlace(int old[], int length, int num){
    int *newArray = (int*)malloc(sizeof(int)*length-1);
    if (newArray == NULL){
        printf("Error! couldn't allocate space.");
        return NULL;
    }
    for (int i = 0; i < num; i++){
            newArray[i] = old[i];
    }
    for (int i = num+1 ; i < length ; i++){
        newArray[i-1]= old[i];
    }
    
    return newArray;
}

int findEmpty(int visited[], int size){
    int count =0;
    while (count < size){
        if (visited[count] == 0){
            return 0;
        }
        count++;
    }
    return count;
}

pnode getHead(int num){
    pnode head = NULL;
    int count = num;
    while (count >= 0){
        head = createNewNodeNext(count,head);
        count--;
    }
    return head;
}


//---------------NEED TO USE FUNCTIONS----------------------


void deleteGraph_cmd(pnode *head){
    while (*head){
        pedge temp = (*head)->edges;
        while (temp){
            pedge next = temp->next;
            free(temp);
            temp = next;
        }
        pnode tempNode = (*head);
        *head= (*head)->next;
        free(tempNode);
    }
    *head = NULL;
}

void build_graph_cmd(pnode *head){
    int num= -1;
    pedge prev = NULL;
    scanf("%d", &num);
    pnode current = findNode(*head, num);
    while(scanf("%d", &num)==1){
        pnode endPoint = findNode(*head, num);
        scanf("%d", &num);
        prev = createNewEdge(num,endPoint,prev);
    }
    current->edges = prev;
}


void insert_node_cmd(pnode *head){
    int num, weight, endPoint;
    pnode previous = *head;
    scanf("%d", &num);

    pnode new_node = findNode(*head, num);
    int check = 0;

    if (new_node == NULL){
        new_node = createNewNodeNext(num, NULL);
    }
    else{
        check = 1;
        removeExiting(new_node);
        new_node->edges = NULL;
    }
    while (scanf("%d", &endPoint) > 0){
        scanf("%d", &weight);
        addNewEdge(new_node, findNode(*head, endPoint), weight);
    }

    if (check == 1 || *head == NULL){
        if (*head == NULL){
            *head = new_node;
            return;
        }
        return;
    }
    while (previous->next){
        previous= previous->next;
    }
    previous->next = new_node;
}

void delete_node_cmd(pnode *head, int num){
    pnode temp = *head;
    pnode *previous = head;
    while (temp != NULL){
        if (temp->node_num != num){
            previous = &(temp ->next);
            temp = temp->next;   
        }
        else{
            break;
        }
    }
    if (temp ==NULL){
        return;
    }
    removeEdgesBetweenNodes(*head, temp);
    *previous = temp->next;
    free(temp);
}