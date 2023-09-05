#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure of a node in the linked list
struct node {
    int data;
    struct node *next;
};

// Define the structure of the circular queue
struct Queue {
    struct node *front;  // Pointer to the front of the queue
    struct node *rear;   // Pointer to the rear of the queue
};

// Function to create a new node with given data
struct node* newNode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));  // Allocate memory for the new node
    temp->data = data;  // Set the data of the node
    temp->next = NULL;  // Set the next pointer of the node to NULL
    return temp;  // Return the new node
}

// Function to create a new empty queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));  // Allocate memory for the new queue
    q->front = q->rear = NULL;  // Set both front and rear pointers to NULL to indicate an empty queue
    return q; // Return the new queue
}

// Function to add an element to the queue (enqueue operation)
void enqueue(struct Queue* q, int data, FILE* output) {
    struct node* temp = newNode(data);  // Create a new node with the given data

    if (q->rear == NULL) {  // If the queue is empty
    q->front = q->rear = temp;  // Set both front and rear pointers to the new node
    q->rear->next = q->front;  // Set the next pointer of the rear node to the front node, making it circular
    } else {
      q->rear->next = temp;  // Set the next pointer of the current rear node to the new node
      q->rear = temp;  // Update the rear pointer to the new node
      q->rear->next = q->front;  // Set the next pointer of the rear node to the front node, making it circular
   }

   fprintf(output, "Inserted value: %d\n", data);  // Print the inserted value to the output file

}

// Function to remove an element from the queue (dequeue operation)
void dequeue(struct Queue* q, FILE* output) {
    if (q->front == NULL) {
        fprintf(output, "Queue is Empty\n");  // Print "Queue is Empty" to the output file
        return;
    }

   if (q->front == q->rear) {  // If there is only one node in the queue
    fprintf(output, "deleted value: %d\n", q->front->data);  // Print the deleted value to the output file
    free(q->front);  // Free the memory allocated for the front node
    q->front = q->rear = NULL;  // Set both front and rear pointers to NULL to indicate an empty queue
} else {
    fprintf(output, "deleted value: %d\n", q->front->data);  // Print the deleted value to the output file
    struct node* temp = q->front;  // Create a temporary node and set it to the front node
    q->front = q->front->next;  // Update the front pointer to the next node
    q->rear->next = q->front;  // Set the next pointer of the rear node to the front node, maintaining circularity
    free(temp);  // Free the memory allocated for the front node
}

}

// Function to display the contents of the queue
void display(struct Queue* q, FILE* output) {
    struct node* current = q->front;   // Initialize a pointer to the front of the queue
    if (current == NULL) {  // If the queue is empty
        fprintf(output, "Queue is Empty\n");  // Print "Queue is Empty" to the output file
        return;
    }

   fprintf(output, "Elements of the queue: "); // Print "Elements of the queue: " to the output file
do {
    fprintf(output, "%d", current->data);  // Print the data of the current node to the output file
    current = current->next;  // Move the current pointer to the next node
    if (current != q->front) {  // If the current node is not the front node
        fprintf(output, " ");  // Print a space to separate the elements
    }
} while (current != q->front);  // Repeat until we reach the front node again (circular queue)
fprintf(output, "\n");  // Print a newline character to the output file

}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s input_file\n", argv[0]); // Print the correct usage of the program
        return 1;  // Exit the program with an error status
    }

    FILE *input, *output;
    input = fopen(argv[1], "r"); // Open the input file in read mode
    output = fopen("output.txt", "w"); // Open the output file in write mode

   if (input == NULL) {
       printf("Unable to open input file\n"); // Print an error message if the input file cannot be opened
       return 1; // Exit the program with an error status
   }

   if (output == NULL) {
       printf("Unable to open output file\n"); // Print an error message if the output file cannot be opened
       return 1; // Exit the program with an error status
   }

   struct Queue* q = createQueue(); // Create a new empty queue
   char op[10]; // Variable to store the operation (enqueue, dequeue, or display)
   int data; // Variable to store the data value

   while (fscanf(input, "%s", op) != EOF) { // Read the operation from the input file until the end of file
       if (strcmp(op, "enqueue") == 0) { // If the operation is enqueue
           fscanf(input, "%d", &data); // Read the data value from the input file
           enqueue(q, data, output); // Enqueue the data value into the queue
       } else if (strcmp(op, "dequeue") == 0) { // If the operation is dequeue
           dequeue(q, output); // Dequeue an element from the queue
       } else if (strcmp(op, "display") == 0) { // If the operation is display
           display(q, output); // Display the contents of the queue
       } else {
         fprintf(output, "Invalid operation: %s\n", op); // Print an error message for an invalid operation
       }
}

fclose(input); // Close the input file
fclose(output); // Close the output file
return 0; // Exit the program with a success status

}
