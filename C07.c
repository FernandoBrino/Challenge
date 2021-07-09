#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

char product1[20];
char product2[20];
char product3[20];
int quantity1;
int quantity2;
int quantity3;

int searchProduct() {
    system("cls");
    FILE *arc;

    char product[20];
    int i, j;

    printf("Digite o nome do produto que deseja procurar: ");
    scanf("%s", &product);

    arc = fopen("productList.txt", "r");

    for(i = 0; i < 3; i++) {
        fread(&product1, sizeof(product1), 1, arc);
        fread(&quantity1, sizeof(quantity1), 1, arc);

        for(j = 0; product1[j] != '\0'; j++) {
            if(product[j] != product1[j]) {
                break;
            }
        }

        if(product[j] == '\0' && product1[j] == '\0') {
            system("cls");
            printf("Product: %s\n", product1);
            printf("Quantity: %d\n\n", quantity1);

            fclose(arc);
            return i;
        }
    }
}

int menu(){
    int choice;

    printf("1 - Entrada de dados\n");
    printf("2 - Listar dados\n");
    printf("3 - Pesquisar produto pelo nome\n");
    printf("4 - Pesquisar produto pela 1º letra\n");
    printf("5 - Alterar dados\n");
    printf("6 - Excluir dados\n");
    printf("7 - Sair\n");
    printf("\nDigite o numero correspondente a opcao: ");
    scanf("%d", &choice);
    return (choice);
}

void dataSubmit(){
    system("cls");

    FILE *arc;
    arc = fopen("productList.txt", "wt");
    if(arc == NULL){
        printf("Erro ao encontrar arquivo!!");
        exit(0);
    }

    else{
        printf("Digite o nome do 1º Produto: ");
        scanf("%s", &product1);
        printf("Digite a quantidade de %s: ", product1);
        scanf("%d", &quantity1);
        fwrite(&product1, sizeof(product1), 1, arc);
        fwrite(&quantity1, sizeof(quantity1), 1, arc);

        printf("\nDigite o nome do 2º Produto: ");
        scanf("%s", &product2);
        printf("Digite o nome de %s: ", product2);
        scanf("%d", &quantity2);
        fwrite(&product2, sizeof(product2), 1, arc);
        fwrite(&quantity2, sizeof(quantity2), 1, arc);

        printf("\nDigite o nome do 3º Produto: ");
        scanf("%s", &product3);
        printf("Digite o nome de %s: ", product3);
        scanf("%d", &quantity3);
        fwrite(&product3, sizeof(product3), 1, arc);
        fwrite(&quantity3, sizeof(quantity3), 1, arc);
    }
    fclose(arc);
    system("cls");

}

void dataList(){

    system("cls");

    FILE *arc;
    arc = fopen("productList.txt", "r");

    if(arc == NULL){
        printf("Erro ao encontrar arquivo!!");
        exit(0);
    }

    else{
        fread(&product1, sizeof(product1), 1, arc);
        fread(&quantity1, sizeof(quantity1), 1, arc);

        fread(&product2, sizeof(product2), 1, arc);
        fread(&quantity2, sizeof(quantity2), 1, arc);

        fread(&product3, sizeof(product3), 1, arc);
        fread(&quantity3, sizeof(quantity3), 1, arc);

        printf("Product: %s\n", product1);
        printf("Quantity: %d\n\n", quantity1);

        printf("Product: %s\n", product2);
        printf("Quantity: %d\n\n", quantity2);

        printf("Product: %s\n", product3);
        printf("Quantity: %d\n\n", quantity3);
    }

    fclose(arc);
}

int searchCompleteName(){
    system("cls");

    FILE*arc;
    arc = fopen("productList.txt", "rt");

    char searchProduct[20];
    int i;
    int j;

    printf("Digite o nome do produto que deseja procurar: ");
    scanf("%s", &searchProduct);

    for(i = 0; i < 3; i++){
        fread(&product1, sizeof(product1), 1, arc);
        fread(&quantity1, sizeof(quantity1), 1, arc);

        for(j = 0; product1[j] != '\0'; j++){
            if(searchProduct[j] != product1[j]){
                break;
            }
        }

        if(searchProduct[j] == '\0' && product1[j] == '\0'){
            printf("Product: %s\n", product1);
            printf("Quantity: %d\n\n", quantity1);
            fclose(arc);
            return i;
        }
    }

    fclose(arc);
    return -1;
}

int searchFirstLetter(){
    FILE*arc;
    char product;
    int i = 0;
    int j = 0;

    printf("Digite a letra inicial do produto desejado: ");
    scanf("%s", &product);
    arc = fopen("productList.txt", "r");

    for(i = 0; i < 3; i++){
        fread(&product1, sizeof(product1), 1, arc);
        fread(&quantity1, sizeof(quantity1), 1, arc);

        if(product == product1[0]){
            printf("%Product: %s\n", product1);
            printf("Quantity: %d\n\n", quantity1);
            j++;
        }
    }

    if(j == 0){
        printf("Erro ao encontrar o Produto!!");
        searchFirstLetter();
    }
    fclose(arc);
}

int changeProduct(){
    FILE *arc;

    int valid;
    int byts;
    int userWish;
    int i, j;

    userWish = searchProduct();

    if(userWish == -1){
        printf("Erro ao encontrar produto");
        changeProduct();
    }

    byts = (sizeof(product1) + sizeof(quantity1)) *userWish ;

    arc = fopen("productList.txt", "r+");

    fseek(arc, byts, 0);

    fread(&product1, sizeof(product1), 1,arc);
    fread(&quantity1, sizeof(quantity1), 1, arc);

    char sup1[20];
    int sup2;
    sup1[20] = product1[20];
    sup2 = quantity1;



    for(int i = 0; i < 20; i++) {
        sup1[i] = product1[i];
    }

    printf("Alterar produto: ", sup1);
    scanf("%s", &product1);

     do {

            printf("Alterar quantidade: ", sup2);
            scanf("%d", &quantity1);

            if(quantity1 < 0 || quantity1 == 10) {
                printf("Nao é permitido digitar numeros negativos ou o numero 10.\n\n" );
            }

    } while(quantity1 < 0 || quantity1 == 10);

    fseek(arc, byts, 0);

    fwrite(&product1, sizeof(product1), 1, arc);
    fwrite(&quantity1, sizeof(quantity1), 1, arc);

    fclose(arc);
}

void deleteProduct(){
    int userWish;
    int byts;
    int i = 0;

    FILE *arc;

    userWish = searchProduct();

     if(userWish == -1) {
        printf("Erro ao encontrar produto");
        deleteProduct();
    }

    byts = (sizeof(product1) + sizeof(quantity1)) * userWish;

    arc = fopen("productList.txt", "r+");

    fseek(arc, byts, 0);

    fread(&product1, sizeof(product1), 1, arc);
    fread(&quantity1, sizeof(quantity1), 1, arc);

    product1[0] = '*';
    quantity1 = NULL;

    fseek(arc, byts, 0);

    fwrite(&product1, sizeof(product1), 1, arc);
    fwrite(&quantity1, sizeof(quantity1), 1, arc);

    fclose(arc);

    printf("Produto deletado!!\n\n");
}

int exitProgramm(){
    printf("Programa encerrado!!\n");
    exit(0);
}
int main(void){
    setlocale(LC_ALL, "portuguese");
    int choice;

    do{
        choice = menu();
        switch(choice){
            case 1:
                dataSubmit();
            break;
            case 2:
                dataList();
            break;
            case 3:
                searchCompleteName();
            break;
            case  4:
                searchFirstLetter();
            break;
            case 5:
                changeProduct();
            break;
            case 6:
                deleteProduct();
            break;
            case 7:
                exitProgramm();
            break;
        }
    }while(choice > 0 || choice <=7);
}
