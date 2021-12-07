//======================================PROJETO 2 - PROGRAMACAO ESTRUTURADA=====================================
//=======================================ALANA GABRIELE E BEATRIZ RIBEIRO=======================================
//==============================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct
{
    char cidade[30], bairro[30], rua[30];
    int numero, cep;
} endereco;
typedef struct
{
    endereco endereco, backup_endereco;
    int idUsuario, backup_idUsuario;
    char nome[100], sexo[50], email[100], backup_nome[100], backup_sexo[50], backup_email[100];
    float altura, backup_altura;
    bool vacina, backup_vacina;
} dado[1000];


int menu();
void incluirUsuario(int indice, dado *usuario);
int gerarId(int indice, dado *usuario);
void validaNome(int indice, dado *usuario);
void validaEmail(int indice, dado *usuario);
void validarSexo(int indice, dado *usuario);
void validarEndereco(int indice, dado *usuario);
void validarAltura(int indice, dado *usuario);
void validarVacina(int indice, dado *usuario);
void imprimeUm(int indice, dado *usuario);
int pesquisaUsuario(int indice, dado *usuario);
void pesquisaBinaria(int indice, dado *usuario);
void pesquisaEmail(int indice, dado *usuario);
void editarUsuario(int indice, dado *usuario);
void excluirUsuario(int indice, dado *usuario);
void imprimir(int indice, dado *usuario);
void backup(int indice, dado *usuario);
void restaurar(int indice, dado *usuario);
int i;

int main(void)
{
    dado usuario;
    int indice = 0;
    char resposta [20];
    system("cls");
    do
    {
        switch (menu())
        {
        case 1:
        	do{		
            incluirUsuario(indice, &usuario);
            indice++;
            printf("Deseja Incluir mais um usuario? (Responda com 'sim' ou 'nao'): ");
            fgets(resposta,10,stdin);
        } while(stricmp(resposta,"sim\n")==0);
            break;
        case 2:
		do{		
            editarUsuario(indice, &usuario);
            printf("Deseja editar mais um usuario? (Responda com 'sim' ou 'nao'): ");
            fgets(resposta,10,stdin);
        } while(stricmp(resposta,"sim\n")==0);
		break;
        case 3:
           	do{		
            excluirUsuario(indice, &usuario);
            indice--;
            printf("Deseja excluir mais um usuario? (Responda com 'sim' ou 'nao'): ");
            fgets(resposta,10,stdin);
        } while(stricmp(resposta,"sim\n")==0);
        break;
        case 4:
            pesquisaBinaria(indice, &usuario);
            break;
        case 5:
            pesquisaEmail(indice, &usuario);
            break;
        case 6:
            imprimir(indice, &usuario);
            break;
        case 7:
            backup(indice, &usuario);
            break;
        case 8:
            restaurar(indice, &usuario);
            break;
        default:
            printf(" Insira um numero valido!\n");
            break;
        }
    } while (indice <= 1000);
    return 0;
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
    system("cls");
    return opcao;
}
int gerarId(int indice, dado *usuario)
{
    srand(time(NULL));                           //id nao se repetir
    usuario[indice]->idUsuario = rand() % 10000; //gerar numero randomico de 0 a 1000
    printf(" Seu Id de Usuario e %d \n", usuario[indice]->idUsuario);
    fflush(stdin);
}
void validarNome(int indice, dado *usuario)
{
    do
    {
        printf(" Nome completo: ");
        fflush(stdin);
        fgets(usuario[indice]->nome, 100, stdin);
    } while (strlen(usuario[indice]->nome) < 1); //numero de caracteres do string
}
void validarEmail(int indice, dado *usuario)
{
    do
    {
        printf(" Email: ");
        fgets(usuario[indice]->email, 100, stdin);
        fflush(stdin);
        if (strchr(usuario[indice]->email, '@') == NULL)
        {
            printf(" EMAIL INVALIDO!\nEmails devem conter '@'!\n");
        }
    } while (strchr(usuario[indice]->email, '@') == NULL); //verificar se existe @
}
void validarSexo(int indice, dado *usuario)
{
    do
    {
        printf(" Sexo - Feminino, masculino ou nao declarar: ");
        fflush(stdin);
        fgets(usuario[indice]->sexo, 50, stdin);
        if ((stricmp(usuario[indice]->sexo, "feminino\n") != 0) && (stricmp(usuario[indice]->sexo, "masculino\n") != 0) && (stricmp(usuario[indice]->sexo, "nao declarar\n") != 0))
            printf("Sexo invalido!\n");
    } while ((stricmp(usuario[indice]->sexo, "feminino\n") != 0) && (stricmp(usuario[indice]->sexo, "masculino\n") != 0) && (stricmp(usuario[indice]->sexo, "nao declarar\n") != 0));
}

void validarEndereco(int indice, dado *usuario)
{
    printf(" Endereco:\n");
    do
    {
        printf("    Cidade:");
        fflush(stdin);
        fgets(usuario[indice]->endereco.cidade, 40, stdin);
    } while (strlen(usuario[indice]->endereco.cidade) < 1);

    do
    {
        printf("    Bairro: ");
        fflush(stdin);
        fgets(usuario[indice]->endereco.bairro, 40, stdin);
    } while (strlen(usuario[indice]->endereco.bairro) < 1);

    do
    {
        printf("    Rua: ");
        fflush(stdin);
        fgets(usuario[indice]->endereco.rua, 40, stdin);
    } while (strlen(usuario[indice]->endereco.rua) < 1);

    printf("    Numero: ");
    fflush(stdin);
    scanf("%d", &usuario[indice]->endereco.numero);

    printf("    CEP: ");
    fflush(stdin);
    scanf("%d", &usuario[indice]->endereco.cep);
    
}
void validarAltura(int indice, dado *usuario)
{
    do
    {
        printf(" Altura em metros: ");
        scanf("%f", &usuario[indice]->altura);
        if ((usuario[indice]->altura < 1) || (usuario[indice]->altura > 2))
            printf(" Altura invalida! Digite um valor entre 1 e 2.\n");
    } while ((usuario[indice]->altura < 1) || (usuario[indice]->altura > 2));
}
void validarVacina(int indice, dado *usuario)
{
    char validavacina[20];
    do
    {
        printf(" Voce ja foi vacinado(a)? responda com 'sim' ou 'nao': ");
        fflush(stdin);
        fgets(validavacina, 20, stdin);
        if (stricmp(validavacina, "sim\n") == 0)
        {
            usuario[indice]->vacina = true;
        }
        else if (stricmp(validavacina, "sim\n") == 0)
        {
            usuario[indice]->vacina = false;
        }
        else
        {
            printf(" Resposta Invalida, responda com 'sim' ou 'nao':");
        }

    } while ((stricmp(validavacina, "sim\n") != 0) && (stricmp(validavacina, "nao\n") != 0));
}
void incluirUsuario(int indice, dado *usuario)
{
   
    system("cls");
    printf("=======================INCLUIR USUARIO=======================\n");
    gerarId(indice,usuario);
    validarNome(indice, usuario);
    validarEmail(indice, usuario);
    validarEndereco(indice,usuario);
    validarSexo(indice, usuario);
    validarAltura(indice, usuario);
    validarVacina(indice, usuario);
    system("cls");
    system("color 0B");
    printf(" USUARIO INCLUIDO COM SUCESSO!\n\n");
 system("pause");}
int pesquisaUsuario(int indice, dado *usuario)
{
    int pesquisaID, n, i;
    printf(" Insira o Id do usuario: ");
    scanf("%d", &pesquisaID);

    for (i = 0; i <= indice; i++)
    {
        if (usuario[i]->idUsuario == pesquisaID)
        {
            n = i;
            break;
        }
        else
        {
            n = -1;
        }
    }
    return n;
}
void imprimeUm(int indice, dado *usuario)
{

    printf(" Id: %d\n", usuario[indice]->idUsuario);
    printf(" Nome: %s", usuario[indice]->nome);
    printf(" Email: %s", usuario[indice]->email);
    printf(" Sexo: %s", usuario[indice]->sexo);
    printf(" Endereco:\n");
    printf("    Cidade: %s", usuario[indice]->endereco.cidade);
    printf("    Bairro: %s", usuario[indice]->endereco.bairro);
    printf("    Rua: %s", usuario[indice]->endereco.rua);
    printf("    Numero: %d\n", usuario[indice]->endereco.numero);
    printf("    Cep: %d\n", usuario[indice]->endereco.cep);
    printf(" Altura: %.2f m\n", usuario[indice]->altura);
    if (usuario[indice]->vacina == true)
        printf(" Vacina: SIM (X) NAO( )\n\n");
    else
        printf(" Vacina: SIM ( ) NAO(X)\n\n");
    printf("===========================================================\n");
}

void editarUsuario(int indice, dado *usuario)
{
    int opcao, n;
    char resposta[10];
    printf("=======================EDITAR USUARIO=====================\n");

    do
    {
        system("color 0F");
        n = pesquisaUsuario(indice, usuario);
        if (n >= 0)
        {
            system("cls");
            printf("====================USUARIO ENCONTRADO===================\n");
            imprimeUm(n, usuario);
            
            printf(" Gostaria de editar as informacoes desse usuario?(Responda com 'sim' ou 'nao': ");
            fflush(stdin);
            fgets(resposta, 20, stdin);
            if(stricmp(resposta,"sim\n")==0){
            do{
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
                validarNome(n, usuario);
                break;
            case 2:
                validarEmail(n, usuario);
                break;
            case 3:
                validarSexo(n, usuario);
                break;
            case 4:
                validarEndereco(n, usuario);
                break;
            case 5:
                validarAltura(n, usuario);
                break;
            case 6:
                validarVacina(n, usuario);
                break;
            case 7:
                menu();
                break;
            default:
                break;
            }
            system("cls");
            system("color 0B");
            printf(" DADO EDITADO COM SUCESSO!\n Deseja fazer mais alguma alteracao? (Responda com 'sim' ou 'nao') \n");
            fflush(stdin);
            fgets(resposta, 20, stdin);
    }while(stricmp(resposta,"sim\n")==0);
       }else if(stricmp(resposta,"nao\n")==0)
       {
           menu();
           }else{
               printf(" RESPOSTA INVALIDA!");
           } }
        else
        {
            system("cls");
            system("color 0C");
            printf(" USUARIO NAO ENCONTRADO!\nDeseja Pesquisar Novamente? Responda com 'sim' ou 'nao':");
            fflush(stdin);
            fgets(resposta, 20, stdin);
        }
    } while (stricmp(resposta, "sim\n") == 0);
}
void excluirUsuario(int indice, dado *usuario)
{
    int n;
    char resposta[10];
    printf("======================EXLUIR USUARIO======================\n");
    n = pesquisaUsuario(indice, usuario);
    if (n >= 0)
    {
        imprimeUm(n, usuario);
        printf("==========================================================\n");
        printf(" Tem certeza que deseja excluir esse usuario? (Responda com 'sim' ou 'nao')\n");
        fflush(stdin);
        fgets(resposta, 10, stdin);
        if (stricmp(resposta, "sim\n") == 0)
        {
            for (i = n + 1; i <= indice; i++)
            {
                usuario[n]->idUsuario = usuario[n + 1]->idUsuario;
                strcpy(usuario[n]->nome, usuario[n + 1]->nome);
                strcpy(usuario[n]->email, usuario[n + 1]->nome);
                strcpy(usuario[n]->sexo, usuario[n + 1]->sexo);
                strcpy(usuario[n]->endereco.cidade, usuario[n+1]->endereco.cidade);
                strcpy(usuario[n]->endereco.bairro, usuario[n+1]->endereco.bairro);
                strcpy(usuario[n]->endereco.rua, usuario[n + 1]->endereco.rua);
                usuario[n]->endereco.numero = usuario[n + 1]->endereco.numero;
                usuario[n]->endereco.cep = usuario[n + 1]->endereco.cep;
                usuario[n]->altura = usuario[n + 1]->altura;
                usuario[n]->vacina = usuario[n + 1]->vacina;
                system("cls");
                system("color 0B");
                printf(" USUARIO EXCLUIDO COM SUCESSO!\n");
                n++;
                system("pause");
            }
        }
        else
        {
            menu();
        }
    }
}
void pesquisaBinaria(int indice, dado *usuario)
{
    int x, n, pesquisaID, maior = 0, aux_cep, aux_num;
    char aux_nome[100], aux_sexo[50], aux_endereco[100], aux_email[50], aux_cidade[50], aux_bairro[50], aux_rua[50];
    bool aux_vacina;
    char resposta[10];
    do
    {
        for (i = 0; i <= indice; i++)
        {
            if (usuario[i]->idUsuario > maior)
            {
                maior = usuario[i]->idUsuario;
            }
        }
        if(indice>1){
	
        for (i = 0; i <= indice; i++)
        {
       

            for (x = i + 1; x <= indice; x++)
            {
                

                if (usuario[i]->idUsuario > usuario[x]->idUsuario && usuario[x]->idUsuario != NULL)
                {
                	   

                    //trocar os valores pra ordenar por ordem crescente de id
                    usuario[i]->idUsuario = usuario[i]->idUsuario + usuario[x]->idUsuario; //id
                    usuario[x]->idUsuario = usuario[i]->idUsuario - usuario[x]->idUsuario;
                    usuario[i]->idUsuario = usuario[i]->idUsuario - usuario[x]->idUsuario;
                    strcpy(aux_nome,( usuario[i]->nome)); //ordenar nome
                    strcpy((usuario[i]->nome), (usuario[x]->nome));
                    strcpy((usuario[x]->nome), aux_nome);
                    strcpy(aux_email, usuario[i]->email); //ordenar email
                    strcpy(usuario[i]->email, usuario[x]->email);
                    strcpy(usuario[x]->email, aux_email);
                    strcpy(aux_cidade, usuario[i]->endereco.cidade); //ordenar cidade
                    strcpy(usuario[i]->endereco.cidade, usuario[x]->endereco.cidade);
                    strcpy(usuario[x]->endereco.cidade, aux_cidade);
                    strcpy(aux_bairro, usuario[i]->endereco.bairro); //ordenar bairro
                    strcpy(usuario[i]->endereco.bairro, usuario[x]->endereco.bairro);
                    strcpy(usuario[x]->endereco.bairro, aux_bairro);
                    strcpy(aux_rua, usuario[i]->endereco.rua); //ordenar rua
                    strcpy(usuario[i]->endereco.rua, usuario[x]->endereco.rua);
                    strcpy(usuario[x]->endereco.rua, aux_rua);
                    usuario[i]->endereco.numero = usuario[i]->endereco.numero + usuario[x]->endereco.numero; //ordenar numero
                    usuario[x]->endereco.numero = usuario[i]->endereco.numero - usuario[x]->endereco.numero;
                    usuario[i]->endereco.numero = usuario[i]->endereco.numero - usuario[x]->endereco.numero;
                    usuario[i]->endereco.cep = usuario[i]->endereco.cep + usuario[x]->endereco.cep; //ordenar cep
                    usuario[x]->endereco.cep = usuario[i]->endereco.cep - usuario[x]->endereco.cep;
                    usuario[i]->endereco.cep = usuario[i]->endereco.cep - usuario[x]->endereco.cep;
                    strcpy(aux_sexo, usuario[i]->sexo); //ordenar sexo
                    strcpy(usuario[i]->sexo, usuario[x]->sexo);
                    strcpy(usuario[x]->sexo, aux_sexo);
                    usuario[i]->altura = usuario[i]->altura + usuario[x]->altura; //ordenar altura
                    usuario[x]->altura = usuario[i]->altura - usuario[x]->altura;
                    usuario[i]->altura = usuario[i]->altura - usuario[x]->altura;
                    usuario[i]->vacina = usuario[i]->vacina + usuario[x]->vacina; //ordenar vacina
                    usuario[x]->vacina = usuario[i]->vacina - usuario[x]->vacina;
                    usuario[i]->vacina = usuario[i]->vacina - usuario[x]->vacina;
                }
            }
        }	
	}
	        
        printf("Insira o Id do usuario: ");
        scanf("%d", &pesquisaID);
        if (pesquisaID <maior/2)
        {
            for (i = 0; i <= indice / 2; i++)
            {
                if (usuario[i]->idUsuario == pesquisaID)
                {
                    n = i;
                    break;
                }
                else
                {
                    n = -1;
                }
            }
        }
        else
        {
            for (i = indice / 2; i <= indice; i++)
            {
                if (usuario[i]->idUsuario == pesquisaID)
                {
                    n = i;
                    break;
                }
                else
                {
                    n = -1;
                }
            }
        }
        if (n >= 0)
        {
            system("cls");
            system("color 0B");
            printf("===================USUARIO ENCONTRADO=====================\n");
            imprimeUm(n, usuario);
            system("pause");
            printf("\n Deseja Pesquisar novamente? (Responda com 'sim' ou 'nao')\n");
            fflush(stdin);
            fgets(resposta, 10, stdin);
        }
        else
        {
            system("cls");
            system("color 0C");
            printf(" USUARIO NAO ENCONTRADO!\n Deseja Pesquisar novamente? (Responda com 'sim' ou 'nao')\n");
            fflush(stdin);
            fgets(resposta, 10, stdin);
        }
    } while (stricmp(resposta, "sim\n") == 0);
}
void pesquisaEmail(int indice, dado *usuario)
{
    int n;
    char email[100], resposta[10];
    do
    {
        system("color 0F");
        printf(" Insira o Email do usuario: ");
        fflush(stdin);
        fgets(email, 100, stdin);
        for (i = 0; i <= indice; i++)
        {
            if (stricmp(email, usuario[i]->email) == 0)
            {
                n = i;
                break;
            }
            else
            {
                n = -1;
            }
        }
        if (n >= 0)
        {
            system("color 0B");
            printf("=====================USUARIO ENCONTRADO=====================\n");
            imprimeUm(n, usuario);
        }
        else
        {
            system("color 0C");
            printf(" USUARIO NAO ENCONTRADO!");
        }
        printf(" Deseja pesquisar novamente? (responda com 'sim' ou 'nao')\n");
        fflush(stdin);
        fgets(resposta, 10, stdin);
    } while (stricmp(resposta, "sim\n") == 0);
    system("pause");
}
void imprimir(int indice, dado *usuario)
{
    if (usuario[0]->idUsuario > 0)
    {
        printf("============IMPRIMIR USUARIOS===============\n");
        for (i = 0; i <= indice; i++)
        {
            if (usuario[i]->idUsuario > 0)
            {
                imprimeUm(i, usuario);
               
            }
        }
    }
    else
    {
        system("color 0C");
        printf("\n\n\n Voce ainda nao adicionou usuarios...\n\n\n");
        printf("======================================\n\n");
    }
    system("pause");
}
void backup(int indice, dado *usuario)
{
    for (i = 0; i <= indice; i++)
    {
        usuario[i]->backup_idUsuario = usuario[i]->idUsuario;
        strcpy(usuario[i]->backup_nome, usuario[i]->nome);
        strcpy(usuario[i]->backup_email, usuario[i]->email);
        strcpy(usuario[i]->backup_sexo, usuario[i]->sexo);
        strcpy(usuario[i]->backup_endereco.cidade, usuario[i]->endereco.cidade);
        strcpy(usuario[i]->backup_endereco.bairro, usuario[i]->endereco.bairro);
        strcpy(usuario[i]->backup_endereco.rua, usuario[i]->endereco.rua);
        usuario[i]->backup_endereco.numero = usuario[i]->endereco.numero;
        usuario[i]->backup_endereco.cep = usuario[i]->endereco.cep;
        usuario[i]->backup_altura = usuario[i]->altura;
        usuario[i]->backup_vacina = usuario[i]->backup_vacina;
    }
    system("color 0B");
    printf("\n\n\n BACKUP REALIZADO COM SUCESSO!\n\n");
    system("pause");
}
void restaurar(int indice, dado *usuario)
{
    char resposta[20];
    printf("=======================RESTAURAR  DADOS===========================\n");
    printf(" Tem certeza que deseja restaurar os  dados? (Responda com 'sim' ou 'nao')\n");
    fflush(stdin);
    fgets(resposta, 10, stdin);
    if (stricmp(resposta, "sim\n") == 0)
    {
        for (i = 0; i <= indice; i++)
        {
            usuario[i]->idUsuario = usuario[i]->backup_idUsuario;
            strcpy(usuario[i]->nome, usuario[i]->backup_nome);
            strcpy(usuario[i]->email, usuario[i]->backup_email);
            strcpy(usuario[i]->sexo, usuario[i]->backup_sexo);
            strcpy(usuario[i]->endereco.cidade, usuario[i]->backup_endereco.cidade);
            strcpy(usuario[i]->endereco.bairro, usuario[i]->backup_endereco.bairro);
            strcpy(usuario[i]->endereco.rua, usuario[i]->backup_endereco.rua);
            usuario[i]->endereco.numero = usuario[i]->backup_endereco.numero;
            usuario[i]->endereco.cep = usuario[i]->backup_endereco.cep;
            usuario[i]->altura = usuario[i]->backup_altura;
            usuario[i]->backup_vacina = usuario[i]->backup_vacina;
        }
        system("cls");
        system("color 0B");
        printf("\n\n\n DADOS RESTAURADOS COM SUCESSO!!\n\n");
        system("pause");
    }
}

