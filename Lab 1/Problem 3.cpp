#include <stdio.h>
typedef struct employee{
    char ime[100];
    char embg[100];
    char imeoddel[100];
    int plata;
}employee;

typedef struct Company{
    char ime[100];
    employee vraboteni[100];
    int size;
}Company;

void readcompany(Company *comp, employee *emp){
    int size;
    scanf("%s", &comp->ime, &comp->size);
    for (int j=0; j<comp->size; j++){
        scanf("%s %s %s %d", &comp->vraboteni->ime, &comp->vraboteni->embg, &comp->vraboteni->imeoddel, &comp->vraboteni->plata);
    }

}

void printEmployeesBelowAverageSalary(Company *comp, int numCompanies){
    int i,j;
    int sum=0;
    float avg=0;

    for (i=0; i<numCompanies; i++){
        for (j=0; j<comp[i].size; j++){
            sum+=comp[i].vraboteni[j].plata;
        }
    }
}
int main() {
    int n;
    scanf("%d", &n);
    Company c[100];
    employee e[100];
    for (int i=0; i<n; i++){
        readcompany(&c, &e);
    }
    return 0;
}
