
long mult2(long a, long b);

void mulstore(long x, long y, long *dest){
  long t = mult2(x ,y);
  *dest = t;
}

