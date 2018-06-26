// LigadorAssembler.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char* argv[])
{
	// Faremos o parse do arquivo
	// Inicialmente pelo código-fonte, para isso teremos uma tabela semelhante a do montador
	// que nos dirá a instrução e o número de operandos de cada código respectivo
	// Depois de mapearmos as instruções e operandos, vamos verificar a TGD
	int numberOfFiles = argc - 1;
	std::ifstream primeiroArquivo;
	std::ifstream segundoArquivo;
	std::string nomePrimeiroArquivo;
	std::string nomeSegundoArquivo;

	std::stringstream bufferPrimeiroArquivo;
	std::stringstream bufferSegundoArquivo;

	if (numberOfFiles == 2) {
		nomePrimeiroArquivo = argv[1];
		nomePrimeiroArquivo = argv[2];
		primeiroArquivo.open(nomePrimeiroArquivo);
		if (primeiroArquivo.is_open() && primeiroArquivo.good()) {
			bufferPrimeiroArquivo << primeiroArquivo.rdbuf();
			primeiroArquivo.close();
		}
		segundoArquivo.open(nomeSegundoArquivo);
		if (segundoArquivo.is_open() && segundoArquivo.good()) {
			bufferSegundoArquivo << segundoArquivo.rdbuf();
			segundoArquivo.close();
		}
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

