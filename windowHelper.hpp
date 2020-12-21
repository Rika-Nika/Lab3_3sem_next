#pragma once

#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp> 
#include "framework.h"
#include "Util.hpp"
#include <boost/algorithm/string.hpp>
#include "Deikstra.hpp"
#include "FloydWarshall.hpp"
#include "GraphMatrix.hpp"

// Функция преобразования числа в строку
char* IntToStr(int n)
{
	char s[40], t, * temp;
	int i, k;
	int sign = 0;
	i = 0;
	k = n;
	if (k < 0)
	{
		sign = 1;
		k = -k;
	}
	do
	{
		t = k % 10;
		k = k / 10;
		s[i] = t | 0x30;
		i++;
	} while (k > 0);
	if (sign == 1)
	{
		s[i] = '-';
		i++;
	}
	temp = new char[i];
	k = 0;
	i--;
	while (i >= 0)
	{
		temp[k] = s[i];
		i--;
		k++;
	}
	temp[k] = '\0';
	return (temp);
}

void getString(HWND SearchStr, std::wstring& str)
{
	int bufferLength = ::GetWindowTextLength(SearchStr) + 1;
	std::vector<wchar_t> buffer(bufferLength);
	::GetWindowText(SearchStr, buffer.data(), bufferLength);
	str = buffer.data();
}

void testDeikstra(HWND hWndOutput0, HWND hWndOutput1, HWND hWndOutput2,
	Alg alg, int startVert, int endVert, Matrix matrixEnum, GraphMatrix<int> * matrix,  std::wstring fileName)
{
	int numberOfVert = matrix->getSize();
	std::wostringstream oss1;
	std::wostringstream oss2;
	std::wostringstream oss3;

	//массив посещенных вершин
	int* goodPath = (int*)malloc(sizeof(int) * numberOfVert);
	int* minLength = (int*)malloc(sizeof(int) * numberOfVert);
	int countVer = 0; // Длина пути

	int alg1[3] = { 4,3,1 };
	int alg1Vert[2] = { 1,4 };
	int alg2[4] = { 5,6,3,1 };
	int alg2Vert[2] = { 1,5 };
	int alg3[3] = { 6,5,1 };
	int alg3Vert[2] = { 1,6 };
	bool res = true;
	switch (matrixEnum)
	{
	case Matrix::Matrix1:
		if (startVert == alg1Vert[0] && endVert == alg1Vert[1]) {
			for (int i = countVer - 1; i >= 0; --i)
			{
				res = res && (goodPath[i] == alg1[i]);
			}
			if (res)
			{
				oss3 << L"----Тест пройден----";
			}
			else
			{
				oss3 << L"----Тест завален----";
			}
		}
	case Matrix::Matrix2:
		if (startVert == alg2Vert[0] && endVert == alg2Vert[1]) {
			for (int i = countVer - 1; i >= 0; --i)
			{
				res = res && (goodPath[i] == alg2[i]);
			}
			if (res)
			{
				oss3 << L"----Тест пройден----";
			}
			else
			{
				oss3 << L"----Тест завален----";
			}
		}
	case Matrix::Matrix3:
		if (startVert == alg3Vert[0] && endVert == alg3Vert[1]) {
			for (int i = countVer - 1; i >= 0; --i)
			{
				res = res && (goodPath[i] == alg3[i]);
			}
			if (res)
			{
				oss3 << L"----Тест пройден----";
			}
			else
			{
				oss3 << L"----Тест завален----";
			}
		}
	default:;
	}

	oss2 << L"Алгоритм Дейкстры.\r\nНаилучший путь из " << startVert << L" в " << endVert << "\r\n";
	if (!oss3.str().empty())
	{
		oss2 << oss3.str() << "\r\n";
	}

	auto startTime = std::chrono::system_clock::now();
	deikstra<int>(matrix, startVert, endVert, goodPath, countVer, minLength);
	auto endTime = std::chrono::system_clock::now();
	auto delta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

	oss2 << L"Время выполнения (микро сек): " << delta.count() << "\r\n";
	oss2 << L"Длина пути " << minLength[endVert - 1] << "\r\n";
	for (int i = countVer - 1; i >= 0; --i)
	{
		oss2 << goodPath[i] << L"\t";
	}

	std::string str("Алгоритм; Количество вершин; Время выполнения\n");
	str.append("Дейкстра;").append(std::to_string(numberOfVert)).append(";").append(std::to_string(delta.count())).append("\n");
	
	SetWindowText(hWndOutput1, oss2.str().c_str());
	writeToCSV(fileName.append(L"_D_").append(std::to_wstring(numberOfVert)), str);

}

void testfloydWarshall(HWND hWndOutput0, HWND hWndOutput1, HWND hWndOutput2,
	Alg alg, int startVert, int endVert, Matrix matrixEnum, GraphMatrix<int>* matrix, std::wstring fileName)
{
	int numberOfVert = matrix->getSize();
	std::wostringstream oss1;
	std::wostringstream oss2;
	std::wostringstream oss3;

	//массив посещенных вершин
	int* goodPath = (int*)malloc(sizeof(int) * numberOfVert);
	int length;
	int countVer = 0; // Длина пути

	int alg1[3] = { 4,3,1 };
	int alg1Vert[2] = { 1,4 };
	int alg2[4] = { 5,6,3,1 };
	int alg2Vert[2] = { 1,5 };
	int alg3[3] = { 6,5,1 };
	int alg3Vert[2] = { 1,6 };
	bool res = true;
	switch (matrixEnum)
	{
	case Matrix::Matrix1:
		if (startVert == alg1Vert[0] && endVert == alg1Vert[1]) {
			for (int i = countVer - 1; i >= 0; --i)
			{
				res = res && (goodPath[i] == alg1[i]);
			}
			if (res)
			{
				oss3 << L"----Тест пройден----";
			}
			else
			{
				oss3 << L"----Тест завален----";
			}
		}
	case Matrix::Matrix2:
		if (startVert == alg2Vert[0] && endVert == alg2Vert[1]) {
			for (int i = countVer - 1; i >= 0; --i)
			{
				res = res && (goodPath[i] == alg2[i]);
			}
			if (res)
			{
				oss3 << L"----Тест пройден----";
			}
			else
			{
				oss3 << L"----Тест завален----";
			}
		}
	case Matrix::Matrix3:
		if (startVert == alg3Vert[0] && endVert == alg3Vert[1]) {
			for (int i = countVer - 1; i >= 0; --i)
			{
				res = res && (goodPath[i] == alg3[i]);
			}
			if (res)
			{
				oss3 << L"----Тест пройден----";
			}
			else
			{
				oss3 << L"----Тест завален----";
			}
		}
	default:;
	}

	oss2 << L"Алгоритм Флойда — Уоршелла.\r\nНаилучший путь из " << startVert << L" в " << endVert << "\r\n";
	if (!oss3.str().empty())
	{
		oss2 << oss3.str() << "\r\n";
	}

	auto startTime = std::chrono::system_clock::now();
	floydWarshall<int>(matrix, startVert, endVert, goodPath, countVer, length);
	auto endTime = std::chrono::system_clock::now();
	auto delta= std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

	oss2 << L"Время выполнения (микро сек): " << delta.count() << "\r\n";
	oss2 << L"Длина пути " << length << "\r\n";

	for (int i = 0; i < countVer; ++i)
	{
		oss2 << goodPath[i] << L"\t";
	}

	std::string str("Алгоритм; Количество вершин; Время выполнения\n");
	str.append("Флойда—Уоршелла").append(std::to_string(numberOfVert)).append(";").append(std::to_string(delta.count())).append("\n");

	SetWindowText(hWndOutput2, oss2.str().c_str());
	writeToCSV(fileName.append(L"_F_").append(std::to_wstring(numberOfVert)), str);
}

void testAlg(HWND hWndOutput0, HWND hWndOutput1, HWND hWndOutput2,
	HWND hFileName, Alg alg, HWND hStartVert, HWND hEndVert, Matrix matrixEnum)
{
	std::wostringstream oss1;
	std::wstring fileName;
	std::wstring startVertStr;
	std::wstring endVertStr;
	getString(hFileName, fileName);
	getString(hStartVert, startVertStr);
	getString(hEndVert, endVertStr);
	int startVert;
	int endVert;
	startVert = stoi(startVertStr);
	endVert = stoi(endVertStr);
	int  numberOfVert;
	//матрица смежности
	GraphMatrix<int> * matrix = loadMatrix<int>(fileName, numberOfVert);
	if (nullptr != matrix) {
		if (startVert<1 || endVert>numberOfVert)
		{
			oss1 << L"Вершины заданы неверно" << L"\t";
			SetWindowText(hWndOutput0, oss1.str().c_str());
			return;
		}
		oss1 << L"Матрица смежности из файла: " << fileName << "\r\n";
		for (int i = 0; i < numberOfVert; ++i)
		{
			oss1 << "\r\n";;
			for (int j = 0; j < numberOfVert; ++j)
			{
				int w =(int) matrix->getWeight(i, j);
				oss1 << w << L"\t";;
			}
		}

	}
	else
	{
		oss1.str(L"");
		oss1 << L"Файл не найден";
		SetWindowText(hWndOutput0, oss1.str().c_str());
		return;
	}
	SetWindowText(hWndOutput0, oss1.str().c_str());
	testDeikstra(hWndOutput0, hWndOutput1, hWndOutput2, alg, startVert, endVert, matrixEnum, matrix, fileName);
	testfloydWarshall(hWndOutput0, hWndOutput1, hWndOutput2, alg, startVert, endVert, matrixEnum, matrix, fileName);
}




