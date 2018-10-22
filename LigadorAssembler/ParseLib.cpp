#include "ParseLib.h"



ParseLib::ParseLib()
{
}


ParseLib::~ParseLib()
{
}

std::vector<std::string> ParseLib::parseArquivo(std::string conteudoArquivo)
{
	std::vector<std::string> linhasDoArquivo = separaEmLinhas(conteudoArquivo);
	return linhasDoArquivo;
}

std::vector<int> ParseLib::parseCodigoFonte(std::vector<std::string> conteudoArquivo)
{
	std::string linhaCodigo;
	for (int i = 0; i < conteudoArquivo.size(); i++) {
		for (int j = 0; j < conteudoArquivo.size(); j++) {
			if (conteudoArquivo[i].find("CODE") != std::string::npos) {
				linhaCodigo = conteudoArquivo[i+1];
			}
		}
	}

	std::vector<int> vetorCodigo;
	std::stringstream stream(linhaCodigo);
	int n; 
	while (stream >> n) { 
		vetorCodigo.push_back(n);
	}
	std::cout << std::endl;
	return vetorCodigo;
}

std::vector<int> ParseLib::parseMapaDeBits(std::vector<std::string> conteudoArquivo)
{
	std::string linhaCodigo;
	for (auto& linhasArquivo : conteudoArquivo) {
		if (linhasArquivo[0] == 'R') {
			linhaCodigo = linhasArquivo;
		}
	}

	linhaCodigo.erase(0, 2);
	std::vector<int> vetorCodigo;
	for(int i = 0; i < linhaCodigo.size() ; i++) {
		std::cout << "Numero: " << linhaCodigo[i] << std::endl;
		vetorCodigo.push_back(linhaCodigo[i] - '0'); // Conversão para inteiro
	}
	std::cout << std::endl;
	return vetorCodigo;
}

std::map<std::string, InfoDeUso> ParseLib::parseTabelaDeUso(std::vector<std::string> conteudoArquivo)
{
	std::map<std::string, InfoDeUso> tabelaDeUso;
	TabelaLib tabelaLib;
	std::vector<std::string> linhasDeUso; // Linhas que dizem respeito a tabela de definições
	for (auto& linhaArquivo : conteudoArquivo) {
		if (linhaArquivo[0] == 'U') {
			linhasDeUso.push_back(linhaArquivo);
		}
	}

	for (auto& linhaDef : linhasDeUso) {
		std::string copia = linhaDef;
		std::string nomeVariavel;
		std::string valor;
		int valorInteiro;
		std::string temp;

		temp = copia.substr(copia.find(',') + 1, copia.size());
		nomeVariavel = temp.substr(0, temp.find(','));
		valor = temp.substr(temp.find(',') + 1, temp.size());
		valorInteiro = converteStringParaInt(valor);

		InfoDeUso infoDeUso = InfoDeUso(valorInteiro);
		if (!(tabelaDeUso.find(nomeVariavel) == tabelaDeUso.end())) { // Se já temos uma variável X inclusa na tabela, apenas adicionamos mais um valor
			tabelaDeUso.at(nomeVariavel).valorList.push_back(infoDeUso.valorList[0]);
		}
		else {
			tabelaDeUso.insert(std::make_pair(nomeVariavel, InfoDeUso(valorInteiro)));
		}
	}

	//DEBUG
	/*for (auto &itemDef : tabelaDeUso) {
		for (auto &valor : itemDef.second.valorList) {
			std::cout << "Simbolo: " << itemDef.first << std::endl;
			std::cout << "Valor: " << valor << std::endl;
			}
		}*/
	return tabelaDeUso;
}

std::map<std::string, InfoDeDefinicao> ParseLib::parseTabelaDeDefinicoes(std::vector<std::string> conteudoArquivo)
{
	std::map<std::string, InfoDeDefinicao> tabelaDeDefinicoes;
	TabelaLib tabelaLib;
	std::vector<std::string> linhasDeDefinicao; // Linhas que dizem respeito a tabela de definições
	for (auto& linhaArquivo : conteudoArquivo) {
		if (linhaArquivo[0] == 'D') {
			linhasDeDefinicao.push_back(linhaArquivo);
		}
	}

	
	// Agora fazemos o parse das informações da linha e inserimos em nossa tabela de definições
	// A linha tem o seguinte formato:
	// D,[nome_variável],[valor]
	for (auto& linhaDef : linhasDeDefinicao) {
		std::string copia = linhaDef;
		std::string nomeVariavel;
		std::string valor;
		int valorInteiro;
		std::string temp;

		temp = copia.substr(copia.find(',') + 1, copia.size());
		nomeVariavel = temp.substr(0, temp.find(','));
		valor = temp.substr(temp.find(',') + 1, temp.size());
		valorInteiro = converteStringParaInt(valor);
		tabelaDeDefinicoes.insert(std::make_pair(nomeVariavel, InfoDeDefinicao(valorInteiro)));
	}

	//DEBUG
	/*for (auto &itemDef : tabelaDeDefinicoes) {
		std::cout << "Simbolo: " << itemDef.first << std::endl;
		std::cout << "Valor: " << itemDef.second.valor << std::endl;
	}*/

	return tabelaDeDefinicoes;
}

int ParseLib::criarFatorDeCorrecao(std::vector<std::string> linhasDoCodigo)
{
	std::string linhaSize;
	for (auto& linhasArquivo : linhasDoCodigo) {
		if (linhasArquivo[0] == 'S') {
			linhaSize = linhasArquivo;
		}
	}
	
	int tamanhoCodigo;
	std::string sizeOfCode = linhaSize.substr(2, linhaSize.length());
	tamanhoCodigo = converteStringParaInt(sizeOfCode);
	// DEBUG
	//std::cout << "Tamanho do codigo: " << tamanhoCodigo << std::endl;
	return tamanhoCodigo;
}

std::vector<std::string> ParseLib::separaEmLinhas(std::string fileString) {
	std::vector<std::string> strings;
	const std::string delimiter = "\n";

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = fileString.find(delimiter, prev)) != std::string::npos) {
		strings.push_back(fileString.substr(prev, pos - prev));
		prev = pos + 1;
	}

	// To get the last substring (or only, if delimiter is not found)
	strings.push_back(fileString.substr(prev));

	return strings;
}

int ParseLib::converteStringParaInt(std::string operando) {
	return std::stoi(operando);
}

