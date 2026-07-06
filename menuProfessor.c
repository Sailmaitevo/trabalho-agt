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
					int mediaAluno = alunoMedia(aluno.id, id);
					if (mediaAluno != -1) {
						turmas[j].soma += 
						turmas[j].contador++;
					}
					flag = 0;
				}
			}
			if(!flag) continue;
        
		Turma aux = {aluno.ano, aluno.turma, 0, 0};
        turmas[maxIndex] = aux;
		maxIndex++;
    }
	
	cabecalho();
	int turmasComNota = 0;
	for(int i = 0; i < maxIndex; i++){
		if (turmas[i].contador) {
			if (turmasComNota == 0) {
				printf("Turma - Media\n");
			}
			turmasComNota++;
			printf("%d%c - %1.f\n", turmas[i].ano, turmas[i].turma, turmas[i].soma/turmas[i].contador);
		}
	}

	if (turmasComNota == 0) {
		printf("Nenhuma turma com nota ainda...\n");
	}
	esperar();
}
int professorListarNotas(int id, int ano, char turma){
	Aluno alunos[TURMA_SIZE] = {};
	int tamanho = preencherTurma(ano, turma, alunos);
	if(!tamanho) return 0;
	
	cabecalho();
	int flag = 0;
	printf("Notas da turma %d%c:\n", ano, turma);
	
	printf("id - nome - media - faltas");
	for(int i = 0; i < tamanho; i++){
		printf("%d - %s - %.1f - %d\n", alunos[i].id, alunos[i].nome, alunoMedia(alunos[i].id, id), alunoFaltas(id, alunos[i].id));
		flag = 1;
	}
	
	return 1;
}
void professorConsultarNotas(int id, int idAluno){
	cabecalho();
	Prova provas[MAXN] = {};
	int tamanho = preencherProvas(id, ALUNOS[idAluno-1].ano, ALUNOS[idAluno-1].turma, provas);
	if(!tamanho){
		printf("Nao foram encontradas provas para %s", ALUNOS[idAluno-1].nome);
		esperar();
		return;
	}
	
	printf("Notas d@ alun@ %d - %s\n", idAluno, ALUNOS[idAluno-1].nome);
	for(int i = 0; i < tamanho; i++){
		printf("%s - %.1f\n", provas[i].nome, alunoNota(provas[i].id, idAluno));
	}
	printf("Faltas: %d", alunoFaltas(id, idAluno));
	esperar();
}

void professorTabelaDeNotas(int id, int final){
	int ano; char turma;
	
	int tamanhoA;
	Aluno alunos[MAXN] = {};
	
	printf("\nEscolha uma turma para fazer a tabela: ");
	while(1){
		inputTurma(&ano, &turma);

		tamanhoA = preencherTurma(ano, turma, alunos);
		
		if(tamanhoA) break;
		printf("Turma invalida! Tente novamente: ");
	}
	
	FILE *arquivo = NULL;
	printf("Deseja salvar num arquivo de texto? (s/n)");
	int salvar = inputSimNao();
	if(salvar){
		char caminho[NAME_SIZE+4];
		int flag = 0;
		printf("Digite o nome do arquivo (ate %d caracteres sem extensao, 0 para cancelar)", NAME_SIZE-1);
		while(1){
			mostrarAreaInput();
			scanf("%s", caminho);
			getchar();
			if(!strcmp(caminho, "0")){
				salvar = 0;
				break;
			}
			if(!strlen(caminho)) continue;
			
			sprintf(caminho+strlen(caminho), ".txt");
			arquivo = fopen(caminho, "r");
			if(arquivo != NULL){
				printf("Arquivo ja existe, tente novamente");
				fclose(arquivo);
				continue;
			}
			break;
		}
		arquivo = fopen(caminho, "w");
	}
	
	cabecalho();
	char tempo[80];
	pegarTempo(tempo, sizeof(tempo));
	printf("Tabela de notas da turma %d%c\nDocumento gerado em %s", ano, turma, tempo);
	if(salvar) fprintf(arquivo, "Tabela de notas da turma %d%c\nDocumento gerado em %s", ano, turma, tempo);
	
	Prova provas[MAXN] = {};
	int tamanhoP = preencherProvas(id, ano, turma, provas);
	if(!tamanhoP){
		printf("\nNao foram encontradas provas para essa turma");
		if(salvar) fprintf(arquivo, "\nNao foram encontradas provas para essa turma");
		esperar();
		return;
	}
	
	char s[NAME_SIZE] = "Nome";
	padString(s, NAME_SIZE);
	printf("\n| %s |", s);
	if(salvar) fprintf(arquivo, "\n| %s |", s);
	
	if (final){
		strcpy(s, "Media");
		padString(s, NAME_SIZE);
		printf(" %s |", s);
		if(salvar) fprintf(arquivo, " %s |", s);
	} else {
		for(int i = 0; i < tamanhoP; i++){
			char c[NAME_SIZE];
			strcpy(c, provas[i].nome);
			padString(c, NAME_SIZE);
			printf(" %s |", c);
			if(salvar) fprintf(arquivo, " %s |", c);
		}
	}

	strcpy(s, "Faltas");
	padString(s, NAME_SIZE);
	printf(" %s |", s);
	if(salvar) fprintf(arquivo, " %s |", s);

	if (final) {
		strcpy(s, "Resultado");
		padString(s, NAME_SIZE);
		printf(" %s |", s);
		if(salvar) fprintf(arquivo, " %s |", s);
	
		strcpy(s, "Nota Exame");
		padString(s, NAME_SIZE);
		printf(" %s |", s);
		if(salvar) fprintf(arquivo, " %s |", s);
	}
	
	for(int i = 0; i < tamanhoA; i++){
		char n[NAME_SIZE];
		float media = 0;

		strcpy(n, alunos[i].nome);
		padString(n, NAME_SIZE);
		printf("\n| %s |", n);
		if(salvar) fprintf(arquivo, "\n| %s |", n);
		
		char c[(NAME_SIZE+3)*tamanhoP];
		strcpy(c, "");
		
		for(int j = 0; j < tamanhoP; j++){
			char aux[NAME_SIZE];
			float notaProva = alunoNota(provas[j].id, alunos[i].id);
			media += notaProva;

			if (!final) {
				sprintf(aux, "%.1f", notaProva);
				padString(aux, NAME_SIZE);
				
				sprintf(c+strlen(c), " %s |", aux);
			}
		}
		printf("%s", c);
		if(salvar) fprintf(arquivo, "%s", c);

		media /= tamanhoP;
		
		if (final) {
			strcpy(n, "");
			sprintf(n, "%.1f", media);
			padString(n, NAME_SIZE);
			printf(" %s |", n);
			if(salvar) fprintf(arquivo, " %s |", n);
		}

		int faltas = alunoFaltas(id, alunos[i].id);

		strcpy(n, "");
		sprintf(n, "%d", faltas);
		padString(n, NAME_SIZE);
		printf(" %s |", n);
		if(salvar) fprintf(arquivo, " %s |", n);

		if (final) {
			int exame = 0;
			strcpy(n, "");
			if (faltas > AULAS_NUM / 4) {
				sprintf(n, "REPROVAD@ POR FALTA");
			} else if (calcularMediaExame(media) > 10) {
				sprintf(n, "REPROVAD@");
			} else if (media < MEDIA_MIN) {
				exame = 1;
				sprintf(n, "EM EXAME");
			} else {
				sprintf(n, "APROVAD@");
			}
			padString(n, NAME_SIZE);
			printf(" %s |", n);
			if(salvar) fprintf(arquivo, " %s |", n);
	
			strcpy(n, "");
			if (exame) {
				sprintf(n, "%.1f", calcularMediaExame(media));
			} else {
				sprintf(n, " - ");
			}
			
			padString(n, NAME_SIZE);
			printf(" %s |", n);
			if(salvar) fprintf(arquivo, " %s |", n);
		}
	}
	
	if(salvar) fclose(arquivo);
	
	esperar();
}
void professorListarProvas(int id){
	cabecalho();
	Prova provas[MAXN];
	int tamanho = preencherProvas(id, 0, 0, provas);
	if(!tamanho){
		printf("Nao ha nenhuma prova registrada");
		esperar();
		return;
	}
	
	printf("id - nome - turma");
	for(int i = 0; i < tamanho; i++){
		printf("\n%d - %s - %d%c", provas[i].id, provas[i].nome, provas[i].ano, provas[i].turma);
	}
	
	esperar();
}

void professorCriarProva(int id){
	char nome[NAME_SIZE];
	int ano;
	char turma;
	int tamanho;
	
	cabecalho();
	printf("Cadastrando prova nova\n");
	printf("Insira a turma: ");
	int resultado = scanf("%d%c", &ano, &turma);
	if (!resultado || turma != '\n') {
		consumirInput();
	}
	
	Aluno alunos[MAXN];
	tamanho = preencherTurma(ano, turma, alunos);
	if(!tamanho) {
		printf("Turma invalida.\n");
		esperar();
		return;
	}
	
	int confirma = 0;
	do {
		printf("Insira o nome para a prova (ate %d caracteres): ", NAME_SIZE - 1);
		digitaString(NAME_SIZE, nome);
		
		if(buscarProva(nome, ano, turma, id)){
			printf("Prova ja existe, tente novamente.\n");
			continue;
		}
		
		printf("O nome e %s, confirma? (s para confirmar)", nome);
		confirma = inputSimNao();
	} while (!confirma);
	
	cabecalho();
	printf("Cadastrando %s\n para %d%c", nome, ano, turma);
	

	cadastrarProva(nome, id, ano, turma);
}
void professorEditarNotas(int id, int unico){
	printf("Selecione uma turma: ");
	int tamanhoA, ano;
	char turma;
	Aluno alunos[MAXN];
	
	inputTurma(&ano, &turma);
	tamanhoA = preencherTurma(ano, turma, alunos);
	
	if(!tamanhoA) {
		printf("Turma invalida. ");
		return;
	}
	
	cabecalho();
	printf("Provas da turma %d%c", ano, turma);

	int flag = 1;
	for(int i = 0; i < MAXN; i++){
		if(PROVAS[i].idProfessor == id && PROVAS[i].ano == ano && PROVAS[i].turma == turma){
			printf("\n%s", PROVAS[i].nome);
			flag = 0;
		}
	}
	if(flag){
		printf("\nNao foram encontradas provas para essa turma");
		esperar();
		return;
	}
	printf("\n\nEscolha uma das provas acima: ");
	
	char nomeProva[NAME_SIZE];
	int idProva;
	do {
		digitaString(NAME_SIZE, nomeProva);
		if(!strcmp(nomeProva, "0")) return;
		idProva = buscarProva(nomeProva, ano, turma, id);
		if(!idProva) printf("Insira uma prova existente");
	} while(!idProva);
	
	if(unico){
		char nomeAluno[MAXN];
		int idAluno;
		
		cabecalho();
		printf("Notas d@s alun@s da turma %d%c em %s", ano, turma, nomeProva);
		printf("\nAlun@ - Nota:");
		
		for(int i = 0; i < tamanhoA; i++){
			printf("\n%s - %.1f", alunos[i].nome, alunoNota(idProva, alunos[i].id));
		}
		
		printf("\n\nEscolha um(a) alun@: ");
		int alunoExiste = 0;
		do {
			digitaString(NAME_SIZE, nomeAluno);
			idAluno = buscarAluno(nomeAluno, 0);

			alunoExiste = idAluno && ALUNOS[idAluno - 1].ano == ano && ALUNOS[idAluno - 1].turma == turma;
			if (!alunoExiste) {
				printf("Insira um(a) alun@ existente dessa turma");
			}
		} while(!alunoExiste);
		
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
			float notaAluno = alunoNota(idProva, alunos[i].id);
			printf("%s\n%s\nNota atual: %.1f\nNova nota: ", nomeProva, alunos[i].nome, notaAluno);
			
			float nota;
			while(1){
				scanf("%f", &nota);
				consumirInput();
				if(nota <= 10 && nota >= 0) break;
				printf("A nota deve estar entre 0 e 10, tente novamente: ");
			}
			
			editarNota(idProva, alunos[i].id, nota);
		}
	}
}
void professorIncrementarFaltas(int id){
	printf("Selecione uma turma: ");
	int tamanho, ano;
	char turma;
	Aluno alunos[MAXN];
	
	do{
		inputTurma(&ano, &turma);
		tamanho = preencherTurma(ano, turma, alunos);
		
		if(!tamanho) printf("Turma invalida, tente novamente: ");
	} while(!tamanho);
	
	cabecalho();
	printf("id - nome - faltas");
	for(int i = 0; i < tamanho; i++){
		printf("\n%d - %s - %d", alunos[i].id, alunos[i].nome, alunoFaltas(id, alunos[i].id));
	};
	
	printf("\n\nEscolha um(a) alun@: ");
	
	char nomeAluno[NAME_SIZE];
	int idAluno;
	int existe = 0;
	do {
		digitaString(NAME_SIZE, nomeAluno);
		idAluno = buscarAluno(nomeAluno, 0);
		existe = !(!idAluno || ALUNOS[idAluno-1].ano != ano || ALUNOS[idAluno-1].turma != turma);
		if(!existe)
			printf("Insira um(a) alun@ existente e dessa turma: ");
	} while (!existe);
	
	cabecalho();
	int incremento;
	printf("%s - %d faltas", ALUNOS[idAluno-1].nome, alunoFaltas(id, idAluno));
	printf("\nQuantas faltas devem ser incrementadas? (numeros negativos podem ser usados) ");
	scanf("%d", &incremento);
	consumirInput();
	incrementarFaltas(id, idAluno, incremento);
	
	cabecalho();
	printf("%s - %d faltas", ALUNOS[idAluno-1].nome, alunoFaltas(id, idAluno));
	esperar();
}
void professorDeletarProva(int id){
	cabecalho();
	Prova provas[MAXN];
	int tamanho = preencherProvas(id, 0, 0, provas);
	if(!tamanho){
		printf("Nao ha provas cadastradas");
		esperar();
		return;
	}
	
	printf("id - nome - turma");
	for(int i = 0; i < tamanho; i++){
		printf("\n%d - %s - %d%c", provas[i].id, provas[i].nome, provas[i].ano, provas[i].turma);;
	}
	
	int idProva;
	printf("\n\nEscolha uma dessas provas (pelo id): ");
	int flag = 0;
	while(1){
		scanf("%d", &idProva);
		for(int i = 0; i < tamanho; i++){
			if(provas[i].id == idProva) flag = 1;
		}
		if(flag) break;
		printf("Id invalido, tente novamente: ");
	}
	
	cabecalho();
	char resposta[NAME_SIZE];
	printf("Voce esta prestes a deletar %s, tem certeza?\nDigite o nome da prova para confirmar: ", PROVAS[idProva-1].nome);
	scanf("%s", resposta);
	if(!strcmp(resposta, PROVAS[idProva-1].nome)) deletarProva(idProva);
}

void mostrarMenuProfessor(){
	int opcao;
	
	do {
		cabecalho();
		printf("Bem-vind@, %s, o que voce quer fazer hoje?\n", PROFESSORES[SESSION_ID - 1].nome);
		printf("0 - Sair\n");
		printf("1 - Ver turmas\n");
		printf("2 - Ver provas\n");
		printf("3 - Cadastrar prova\n");
		printf("4 - Editar notas em massa\n");
		printf("5 - Editar notas de um(a) unic@ alun@\n");
		printf("6 - Incrementar faltas de um(a) alun@\n");
		printf("7 - Excluir prova\n");
		printf("8 - Gerar tabela de nota das provas\n");
		printf("9 - Gerar tabela de nota final\n");
		printf("10 - Alterar senha\n");
		
		opcao = digitaOpcao(0, 10);
		
		switch(opcao){
			char senha[PASS_SIZE], senhaNova[PASS_SIZE], senhaNovaConfirmar[PASS_SIZE];
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
				break;
			case 1:
				professorListarTurmas(SESSION_ID);
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
				professorIncrementarFaltas(SESSION_ID);
				break;
			case 7:
				professorDeletarProva(SESSION_ID);
				break;
			case 8:
				professorTabelaDeNotas(SESSION_ID, 0);
				break;
			case 9:
				professorTabelaDeNotas(SESSION_ID, 1);
				break;
			case 10:
				mudarSenha(TIPO_PROF);
				break;
		}
	} while(opcao);
}
