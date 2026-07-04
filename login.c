#include "login.h"
#define LIMITE_TENTATIVA 5

void digitaString(int tamanho, char str[tamanho]) {
  mostrarAreaInput();
  fgets(str, tamanho, stdin);
  str[strcspn(str, "\n")] = '\0';
}

void login(){
	char usuario[NAME_SIZE];
	char senha[PASS_SIZE];
	int id;

	int tipo = 0;
	int flag = 0;
	printf("Digite o seu nome:");
	int valido = 0;
	while(!valido){
		digitaString(NAME_SIZE, usuario);

		id = buscarAdmin(usuario);
		if (id == 0) {
			id = buscarProfessor(usuario);
			if (id == 0) {
				id = buscarAluno(usuario);
				if (id != 0) {
					tipo = TIPO_ALUNO;
					valido = 1;
				}
			} else {
				tipo = TIPO_PROF;
				valido = 1;
			}
		} else {
			tipo = TIPO_ADMIN;
			valido = 1;
		}

		if (!valido) {
			printf("Nome de usuario (%s) invalido!\nTente novamente:", usuario);
		}
	}

	cabecalho();

	printf("Insira a senha de %s: ", usuario);

	flag = 0;
	for(int i = 0; i < LIMITE_TENTATIVA; i++){
		digitaString(PASS_SIZE, senha);
		if(validarSenha(id, tipo, senha)){
			flag = 1;
			break;
		}
		cabecalho();
		printf("Senha incorreta, tente novamente: ");
	}
	if(!flag){
		limpar();
		printf("Senha errada inserida %d vezes, encerrando o programa...", LIMITE_TENTATIVA);
		exit(0);
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