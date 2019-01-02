#include <stdio.h>



int main() {

    int X1, Y1, X2, Y2, absx, absy;

 while((scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2)==4)&&((X1<=8)&&(X2<=8) &&(Y1<=8) &&(Y2<=8)&&(X1>=1)&&(X2>=1) &&(Y1>=1)&&(Y2>=1))){

        if(X1>=X2)
            absx= X1-X2;
        else
            absx= X2-X1;


        if(Y1>=Y2)
            absy= Y1-Y2;
        else
            absy= Y2-Y1;


        if((absx==absy)&&((absx*absy)!=0))
            printf("1\n");

        if((absx!=absy)&&((absx*absy)==0))
            printf("1\n");

        if((absx!=absy)&&((absx*absy)!=0))
            printf("2\n");

        if((absx==absy)&&((absx*absy)==0))
            printf("0\n");

 }

    return 0;
}
