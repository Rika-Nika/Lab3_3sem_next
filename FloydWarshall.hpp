#pragma once
#include <minwindef.h>

#include "GraphMatrix.hpp"
template<typename T>
void floydWarshall(GraphMatrix<T>* matrix, int startVert, int endVert, int* goodPath, int& countPath, int& length) {
	--startVert;
	--endVert;
	int numberOfVert = matrix->getSize();
	//матрица минимальных расстояний
	int** dist = (int**)malloc(sizeof(int) * numberOfVert);
	//матрица индексов вершин
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
	//Пробегаемся по всем вершинам и ищем более короткий путь
	//через вершину k
	for (int k = 0; k < numberOfVert; k++) {
		for (int i = 0; i < numberOfVert; i++) {
			for (int j = 0; j < numberOfVert; j++) {
				//Новое значение ребра равно минимальному между старым
				//и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}

	length = dist[startVert][endVert];
	// Восстановление пути
    // goodPath массив посещенных вершин
    //endVert  индекс конечной вершины 
	goodPath[0] = startVert + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины

	while (startVert  != endVert) // пока не дошли до начальной вершины
	{
		startVert = next[startVert][endVert];
		goodPath[k] = startVert+1;
		k++;
	}
	countPath = k;
	
}
