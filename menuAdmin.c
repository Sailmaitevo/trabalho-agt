#include "menuAdmin.h"

void admListarProfessores(){
	cabecalho();
	printf("ID - Nome - Materia");
	for(int i = 0; i < MAXN; i++){
		Professor professor = PROFESSORES[i-1];
		if(!professor.id) continue;
		
		printf("\n%d - %s - %s", professor.id, professor.nome, professor.materia);
	}
	esperar();
}
void admListarAlunos(){
	cabecalho();
	printf("ID - Nome - Turma");
	for(int i = 0; i < MAXN; i++){
		Aluno aluno = ALUNOS[i-1];
		if(!aluno.id) continue;
		
		printf("\n%d - %s - %d%c", aluno.id, aluno.nome, aluno.ano, aluno.turma);
	}
	esperar();
}
void admListarTurmas(){
	cabecalho();
	
	typedef struct {
		int ano; char turma;
	} Turma;
	Turma jaForam[MAXN] = {};
	int maiorIndex = -1;
	
	printf("Turma - Alunos");
	for(int i = 0; i < MAXN; i++){
		Turma turma = {ALUNOS[i].ano, ALUNOS[i].turma};
		if (turma.ano == 0) {
			break;
		}

		int flag = 0;
		for(int j = 0; j <= maiorIndex; j++){
			if(turma.ano == jaForam[j].ano && turma.turma == jaForam[j].turma){
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		
		maiorIndex++;
		jaForam[maiorIndex] = turma;
	}

	for(int i = 0; i <= maiorIndex; i++){
		int ano = jaForam[i].ano;
		char turma = jaForam[i].turma;
		
		float soma = 0;
		Aluno alunos[MAXN] = {};
		int tamanho = preencherTurma(ano, turma, alunos);
		
		printf("\n%d%c - %d", ano, turma, tamanho);
	}
	
	esperar();
}

void admCadastrar(){
	int permissao = admPedirNivelDePermissao(1);
	if(!permissao) return;
	
	char nome[NAME_SIZE];
	printf("Digite o nome (ate %d caracteres): ", NAME_SIZE - 1);
	digitaNomeValido(nome, 0);
	
	char senhaPadrao[PASS_SIZE] = "123456";
	switch(permissao){
		int ano, id;
		char turma, materia[MATERIA_SIZE];
		case 1:
			printf("Digite a turma de %s (Ano e letra, ex. 9A):", nome);
			digitaTurmaValida(&ano, &turma);
			
			id = cadastrarAluno(nome, senhaPadrao, ano, turma);
			printf("Alun@ %s criad@ com sucesso na turma %d%c com o id %d\nA senha padrao e 123456", nome, ano, turma, id);
			esperar();
			break;
		case 2:
			printf("Digite a materia d@ professor@ (3 caracteres):");
			digitaMateriaValida(materia);
			id = cadastrarProfessor(nome, senhaPadrao, materia);
			printf("Professor@ %s criado com sucesso para a materia %s com o id %d\nA senha padrao e 123456", nome, materia, id);
			esperar();
			break;
		case 3:
			id = cadastrarAdmin(nome, senhaPadrao);
			printf("Admin %s criado com sucesso com o id %d\nA senha padrao e 123456", nome, id);
			esperar();
			break;
	}
}
void admDeletar(){
	char nome[NAME_SIZE];
	
	cabecalho();

	int valido = 0;
	printf("Digite o nome para excluir (0 para voltar):");
	
	int tipo = 0;
	int id = 0;
	while(!valido) {
		digitaString(NAME_SIZE, nome);
		if(!strcmp(nome, "0")) return;
		if (acharIdTipo(&id, &tipo, nome)) {
			valido = 1;
		} else {
			printf("Nome invalido, tente de novo:");
		}
		
	}
	acharNome(id, tipo, nome);

	if (tipo == TIPO_ADMIN && (id == 1 || id == SESSION_ID)) {
		if (id == 1) {
			printf("Nao eh possivel deletar o admin inicial.");
		} else {
			printf("Voce nao pode se deletar.");
		} 
	} else {
		printf("Voce esta prestes a deletar %s, tem certeza?\nDigite S para confirmar: ", nome);
	
		if (inputSimNao()) {
			switch (tipo) {
				case TIPO_ALUNO:
					deletarAluno(id);
					printf("Aluno@ deletad@ com sucesso");
					break;
				case TIPO_ADMIN:
					deletarAdmin(id);
					printf("Admin deletado com sucesso");
					break;
				case TIPO_PROF:
					deletarProfessor(id);
					printf("Professor deletado com sucesso");
					break;
			}
		} else {
			printf("Delecao cancelada");	
		}
	}
	esperar();
}
void admEditar(){
	cabecalho();
	printf("Digite o nome do usuario (0 para voltar):");
	int valido = 0;
	char nome[NAME_SIZE];
	int id;
	int tipo;

	while (!valido) {
		digitaString(NAME_SIZE, nome);
		if(!strcmp(nome, "0")) return;
		if (acharIdTipo(&id, &tipo, nome)) {
			valido = 1;
		} else {
			printf("Tente de novo:");
		}
	}

	int volta;
	
	do {
		volta = 0;
		switch (tipo) {
			Aluno aluno;
			Professor professor;
			Admin admin;
			int opcao;
			case TIPO_ALUNO:
				aluno = ALUNOS[id - 1];
				cabecalho();
				printf("Qual deseja alterar? ");
				printf("\n1 - Nome: %s", aluno.nome);
				printf("\n2 - Turma: %d%c", aluno.ano, aluno.turma);
				opcao = digitaOpcao(1, 2);
				if(opcao == 1){
					char nomeNovo[NAME_SIZE];
					int nomeValido = 0;
					printf("Digite 0 para voltar\n");
					printf("Nome atual: %s\n", aluno.nome);
					printf("Nome novo: ");
					digitaNomeValido(nomeNovo, 1);
					if(!strcmp(nomeNovo, "0")){
						volta = 1;
						continue;
					}
					strcpy(aluno.nome, nomeNovo);
				} else if(opcao == 2){
					int ano; char turma;
					printf("Turma atual: %d%c\n", aluno.ano, aluno.turma);
					printf("Turma nova: ");
					digitaTurmaValida(&ano, &turma);
					aluno.ano = ano;
					aluno.turma = turma;
				}
				
				ALUNOS[id-1] = aluno;
				printf("Aluno alterado com sucesso");
				break;
			case TIPO_PROF:
				cabecalho();
				professor = PROFESSORES[id - 1];
				printf("Qual deseja alterar? ");
				printf("\n1 - Nome: %s", professor.nome);
				printf("\n2 - Materia: %s", professor.materia);
				opcao = digitaOpcao(1, 2);
				if(opcao == 1){
					char nomeNovo[NAME_SIZE];
					printf("Digite 0 para voltar\n");
					printf("Nome atual: %s\n", professor.nome);
					printf("Nome novo: ");
					digitaNomeValido(nomeNovo, 1);
					if(!strcmp(nomeNovo, "0")){
						volta = 1;
						continue;
					}
					strcpy(professor.nome, nomeNovo);
				} else if(opcao == 2){
					char materiaNova[MATERIA_SIZE];
					printf("Materia atual: %s\n", professor.materia);
					printf("Materia nova: ");
					digitaMateriaValida(materiaNova);
					strcpy(professor.materia, materiaNova);
				}
				
				PROFESSORES[id-1] = professor;
				printf("Professor alterado com sucesso");
				break;
			case TIPO_ADMIN:
				if (SESSION_ID == id) {
					cabecalho();
					char nomeNovo[NAME_SIZE];
					printf("Nome atual: %s\n", ADMINS[id - 1].nome);
					printf("Nome novo: ");
					digitaNomeValido(nomeNovo, 1);

					strcpy(ADMINS[id - 1].nome, nomeNovo);
					printf("Admin alterado com sucesso");
				} else {
					printf("Voce nao pode modificar outros admins");
				}
		}
	} while (volta);

	esperar();
}

int admPedirNivelDePermissao(int admin){
	cabecalho();
	printf("Qual o nivel de permissao do usuario?\n");
	printf("0 - Voltar\n");
	printf("1 - Aluno\n");
	printf("2 - Professor\n");
	if(admin) printf("3 - Admin");

	mostrarAreaInput();
	
	int opcao;

	if(!scanf("%d", &opcao) || !(opcao >= 1 && opcao <= admin ? 3 : 2)) {
		opcao = 0;
	}
	consumirInput();
	return opcao;
}

void mostrarMenuAdmin(){
	Admin usuario = ADMINS[SESSION_ID - 1];
	
	int opcao = 1;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s. O que voce quer fazer hoje?\n", usuario.nome);
		printf("0 - Sair\n");
		printf("1 - Ver professores\n");
		printf("2 - Ver alunos\n");
		printf("3 - Ver turmas\n");
		printf("4 - Cadastrar usuario\n");
		printf("5 - Deletar usuario\n");
		printf("6 - Editar dados de um usuario\n");
		printf("7 - Alterar senha");
		
		opcao = digitaOpcao(0, 7);
		
		switch(opcao){
			char senha[PASS_SIZE], senhaNova[PASS_SIZE], senhaNovaConfirmar[PASS_SIZE];
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
				break;
			case 1:
				admListarProfessores();
				break;
			case 2:
				admListarAlunos();
				break;
			case 3:
				admListarTurmas();
				break;
			case 4:
				admCadastrar();
				break;
			case 5:
				admDeletar();
				break;
			case 6:
				admEditar();
				break;
			case 7:
				mudarSenha(TIPO_ADMIN);
				break;
		}
	} while(opcao);
	
	return;
}