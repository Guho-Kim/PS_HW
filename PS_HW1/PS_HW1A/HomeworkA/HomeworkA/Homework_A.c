#include<stdio.h>
int main() {
	/*
		Problem 3n+1
	*/
	int x, y;
	int count = 0;
	int count_max = 0;
	int j;
	scanf("%d %d", &x, &y);

	for (int i = x; i <= y; i++) {
		j = i;
		count++;
		while (j!=1) {
			if (j % 2 == 0) {
				j /= 2;
				count++;
			}
			else {
				j = 3* j +1;
				count++;
			}
		}
		if (count_max < count)
			count_max = count;
		count = 0;
	}
	printf("%d %d %d", x, y, count_max);



	return 0;
}