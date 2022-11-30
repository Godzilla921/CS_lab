# include <stdio.h>

int f(int *rsp)
{
	int *r13=rsp;
	int *rbp;
	int r14d=0;
	int eax;
	long rax;
	int ebx;
	while(1){
		rbp=r13;
		eax=*r13;
		eax--;
		if(eax>5||eax<0) {
			//printf("bomb\n");
			return 0;
		}
		r14d++;
		if(r14d==6) break;
		ebx=r14d;
		while(1){
			rax=(long)eax;
			eax=*(rsp+rax);
			if(*rbp!=eax){
				ebx++;
				if(ebx>5||ebx<0) break;
			}else{
				//printf("bomb\n");
				return 0;
			}
		}
		r13++;
	}
	return 1;
}

int main()
{
	int a[6];
	for(int i=1;i<=6;i++){
		for(int j=1;j<=6;j++){
			for(int k=1;k<=6;k++){
				for(int l=1;l<=6;l++){
					for(int m=1;m<=6;m++){
						for(int n=1;n<=6;n++){
							a[0]=i;
							a[1]=j;
							a[2]=k;
							a[3]=l;
							a[4]=m;
							a[5]=n;	
							if(f(a)){
								for(int ii=0;ii<6;ii++){
								printf("%d  ",a[ii]);
								}
								printf("\n");
								//return 0;
							}
						}
					}
				}
			}
		}
	}
	a[0]=4;
							a[1]=5;
							a[2]=6;
							a[3]=2;
							a[4]=3;
							a[5]=1;
							if(f(a)) 	printf("yes\n");
	return 0;
}
