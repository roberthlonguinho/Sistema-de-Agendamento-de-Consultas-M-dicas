#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nodeptr;
typedef struct nodef *nodefptr;

struct node{
    int CRM; 
    char nome[100];
    char especialidade[100];
    nodeptr next;
};

struct consulta{
    char paciente[100];
    int CRM;
};

struct nodef{
    struct consulta elen;
    nodefptr next;
};

void cadastrarMedico(nodeptr *u){

    nodeptr p = (nodeptr)malloc(sizeof(struct node));

    if(p == NULL){
		printf("\n--------------------------\n");
        printf("Nao foi possivel cadastrar m�dico!\n");
        printf("\n--------------------------\n");
        return;

    }
	
	printf("\n--------------------------\n");
    printf("CRM do medico:\n");
    scanf("%d", &p->CRM);
    printf("Nome do medico:\n");
    scanf(" %[^\n]s", p->nome);
    printf("Especialidade do medico:\n");
    scanf(" %[^\n]s", p->especialidade);
    printf("\n--------------------------\n");
    p->next = *u;
    *u = p;

    printf("Medico cadastrado com sucesso!\n");
    printf("\n--------------------------\n");

}


void enqueueConsulta(nodefptr *p, nodefptr *u, struct consulta consul){

    nodefptr n = (nodefptr)malloc(sizeof(struct nodef));

    if(n == NULL){
    	
		printf("\n--------------------------\n");
        printf("Nao foi possivel empilhar consulta!\n");
        printf("\n--------------------------\n");
        return;

    }

    n->elen = consul;
    n->next = NULL;

    if(*u != NULL){
        (*u)->next = n;
    }
    *u = n;
    if (*p == NULL) {
        *p = n;
    }

}


struct consulta dequeueConsulta(nodefptr *p, nodefptr *u){
	
    struct consulta c = {"", -1};
    
    if(*p == NULL){
    	
    	printf("\n--------------------------\n");
        printf("A fila de consultas est� vazia!\n Nenhuma consulta para liberar.\n");
        printf("\n--------------------------\n");

        return c;

}

    nodefptr aux = *p;
    c = aux->elen;
    *p = aux->next;
    if(*p == NULL){
        *u = NULL;
    }
    free(aux);
    return c;

}


void cadastrarConsulta(nodefptr *p, nodefptr *u){

    struct consulta consul;
	printf("\n--------------------------\n");
    printf("Nome do paciente: ");
    scanf(" %[^\n]s", consul.paciente);
    printf("CRM do medico: ");
    scanf("%d", &consul.CRM);
    printf("\n--------------------------\n");
    enqueueConsulta(p, u, consul);
    printf("\n--------------------------\n");
    printf("Consulta cadastrada com sucesso!\n");
    printf("\n--------------------------\n");

}


void listarMedicos(nodeptr med){

    nodeptr p = med;

    if(p == NULL){
    printf("\n--------------------------\n");
    printf("Nenhum m�dico cadastrado.\n");
    printf("\n--------------------------\n");
    return;

	}

    while(p != NULL){
	    printf("\n--------------------------\n");
        printf("CRM: %d\n", p->CRM);
        printf("Nome: %s\n", p->nome);
        printf("Especialidade: %s\n", p->especialidade);
        printf("\n------------------------------------\n");
        p = p->next;

    }
}


void listarConsultas(nodefptr aux){

    nodefptr p = aux;

    if(p == NULL){
		printf("\n--------------------------\n");
        printf("\n Nenhuma consulta cadastrada.\n");
        printf("\n--------------------------\n");
        return;

    }

    while(p != NULL){
    	
		printf("\n--------------------------\n");
        printf("Paciente: %s\n", p->elen.paciente);
        printf("CRM do medico: %d\n", p->elen.CRM);
        printf("\n----------------------------\n");
        p = p->next;

    }
}


void CRMM(nodefptr *p, nodefptr *u){

    struct consulta consul = dequeueConsulta(p, u);

    if(consul.CRM != -1){
		printf("\n--------------------------\n");
        printf("Consulta liberada para o paciente: %s\n", consul.paciente);
        printf("CRM do medico: %d\n", consul.CRM );
        printf("\n--------------------------\n");

    }
}


void liberarListas(nodeptr *p, nodefptr *q){

    while(*p != NULL){

        nodeptr aux = *p;
        *p = (*p)->next;
        free(aux);

    }


    while(*q != NULL){

        nodefptr aux = *q;
        *q = (*q)->next;
        free(aux);

    }

}

void deletarmedico(nodeptr *p, int CRM){
    nodeptr a, q;
    a=NULL, q=*p; 

    while(q != NULL && q->CRM != CRM){
        a = q;
        q = q->next;
    }
    if(q!=NULL){
        if(a==NULL){
            *p=q->next;
        }else{
            a->next=q->next;
        }
        free(q);
    }
}

int main(void){

    nodeptr p = NULL; nodefptr a = NULL;
    nodefptr u = NULL;
    int opcao;
	int CRM;

    do {

        printf("\n------------MENU------------\n");
        printf("1. Cadastrar medico        |\n");
        printf("2. Cadastrar consulta      |\n");
        printf("3. Liberar consulta        |\n");
        printf("4. Listar medicos          |\n");
        printf("5. Listar consultas        |\n");
        printf("6. Deletar medico          |\n");
        printf("7. Sair                    |\n");
        printf("----------------------------\n");
        printf("\n Escolha uma opcao: ");
        scanf("%d", &opcao);

    switch(opcao){


    case 1:
    cadastrarMedico(&p);
    break;


    case 2:
    cadastrarConsulta(&a, &u);
    break;


    case 3:
    CRMM(&a, &u);
    liberarListas(&p, &a);
    break;


    case 4:
    listarMedicos(p);
    break;


    case 5:
    listarConsultas(a);
    break;


    case 6:
    printf(" Digite o codigo CRM do medico que deseja de letar:\n");
    scanf(" %d", &CRM);
    deletarmedico(&p, CRM);
    break;

	case 7:
	break;
	
	default:
    printf("Opcao invalida! \nPor favor, tente novamente!\n");
    break;
}

} while (opcao != 7);

}
