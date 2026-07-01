#include "menuAdmin.h"

void mostrarMenuAdmin(){
	Admin usuario = ADMINS[SESSION_ID - 1];
	
	int opcao = 1;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s, o que você quer fazer hoje?\n", usuario.nome);
		printf("0 - sair\n");
		printf("1 - ver alunos\n");
		printf("2 - ver professores\n");
		printf("3 - ver turmas\n");
		printf("4 - cadastrar usuario\n");
		printf("5 - deletar usuario\n");
		printf("6 - editar dados\n");
		
		scanf("%d", &opcao);
		
		printf("Opcao: %d", opcao);
	} while(opcao);
	
	return;
}