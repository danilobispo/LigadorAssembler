#pragma once
#include "TabelaLib.h"
#include <iostream>
class Ligador
{
public:
	Ligador();
	~Ligador();

	std::map<std::string, InfoDeUso> fazerCorrecaoDeEnderecosNaTabelaDeUso(std::map<std::string, InfoDeUso> tabela, int fatorCorrecao);
	std::map<std::string, InfoDeDefinicao> fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela, int fatorCorrecao);
	std::vector<int> alinharCodigosFonte(std::vector<int> codigo1, std::vector<int> codigo2);
	std::vector<int> alinharMapasDeBits(std::vector<int> codigo1, std::vector<int> codigo2);
	std::vector<int> fazerCorrecaoDeEnderecosNoCodigoFonte(std::vector<int> codigoFonteFinal, std::vector<int> mapaDeBitsFinal, std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes, std::map<std::string, InfoDeUso> tabelaDeUsoPrimeiroArquivo, std::map<std::string, InfoDeUso> tabelaDeUsoSegundoArquivo);

};

