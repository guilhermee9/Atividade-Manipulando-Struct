/*
Título: Atividade: Manipulando Struct
Autor: Profe. Berssa
Data: 2024.10.11
*/




#include <iostream>
#include <string>
#include <algorithm>  // Para usar a função sort()
#include <limits>     // Para usar numeric_limits
#include <iomanip>  // Para usar setw e ajustar a largura das colunas

using namespace std;

// Definindo a struct Pessoa
struct Pessoa {
    int codigo;
    string nome;
    float altura;
};

// Função para aguardar que o usuário pressione Enter
void esperarEnter() {
    cout << "\nPressione Enter para continuar...";
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpa qualquer caractere no buffer e aguarda o Enter
    cin.get();  // Aguarda o usuário pressionar Enter
}

// Função para limpar o buffer de entrada
void limparBuffer() {
    cin.clear();  // Limpa o estado de erro
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora entradas inválidas no buffer
}

// Função genérica para exibir mensagens de erro
void exibirMensagemErro(const string &mensagem) {
    cout << mensagem << endl;
}

// Função para ler uma string válida
string lerStringValida(const string &mensagem) {
    string entrada;
    cout << mensagem;
    getline(cin, entrada);  // Usa getline para aceitar entradas com espaços
    return entrada;
}

// Função para ler um número inteiro válido
int lerCodigoValido(const string &mensagem) {
    int numero;
    while (true) {
        cout << mensagem;
        cin >> numero;
        if (cin.fail()) {
            limparBuffer();  // Limpa o estado de erro e o buffer
            exibirMensagemErro("Entrada inválida! Por favor, insira um número inteiro.");
        } else {
            limparBuffer();  // Limpa o buffer após a entrada válida
            return numero;
        }
    }
}

// Função para ler uma altura válida
float lerAlturaValida(const string &mensagem) {
    float altura;
    while (true) {
        cout << mensagem;
        cin >> altura;
        if (cin.fail() || altura <= 0) {
            limparBuffer();  // Limpa o estado de erro e o buffer
            exibirMensagemErro("Entrada inválida! Por favor, insira uma altura válida (acima de 0).");
        } else {
            limparBuffer();  // Limpa o buffer após a entrada válida
            return altura;
        }
    }
}

// Função para zerar o array de pessoas
void zerarArray(Pessoa array[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        array[i].codigo = 0;
        array[i].nome = "";
        array[i].altura = 0.0;
    }
    cout << "Array de pessoas zerado!";
    esperarEnter();  // Espera o usuário pressionar Enter
}

// Função para mostrar o array de pessoas com alinhamento
void mostrarArray(Pessoa array[], int tamanho) {
    // Título das colunas com alinhamento
    cout << left << setw(10) << "Código" << "\t" 
         << left << setw(20) << "Nome" << "\t"
         << left << setw(10) << "Altura" << endl;

    // Linha divisória
    cout << string(50, '-') << endl;

    // Exibe cada pessoa no array com as colunas alinhadas
    for (int i = 0; i < tamanho; i++) {
        cout << left << setw(10) << array[i].codigo << "\t"
             << left << setw(20) << array[i].nome << "\t"
             << left << setw(10) << array[i].altura << "m" << endl;
    }

    esperarEnter();  // Espera o usuário pressionar Enter
}

// Função para preencher o array de pessoas com entradas do usuário
void preencherArray(Pessoa array[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        array[i].codigo = lerCodigoValido("Digite o código da pessoa [" + to_string(i) + "]: ");
        //limparBuffer();  // Limpa o buffer antes de capturar a string
        array[i].nome = lerStringValida("Digite o nome da pessoa [" + to_string(i) + "]: ");
        array[i].altura = lerAlturaValida("Digite a altura da pessoa [" + to_string(i) + "] (em metros): ");
    }
    cout << "Array de pessoas preenchido manualmente!";
    esperarEnter();  // Espera o usuário pressionar Enter
}

// Função para editar uma pessoa em uma posição específica do array
void editarArray(Pessoa array[], int tamanho) {
    int posicao = lerCodigoValido("Digite a posição que deseja editar (0 a " + to_string(tamanho - 1) + "): ");

    // Garante que a posição esteja dentro dos limites do array
    while (posicao < 0 || posicao >= tamanho) {
        exibirMensagemErro("Posição inválida! Tente novamente.");
        posicao = lerCodigoValido("Digite uma posição válida: ");
    }

    array[posicao].codigo = lerCodigoValido("Digite o novo código para a posição [" + to_string(posicao) + "]: ");
    limparBuffer();  // Limpa o buffer antes de capturar a string
    array[posicao].nome = lerStringValida("Digite o novo nome para a posição [" + to_string(posicao) + "]: ");
    array[posicao].altura = lerAlturaValida("Digite a nova altura para a posição [" + to_string(posicao) + "] (em metros): ");
    cout << "Pessoa editada com sucesso!";
    esperarEnter();  // Espera o usuário pressionar Enter
}

// Função para verificar se uma pessoa está presente no array por código
void verificarPessoa(Pessoa array[], int tamanho) {
    int codigo = lerCodigoValido("Digite o código da pessoa que deseja verificar: ");
    bool encontrado = false;

    // Verifica se o código está no array
    for (int i = 0; i < tamanho; i++) {
        if (array[i].codigo == codigo) {
            cout << "Pessoa com código '" << codigo << "' encontrada: Nome: " << array[i].nome << ", Altura: " << array[i].altura << "m" << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Pessoa com código '" << codigo << "' não encontrada." << endl;
    }

    esperarEnter();  // Espera o usuário pressionar Enter
}

// Função para ordenar o array de pessoas pelo código
void ordenarArray(Pessoa array[], int tamanho) {
    sort(array, array + tamanho, [](Pessoa a, Pessoa b) {
        return a.codigo < b.codigo;
    });
    cout << "Array de pessoas ordenado por código!";
    esperarEnter();  // Espera o usuário pressionar Enter
}

// Função que exibe o menu e retorna a escolha do usuário
int menu() {
    cout << "\nEscolha uma opção:\n";
    cout << "1 - Mostrar array de pessoas\n";
    cout << "2 - Zerar array de pessoas\n";
    cout << "3 - Preencher array de pessoas\n";
    cout << "4 - Editar pessoa no array\n";
    cout << "5 - Verificar pessoa no array\n";
    cout << "6 - Ordenar array de pessoas por código\n";
    cout << "0 - Sair\n";
    return lerCodigoValido("Opção: ");
}

int main() {
    const int TAMANHO = 5;  // Define o tamanho do array de pessoas
    Pessoa array[TAMANHO];  // Declara o array para armazenar 5 registros de pessoas

    int opcao;

    do {
        opcao = menu();  // Mostra o menu e lê a opção do usuário

        switch (opcao) {
            case 1:
                mostrarArray(array, TAMANHO);
                break;
            case 2:
                zerarArray(array, TAMANHO);
                break;
            case 3:
                preencherArray(array, TAMANHO);
                break;
            case 4:
                editarArray(array, TAMANHO);
                break;
            case 5:
                verificarPessoa(array, TAMANHO);
                break;
            case 6:
                ordenarArray(array, TAMANHO);
                break;
            case 0:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                exibirMensagemErro("Opção inválida! Escolha uma opção válida.");
                break;
        }
    } while (opcao != 0);  // O programa continua executando até que o usuário escolha sair

    return 0;
}
