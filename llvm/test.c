/* 
编译可执行文件
./clang test.c -o test

生成LLVM 字节码文件
./clang -O3 -emit-llvm test.c -c -o test.bc

生成LLVM  可视化字节码文件
./clang -O3 -emit-llvm test.c -S -o test.ll
 
运行可执行文件
./test
 
运行字节码文件
./lli test.bc

反汇编字节码文件
./llvm-dis < test.bc | less

编译字节码为汇编文件
./llc test.bc -o test.s

 */

#include <stdio.h>
int main() {
  printf("hello llvm\n");
  return 0;
}


