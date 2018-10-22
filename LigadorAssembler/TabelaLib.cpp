#include "TabelaLib.h"


TabelaLib::TabelaLib(){}
TabelaLib::~TabelaLib(){}

std::map<std::string, InfoDeDefinicao> TabelaDeDefinicoes;
std::map<std::string, InfoDeUso> TabelaDeUso;

std::map <std::string, InfoDeInstrucoes> TabelaLib::TabelaDeInstrucoes{
{ "add",{ 1,2, opcodes::ADD } },
{ "sub",{ 1,2, opcodes::SUB } },
{ "mult",{ 1,2, opcodes::MULT } },
{ "div",{ 1,2, opcodes::DIV } },
{ "jmp",{ 1,2, opcodes::JMP } },
{ "jmpn",{ 1,2,opcodes::JMPN } },
{ "jmpp",{ 1,2, opcodes::JMPP } },
{ "jmpz",{ 1,2, opcodes::JMPZ } },
{ "copy",{ 2,3, opcodes::COPY } },
{ "load",{ 1,2, opcodes::LOAD } },
{ "store",{ 1,2,opcodes::STORE } },
{ "input",{ 1,2, opcodes::INPUT } },
{ "output",{ 1,2,opcodes::OUTPUT } },
{ "stop",{ 0,1, opcodes::STOP } }
};


InfoDeDefinicao::InfoDeDefinicao(int valor) : valor(valor) {}
InfoDeUso::InfoDeUso(int valor){valorList.push_back(valor);}

std::map<std::string, InfoDeDefinicao> TabelaLib::gerarTabelaGlobalDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela1, std::map<std::string, InfoDeDefinicao> tabela2) {
	std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes = tabela1;
	tabelaGlobalDeDefinicoes.insert(tabela2.begin(), tabela2.end());
	for (auto& itemDef : tabelaGlobalDeDefinicoes) {
		std::cout << "Simbolo TGD: " << itemDef.first << std::endl;
		std::cout << "Valor TGD: " << itemDef.second.valor << std::endl;

	}

	return tabelaGlobalDeDefinicoes;
}

std::map<std::string, InfoDeDefinicao> TabelaLib::gerarTabelaGlobalDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela1, std::map<std::string, 
	InfoDeDefinicao> tabela2, 
	std::map<std::string, InfoDeDefinicao> tabela3,
	std::map<std::string, InfoDeDefinicao> tabela4) {
	std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes = tabela1;
	tabelaGlobalDeDefinicoes.insert(tabela2.begin(), tabela2.end());
	tabelaGlobalDeDefinicoes.insert(tabela3.begin(), tabela3.end());
	tabelaGlobalDeDefinicoes.insert(tabela4.begin(), tabela4.end());
	for (auto& itemDef : tabelaGlobalDeDefinicoes) {
		std::cout << "Simbolo TGD: " << itemDef.first << std::endl;
		std::cout << "Valor TGD: " << itemDef.second.valor << std::endl;

	}

	return tabelaGlobalDeDefinicoes;
}

std::map<std::string, InfoDeDefinicao> TabelaLib::gerarTabelaGlobalDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela1, std::map<std::string,
	InfoDeDefinicao> tabela2,
	std::map<std::string, InfoDeDefinicao> tabela3) {
	std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes = tabela1;
	tabelaGlobalDeDefinicoes.insert(tabela2.begin(), tabela2.end());
	tabelaGlobalDeDefinicoes.insert(tabela3.begin(), tabela3.end());
	for (auto& itemDef : tabelaGlobalDeDefinicoes) {
		std::cout << "Simbolo TGD: " << itemDef.first << std::endl;
		std::cout << "Valor TGD: " << itemDef.second.valor << std::endl;

	}

	return tabelaGlobalDeDefinicoes;
}
