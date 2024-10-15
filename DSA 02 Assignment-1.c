#include <stdio.h>
#include <stdlib.h>

#define MAX_FLOORS 10

struct Node {
    int floor;
    struct Node* next;
};
struct Node* createNode(int floor) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->floor = floor;
    newNode->next = NULL;
    return newNode;
}
void enqueue(struct Node** rear, struct Node** front, int floor) {
    struct Node* newNode = createNode(floor);
    if (*rear == NULL) {
        *front = *rear = newNode;
        return;
    }
    (*rear)->next = newNode;
    *rear = newNode;
}

int dequeue(struct Node** front) {
    if (*front == NULL) {
        printf("No floor requests.\n");
        return -1;
    }
    struct Node* temp = *front;
    int floor = temp->floor;
    *front = (*front)->next;
    if (*front == NULL)
        *front = NULL;
    free(temp);
    return floor;
}

void displayQueue(struct Node* front) {
    if (front == NULL) {
        printf("No pending floor requests.\n");
        return;
    }
    printf("Pending floors: ");
    while (front != NULL) {
        printf("%d ", front->floor);
        front = front->next;
    }
    printf("\n");
}

int main() {
    struct Node* front = NULL;
    struct Node* rear = NULL;
    int currentFloor = 0, choice, floor;

    do {
        printf("\nLift is at floor %d.\n", currentFloor);
        printf("1. Request a floor\n2. Move the lift\n3. Display pending requests\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the floor number (0-%d): ", MAX_FLOORS);
                scanf("%d", &floor);
                if (floor >= 0 && floor <= MAX_FLOORS) {
                    enqueue(&rear, &front, floor);
                } else {
                    printf("Invalid floor number!\n");
                }
                break;
            case 2:
                floor = dequeue(&front);
                if (floor != -1) {
                    printf("Moving lift to floor %d...\n", floor);
                    currentFloor = floor;
                }
                break;
            case 3:
                displayQueue(front);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}

