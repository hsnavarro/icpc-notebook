//
// Created by Henrique Navarro on 12/08/2018.
//
#include <bits/stdc++.h>
#define db(x) cerr << #x << " = " << x << endl
#define _ << ", " <<
using namespace std;

int col[10], lin[10], reg[4][4], res[10][10];

bool test(int x, int y, int k){
    if((lin[x] | col[y] | reg[(x-1)/3 + 1][(y-1)/3 + 1]) & (1<<k)) return false;
    return true;
}

void add(int x, int y, int k){
    if(k == 0) return;
    lin[x] += (1<<k);
    col[y] += (1<<k);
    reg[(x-1)/3 + 1][(y-1)/3 + 1] += (1<<k);
    res[x][y] = k;
}

void rem(int x, int y, int k){
    lin[x] -= (1<<k);
    col[y] -= (1<<k);
    reg[(x-1)/3 + 1][(y-1)/3 + 1] -= (1<<k);
    res[x][y] = 0;
}

bool bt(int x, int y){
    if(y>9) return true;
    if(x>9) return bt(1,y+1);
    if(res[x][y]) return bt(x+1,y);

        for (int k = 1; k <= 9; k++) {
            if (test(x, y, k)) {
                add(x, y, k);
                //db(x _ y _ k);
                if (bt(x+1, y)) return true;
                rem(x, y, k);
            }
        }
    return false;
}

int t, l, c, ts;
char aux;

int main() {
    scanf("%d", &ts);

while(ts--) {

    for (int k = 0; k < 10; k++) {
        col[k] = 0;
        lin[k] = 0;
    }

    for (int k = 0; k < 10; k++) {
        for (int j = 0; j < 10; j++) {
            if(k <= 4 and j <= 4) reg[k][j] = 0;
            res[k][j] = 0;
        }
    }

    for (int l = 1; l <= 9; l++) {
        for (int c = 1; c <= 9; c++) {
            scanf(" %c", &aux);
            add(l, c, aux - '0');
        }
    }

    bt(1, 1);
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (j == 9) printf("%d\n", res[i][j]);
            else printf("%d", res[i][j]);
        }
        if(i == 9) printf("\n");
    }
}

/*
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (!(j % 3) and j != 9) printf("%d | ", res[i][j]);
            else if (j == 9) printf("%d\n", res[i][j]);
            else printf("%d ", res[i][j]);
        }
        if (!(i % 3) and i != 9) printf("---------------------\n");
    }
}
 */

    return 0;
}
