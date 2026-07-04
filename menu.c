#include "menu.h"

int SESSION_ID;

void limpar() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void cabecalho(){
  limpar();
  printf("==== SIGA (Sistema Integrado de Gestao Algoritmica) ====\n");
}

void menuLogin(){
  cabecalho();
  login();
}

void padString(char *string, int size){
	for(int i = strlen(string); i < size - 1; i++){
		string[i] = ' ';
	}
	string[size - 1] = 0;
}

void esperar(){
	printf("\n\nPressione ENTER para continuar");
	consumirInput();
}

void mostrarAreaInput() {
  printf("\n>");
}

void consumirInput() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int inputSimNao() {
	char resposta[2];
	digitaString(2, resposta);
	return fazerMinusculo(resposta[0]) == 's';
}