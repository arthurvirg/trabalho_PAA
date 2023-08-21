#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

#define MAX_ROOMS 100
#define MAX_QUERIES 20

double distance_with_ventilation;
double distance_without_ventilation;
bool visited[MAX_ROOMS];

int minDistance(double distance[], int n, bool visited[]) {
    double min = DBL_MAX;
    int minIndex;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && distance[i] <= min) {
            min = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

double dijkstra(double graph[MAX_ROOMS][MAX_ROOMS], int src, int n, int menorDist) {
    double distance[n];
    bool visited[n];
    
    for (int i = 0; i < n; i++) {
        distance[i] = DBL_MAX;
        visited[i] = false;
    }

    distance[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(distance, n, visited);
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != DBL_MAX && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    return distance[menorDist];
}

int main() {
    int M, E, N, C;
    scanf("%d %d %d %d", &M, &E, &N, &C);

    double graph_with_ventilation[MAX_ROOMS][MAX_ROOMS] = {0};
    double graph_without_ventilation[MAX_ROOMS][MAX_ROOMS] = {0};

    for (int i = 0; i < E; i++) {
        int u, v;
        double d;
        scanf("%d %d %lf", &u, &v, &d);
        graph_without_ventilation[u][v] = graph_without_ventilation[v][u] = d;
        graph_with_ventilation[u][v] = graph_with_ventilation[v][u] = d;
    }
   
    for (int j = 0; j < N; j++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph_with_ventilation[a][b] = graph_with_ventilation[b][a] = 1.0; // Considerando túneis/ventilações como arestas de tempo 1
    }
    
    int src = 0;

    for (int i = 0; i < C; i++){
        int impostor;
        scanf("%d", &impostor);
        
        distance_with_ventilation = dijkstra(graph_with_ventilation, src, M, impostor);
        distance_without_ventilation = dijkstra(graph_without_ventilation, src, M, impostor);

        //printf("%.1f | %.1f ", distance_without_ventilation, distance_with_ventilation);

        if (distance_without_ventilation <= distance_with_ventilation ||
            distance_without_ventilation == distance_with_ventilation) {
            printf("victory\n");
        } else {
            printf("defeat\n");
        }
    }

    return 0;
}