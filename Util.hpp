#pragma once
#include <fstream>
#include <iostream>
#include <random>
#include <boost/archive/text_oarchive.hpp>
#include <boost/interprocess/mapped_region.hpp>


enum class Alg {
	Alg1,
	Alg2
};
enum class Matrix {
	Matrix1,
	Matrix2,
	Matrix3
};

//int integerCompare(int a, int b) {
//    if (a > b) {
//        return 1;
//    }
//    else if (a < b) {
//        return 0;
//    }
//    else {
//        return 2;
//    }
//}


inline bool chckValue(const int* arr, int size, int x) {
	bool res = false;
	for (int i = 0; i < size; ++i) {
		if (arr[i] == x) {
			res = true;
		}
	}
	return res;
}

inline int* getRandomNumbers(int min, int max) {
	static const auto fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	auto* values = new int[max - min];
	auto size = 0;
	for (auto i = min; i < max; ++i) {
		const auto value = static_cast<int>(rand() * fraction * (max - min + 1) + min);
		if (!chckValue(values, size, value)) {
			values[i] = value;
			size++;
		}
		else {
			i--;
		}
	}
	return values;
}

inline std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

template<typename T>
T** loadMatrix(std::wstring fileName, int& _numberOfVert)
{

	std::wstring path = L"c:\\tmp\\Lab3_3sem\\";
	path.append(fileName).append(L".txt");
	std::ifstream file(path);
	if(file.fail())
	{
		return nullptr;
	}
	int numberOfVert;
	file >> numberOfVert;
	_numberOfVert = numberOfVert;
	std::cout << numberOfVert << std::endl;
	//Матрица смежности с весами ребер графа(777 - ребра нет, 0 ребро в себя)
	T** _matrix = (T**)malloc(sizeof(T) * numberOfVert);
	for (int i = 0; i < numberOfVert; i++) {
		_matrix[i] = (T*)malloc(sizeof(int) * numberOfVert);
	}

	//Считываем матрицу весов ребер
	for (int i = 0; i < numberOfVert; i++) {
		for (int j = 0; j < numberOfVert; j++) {
			file >> _matrix[i][j];
		}
	}

	file.close();
	return _matrix;
}

inline void writeToCSV(std::wstring fileName, std::string outputData)
{
	
	std::wstring path = L"c:\\tmp\\Lab3_3sem\\";
	path.append(fileName).append(L".csv");
	std::ofstream file;
	
	file.open(path);
	file << outputData;
	file.close();
}