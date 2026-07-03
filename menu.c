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
  printf("==== SIGA (Sistema Integrado de Gestão Algoritmica) ====\n");
}

void menuLogin(){
  cabecalho();
  int opcao;
  printf("Bem-vindo, escolha uma forma de login:\n1- Aluno\n2- Professor\n3- Administrador\n");
  scanf("%d", &opcao);
  switch(opcao){
    case 1:
      loginAluno();
      return;
    case 2:
      loginProfessor();
      return;
    case 3:
      loginAdmin();
      return;
    default:
      menuLogin();
      return;
  }
}

void padString(char *string, int size){
	for(int i = strlen(string); i < size - 1; i++){
		string[i] = ' ';
	}
	string[size - 1] = 0;
}

void esperar(){
	printf("\n\nPressione ENTER para continuar");
	
	int c;
	while((c = getchar()) != '\n');
	fflush(stdout);
	while((c = getchar()) != '\n');
}