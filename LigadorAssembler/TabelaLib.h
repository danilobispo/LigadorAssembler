#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <vector>
#include <array>
#include <iostream>

enum opcodes {
	ADD = 1,
	SUB,
	MULT,
	DIV,
	JMP,
	JMPN,
	JMPP,
	JMPZ,
	COPY,
	LOAD,
	STORE,
	INPUT,
	OUTPUT,
	STOP
};

struct InfoDeInstrucoes {
	int numeroDeOperandos;
	int tamanho;
	opcodes opcodesInstrucoes;
};

struct InfoDeDefinicao {
	int valor;
	InfoDeDefinicao(int valor);
};

struct InfoDeUso {
	std::vector<int> valorList;
	InfoDeUso(int valor);
};

class TabelaLib
{
public:
	TabelaLib();
	~TabelaLib();

	std::map<std::string, InfoDeDefinicao> gerarTabelaGlobalDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela1, std::map<std::string, InfoDeDefinicao> tabela2);

	std::map<std::string, InfoDeDefinicao> gerarTabelaGlobalDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela1, std::map<std::string, InfoDeDefinicao> tabela2, std::map<std::string, InfoDeDefinicao> tabela3, std::map<std::string, InfoDeDefinicao> tabela4);

	std::map<std::string, InfoDeDefinicao> gerarTabelaGlobalDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela1, std::map<std::string, InfoDeDefinicao> tabela2, std::map<std::string, InfoDeDefinicao> tabela3);

	//Tabela de definições
	void insereSimboloNaTabelaDeDefinicoes(std::string, InfoDeDefinicao, std::map<std::string, InfoDeDefinicao>);
	/*bool rotuloJaExistenteNaTabelaDeDefinicoes(std::string rotulo);
	InfoDeDefinicao obtemSimboloNaTabelaDeDefinicoes(std::string id);*/

private:
	static std::map<std::string, InfoDeInstrucoes> TabelaDeInstrucoes;
	static std::map<std::string, InfoDeDefinicao> TabelaDeDefinicoes;
	static std::map<std::string, InfoDeUso> TabelaDeUso;
};

