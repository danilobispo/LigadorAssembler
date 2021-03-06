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
	std::ifstream terceiroArquivo;
	std::ifstream quartoArquivo;
	std::string nomePrimeiroArquivo;
	std::string nomeSegundoArquivo;
	std::string nomeTerceiroArquivo;
	std::string nomeQuartoArquivo;

	std::stringstream bufferPrimeiroArquivo;
	std::stringstream bufferSegundoArquivo;
	std::stringstream bufferTerceiroArquivo;
	std::stringstream bufferQuartoArquivo;

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

	// Saídas do terceiro arquivo
	std::map<std::string, InfoDeDefinicao> tabelaDeDefinicaoTerceiroArquivo;
	std::map<std::string, InfoDeUso> tabelaDeUsoTerceiroArquivo;
	std::vector<int> codigoFonteTerceiroArquivo;
	std::vector<int> mapaDeBitsTerceiroArquivo;

	// Saídas do quarto arquivo
	std::map<std::string, InfoDeDefinicao> tabelaDeDefinicaoQuartoArquivo;
	std::map<std::string, InfoDeUso> tabelaDeUsoQuartoArquivo;
	std::vector<int> codigoFonteQuartoArquivo;
	std::vector<int> mapaDeBitsQuartoArquivo;

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
		arquivoDeSaida.open(nomePrimeiroArquivo + ".e");

		for (auto& itemCodigoFinal : codigoFonteFinal) {
			arquivoDeSaida << itemCodigoFinal << " ";
		}
		arquivoDeSaida.close();
	}

	else if (numberOfFiles == 3) {

		nomePrimeiroArquivo = argv[1];
		nomeSegundoArquivo = argv[2];
		nomeTerceiroArquivo = argv[3];
		int fatorDeCorrecaoC;

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
			std::cout << "Tamanho Segundo arquivo: " << codigoFonteSegundoArquivo.size() << std::endl;
			fatorDeCorrecaoC = parseLib.criarFatorDeCorrecao(linhasDoArquivo);
			fatorDeCorrecaoC += fatorDeCorrecao;
			std::cout << "Tamanho Segundo+Primeiro arquivo: " << fatorDeCorrecaoC << std::endl;
			segundoArquivo.close();
		}
		terceiroArquivo.open(nomeTerceiroArquivo);
		if (terceiroArquivo.is_open() && terceiroArquivo.good()) {
			bufferTerceiroArquivo << terceiroArquivo.rdbuf();
			std::vector<std::string> linhasDoArquivo = parseLib.parseArquivo(bufferTerceiroArquivo.str());
			tabelaDeDefinicaoTerceiroArquivo = parseLib.parseTabelaDeDefinicoes(linhasDoArquivo);
			tabelaDeUsoTerceiroArquivo = parseLib.parseTabelaDeUso(linhasDoArquivo);
			codigoFonteTerceiroArquivo = parseLib.parseCodigoFonte(linhasDoArquivo);
			mapaDeBitsTerceiroArquivo = parseLib.parseMapaDeBits(linhasDoArquivo);
			terceiroArquivo.close();
		}

		// Processo de ligação se inicia aqui:
		Ligador ligador;
		tabelaDeDefinicaoSegundoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(tabelaDeDefinicaoSegundoArquivo, fatorDeCorrecao);
		tabelaDeUsoSegundoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeUso(tabelaDeUsoSegundoArquivo, fatorDeCorrecao);
		tabelaDeDefinicaoTerceiroArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(tabelaDeDefinicaoTerceiroArquivo, fatorDeCorrecaoC);
		tabelaDeUsoTerceiroArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeUso(tabelaDeUsoTerceiroArquivo, fatorDeCorrecaoC);
		TabelaLib tabelaLib;
		std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes =
			tabelaLib.gerarTabelaGlobalDeDefinicoes(tabelaDeDefinicaoPrimeiroArquivo, tabelaDeDefinicaoSegundoArquivo, tabelaDeDefinicaoTerceiroArquivo);
		std::vector<int> codigoFonteParcial = ligador.alinharCodigosFonte(codigoFontePrimeiroArquivo, codigoFonteSegundoArquivo);
		codigoFonteParcial = ligador.alinharCodigosFonte(codigoFonteParcial, codigoFonteTerceiroArquivo);
		std::vector<int> mapasDeBitsFinal = ligador.alinharMapasDeBits(mapaDeBitsPrimeiroArquivo, mapaDeBitsSegundoArquivo);
		mapasDeBitsFinal = ligador.alinharMapasDeBits(mapasDeBitsFinal, mapaDeBitsTerceiroArquivo);

		std::vector<int> codigoFonteFinal = ligador.fazerCorrecaoDeEnderecosNoCodigoFonte(codigoFonteParcial, mapasDeBitsFinal, tabelaGlobalDeDefinicoes,
			tabelaDeUsoPrimeiroArquivo, tabelaDeUsoSegundoArquivo, tabelaDeUsoTerceiroArquivo);

		arquivoDeSaida.open(nomePrimeiroArquivo + ".e");

		for (auto& itemCodigoFinal : codigoFonteFinal) {
			arquivoDeSaida << itemCodigoFinal << " ";
		}
		arquivoDeSaida.close();

	}
	else if (numberOfFiles == 4) {
		nomePrimeiroArquivo = argv[1];
		nomeSegundoArquivo = argv[2];
		nomeTerceiroArquivo = argv[3];
		nomeQuartoArquivo = argv[4];
		int fatorDeCorrecaoC;
		int fatorDeCorrecaoD;

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
			std::cout << "Tamanho Segundo arquivo: " << codigoFonteSegundoArquivo.size() << std::endl;
			fatorDeCorrecaoC = parseLib.criarFatorDeCorrecao(linhasDoArquivo);
			fatorDeCorrecaoC += fatorDeCorrecao;
			std::cout << "Tamanho Segundo+Primeiro arquivo: " << fatorDeCorrecaoC << std::endl;
			segundoArquivo.close();
		}
		terceiroArquivo.open(nomeTerceiroArquivo);
		if (terceiroArquivo.is_open() && terceiroArquivo.good()) {
			bufferTerceiroArquivo << terceiroArquivo.rdbuf();
			std::vector<std::string> linhasDoArquivo = parseLib.parseArquivo(bufferTerceiroArquivo.str());
			tabelaDeDefinicaoTerceiroArquivo = parseLib.parseTabelaDeDefinicoes(linhasDoArquivo);
			tabelaDeUsoTerceiroArquivo = parseLib.parseTabelaDeUso(linhasDoArquivo);
			codigoFonteTerceiroArquivo = parseLib.parseCodigoFonte(linhasDoArquivo);
			mapaDeBitsTerceiroArquivo = parseLib.parseMapaDeBits(linhasDoArquivo);
			std::cout << "Tamanho Segundo arquivo: " << codigoFonteSegundoArquivo.size() << std::endl;
			fatorDeCorrecaoD = parseLib.criarFatorDeCorrecao(linhasDoArquivo);
			fatorDeCorrecaoD += fatorDeCorrecaoC + fatorDeCorrecao;
			std::cout << "Tamanho Terceiro+Segundo+Primeiro arquivo: " << fatorDeCorrecaoD << std::endl;
			terceiroArquivo.close();
		}

		quartoArquivo.open(nomeQuartoArquivo);
		if (quartoArquivo.is_open() && quartoArquivo.good()) {
			bufferQuartoArquivo << quartoArquivo.rdbuf();
			std::vector<std::string> linhasDoArquivo = parseLib.parseArquivo(bufferTerceiroArquivo.str());
			tabelaDeDefinicaoTerceiroArquivo = parseLib.parseTabelaDeDefinicoes(linhasDoArquivo);
			tabelaDeUsoTerceiroArquivo = parseLib.parseTabelaDeUso(linhasDoArquivo);
			codigoFonteTerceiroArquivo = parseLib.parseCodigoFonte(linhasDoArquivo);
			mapaDeBitsTerceiroArquivo = parseLib.parseMapaDeBits(linhasDoArquivo);
			terceiroArquivo.close();
		}

		// Processo de ligação se inicia aqui:
		Ligador ligador;
		tabelaDeDefinicaoSegundoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(tabelaDeDefinicaoSegundoArquivo, fatorDeCorrecao);
		tabelaDeUsoSegundoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeUso(tabelaDeUsoSegundoArquivo, fatorDeCorrecao);
		tabelaDeDefinicaoTerceiroArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(tabelaDeDefinicaoTerceiroArquivo, fatorDeCorrecaoC);
		tabelaDeUsoTerceiroArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeUso(tabelaDeUsoTerceiroArquivo, fatorDeCorrecaoC);
		tabelaDeDefinicaoQuartoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeDefinicoes(tabelaDeDefinicaoTerceiroArquivo, fatorDeCorrecaoD);
		tabelaDeUsoQuartoArquivo = ligador.fazerCorrecaoDeEnderecosNaTabelaDeUso(tabelaDeUsoTerceiroArquivo, fatorDeCorrecaoD);

		TabelaLib tabelaLib;
		std::map<std::string, InfoDeDefinicao> tabelaGlobalDeDefinicoes =
			tabelaLib.gerarTabelaGlobalDeDefinicoes(tabelaDeDefinicaoPrimeiroArquivo, tabelaDeDefinicaoSegundoArquivo, tabelaDeDefinicaoTerceiroArquivo);
		std::vector<int> codigoFonteParcial = ligador.alinharCodigosFonte(codigoFontePrimeiroArquivo, codigoFonteSegundoArquivo);
		codigoFonteParcial = ligador.alinharCodigosFonte(codigoFonteParcial, codigoFonteTerceiroArquivo);
		codigoFonteParcial = ligador.alinharCodigosFonte(codigoFonteParcial, codigoFonteQuartoArquivo);
		std::vector<int> mapasDeBitsFinal = ligador.alinharMapasDeBits(mapaDeBitsPrimeiroArquivo, mapaDeBitsSegundoArquivo);
		mapasDeBitsFinal = ligador.alinharMapasDeBits(mapasDeBitsFinal, mapaDeBitsTerceiroArquivo);
		mapasDeBitsFinal = ligador.alinharMapasDeBits(mapasDeBitsFinal, mapaDeBitsQuartoArquivo);

		std::vector<int> codigoFonteFinal = ligador.fazerCorrecaoDeEnderecosNoCodigoFonte(codigoFonteParcial, mapasDeBitsFinal, tabelaGlobalDeDefinicoes,
			tabelaDeUsoPrimeiroArquivo, tabelaDeUsoSegundoArquivo, tabelaDeUsoTerceiroArquivo, tabelaDeUsoQuartoArquivo);

		arquivoDeSaida.open(nomePrimeiroArquivo + ".e");

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
			std::vector<std::string> linhasDoArquivo = parseLib.parseArquivo(bufferPrimeiroArquivo.str());
			codigoFontePrimeiroArquivo = parseLib.parseCodigoFonte(linhasDoArquivo);

			arquivoDeSaida.open(nomePrimeiroArquivo+".e");
			for (auto& itemCodigoFinal : codigoFontePrimeiroArquivo) {
				arquivoDeSaida << itemCodigoFinal << " ";
			}
			arquivoDeSaida.close();
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

