#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "string.h"

// Main Prosedur untuk command

void COMMAND(Stack *gamestate) {
    int input = 0;
    while (1) {
        printf("List command :\n");
        printf("1. Attack\n");
        printf("2. Level Up\n");
        printf("3. Skill\n");
        printf("4. Undo\n");
        printf("5. End Turn\n");
        printf("6. Move\n");
        printf("7. Save\n");
        printf("8. Exit\n");
        printf("ENTER COMMAND : ");
        scanf("%d", &input);
        printf("Your choice is : %d\n",input);

        switch(input) {
            case 1 :
                ATTACK(&gamestate);
                break;
            case 2 :
                LEVEL_UP(&gamestate);
                break;
            case 3 :
                SKILL(&gamestate);
                break;
            case 4 :
                UNDO(&gamestate);
                break;
            case 5 :
                END_TURN(&gamestate);
                break;
            case 6 :
                MOVE(&gamestate);
                break;
            case 7 :
                SAVE(&gamestate);
                break;
            case 8 :
                EXIT(&gamestate);
                break;
        }
    }
}

// Prosedur untuk melakukan ATTACK
void ATTACK(Stack *gamestate)
{
    printf("Daftar bangunan:\n");
    // Mnampilkan Daftar Bangunan
    printf("Bangunan yang digunakan untuk menyerang : ");
    int nomorBangunan;
    scanf("%d", &nomorBangunan);
    // while () {
    //
    // }
    printf("Daftar bangunan yang dapat diserang\n");
    // Menampilkan daftar bangunan yang dapat diserang
    printf("Bangunan yang diserang : ");
    int nomorBangunanDiserang;
    scanf("%d", &nomorBangunanDiserang);
    // while () {
    //
    // }
    int jumlahPasukan;
    printf("Jumlah pasukan: ");
    scanf("%d", &jumlahPasukan);

    // cek apakah berhasil diambil atau tidak
    if (1) {
        printf("Bangunan menjadi milikmu!\n");
    } else {
        printf("Bangunan gagal direbut.\n");
    }
}

// Prosedur untuk Melakukan LEVEL UP
void LEVEL_UP(Stack *gamestate) {
    // $ Kamus Lokal
    Player CurrP = GetCurrPlayer(*gamestate);
    // $ Algoritma
    printf("Daftar bangunan\n");
    // Menampilkan daftar Bangunan
    printf("Bangunan yang akan di level up : ");
    int nomorBangunan;
    scanf("%d", &nomorBangunan);
    // lakukan pengecekan keberhasilan level up
    if (1) {
        printf("Level %s-mu meningkat menjadi %d\n");
    } else {
        printf("Jumlah pasukan %s kurang untuk level up\n");
    }
}

//void abcabc(Stack* gamestate) {
 //   printf("abcabc masuk\n");
   // fflush(stdout);
    //SKILL(*gamestate);
//}
// Prosedur untuk memakai skill yang sedang dimiliki pemain
void SKILL(Stack *gamestate) {
    // $ Kamus Lokal
    Qinfotype temp;
    Queue Qtemp;
    Sinfotype buang;

    //Player CurrP = GetCurrPlayer(*gamestate);
    //printf("%d\n", TurnInfo(CurrP))
    // $ Algoritma

    Qtemp = Skill(GetCurrPlayer(*gamestate));
    if (IsQEmpty(Qtemp)){
        printf("You don't have any skill\n");
        //QAdd(&Qtemp, "IU");
    }

    else{
            //PrintQueue(Skill(CurrP));
            printf("You have used the skill : ");
            PrintInfoHead(Qtemp);
            printf("\n");
            QDel(&Qtemp, &temp);
            //PrintQueue(Skill(CurrP));
            printf("All your buildings have been Leveled Up!!\n");

        Skill(GetCurrPlayer(*gamestate)) = Qtemp;
    }
}

// Prosedur untuk melakukan UNDO
void UNDO(Stack *gamestate) {
    // $ Kamus Lokal
    Sinfotype Buang;
    if (IsFirstAct(*gamestate)) {
        printf("You cannot undo at the moment!");
    } else {
        printf("You have undone your past action!");
        Pop(&gamestate,&Curr(*gamestate));
    }
}

// Prosedur untuk melakukan END_TURN
void END_TURN(Stack *gamestate) {
    ChangeTurn(gamestate);

}

// Prosedur untuk melakukan SAVE
void SAVE(Stack *gamestate)
{
    printf("Lokasi save file: ");
}


// Prosedur untuk melakukan MOVE
void MOVE(Stack *gamestate)
{
    printf("Daftar bangunan\n");
    // Menampilkan daftar Bangunan
    printf("Pilih bangunan : ");
    int nomorBangunan;
    scanf("%d", &nomorBangunan);
    // melakukan validasi input
    // while () {
    //
    // }

    printf("Daftar bangunan terdekat :\n");
    // Menampilkan daftar bangunan terdekat
    printf("Bangunan yang akan menerima : ");
    int nomorBangunanDiterima;
    scanf("%d", nomorBangunanDiterima);
    printf("Jumlah pasukan : ");
    int jumlahPasukan;
    scanf("%d", jumlahPasukan);
    // melakukan validasi input
    // while () {
    //
    // }
    printf("%d pasukan [...] telah berpindah ke [...]\n", jumlahPasukan);
}

// Prosedur untuk melakukan EXIT Game
void EXIT(Stack *gamestate)
{
    char inp;
    printf("Apakah Anda ingin melakukan save terlebih dahulu? Y/N\n");
    scanf(" %c", &inp);
    if (inp == 'Y') {
        SAVE(gamestate);
    } else if (inp == 'N') {
        //ExitMenu = true;
    }
    // keluar
}
