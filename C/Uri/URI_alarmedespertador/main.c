#include <stdio.h>
#include <stdlib.h>

int main()
{
    int H1, M1, H2, M2, T1, T2, V;

    while((H1 != 0) || (H2 != 0) || (M1 != 0) || (M2 != 0)){
        scanf("%d %d %d %d", &H1, &M1, &H2, &M2);

        if((H1 == 0) && (H2 == 0) && (M1 == 0) && (M2 == 0))
            break;

        T1= (H1*60) + M1;
        T2= (H2*60) + M2;

        if(T1==T2){
            printf("%d\n", 0);
            continue;
        }

        V=(T1<T2) ? 1 : 2;

        if(V==1)
            printf("%d\n", T2-T1);
        else
        {
            printf("%d\n", (1440 - (T1-T2)) );
        }
    }
    return 0;
}
