#include "login.h"

void login(){
	char usuario[NAME_SIZE];
	char senha[PASS_SIZE];
	int id;

	int tipo = 0;
	int flag = 0;
	printf("Insira seu nome de usuario (0 para voltar): ");
	while(1){
		scanf("%s", usuario);

		if(!strcmp(usuario, "0")){
			menuLogin();
			return;
		}

		id = buscarAdmin(usuario);
		if (id == 0) {
			id = buscarProfessor(usuario);
			if (id == 0) {
				id = buscarAluno(usuario);
				if (id != 0) {
					tipo = TIPO_ALUNO;
					break;
				}
			} else {
				tipo = TIPO_PROF;
				break;
			}
		} else {
			tipo = TIPO_ADMIN;
			break;
		}

		printf("Nome de usuario (%s) invalido!\nTente novamente (0 para voltar):", usuario);
	}

	cabecalho();

	printf("Ola, %s!\nInsira sua senha: ", usuario);

	flag = 0;
	for(int i = 0; i < 5; i++){
		scanf("%s", senha);
		if(validarSenha(id, tipo, senha)){
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
	switch (tipo) {
		case TIPO_ADMIN:
			mostrarMenuAdmin();
			break;
		case TIPO_PROF:
			mostrarMenuProfessor();
			break;
		case TIPO_ALUNO:
			mostrarMenuAluno();
			break;
	}
}