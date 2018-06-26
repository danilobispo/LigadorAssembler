#pragma once
#include <sstream>
class ParseLib
{
public:
	ParseLib();
	~ParseLib();
	void parseArquivo(std::string nomeArquivo);
	void parseCodigoFonte();
	void parseMapaDeBits(std::stringstream mapaBits);
	void parseTabelaDeUso();
	void parseTabelaDeDefinicoes();
	


};

