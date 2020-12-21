#pragma once

template<typename T>
class GraphMatrix {
private:
	T** _matrix;
	int _sizeMatrix;

public: GraphMatrix(int numberOfVert) {
	_sizeMatrix = numberOfVert;
	_matrix = (int**)malloc(sizeof(int) * numberOfVert);
	for (int i = 0; i < numberOfVert; i++) {
		_matrix[i] = (T*)malloc(sizeof(T) * numberOfVert);
	}
}
	  void addVert(int u, int v, T weight)
	  {
		  _matrix[u][v] = weight;
		  _matrix[v][u] = weight;
	  }
	  T& operator()(int u, int v)
	  {
		  return  this->_matrix[u][v];
	  }

	  T	getWeight(int u, int v)
	  {
		  return  this->_matrix[u][v];
	  }
	int getSize()
{
		return _sizeMatrix;
}
};
