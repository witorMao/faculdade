#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dynamiclist.h"

int main(){
    int option;
    bool leave = false;
    char name[31];
    int newposition;
    List l;
    create_list(&l);
    while(leave == false){
        scanf("%d\n", &option);
        switch(option){
            case 1:
                read_site(&l);
            break;
            case 2:
                scanf("%[a-z-A-Z0-9 ]\n", name);
                scanf("%d\n", &newposition);
                swap(&l, name, newposition);
            break;
            case 3:
                radix_sort(&l);
            break;
            case 4:
                print_list(&l);
            break;
            case 5:
                free_list(&l);
                leave = true;
            break;
        }
    }
}
