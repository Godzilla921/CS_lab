
farm.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <start_farm>:
   0:	f3 0f 1e fa          	endbr64 
   4:	b8 01 00 00 00       	mov    $0x1,%eax
   9:	c3                   	ret    

000000000000000a <setval_366>:
   a:	f3 0f 1e fa          	endbr64 
   e:	c7 07 68 89 c7 90    	movl   $0x90c78968,(%rdi)
  14:	c3                   	ret    

0000000000000015 <addval_462>:
  15:	f3 0f 1e fa          	endbr64 
  19:	8d 87 58 90 94 c3    	lea    -0x3c6b6fa8(%rdi),%eax
  1f:	c3                   	ret    

0000000000000020 <setval_422>:/*-------------------movq %rax,%rdi ret---------------*/
  20:	f3 0f 1e fa          	endbr64 
  24:	c7 07 48 89 c7 c3    	movl   $0xc3c78948,(%rdi)  //48 89 c7 > movq %rax,%rdi
  2a:	c3                   	ret    

000000000000002b <setval_219>:/*-------------------- popq %rax ret--------------------*/
  2b:	f3 0f 1e fa          	endbr64 
  2f:	c7 07 98 d2 58 c3    	movl   $0xc358d298,(%rdi)  // 58 popq %rax c3 ret
  35:	c3                   	ret    

0000000000000036 <setval_246>: /*-------------------movq %rax,%rdi ret---------------*/
  36:	f3 0f 1e fa          	endbr64 
  3a:	c7 07 48 89 c7 c3    	movl   $0xc3c78948,(%rdi)  //48 89 c7 > movq %rax,%rdi c3 ret
  40:	c3                   	ret    

0000000000000041 <getval_147>:/*-------------------movel %eax,%edi ret---------------*/
  41:	f3 0f 1e fa          	endbr64 
  45:	b8 7a 08 89 c7       	mov    $0xc789087a,%eax  //89 c7 > movl %eax,%edi
  4a:	c3                   	ret    

000000000000004b <addval_385>:
  4b:	f3 0f 1e fa          	endbr64 
  4f:	8d 87 00 58 90 c3    	lea    -0x3c6fa800(%rdi),%eax // popq nop ret
  55:	c3                   	ret    

0000000000000056 <setval_107>:
  56:	f3 0f 1e fa          	endbr64 
  5a:	c7 07 34 1d 58 92    	movl   $0x92581d34,(%rdi)
  60:	c3                   	ret    

0000000000000061 <mid_farm>:
  61:	f3 0f 1e fa          	endbr64 
  65:	b8 01 00 00 00       	mov    $0x1,%eax
  6a:	c3                   	ret    

000000000000006b <add_xy>: /*----------- rax=rdi+rsi  ret-----------------*/
  6b:	f3 0f 1e fa          	endbr64 
  6f:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
  73:	c3                   	ret    

0000000000000074 <addval_372>:
  74:	f3 0f 1e fa          	endbr64 
  78:	8d 87 89 d6 78 c9    	lea    -0x36872977(%rdi),%eax
  7e:	c3                   	ret    

000000000000007f <setval_294>:
  7f:	f3 0f 1e fa          	endbr64 
  83:	c7 07 89 d6 c7 7c    	movl   $0x7cc7d689,(%rdi)
  89:	c3                   	ret    

000000000000008a <setval_155>:/*------------ popq 5rax  movl %esp,%eax  ret ---------*/  
  8a:	f3 0f 1e fa          	endbr64 
  8e:	c7 07 58 89 e0 c3    	movl   $0xc3e08958,(%rdi)  // 58 popq %rax 89 e0 movl %esp,%eax c3 ret
  94:	c3                   	ret    

0000000000000095 <addval_245>:/*-------------- movl %ecx,%edx  andb %al,%al  ret-------------------*/
  95:	f3 0f 1e fa          	endbr64 
  99:	8d 87 89 ca 20 c0    	lea    -0x3fdf3577(%rdi),%eax  // 89 ca movl %ecx,%edx  20 c0 andb %al,%al
  9f:	c3                   	ret    

00000000000000a0 <getval_483>:
  a0:	f3 0f 1e fa          	endbr64 
  a4:	b8 48 89 e0 c1       	mov    $0xc1e08948,%eax
  a9:	c3                   	ret    

00000000000000aa <setval_231>:/*--------------movl %eax,%ecx orb %bl,%bl ret--------------*/
  aa:	f3 0f 1e fa          	endbr64 
  ae:	c7 07 89 c1 08 db    	movl   $0xdb08c189,(%rdi) // 89 c1 movl %eax,%ecx  08 db orb %bl,%bl
  b4:	c3                   	ret    

00000000000000b5 <setval_486>:/*--------------- movl %ecx,%edx testb %bl,%bl ret --------------*/
  b5:	f3 0f 1e fa          	endbr64 
  b9:	c7 07 89 ca 84 db    	movl   $0xdb84ca89,(%rdi)  // 89 ca movl %ecx,%edx  84 db testb %bl,%bl
  bf:	c3                   	ret    

00000000000000c0 <getval_210>:
  c0:	f3 0f 1e fa          	endbr64 
  c4:	b8 89 d6 30 c9       	mov    $0xc930d689,%eax
  c9:	c3                   	ret    

00000000000000ca <addval_229>:
  ca:	f3 0f 1e fa          	endbr64  
  ce:	8d 87 89 c1 60 d2    	lea    -0x2d9f3e77(%rdi),%eax  
  d4:	c3                   	ret    

00000000000000d5 <getval_301>:/*------------ movl %edx,%esi andb %dl,%dl ret ---------*/
  d5:	f3 0f 1e fa          	endbr64 
  d9:	b8 89 d6 20 d2       	mov    $0xd220d689,%eax  // 89 d6 movl %edx,%esi  20 d2 andb %dl,%dl
  de:	c3                   	ret    

00000000000000df <setval_459>:
  df:	f3 0f 1e fa          	endbr64 
  e3:	c7 07 89 c1 18 d2    	movl   $0xd218c189,(%rdi)
  e9:	c3                   	ret    

00000000000000ea <setval_186>:
  ea:	f3 0f 1e fa          	endbr64  
  ee:	c7 07 89 c1 a4 c0    	movl   $0xc0a4c189,(%rdi) 
  f4:	c3                   	ret    

00000000000000f5 <addval_395>:
  f5:	f3 0f 1e fa          	endbr64 
  f9:	8d 87 88 d6 20 d2    	lea    -0x2ddf2978(%rdi),%eax  //20 d2 andb %dl,%dl
  ff:	c3                   	ret    

0000000000000100 <getval_425>:
 100:	f3 0f 1e fa          	endbr64 
 104:	b8 89 ca a4 c9       	mov    $0xc9a4ca89,%eax
 109:	c3                   	ret    

000000000000010a <setval_417>:
 10a:	f3 0f 1e fa          	endbr64 
 10e:	c7 07 9f 48 09 e0    	movl   $0xe009489f,(%rdi) 
 114:	c3                   	ret    

0000000000000115 <getval_113>:
 115:	f3 0f 1e fa          	endbr64 
 119:	b8 8b c1 c3 a8       	mov    $0xa8c3c18b,%eax
 11e:	c3                   	ret    

000000000000011f <getval_145>:
 11f:	f3 0f 1e fa          	endbr64 
 123:	b8 48 89 e0 92       	mov    $0x92e08948,%eax
 128:	c3                   	ret    

0000000000000129 <addval_191>:
 129:	f3 0f 1e fa          	endbr64 
 12d:	8d 87 48 89 e0 c2    	lea    -0x3d1f76b8(%rdi),%eax
 133:	c3                   	ret    

0000000000000134 <addval_423>:
 134:	f3 0f 1e fa          	endbr64 
 138:	8d 87 89 ca 00 d2    	lea    -0x2dff3577(%rdi),%eax
 13e:	c3                   	ret    

000000000000013f <addval_491>:
 13f:	f3 0f 1e fa          	endbr64 
 143:	8d 87 bc 89 c1 94    	lea    -0x6b3e7644(%rdi),%eax
 149:	c3                   	ret    

000000000000014a <setval_222>:/*---------- movl %edx,%esi orb %al,%al ret --------------*/
 14a:	f3 0f 1e fa          	endbr64 
 14e:	c7 07 89 d6 08 c0    	movl   $0xc008d689,(%rdi)  //89 d6 movl %edx,%esi 08 c0 orb %al,%al
 154:	c3                   	ret    

0000000000000155 <setval_232>:/*----------- movq %rsp,%rax ret --------------*/
 155:	f3 0f 1e fa          	endbr64 
 159:	c7 07 c8 48 89 e0    	movl   $0xe08948c8,(%rdi) //48 89 e0 movq %rsp,%rax
 15f:	c3                   	ret    

0000000000000160 <getval_201>:/*----------- movl %eax,%ecx andb %dl,%dl ret -------------*/
 160:	f3 0f 1e fa          	endbr64 
 164:	b8 89 c1 20 d2       	mov    $0xd220c189,%eax //89 c1 movl %eax,%ecx 20 d2 andb %dl,%dl
 169:	c3                   	ret    

000000000000016a <getval_269>:
 16a:	f3 0f 1e fa          	endbr64 
 16e:	b8 81 ca 08 d2       	mov    $0xd208ca81,%eax //08 d2 orb %dl,%dl
 173:	c3                   	ret    

0000000000000174 <getval_299>:
 174:	f3 0f 1e fa          	endbr64 
 178:	b8 f2 8b d6 90       	mov    $0x90d68bf2,%eax // 90 nop
 17d:	c3                   	ret    

000000000000017e <addval_479>:/*----------- movq %rsp,%rax ret --------------*/
 17e:	f3 0f 1e fa          	endbr64 
 182:	8d 87 48 89 e0 c3    	lea    -0x3c1f76b8(%rdi),%eax // 89 e0 c3
 188:	c3                   	ret    

0000000000000189 <getval_466>:
 189:	f3 0f 1e fa          	endbr64 
 18d:	b8 c9 d6 90 90       	mov    $0x9090d6c9,%eax
 192:	c3                   	ret    

0000000000000193 <addval_154>:
 193:	f3 0f 1e fa          	endbr64 
 197:	8d 87 89 c1 28 c0    	lea    -0x3fd73e77(%rdi),%eax
 19d:	c3                   	ret    

000000000000019e <setval_159>:
 19e:	f3 0f 1e fa          	endbr64 
 1a2:	c7 07 10 09 ca c3    	movl   $0xc3ca0910,(%rdi)
 1a8:	c3                   	ret    

00000000000001a9 <addval_414>:
 1a9:	f3 0f 1e fa          	endbr64 
 1ad:	8d 87 09 ca 20 d2    	lea    -0x2ddf35f7(%rdi),%eax
 1b3:	c3                   	ret    

00000000000001b4 <setval_484>:
 1b4:	f3 0f 1e fa          	endbr64 
 1b8:	c7 07 48 89 e0 92    	movl   $0x92e08948,(%rdi)  
 1be:	c3                   	ret    

00000000000001bf <getval_284>:
 1bf:	f3 0f 1e fa          	endbr64 
 1c3:	b8 89 ca 90 c7       	mov    $0xc790ca89,%eax    
 1c8:	c3                   	ret    

00000000000001c9 <end_farm>:
 1c9:	f3 0f 1e fa          	endbr64 
 1cd:	b8 01 00 00 00       	mov    $0x1,%eax
 1d2:	c3                   	ret    
