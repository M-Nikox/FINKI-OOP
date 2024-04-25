#include <stdio.h>
#include <string.h>

typedef struct UmetnickoDelo{
    char author[100];
    float price;
    int type; //1 picture 2 sculpture
}UmetnickoDelo;

typedef struct Galerija{
    char name[50];
    UmetnickoDelo dela[30];
    int num_dela;
}Galerija;

void print(Galerija g){
    printf("%s\n", g.name);
    for (int i=0; i<g.num_dela; i++){
        printf("%s %.2f %d\n", g.dela[i].author, g.dela[i].price, g.dela[i].type);
    }
}

int getgalerii(Galerija *g){
    int i=0;
    for (i=0; g[i].name[0]!='\0'; i++){}
    return i;
}

void najdobra_ponuda(Galerija *g, int n, int tip){
    float best=999999;
    int best_index=-1;
    if (tip==1){
        for (int i=0; i<n; i++){
            for (int j=0; j<g[i].num_dela; j++){
                if (g[i].dela[j].type == tip){
                    if (g[i].dela[j].price < best){
                        best=g[i].dela[j].price;
                        best_index=i;
                    }
                }
            }
        }
        if (best_index != -1) {
            printf("Najevtino umetnicko delo tip slika go nudi galerijata: %s so cena: %.2f\n", g[best_index].name, best);
        }
        else {
            printf("Ne e pronajdeno delo od tip slika\n");
        }
    }
    else if (tip==2){
        for (int i=0; i<n; i++){
            for (int j=0; j<g[i].num_dela; j++){
                if (g[i].dela[j].type == tip){
                    if (g[i].dela[j].price < best){
                        best=g[i].dela[j].price;
                        best_index=i;
                    }
                }
            }
        }
        if (best_index != -1) {
            printf("Najevtino umetnicko delo tip skulptura go nudi galerijata: %s so cena: %.2f\n", g[best_index].name, best);
        }
        else {
            printf("Ne e pronajdeno umetnicko delo od tip skulptura\n");
        }
    }
}


int main() {
    int n;
    scanf("%d", &n);
    Galerija galerii[n];
    for (int i=0; i<n; i++){
        scanf("%s %d", &galerii[i].name, &galerii[i].num_dela);
            for (int j=0; j<galerii[i].num_dela; j++){
                scanf("%s %f %d", &galerii[i].dela[j].author, &galerii[i].dela[j].price, &galerii[i].dela[j].type);
            }
    }

    for (int i=0; i<n; i++) {
        print(galerii[i]);
    }

    int whichtype;
    scanf("%d", &whichtype);

    najdobra_ponuda(galerii, n, whichtype);

    return 0;
}
