#include<stdio.h>
#define MAX_N 11
#define MAX_VAL 1000
typedef struct Index {
	int row;
	int col;
	int in;
} Index;

//row,col부터 끝까지 만들어줘. 만들다가 에러 뜨면 넣으려 했던 값이랑 row, col 알려줘
//왼족 위에서 작하는 거니까 좌측과 상측보다 큰 것 따지고/ 우측과 하측에 노란 박스 있다고 하면 또 비교해야함. 즉 index가 col+1==row || col+1==n-row-1 이거나, row+1==col || row+1 n-col-1일 때. 걔들 보다 작은 것도 고려.
Index fillTheMatrix(int matrix[][MAX_N], Index index[], int curr, int row, int col, int n, int max_v) {
	Index index2;
	for (; row < n; row++) {
		for (; col < n; col++) {
			if (row == 0) curr = matrix[row][col - 1] + 1;
			else curr = matrix[row - 1][col] + 1;
			for (; curr < max_v; curr++) {
				//넣으려는 값이 대각선이면 스킵
				if (col == row || col == n - 1 - row) break;
				//시작하기 전에 우측이나 하측에 노란박스 있으면 비교부터.
				//오른쪽 값보다 클 때
				else if ((col + 1 == row || col + 1 == n - row - 1) && (curr > matrix[row][col + 1])) {
					curr = matrix[row][col + 1] - 1;
					break;
				}
				//아래쪽 값보다 클 때
				else if ((row + 1 == col || row + 1 == n - col - 1) && (curr > matrix[row + 1][col])) {
					curr = matrix[row + 1][col] - 1;
					break;
				}
				//아래 두 개는 넣고 뺀다는 것
				//col>0일 경우 왼쪽 값과 위쪽 값보다 커야한다.


				//왼쪽과 위쪽 값 비교
				if (row == 0) {
					if (matrix[row][col - 1] < curr && (index[curr].in != 1)) {
						matrix[row][col] = curr;
						index[matrix[row][col]].row = row;
						index[matrix[row][col]].col = col;
						index[matrix[row][col]].in = 1;
						break;
					}
				}

				else {
					if (col == 0) {
						if (matrix[row - 1][col] < curr && (index[curr].in != 1)) {
							matrix[row][col] = curr;
							index[matrix[row][col]].row = row;
							index[matrix[row][col]].col = col;
							index[matrix[row][col]].in = 1;
							break;
						}
					}
					else if (col > 0) {
						if (matrix[row][col - 1] < curr && matrix[row - 1][col] < curr && (index[curr].in != 1)) {
							matrix[row][col] = curr;
							index[matrix[row][col]].row = row;
							index[matrix[row][col]].col = col;
							index[matrix[row][col]].in = 1;
							break;
						}
					}
				}
			}
			//넣을 게 없으면 return;
			if (matrix[row][col] == 0) {
				index2.row = row;
				index2.col = col;
				index2.in = curr;
				return index2;
			}

		}
		//for of col 끝나면 col =0으로 초기화.
		col = 0;
	}
	index2.row = row;
	index2.col = col;
	index2.in = curr;
	return index2;
}

//리셋
resetMatrix(int matrix[][MAX_N], int n, Index index[]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!((i == j) || (i == n - 1 - j))) {
				matrix[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < MAX_VAL + 1; i++) {
		index[i].row = -1;
		index[i].col = -1;
		index[i].in = 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				index[matrix[i][j]].row = i;
				index[matrix[i][j]].col = j;
				index[matrix[i][j]].in = 1;
			}
		}
	}
}
//리턴된 인덱스 저장
void fillTheIndex(Index index_store[], Index index[], Index index2, int matrix[][MAX_N]) {
	index_store[index2.in].row = index2.row;
	index_store[index2.in].col = index2.col;
	index_store[index2.in].in = 1;
	index[index2.in].row = index2.row;
	index[index2.in].col = index2.col;
	index[index2.in].in = 1;

	for (int i = 0; i < MAX_VAL; i++) {
		if (index_store[i].in == 1) {
			matrix[index_store[i].row][index_store[i].col] = i;
			//printf("(%d, %d)에 %d값 fix\n", index2.row, index2.col, i);//test
		}

	}


}



int main() {
	int n;
	int curr;
	int row;
	int matrix[MAX_N][MAX_N] = { 0 };
	int max_v;
	Index index_store[MAX_VAL + 1];
	Index index[MAX_VAL + 1];
	Index index2;

	//index_store 초기화. 나중에 저장한 값 비교해야함
	for (int i = 0; i < MAX_VAL + 1; i++) {
		index_store[i].in = 0;
		index[i].in = 0;
	}

	scanf("%d", &n);

	for (int i = 0; i < n; i++) matrix[n][i] = 1001;
	for (int i = 0; i < n; i++) matrix[i][n] = 1001;

	//대각선 채우기
	for (int i = 0; i < n; i++) scanf("%d", &matrix[i][i]);
	for (int i = 0; i < n; i++) scanf("%d", &matrix[n - 1 - i][i]);
	max_v = matrix[n - 1][n - 1];

	//대각선 index 정보 입력.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				index[matrix[i][j]].row = i;
				index[matrix[i][j]].col = j;
				index[matrix[i][j]].in = 1;
			}
		}
	}

	//1트
	index2 = fillTheMatrix(matrix, index, 0, 0, 1, n, max_v);

	//2트부터
	for (int i = 0; i < n * (n - 1); i++) {
		//만약 끝까지 채우지 못하고 return 했다면
		if (!(index2.row == n && index2.col == 0)) {
			resetMatrix(matrix, n, index);
			fillTheIndex(index_store, index, index2, matrix);
			index2 = fillTheMatrix(matrix, index, 0, 0, 1, n, max_v);
		}
		//matrix 출력
		else {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%d ", matrix[i][j]);
				}
				printf("\n");
			}
			return 0;
		}
	}
	printf("Infeasible");
	return 0;
}