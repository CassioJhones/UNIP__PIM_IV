#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
void MenuInicial();
void TelaCadastroFuncionario();
void TelaDoUsuario();
void TelaLogin();
void NovaSenha();
void TelaCadastroEmpresa();
void Consulta();
void CadastroEmpresa();

char admin[20];
char SenhaAdmin[20];
char UserName[20];
char UserSenha[20];
int opcao;

int main (void)
{
    setlocale(LC_ALL,"Portuguese"); // para os acentos da lingua portuguesa aparecer corretamente
    MenuInicial();
    return 0;
}

void MenuInicial()
{
    system("cls");

    printf("\t-------------------------------------");
    printf("\n\t\t   SISTEMA GESA");
    printf("\n\tGerenciador de Soluções Ambientais");
    printf("\n\t\t   Seja Bem-Vindo");
    printf("\n\t-------------------------------------\n");

    printf("\nEscolha uma opção:\n");
    printf("\n[1] Realizar Login");
    printf("\n[2] Não tenho cadastro");
    printf("\n[3] Esqueci minha senha");
    printf("\n[4] Fechar Programa\n");

    printf("Opcao:  ");
    scanf("%d",&opcao);
    switch (opcao)
    {
    case 1:
        TelaLogin();
        break;
    case 2:
        TelaCadastroFuncionario();
        break;
    case 3:
        NovaSenha();
        break;
    case 4:
        printf("----Até Logo----");
        break;
    default:
        printf("\n[--Opção Inválida--]\n");
        system("pause");
        MenuInicial();
        break;
    }
}

void TelaCadastroFuncionario()
{
    char ch;
    char UserMail[20];

    system("cls");
    printf("\t-------------------------------------");
    printf("\n\t\tCADASTRO DE FUNCIONARIO");
    printf("\n\t-------------------------------------\n");

    printf("\nPor favor, preencha os seguintes dados:");
    printf("\nNome Completo:");
    scanf(" %20[^\n]", UserName);
    printf("\nCPF:");

    printf("\nE-Mail:");
    scanf("%s",UserMail);

    printf("\n \n Cadastro Realizado com Sucesso!");
    printf("\nSeu usuario: %s ",UserName);
    printf("\nSua Senha: %s \n",UserSenha);
    printf("\nRetorne a tela inicial usando 'espaço'");

    while (1)
    {
        ch = _getch();

        if (ch == ' ')
        {
            MenuInicial();
            break;
        }
    }

}

void TelaLogin()
{
    char ch;
    system("cls");
    printf("\t---------------------------");
    printf("\n\t\tFAZER LOGIN");
    printf("\n\t---------------------------\n");

    printf("\nUsuario: ");
    scanf("%s",admin);
    printf("Senha: ");
    scanf("%s",SenhaAdmin);

    if (strcmp(admin, "0") == 0 && strcmp(SenhaAdmin, "0") == 0)
    {
        printf("\n[---- Acesso permitido!----]\n");
        system("pause");
        TelaDoUsuario();
    }
    else
    {
        printf("\n[--- Acesso Negado ---]\n");
        printf("\n[0] Menu Inicial");
        printf("\n[1] Tentar Novamente\n");
        while (1)
        {
            ch = _getch();
            if (ch == '0')
            {
                MenuInicial();
                break;
            }
            else if(ch == '1')
            {
                TelaLogin();
            }
        }
    }
}

void NovaSenha()
{
    char ch;
    system("cls");
    printf("\t---------------------------");
    printf("\n\t\tNOVA SENHA");
    printf("\n\t---------------------------\n");

    printf("\nDigite a nova senha:");
    scanf("%s", UserSenha);

    printf("\n[--- Senha Criada ---]\n");
    printf("\n[0] Menu Inicial");
    printf("\n[1] Rep\n");
    while (1)
    {
        ch = _getch();
        if (ch == '0')
        {
            MenuInicial();
            break;
        }
    }
}

void Consulta() {

}

void CadastroEmpresa()
{

    system("cls");
    printf("\t-------------------------------------");
    printf("\n\t\tCADASTRO DE EMPRESA");
    printf("\n\t-------------------------------------\n");

    printf("\nPor favor, preencha os seguintes dados:\n");
    printf("\nRazão Social:");
    printf("\nNome Fantasia:");
    scanf("%s",UserSenha);
    printf("\nCNPJ:");
    printf("\nData de Abertura:");
    printf("\nResponsavel:");
    printf("\nTelefone:");
    printf("\nE-mail:");
    printf("\nEndereço:");
    printf("\nBairro:");
    printf("\nCidade:");
    printf("\nEstado:");
    printf("\nCEP:");
    printf("\nIndustria(Nicho):");

    printf("\nEmpresa Cadastrada com sucesso!\n \n");
    system("PAUSE");
    TelaDoUsuario();
}

void TelaDoUsuario()
{
    system("cls");
    printf("\t---------------------------");
    printf("\n\t\tMENU INICIAL");
    printf("\n\t---------------------------\n");

    printf("\nEscolha uma opção:\n");
    printf("\n[1] Cadastrar Nova Empresa");
    printf("\n[2] Gerenciar Empresas");
    printf("\n[3] Relatorios Globais");
    printf("\n[4] Sair\n");

    printf("Opcao:  ");
    scanf("%d",&opcao);
    switch (opcao)
    {
    case 1:
        CadastroEmpresa();
        break;
    case 2:
        printf("Opcao:  ");
        break;
    case 3:
        printf("Opcao:  ");
        break;
    case 4:
        MenuInicial();
        break;
    default:
        printf("\n[--Opção Inválida--]\n");
        system("pause");
        TelaDoUsuario();
        break;
    }
}
