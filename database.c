#include "database.h"
const char MSG_DB_CHEIO[] = "Erro! O banco de dados esta cheio!\nSobrescrevendo o banco de dados e fechando a aplicação...";

FILE *importarArquivo(char *caminho){
	FILE *arquivo = fopen(caminho, "r");
	if(arquivo == NULL){
		arquivo = fopen(caminho, "w");
		if(arquivo == NULL){
			printf("Erro fatal: não foi possível criar o arquivo %s", caminho);
			exit(EXIT_FAILURE);
		}
	}
	fclose(arquivo);
	
	return fopen(caminho, "r");
}

void importarDatabase(){
	printf("Importando banco de dados...\n");
	FILE *admins = importarArquivo("Database/Admins.csv");
	char linhaAdmins[NAME_SIZE+19];
	
	for(int i = 0; fgets(linhaAdmins, sizeof(linhaAdmins), admins) != NULL; i++){
		sscanf(linhaAdmins, "%d,%[^,],%u", &ADMINS[i].id, &ADMINS[i].nome, &ADMINS[i].senha);
	}
	
	FILE *alunos = importarArquivo("Database/Alunos.csv");
	char linhaAlunos[NAME_SIZE+23];
	
	for(int i = 0; fgets(linhaAlunos, sizeof(linhaAlunos), alunos) != NULL; i++){
		sscanf(linhaAlunos, "%d,%[^,],%u,%d,%c", &ALUNOS[i].id, &ALUNOS[i].nome, &ALUNOS[i].senha, &ALUNOS[i].ano, &ALUNOS[i].turma);
	}
	
	FILE *professores = importarArquivo("Database/Professores.csv");
	char linhaProfessores[NAME_SIZE+24];
	
	for(int i = 0; fgets(linhaProfessores, sizeof(linhaProfessores), professores) != NULL; i++){
		sscanf(linhaProfessores, "%d,%[^,],%u,%s", &PROFESSORES[i].id, &PROFESSORES[i].nome, &PROFESSORES[i].senha, &PROFESSORES[i].materia);
	}
	
	FILE *provas = importarArquivo("Database/Provas.csv");
	char linhaProvas[NAME_SIZE+19];
	
	for(int i = 0; fgets(linhaProvas, sizeof(linhaProvas), provas) != NULL; i++){
		sscanf(linhaProvas, "%d,%[^,],%d,%d,%c", &PROVAS[i].id, PROVAS[i].nome, &PROVAS[i].idProfessor, &PROVAS[i].ano, &PROVAS[i].turma);
	}
		
	FILE *notas = importarArquivo("Database/Notas.csv");
	char linhaNotas[17];
	
	for(int i = 0; fgets(linhaNotas, sizeof(linhaNotas), notas) != NULL; i++){
		sscanf(linhaNotas, "%d,%d,%f", &NOTAS[i].idProva, &NOTAS[i].idAluno, &NOTAS[i].nota);
		NOTAS[i].nota = roundf(NOTAS[i].nota * 10.0)/10.0;
	}
	
	fclose(admins);
	fclose(alunos);
	fclose(notas);
	fclose(professores);
	fclose(provas);
}

void sobrescreverDatabase(){
	FILE *admins = fopen("Database/Admins.csv", "w");
	FILE *alunos = fopen("Database/Alunos.csv", "w");
	FILE *notas = fopen("Database/Notas.csv", "w");
	FILE *professores = fopen("Database/Professores.csv", "w");
	FILE *provas = fopen("Database/Provas.csv", "w");
	
	for(int i = 0; i < MAXN; i++){
		if(ADMINS[i].id)
			fprintf(admins, "%d,%s,%u\n", ADMINS[i].id, ADMINS[i].nome, ADMINS[i].senha);
		if(ALUNOS[i].id)
			fprintf(alunos, "%d,%s,%u,%d,%c\n", ALUNOS[i].id, ALUNOS[i].nome, ALUNOS[i].senha, ALUNOS[i].ano, ALUNOS[i].turma);
		if(NOTAS[i].idProva)
			fprintf(notas, "%d,%d,%f\n", NOTAS[i].idProva, NOTAS[i].idAluno, NOTAS[i].nota);
		if(PROFESSORES[i].id)
			fprintf(professores, "%d,%s,%u,%s\n", PROFESSORES[i].id, PROFESSORES[i].nome, PROFESSORES[i].senha, PROFESSORES[i].materia);
		if(PROVAS[i].id)
			fprintf(provas, "%d,%s,%d,%d,%c\n", PROVAS[i].id, PROVAS[i].nome, PROVAS[i].idProfessor, PROVAS[i].ano, PROVAS[i].turma);
	}
	
	fclose(admins);
	fclose(alunos);
	fclose(notas);
	fclose(professores);
	fclose(provas);
	
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

void cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]){
    for(int i = 0; i < MAXN; i++){
        if(PROFESSORES[i].id == 0){
			Professor professor = {i+1, "", criptografar(senha), ""};
			strcpy(professor.nome, nome);
			strcpy(professor.materia, materia);
            PROFESSORES[i] = professor;
            return;
        }
    }
    
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase();
}
void cadastrarAluno(char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, char turma){
    for(int i = 0; i < MAXN; i++){
        if(ALUNOS[i].id == 0){
			Aluno aluno = {i+1, "", criptografar(senha), ano, turma};
			strcpy(aluno.nome, nome);
            ALUNOS[i] = aluno;
            return;
        }
    }
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase(); 
}
void cadastrarProva(char nome[NAME_SIZE], int idProfessor, int ano, char turma){
    for(int i = 0; i < MAXN; i++){
        if(PROVAS[i].id == 0){
			Prova prova = {i+1, "", idProfessor, ano, turma};
			strcpy(prova.nome, nome);
            PROVAS[i] = prova;
            zerarNotas(i, 0);
            return;
        }
    }
    printf("Erro! O banco de dados esta cheio!\nSobrescrevendo o banco de dados e fechando a aplicação...");
    sobrescreverDatabase();
}
void cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ADMINS[i].id == 0){
			Admin admin = {i+1, "", criptografar(senha)};
			strcpy(admin.nome, nome);
            ADMINS[i] = admin;
            return;
        }
    }
    
    printf("Erro! O banco de dados esta cheio!");
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

void deletarProfessor(int id){
	Professor professor = {0, "", 0, "---"};
    PROFESSORES[id-1] = professor;
}
void deletarAluno(int id){
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

int validarProfessor(int id, char senha[PASS_SIZE]){
    unsigned senhaCriptografada = criptografar(senha);
    return PROFESSORES[id-1].senha == senhaCriptografada;
}
int validarAluno(int id, char senha[PASS_SIZE]){
    unsigned senhaCriptografada = criptografar(senha);
    return ALUNOS[id-1].senha == senhaCriptografada;
}
int validarAdmin(int id, char senha[PASS_SIZE]){
    unsigned senhaCriptografada = criptografar(senha);
    return ADMINS[id-1].senha == senhaCriptografada;
}

int buscarProfessor(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(!strcmp(PROFESSORES[i].nome, nome)) return i+1;
    }
    return 0;
}
int buscarAluno(char nome[NAME_SIZE]){
	for(int i = 0; i < MAXN; i++){
		if(!strcmp(ALUNOS[i].nome, nome)) return i+1;
    }
    return 0;
}
int buscarAdmin(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(!strcmp(ADMINS[i].nome, nome)) return i+1;
    }
    return 0;
}
int buscarProva(char nome[NAME_SIZE]){
	for(int i = 0; i < MAXN; i++){
        if(!strcmp(PROVAS[i].nome, nome)) return i+1;
    }
    return 0;
}
int buscarProfessorPorMateria(char materia[4]){
	for(int i = 0; i < MAXN; i++){
		if(!strcmp(PROFESSORES[i].materia, materia)) return i+1;
	}
	return 0;
}