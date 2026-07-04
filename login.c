#include "login.h"
#define LIMITE_TENTATIVA 5

void digitaString(int tamanho, char str[tamanho]) {
  mostrarAreaInput();
  fgets(str, tamanho, stdin);

	// ver se o newline foi lido ou nao
	if (strchr(str, '\n') != NULL) {
		str[strcspn(str, "\n")] = '\0';
	} else {
		consumirInput();
	}

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
		if (acharIdTipo(&id, &tipo, usuario)) {
			valido = 1;
		} else {
			printf("Nome de usuario (%s) invalido!\nTente novamente:", usuario);
		}
	}

	acharNome(id, tipo, usuario);
	cabecalho();

	printf("Digite a senha de %s: ", usuario);

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
		cabecalho();
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