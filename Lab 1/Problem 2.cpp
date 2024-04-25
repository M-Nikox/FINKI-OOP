#include <stdio.h>
typedef struct Point{
    int x;
    int y;
}Point;

typedef struct Circle{
Point centar;
int radius;
}Circle;

void readpoints(Point *p, Circle *c){
   scanf("%d %d", &c->centar.x, &c->centar.y);
   scanf("%d", &c->radius);
}

void findbiggest(Point *p, Circle *c, int n){
    int maxindex=0;
    float maxplosh=0;
    int maxrad=c[0].radius;
    for (int i=0; i<n; i++){
        float ploshtina=(c->radius)*(c->radius)*3.14;
        if (c[i].radius > maxrad){
            maxrad=c[i].radius;
            maxindex=i;
        }
        maxplosh=maxrad*maxrad*3.14;
        //if (maxplosh<ploshtina){
         //   maxplosh=ploshtina;
        //    maxindex=i;
       // } else continue;
    }
    printf("Largest circle has area of: %.2f with centre: (%d,%d)", maxplosh, c[maxindex].centar.x, c[maxindex].centar.y);
}
int main() {
    int n;
    scanf("%d", &n);
    if (n>100||n<1){
        return -1;
    }
    Point p[100];
    Circle c[100];
    for (int i=0; i<n; i++){
        readpoints(&p[i], &c[i]);
    }

    findbiggest(p, c, n);

    return 0;
}
