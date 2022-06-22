#pragma once
#include <vector>
#include "EMath.h"
class Parser 
{
public:
	Parser ();
	~Parser () = default;

	void Parse();
	std::vector<Elite::FPoint3> GetVertices();
	std::vector<int>GetIndex();
private:
	std::vector<Elite::FPoint3> m_VertexList;
	std::vector<int> m_indexlist;
};

