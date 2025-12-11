//Write a program to simulate Nondeterministic Finite Automata (NFA)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int row = 0;

struct node {
    int data;
    struct node* next;
    char edgetype;
} typedef node;

// Add edge to adjacency list
node* push(node* first, char edgetype, int data) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->edgetype = edgetype;
    new_node->data = data;
    new_node->next = NULL;

    if (first == NULL) return new_node;

    first->next = push(first->next, edgetype, data);
    return first;
}

// NFA recursive acceptance check
int nfa(node** graph, int current, char* input, int* accept, int start) {
    if (start == (int)strlen(input))
        return accept[current];

    node* temp = graph[current];
    while (temp != NULL) {
        if (input[start] == temp->edgetype)
            if (nfa(graph, temp->data, input, accept, start + 1))
                return 1;
        temp = temp->next;
    }
    return 0;
}

// Generate all binary strings of size n
void generate(char** arr, int size, char* a) {
    if (size == 0) {
        strcpy(arr[row++], a);
        return;
    }

    char temp0[20], temp1[20];
    strcpy(temp0, a);
    strcpy(temp1, a);

    strcat(temp0, "0");
    strcat(temp1, "1");

    generate(arr, size - 1, temp0);
    generate(arr, size - 1, temp1);
}

int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    node* graph[n + 1];
    for (int i = 0; i <= n; i++) graph[i] = NULL;

    int accept[n + 1];
    for (int i = 0; i <= n; i++) accept[i] = 0;

    printf("Enter NFA transitions (index accept number_of_edges edge node ...):\n");
    for (int i = 0; i < n; i++) {
        int index, acc, number_nodes;
        scanf("%d%d%d", &index, &acc, &number_nodes);
        accept[index] = acc;

        for (int j = 0; j < number_nodes; j++) {
            int edge, node_add;
            scanf("%d%d", &edge, &node_add);
            graph[index] = push(graph[index], '0' + edge, node_add);
        }
    }

    printf("\n==================== INPUT DONE ====================\n\n");
    printf("Accepted strings by NFA:\n");

    int size = 1;
    int count = 0;

    if (accept[1] == 1) { // Check for empty string
        printf("e\n");
        count++;
    }

    while (count < 10) {
        int power = (int)pow(2, size);
        char** arr = (char**)malloc(power * sizeof(char*));
        for (int i = 0; i < power; i++)
            arr[i] = (char*)malloc((size + 1) * sizeof(char));

        char a[20] = "";
        row = 0;
        generate(arr, size, a);

        for (int i = 0; i < power; i++) {
            char input[20] = "";
            strcpy(input, arr[i]);

            int result = nfa(graph, 1, input, accept, 0);
            if (result == 1) {
                printf("%s\n", input);
                count++;
            }
            if (count == 10) break;
        }

        for (int i = 0; i < power; i++) free(arr[i]);
        free(arr);

        size++;
        row = 0;
    }

    return 0;
}
