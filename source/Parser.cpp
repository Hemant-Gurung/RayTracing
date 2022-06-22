#include "Parser.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <fstream>
Parser::Parser()
{

}

void Parser::Parse()
{
	//// using ifstream to read files
	std::ifstream fs("lowpoly_bunny.obj");
	//std::ifstream fs("octa-color.obj");
	// compare string
	std::string lineStr;

	// read first word of file
	char c = fs.get();
	// if fs is not null
	std::ifstream infile;
	while (std::getline(fs, lineStr))
	{
		int indx{};
		std::stringstream ss(lineStr);
		std::string word;
		// seperate into word
		ss >> word;

		// if the line starts with v then we stor the numbers after that in vertex list
		if (word == "v")
		{
			Elite::FPoint3 vertex;
			int index{1};
			
			// as long as string stream ss is valid/ has words in in
			while (ss >> word)
			{
				// store x component
				if (index == 1)
				{
					index++;
					vertex.x = std::stof(word);
				}
				// store y component
				else if (index == 2)
				{
					index++;
					vertex.y = std::stof(word);
				}
				// store z component
				else if (index ==3 )
				{
					index++;
					vertex.z = std::stof(word);
				}
			}
			// in the end add those vertex into the vertex list
			//vertex.y += 3.5f;
			m_VertexList.push_back(vertex);
		}
		
		// seperate into int
		//ss >> word;
		else if (word == "f")
		{
			Elite::FVector3 indexBuffer;
			int index{};
			
			// as long as string stream ss is valid/ has words in in
			while (ss >> word)
			{
				// store x component
				int a = std::stoi(word);
				m_indexlist.push_back(a);
			}
			// in the end add those vertex into the vertex list
			
		}
	}
	fs.close();


	
}

std::vector<Elite::FPoint3> Parser::GetVertices()
{
	return m_VertexList;
}

std::vector<int> Parser::GetIndex()
{
	return m_indexlist;
}
