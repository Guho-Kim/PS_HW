#include<stdio.h>
#define MAX_N 11
#define MAX_VAL 1000
typedef struct Index {
	int row;
	int col;
	int in;
} Index;

//row,col���� ������ �������. ����ٰ� ���� �߸� ������ �ߴ� ���̶� row, col �˷���
//���� ������ ���ϴ� �Ŵϱ� ������ �������� ū �� ������/ ������ ������ ��� �ڽ� �ִٰ� �ϸ� �� ���ؾ���. �� index�� col+1==row || col+1==n-row-1 �̰ų�, row+1==col || row+1 n-col-1�� ��. �µ� ���� ���� �͵� ���.
Index fillTheMatrix(int matrix[][MAX_N], Index index[], int curr, int row, int col, int n, int max_v) {
	Index index2;
	for (; row < n; row++) {
		for (; col < n; col++) {
			if (row == 0) curr = matrix[row][col - 1] + 1;
			else curr = matrix[row - 1][col] + 1;
			for (; curr < max_v; curr++) {
				//�������� ���� �밢���̸� ��ŵ
				if (col == row || col == n - 1 - row) break;
				//�����ϱ� ���� �����̳� ������ ����ڽ� ������ �񱳺���.
				//������ ������ Ŭ ��
				else if ((col + 1 == row || col + 1 == n - row - 1) && (curr > matrix[row][col + 1])) {
					curr = matrix[row][col + 1] - 1;
					break;
				}
				//�Ʒ��� ������ Ŭ ��
				else if ((row + 1 == col || row + 1 == n - col - 1) && (curr > matrix[row + 1][col])) {
					curr = matrix[row + 1][col] - 1;
					break;
				}
				//�Ʒ� �� ���� �ְ� ���ٴ� ��
				//col>0�� ��� ���� ���� ���� ������ Ŀ���Ѵ�.


				//���ʰ� ���� �� ��
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
			//���� �� ������ return;
			if (matrix[row][col] == 0) {
				index2.row = row;
				index2.col = col;
				index2.in = curr;
				return index2;
			}

		}
		//for of col ������ col =0���� �ʱ�ȭ.
		col = 0;
	}
	index2.row = row;
	index2.col = col;
	index2.in = curr;
	return index2;
}

//����
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
//���ϵ� �ε��� ����
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
			//printf("(%d, %d)�� %d�� fix\n", index2.row, index2.col, i);//test
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

	//index_store �ʱ�ȭ. ���߿� ������ �� ���ؾ���
	for (int i = 0; i < MAX_VAL + 1; i++) {
		index_store[i].in = 0;
		index[i].in = 0;
	}

	scanf("%d", &n);

	for (int i = 0; i < n; i++) matrix[n][i] = 1001;
	for (int i = 0; i < n; i++) matrix[i][n] = 1001;

	//�밢�� ä���
	for (int i = 0; i < n; i++) scanf("%d", &matrix[i][i]);
	for (int i = 0; i < n; i++) scanf("%d", &matrix[n - 1 - i][i]);
	max_v = matrix[n - 1][n - 1];

	//�밢�� index ���� �Է�.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				index[matrix[i][j]].row = i;
				index[matrix[i][j]].col = j;
				index[matrix[i][j]].in = 1;
			}
		}
	}

	//1Ʈ
	index2 = fillTheMatrix(matrix, index, 0, 0, 1, n, max_v);

	//2Ʈ����
	for (int i = 0; i < n * (n - 1); i++) {
		//���� ������ ä���� ���ϰ� return �ߴٸ�
		if (!(index2.row == n && index2.col == 0)) {
			resetMatrix(matrix, n, index);
			fillTheIndex(index_store, index, index2, matrix);
			index2 = fillTheMatrix(matrix, index, 0, 0, 1, n, max_v);
		}
		//matrix ���
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