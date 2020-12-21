#pragma once
#include <minwindef.h>

#include "GraphMatrix.hpp"
template<typename T>
void floydWarshall(GraphMatrix<T>* matrix, int startVert, int endVert, int* goodPath, int& countPath, int& length) {
	--startVert;
	--endVert;
	int numberOfVert = matrix->getSize();
	//������� ����������� ����������
	int** dist = (int**)malloc(sizeof(int) * numberOfVert);
	//������� �������� ������
	int** next = (int**)malloc(sizeof(int) * numberOfVert);
	for (int i = 0; i < numberOfVert; i++) {
		dist[i] = (T*)malloc(sizeof(T) * numberOfVert);
		next[i] = (T*)malloc(sizeof(T) * numberOfVert);
	}
	for (int i = 0; i < numberOfVert; ++i)
	{
		for (int j = 0; j < numberOfVert; ++j)
		{
			if (i == j)
			{
				dist[j][j] = 0;
				next[j][j] = j;
			}
			else {
				dist[i][j] = matrix->getWeight(i, j);
				next[i][j] = j;
			}
		}
	}
	//����������� �� ���� �������� � ���� ����� �������� ����
	//����� ������� k
	for (int k = 0; k < numberOfVert; k++) {
		for (int i = 0; i < numberOfVert; i++) {
			for (int j = 0; j < numberOfVert; j++) {
				//����� �������� ����� ����� ������������ ����� ������
				//� ������ ����� i <-> k + k <-> j (���� ����� k ������ �������)
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}

	length = dist[startVert][endVert];
	// �������������� ����
    // goodPath ������ ���������� ������
    //endVert  ������ �������� ������� 
	goodPath[0] = startVert + 1; // ��������� ������� - �������� �������
	int k = 1; // ������ ���������� �������

	while (startVert  != endVert) // ���� �� ����� �� ��������� �������
	{
		startVert = next[startVert][endVert];
		goodPath[k] = startVert+1;
		k++;
	}
	countPath = k;
	
}
