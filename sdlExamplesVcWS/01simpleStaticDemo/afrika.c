#define _CRT_SECURE_NO_WARNINGS
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
#include "dialogoak.h"
#include "ezarpenak.h"
#include "gida.h"
#include "irabazi.h"
#include "irudiak.h"
#include "musika.h"
#include "jolasa.h" 
#include "orokorrak.h"
#include "kredituak.h"
#include "menua.h"
#include "OurTypes.h"
#include "soinu_efektuak.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define KOP_ZUHAITZAK_HAZIAK 12
void escape(ebentua);
int musikaJarri(int erreproduzitu, int MUSIKA);
int dialogoapantailaratu(IRUDIA);
void cursorra(int marraztu, const char* argazkia, int posX, int posY);
int barruan(int posX, int zabalera, int posY, int altuera);
void atzekoplanoaJarri(int argazki);
void atzerajoan(int pantaila, int n, int dirualdaketa);
void trofeoaren_selloa(int kontadorea, int nKont, int n, int trofeoarenIDa);

/* ------- ALDAGAI GLOBALAK -------*/
KLIKABLEAK atzera;
POSIZIOA pos;
dirua, erreproduzitu;
trofeoak[];


/* --------------------------- AFRIKAN GERTATU BEHARREKOAK -----------------------------------*/
int afrika(void)
{
    /* ------------- ALDAGAIAK DEKLARATU ---------------*/
    int i, idlortu[KOP_ZUHAITZAK_HAZIAK], ebentu = 0, irten = 0, zuhaitzkop = 0, dirualdaketa = 0;


    /* ----------- STRUCT-EI BALIOAK EMAN --------------*/
    KONTINENTEAK afrika =
    {
          {HAZIA, ZUHAITZA1, ZUHAITZA2, ZUHAITZA3},
          AFRIKA_TROFEOA,
    };

    KLIKABLEAK haziak_zuhaitzak[KOP_ZUHAITZAK_HAZIAK] =
    {
        {245, 925, 245 + (295 - 245), 925 + (951 - 925)},  //[0] hazia1
        {860, 882, 860 + (910 - 860), 882 + (909 - 882)}, //[1] hazia2
        {1537, 872, 1537 + (1587 - 1537), 872 + (899 - 872)}, //[2] hazia3

        {222, 843, 222 + (311 - 222), 843 + (952 - 843)},  //[3] zuhaitza1
        {842, 801, 842 + (928 - 842), 801 + (910 - 801)}, //[4] zuhaitza1
        {1519, 789, 1519 + (1605 - 1519), 789 + (898 - 789)}, //[5] zuhaitza1

        {201, 742, 201 + (352 - 201), 742 + (951 - 742)},  //[6] zuhaitza2
        {815, 702, 815 + (965 - 815), 702 + (909 - 702)}, //[7] zuhaitza2
        {1510, 690, 1510 + (1660 - 1510), 690 + (896 - 690)}, //[8] zuhaitza2


        {58, 451, 58 + (484 - 58), 451 + (955 - 451)},  //[9] zuhaitza3
        {672, 408, 672 + (1098 - 672), 408 + (912 - 408)}, //[10] zuhaitza3
        {1361, 409, 1361 + (1787 - 1361), 409 + (912 - 409)}, //[11] zuhaitza3
    };

    JOKOKO_ELEMENTUAK haziak_zuhaitzak_berria[KOP_ZUHAITZAK_HAZIAK] =
    {
        {0, HAZIA, haziak_zuhaitzak[0]},
        {0, HAZIA, haziak_zuhaitzak[1]},
        {0, HAZIA, haziak_zuhaitzak[2]},
        {0, ZUHAITZA1, haziak_zuhaitzak[3]},
        {0, ZUHAITZA1, haziak_zuhaitzak[4]},
        {0, ZUHAITZA1, haziak_zuhaitzak[5]},
        {0, ZUHAITZA2, haziak_zuhaitzak[6]},
        {0, ZUHAITZA2, haziak_zuhaitzak[7]},
        {0, ZUHAITZA2, haziak_zuhaitzak[8]},
        {0, ZUHAITZA3, haziak_zuhaitzak[9]},
        {0, ZUHAITZA3, haziak_zuhaitzak[10]},
        {0, ZUHAITZA3, haziak_zuhaitzak[11]},
    };


    /* ------------- ATZEKO PLANOA/FONDOA ETA HAZIAK --------------*/
    atzekoplanoaJarri(AFRIKA);

    for (i = 0; i <= 2; i++)
    {
        idlortu[i] = irudiaKargatu(haziak_zuhaitzak_berria[i].irudiarenHelbidea);
        irudiaMugitu(idlortu[i], haziak_zuhaitzak_berria[i].posizioa.posX, haziak_zuhaitzak_berria[i].posizioa.posY);
    }

    irudiakMarraztu();
    pantailaBerriztu();


    /* ------------------- MUSIKA  --------------------*/
    musikaJarri(erreproduzitu, MUSIKA_AFRIKA);


    /* ------------------ DIALOGOAK -------------------*/
    dialogoapantailaratu(AFRIKA_DIALOGOA);



    /* ------------- ARRATOIAREN KURTSORRA --------------*/
    cursorra(1, REGADERA, 20, 30);



    /* ------------- BUKLE BAT, EBENTUAK KONTUAN IZANDA --------------*/
    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();

        /* ------ ESCAPE EGITEKO -------*/
        escape(ebentu);

        /* ------- KLIK BAT EGITEAN GERTATU BEHARREKOA -------*/
        if (ebentu == SAGU_BOTOIA_EZKERRA) //klik egitean
        {
            pos = saguarenPosizioa();

            /* ------ AURREKO PANTAILARA JOATEKO -------*/
            atzerajoan(1, 3, dirualdaketa);


            /* --------- REGADERAREN SOINUA ----------*/
            int idSoinuaRegadera = loadSound(REGADERA_SOINUA);


            /* ---------------------------- ZUHAITZAK HAZTEKO -----------------------------------*/
            int i, z, k, j, abiso = 0, zuhaitza1bihurtu, zuhaitza2bihurtu, zuhaitza3bihurtu;

            for (i = 3; i < KOP_ZUHAITZAK_HAZIAK - 6; i++)
            {
                if (barruan(haziak_zuhaitzak[i].posX, haziak_zuhaitzak[i].zabalera, haziak_zuhaitzak[i].posY, haziak_zuhaitzak[i].altuera) && (!haziak_zuhaitzak_berria[i].estado))
                {
                    z = i;
                    k = i + 3;
                    j = i + 6;
                    playSound(idSoinuaRegadera);
                    SDL_Delay(300);


                    if (abiso == 0)
                    {
                        zuhaitza1bihurtu = irudiaKargatu(afrika.idElementu[1]);
                        irudiaMugitu(zuhaitza1bihurtu, haziak_zuhaitzak_berria[z].posizioa.posX, haziak_zuhaitzak_berria[z].posizioa.posY);
                        abiso = 1;
                    }
                    irudiakMarraztu();
                    pantailaBerriztu();
                    SDL_Delay(500);

                    if (abiso == 1)
                    {
                        zuhaitza2bihurtu = irudiaKargatu(afrika.idElementu[2]);
                        irudiaMugitu(zuhaitza2bihurtu, haziak_zuhaitzak_berria[k].posizioa.posX, haziak_zuhaitzak_berria[k].posizioa.posY);
                        irudiaKendu(zuhaitza1bihurtu);
                        abiso = 2;
                    }
                    irudiakMarraztu();
                    pantailaBerriztu();
                    SDL_Delay(500);

                    if (abiso == 2)
                    {
                        zuhaitza3bihurtu = irudiaKargatu(afrika.idElementu[3]);
                        irudiaMugitu(zuhaitza3bihurtu, haziak_zuhaitzak_berria[j].posizioa.posX, haziak_zuhaitzak_berria[j].posizioa.posY);
                        irudiaKendu(zuhaitza2bihurtu);
                        haziak_zuhaitzak_berria[i].estado = 1;
                        zuhaitzkop += 1;
                        dirua -= 50;
                        dirualdaketa -= 50;
                    }
                    irudiakMarraztu();
                    pantailaBerriztu();
                }
            }

            //AZKEN ELEMENTUARI DELAY-A AFEKTATU EZ DEZAN
            irudiakMarraztu();
            pantailaBerriztu();

            /* ------- TROFEOA PANTAILARATU -------*/
            trofeoaren_selloa(zuhaitzkop, KOP_ZUHAITZAK_HAZIAK / 4, 3, afrika.idTrofeoa);
        }

        /* ------- DIRUA PANTAILARATU -------*/
        diruaPantailaratu(dirua);
        pantailaBerriztu();


        /* ------- SOINU GUZTIAK DESKARGATU -------*/
        soundsUnload();
    }
    return 0;
}