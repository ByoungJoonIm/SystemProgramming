#include <stdio.h>

int main(int argc, char *argv[]){
	char buf1[20];
	char buf2[20];
	char buf3[20];
	int a;

	while(scanf("%s\t%s\t%s", buf1, buf2, buf3) > 0){
		printf("%s\n%s\n%s\n", buf1, buf2, buf3);
	}


}
