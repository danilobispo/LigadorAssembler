// LigadorAssembler.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "ParseLib.h"
#include "Ligador.h"


int main(int argc, char* argv[])
{
	int numberOfFiles = argc - 1;
	std::ifstream primeiroArquivo;
	std::ifstream segundoArquivo;
	std::string nomePrimeiroArquivo;
	std::string nomeSegundoArquivo;

	std::stringstream bufferPrimeiroArquivo;
	std::stringstream bufferSegundoArquivo;

	// Saídas do primeiro arquivo
	std::map<std::string, InfoDeDefinicao> tabelaDeDefinicaoPrimeiroArquivo;
	std::map<std::string, InfoDeUso> tabelaDeUsoPrimeiroArquivo;
	std::vector<int> codigoFontePrimeiroArquivo;
	std::vector<int> mapaDeBitsPrimeiroArquivo;
	int fatorDeCorrecao;

	// Saídas do segundo arquivo
	std::map<std::string, InfoDeDefinicao> tabelaDeDefinicaoSegundoArquivo;
	std::map<std::string, InfoDeUso> tabelaDeUsoSegundoArquivo;
	std::vector<int> codigoFonteSegundoArquivo;
	std::vector<int> mapaDeBitsSegundoArquivo;

	// Arquivo de saída
	std::ofstream arquivoDeSaida;

	ParseLib parseLib;

	if (numberOfFiles == 2) {
		nomePrimeiroArquivo = argv[1];
		nomeSegundoArquivo = argv[2];
		primeiroArquivo.open(nomePrimeiroArquivo);
		if (primeiroArquivo.is_open() && primeiroArquivo.good()) {
			bufferPrimeiroArquivo << primeiroArquivo.rdbuf();
			std::vector<std::string> linhasDoArquivo = parseLib.parseArquivo(bufferPrimeiroArquivo.str());
			tabelaDeDefinicaoPrimeiroArquivo = parseLib.parseTabelaDeDefinicoes(linhasDoArquivo);
			tabelaDeUsoPrimeiroArquivo = parseLib.parseTabelaDeUso(linhasDoArquivo);
			codigoFontePrimeiroArquivo = parseLib.parseCodigoFonte(linhasDoArquivo);
			mapaDeBitsPrimeiroArquivo = parseLib.parseMapaDeBits(linhasDoArquivo);
			std::cout << "Tamanho primeiro arquivo: " << codigoFontePrimeiroArquivo.size() << std::endl;
			fatorDeCorrecao = parseLib.criarFatorDeCorrecao(linhasDoArquivo);
			std::cout << "Tamanho primeiro arquivo: " << fatorDeCorrecao << std::endl;
			primeiroArquivo.close();
		}
		segundoArquivo.open(nomeSegundoArquivo);
		if (segundoArquivo.is_open() && segundoArquivo.good()) {
			bufferSegundoArquivo << segundoArquivo.rdbuf();
			std::vector<std::string> linhasDoArquivo = parseLib.parseArquivo(bufferSegundoArquivo.str());
			tabelaDeDefinicaoSegundoArquivo = parseLib.parseTabelaDeDefinicoes(linhasDoArquivo);
			tabelaDeUsoSegundoArquivo = parseLib.parseTabelaDeUso(linhasDoArquivo);
			codigoFonteSegundoArquivo = parseLib.parseCodigoFonte(linhasDoArquivo);
			mapaDeBitsSegundoArquivo = parseLib.parseMapaDeBits(linhasDoArquivo);
			segundoArquivo.close();
		}
		// Processo de ligação se inicia aqui:
		Ligador ligador;
		tabelaDeDefinicaoSegundoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(tabelaDeDefinicaoSegundoArquivo, fatorDeCorrecao);
		tabelaDeUsoSegundoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeUso(tabelaDeUsoSegundoArquivo, fatorDeCorrecao);
		TabelaLib tabelaLib;
		std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes = 
			tabelaLib.gerarTabelaGlobalDeDefinicoes(tabelaDeDefinicaoPrimeiroArquivo, tabelaDeDefinicaoSegundoArquivo);
		std::vector<int> codigoFonteParcial = ligador.alinharCodigosFonte(codigoFontePrimeiroArquivo, codigoFonteSegundoArquivo);
		std::vector<int> mapasDeBitsFinal = ligador.alinharMapasDeBits(mapaDeBitsPrimeiroArquivo, mapaDeBitsSegundoArquivo);

		std::vector<int> codigoFonteFinal = ligador.fazerCorrecaoDeEnderecosNoCodigoFonte(codigoFonteParcial, mapasDeBitsFinal, tabelaGlobalDeDefinicoes,
			tabelaDeUsoPrimeiroArquivo, tabelaDeUsoSegundoArquivo);
		arquivoDeSaida.open("arquivo_saida.o");

		for (auto& itemCodigoFinal : codigoFonteFinal) {
			arquivoDeSaida << itemCodigoFinal << " ";
		}
		arquivoDeSaida.close();
	}
	else if (numberOfFiles == 1)
	{
		nomePrimeiroArquivo = argv[1];
		primeiroArquivo.open(nomePrimeiroArquivo);
		if (primeiroArquivo.is_open() && primeiroArquivo.good()) {
			bufferPrimeiroArquivo << primeiroArquivo.rdbuf();
			primeiroArquivo.close();
		}
	}
	else
	{
		std::cout << "Número inválido de parâmetros!" << std::endl;
		std::cout << "Aperte ENTER para sair";
		getchar();
		return -1;
	}
	std::cout << "Aperte ENTER para sair";
	getchar();
    return 0;
}

