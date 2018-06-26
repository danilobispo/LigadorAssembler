#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <locale>
#include "TabelaLib.h"
class ParseLib
{
public:
	ParseLib();
	~ParseLib();

	// Etapas de parse
	std::vector<std::string> parseArquivo(std::string arquivoString);
	std::vector<int> parseCodigoFonte(std::vector<std::string> conteudoArquivo);
	std::vector<int> parseMapaDeBits(std::vector<std::string> conteudoArquivo);
	std::map<std::string, InfoDeUso> parseTabelaDeUso(std::vector<std::string> conteudoArquivo);
	std::map<std::string, InfoDeDefinicao> parseTabelaDeDefinicoes(std::vector<std::string> conteudoArquivo);

	int criarFatorDeCorrecao(std::vector<std::string> conteudoArquivo);
	
	// Funções auxiliares
	std::vector<std::string> separaEmLinhas(std::string fileString);
	int converteStringParaInt(std::string operando);
};

