// ----------------------------------------------**
// PROJETO II - RICARDO                          **
// Micael Jonathan - José Guilherme (P2)         **
// ----------------------------------------------**

#include <iostream>
#include <cstdlib> // Preciso para gerar um numero aleatorio
#include <ctime>  // Preciso para gerar um numero aleatorio
using namespace std;
// Definindo as structs Nolista(Candidatos), Atividade(Atividades) e Matrix
struct Nolista{
     string nome;
     int inscricao;
     string email;
     string curso;
     Nolista *prox;
     Nolista *ant;
     int freq; // Adicionado para organizar a frequencia dos candidatos ao sorteio
};

struct Sorteados{
    string nome;
    Sorteados *prox;
};

struct Atividade{
     string atv;
     string tipo_atv;
     string data;
     int hora;
     Atividade *prox;
};

struct Descritor{
     Nolista *ini;
     Nolista *fim;
};

bool** Matrix_Atividades; // Definindo ponteiro de boleanas junto as structs para melhor organização

// Funções de inicialização das duas listas
Descritor * criarlistaDupla(){
     Descritor *novo = new Descritor;
     novo -> ini = NULL;
     novo -> fim = NULL;
     return novo;
}
Atividade* criarlistaSimples(){
     return NULL;
}
//Função para preencher a lista de candidatos
void inserir_candidato(Descritor *&l, string nome, int inscricao, string email, string curso){
     Nolista *novo = new Nolista;
     novo -> nome = nome;
     novo -> inscricao = inscricao;
     novo -> email = email;
     novo -> curso = curso;
     novo -> prox = NULL;
     novo -> ant = NULL;
     // int freq não sera definido nesta função, sendo lixo até sua função ser chamada

     if(l -> ini == NULL){
          l -> ini = novo;
          l -> fim = novo;
     }
     else{
          l -> fim -> prox = novo;
          novo -> ant = l -> fim;
          l -> fim = novo;
     }
}

void imprimirCandidatos(Descritor *l){
     Nolista *p = l -> ini;
     while (p != NULL){
          cout << p->nome << " - ";
          cout << p->email << " - ";
          cout << p->inscricao<< " - ";
          cout << p->curso<< endl;
          p = p -> prox;
     }

}

// Função para prencher a lista de atividade e ler sua leitura

Atividade* gerarlista_atv(Atividade *&l, string atv, string tipo_atv, int hora, string data){
     Atividade *atv_bloco = new Atividade;
     atv_bloco -> atv = atv;
     atv_bloco -> tipo_atv = tipo_atv;
     atv_bloco -> data = data;
     atv_bloco -> hora = hora;
     atv_bloco -> prox = NULL;
     if (l == NULL){
     l = atv_bloco;
     }else{
     atv_bloco -> prox = l;
     l = atv_bloco;
     }
     return atv_bloco;
     }

void imprimir_atv(Atividade* l){
     Atividade* aux = l;
     while (aux -> prox != NULL){
     cout << "Atividade: " << aux -> atv << endl;
     cout << "Tipo " << aux -> tipo_atv << endl;
     cout << "Data: " << aux -> data << endl;
     cout << "Hora: " << aux -> hora << endl << endl;
     aux = aux -> prox;
     }
     cout << "Atividade: " << aux -> atv << endl;
     cout << "Tipo " << aux -> tipo_atv << endl;
     cout << "Data: " << aux -> data << endl;
     cout << "Hora: " << aux -> hora << endl << endl;
}

// Função da Matrix -----------------

bool** trabalho_matrix(int contador_A, int contador_C, Atividade* l, Descritor* lista_candidado){
     bool** Matrix_Atividades = new bool*[contador_A];
     for (int i = 0; i < contador_A; i++){
     Matrix_Atividades[i] = new bool[contador_C];
     }
     // Inicializando Matriz em FALSE
     for (int i = 0; i < contador_A; i++){
     for (int j = 0; j < contador_C; j++){
          Matrix_Atividades[i][j] = false;
     }
     }
     // Fazendo comparação
     Nolista* aux = lista_candidado -> ini;
     Atividade* aux2 = l;
     for (int i = 0; i < contador_A; i++){
     for (int j = 0; j < contador_C; j++){
          if (aux -> curso == l -> atv){
          Matrix_Atividades[i][j] = true;
          aux2 = aux2 -> prox;
          }else{
          Matrix_Atividades[i][j] = false;
          }
     }
     aux = aux -> prox;
     }
     return Matrix_Atividades;
}

// Função para trabalhar na frequencia, agindo direto no ponteiro l com uso de (&)
void inserir_freq(Descritor *&l, int contador_C){
     int freq = 0;
     Nolista* aux = l -> ini; // Iniciando ponteiro para escrever
     for (int i = 0; i < contador_C; i++){
     cout << "Por favor insira a frequencia de cada dandidato em ordem (entre 0 e 100): ";
     cin >> freq;
     if (freq < 0 || freq > 100){
          cout << endl << "DIGITO INVALIDO!" << endl;
          i -= 1;
     }else{
          aux -> freq = freq;
          aux = aux -> prox;
     }
     }
     aux = l -> ini; // Resetando ponteiro para leitura
     for (int j = 0; j < contador_C; j++){
          cout << endl << "Frequencias: " << aux -> freq << "%*" << endl;
          aux = aux -> prox;
     }
}

// Função para trabalhar e sortear
void trabalhar_sorteio(Sorteados *&l2, int contador_C, Nolista* juiz){
     if (juiz -> freq >= 75){
          Sorteados *nome_lista = new Sorteados;
          nome_lista -> nome = juiz -> nome;
          nome_lista -> prox = NULL;
     if (l2 == NULL){
          l2 = nome_lista;
     }else{
          nome_lista -> prox = l2;
          l2 = nome_lista;
     }
     }
}

void realizar_sorteio(Sorteados *l2, string sorteio1, string sorteio2, string sorteio3){
     // Inicializando seed do rand usando o relogio
     srand(time(0));
     // Configurando ponteiros e variaveis
     Sorteados* contador = l2;
     int tamanho = 0;
     int aleatorio = 0;
     // Contar quantos participantes
     while (contador -> prox != NULL){
          tamanho++;
          contador = contador -> prox; 
     }
     tamanho++;
     contador = contador -> prox;
     // Iniciar o sorteio
     contador = l2;
     aleatorio = rand() % tamanho + 1;
     for (int j = 1; j == aleatorio; j++){
          contador = contador -> prox;
     }
     cout << "Vencedor - " << sorteio1 << " - " << contador -> nome << "!!" << endl;
     contador = l2;
     aleatorio = rand() % tamanho + 1;
     for (int j = 1; j == aleatorio; j++){
          contador = contador -> prox;
     }
     cout << "Vencedor - " << sorteio2 << " - " << contador -> nome << "!!" << endl;
     contador = l2;
     aleatorio = rand() % tamanho + 1;
     for (int j = 1; j == aleatorio; j++){
          contador = contador -> prox;
     }
     cout << "Vencedor - " << sorteio3 << " - " << contador -> nome << "!!" << endl;
}

int main(){
     //Criando lista candidatos e ponteiro atividade
     Descritor *lista_candidado = criarlistaDupla(); // Descritor
     Atividade *l = criarlistaSimples(); // Ponteiro L simples
     Sorteados* l2 = NULL; // Ponteiro dos sorteados
     //Variáveis da lista de candidados, atividades e main
     string sorteio1 = "Fiat UNO 2006";
     string sorteio2 = "Caixa de BIS";
     string sorteio3 = "5 reais em barras de ouro que valem mais do que dinheiro";
     string nome, email, curso, atv, tipo_atv, data;
     int inscricao, hora, contador_C = 0, contador_A = 0;
     // INSERIR ATIVIDADES -----------//
     cout << "Digite o nome da atividade (Fim para sair): " << endl;
     cin >> atv;
     while (atv != "Fim"){
          cout << "Digite o tipo da atividade: " << endl;
          cin >> tipo_atv;
          cout << "Digite a data: " << endl;
          cin >> data;
          cout << "Digite a hora em formato 24h sem minutos: " << endl;
          cin >> hora;
          contador_A++;
          gerarlista_atv(l, atv, tipo_atv, hora, data);
          cout << "Digite o nome da atividade (Fim para sair): " << endl;
          cin >> atv;
     }
     //INSERIR CANDIDATO ---------- //
     cout<<"Digite o nome do candidato (Fim para sair): "<<endl;
     cin>>nome;
     while (nome != "Fim"){
          cout<<"Digite o email do usuario: "<<endl;
          cin>>email;
          cout<<"Digite o numero da inscrição: "<<endl;
          cin>>inscricao;
          imprimir_atv(l);
          cout<<"Digite a atividade desejada (Sem erros de escrita): "<<endl;
          cin >> curso;
          contador_C++;
          inserir_candidato(lista_candidado, nome, inscricao, email, curso);
          cout<<"Digite o nome do candidato (Fim para sair): "<<endl;
          cin>>nome;
     }
     imprimirCandidatos(lista_candidado);
     // CRIANDO MATRIX DE BOOL -----------//
     cout << endl << "Gerando Matrix..." << endl;
     trabalho_matrix(contador_A, contador_C, l, lista_candidado);
     // TRABALHANDO FREQUENCIA
     cout << endl << "Iniciando frequencia..." << endl; // Escrita trabalhada direto na função
     inserir_freq(lista_candidado, contador_C);
     cout << "Iniciando sorteio..." << endl; // Inicializando e inserindo nomes a uma lista de candidatos elegiveis
     Nolista* juiz = lista_candidado -> ini;
     for (int i = 0; i < contador_C; i++){
          trabalhar_sorteio(l2, contador_C, juiz);
          juiz = juiz -> prox;
     }
     realizar_sorteio(l2, sorteio1, sorteio2, sorteio3);
     cout << endl << "Fim!!!!!!" << endl;
}