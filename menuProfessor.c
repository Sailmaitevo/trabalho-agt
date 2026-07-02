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

void professorListarNotas(int id, int ano, char turma){
	cabecalho();
	printf("Notas da turma %d%c:\n", ano, turma);
	for(int i = 0; i < MAXN; i++){
		if(ALUNOS[i].ano == ano && ALUNOS[i].turma == turma){
			printf("%d - %s - %.1f\n", i+1, ALUNOS[i].nome, alunoMedia(i+1, id));
		}
	}
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
	
	cabecalho();
	printf("Tabela de notas da turma %d%c:", ano, turma);
	
	Prova provas[MAXN] = {};
	int tamanhoP = professorPreencherProvas(id, ano, turma, provas);
	
	Aluno alunos[MAXN] = {};
	int tamanhoA = preencherTurma(ano, turma, alunos);
	
	char c[NAME_SIZE] = "Nome";
	padString(c, NAME_SIZE);
	printf("\n| %s |", c);
	
	for(int i = 0; i < tamanhoP; i++){
		char c[NAME_SIZE];
		strcpy(c, provas[i].nome);
		padString(c, NAME_SIZE);
		printf(" %s |", c);
	}
	for(int i = 0; i < tamanhoA; i++){
		char n[NAME_SIZE];
		strcpy(c, alunos[i].nome);
		padString(c, NAME_SIZE);
		printf("\n| %s |", c);
		
		char c[(NAME_SIZE+3)*tamanhoP];
		for(int j = 0; j < tamanhoP; j++){
			sprintf(c, " %.1f |", alunoNota(provas[j].id, alunos[i].id));
			padString(c, NAME_SIZE);
		}
		printf("%s", c);
	}
	
	char opcao;
	printf("\n\nDeseja salvar num arquivo? (s/n)");
	scanf("%c", opcao);
	if(opcao == 's'){
		char *nome;
		printf("Insira o nome do arquivo: ");
		scanf("%s", nome);
		FILE *arquivo = fopen(nome, "w+");
		
		char c[NAME_SIZE] = "Nome";
		padString(c, NAME_SIZE);
		fprintf(arquivo, "| %s |", c);
		
		for(int i = 0; i < tamanhoP; i++){
			char c[NAME_SIZE];
			strcpy(c, provas[i].nome);
			padString(c, NAME_SIZE);
			fprintf(arquivo, " %s |", c);
		}
		for(int i = 0; i < tamanhoA; i++){
			char n[NAME_SIZE];
			strcpy(c, alunos[i].nome);
			padString(c, NAME_SIZE);
			fprintf(arquivo, "\n| %s |", c);
			
			char c[(NAME_SIZE+3)*tamanhoP];
			for(int j = 0; j < tamanhoP; j++){
				sprintf(c, " %.1f |", alunoNota(provas[j].id, alunos[i].id));
			}
			fprintf(arquivo, "%s", c);
		}
	}
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

void mostrarMenuProfessor(){
	int opcao;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s, o que voce quer fazer hoje?\n", PROFESSORES[SESSION_ID - 1].nome);
		printf("0 - Sair\n");
		printf("1 - Ver turmas\n");
		printf("2 - Ver provas\n");
		printf("3 - Cadastrar prova\n");
		printf("4 - Editar notas\n");
		printf("5 - Gerar tabela de notas");
		
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
				if(scanf("%d%c", &ano, &turma) != 2) break;
				professorListarNotas(SESSION_ID, ano, turma);
				
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
			case 3:
				// professorCriarProva();
				break;
			case 4:
				// professorPreencherNotas();
				break;
			case 5:
				professorTabelaDeNotas(SESSION_ID);
				break;
		}
	} while(opcao);
}
