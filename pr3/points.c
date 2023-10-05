#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double mas;
} Point;

// consuming distance between two points
double findDistance(Point p1, Point p2);
// find point with min mas
int findMinMasPointInd(Point * points, int n);
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
        int idx = findMinMasPointInd(&points[0], n);
        int nearestIndx = 0;
        double minDist;
        if (idx == 0) {
            minDist = findDistance(points[idx], points[1]);
            nearestIndx = 1;
        } else {
            minDist = findDistance(points[idx], points[0]);
        }
        for (int i = 1; i < n; i++) {
            if (i != idx) {
                double distance = findDistance(points[idx], points[i]);
                if (distance < minDist) {
                    nearestIndx = i;
                    minDist = distance;
                }
            } 
        }
        points[nearestIndx].mas += points[idx].mas;
        // delete element
        for (int i = idx; i < n - 1; i++) {
            points[i] = points[i + 1];
        }
        n--;
        points = (Point*)realloc(points, sizeof(Point) * n);
        printPoints(&points[0], n);
    }
    printf("Last point(%.1lf; %.1lf) mas: %.1lf\n", points[n - 1].x, points[n - 1].y, points[n - 1].mas);
    return 0;
}

double findDistance(Point p1, Point p2) {
    double a = pow(p2.x - p1.x, 2);
    double b = pow(p2.y - p1.y, 2);
    return sqrt( a + b );
}

int findMinMasPointInd(Point * points, int n) {
    int idx = 0;
    double minMas = points[0].mas;
    for (int i = 1; i < n; i++) {
        if (minMas > points[i].mas) {
            minMas = points[i].mas;
            idx = i;
        }
    }
    return idx;
}

void printPoints(Point * points, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf(" ( %.1lf; %.1lf : %.1lf )", points[i].x, points[i].y, points[i].mas);
    }
    printf("]\n");
}