#include "menuAluno.h"

void alunoVerNotas(int id, char materia[4]){
    Nota notas[MAXN] = {};
    int tamanho = alunoPreencherNotas(id, materia, notas);
	
    float soma = 0;
    
    for(int i = 0; i < tamanho; i++){
        soma += notas[i].nota;
    }

	cabecalho();
    printf("Notas em %s - Prof. %s\n", materia, PROFESSORES[buscarProfessorPorMateria(materia)-1].nome);
    for(int i = 0; i < tamanho; i++){
        printf("%s: %.1f\n", PROVAS[notas[i].idProva-1].nome, notas[i].nota);
    }
    printf("Media na materia: %.1f", soma/tamanho);
	
	printf("\n\nPressione ENTER para voltar\n");
	
	int c;
	while((c = getchar()) != '\n');
	fflush(stdout);
	while((c = getchar()) != '\n');
}

void alunoVerMedias(int id){
	typedef struct {
		char materia[4];
        float soma;
        unsigned int contador;
    } Materia;
	
    Nota notas[MAXN] = {};
    Materia materias[MAXN] = {};
    int tamanho = alunoPreencherNotas(id, "***", notas);
    int maxIndex = 0;
	
    for(int i = 0; i < tamanho; i++){ // percorre todas as notas do aluno para separar por materia
        int flag = 1;
		char materia[4];
		strcpy(materia, PROFESSORES[PROVAS[notas[i].idProva-1].idProfessor-1].materia);
        for(int j = 0; j <= maxIndex; j++){ // percorre o array de notas vendo se ja existe um struct da materia em questao
            if(!strcmp(materia, materias[j].materia)){
				materias[j].soma += notas[i].nota;
                materias[j].contador++;
                flag = 0;
                break;
            }
        }
        if(!flag) continue;
        
		Materia a = {"", notas[i].nota, 1};
		strcpy(a.materia, materia);
        materias[maxIndex] = a;
		maxIndex++;
    }
	
	printf("AAAAAAAAAAAAAAAAAAAAAAA\n\n");
	cabecalho();
    float soma = 0;
    int contador = 0;
    for(int i = 0; i < maxIndex; i++){
		printf("Media em %s: %.1f\n", materias[i].materia, materias[i].soma/materias[i].contador);
        soma += materias[i].soma/materias[i].contador;
        contador++;
    }
    printf("Media geral: %.1f", soma/contador);
	
	printf("\n\nEscolha uma materia para ver detalhes ou 0 para voltar:\n");
	char opcao[4];
	scanf("%s", opcao);
	for(int i = 0; i < maxIndex; i++){
		if(!strcmp(materias[i].materia, opcao)){
			alunoVerNotas(id, materias[i].materia);
			return;
		}
	}
}

int alunoPreencherNotas(int id, char *materia, Nota *notas){
    int index = 0;

    for(int i = 0; i < (MAXN); i++){
        Nota nota = NOTAS[i];
        const char *materiaNota = PROFESSORES[PROVAS[nota.idProva - 1].idProfessor - 1].materia;
        if(nota.idAluno == id && (!strcmp(materia, materiaNota) || !strcmp(materia, "***"))){
            notas[index] = NOTAS[i];
            index++;
        }
    }

    return index;
}

void mostrarMenuAluno(){
	int opcao;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s, o que voce quer fazer hoje?\n", ALUNOS[SESSION_ID - 1].nome);
		printf("0 - sair\n");
		printf("1 - ver notas\n");
		
		scanf("%d", &opcao);
		
		switch(opcao){
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
			case 1:
				printf("\n\nA OPCAO E %d", opcao);
				alunoVerMedias(SESSION_ID);
				break;
		}
	} while(opcao);
	
	return;
}