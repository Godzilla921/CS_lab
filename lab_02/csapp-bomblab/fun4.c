# include <stdio.h>

int func(int a,int b,int c)
{
    int result=c-b;
    int val=result<0?1:0;
    val+=result;
    val>>=1;
    val+=b;
    if(val>a){
        result=2*func(a,b,val-1);
    }else if(val<a){
        result=2*func(a,val+1,c)+1;
    }
    return result;
}

int main()
{
    for(int i=0;i<=14;i++){
        printf("i=%d, f=%d\n",i,func(i,0,14));
    }
    return 0;
}
