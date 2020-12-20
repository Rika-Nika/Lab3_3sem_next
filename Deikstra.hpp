#pragma once
#include <consoleapi2.h>
#include <cstdio>
const int MAX_INT = 777;
template<typename T>
void deikstra(T** matrix, int numberOfVert, int startVert, int endVert, int * goodPath, int& countPath, T* minLength) {
    --startVert;
    --endVert;
    //minLength минимальное рассто€ние
    int * v = (T*)malloc(sizeof(int) * numberOfVert); // посещенные вершины
    int temp, minindex, min;
    
    //»нициализаци€ вершин и рассто€ний
    for (int i = 0; i < numberOfVert; i++)
    {
        minLength[i] = MAX_INT;
        v[i] = 1;
    }
    minLength[startVert] = 0;
    // Ўаг алгоритма
    do {
        minindex = MAX_INT;
        min = MAX_INT;
        for (int i = 0; i < numberOfVert; i++)
        { // ≈сли вершину ещЄ не обошли и вес меньше min
            if ((v[i] == 1) && (minLength[i] < min))
            { // ѕереприсваиваем значени€
                min = minLength[i];
                minindex = i;
            }
        }
        // ƒобавл€ем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != MAX_INT)
        {
            for (int i = 0; i < numberOfVert; i++)
            {
                if (matrix[minindex][i] > 0)
                {
                    temp = min + matrix[minindex][i];
                    if (temp < minLength[i])
                    {
                        minLength[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < MAX_INT);
   
    // ¬осстановление пути
    // goodPath массив посещенных вершин
    //endVert  индекс конечной вершины 
    goodPath[0] = endVert + 1; // начальный элемент - конечна€ вершина
    int k = 1; // индекс предыдущей вершины
    int weight = minLength[endVert]; // вес конечной вершины

    while (endVert != startVert) // пока не дошли до начальной вершины
    {
        for (int i = 0; i < numberOfVert; i++) // просматриваем все вершины
            if (matrix[i][endVert] != 0)   // если св€зь есть
            {
                int temp = weight - matrix[i][endVert]; // определ€ем вес пути из предыдущей вершины
                if (temp == minLength[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохран€ем новый вес
                    endVert = i;       // сохран€ем предыдущую вершину
                    goodPath[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
    }
    countPath = k;
}
