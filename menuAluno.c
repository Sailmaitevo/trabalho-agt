#include "menuAluno.h"

void alunoVerNotas(int id, int idProfessor){
    Nota notas[MAXN] = {};
	Professor professor = PROFESSORES[idProfessor - 1];
	
    int tamanho = alunoPreencherNotas(id, idProfessor, notas);
	
    float soma = 0;
    
    for(int i = 0; i < tamanho; i++){
        soma += notas[i].nota;
    }

	cabecalho();
    printf("Notas em %s - Prof. %s\n", professor.materia, professor.nome);
    for(int i = 0; i < tamanho; i++){
        printf("%s: %.1f\n", PROVAS[notas[i].idProva-1].nome, notas[i].nota);
    }
    printf("Media na materia: %.1f", soma/tamanho);
	
	esperar();
	
	alunoVerMedias(id);
}
void alunoVerMedias(int id){
	typedef struct {
		char materia[4];
        float soma;
        int contador;
		int idProfessor;
    } Materia;
	
    Nota notas[MAXN] = {};
    Materia materias[MAXN] = {};
    int tamanho = alunoPreencherNotas(id, 0, notas);
    int maxIndex = 0;
	
    for(int i = 0; i < tamanho; i++){
        int flag = 0;
		int idProfessor = PROVAS[notas[i].idProva-1].idProfessor;
        for(int j = 0; j < maxIndex; j++){
			if(idProfessor == materias[j].idProfessor){
				materias[j].soma += notas[i].nota;
                materias[j].contador++;
                flag = 1;
                break;
            }
        }
        if(flag) continue;
        
		Materia aux = {"", notas[i].nota, 1, idProfessor};
		strcpy(aux.materia, PROFESSORES[idProfessor-1].materia);
        materias[maxIndex] = aux;
		maxIndex++;
    }
	
	cabecalho();
    float soma = 0;
    int contador = 0;
	
	if(!tamanho){
		printf("\nNao foram encontradas notas");
		esperar();
		return;
	}
	
    for(int i = 0; i < maxIndex; i++){
		printf("%d - %s: %.1f\n", i+1, materias[i].materia, materias[i].soma/materias[i].contador);
        soma += materias[i].soma/materias[i].contador;
        contador++;
    }
    printf("Media geral: %.1f", soma/contador);
	
	int opcao;
	printf("\n\nInsira uma materia (utilize o numero) para ver detalhes ou 0 para voltar: ");
	opcao = digitaOpcao(0, maxIndex);
	if(opcao >= 1 && opcao <= maxIndex){
		alunoVerNotas(id, materias[opcao-1].idProfessor);
	}
}
void alunoVerFaltas(int id){
	Faltas faltas[MAXN] = {};
	int tamanho = alunoPreencherFaltas(id, faltas);
	
	cabecalho();
	printf("Suas faltas");
	if(!tamanho){
		printf("\nNao foram encontradas faltas");
	}
	for(int i = 0; i < tamanho; i++){
		printf("\n%s - %d", PROFESSORES[faltas[i].idProfessor-1].materia, faltas[i].numero);
	}
	
	esperar();
}
void alunoBoletim(int id){
	Aluno aluno = ALUNOS[id-1];
	
	FILE *arquivo = NULL;
	printf("Deseja salvar num arquivo de texto? (s/n)");
	int salvar = inputSimNao();
	if(salvar){
		char caminho[NAME_SIZE+4];
		int flag = 0;
		printf("Digite o nome do arquivo (ate %d caracteres sem extensao, 0 para cancelar)", NAME_SIZE-1);
		while(1) {
			digitaString(NAME_SIZE, caminho);
			if(!strcmp(caminho, "0")){
				salvar = 0;
				break;
			}
			
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
	printf("Boletim - %s\nDocumento gerado em %s", aluno.nome, tempo);
	if(salvar) fprintf(arquivo, "Boletim - %s\nDocumento gerado em %s", aluno.nome, tempo);
	
	Nota notas[MAXN] = {};
	int professores[MAXN] = {}, maxIndex = 0;
	int tamanho = alunoPreencherNotas(id, 0, notas);
	for(int i = 0; i < tamanho; i++){
		int flag = 0;
		for(int j = 0; j < maxIndex; j++){
			if(PROVAS[notas[i].idProva - 1].idProfessor == professores[j]){
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		professores[maxIndex] = PROVAS[notas[i].idProva - 1].idProfessor;
		maxIndex++;
	}
	
	if(!tamanho){
		printf("\nNao foram encontradas notas para ess@ alun@");
		if(salvar) fprintf(arquivo, "\nNao foram encontradas notas para ess@ alun@");
		esperar();
		return;
	}
	
	char s[NAME_SIZE+MATERIA_SIZE+2] = "Materia (professor(a))";
	padString(s, NAME_SIZE+MATERIA_SIZE+2, 'd');
	printf("\n| %s |", s);
	if(salvar) fprintf(arquivo, "\n| %s |", s);
	
	printf(" Media |");
	if(salvar) fprintf(arquivo, " Media |", s);
	
	printf(" Faltas |");
	if(salvar) fprintf(arquivo, " Faltas |", s);
	
	strcpy(s, "Resultado");
	padString(s, NAME_SIZE-6, 'c');
	printf(" %s |", s);
	if(salvar) fprintf(arquivo, " %s |", s);

	printf(" Nota Minima No Exame |");
	if(salvar) fprintf(arquivo, " Nota Minima No Exame |");
	
	float notas_total = 0;
	int faltas_total = 0;
	for(int i = 0; i < maxIndex; i++){
		Professor professor = PROFESSORES[professores[i]-1];
		
		float media = alunoMedia(id, professor.id);
		int faltas = alunoFaltas(id, professor.id);
		notas_total += media;
		faltas_total += faltas;
		
		sprintf(s, "%s (%s)", professor.materia, professor.nome);
		padString(s, NAME_SIZE+MATERIA_SIZE+2, 'd');
		printf("\n| %s |", s);
		if(salvar) fprintf(arquivo, "\n| %s |", s);
		
		char c[NAME_SIZE] = {};
		
		sprintf(c, "%.1f", media);
		padString(c, 6, 'c');
		printf(" %s |", c);
		if(salvar) fprintf(arquivo, " %s |", c);
		
		sprintf(c, "%d", faltas);
		padString(c, 7, 'c');
		printf(" %s |", c);
		if(salvar) fprintf(arquivo, " %s |", c);

		int exame = 0;
		if (faltas > AULAS_NUM / 4) {
			sprintf(s, "REP POR FALTA");
		} else if (calcularMediaExame(media) > 10) {
			sprintf(s, "REPROVAD@");
		} else if (media < MEDIA_MIN) {
			exame = 1;
			sprintf(s, "EM EXAME");
		} else {
			sprintf(s, "APROVAD@");
		}
		padString(s, NAME_SIZE-6, 'c');
		printf(" %s |", s);
		if(salvar) fprintf(arquivo, " %s |", s);

		strcpy(s, "");
		if (exame) {
			sprintf(s, "%.1f", calcularMediaExame(media));
		} else {
			sprintf(s, " - ");
		}
		
		padString(s, strlen("Nota Minima No Exame "), 'c');
		printf(" %s |", s);
		if(salvar) fprintf(arquivo, " %s |", s);
	}
	
	if(salvar) fclose(arquivo);
	
	esperar();
}

void mostrarMenuAluno(){
	
	int opcao;
	
	do {
		cabecalho();
		printf("Bem-vind@, %s, o que voce quer fazer hoje?\n", ALUNOS[SESSION_ID - 1].nome);
		printf("0 - sair\n");
		printf("1 - ver notas\n");
		printf("2 - ver faltas\n");
		printf("3 - gerar boletim\n");
		printf("4 - alterar senha\n");
		
		opcao = digitaOpcao(0, 4);
		
		switch(opcao){
			char senha[PASS_SIZE], senhaNova[PASS_SIZE], senhaNovaConfirmar[PASS_SIZE];
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
				break;
			case 1:
				alunoVerMedias(SESSION_ID);
				break;
			case 2:
				alunoVerFaltas(SESSION_ID);
				break;
			case 3:
				alunoBoletim(SESSION_ID);
				break;
			case 4:
				mudarSenha(TIPO_ALUNO);
				break;
		}
	} while(opcao);
}
