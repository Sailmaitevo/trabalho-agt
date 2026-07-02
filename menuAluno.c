#include "menuAluno.h"

void alunoVerNotas(int id, int idProfessor){
	printf("OI");
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
	
	printf("\n\nPressione ENTER para voltar\n");
	
	alunoVerMedias(id);
}

void alunoVerMedias(int id){
	typedef struct {
		char materia[4];
        float soma;
        unsigned contador;
		int idProfessor;
    } Materia;
	
    Nota notas[MAXN] = {};
    Materia materias[MAXN] = {};
    int tamanho = alunoPreencherNotas(id, 0, notas);
    int maxIndex = 0;
	
    for(int i = 0; i < tamanho; i++){
        int flag = 1;
		int idProfessor = PROVAS[notas[i].idProva-1].idProfessor;
        for(int j = 0; j <= maxIndex; j++){ // percorre o array de notas vendo se ja existe um struct da materia em questao
            if(idProfessor == materias[j].idProfessor){
				materias[j].soma += notas[i].nota;
                materias[j].contador++;
                flag = 0;
                break;
            }
        }
        if(!flag) continue;
        
		Materia aux = {"", notas[i].nota, 1, idProfessor};
		strcpy(aux.materia, PROFESSORES[idProfessor-1].materia);
        materias[maxIndex] = aux;
		maxIndex++;
    }
	
	cabecalho();
    float soma = 0;
    int contador = 0;
    for(int i = 0; i < maxIndex; i++){
		printf("%d - %s: %.1f\n", i+1, materias[i].materia, materias[i].soma/materias[i].contador);
        soma += materias[i].soma/materias[i].contador;
        contador++;
    }
    printf("Media geral: %.1f", soma/contador);
	
	int opcao;
	printf("\n\nInsira uma materia (utilize o numero) para ver detalhes ou 0 para voltar: ");
	scanf("%d", &opcao);
	if(opcao >= 1 && opcao <= maxIndex){
		alunoVerNotas(id, materias[opcao-1].idProfessor);
	}
}

int alunoPreencherNotas(int id, int idProfessor, Nota *notas){
    int index = 0;

    for(int i = 0; i < MAXN; i++){
        Nota nota = NOTAS[i];
        int idProfessorNota = PROVAS[nota.idProva - 1].idProfessor;
        if(nota.idAluno == id && (idProfessor == idProfessorNota || idProfessor == 0)){
            notas[index] = NOTAS[i];
            index++;
        }
    }

    return index;
}

float alunoMedia(int id, int idProfessor){
	Nota notas[MAXN] = {};
	int tamanho = alunoPreencherNotas(id, idProfessor, notas);
	if(!tamanho) return 0;
	
	float soma = 0;
	for(int i = 0; i < tamanho; i++){
		soma += notas[i].nota;
	}
	return soma / tamanho;
};

float alunoNota(int idProva, int idAluno){
	for(int i = 0; i < MAXN; i++){
		if(NOTAS[i].idProva == idProva && NOTAS[i].idAluno == idAluno) return NOTAS[i].nota;
	}
	
	return 0;
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
				break;
			case 1:
				alunoVerMedias(SESSION_ID);
				break;
		}
	} while(opcao);
}