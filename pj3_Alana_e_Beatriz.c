//======================================PROJETO 3 - PROGRAMACAO ESTRUTURADA=====================================
//=======================================ALANA GABRIELE E BEATRIZ RIBEIRO=======================================
//==============================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct end endereco;
struct end
{
    char cidade[30], bairro[30], rua[30];
    int numero, cep;
};

typedef struct lista dado;
struct lista
{
    endereco endereco, backup_endereco;
    int idUsuario, backup_idUsuario;
    char nome[100], sexo[20], email[100], backup_nome[100], backup_sexo[50], backup_email[100];
    float altura, backup_altura;
    bool vacina, backup_vacina;
    dado *prox;
} * primeiro;

dado *inicializar();
int menu();
dado *incluirUsuario(dado *primeiro);
int gerarId();
char *validarNome();
char *validarEmail();
char *validarSexo();
endereco validarEndereco();
float validarAltura();
bool validarVacina();
void imprimeUm(dado *temp);
dado *pesquisaUsuario(dado *primeiro);
dado *pesquisarEmail(dado *primeiro);
dado *editarUsuario(dado *primeiro);
dado *excluirUsuario(dado *primeiro);
void imprimir(dado *primeiro);
void backup(dado *primeiro);
void restaurar(dado *primeiro);

int main(void)
{
    int acao;
    char resposta[5];
    primeiro = inicializar();
    do
    {
        acao = menu();
        switch (acao)
        {
        case 1:
            do
            {
                primeiro = incluirUsuario(primeiro);
                printf("Deseja Incluir mais um usuario? (Responda com 'sim' ou 'nao'): ");
                fgets(resposta, 10, stdin);

            } while (strcmp(resposta, "sim\n") == 0);
            break;
        case 2:
            do
            {
                editarUsuario(primeiro);
                printf("Deseja editar mais um usuario? (Responda com 'sim' ou 'nao'): ");
                fgets(resposta, 10, stdin);
            } while (strcmp(resposta, "sim\n") == 0);
            break;
        case 3:
            do
            {
                primeiro = excluirUsuario(primeiro);
                printf("Deseja excluir mais um usuario? (Responda com 'sim' ou 'nao'): ");
                fgets(resposta, 10, stdin);
            } while (strcmp(resposta, "sim\n") == 0);
            break;

        case 4:
            imprimeUm(pesquisaUsuario(primeiro));
            break;
        case 5:
            imprimeUm(pesquisarEmail(primeiro));
            system("pause");
            break;
        case 6:
            imprimir(primeiro);
            break;
        case 7:
            backup(primeiro);
            break;
        case 8:
            restaurar(primeiro);
            break;
        default:
            printf("Insira um numero valido!\n");
            break;
        }
    } while (acao > 0);

    return 0;
}
dado *inicializar()
{
    return NULL;
}
int menu()
{
    int opcao;
    fflush(stdin);
    system("cls");
    system("color 0F");
    printf("==================MENU=====================\n");
    printf(" 1. Incluir um usuario por vez\n");
    printf(" 2. Editar um usuario\n");
    printf(" 3. Excluir um usuario\n");
    printf(" 4. Buscar um usuario pelo id\n");
    printf(" 5. Buscar um usuario pelo email\n");
    printf(" 6. Imprimir todos os usuarios cadastrados\n");
    printf(" 7. Fazer backup dos usuarios cadastrados\n");
    printf(" 8. Fazer restauracao dos  dados\n");
    printf("===========================================\n");
    printf(" Escolha um numero: ");
    scanf("%d", &opcao);
    fflush(stdin);
    system("cls");
    return opcao;
}
int gerarId()
{
    int id;
    srand(time(NULL));   //id nao se repetir
    id = rand() % 10000; //gerar numero randomico de 0 a 1000
    printf(" Seu Id de Usuario e %d \n", id);
    fflush(stdin);
    return id;
}
char *validarNome()
{
    char *nome = (char *)malloc(sizeof(char) * 100);
    do
    {
        printf(" Nome completo: ");
        fflush(stdin);
        fgets(nome, 100, stdin);
    } while (strlen(nome) < 1); //numero de caracteres do string
    return nome;
}
char *validarEmail()
{
    char *email = (char *)malloc(sizeof(char) * 100);
    do
    {
        printf(" Email: ");
        fflush(stdin);
        fgets(email, 100, stdin);
        if (strchr(email, '@') == NULL)
        {
            printf(" EMAIL INVALIDO!\nEmails devem conter '@'!\n");
        }
    } while (strchr(email, '@') == NULL); //verificar se existe @
    return email;
}
char *validarSexo()
{
    char *sexo = (char *)malloc(sizeof(char) * 20);

    do
    {
        printf(" Sexo - Feminino, masculino ou nao declarar: ");
        fflush(stdin);
        fgets(sexo, 20, stdin);
        if ((strcmp(sexo, "feminino\n") != 0) && (strcmp(sexo, "masculino\n") != 0) && (strcmp(sexo, "nao declarar\n") != 0))
            printf("Sexo invalido!\n");
    } while ((strcmp(sexo, "feminino\n") != 0) && (strcmp(sexo, "masculino\n") != 0) && (strcmp(sexo, "nao declarar\n") != 0));
    return sexo;
}
endereco validarEndereco()
{
    endereco endereco;
    printf(" Endereco:\n");
    do
    {
        printf("\tCidade:");
        fflush(stdin);
        fgets(endereco.cidade, 40, stdin);
    } while (strlen(endereco.cidade) < 1);

    do
    {
        printf("\tBairro: ");
        fflush(stdin);
        fgets(endereco.bairro, 40, stdin);
    } while (strlen(endereco.bairro) < 1);

    do
    {
        printf("\tRua: ");
        fflush(stdin);
        fgets(endereco.rua, 40, stdin);
    } while (strlen(endereco.rua) < 1);

    printf("\tNumero: ");
    fflush(stdin);
    scanf("%d", &endereco.numero);

    printf("\tCEP: ");
    fflush(stdin);
    scanf("%d", &endereco.cep);
    return endereco;
}
float validarAltura()
{
    float altura;
    do
    {
        printf(" Altura em metros: ");
        scanf("%f", &altura);
        if ((altura < 1) || (altura > 2))
            printf(" Altura invalida! Digite um valor entre 1 e 2.\n");
    } while ((altura < 1) || (altura > 2));
    return altura;
}
bool validarVacina()
{
    char validavacina[20];
    bool vacina;
    do
    {
        printf(" Voce ja foi vacinado(a)? responda com 'sim' ou 'nao': ");
        fflush(stdin);
        fgets(validavacina, 20, stdin);
        if (strcmp(validavacina, "sim\n") == 0)
        {
            vacina = true;
        }
        else if (strcmp(validavacina, "nao\n") == 0)
        {
            vacina = false;
        }
        else
        {
            printf(" Resposta Invalida, responda com 'sim' ou 'nao':");
        }

    } while ((strcmp(validavacina, "sim\n") != 0) && (strcmp(validavacina, "nao\n") != 0));
    return vacina;
}
dado *incluirUsuario(dado *primeiro)
{
    dado *novo = (dado *)malloc(sizeof(primeiro));
    system("cls");
    system("color 0F");
    printf("=======================INCLUIR USUARIO=======================\n");
    novo->idUsuario = gerarId();
    strcpy(novo->nome, validarNome());
    strcpy(novo->email, validarEmail());
    strcpy(novo->sexo, validarSexo());
    novo->altura = validarAltura();
    novo->endereco = validarEndereco();
    novo->vacina = validarVacina();
    fflush(stdin);
    novo->prox = primeiro;
    system("cls");
    system("color 0B");
    printf(" USUARIO INCLUIDO COM SUCESSO!\n\n");
    return novo;
    system("pause");
}
dado *pesquisaUsuario(dado *primeiro)
{
    dado *aux, *temp;
    int pesquisaID;
    printf(" Insira o Id do usuario: ");
    scanf("%d", &pesquisaID);

    for (aux = primeiro; aux != NULL; aux = aux->prox)
    {
        if (aux->idUsuario == pesquisaID)
        {
            temp = aux;
            break;
        }
        else
        {
            temp = NULL;
        }
        return temp;
    }
}
void imprimeUm(dado *temp)
{
    if (temp == NULL)
    {
        printf("USUARIO NAO ENCONTRADO!");
    }
    else
    {
        printf(" Id: %d\n", temp->idUsuario);
        printf(" Nome: %s", temp->nome);
        printf(" Email: %s", temp->email);
        printf(" Sexo: %s", temp->sexo);
        printf(" Endereco:\n");
        printf("\tCidade: %s", temp->endereco.cidade);
        printf("\tBairro: %s", temp->endereco.bairro);
        printf("\tRua: %s", temp->endereco.rua);
        printf("\tNumero: %d\n", temp->endereco.numero);
        printf("\tCep: %d\n", temp->endereco.cep);
        printf(" Altura: %.2f m\n", temp->altura);
        if (temp->vacina == true)
            printf(" Vacina: SIM (X) NAO( )\n\n");
        else
            printf(" Vacina: SIM ( ) NAO(X)\n\n");
        printf("===========================================================\n");
    }
}
void imprimir(dado *primeiro)
{
    dado *aux;
    printf("=======================IMPRIMIR USUARIOS=========================\n");
    for (aux = primeiro; aux != NULL; aux = aux->prox)
    {
        imprimeUm(aux);
    }
    system("pause");
}
dado *editarUsuario(dado *primeiro)
{
    dado *aux;
    int opcao;
    char resposta[10];

    printf("=======================EDITAR USUARIO=====================\n");
    do
    {
        system("color 0F");
        aux = pesquisaUsuario(primeiro);
        if (aux != NULL)
        {
            system("cls");
            printf("====================USUARIO ENCONTRADO===================\n");
            imprimeUm(aux);

            printf(" Gostaria de editar as informacoes desse usuario?(Responda com 'sim' ou 'nao'): ");
            fflush(stdin);
            fgets(resposta, 20, stdin);
            if (strcmp(resposta, "sim\n") == 0)
            {
                do
                {
                    system("cls");
                    system("color 0F");
                    printf("========================EDITAR USUARIO====================\n");
                    printf("\n Digite o numero correspondente a informacao que deseja editar:\n");
                    printf(" 1. Nome\n");
                    printf(" 2. Email\n");
                    printf("3. Sexo\n");
                    printf(" 4. Endereco\n");
                    printf(" 5. Altura\n");
                    printf(" 6. Vacina\n");
                    printf(" 7. Voltar ao Menu Anterior\n");
                    printf("==========================================================\n");
                    printf(" Digite: ");
                    scanf("%d", &opcao);
                    switch (opcao)
                    {
                    case 1:
                        strcpy(aux->nome, validarNome());
                        break;
                    case 2:
                        strcpy(aux->email, validarEmail());
                        break;
                    case 3:
                        strcpy(aux->sexo, validarSexo());
                        break;
                    case 4:
                        aux->endereco = validarEndereco();
                        break;
                    case 5:
                        aux->altura = validarAltura();
                        break;
                    case 6:
                        aux->vacina = validarVacina();
                        break;
                    case 7:
                        menu();
                        break;
                    default:
                        printf("Opcao Invalida!");
                        break;
                    }
                    system("cls");
                    system("color 0B");
                    printf(" DADO EDITADO COM SUCESSO!\n Deseja fazer mais alguma alteracao? (Responda com 'sim' ou 'nao') \n");
                    fflush(stdin);
                    fgets(resposta, 20, stdin);
                } while (strcmp(resposta, "sim\n") == 0);
            }
            else if (strcmp(resposta, "nao\n") == 0)
            {
                menu();
            }
            else
            {
                printf(" RESPOSTA INVALIDA!");
            }
        }
        else
        {
            system("cls");
            system("color 0C");
            printf(" USUARIO NAO ENCONTRADO!\nDeseja Pesquisar Novamente? Responda com 'sim' ou 'nao':");
            fflush(stdin);
            fgets(resposta, 20, stdin);
        }
    } while (strcmp(resposta, "sim\n") == 0);
}
dado *excluirUsuario(dado *primeiro)
{

    dado *ant = NULL, *aux = primeiro;
    dado *pesquisaID;
    char resposta[10];
    printf("======================EXLUIR USUARIO======================\n");
    pesquisaID = pesquisaUsuario(primeiro);
    if (pesquisaID != NULL)
    {
        imprimeUm(pesquisaID);
        printf(" Tem certeza que deseja excluir esse usuario? (Responda com 'sim' ou 'nao')\n");
        fflush(stdin);
        fgets(resposta, 10, stdin);
        if (strcmp(resposta, "sim\n") == 0)
        {
            if (aux == NULL)
            {
                return NULL;
            }

            while (aux != NULL)
            {
                if (aux->idUsuario == pesquisaID->idUsuario)
                    break;
                ant = aux;
                aux = aux->prox;
            }

            if (ant == NULL)
            {
                primeiro = aux->prox;
                free(aux);
            }
            else if (aux != NULL)
            {
                ant->prox = aux->prox;
                free(aux);
            }
            system("cls");
            system("color 0B");
            printf(" USUARIO EXCLUIDO COM SUCESSO!\n");
            system("pause");
            return primeiro;
        }
    }
    else
    {
        system("cls");
        printf("USUARIO NAO ENCONTRADO!");
    }
    system("pause");
}
dado *pesquisarEmail(dado *primeiro)
{
    char email[100];
    dado *temp, *aux;
    system("color 0F");
    printf(" Insira o Email do usuario: ");
    fflush(stdin);
    fgets(email, 100, stdin);
    for (aux = primeiro; aux != NULL; aux = aux->prox)
    {
        if (strcmp(aux->email, email) == 0)
        {
            temp = aux;
            break;
        }
        else
        {
            temp = NULL;
        }
    }
    return temp;
}
void backup(dado *primeiro)
{
    dado *aux;
    for (aux = primeiro; aux != NULL; aux = aux->prox)
    {
        aux->backup_idUsuario = aux->idUsuario;
        strcpy(aux->backup_nome, aux->nome);
        strcpy(aux->backup_email, aux->email);
        strcpy(aux->backup_email, aux->email);
        strcpy(aux->backup_sexo, aux->sexo);
        strcpy(aux->backup_endereco.cidade, aux->endereco.cidade);
        strcpy(aux->backup_endereco.bairro, aux->endereco.bairro);
        strcpy(aux->backup_endereco.rua, aux->endereco.rua);
        aux->backup_endereco.numero = aux->endereco.numero;
        aux->backup_endereco.cep = aux->endereco.cep;
        aux->backup_altura = aux->altura;
        aux->backup_vacina = aux->backup_vacina;
    }
    system("color 0B");
    printf("\n\n\n BACKUP REALIZADO COM SUCESSO!\n\n");
    system("pause");
}
void restaurar(dado *primeiro)
{
    dado *aux;
    char resposta[20];
    printf("=======================RESTAURAR  DADOS===========================\n");
    printf(" Tem certeza que deseja restaurar os  dados? (Responda com 'sim' ou 'nao')\n");
    fflush(stdin);
    fgets(resposta, 10, stdin);
    if (strcmp(resposta, "sim\n") == 0)
    {
        for (aux = primeiro; aux != NULL; aux = aux->prox)
        {
            aux->idUsuario = aux->backup_idUsuario;
            strcpy(aux->nome, aux->backup_nome);
            strcpy(aux->email, aux->backup_email);
            strcpy(aux->sexo, aux->backup_sexo);
            strcpy(aux->endereco.cidade, aux->backup_endereco.cidade);
            strcpy(aux->endereco.bairro, aux->backup_endereco.bairro);
            strcpy(aux->endereco.rua, aux->backup_endereco.rua);
            aux->endereco.numero = aux->backup_endereco.numero;
            aux->endereco.cep = aux->backup_endereco.cep;
            aux->altura = aux->backup_altura;
            aux->backup_vacina = aux->backup_vacina;
        }
        system("cls");
        system("color 0B");
        printf("\n\n\n DADOS RESTAURADOS COM SUCESSO!!\n\n");
        system("pause");
    }
}
