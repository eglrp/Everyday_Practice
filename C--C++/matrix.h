#ifndef _MATRIX_H
#define _MATRIX_H

#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

//��ʼ��һ����ά����
double** getMatrix(int rows, int columns){
	double **rect = (double**)calloc(rows, sizeof(double*));
	int i;
	for (i = 0; i < rows; ++i)
		rect[i] = (double*)calloc(columns, sizeof(double));
	return rect;
}

//����һ����λ����
double** getIndentityMatrix(int rows){
	double** IM = getMatrix(rows, rows);
	int i;
	for (i = 0; i < rows; ++i)
		IM[i][i] = 1.0;
	return IM;
}

//����һ������ĸ���
double** copyMatrix(double** matrix, int rows, int columns){
	double** rect = getMatrix(rows, columns);
	int i, j;
	for (i = 0; i < rows; ++i)
	for (j = 0; j < columns; ++j)
		rect[i][j] = matrix[i][j];
	return rect;
}

//��һ��һά����õ�һ����ά����
void getFromArray(double** matrix, int rows, int columns, double *arr){
	int i, j, k = 0;
	for (i = 0; i < rows; ++i){
		for (j = 0; j < columns; ++j){
			matrix[i][j] = arr[k++];
		}
	}
}

//��ӡ��ά����
void printMatrix(double** matrix, int rows, int columns){
	int i, j;
	for (i = 0; i < rows; ++i){
		for (j = 0; j < columns; ++j){
			printf("%-10f\t", matrix[i][j]);
		}
		printf("\n");
	}
}

//�ͷŶ�ά����
void freeMatrix(double** matrix, int rows){
	int i;
	for (i = 0; i < rows; ++i)
		free(matrix[i]);
	free(matrix);
}

//��ȡ��ά�����ĳһ��
double* getRow(double **matrix, int rows, int columns, int index){
	assert(index < rows);
	double *rect = (double*)calloc(columns, sizeof(double));
	int i;
	for (i = 0; i < columns; ++i)
		rect[i] = matrix[index][i];
	return rect;
}

//��ȡ��ά�����ĳһ��  
double* getColumn(double **matrix, int rows, int columns, int index){
	assert(index < columns);
	double *rect = (double*)calloc(rows, sizeof(double));
	int i;
	for (i = 0; i < rows; ++i)
		rect[i] = matrix[i][index];
	return rect;
}

//���ö�ά�����ĳһ��   
void setColumn(double **matrix, int rows, int columns, int index, double *arr){
	assert(index < columns);
	int i;
	for (i = 0; i < rows; ++i)
		matrix[i][index] = arr[i];
}

//���������ĳ����
void exchangeColumn(double **matrix, int rows, int columns, int i, int j){
	assert(i < columns);
	assert(j < columns);
	int row;
	for (row = 0; row < rows; ++row){
		double tmp = matrix[row][i];
		matrix[row][i] = matrix[row][j];
		matrix[row][j] = tmp;
	}
}


//�õ������ת��
double** getTranspose(double **matrix, int rows, int columns){
	double **rect = getMatrix(columns, rows);
	int i, j;
	for (i = 0; i < columns; ++i){
		for (j = 0; j < rows; ++j){
			rect[i][j] = matrix[j][i];
		}
	}
	return rect;
}

//�����������ڻ�
double vectorProduct(double *vector1, double *vector2, int len){
	double rect = 0.0;
	int i;
	for (i = 0; i < len; ++i)
		rect += vector1[i] * vector2[i];
	return rect;
}

//�����������
double** matrixProduct(double **matrix1, int rows1, int columns1, double **matrix2, int columns2){
	double **rect = getMatrix(rows1, columns2);
	int i, j;
	for (i = 0; i < rows1; ++i){
		for (j = 0; j < columns2; ++j){
			double *vec1 = getRow(matrix1, rows1, columns1, i);
			double *vec2 = getColumn(matrix2, columns1, columns2, j);
			rect[i][j] = vectorProduct(vec1, vec2, columns1);
			free(vec1);
			free(vec2);
		}
	}
	return rect;
}

//�õ�ĳһ��Ԫ�ص�ƽ����
double getColumnNorm(double** matrix, int rows, int columns, int index){
	assert(index < columns);
	double* vector = getColumn(matrix, rows, columns, index);
	double norm = vectorProduct(vector, vector, rows);
	free(vector);
	return norm;
}

//��ӡ����
void printVector(double* vector, int len){
	int i;
	for (i = 0; i < len; ++i)
		printf("%-15.8f\t", vector[i]);
	printf("\n");
}

/*���ļ��ж�ȡ����*/
void readFromFile(double **matrix, int row, int col, char* file){
	FILE *fp;
	int len = col * 10;
	char *buf = (char*)calloc(len, sizeof(char));
	if ((fp = fopen(file, "r")) == NULL){
		perror("fopen");
		printf("%s\n", file);
		exit(1);
	}
	int i, j;
	for (i = 0; i < row; ++i){
		if (fgets(buf, len, fp) == NULL){
			fprintf(stderr, "�ļ�������С�ھ�����Ҫ������\n");
			exit(1);
		}
		char *seg = strtok(buf, "\t");
		double ele = atof(seg);
		matrix[i][0] = ele;
		for (j = 1; j < col; ++j){
			if ((seg = strtok(NULL, "\t")) == NULL){
				fprintf(stderr, "�ļ�������С�ھ�����Ҫ������\n");
				exit(1);
			}
			ele = atof(seg);
			matrix[i][j] = ele;
		}
		memset(buf, 0x00, len);
	}
	free(buf);
	fclose(fp);
}

/*�Ѿ���д���ļ�*/
void writeToFile(double **matrix, int rows, int columns, char* file){
	FILE *fp;
	if ((fp = fopen(file, "w")) == NULL){
		perror("fopen");
		exit(1);
	}
	fprintf(fp, "%d\t%d\n", rows, columns);        //�ļ����м�¼���������������
	int i, j;
	for (i = 0; i < rows; ++i){
		for (j = 0; j < columns; ++j){
			fprintf(fp, "%-10f\t", matrix[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

/*������д���ļ�*/
void vectorToFile(double *vector, int len, char* file){
	FILE *fp;
	if ((fp = fopen(file, "w")) == NULL){
		perror("fopen");
		exit(1);
	}
	int i;
	for (i = 0; i < len; ++i){
		fprintf(fp, "%-10f\t", vector[i]);
	}
	fclose(fp);
}

#define THREASHOLD 1e-8

/*�����������е���Jacobi�����任*/
void orthogonalVector(double *Ci, double *Cj, int len1, double *Vi, double *Vj, int len2, int *pass){
	double ele = vectorProduct(Ci, Cj, len1);
	if (fabs(ele) < THREASHOLD)
		return;     //��������Ѿ�����������Ҫ���б任���򷵻�true
	*pass = 0;
	double ele1 = vectorProduct(Ci, Ci, len1);
	double ele2 = vectorProduct(Cj, Cj, len1);



	double tao = (ele1 - ele2) / (2 * ele);
	double tan = sign(tao) / (fabs(tao) + sqrt(1 + pow(tao, 2)));
	double cos = 1 / sqrt(1 + pow(tan, 2));
	double sin = cos*tan;

	int row;
	for (row = 0; row < len1; ++row){
		double var1 = Ci[row] * cos + Cj[row] * sin;
		double var2 = Cj[row] * cos - Ci[row] * sin;

		Ci[row] = var1;
		Cj[row] = var2;

	}
	for (row = 0; row < len2; ++row){
		double var1 = Vi[row] * cos + Vj[row] * sin;
		double var2 = Vj[row] * cos - Vi[row] * sin;

		Vi[row] = var1;
		Vj[row] = var2;

	}
}

/*��������н��е���Jacobi�����任��V�Ƿ�����/����Ϊcolumns*/
void orthogonal(double **matrix, int rows, int columns, int i, int j, int *pass, double **V){
	assert(i < j);

	double* Ci = getColumn(matrix, rows, columns, i);
	double* Cj = getColumn(matrix, rows, columns, j);
	double* Vi = getColumn(V, columns, columns, i);
	double* Vj = getColumn(V, columns, columns, j);
	orthogonalVector(Ci, Cj, rows, Vi, Vj, columns, pass);

	int row;
	for (row = 0; row < rows; ++row){
		matrix[row][i] = Ci[row];
		matrix[row][j] = Cj[row];
	}
	for (row = 0; row < columns; ++row){
		V[row][i] = Vi[row];
		V[row][j] = Vj[row];
	}
	free(Ci);
	free(Cj);
	free(Vi);
	free(Vj);
}

void normalize(double **A, int rows, int columns){
	double *sigular = (double*)calloc(columns, sizeof(double));
	int i, j;
	for (i = 0; i < columns; ++i){
		double *vector = getColumn(A, rows, columns, i);
		double norm = sqrt(vectorProduct(vector, vector, rows));
		sigular[i] = norm;
	}
	char outFileS[7] = { 'S', 'X', '.', 'm', 'a', 't', '\0' };
	outFileS[1] = '0' + myRank;
	vectorToFile(sigular, columns, outFileS);
	double **U = getMatrix(rows, columns);
	for (j = 0; j < columns; ++j){
		if (sigular[j] == 0)
		for (i = 0; i < rows; ++i)
			U[i][j] = 0;
		else
		for (i = 0; i < rows; ++i)
			U[i][j] = A[i][j] / sigular[j];
	}
	char outFileU[7] = { 'U', 'X', '.', 'm', 'a', 't', '\0' };
	outFileU[1] = '0' + myRank;
	writeToFile(U, rows, columns, outFileU);
	free(sigular);
	freeMatrix(U, rows);
}



#endif