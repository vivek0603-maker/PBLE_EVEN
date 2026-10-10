#include <stdio.h>
#include <string.h>

#define MAX 20
#define INF 999999

int n = 0, start = -1, done = 0;
char place[MAX][50];
int graph[MAX][MAX];
int distance[MAX], previous[MAX], visited[MAX];

void inputGraph()
{
    int count;

    printf("Enter number of locations: ");

    if (scanf("%d", &count) != 1 || count < 1 || count > MAX) {
        printf("Invalid input!\n");
        n = 0;
        start = -1;
        done = 0;
        return;
    }

    n = count;
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Enter location %d: ", i + 1);

        if (fgets(place[i], 50, stdin) == NULL) {
            place[i][0] = '\0';
        }

        place[i][strcspn(place[i], "\n")] = '\0';

        if (place[i][0] == '\0')
            sprintf(place[i], "Location%d", i + 1);
    }

    printf("\nEnter distances (-1 for no connection):\n");

    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;

        for (int j = i + 1; j < n; j++) {
            int w;

            printf("Distance from %s to %s: ",
                   place[i], place[j]);

            if (scanf("%d", &w) != 1) {
                printf("Invalid input!\n");
                n = 0;
                start = -1;
                done = 0;
                return;
            }

            if (w < 0 || w >= INF)
                graph[i][j] = graph[j][i] = INF;
            else
                graph[i][j] = graph[j][i] = w;
        }
    }

    start = -1;
    done = 0;

    printf("\nGraph saved successfully.\n");
}

void showMatrix()
{
    if (n == 0) {
        printf("Enter the graph first.\n");
        return;
    }

    printf("\nAdjacency Matrix:\n\t");

    for (int i = 0; i < n; i++)
        printf("L%d\t", i + 1);

    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("L%d\t", i + 1);

        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }

        printf("\n");
    }
}

void chooseSource()
{
    int ch;

    if (n == 0) {
        printf("Enter the graph first.\n");
        return;
    }

    printf("\nSelect starting location:\n");

    for (int i = 0; i < n; i++)
        printf("%d. %s\n", i + 1, place[i]);

    printf("Choice: ");

    if (scanf("%d", &ch) != 1) {
        printf("Invalid input!\n");
        return;
    }

    if (ch >= 1 && ch <= n) {
        start = ch - 1;
        done = 0;

        printf("Starting location: %s\n", place[start]);
    }
    else {
        printf("Invalid choice!\n");
    }
}

int minimum()
{
    int min = INF, index = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && distance[i] < min) {
            min = distance[i];
            index = i;
        }
    }

    return index;
}

void dijkstra()
{
    if (n == 0 || start == -1) {
        printf("Enter graph and select starting location first.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        previous[i] = -1;
        visited[i] = 0;
    }

    distance[start] = 0;

    int count = 0;

    while (count < n) {
        int u = minimum();

        if (u == -1)
            break;

        visited[u] = 1;
        count++;

        for (int v = 0; v < n; v++) {
            if (!visited[v] &&
                graph[u][v] != INF &&
                distance[u] + graph[u][v] < distance[v]) {

                distance[v] = distance[u] + graph[u][v];
                previous[v] = u;
            }
        }
    }

    done = 1;
    printf("Shortest routes calculated successfully.\n");
}

void showPath(int v)
{
    if (previous[v] == -1) {
        printf("%s", place[v]);
        return;
    }

    showPath(previous[v]);
    printf(" -> %s", place[v]);
}

void showRoutes()
{
    if (!done) {
        printf("Run Dijkstra first.\n");
        return;
    }

    printf("\nRoutes from %s:\n", place[start]);

    for (int i = 0; i < n; i++) {
        if (i == start)
            continue;

        printf("%s: ", place[i]);

        if (distance[i] == INF) {
            printf("Unreachable\n");
        }
        else {
            printf("Distance = %d, Path = ", distance[i]);
            showPath(i);
            printf("\n");
        }
    }
}

void showDistances()
{
    if (!done) {
        printf("Run Dijkstra first.\n");
        return;
    }

    printf("\nDistances from %s:\n", place[start]);

    for (int i = 0; i < n; i++) {
        if (distance[i] == INF)
            printf("%s: Unreachable\n", place[i]);
        else
            printf("%s: %d\n", place[i], distance[i]);
    }
}

int main()
{
    int choice = 0;

    while (choice != 7) {
        printf("\n--- Campus Route Finder ---\n");
        printf("1. Enter locations and distances\n");
        printf("2. Show adjacency matrix\n");
        printf("3. Select starting location\n");
        printf("4. Calculate shortest routes\n");
        printf("5. Display shortest paths\n");
        printf("6. Display all distances\n");
        printf("7. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                inputGraph();
                break;
            case 2:
                showMatrix();
                break;
            case 3:
                chooseSource();
                break;
            case 4:
                dijkstra();
                break;
            case 5:
                showRoutes();
                break;
            case 6:
                showDistances();
                break;
            case 7:
                printf("Program ended.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}