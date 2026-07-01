#include "login.h"

void login(int (*buscar)(char*), int (*validar)(int, char[PASS_SIZE]), void (*mostrarMenu)()){
	char usuario[NAME_SIZE];
	char senha[PASS_SIZE];
	int id;

	int flag = 0;
	printf("Insira seu nome de usuario (0 para voltar): ");
	while(1){
		scanf("%s", usuario);

		if(!strcmp(usuario, "0")){
			menuLogin();
			return;
		}

		id = buscar(usuario);
		if(id) break;

		printf("Nome de usuario (%s) invalido!\nTente novamente (0 para voltar):", usuario);
	}

	cabecalho();

	printf("Ola, %s!\nInsira sua senha: ", usuario);

	flag = 0;
	for(int i = 0; i < 5; i++){
		scanf("%s", senha);
		if(validar(id, senha)){
			flag = 1;
			break;
		}
		cabecalho();
		printf("Senha incorreta, tente novamente: ");
	}
	if(!flag){
		printf("Senha errada inserida mais de 5 vezes, encerrando o programa");
		exit(EXIT_FAILURE);
	}

	SESSION_ID = id;
	mostrarMenu();
}

void loginAluno(){
	login(&buscarAluno, &validarAluno, &mostrarMenuAluno);
}
void loginProfessor(){
	login(&buscarProfessor, &validarProfessor, &mostrarMenuProfessor);
}
void loginAdmin(){
	login(&buscarAdmin, &validarAdmin, &mostrarMenuAdmin);
}