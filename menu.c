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

void digitaNomeValido(char nome[NAME_SIZE], int capitalizacaoImporta) {
	int valido = 0;
	while(!valido){
		digitaString(NAME_SIZE, nome);
		
		if(strlen(nome) > 0) {
			if(
				buscarAluno(nome, capitalizacaoImporta) ||
				buscarProfessor(nome, capitalizacaoImporta) ||
				buscarAdmin(nome, capitalizacaoImporta)
			){
				printf("Esse nome ja foi cadastrado, tente novamente: ");
				continue;
			} else {
				valido = 1;
			}
		} else {
			printf("Digite um nome: ");
		}
	}
}

int inputTurma(int *ano, char *turma) {
	int resultado = scanf("%d%c", ano, turma);
	// \n foi dado como o %c nesse caso
	if (resultado && *turma != '\n') {
		consumirInput();
	}
	return resultado;
}

void digitaTurmaValida(int *anoPointer, char *turmaPointer) {
mostrarAreaInput();
	int ano;
	char turma;
	int valido = 0;
	while(!valido){
		int resultado = inputTurma(&ano, &turma);

		if (resultado && ehLetra(turma)) {
			if (ano < 1 || ano > 12) {
				printf("Ano invalido. O ano deve ser de 1-9 para o ensino fundamental e 10-12 para o ensino medio.\nDigite novamente:");
				mostrarAreaInput();
			} else {
				valido = 1;
				turma = fazerMaiusculo(turma);
			}
		} else {
			printf("Formato invalido, voce deve digitar no formato ano e letra, ex. 9A.\nTente novamente:");
			if (!resultado) {
				consumirInput();
			}
			mostrarAreaInput();
		}

		if (valido) {
			Aluno alunos[TURMA_SIZE];
			int tamanho = preencherTurma(ano, turma, alunos);
			if(tamanho >= TURMA_SIZE) printf("Turma %d%c cheia, escolha outra: ", ano, turma);
			if(!tamanho){
				printf("Turma %d%c inexistente, digite S para cria-la: ", ano, turma);
				if (!inputSimNao()) {
					valido = 0;
					printf("Digite outra turma:");
					mostrarAreaInput();
				}
			}
		}
	}

	*anoPointer = ano;
	*turmaPointer = turma;
}

int digitaOpcao(int min, int max) {
	int valido = 0;
	int opcao;
	while (!valido) {
		mostrarAreaInput();
		int resultado = scanf("%d", &opcao);
		consumirInput();
		if (!resultado || !(opcao >= min && opcao <= max)) {
			printf("Tente novamente:");
		} else {
			valido = 1;
		}
	}

	return opcao;
}

void digitaMateriaValida(char materia[MATERIA_SIZE]) {
	int valido = 0;
	while(!valido){
		digitaString(MATERIA_SIZE, materia);
		int tudoLetra = 1;
		for (int i = 0; i < MATERIA_SIZE - 1; i++) {
			if (!ehLetra(materia[i])) {
				tudoLetra = 0;
				break;
			} else {
				materia[i] = fazerMaiusculo(materia[i]);
			}
		}
		if(strlen(materia) == MATERIA_SIZE - 1 && tudoLetra) {
			valido = 1;
		} else {
			printf("Tente novamente:");
		}
	}
}

void mudarSenha(int tipo) {
	cabecalho();
	char senha[PASS_SIZE];
	char senhaNova[PASS_SIZE];
	char senhaNovaConfirmar[PASS_SIZE];
	printf("Digite sua senha atual: ");
	digitaString(PASS_SIZE, senha);
	
	if(validarSenha(SESSION_ID, tipo, senha)){
		cabecalho();
		printf("Digite sua nova senha (3 a %d caracteres): ", PASS_SIZE - 1);
		int valido = 0;
		while(!valido){
			digitaString(PASS_SIZE, senhaNova);
			if(strlen(senhaNova) > 2) {
				valido = 1;
			} else {
				printf("Input invalido, tente de novo: ");
			}
		}
		printf("Digite a nova senha novamente: ");
		digitaString(PASS_SIZE, senhaNovaConfirmar);
		if(!strcmp(senhaNova, senhaNovaConfirmar)){
			unsigned hash = criptografar(senhaNova);
			switch (tipo) {
				case TIPO_ADMIN:
					ADMINS[SESSION_ID-1].senha = hash;
					break;
				case TIPO_ALUNO:
					ALUNOS[SESSION_ID-1].senha = hash;
					break;
				case TIPO_PROF:
					PROFESSORES[SESSION_ID-1].senha = hash;
					break;
			}
			printf("Senha alterada com sucesso");
		} else {
			printf("ERRO: As duas senhas nao batem");
		}
		esperar();
	} else {
		printf("Senha incorreta.");
		esperar();
	}
}