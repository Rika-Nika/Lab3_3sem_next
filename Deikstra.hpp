#pragma once
#include <consoleapi2.h>
#include <cstdio>
const int MAX_INT = 777;
template<typename T>
void deikstra(T** matrix, int numberOfVert, int startVert, int endVert, int * goodPath, int& countPath, T* minLength) {
    --startVert;
    --endVert;
    //minLength ����������� ����������
    int * v = (T*)malloc(sizeof(int) * numberOfVert); // ���������� �������
    int temp, minindex, min;
    
    //������������� ������ � ����������
    for (int i = 0; i < numberOfVert; i++)
    {
        minLength[i] = MAX_INT;
        v[i] = 1;
    }
    minLength[startVert] = 0;
    // ��� ���������
    do {
        minindex = MAX_INT;
        min = MAX_INT;
        for (int i = 0; i < numberOfVert; i++)
        { // ���� ������� ��� �� ������ � ��� ������ min
            if ((v[i] == 1) && (minLength[i] < min))
            { // ��������������� ��������
                min = minLength[i];
                minindex = i;
            }
        }
        // ��������� ��������� ����������� ���
        // � �������� ���� �������
        // � ���������� � ������� ����������� ����� �������
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
   
    // �������������� ����
    // goodPath ������ ���������� ������
    //endVert  ������ �������� ������� 
    goodPath[0] = endVert + 1; // ��������� ������� - �������� �������
    int k = 1; // ������ ���������� �������
    int weight = minLength[endVert]; // ��� �������� �������

    while (endVert != startVert) // ���� �� ����� �� ��������� �������
    {
        for (int i = 0; i < numberOfVert; i++) // ������������� ��� �������
            if (matrix[i][endVert] != 0)   // ���� ����� ����
            {
                int temp = weight - matrix[i][endVert]; // ���������� ��� ���� �� ���������� �������
                if (temp == minLength[i]) // ���� ��� ������ � ������������
                {                 // ������ �� ���� ������� � ��� �������
                    weight = temp; // ��������� ����� ���
                    endVert = i;       // ��������� ���������� �������
                    goodPath[k] = i + 1; // � ���������� �� � ������
                    k++;
                }
            }
    }
    countPath = k;
}
