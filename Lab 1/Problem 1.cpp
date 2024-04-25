#include <stdio.h>

typedef struct Transaction{
    int id;
    int suma;
    int provizija;
    int deborkred;
}Transaction;

void readtransaction(Transaction *t) {
    int br;
    scanf("%d %d %d %d", &t->id, &t->suma, &t->provizija, &t->deborkred);
}

int printtransaction(Transaction t){
    int suma=0;
    if (t.deborkred){
        printf("%d %d\n", t.id, t.suma+t.provizija);
        suma+=t.suma+t.provizija;
    }
    return suma;
}

int main() {
    int n;
    int k=0;
    scanf("%d", &n);
    if (n>100){
        return -1;
    }
    Transaction t[100];

    for (int i=0; i<n; i++){
        readtransaction(&t[i]);
    }

    for (int i=0; i<n; i++){
        k+=printtransaction(t[i]);
    }
    if (k==0){
        printf("No credit card transaction");
    }
    return 0;
}
