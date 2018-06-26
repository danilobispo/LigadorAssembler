#include "Ligador.h"



Ligador::Ligador()
{}


Ligador::~Ligador()
{
}

std::map<std::string, InfoDeUso> Ligador::fazerCorrecaoDeEnderecosNaTabelaDeUso(std::map<std::string, InfoDeUso> tabela, int fatorCorrecao)
{
	std::map<std::string, InfoDeUso> tabelaCopy = tabela;
	for (auto& itemTabela : tabelaCopy) {
		for (auto& valor : itemTabela.second.valorList) {
			valor += fatorCorrecao;
		}
	}

	/*DEBUG
	for (auto& itemTabela : tabelaCopy) {
		for (auto& valor : itemTabela.second.valorList) {
			std::cout << "Simbolo: " << itemTabela.first << std::endl;
			std::cout << "Valor: " << valor << std::endl;
		}
	}*/

	return tabelaCopy;
}

std::map<std::string, InfoDeDefinicao> Ligador::fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(std::map<std::string, InfoDeDefinicao> tabela, int fatorCorrecao)
{
	std::map<std::string, InfoDeDefinicao> tabelaCopy = tabela;
	for (auto& itemTabela : tabelaCopy) {
			itemTabela.second.valor += fatorCorrecao;
	}

	// DEBUG
	/*for (auto& itemTabela : tabelaCopy) {
		std::cout << "Simbolo: " << itemTabela.first << std::endl;
		std::cout << "Valor: " << itemTabela.second.valor << std::endl;
	}*/
	return tabelaCopy;
}

std::vector<int> Ligador::alinharCodigosFonte(std::vector<int> codigoFonte1, std::vector<int> codigoFonte2)
{
	codigoFonte1.insert(codigoFonte1.end(), codigoFonte2.begin(), codigoFonte2.end());
	for (auto &valor : codigoFonte1) {
		std::cout << "Valor: " << valor << std::endl; 
	}
	return codigoFonte1;
}

std::vector<int> Ligador::alinharMapasDeBits(std::vector<int> mapaDeBits1, std::vector<int> mapaDeBits2)
{
	mapaDeBits1.insert(mapaDeBits1.end(), mapaDeBits2.begin(), mapaDeBits2.end());
	for (auto &valor : mapaDeBits1) {
		std::cout << "Valor do mapaBits: " << valor << std::endl;
	}
	return mapaDeBits1;
}

std::vector<int> Ligador::fazerCorrecaoDeEnderecosNoCodigoFonte(
	std::vector<int> codigoFonteFinal,
	std::vector<int> mapaDeBitsFinal, 
	std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes,
	std::map<std::string, InfoDeUso> tabelaDeUsoPrimeiroArquivo,
	std::map<std::string, InfoDeUso> tabelaDeUsoSegundoArquivo) {
	std::cout << "Size codigo fonte: " << codigoFonteFinal.size() << std::endl;
	std::cout << "Size mapa de bits: " << mapaDeBitsFinal.size() << std::endl;

	for (int i = 0; i < mapaDeBitsFinal.size(); i++) {
		if (mapaDeBitsFinal[i] == 1) { // Se a posição do mapa de bits tiver 1, significa que o programa precisa resolver um endereço realocado
			for (auto& itemTabelaDeUso : tabelaDeUsoPrimeiroArquivo) { // Busca utilização na primeira tabela de uso
				for (auto& valorTab : itemTabelaDeUso.second.valorList) {
					if (valorTab == i) {
						std::string nomeVariavel = itemTabelaDeUso.first;
						codigoFonteFinal[i] += tabelaGlobalDeDefinicoes.at(nomeVariavel).valor; //Soma com o valor final
					}
				}
			}
			for (auto& itemTabelaDeUso : tabelaDeUsoSegundoArquivo) {
				for (auto& valorTab : itemTabelaDeUso.second.valorList) { // Ou se foi na segunda tabela de uso
					if (valorTab == i) {
						std::string nomeVariavel = itemTabelaDeUso.first;
						codigoFonteFinal[i] += tabelaGlobalDeDefinicoes.at(nomeVariavel).valor; // Soma com o valor do local
					}
				}
			}
		}
	}
	return codigoFonteFinal;
}
