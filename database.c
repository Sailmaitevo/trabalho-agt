#include "database.h"

Professor PROFESSORES[MAXN];
Aluno ALUNOS[MAXN];
Prova PROVAS[MAXN];
Nota NOTAS[MAXN];
Admin ADMINS[MAXN];
Faltas FALTAS[MAXN];

const char MSG_DB_CHEIO[] = "Erro! O banco de dados esta cheio!\nSobrescrevendo o banco de dados e fechando a aplicação...";

FILE *importarArquivo(char *caminho, char *padrao){
	FILE *arquivo = fopen(caminho, "r");
	if(arquivo == NULL){
		arquivo = fopen(caminho, "w");
		if(arquivo == NULL){
			printf("Erro fatal: não foi possível criar o arquivo %s", caminho);
			exit(EXIT_FAILURE);
		}
		fprintf(arquivo, padrao);
	}
	fclose(arquivo);
	
	return fopen(caminho, "r");
}

void importarDatabase(){
	printf("Importando banco de dados...\n");
	FILE *admins = importarArquivo("Database/Admins.csv", "1,Adm,1713679732");
	char linhaAdmins[NAME_SIZE+19];
	for(int i = 0; fgets(linhaAdmins, sizeof(linhaAdmins), admins) != NULL; i++){
		sscanf(linhaAdmins, "%d,%[^,],%u", &ADMINS[i].id, &ADMINS[i].nome, &ADMINS[i].senha);
	}
	
	FILE *alunos = importarArquivo("Database/Alunos.csv", "");
	char linhaAlunos[NAME_SIZE+23];
	for(int i = 0; fgets(linhaAlunos, sizeof(linhaAlunos), alunos) != NULL; i++){
		sscanf(linhaAlunos, "%d,%[^,],%u,%d,%c", &ALUNOS[i].id, &ALUNOS[i].nome, &ALUNOS[i].senha, &ALUNOS[i].ano, &ALUNOS[i].turma);
	}
	
	FILE *professores = importarArquivo("Database/Professores.csv", "");
	char linhaProfessores[NAME_SIZE+24];
	for(int i = 0; fgets(linhaProfessores, sizeof(linhaProfessores), professores) != NULL; i++){
		sscanf(linhaProfessores, "%d,%[^,],%u,%s", &PROFESSORES[i].id, &PROFESSORES[i].nome, &PROFESSORES[i].senha, &PROFESSORES[i].materia);
	}
	
	FILE *provas = importarArquivo("Database/Provas.csv", "");
	char linhaProvas[NAME_SIZE+19];
	for(int i = 0; fgets(linhaProvas, sizeof(linhaProvas), provas) != NULL; i++){
		sscanf(linhaProvas, "%d,%[^,],%d,%d,%c", &PROVAS[i].id, PROVAS[i].nome, &PROVAS[i].idProfessor, &PROVAS[i].ano, &PROVAS[i].turma);
	}
		
	FILE *notas = importarArquivo("Database/Notas.csv", "");
	char linhaNotas[26];
	for(int i = 0; fgets(linhaNotas, sizeof(linhaNotas), notas) != NULL; i++){
		sscanf(linhaNotas, "%d,%d,%f", &NOTAS[i].idProva, &NOTAS[i].idAluno, &NOTAS[i].nota);
		NOTAS[i].nota = roundf(NOTAS[i].nota * 10.0)/10.0;
	}
	
	FILE *faltas = importarArquivo("Database/Faltas.csv", "");
	char linhaFaltas[32];
	for(int i = 0; fgets(linhaFaltas, sizeof(linhaFaltas), faltas) != NULL; i++){
		sscanf(linhaFaltas, "%d,%d,%d", &FALTAS[i].idProfessor, &FALTAS[i].idAluno, &FALTAS[i].numero);
	}
	
	fclose(admins);
	fclose(alunos);
	fclose(notas);
	fclose(professores);
	fclose(provas);
	fclose(faltas);
}
void sobrescreverDatabase(){
	FILE *admins = fopen("Database/Admins.csv", "w");
	FILE *alunos = fopen("Database/Alunos.csv", "w");
	FILE *notas = fopen("Database/Notas.csv", "w");
	FILE *professores = fopen("Database/Professores.csv", "w");
	FILE *provas = fopen("Database/Provas.csv", "w");
	FILE *faltas = fopen("Database/Faltas.csv", "w");
	
	for(int i = 0; i < MAXN; i++){
		if(ADMINS[i].id)
			fprintf(admins, "%d,%s,%u\n", ADMINS[i].id, ADMINS[i].nome, ADMINS[i].senha);
		if(ALUNOS[i].id)
			fprintf(alunos, "%d,%s,%u,%d,%c\n", ALUNOS[i].id, ALUNOS[i].nome, ALUNOS[i].senha, ALUNOS[i].ano, ALUNOS[i].turma);
		if(NOTAS[i].idProva)
			fprintf(notas, "%d,%d,%.1f\n", NOTAS[i].idProva, NOTAS[i].idAluno, NOTAS[i].nota);
		if(PROFESSORES[i].id)
			fprintf(professores, "%d,%s,%u,%s\n", PROFESSORES[i].id, PROFESSORES[i].nome, PROFESSORES[i].senha, PROFESSORES[i].materia);
		if(PROVAS[i].id)
			fprintf(provas, "%d,%s,%d,%d,%c\n", PROVAS[i].id, PROVAS[i].nome, PROVAS[i].idProfessor, PROVAS[i].ano, PROVAS[i].turma);
		if(FALTAS[i].idAluno)
			fprintf(faltas, "%d,%d,%d\n", FALTAS[i].idProfessor, FALTAS[i].idAluno, FALTAS[i].numero);
	}
	
	fclose(admins);
	fclose(alunos);
	fclose(notas);
	fclose(professores);
	fclose(provas);
	fclose(faltas);
	
	printf("\nObrigado por utilizar nosso servico\nAte breve");
	exit(EXIT_SUCCESS);
}

unsigned criptografar(const unsigned char *str) {
    unsigned hash = 7723;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]){
    for(int i = 0; i < MAXN; i++){
        if(PROFESSORES[i].id == 0){
			Professor professor = {i+1, "", criptografar(senha), ""};
			strcpy(professor.nome, nome);
			strcpy(professor.materia, materia);
            PROFESSORES[i] = professor;
            return i+1;
        }
    }
    
    printf(MSG_DB_CHEIO);
    sobrescreverDatabase();
}
int cadastrarAluno(char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, char turma){
    for(int i = 0; i < MAXN; i++){
        if(ALUNOS[i].id == 0){
			Aluno aluno = {i+1, "", criptografar(senha), ano, turma};
			strcpy(aluno.nome, nome);
            ALUNOS[i] = aluno;
            return i+1;
        }
    }
    printf(MSG_DB_CHEIO);
    sobrescreverDatabase(); 
}
int cadastrarProva(char nome[NAME_SIZE], int idProfessor, int ano, char turma){
    for(int i = 0; i < MAXN; i++){
        if(!PROVAS[i].id){
			Prova prova = {i+1, "", idProfessor, ano, turma};
			strcpy(prova.nome, nome);
            PROVAS[i] = prova;
            zerarNotas(i+1, 0);
            return i+1;
        }
    }
    printf(MSG_DB_CHEIO);
    sobrescreverDatabase();
}
int cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ADMINS[i].id == 0){
			Admin admin = {i+1, "", criptografar(senha)};
			strcpy(admin.nome, nome);
            ADMINS[i] = admin;
            return i+1;
        }
    }
    
    printf(MSG_DB_CHEIO);
    sobrescreverDatabase();
}

void zerarNotas(int idProva, int delete){
    Prova prova = PROVAS[idProva-1];
    int ultimoIndex = 0;

    for(int i = 0; i < MAXN; i++){
        if (ultimoIndex == MAXN){
            printf("Erro, o banco de dados esta cheio!");
            deletarProva(idProva);
            sobrescreverDatabase();
        }

        if(ALUNOS[i].ano == prova.ano && ALUNOS[i].turma == prova.turma){
            for(ultimoIndex; ultimoIndex < MAXN; ultimoIndex++){
                if(NOTAS[ultimoIndex].idProva == 0){
					Nota nota = {delete ? 0 : idProva, i+1, 0.0};
                    NOTAS[ultimoIndex] = nota;
                    break;
                }
            }
        }
    }
}
void editarNota(int idProva, int idAluno, float nota){
	int ultimoVazio = -1;
	
	for(int i = 0; i < MAXN; i++){
		if(NOTAS[i].idAluno == idAluno && NOTAS[i].idProva == idProva){
			NOTAS[i].nota = nota;
			return;
		}
		if(NOTAS[i].idProva == 0) ultimoVazio = i;
	}
	
	if(ultimoVazio == -1){
		printf(MSG_DB_CHEIO);
		sobrescreverDatabase();
	}
	
	NOTAS[ultimoVazio].idAluno = idAluno;
	NOTAS[ultimoVazio].idProva = idProva;
	NOTAS[ultimoVazio].nota    =    nota;
}

void incrementarFaltas(int idProfessor, int idAluno, int incremento){
	int primeiroVazio = MAXN;
	for(int i = 0; i < MAXN; i++){
		Faltas faltas = FALTAS[i];
		if(!faltas.idAluno){
			primeiroVazio = i < primeiroVazio ? i : primeiroVazio;
			continue;
		}
		if(faltas.idAluno == idAluno && faltas.idProfessor == idProfessor){
			FALTAS[i].numero += incremento;
			if(FALTAS[i].numero < 0) FALTAS[i].numero = 0;
			return;
		}
	}
	if(primeiroVazio >= MAXN){
		printf(MSG_DB_CHEIO);
		sobrescreverDatabase();
	}
	Faltas faltas = {idProfessor, idAluno, incremento < 0 ? 0 : incremento};
	FALTAS[primeiroVazio] = faltas;
}

void deletarProfessor(int id){
	for(int i = 0; i < MAXN; i++){
		if(FALTAS[i].idProfessor == id){
			Faltas faltas = {0, 0, 0};
			FALTAS[i] = faltas;
		}
		
		if(PROVAS[NOTAS[i].idProva-1].idProfessor == id) deletarProva(NOTAS[i].idProva);
	}
	
	Professor professor = {0, "", 0, "---"};
    PROFESSORES[id-1] = professor;
}
void deletarAluno(int id){
	Aluno alunos[MAXN] = {};
	int ano = ALUNOS[id-1].ano;
	char turma = ALUNOS[id-1].turma;
	int tamanho = preencherTurma(ano, turma, alunos) - 1;
	
	for(int i = 0; i < MAXN; i++){
		if(FALTAS[i].idAluno == id){
			Faltas faltas = {0, 0, 0};
			FALTAS[i] = faltas;
		}
		if(NOTAS[i].idAluno == id){
			Nota nota = {0, 0, 0};
			NOTAS[i] = nota;
		}
		if(tamanho && PROVAS[i].ano == ano && PROVAS[i].turma == turma){
			deletarProva(i+1);
		}
	}
	
    Aluno aluno = {0, "", 0, 0, 0};
	ALUNOS[id-1] = aluno;
}
void deletarProva(int id){
    zerarNotas(id, 1);
	Prova prova = {0, "", 0, 0};
    PROVAS[id-1] = prova;
}
void deletarAdmin(int id){
	if(id == 1){
		printf("Não é possível remover o usário administrador principal");
		return;
	}
	Admin admin = {0, "", 0};
    ADMINS[id-1] = admin;
}

int validarSenha(int id, int tipo, char senha[PASS_SIZE]) {
	unsigned hash = 0;
	switch (tipo) {
		case TIPO_ADMIN:
			hash = ADMINS[id-1].senha;
			break;
		case TIPO_ALUNO:
			hash = ALUNOS[id-1].senha;
			break;
		case TIPO_PROF:
			hash = PROFESSORES[id-1].senha;
			break;
	}
	return hash == criptografar(senha);
}

int buscarProfessor(char nome[NAME_SIZE], int capitalizacaoImporta){
    for(int i = 0; i < MAXN; i++){
			if (compararNomes(PROFESSORES[i].nome, nome, capitalizacaoImporta)) {
				return i + 1;
			}
    }
    return 0;
}
int buscarAluno(char nome[NAME_SIZE], int capitalizacaoImporta){
	for(int i = 0; i < MAXN; i++){
		if (compararNomes(ALUNOS[i].nome, nome, capitalizacaoImporta)) {
			return i + 1;
		}
	}
	return 0;
}
int buscarAdmin(char nome[NAME_SIZE], int capitalizacaoImporta){
    for(int i = 0; i < MAXN; i++){
				if(compararNomes(ADMINS[i].nome, nome, capitalizacaoImporta)) {
					return i + 1;
				}
    }
    return 0;
}
int buscarProva(char nome[NAME_SIZE], int ano, char turma){	
	for(int i = 0; i < MAXN; i++){
		if(!strcmp(PROVAS[i].nome, nome) && PROVAS[i].ano == ano && PROVAS[i].turma == turma) return i+1;
	}
	return 0;
}

char fazerMinusculo(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 'a';
  } else {
    return c;
  }
}

char fazerMaiusculo(char c) {
	if (c >= 'a' && c <= 'z') {
		return c - 'a' + 'A';
	} else {
		return c;
	}
}

char ehLetra(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int compararNomes(char nome1[NAME_SIZE], char nome2[NAME_SIZE], int capializacaoImporta) {
  for (int i = 0; i < NAME_SIZE - 1; i++) {
    char c1 = nome1[i];
    char c2 = nome2[i];
    if (c1 == '\0' && c2 == '\0') {
      return 1;
    }
		if (capializacaoImporta) {
			if (c1 != c2) {
				return 0;
			}
		} else {
			if (fazerMinusculo(c1) != fazerMinusculo(c2)) {
				return 0;
			}
		}
  }

  return 1;
}

void acharNome(int id, int tipo, char nome[NAME_SIZE]) {
	switch (tipo) {
		case TIPO_ADMIN:
			strcpy(nome, ADMINS[id - 1].nome);
			break;
		case TIPO_ALUNO:
			strcpy(nome, ALUNOS[id - 1].nome);
			break;
		case TIPO_PROF:
			strcpy(nome, PROFESSORES[id - 1].nome);
			break;
	}
}

int alunoPreencherNotas(int id, int idProfessor, Nota notas[MAXN]){
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
int alunoPreencherFaltas(int id, Faltas *arrayFaltas){
	int index = 0;
	printf("%d", FALTAS[0].numero);
	
	for(int i = 0; i < MAXN; i++){
		Faltas faltas = FALTAS[i];
		if(faltas.idAluno == id){
			arrayFaltas[index] = FALTAS[i];
			index++;
		}
	}
	
	return index;
}
float alunoMedia(int id, int idProfessor){
	Nota notas[MAXN] = {};
	int tamanho = alunoPreencherNotas(id, idProfessor, notas);
	if(!tamanho) return -1;
	
	float soma = 0;
	for(int i = 0; i < tamanho; i++){
		soma += notas[i].nota;
	}
	return soma / tamanho;
};
float alunoNota(int idProva, int idAluno){
	for(int i = 0; i < MAXN; i++){
		if(NOTAS[i].idProva == idProva && NOTAS[i].idAluno == idAluno){
			return NOTAS[i].nota;
		}
	}
	return 0;
}
int alunoFaltas(int idProfessor, int idAluno){
	int faltas = 0;
	
	for(int i = 0; i < MAXN; i++){
		if(idAluno != FALTAS[i].idAluno) continue;
		
		if(!idProfessor) faltas += FALTAS[i].numero;
		else if(idProfessor == FALTAS[i].idProfessor) return FALTAS[i].numero;
	}
	
	return faltas;
}

int preencherProvas(int id, int ano, char turma, Prova *provas){
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
int preencherTurma(int ano, char turma, Aluno alunos[TURMA_SIZE]){
	int length = 0;
	
	for(int i = 0; i < MAXN; i++){
		Aluno aluno = ALUNOS[i];
		if(ano == aluno.ano && aluno.turma == turma){
			alunos[length] = aluno;
			length++;
			if (length >= TURMA_SIZE) {
				break;
			}
		}
	}
	
	return length;
}

int acharIdTipo(int *id, int *tipo, char nome[NAME_SIZE]) {
	int novoId = *id;
	int novoTipo;
	novoId = buscarAluno(nome, 0);
	if (novoId == 0) {
		novoId = buscarProfessor(nome, 0);
		if (novoId == 0) {
			novoId = buscarAdmin(nome, 0);
			if (novoId == 0) {
				return 0;
			} else {
				novoTipo = TIPO_ADMIN;
			}
		} else {
			novoTipo = TIPO_PROF;
		}
	} else {
		novoTipo = TIPO_ALUNO;
	}
	*id = novoId;
	*tipo = novoTipo;

	return 1;
}