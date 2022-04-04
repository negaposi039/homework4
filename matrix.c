#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); // 행렬 생성 함수
void print_matrix(int** matrix, int row, int col); // 행렬 출력 함수
int free_matrix(int** matrix, int row, int col); // 동적 할당 해제 함수
int fill_data(int** matrix, int row, int col); // 행렬 값을 채우는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬 덧셈 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬 뺄셈 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 행렬 전치 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 행렬 a와 전치행렬의 곱셈 함수

int main()
{
    char command; // 명령 변수
    printf("[----- [Kim Hyeong Jin]  [2021041079] -----]\n");

	int row, col; // 행, 열 변수
	srand(time(NULL)); // time으로 rand() seed 값 사용

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); // 행, 열 입력
    int** matrix_a = create_matrix(row, col); // create_matrix 함수로 행렬 A 생성
	int** matrix_b = create_matrix(row, col); // create_matrix 함수로 행렬 B 생성
    int** matrix_a_t = create_matrix(col, row); // create_matrix 함수로 행렬 A의 전치행렬 생성

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} // NULL 값 리턴 시 프로그램 비정상 종료 (return -1)

	do{   // do-while 문으로 재실행 가능한 메뉴 구현
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령 입력

		switch(command) {
		case 'z': case 'Z': // z 명령 시 fill_data 함수 이용, 행렬 값 채움
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P': // p 명령 시 print_matrix 함수 이용, 행렬 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
        case 'a': case 'A': // a 명령 시 addition_matrix 함수 이용, 행렬 덧셈 후 출력
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
        case 's': case 'S': // s 명령 시 subtraction_matrix 함수 이용, 행렬 뺄셈 후 출력
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
        case 't': case 'T':
			printf("Transpose matrix_a \n"); // t 명령 시 transpose_matrix 함수 이용, 행렬 전치 후 출력
			printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M': // m 명령 시 transpose_matrix, multiply_matrix 함수 이용, 행렬 전치, 곱셈 후 출력
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
        case 'q': case 'Q': // q 명령시 free_matrix 함수 이용, 행렬 동적할당 해제 후 반복문 탈출
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default: // case 이외 시 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 메시지
			break;
		}

	}while(command != 'q' && command != 'Q'); // Quit 명령어 입력하지 않으면 반복

	return 1; // 프로그램 정상 종료
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료 (return -1)
		printf("Check the size of row and col!\n"); // 에러 메시지
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); // 이중 포인터 이용, 동적할당으로 matrix 행 구현 (2차원 배열)
	for (int r = 0; r < row; r++) {  // for 반복문으로 matrix 열의 각 성분에 동적할당 되도록 함
		matrix[r] = (int*)malloc(sizeof(int) * col); // 동적할당으로 matrix 열 구현
	}

	/* Check post conditions */
	if (matrix == NULL) { // 비정상 결과값 시 비정상 종료(return -1)
		printf("Memory Allocation Failed.\n"); // 에러 메시지
		return NULL; 
	}

	return matrix; // 생성된 행렬 matrix 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료
		printf("Check the size of row and col!\n"); // 에러 메시지
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 반복문 이용하여 행렬 matrix 2차원 배열 출력
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {  // 비정상 결과값 시 비정상 종료
		printf("Memory Allocation Failed.\n"); // 에러 메시지
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료 (return -1)
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 반복문 이용하여 matrix 행 동적할당 해제
		free(matrix[matrix_row]);
	}

	free(matrix); // matrix 변수 동적할당 해제
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료 (return -1)
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) // 반복문 이용하여 행렬 matrix 2차원 배열에 값 저장
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20; // rand() 이용 랜덤값 저장
	/* Check post conditions */
    if (matrix == NULL) { // 비정상 결과값 시 비정상 종료 (return -1)
		printf("Memory Allocation Failed.\n"); // 에러 메시지
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col); // 덧셈 결과 저장할 행렬 2차원 배열 생성
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료 (return -1)
		printf("Check the size of row and col!\n"); // 에러 메시지
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 반복문 이용 각 성분 덧셈, matrix_sum에 A 행렬과 B 행렬 덧셈 값 저장
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { // 비정상 결과값 시 비정상 종료(return -1)
		printf("Memory Allocation Failed.\n"); // 에러 메시지
		return -1;
	}

	print_matrix(matrix_sum, row, col); // print_matrix 함수 이용 matrix_sum 출력
	free_matrix(matrix_sum, row, col); // free_matrix 함수 이용 matrix_sum 동적 할당 해제
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); // 뺄셈 결과 저장할 행렬 2차원 배열 생성
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료 (return -1)
		printf("Check the size of row and col!\n"); // 에러 메시지
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 반복문 이용 각 성분 뺄셈, matrix_sub에 A 행렬과 B 행렬 덧셈 값 저장
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { // 비정상 결과값 시 비정상 종료(return -1)
		printf("Memory Allocation Failed.\n"); // 에러 메시지
		return -1;
	}
	print_matrix(matrix_sub, row, col); // print_matrix 함수 이용 matrix_sub 출력
	free_matrix(matrix_sub, row, col); // free_matrix 함수 이용 matrix_sub 동적 할당 해제

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료 (return -1)
		printf("Check the size of row and col!\n"); // 에러 메시지
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 반복문 사용 m*n 행렬을 n*m 행렬로 바꾸어 전치행렬 생성
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) { // 비정상 결과값 시 비정상 종료 (return -1)
		printf("Memory Allocation Failed.\n"); // 에러 메시지
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row); // 곱셈 결과 저장할 행렬 2차원 배열 (m*n 행렬과 n*m 행렬의 곱셈이므로 m*m) 생성
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 비정상 입력값 전달 시 비정상 종료 (return -1)
		printf("Check the size of row and col!\n"); // 에러 메시지
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) { // 반복문 사용 행렬 곱셈
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) { // 반복문 사용 행렬의 곱셈 수행
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; // 곱셈 결과 행렬 성분에 저장될 값(matrix_a의 행 성분 * matrix_t의 열 성분) temp에 저장
			matrix_axt[matrix_a_row][matrix_t_row] = temp; // 곱셈 결과 행렬에 계산된 temp 값 저장
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { // 비정상 결과값 시 비정상 종료 (return -1)
		printf("Memory Allocation Failed.\n"); // 에러 메시지
		return -1;
	}
	print_matrix(matrix_axt, row, row); // print_matrix 함수 이용 matrix_axt 출력
	free_matrix(matrix_axt, row, col); // free_matrix 함수 이용 matrix_axt 동적 할당 해제
	return 1;
}


