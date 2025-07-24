#include <stdio.h>
#include <stdbool.h>
#include "cima_log.h"

int cima_log_rec(int a[], int lft, int rgt) {
    //Agrego mas casos base (esto no puede pasar):
    if (lft > rgt) {
        return -1; 
    }

    //Caso de que sea de longitud 1:
    if (lft == rgt) {
        return lft;
    }

    //Resumo mas facil el caso que lft y rgt sean consecutivos y de forma mas general:
    if (rgt - lft == 1) {
        return (a[lft] < a[rgt]) ? rgt : lft;
    }

    int mid = (lft + rgt) / 2;

    if (a[mid - 1] < a[mid] && a[mid] > a[mid + 1]) {
        return mid;
    } else if (a[mid - 1] > a[mid]) {
        return cima_log_rec(a, lft, mid - 1);
    } else {
        return cima_log_rec(a, mid + 1, rgt);
    }
}

int cima_log(int a[], int length) {
    return cima_log_rec(a, 0, length - 1);
}
