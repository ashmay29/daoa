#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 5

// Function to print the Minimum Spanning Tree (MST)
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to find the vertex with the minimum key value, from the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1; // Initialize min_index
    for (int v = 0; v < V; v++) {
        // If vertex v is not yet included in MST and its key value is less than current min
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void primMST(int graph[V][V]) {
    int parent[V]; // Array to store constructed MST
    int key[V]; // Key values used to pick minimum weight edge in cut
    bool mstSet[V]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE and mstSet[] as false
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < V; v++) {
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    // Print the constructed MST
    printMST(parent, graph);
}

int main() {
    // Graph represented using adjacency matrix
    int graph[V][V] = {
        {0, 1, 2, 0, 0},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 6, 5},
        {0, 3, 6, 0, 4},
        {0, 0, 5, 4, 0}
    };

    // Print the MST
    primMST(graph);
    return 0;
}
