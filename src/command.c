#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "command.h"
#include "string.h"

// Prosedur untuk melakukan ATTACK
void ATTACK(Sinfotype *state, Bangunan *databuild, Graph relasi) {
    // $ Kamus Lokal
    Player *TopP;
    Player *EnemyP;
    List *Ltop;
    List *Lenemy;
    if (TurnInfo(*state) == 1) {
        TopP = &P1Info(*state);
        EnemyP = &P2Info(*state);
    }
    else {
        TopP = &P2Info(*state);
        EnemyP = &P1Info(*state);
    }
    Ltop = &ListBan(*TopP);
    Lenemy = &ListBan(*EnemyP);

    // $ Algoritma

    // * Bangunan Pemain
    printf(" __\n[__] ====  List of Buildings  ==== [P%d]\n", TurnInfo(*state));
    PrintInfo(*Ltop,*databuild);
    int giliran = TurnInfo(*state);
    printf("Choose a building to attack : ");
    int nomorBangunan;
    do {
        scanf("%d", &nomorBangunan);
        if (nomorBangunan > NbElmtList(*Ltop) || nomorBangunan < 1) {
            printf("Input is not valid! Silakan input index bangunan yang tersedia.\n");
            printf("Choose a building to attack : ");
        } else {printf("\n");}
    } while (nomorBangunan > NbElmtList(*Ltop) || nomorBangunan < 1);

    // * Ambil Bangunan Pemain
    address Pcurr = Search(*Ltop,nomorBangunan);
    int idxBangunanCurr = Info(Pcurr);

    PrintAttack(relasi, *Ltop, *databuild, idxBangunanCurr);
    // * Bangunan Lawan
    printf(" __\n[__] ====  List of Buildings  ==== [P%d]\n", TurnInfo(*state)%2+1);
    PrintInfo(*Lenemy,*databuild);
    printf("Choose a building you want to attack : ");
    int nomorBangunanDiserang;
    do {
        scanf("%d", &nomorBangunanDiserang);
        if (nomorBangunanDiserang > NbElmtList(*Ltop) || nomorBangunanDiserang < 1) {
            printf("Input is not valid! Please input given index of buildings.\n");
            printf("Choose a building you want to attack : ");
        } else {printf("\n");}
    } while (nomorBangunanDiserang > NbElmtList(*Ltop) || nomorBangunanDiserang < 1);
    // * Jumlah Pasukan
    int jumlahPasukan;
    while (1) {
        printf("Amount of soldiers use for attack : ");
        scanf("%d", &jumlahPasukan);
        if (jumlahPasukan > 0 && jumlahPasukan < Tentara(ElmtBan(*databuild, idxBangunanCurr))) {
            // ! Reset Status Critical Hit
            CH(FX(*TopP)) = false;
            break;
        }
        puts("Amount of soldiers is not valid!");
    }
    int idxEnemy = 1;
    TentaraAttack(databuild, idxEnemy, jumlahPasukan);
    boolean criticalHit = CH(FX(*EnemyP));
    boolean attackUp = AU(FX(*EnemyP));
    boolean shield = ActiveSH(SH(FX(*EnemyP)));

    TentaraInvaded(databuild, criticalHit, attackUp, shield, idxEnemy, jumlahPasukan);
    if (CanCapture(*databuild, idxEnemy)) {
      /*if (Search(L1, 3)) {
        printf("Bangunan ke-3 yang dimiliki oleh Pemain ke-1 telah dikuasai oleh Pemain ke-2.\n\n");
        DelP(&L1, 3);
      }
      InsVPrio(&L2, 3);
      TentaraAbsolute(&B, 3);*/
    }

    // cek apakah berhasil diambil atau tidak
    if (1) {
        printf("The building is yours now!\n");
        //CheckGetSH(EnemyP, &Skill(*EnemyP));

    } else {
        printf("You failed to grab the building.\n");
    }
}

// Prosedur untuk Melakukan LEVEL UP
void LEVEL_UP(Sinfotype *state) {
    // $ Kamus Lokal
    Player *TopP;
    Player *EnemyP;
    List *Ltop;
    List *Lenemy;
    Bangunan *databuild;
    if (TurnInfo(*state) == 1) {
        TopP = &P1Info(*state);
        EnemyP = &P2Info(*state);
    } else {
        TopP = &P2Info(*state);
        EnemyP = &P1Info(*state);
    }
<<<<<<< HEAD
    printf("----- Turn %d -----\n", TurnInfo(Curr(*gamestate)));
    Lcurr = &ListBan(*CurrP);
=======
    printf("+++++ Turn %d +++++", TurnInfo(*state));
    Ltop = &ListBan(*TopP);
>>>>>>> e2bf919c4a04604565bbb6b71da3c61e5588f917
    Lenemy = &ListBan(*EnemyP);
    databuild = &DataB(*state);

    // $ Algoritma
    // * Menampilkan daftar Bangunan
    printf(" __\n[__] ==== List of Buildings ==== [P%d]\n",TurnInfo(*state));
    PrintInfo(*Ltop, *databuild);
    printf("\n");

    // * User Input
    int nomorBangunan;
    printf("Choose the building you want to level-up : ");
    scanf("%d", &nomorBangunan);

    urutan nopilihan = GetInfo(*Ltop, nomorBangunan);

    // * Melakukan pengecekan keberhasilan level up
    char namaBuilding = Name(ElmtBan(*databuild, nopilihan));
    if (CheckLevelUp(*databuild,nopilihan)) {
        LevelUp(databuild,nopilihan);
        if (namaBuilding == 'C') { printf("Your Castle ");
        } else if (namaBuilding == 'V') { printf("Your Village ");
        } else if (namaBuilding == 'T') { printf("Your Tower ");
        } else /*(namaBuilding == 'T')*/ {printf("Your Fort ");}
        printf("has been leveled up to level %d!\n", Level(ElmtBan(*databuild,nopilihan)));
    } else {
        printf("You don't have enough soldiers at ");
        if (namaBuilding == 'C') { printf("your Castle ");
        } else if (namaBuilding == 'V') { printf("your Village ");
        } else if (namaBuilding == 'T') { printf("your Tower ");
        } else /*(namaBuilding == 'T')*/ {printf("your Fort ");}
        printf("to Level Up the building!\n", Name(ElmtBan(*databuild,nopilihan)));
    }
}

// Prosedur untuk memakai skill yang sedang dimiliki pemain
void SKILL(Stack *gamestate, Bangunan *databuild) {
    // $ Kamus Lokal
    Qinfotype usedskill;
    Player *TopP;
    Player *EnemyP;
    Queue *Qtop;
    Queue *Qenemy;
    List *Lenemy;

    if (TurnInfo(InfoTop(*gamestate)) == 1) {
        TopP = &P1Info(InfoTop(*gamestate));
        EnemyP = &P2Info(InfoTop(*gamestate));
    } else {
        TopP = &P2Info(InfoTop(*gamestate));
        EnemyP = &P1Info(InfoTop(*gamestate));
    }
    Qtop = &Skill(*TopP);
    Qenemy = &Skill(*EnemyP);
    Lenemy = &ListBan(*EnemyP);

    // $ Algoritma
    if (IsQEmpty(*Qtop)) {
        printf("Oh no! You don't have any skills!\n");
    } else {
        // * Use Skill
        QDel(Qtop, &usedskill);
        // * Switch
        if (strcmpi(usedskill,"IU") == 0) {
            printf("!!! INSTANT UPGRADE !!!\n");
            InstantUpgrade(TopP,databuild);
            printf("All your buildings have been Leveled Up!!\n");

        } else if (strcmpi(usedskill,"SH") == 0) {
            printf("!!! SHIELD UP !!!\n");
            Shield(TopP);
            printf("All your buildings have been Shielded for 2 turns!!\n");

        } else if (strcmpi(usedskill,"ET") == 0) {
            printf("You have gained an Extra Turn!!\n");
            ExtraTurn(TopP);
            // ! Detector Skill Critical Hit
            CheckGetCH(Qenemy);

        } else if (strcmpi(usedskill,"AU") == 0) {
            printf("!!! ATTACK UP !!!\n");
            AttackUp(TopP);
            printf("Your attacks for this turn ignore building defenses!!\n");

        } else if (strcmpi(usedskill,"CH") == 0) {
            printf("!!! CRITICAL HIT IMMINENT !!!\n");
            CriticalHit(TopP);
            printf("Your next attack will be twice as effective!!\n");


        } else if (strcmpi(usedskill,"IR") == 0) {
            printf("!!! INSTANT REINFORCEMENT !!!\n");
            InstantReinforcement(TopP, databuild);
            printf("All your buildings have been added by 5 soldiers!!\n");

        } else if (strcmpi(usedskill,"BA") == 0) {
            int bangunanmusuh1 = NbElmtList(*Lenemy);
            printf("!!! BARRAGE !!!\n");
            Barrage(TopP, EnemyP, databuild);
            int bangunanmusuh2 = NbElmtList(*Lenemy);
            printf("Soldiers in all your enemy's buildings have been decreased by 10!!\n");
            if (bangunanmusuh1 > bangunanmusuh2)
                printf("You've managed to snag a few buildings as well, impressive...\n");
        }
        ClearStack(gamestate);

    }
}

// Prosedur untuk melakukan UNDO
void UNDO(Stack *gamestate) {
    // $ Kamus Lokal
    Sinfotype buang;
    // $ Algoritma
    if (IsFirstAct(*gamestate)) {
        printf("You cannot Undo at the moment!\n");
    } else {
        printf("You have undone your past action!\n");
        Pop(gamestate, &buang);
    }
}

// Prosedur untuk melakukan MOVE
void MOVE(Sinfotype *state, Bangunan *databuild, Graph relasi) { // todo
    // $ Kamus Lokal
    Player *CurrP;
    List *Ltop;
    if (TurnInfo(*state) == 1) {
        CurrP = &P1Info(*state);
    } else {
        CurrP = &P2Info(*state);
    }
    Ltop = &ListBan(*CurrP);
    // $ Algoritma
    // * Bangunan Pemain
    printf(" __\n[__] ==== List of Buildings  ==== [P%d]\n", TurnInfo(*state));
    PrintInfo(*Ltop,*databuild);
    int giliran = TurnInfo(*state);
    int nomorBangunan;
    do {
        printf("Choose a building to move : ");
        scanf("%d", &nomorBangunan);
        if (nomorBangunan > NbElmtList(*Ltop) || nomorBangunan < 1) {
            printf("Input is not valid! Please input given index of buildings.\n");
        } else {printf("\n");}
    } while (nomorBangunan > NbElmtList(*Ltop) || nomorBangunan < 1);
    // * Ambil Bangunan Pemain
    address Pcurr = Search(*Ltop,nomorBangunan);
    int idxBangunanCurr = Info(Pcurr);

    // Menampilkan daftar bangunan terdekat
    int jumlahBangunanTerdekat;
    printf("List of Nearest Buildings :\n");
    PrintMove(relasi, *Ltop, *databuild, idxBangunanCurr, &jumlahBangunanTerdekat);
    if (jumlahBangunanTerdekat == 0) {
        puts("....");
        sleep(1);
        puts("It seems that this building does not have any other connected building.");
        puts("Press enter to go back to the main menu.");
        getchar();
        return;
    }
    int nomorBangunanDiterima;
    while (1) {
        printf("Choose a building which will receive the soldiers : ");
        scanf("%d", nomorBangunanDiterima);
        if (0 < nomorBangunanDiterima && nomorBangunanDiterima <= jumlahBangunanTerdekat)
            break;
        puts("Index input is invalid!");
    }
    int idxBangunanAcc = GetIdxMove(relasi, *Ltop, *databuild, idxBangunanCurr, nomorBangunanDiterima);
    int jumlahPasukan;
    while (1) {
        printf("Enter your desired amount of soldiers : ");
        scanf("%d", jumlahPasukan);
        if (0 < jumlahPasukan && jumlahPasukan <= Tentara(ElmtBan(*databuild, idxBangunanCurr)))
            break;
        puts("Input of amount soldiers is invalid!");
    }
    Tentara(ElmtBan(*databuild, idxBangunanCurr)) -= jumlahPasukan;
    Tentara(ElmtBan(*databuild, idxBangunanAcc)) += jumlahPasukan;
    printf("%d soldier(s) from ", jumlahPasukan);
    char namaBuilding = Name(ElmtBan(*databuild, idxBangunanCurr));
    if (namaBuilding == 'C') {
      printf("Castle ");
    } else if (namaBuilding == 'V') {
      printf("Village ");
    } else if (namaBuilding == 'T') {
      printf("Tower ");
    } else /* (Name(ElmtBan(B, InfoG2(C))) == 'F') */ {
      printf("Fort ");
    }

    TulisPOINT(Posisi(ElmtBan(*databuild, idxBangunanCurr)));

    printf("has been moved to ");

    namaBuilding = Name(ElmtBan(*databuild, idxBangunanAcc));
    if (namaBuilding == 'C') {
      printf("Castle ");
    } else if (namaBuilding == 'V') {
      printf("Village ");
    } else if (namaBuilding == 'T') {
      printf("Tower ");
    } else /* (Name(ElmtBan(B, InfoG2(C))) == 'F') */ {
      printf("Fort ");
    }

    TulisPOINT(Posisi(ElmtBan(*databuild, idxBangunanAcc)));

    puts("");

}

// Prosedur untuk melakukan SAVE
void SAVE(Sinfotype *state) {
    printf("Lokasi save file: ");
    // todo SAVEFILE
}



// Prosedur untuk melakukan EXIT Game
boolean EXIT(Sinfotype *state) {
    char inp;
    printf("Do you want to save the game before exiting the game? ");
    do {
        printf("Y/N/C\n");
        scanf(" %c", &inp);
        if (inp == 'Y') {
            SAVE(state);
            return true;
        } else if (inp == 'N') {
            return true;
        } else if (inp == 'C') {
            return false;
        }
    } while (inp != 'Y' && inp != 'N' && inp != 'C');
}
