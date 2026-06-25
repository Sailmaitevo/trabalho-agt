#include "database.h"
const char MSG_DB_CHEIO[] = "Erro! O banco de dados esta cheio!\nSobrescrevendo o banco de dados e fechando a aplicação...";

unsigned criptografar(const unsigned char *str) {
    unsigned hash = 7723;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]){
    for(int i = 0; i < MAXN; i++){
        if(PROFESSORES[i].id == 0){
			Professor professor = {i+1, nome, criptografar(senha), materia};
            PROFESSORES[i] = professor;
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase();
}

void cadastrarAluno(int id, char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, char turma, int idPai){
    for(int i = 0; i < MAXN; i++){
        if(ALUNOS[i].id == 0){
			Aluno aluno = {i+1, nome, criptografar(senha), ano, turma, idPai};
            ALUNOS[i] = aluno;
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase(); 
}

void cadastrarProva(int idProfessor, int ano, char turma){
    for(int i = 0; i < MAXN; i++){
        if(PROVAS[i].id == 0){
			Prova prova = {i+1, ano, turma};
            PROVAS[i] = prova;
            criarNotas(i);
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!\nSobrescrevendo o banco de dados e fechando a aplicação...");
    sobrescreverDatabase();
}

void cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ADMINS[i].id == 0){
			Admin admin = {i+1, nome, criptografar(senha)};
            ADMINS[i] = admin;
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase();
}

void zerarNotas(int idProva){
    Prova prova = PROVAS[idProva-1];
    int ultimoIndex = 0;

    for(int i = 0; i < MAXN; i++){
        if (ultimoIndex == MAXN << 2){
            printf("Erro, o banco de dados esta cheio!");
            deletarProva(idProva);
            sobrescreverDatabase();
        }

        if(ALUNOS[i].ano == prova.ano && ALUNOS[i].turma == prova.turma){
            for(ultimoIndex; ultimoIndex < MAXN; ultimoIndex++){
                if(NOTAS[ultimoIndex].idProva == 0){
					Nota nota = {idProva, i+1, 0.0};
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
    Aluno aluno = {0, "", 0, 0, 0, 0};
	ALUNOS[id-1] = aluno;
}
void deletarProva(int id){
    for(int i = 0; i < (MAXN << 2); i++){
        if(NOTAS[i].idProva == id){
			Nota nota = {0, 0, 0.0};
			NOTAS[i] = nota;
		}
    }
	Prova prova = {0, 0, 0};
    PROVAS[id-1] = prova;
}
void deletarAdmin(int id){
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
        if(PROFESSORES[i].nome == nome) return i+1;
    }
    return 0;
}
int buscarAluno(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ALUNOS[i].nome == nome) return i+1;
    }
    return 0;
}
int buscarAdmin(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ADMINS[i].nome == nome) return i+1;
    }
    return 0;
}