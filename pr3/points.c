#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double mas;
} Point;

// sort point by mass
void sortPoints(Point * points, int n);
// consuming distance between two points
double findDistance(Point p1, Point p2);
// compare points by mass
double comparePoints(Point p1, Point p2) {
    return p1.mas - p2.mas;
}
// print all points
void printPoints(Point * points, int n);
    
int main() {
    int n; // amount of points
    printf("Enter amount of points:");
    scanf("%d", &n);
    // allocate memory for the array
    Point * points = (Point*)malloc(sizeof(Point) * n);
    if (points == NULL) {
        printf("Error in allocating memory!\n");
        exit(0);
    }
    // generate array
    for (int i = 0; i < n; i++) {
        printf("Enter x-coordinate of %d point: ", i + 1);
        scanf("%lf", &points[i].x);
        printf("Enter y-coordinate of %d point: ", i + 1);
        scanf("%lf", &points[i].y);
        printf("Enter mas of %d point: ", i + 1);
        scanf("%lf", &points[i].mas);
    }

    printf("Your points:\n");
    printPoints(&points[0], n);
    while (n > 1) {
        int minIdx = 0;
        double minDistance = findDistance(points[0], points[1]);
        // find min distance
        for (int i = 1; i < n - 1; i++) {
            sortPoints(&points[0], n);
            double dist = findDistance(points[0], points[i]);
            if (dist < minDistance) {
                minDistance = dist;
                minIdx = i;
            }
        }
        points[minIdx].mas += points[0].mas;
        for (int z = 0; z < n - 1; z++) {
            points[z] = points[z + 1];
        }
        n--;
        points = (Point*)realloc(points, sizeof(Point) * n);
        //printPoints(&points[0], n);
    }
    printf("Last point(%.1lf; %.1lf) mas: %.1lf\n", points[n - 1].x, points[n - 1].y, points[n - 1].mas);
    return 0;
}

double findDistance(Point p1, Point p2) {
    return sqrt(pow((p2.x - p1.x), 2) - pow((p2.y - p1.y), 2));
}

void sortPoints(Point * points, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (points[j].mas > points[j + 1].mas) {
                Point tmp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = tmp;
            }
        }
    }
}

void printPoints(Point * points, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf(" ( %.1lf; %.1lf : %.1lf )", points[i].x, points[i].y, points[i].mas);
    }
    printf("]\n");
}