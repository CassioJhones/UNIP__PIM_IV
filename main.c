#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

// c�digos ANSI para cores
#define ANSI_RESET   "\x1b[0m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"

struct Usuario {
    char nome_completo[100];
    char login[20];
    char senha[20];
    int empresaSelecionada;
};

struct Empresa {
    char razao_social[100];
    char nome_fantasia[100];
    char cnpj[15];
    char data_abertura[11];
    char telefone[15];
    char responsavel[100];
    char email[100];
    char endereco[100];
    char bairro[50];
    char cidade[50];
    char estado[3];
    char cep[10];
    char indicadores[500];
};

enum Telas {
    TELA_MENU_PRINCIPAL,
    TELA_CADASTRO_EMPRESA,
    TELA_GERENCIAR_EMPRESAS,
    TELA_RELATORIO,
    TELA_CONSULTA_EMPRESA,
    TELA_SAIR,
    TELA_NOVA_OPCAO
};

void visualizarIndicadores(const struct Empresa *empresa);
void visualizarIndicadores(const struct Empresa *empresa);
void excluirCadastro(struct Empresa **empresas, int *numEmpresas);
void opGerenciamento(const struct Empresa *empresas, int numEmpresas, int empresaSelecionada, int *telaAtual);
void exibirMenuPrincipal(const struct Usuario *usuarioLogado);
void cadastrarEmpresa(struct Empresa **empresas, int *numEmpresas, int *telaAtual);
void gerenciarEmpresas(struct Empresa *empresas, int numEmpresas, int *telaAtual);
void exibirRelatorio(const struct Empresa *empresas, int numEmpresas, int *telaAtual);
void limparTela();
struct Usuario fazerLogin(const struct Usuario *usuarios, int numUsuarios);

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Usuario usuarios[4] = {
        {"John Doe", "john", "senha123"},
        {"Jane Doe", "jane", "outrasenha"},
        {"Joao", "joao", "1234"},
        {"ADMINISTRADOR", "0", "0"}  // APENAS PARA TESTE - APAGAR DEPOIS
    };

    struct Empresa *empresas = NULL;
    int numEmpresas = 0;
    int telaAtual = TELA_MENU_PRINCIPAL;

    struct Usuario usuarioLogado = fazerLogin(usuarios, 4);
    if (strcmp(usuarioLogado.login, "") == 0) {
        printf(ANSI_RED "\nUsu�rio n�o encontrado. Encerrando o programa\n"ANSI_RESET);system("pause");
        return 0;    }

    printf("\nLogin bem-sucedido! Bem-vindo, %s.\n", usuarioLogado.nome_completo);system("pause");

    while (telaAtual != TELA_SAIR) {
        limparTela();

        switch (telaAtual) {
            case TELA_MENU_PRINCIPAL:
                exibirMenuPrincipal(&usuarioLogado);break;
            case TELA_CADASTRO_EMPRESA:
                cadastrarEmpresa(&empresas, &numEmpresas, &telaAtual);break;
            case TELA_GERENCIAR_EMPRESAS:
                gerenciarEmpresas(empresas, numEmpresas, &telaAtual);break;
            case TELA_RELATORIO:
                exibirRelatorio(empresas, numEmpresas, &telaAtual);break;
            case TELA_CONSULTA_EMPRESA:
                {
                    char cnpjConsulta[15];
                    printf("Digite o CNPJ para consulta: ");
                    scanf(" %[^\n]", cnpjConsulta);

                    int empresaEncontrada = 0;
                     int indiceEmpresa = -1;
                    for (int i = 0; i < numEmpresas; i++) {
                        if (strcmp(empresas[i].cnpj, cnpjConsulta) == 0) {
                            printf(ANSI_GREEN"\nConsulta bem-sucedida!\nAbrindo Gerenciamento para %s\n" ANSI_RESET, empresas[i].nome_fantasia);
                            empresaEncontrada = 1;
                            indiceEmpresa = i;break;}
                    }

                    if (!empresaEncontrada) {
                        printf(ANSI_RED"\nNenhuma empresa encontrada para o CNPJ informado.\n"ANSI_RESET);
                    }else {
                       usuarioLogado.empresaSelecionada = indiceEmpresa;
                       opGerenciamento(empresas, numEmpresas, indiceEmpresa, &telaAtual);}

                    printf("\nPressione Enter para continuar...");
                    while (getchar() != '\n');
                    telaAtual = TELA_MENU_PRINCIPAL;                }                break;
            case TELA_NOVA_OPCAO:
                printf("Nova op��o escolhida!\n");
                // L�gica da nova op��o aqui
                // Altera a tela para o menu principal ap�s a nova op��o
                telaAtual = TELA_MENU_PRINCIPAL;break;}

        if (telaAtual == TELA_MENU_PRINCIPAL) {
            int opcao;
            printf("Op��o escolhida: ");
            scanf("%d", &opcao);

            while (getchar() != '\n');
            switch (opcao) {
                case 1:
                    telaAtual = TELA_CADASTRO_EMPRESA;break;
                case 2:
                    telaAtual = TELA_GERENCIAR_EMPRESAS;break;
                case 3:
                    telaAtual = TELA_RELATORIO;break;
                case 4:
                    telaAtual = TELA_CONSULTA_EMPRESA;break;
                case 5:
                    telaAtual = TELA_SAIR;break;
                default:
                    printf(ANSI_RED"Op��o inv�lida. Tente novamente.\n"ANSI_RESET);break;
            }        }    }

    free(empresas);
    printf("\n----At� Logo----\n");
    return 0;
}
struct Usuario fazerLogin(const struct Usuario *usuarios, int numUsuarios) {
    struct Usuario usuarioLogado;
    char loginInformado[20];
    char senhaInformada[20];
    do {
         limparTela();
        printf("\n\t------------------------------");
        printf(ANSI_GREEN "\n\t\tREALIZAR LOGIN" ANSI_RESET);
        printf("\n\t------------------------------\n");

        printf("Login: ");
        scanf(" %[^\n]", loginInformado);

        while (getchar() != '\n');
        printf("Senha: ");
        scanf(" %[^\n]", senhaInformada);

        int usuarioValido = 0;
        for (int i = 0; i < numUsuarios; i++) {
            if (strcmp(usuarios[i].login, loginInformado) == 0 &&
                strcmp(usuarios[i].senha, senhaInformada) == 0) {
                usuarioLogado = usuarios[i];
                usuarioValido = 1;break;}
        }

        if (!usuarioValido) {
            printf(ANSI_RED"\n[--Usu�rio ou senha inv�lidos. Tente novamente--]\n"ANSI_RESET);system("pause");
            strcpy(usuarioLogado.login, "");        }
    } while (strcmp(usuarioLogado.login, "") == 0);

    return usuarioLogado;
}

void exibirMenuPrincipal(const struct Usuario *usuarioLogado){
    printf("\n\t-------------SISTEMA GESA------------\n");
    printf("\tGerenciador de Solu��es Ambientais\n");
    printf("\tSeja Bem-vindo!" ANSI_GREEN " - %s" ANSI_RESET, usuarioLogado->nome_completo);
    printf("\n\t-------------------------------------\n");

    printf("\nEscolha uma Op��o:\n");
    printf("[1] Cadastrar nova empresa.\n");
    printf("[2] Gerenciar empresas.\n");
    printf("[3] Relat�rio.\n");
    printf("[4] Consultar empresa por CNPJ.\n");
    printf("[5] Sair.\n");
}

void cadastrarEmpresa(struct Empresa **empresas, int *numEmpresas, int *telaAtual) {
    struct Empresa novaEmpresa;

    printf("\n\t-------------------------------------");
    printf("\n\t\tCADASTRO DE EMPRESA");
    printf("\n\t-------------------------------------\n");

    printf("Raz�o Social: ");
    scanf(" %[^\n]", novaEmpresa.razao_social);

    printf("Nome Fantasia: ");
    scanf(" %[^\n]", novaEmpresa.nome_fantasia);

    printf("CNPJ: ");
    scanf(" %[^\n]", novaEmpresa.cnpj);

    printf("Data de Abertura: ");
    scanf(" %[^\n]", novaEmpresa.data_abertura);

    printf("Telefone: ");
    scanf(" %[^\n]", novaEmpresa.telefone);

    printf("Respons�vel: ");
    scanf(" %[^\n]", novaEmpresa.responsavel);

    printf("E-mail: ");
    scanf(" %[^\n]", novaEmpresa.email);

    printf("Endere�o: ");
    scanf(" %[^\n]", novaEmpresa.endereco);

    printf("Bairro: ");
    scanf(" %[^\n]", novaEmpresa.bairro);

    printf("Cidade: ");
    scanf(" %[^\n]", novaEmpresa.cidade);

    printf("Estado: ");
    scanf(" %[^\n]", novaEmpresa.estado);

    printf("CEP: ");
    scanf(" %[^\n]", novaEmpresa.cep);

    struct Empresa *temp = realloc(*empresas, (*numEmpresas + 1) * sizeof(struct Empresa));

    if (temp == NULL) {
        printf(ANSI_RED"Erro ao alocar mem�ria.\n"ANSI_RESET);
        system("pause");
        return;
    }

    *empresas = temp;

    (*empresas)[*numEmpresas] = novaEmpresa;
    (*numEmpresas)++;

    printf(ANSI_GREEN"\nEmpresa cadastrada com sucesso!\n"ANSI_RESET);
    system("pause");    limparTela();
    *telaAtual = TELA_MENU_PRINCIPAL;

}

void gerenciarEmpresas(struct Empresa *empresas, int numEmpresas, int *telaAtual) {
    if (numEmpresas == 0) {
        printf(ANSI_RED"\n[--Nenhuma empresa cadastrada--]\n"ANSI_RESET);
        system("pause"); *telaAtual = TELA_MENU_PRINCIPAL;
    }

    printf("\n\t-----------------------------------");
    printf("\n\t\tGERENCIAR EMPRESAS");
    printf("\n\t-----------------------------------\n");

    printf("Escolha uma op��o:\n");
    printf("[1] Consultar empresa\n");
    printf("[2] Voltar ao menu principal.\n");

    int opcao;
    printf("Op��o escolhida: ");
    scanf("%d", &opcao);

    while (getchar() != '\n');

    switch (opcao) {
        case 1:
            *telaAtual = TELA_CONSULTA_EMPRESA;break;
        case 2:
            *telaAtual = TELA_MENU_PRINCIPAL;break;
        default:
            printf(ANSI_RED"Op��o inv�lida. Tente novamente.\n"ANSI_RESET); system("pause");break;
    }
}

void exibirRelatorio(const struct Empresa *empresas, int numEmpresas, int *telaAtual) {
    if (numEmpresas == 0) {
        printf(ANSI_RED"\n[--Nenhuma empresa cadastrada--]\n"ANSI_RESET);
        *telaAtual = TELA_MENU_PRINCIPAL;
        return;
    }

    printf("\n\t-----------------------------");
    printf("\n\t\tRELAT�RIO");
    printf("\n\t-----------------------------\n");

    for (int i = 0; i < numEmpresas; i++) {
        printf("Empresa %d:\n", i + 1);
        printf("Nome Fantasia: %s\n", empresas[i].nome_fantasia);
        printf("CNPJ: %s\n", empresas[i].cnpj);
        printf("--------------------------------\n");
    }

    printf(ANSI_GREEN"\n--Relat�rio exibido com sucesso!--\n"ANSI_RESET);
    *telaAtual = TELA_MENU_PRINCIPAL;
}

void opGerenciamento(const struct Empresa *empresas, int numEmpresas, int empresaSelecionada, int *telaAtual) {
    printf("\n\t-------------------------------------");
    printf("\n\t\tGERENCIAMENTO - %s", empresas[empresaSelecionada].nome_fantasia);
    printf("\n\t-------------------------------------\n");

    printf("Escolha uma op��o:\n");
    printf("[1] Visualizar dados cadastrais.\n");
    printf("[2] Visualizar Indicadores.\n");
    printf("[3] Gerar Relat�rios.\n");
    printf("[4] Excluir cadastro.\n");
    printf("[5] Voltar ao menu anterior.\n");
    printf("[6] Sair.\n");

    int opcao;
    printf("Op��o escolhida: ");
    scanf("%d", &opcao);

    while (getchar() != '\n');
    switch (opcao) {
        case 1:
            //OPCAO DESNECESSARIO - CONVERSAR COM RESTO DO GRUPO
            break;
        case 2:
            visualizarIndicadores(&empresas[empresaSelecionada]);
            break;
        case 3:
           // JA TEM OUTRA TELA PRA ISSO
            break;
        case 4:
            excluirCadastro(empresas, &numEmpresas);
            printf(ANSI_GREEN"\nCadastro exclu�do com sucesso!\n"ANSI_RESET);
            pausarExecucao();
            *telaAtual = TELA_MENU_PRINCIPAL;break;
        case 5:
            *telaAtual = TELA_MENU_PRINCIPAL;break;
        case 6:
            *telaAtual = TELA_SAIR;break;
        default:
            printf(ANSI_RED"Op��o inv�lida. Tente novamente.\n"ANSI_RESET);break;
    }
}

void excluirCadastro(struct Empresa **empresas, int *numEmpresas) {
    char cnpjExclusao[15];
    printf("\nDigite o CNPJ da empresa que deseja excluir: ");
    scanf(" %[^\n]", cnpjExclusao);

    int indiceExclusao = -1;
    for (int i = 0; i < *numEmpresas; i++) {
        if (strcmp((*empresas)[i].cnpj, cnpjExclusao) == 0) {
            indiceExclusao = i;            break;        }
    }

    if (indiceExclusao != -1) {
        for (int i = indiceExclusao; i < *numEmpresas - 1; i++) {
            (*empresas)[i] = (*empresas)[i + 1];        }

        struct Empresa *temp = realloc(*empresas, (*numEmpresas - 1) * sizeof(struct Empresa));

        if (temp != NULL) {
            *empresas = temp;
            (*numEmpresas)--;
        } else {            printf(ANSI_RED"Erro ao liberar mem�ria.\n"ANSI_RESET);system("pause");        }
    } else {        printf(ANSI_RED"Empresa com o CNPJ fornecido n�o encontrada.\n"ANSI_RESET);    }
}

void limparTela() {
    system("cls");
}

void pausarExecucao() {
    printf(ANSI_GREEN"[---Pressione Enter para continuar---]"ANSI_RESET);
    while (getchar() != '\n');
}

void visualizarIndicadores(const struct Empresa *empresa) {
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    char dataAtual[20];
    strftime(dataAtual, sizeof(dataAtual), "%d/%m/%Y", &tm_info);

    double residosAtual = (rand() % 100000) + 50000.0;
    double residosAnterior = (rand() % 100000) + 20000.0;
double custoDaOperacao = (rand() % 556000) + 25600.0;

    printf(ANSI_GREEN"\n INDICADORES ATUAIS"ANSI_RESET);
    printf("\nNo dia %s a empresa %s tratou de %.2f toneladas,\n ultrapassando a sua marca anterior de %.2f.\n",
           dataAtual, empresa->nome_fantasia, residosAtual, residosAnterior);
    printf(ANSI_GREEN"\n Custo da Opera��o: R$ %.2f"ANSI_RESET, custoDaOperacao);
}
