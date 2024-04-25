#include <stdio.h>
#include <string.h>

typedef struct Laptop{
    char name[100];
    float size;
    int touch;
    int price;
}Laptop;

typedef struct ITStore{
    char name[100];
    char location[100];
    Laptop laptops[100];
    int num_laptops;
}ITStore;

void print(ITStore store){
    printf("%s %s\n", store.name, store.location);
    for (int i=0; i<store.num_laptops; i++){
        printf("%s %g %d\n", store.laptops[i].name, store.laptops[i].size, store.laptops[i].price);
    }
}

void najeftina_ponuda(ITStore *stores, int n){
    int min_index = 0;
    int min = 9999999;
    int i,j;
    for (i=0; i<n; i++){
        for (j=0; j<stores[i].num_laptops; j++){
            if (stores[i].laptops[j].touch==1){
                if (stores[i].laptops[j].price < min){
                    min_index = i;
                    min = stores[i].laptops[j].price;
                }
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\nNajniskata cena iznesuva: %d", stores[min_index].name, stores[min_index].location, min);
}


int main() {
    ITStore s[100];
    int n;
    scanf(" %d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", s[i].name);
        scanf("%s", s[i].location);
        scanf("%d", &s[i].num_laptops);

        for (int j = 0; j < s[i].num_laptops; ++j)
        {
            scanf("%s", s[i].laptops[j].name);
            scanf("%f", &s[i].laptops[j].size);
            scanf("%d", &s[i].laptops[j].touch);
            scanf("%d", &s[i].laptops[j].price);
        }
    }
    for (int i=0; i<n; i++){
        print(s[i]);
    }

    najeftina_ponuda(s, n);

    return 0;
}
