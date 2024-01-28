#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ELEMENT {
  int x;
  struct ELEMENT *next;
  struct ELEMENT *prev;
  struct ELEMENT *con;
};
struct ELEMENT *head = NULL;

int genRandNum(int start, int max) {
  int num = (rand() + start) % max;
  return (num + 1);
}

char isGen[200];
void set0() {
    for(int i=0; i<200; i++) isGen[i] = '0';
}

void Insert(struct ELEMENT **L, int x) {
    struct ELEMENT *tmp = (struct ELEMENT*)malloc(sizeof(struct ELEMENT));
    tmp->x = x;
    tmp->con = NULL;
    if(!*L) {
        tmp->next = tmp;
        tmp->prev = tmp;
        *L = tmp;
    } else {
        struct ELEMENT *robo = *L;
        while(robo->next != *L) robo = (robo->next);
        if(robo->next == *L) {
            tmp->next = *L;
            tmp->prev = robo;
            robo->next = tmp;
            (*L)->prev = tmp;  
        }

    }
}
void PrintAll(struct ELEMENT **L) {
    struct ELEMENT *robo = *L;
    if(robo == NULL) {
        printf("No items\n");
        return;
    }
    while(robo->next != *L) {
        printf("%d -> ", robo->x);
        robo = (robo->next);
    }
    printf("%d\n", head->prev->x);
}
void PrintAllD(struct ELEMENT **L, int x) {
    struct ELEMENT *robo = *L;
    if(robo == NULL) {
        printf("No items\n");
        return;
    }
    do {
        if(robo->x == x) {
            printf("%d:\n", x);
            robo = robo->con;
            while(robo->next != NULL) {
                printf("%d ", robo->x);
                robo = robo->next;
            }
            break;
        }
        robo = robo->next;
    } while(robo != *L);
    printf("%d", robo->x);
}
void PrintAllA(struct ELEMENT **L) {
    struct ELEMENT *robo = *L;
    if(robo == NULL) {
        printf("No items\n");
        return;
    }
    do {
        printf("%d <- %d -> %d\n", robo->prev->x, robo->x, robo->next->x);
        robo = (robo->next);
    } while(robo != *L);
}
void DelElm(struct ELEMENT **L, int x) {
    struct ELEMENT *robo = *L;
    if(robo == NULL) {
        printf("No items\n");
        return;
    }
    if(x == robo->x) {
        struct ELEMENT *robo2 = robo->con;
        struct ELEMENT *robo3 = robo2;
        do {
            robo3=robo2;
            robo2 = robo2->next;
            free(robo3);
        } while(robo2 != NULL);
        robo2 = robo;
        head = robo->next;
        robo = robo->prev;
        robo->next = robo->next->next;
        robo = robo->next;
        robo->prev = robo->prev->prev;
        
        free(robo2);
        return;
    } 
    do {
        if(robo->x == x) {
            struct ELEMENT *robo2 = robo->con;
            struct ELEMENT *robo3 = robo2;
            do {
                robo3=robo2;
                robo2 = robo2->next;
                free(robo3);
            } while(robo2 != NULL);
            robo2 = robo;
            robo = robo->prev;
            robo->next = robo->next->next;
            robo = robo->next;
            robo->prev = robo->prev->prev;
            free(robo2);
            return;
        }
        robo = (robo->next);
    } while(robo != *L);
}
void DelList(struct ELEMENT **L) { 
    for(int i=1; i<=200; i++) DelElm(*L, i);
    head=NULL;
}

void genDiv(struct ELEMENT **L) {
    struct ELEMENT *robo = *L;
    if(robo == NULL) {
        printf("No items\n");
        return;
    }
    do {
        if(robo->con != NULL) continue;
        struct ELEMENT *tmp = (struct ELEMENT*)malloc(sizeof(struct ELEMENT));
        tmp->con = NULL;
        tmp->next = NULL;
        tmp->prev = robo;
        tmp->x = 1;
        robo->con = tmp;
        for(int i=2; i<=(robo->x)/2; i++) {
            if((robo->x)%i == 0) {
                struct ELEMENT *roboCon = (struct ELEMENT*)malloc(sizeof(struct ELEMENT));
                roboCon->next = NULL;
                roboCon->prev = tmp;
                roboCon->x = i;
                roboCon->con = NULL; 
                tmp->next = roboCon;
                tmp = roboCon;
            }
        }
        robo = (robo->next);
    } while(robo != *L);
}
void genNum(int m) {
    int h;
    for(int i=0; i<m; i++) {
        h=genRandNum(1, 200);
        if(isGen[h-1]=='1') continue;
        else {
            isGen[h-1] = '1';
            Insert(&head, h);
        }
    }
} 

int n;

void initL() {
    srand(time(NULL));
    scanf("%d", &n);
    genNum(n);
    genDiv(&head);
}

int main(void) {
    initL();
    
    return 0;
}