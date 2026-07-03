#include "menuProfessor.h"

void professorListarTurmas(int id){
	typedef struct {
		int ano;
		char turma;
        float soma;
        int contador;
    } Turma;
	
    Turma turmas[MAXN] = {};
    int maxIndex = 0;
	
	
    for(int i = 0; i < MAXN; i++){
		int flag = 1;
		Aluno aluno = ALUNOS[i];
        for(int j = 0; j <= maxIndex; j++){ // percorre o array de turmas vendo se ja existe a struct da turma do aluno
            if(aluno.ano == turmas[j].ano && aluno.turma == turmas[j].turma){
				turmas[j].soma += alunoMedia(aluno.id, id);
				turmas[j].contador++;
				flag = 0;
            }
        }
        if(!flag) continue;
        
		Turma aux = {aluno.ano, aluno.turma, 0, 0};
        turmas[maxIndex] = aux;
		maxIndex++;
    }
	
	cabecalho();
    float soma = 0;
    int contador = 0;
    for(int i = 0; i < maxIndex; i++){
		float media = turmas[i].soma/turmas[i].contador;
		printf("%d%c - %.1f\n", turmas[i].ano, turmas[i].turma, media);
        soma += media;
        contador++;
    }
	
    printf("Media geral: %.1f", soma/contador);
}

int professorListarNotas(int id, int ano, char turma){
	Aluno alunos[MAXN] = {};
	int tamanho = preencherTurma(ano, turma, alunos);
	if(!tamanho) return 0;
	
	cabecalho();
	int flag = 0;
	printf("Notas da turma %d%c:\n", ano, turma);
	
	for(int i = 0; i < tamanho; i++){
		printf("%d - %s - %.1f\n", alunos[i].id, alunos[i].nome, alunoMedia(alunos[i].id, id));
		flag = 1;
	}
	
	return 1;
}

void professorConsultarNotas(int id, int idAluno){
	cabecalho();
	Prova provas[MAXN] = {};
	int tamanho = professorPreencherProvas(id, ALUNOS[idAluno-1].ano, ALUNOS[idAluno-1].turma, provas);
	
	printf("Notas d@ alun@ %d - %s\n", idAluno, ALUNOS[idAluno-1].nome);
	for(int i = 0; i < tamanho; i++){
		printf("%s - %.1f\n", provas[i].nome, alunoNota(provas[i].id, idAluno));
	}
}

int professorPreencherProvas(int id, int ano, char turma, Prova *provas){
	int index = 0;
	
	for(int i = 0; i < MAXN; i++){
		Prova prova = PROVAS[i];
		if((prova.ano == ano || ano == 0)
		&& (prova.turma == turma || turma == 0)
		&& (prova.idProfessor == id || id == 0)){
			provas[index] = prova;
			index++;
		};
	}
	
	return index;
}

void professorTabelaDeNotas(int id){
	int ano; char turma;
	
	printf("\nEscolha uma turma para fazer a tabela: ");
	scanf("%d%c", &ano, &turma);
	getchar();
	
	cabecalho();
	printf("Tabela de notas da turma %d%c:", ano, turma);
	
	Prova provas[MAXN] = {};
	int tamanhoP = professorPreencherProvas(id, ano, turma, provas);
	
	Aluno alunos[MAXN] = {};
	int tamanhoA = preencherTurma(ano, turma, alunos);
	
	char s[NAME_SIZE] = "Nome";
	padString(s, NAME_SIZE);
	printf("\n| %s |", s);
	
	for(int i = 0; i < tamanhoP; i++){
		char c[NAME_SIZE];
		strcpy(c, provas[i].nome);
		padString(c, NAME_SIZE);
		printf(" %s |", c);
	}
	for(int i = 0; i < tamanhoA; i++){
		char n[NAME_SIZE];
		strcpy(n, alunos[i].nome);
		padString(n, NAME_SIZE);
		printf("\n| %s |", n);
		
		char c[(NAME_SIZE+3)*tamanhoP];
		strcpy(c, "");
		
		for(int j = 0; j < tamanhoP; j++){
			char aux[NAME_SIZE];
			sprintf(aux, "%.1f", alunoNota(provas[j].id, alunos[i].id));
			padString(aux, NAME_SIZE);
			
			sprintf(c+strlen(c), " %s |", aux);
		}
		printf("%s", c);
	}
	
	esperar("\n\nPressione ENTER para sair");
}

int preencherTurma(int ano, char turma, Aluno *alunos){
	int index = 0;
	
	for(int i = 0; i < MAXN; i++){
		Aluno aluno = ALUNOS[i];
		if(ano == aluno.ano && aluno.turma == turma){
			alunos[index] = aluno;
			index++;
		}
	}
	
	return index;
}

void professorListarProvas(int id){
	cabecalho();
	Prova provas[MAXN];
	int tamanho = professorPreencherProvas(id, 0, 0, provas);
	
	printf("id - nome - turma");
	for(int i = 0; i < tamanho; i++){
		printf("\n%d - %s - %d%c", provas[i].id, provas[i].nome, provas[i].ano, provas[i].turma);
	}
	
	esperar("\n\nPressione ENTER para voltar");
}

void professorCriarProva(int id){
	char nome[NAME_SIZE];
	int ano;
	char turma;
	int tamanho;
	
	cabecalho();
	printf("Cadastrando prova nova\n");
	do {
		printf("Insira a turma: ");
		scanf("%d%c", &ano, &turma);
		getchar();
		
		Aluno alunos[MAXN];
		tamanho = preencherTurma(ano, turma, alunos);
		if(!tamanho) printf("Turma invalida, tente de novo\n");
	} while(!tamanho);
	
	int confirma;
	do {
		printf("Insira o nome para a prova (ate 20 caracteres sem espaco)");
		scanf("%s", &nome);
		
		if(buscarProva(nome, ano, turma)) continue;
		
		getchar();
		printf("O nome e %s, confirma? (s/n)");
		confirma = getchar();
	} while (confirma != 's');
	
	cabecalho();
	printf("Cadastrando %s\n para %d%c", nome);
	

	cadastrarProva(nome, id, ano, turma);
}

void professorEditarNotas(int id, int unico){
	// Seleciona uma turma
	// Mostra as provas
	// Seleciona uma prova
	// Pra cada aluno, mostra a nota atual e pede a nova
	// Continua pedindo ate a nota estar entre 0 e 10
	// Quando finalizado, lista as notas
	
	printf("Selecione uma turma: ");
	int tamanhoA, ano;
	char turma;
	Aluno alunos[MAXN];
	
	do{
		scanf("%d%c", &ano, &turma);
		getchar();
		tamanhoA = preencherTurma(ano, turma, alunos);
		
		if(!tamanhoA) printf("Turma invalida, tente novamente: ");
	} while(!tamanhoA);
	
	cabecalho();
	printf("Provas da turma %d%c", ano, turma);
	
	printf("Provas da turma %d%c", ano, turma);
	for(int i = 0; i < MAXN; i++){
		if(PROVAS[i].idProfessor == id) printf("\n%s", PROVAS[i].nome);
	}
	printf("\n\nEscolha uma das provas acima: ");
	
	char nomeProva[NAME_SIZE];
	int idProva;
	do {
		scanf("%s", nomeProva);
		idProva = buscarProva(nomeProva, ano, turma);
		if(!idProva) printf("Insira uma prova existente");
	} while(!idProva);
	
	if(unico){
		int idAluno;
		
		cabecalho();
		printf("Notas dos alunos da turma %d%c em %s", ano, turma, nomeProva);
		printf("Alun@ - Nota:");
		
		for(int i = 0; i < tamanhoA; i++){
			printf("\n%d - %s - %.1f", alunos[i].id, alunos[i].nome, alunoNota(idProva, alunos[i].id));
		}
		
		printf("\n\nEscolha um por id: ");
		while(1){
			scanf("%d", &idAluno);
			for(int i = 0; i < tamanhoA; i++){
				if(alunos[i].id == idAluno) break;
			}
			printf("Id de aluno invalido, tente novamente: ");
		}
		
		float nota;
		printf("Insira a nota de %s em %s: ", ALUNOS[idAluno-1].nome, nomeProva);
		while(1){
			scanf("%f", &nota);
			if(nota <= 10 && nota >= 0) break;
			printf("A nota deve estar entre 0 e 10, tente novamente: ");
		}
		
		editarNota(idProva, idAluno, nota);
	} else {
		for(int i = 0; i < tamanhoA; i++){
			cabecalho();
			printf("%s\n%s\nNota atual: %.1f\nNova nota: ", nomeProva, alunos[i].nome, alunoNota(idProva, alunos[i].id));
			
			float nota;
			while(1){
				scanf("%f", &nota);
				if(nota <= 10 && nota >= 0) break;
				printf("A nota deve estar entre 0 e 10, tente novamente: ");
			}
			
			editarNota(idProva, alunos[i].id, nota);
		}
	}
}

void professorEditarNotaUnica(int id){
	
}

void mostrarMenuProfessor(){
	int opcao;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s, o que voce quer fazer hoje?\n", PROFESSORES[SESSION_ID - 1].nome);
		printf("0 - Sair\n");
		printf("1 - Ver turmas\n");
		printf("2 - Ver provas\n");
		printf("3 - Cadastrar prova\n");
		printf("4 - Editar notas em massa\n");
		printf("5 - Editar notas de um unico aluno\n");
		printf("6 - Excluir prova\n");
		printf("7 - Gerar tabela de notas\n");
		
		scanf("%d", &opcao);
		
		switch(opcao){
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
				break;
			case 1:
				professorListarTurmas(SESSION_ID);
				
				int ano; char turma;
				printf("Escolha uma turma: ");
				if(scanf("%d%c", &ano, &turma) != 2 || ano == 0 || turma == '\n') break;
				if(!professorListarNotas(SESSION_ID, ano, turma)) break;
				
				int aluno;
				printf("\n\nEscolha um id de aluno (0 para voltar): ");
				if(!scanf("%d", &aluno) ||
					aluno <= 0 ||
					aluno >= MAXN ||
					ALUNOS[aluno-1].ano != ano ||
					ALUNOS[aluno-1].turma != turma
				) break;
				professorConsultarNotas(SESSION_ID, aluno);
				esperar("\n\nAperte ENTER para continuar ");
				
				break;
			case 2:
				professorListarProvas(SESSION_ID);
				break;
			case 3:
				professorCriarProva(SESSION_ID);
				break;
			case 4:
				professorEditarNotas(SESSION_ID, 0);
				break;
			case 5:
				professorEditarNotas(SESSION_ID, 1);
				break;
			case 6:
				// professorDeletarProva();
				break;
			case 7:
				professorTabelaDeNotas(SESSION_ID);
				break;
		}
	} while(opcao);
}