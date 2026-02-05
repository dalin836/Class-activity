#include <stdio.h>
#include <unistd.h>
int main(){
	printf("Hello form dalin\n");
	write(1,"this is a write syscall1\n",24);
return 0;
}
