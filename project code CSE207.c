#include <stdio.h>
#include <stdlib.h>

#define ROW 4
#define COL 4

char grid[ROW][COL] = {
    {'1', '1', '0', '0'},
    {'0', '1', '0', '1'},
    {'0', '1', '1', '1'},
    {'0', '0', '1', '2'}
};

int playerX = 0, playerY = 0;
int moveCount = 0;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

 typedef struct{
    int x, y, dist;
} Node;

int isValid(int x, int y, int visited[ROW][COL]) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL &&
            grid[x][y] != '0' && !visited[x][y]);
}

int findShortestPath() {
    int visited[ROW][COL] = {0};
    Node queue[ROW * COL];
    int front = 0, rear = 0;

    queue[rear++] = (Node){0, 0, 0};
    visited[0][0] = 1;

    while (front < rear) {
        Node curr = queue[front++];

        if (grid[curr.x][curr.y] == '2') {
            return curr.dist;
        }

        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (isValid(newX, newY, visited)) {
                visited[newX][newY] = 1;
                queue[rear++] = (Node){newX, newY, curr.dist + 1};
            }
        }
    }

    return -1; // Not reachable
}

void printGrid() {
    printf("\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == playerX && j == playerY) {
                printf("P ");
            } else {
                printf("%c ", grid[i][j]);
            }
        }
        printf("\n");
    }
}

int isValidMove(int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL);
}

void ratePlayer(int optimalMoves) {
    printf("\nYou took %d moves.\n", moveCount);
    printf("Shortest possible path: %d moves.\n", optimalMoves);

    if (moveCount == optimalMoves) {
        printf("⭐⭐⭐ Perfect! You are a true treasure hunter!\n");
    } else if (moveCount <= optimalMoves + 2) {
        printf("⭐⭐ Great job! Just a little off.\n");
    } else {
        printf("⭐ You made it, but you can be faster next time.\n");
    }
}

void playGame() {
    char move;
    int gameOver = 0;

    int optimalMoves = findShortestPath();
    if (optimalMoves == -1) {
        printf("No path to the treasure exists. Game cannot be played.\n");
        return;
    }

    printf("\t Welcome to Treasure Hunt!\n");

    printf("\nDescription: A pirate needs to navigate a grid to find a hidden treasure. The grid contains traps (indicated by 0), open paths (indicated by 1), and the treasure (indicated by 2). The pirate starts at the top-left corner and must reach the treasure in the fewest steps.");
    printf("\n\nControls: W = up, S = down, A = left, D = right\n");
    printf("\nGOAL: Reach the treasure (2) in as few moves as possible.\n");

   while (!gameOver) { //while game over is false
        printGrid();

        printf("Your move (W/A/S/D): ");
        scanf(" %c", &move);

        int newX = playerX;
        int newY = playerY;

        switch (move) {
            case 'W': case 'w': newX--; break;
            case 'S': case 's': newX++; break;
            case 'A': case 'a': newY--; break;
            case 'D': case 'd': newY++; break;
            default:
                printf("Invalid input! Use W/A/S/D.\n");
                continue;
        }

        if (!isValidMove(newX, newY)) { //if this function returns false
            printf("You can't move outside the map!\n");
            continue;
        }

        char nextCell = grid[newX][newY];

        if (nextCell == '0') {
            printf("Oh no! You stepped on a trap. GAME OVER!\n");
            gameOver = 1;
        } else {
            playerX = newX;
            playerY = newY;
            moveCount++;

            if (nextCell == '2') {
                printGrid();
                printf("\n You found the treasure! \n");
                ratePlayer(optimalMoves);
                gameOver = 1;
            }
        }
    }
}

int main() {
    playGame();
    return 0;
}

