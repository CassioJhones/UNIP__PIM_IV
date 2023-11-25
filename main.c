#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Estrutura do usuário
struct Usuario {
    char nome_completo[100];
    char login[20];
    char senha[20];
};

// Estrutura da Empresa
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
};

// Enumeração para telas
enum Telas {
    TELA_MENU_PRINCIPAL,
    TELA_CADASTRO_EMPRESA,
    TELA_GERENCIAR_EMPRESAS,
    TELA_RELATORIO,
    TELA_CONSULTA_EMPRESA,
    TELA_SAIR,
    TELA_NOVA_OPCAO
};

// Protótipo das funções
void exibirMenuPrincipal();
void cadastrarEmpresa(struct Empresa **empresas, int *numEmpresas, int *telaAtual);
void gerenciarEmpresas(struct Empresa *empresas, int numEmpresas, int *telaAtual);
void exibirRelatorio(const struct Empresa *empresas, int numEmpresas, int *telaAtual);
void limparTela();
struct Usuario fazerLogin(const struct Usuario *usuarios, int numUsuarios);
int validarCNPJ(const char* cnpj);

int main() {
    setlocale(LC_ALL, "Portuguese");

    // Exemplo com dois usuários registrados
    struct Usuario usuarios[3] = {
        {"John Doe", "john", "senha123"},
        {"Jane Doe", "jane", "outrasenha"},
        {"Joao", "joao", "1234"}  // Novo usuário
    };

    struct Empresa *empresas = NULL;
    int numEmpresas = 0;
    int telaAtual = TELA_MENU_PRINCIPAL;

    // Simula o login
    struct Usuario usuarioLogado = fazerLogin(usuarios, 3);

    if (strcmp(usuarioLogado.login, "") == 0) {
        printf("Usuário não encontrado. Encerrando o programa.\n");
        return 0;
    }

    printf("Login bem-sucedido! Bem-vindo, %s.\n", usuarioLogado.nome_completo);

    while (telaAtual != TELA_SAIR) {
        limparTela();  // Limpa a tela antes de exibir a próxima tela

        switch (telaAtual) {
            case TELA_MENU_PRINCIPAL:
                exibirMenuPrincipal();
                break;
            case TELA_CADASTRO_EMPRESA:
                cadastrarEmpresa(&empresas, &numEmpresas, &telaAtual);
                break;
            case TELA_GERENCIAR_EMPRESAS:
                gerenciarEmpresas(empresas, numEmpresas, &telaAtual);
                break;
            case TELA_RELATORIO:
                exibirRelatorio(empresas, numEmpresas, &telaAtual);
                break;
            case TELA_CONSULTA_EMPRESA:
                {
                    char cnpjConsulta[15];
                    printf("Digite o CNPJ para consulta: ");
                    scanf(" %[^\n]", cnpjConsulta);

                    // Implemente a lógica para encontrar a empresa pelo CNPJ
                    int empresaEncontrada = 0;
                    for (int i = 0; i < numEmpresas; i++) {
                        if (strcmp(empresas[i].cnpj, cnpjConsulta) == 0) {
                            printf("\nConsulta bem-sucedida!\n");
                            printf("Nome da empresa: %s\n", empresas[i].nome_fantasia);
                            empresaEncontrada = 1;
                            break;
                        }
                    }

                    if (!empresaEncontrada) {
                        printf("\nNenhuma empresa encontrada para o CNPJ informado.\n");
                    }

                    // Aguarde uma ação do usuário antes de voltar ao menu
                    printf("\nPressione Enter para continuar...");
                    while (getchar() != '\n');

                    // Retorna para o menu principal após a consulta
                    telaAtual = TELA_MENU_PRINCIPAL;
                }
                break;
            case TELA_NOVA_OPCAO:
                printf("Nova opção escolhida!\n");
                // Lógica da nova opção aqui
                // Altera a tela para o menu principal após a nova opção
                telaAtual = TELA_MENU_PRINCIPAL;
                break;
        }

        // Se não for uma transição de tela após uma ação específica, recebe a opção do usuário
        if (telaAtual == TELA_MENU_PRINCIPAL) {
            int opcao;
            printf("Opção escolhida: ");
            scanf("%d", &opcao);

            // Limpa o buffer do teclado
            while (getchar() != '\n');

            // Atualiza a tela correspondente com base na opção
            switch (opcao) {
                case 1:
                    telaAtual = TELA_CADASTRO_EMPRESA;
                    break;
                case 2:
                    telaAtual = TELA_GERENCIAR_EMPRESAS;
                    break;
                case 3:
                    telaAtual = TELA_RELATORIO;
                    break;
                case 4:
                    telaAtual = TELA_CONSULTA_EMPRESA;
                    break;
                case 5:
                    telaAtual = TELA_SAIR;
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }
        }
    }

    // Libera a memória alocada para empresas
    free(empresas);

    printf("----Até Logo----\n");

    return 0;
}

void limparTela() {
    system("cls");  // Limpa a tela no Windows
    // Use "clear" no lugar de "cls" para sistemas Unix/Linux
}

void exibirMenuPrincipal() {
    printf("\nSISTEMA GESA\n");
    printf("Gerenciador de Soluções Ambientais\n");
    printf("Seja Bem-vindo!\n");
    printf("-------------------------------------\n");
    printf("Escolha uma Opção:\n");
    printf("[1] Cadastrar nova empresa.\n");
    printf("[2] Gerenciar empresas.\n");
    printf("[3] Relatório.\n");
    printf("[4] Consultar empresa por CNPJ.\n");
    printf("[5] Sair.\n");
}

void cadastrarEmpresa(struct Empresa **empresas, int *numEmpresas, int *telaAtual) {
    struct Empresa novaEmpresa;

    printf("\n\t-------------------------------------");
    printf("\n\t\tCADASTRO DE EMPRESA");
    printf("\n\t-------------------------------------\n");

    printf("Razão Social: ");
    scanf(" %[^\n]", novaEmpresa.razao_social);

    printf("Nome Fantasia: ");
    scanf(" %[^\n]", novaEmpresa.nome_fantasia);

    printf("CNPJ: ");
    scanf(" %[^\n]", novaEmpresa.cnpj);

    printf("Data de Abertura: ");
    scanf(" %[^\n]", novaEmpresa.data_abertura);

    printf("Telefone: ");
    scanf(" %[^\n]", novaEmpresa.telefone);

    printf("Responsável: ");
    scanf(" %[^\n]", novaEmpresa.responsavel);

    printf("E-mail: ");
    scanf(" %[^\n]", novaEmpresa.email);

    printf("Endereço: ");
    scanf(" %[^\n]", novaEmpresa.endereco);

    printf("Bairro: ");
    scanf(" %[^\n]", novaEmpresa.bairro);

    printf("Cidade: ");
    scanf(" %[^\n]", novaEmpresa.cidade);

    printf("Estado: ");
    scanf(" %[^\n]", novaEmpresa.estado);

    printf("CEP: ");
    scanf(" %[^\n]", novaEmpresa.cep);

    // Alocar mais espaço para o vetor de empresas
    *empresas = realloc(*empresas, (*numEmpresas + 1) * sizeof(struct Empresa));

    if (*empresas == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    // Adicionar a nova empresa ao vetor
    (*empresas)[*numEmpresas] = novaEmpresa;
    (*numEmpresas)++;

    printf("\nEmpresa cadastrada com sucesso!\n");

    // Mantém na tela de cadastro após o cadastro
    // Altera a tela para o menu principal após o cadastro
    *telaAtual = TELA_MENU_PRINCIPAL;
}

void gerenciarEmpresas(struct Empresa *empresas, int numEmpresas, int *telaAtual) {
    if (numEmpresas == 0) {
        printf("Nenhuma empresa cadastrada.\n");
        return;
    }

    printf("\n\t-------------------------------------");
    printf("\n\t\tGERENCIAR EMPRESAS");
    printf("\n\t-------------------------------------\n");

    // Implemente aqui o código para gerenciar as empresas
    // Pode ser exibindo a lista de empresas ou realizando outras ações

    printf("Escolha uma opção:\n");
    printf("[1] Consultar empresa por CNPJ.\n");
    printf("[2] Voltar ao menu principal.\n");

    int opcao;
    printf("Opção escolhida: ");
    scanf("%d", &opcao);

    // Limpa o buffer do teclado
    while (getchar() != '\n');

    switch (opcao) {
        case 1:
            *telaAtual = TELA_CONSULTA_EMPRESA;
            break;
        case 2:
            *telaAtual = TELA_MENU_PRINCIPAL;
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
    }
}

void exibirRelatorio(const struct Empresa *empresas, int numEmpresas, int *telaAtual) {
    if (numEmpresas == 0) {
        printf("Nenhuma empresa cadastrada.\n");
        return;
    }

    printf("\n\t-------------------------------------");
    printf("\n\t\tRELATÓRIO");
    printf("\n\t-------------------------------------\n");

    // Implemente aqui o código para exibir o relatório
    // Pode ser mostrando informações sobre as empresas cadastradas
    printf("Relatório exibido com sucesso!\n");

    // Altera a tela para o menu principal após exibir o relatório
    *telaAtual = TELA_MENU_PRINCIPAL;
}

struct Usuario fazerLogin(const struct Usuario *usuarios, int numUsuarios) {
    struct Usuario usuarioLogado;
    char loginInformado[20];
    char senhaInformada[20];

    printf("\n\t-------------------------------------");
    printf("\n\t\tREALIZAR LOGIN");
    printf("\n\t-------------------------------------\n");

    printf("Login: ");
    scanf(" %[^\n]", loginInformado);

    // Limpa o buffer do teclado
    while (getchar() != '\n');

    printf("Senha: ");
    scanf(" %[^\n]", senhaInformada);

    int usuarioValido = 0;
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].login, loginInformado) == 0 &&
            strcmp(usuarios[i].senha, senhaInformada) == 0) {
                        printf("Login bem-sucedido! Bem-vindo, %s.\n", usuarios[i].nome_completo);
            usuarioLogado = usuarios[i];
            usuarioValido = 1;
            break;
        }
    }

    if (!usuarioValido) {
        printf("Usuário ou senha inválidos.\n");
        strcpy(usuarioLogado.login, "");  // Define um login vazio para indicar que o login falhou
    }

    return usuarioLogado;
}

int validarCNPJ(const char* cnpj) {
    // Implemente a lógica de validação do CNPJ
    // Por enquanto, consideraremos válido se o CNPJ for "12345678901234"
    const char* cnpjFixo = "12345678901234";
    return strcmp(cnpj, cnpjFixo) == 0;
}

void novaOpcao(const struct Empresa *empresas, int numEmpresas, int *telaAtual) {
    printf("\n\t-------------------------------------");
    printf("\n\t\tNOVA OPÇÃO");
    printf("\n\t-------------------------------------\n");

    printf("Escolha uma opção:\n");
    printf("[1] Visualizar dados cadastrais.\n");
    printf("[2] Gerenciar Indicadores.\n");
    printf("[3] Gerar Relatórios.\n");
    printf("[4] Excluir cadastro.\n");
    printf("[5] Voltar ao menu anterior.\n");
    printf("[6] Sair.\n");

    int opcao;
    printf("Opção escolhida: ");
    scanf("%d", &opcao);

    // Limpa o buffer do teclado
    while (getchar() != '\n');

    switch (opcao) {
        case 1:
            // Implemente a lógica para visualizar dados cadastrais
            break;
        case 2:
            // Implemente a lógica para gerenciar indicadores
            break;
        case 3:
            // Implemente a lógica para gerar relatórios
            break;
        case 4:
            // Implemente a lógica para excluir cadastro
            break;
        case 5:
            *telaAtual = TELA_GERENCIAR_EMPRESAS;
            break;
        case 6:
            *telaAtual = TELA_SAIR;
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
    }
}

