#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>

typedef struct pokemon_Information {
    char PokemonName[50];
    int Pokemonlevel;
    char Pokemontype[10];
    char pokemon_ID[50];
    int gender;
    int date;
    int month;
    int year;
    char caught_location[50];
    char caught_by[50];
}pokemon;

void mainMenu()
{
    printf("Pokedex Inventory\n");
    printf("---------------------------\n");
    printf("1) Search for Pokemon\n");
    printf("2) Add Pokemon\n");
    printf("3) Discard Pokemon\n");
    printf("4) Show all Pokemons\n");
    printf("0) Exit!\n");
    printf("---------------------------\n");
}

void searchPokemon(){
    pokemon_Information p1;
    FILE *fp;
    char PokemonName[50];
    fp = fopen("pokedex.txt", "r");
    printf("Enter which pokemon do you want to search: ");
    scanf("\n%[^\n]%*c", PokemonName);
    while(fread(&p1,sizeof (pokemon_Information), 1, fp))
    {
        if(strcmp(p1.PokemonName, PokemonName) == 0){
            printf("--------------------\n");
            printf("DISPLAY POKEMON MENU\n");
            printf("\n Pokemon Name: %s", p1.PokemonName);
            printf("\n Pokemon Type: %s", p1.Pokemontype);
            printf("\n Pokemon Level: %d", p1.Pokemonlevel);
            printf("\n Pokemon ID: %s", p1.pokemon_ID);

            switch (p1.gender) {
                case 1 :
                    printf("\nGENDER : MALE");
                    break;
                case 2:
                    printf("\n GENDER : FEMALE");
                    break;
            }
            printf("\n Caught Date: %d", p1.date);
            printf("\n Caught Month: %d", p1.month);
            printf("\n Caught Year: %d", p1.year);
            printf("\n Caught location: %s", p1.caught_location);
            printf("\n Caught by: %s \n \n",p1.caught_by);
        }
    }
    if (strcmp(p1.PokemonName, PokemonName)<0) {
        printf("\nRecord Not found\n");
    }

    fclose(fp);
    system("pause");
};

void addPokemon(){

    pokemon_Information *pokemon1;
    FILE *fp;
    int n;
    printf("How many Pokemons do you want to enter: ");
    scanf("%d", &n);

    pokemon1 = (pokemon_Information*) calloc(n,sizeof (pokemon_Information));

    for(int i = 0; i < n; i ++){
        fp = fopen("pokedex.txt", "a");
        printf("--------------------\n");
        printf("ADD POKEMON MENU\n");
        printf("Pokemon Name: ");
        scanf("\n%[^\n]%*c", pokemon1[i].PokemonName );
        printf("Pokemon Type: ");
        scanf("\n%[^\n]%*c", pokemon1[i].Pokemontype );
        printf("Pokemon Level: ");
        scanf("%d", &pokemon1[i].Pokemonlevel);
        printf("Pokemon ID: ");
        scanf("%s", &pokemon1[i].pokemon_ID);
        printf("Pokemon Gender \n 1) MALE \n 2)FEMALE \n choose: ");
        scanf("%d", &pokemon1[i].gender);
        printf("Caught Date: ");
        scanf("%d", &pokemon1[i].date);
        printf("Caught Month: ");
        scanf("%d", &pokemon1[i].month);
        printf("Caught Year: ");
        scanf("%d", &pokemon1[i].year);
        printf("Caught location: ");
        scanf("\n%[^\n]%*c",pokemon1[i].caught_location);
        printf("Caught by: ");
        scanf("\n%[^\n]%*c", pokemon1[i].caught_by);
        fwrite(&pokemon1[i], sizeof (pokemon_Information), 1, fp);
        fclose(fp);
    }
    int yesno;
    printf("Want to enter pokemon again?: \n 1)YES \n 2)NO");
    scanf("%d", &yesno);
    switch (yesno) {
        case 1:addPokemon();
        case 2:
            break;
    }
};

void discardPokemon(){
    pokemon_Information p1;
    FILE *fp;
    FILE *fp_temp;
    char pokemon_ID[50];
    bool data_ada;
    char yatidak[10];
    fp = fopen("pokedex.txt","r");
    fp_temp = fopen("pokedextemp.txt","w");
    printf("--------------------\n");
    printf("Delete Pokemon Menu\n");
    printf("Enter pokemon ID on which pokemon you want to delete: ");
    scanf("\n%[^\n]%*c", pokemon_ID);
    while(fread(&p1, sizeof(pokemon_Information), 1, fp))
    {
        if(strcmp(p1.pokemon_ID, pokemon_ID) == 0)
        {
            printf("Pokemon has been discarded\n");
            data_ada = true;
        }
        else{
            fwrite(&p1, sizeof (pokemon_Information), 1, fp_temp);
        }
    }

    if (!data_ada)
    {
        printf("Pokemon hasn't been added yet\n");
    }
    fclose(fp);
    fclose(fp_temp);
    remove("pokedex.txt");
    rename("pokedextemp.txt", "pokedex.txt");
    system("pause");
    puts("");
};

void displayPokemon(){
    pokemon_Information p1;
    FILE *fp;
    fp = fopen("pokedex.txt", "r");
    while(fread(&p1,sizeof (pokemon_Information), 1, fp))
    {
        printf("--------------------\n");
        printf("DISPLAY POKEMON MENU\n");
        printf("\n Pokemon Name: %s", p1.PokemonName);
        printf("\n Pokemon Type: %s", p1.Pokemontype);
        printf("\n Pokemon Level: %d", p1.Pokemonlevel);
        printf("\n Pokemon ID: %s", p1.pokemon_ID);

        switch (p1.gender) {
            case 1 :
                printf("\nGENDER : MALE");
                break;
            case 2:
                printf("\n GENDER : FEMALE");
                break;
        }
        printf("\n Caught Date: %d", p1.date);
        printf("\n Caught Month: %d", p1.month);
        printf("\n Caught Year: %d", p1.year);
        printf("\n Caught location: %s", p1.caught_location);
        printf("\n Caught by: %s \n \n",p1.caught_by);
    }
    fclose(fp);
    system("pause");

};

int main() {
    int choice;
    do {
        mainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchPokemon();
                break;
            case 2:
                addPokemon();
                break;
            case 3:
                discardPokemon();
                break;
            case 4:
                displayPokemon();
                break;
        }

    }while(choice!=0);

}
