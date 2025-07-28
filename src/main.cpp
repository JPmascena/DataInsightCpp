#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    ifstream arquivo("dados.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo CSV." << endl;
        return 1;
    }

    string linha;
    vector<float> notas;

    // Ignora o cabeçalho
    getline(arquivo, linha);

    // Lê o arquivo linha por linha
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, notaStr;
        getline(ss, nome, ',');
        getline(ss, notaStr, ',');

        try {
            float nota = stof(notaStr);
            notas.push_back(nota);
        } catch (...) {
            cout << "Erro ao converter a nota: " << notaStr << endl;
        }
    }

    arquivo.close();

    if (notas.empty()) {
        cout << "Nenhuma nota válida foi lida." << endl;
        return 1;
    }

    // Média
    float soma = 0;
    for (float n : notas) soma += n;
    float media = soma / notas.size();

    // Mediana
    sort(notas.begin(), notas.end());
    float mediana;
    int n = notas.size();
    if (n % 2 == 0)
        mediana = (notas[n/2 - 1] + notas[n/2]) / 2.0;
    else
        mediana = notas[n/2];

    // Desvio padrão
    float somaQuadrados = 0;
    for (float nota : notas)
        somaQuadrados += pow(nota - media, 2);
    float desvioPadrao = sqrt(somaQuadrados / n);

    // Mínimo e máximo
    float minimo = notas.front();
    float maximo = notas.back();

    // Exibe os resultados
    cout << "\n📊 Estatísticas:" << endl;
    cout << "------------------------" << endl;
    cout << "Quantidade:      " << n << endl;
    cout << "Média:           " << media << endl;
    cout << "Mediana:         " << mediana << endl;
    cout << "Desvio padrão:   " << desvioPadrao << endl;
    cout << "Nota mínima:     " << minimo << endl;
    cout << "Nota máxima:     " << maximo << endl;

    return 0;
}

