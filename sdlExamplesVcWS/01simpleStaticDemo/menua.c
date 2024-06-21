#define _CRT_SECURE_NO_WARNINGS
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "irudiak.h"
#include "musika.h"
#include "jolasa.h" 
#include "orokorrak.h"
#include "soinu_efektuak.h"
#include "menua.h"
#include "OurTypes.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define KOP_BOTOI 5
void escape(ebentua);
int musikaJarri(int erreproduzitu, int MUSIKA);
void atzekoplanoaJarri(int argazki);
void atzerajoan(int pantaila, int n, int dirualdaketa);
void mugimenduMenuBotoiak(int index, int* idAldaketa, int irudiAldaketa);
void KlikaEtaSoinuBotoia(int idSoinuaBotoia);
int itxi(void);

/* ------- ALDAGAI GLOBALAK -------*/
KLIKABLEAK atzera = { 35, 46, 35 + (151 - 35), 35 + (134 - 35) };
POSIZIOA pos;
int erreproduzitu = 1;
dirua;
trofeoak[];


/* --------------------------- PROGAMA HASIERATU -----------------------------------*/
int hasieratu(void)
{
    //LEIHOA ZABALDU
    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Ezin da hasieratu: %s \n", SDL_GetError());
        return 0;
    }

    //HASIERA PANTAILA
    hasierapantaila();

    return 0;
}

/* ---------------------------MENUAREN PANTAILA -----------------------------------*/
int hasierapantaila(void)
{
    /* ----------------- ALDAGAIAK DEKLARATU -------------------*/
    int ebentu = 0, irten = 0;

    /* ------------- ATZEKO PLANOA/FONDOA --------------*/
    atzekoplanoaJarri(MENUA);

    /* ------------- MUSIKA ETA SOINUAK --------------*/
    musikaJarri(erreproduzitu, MUSIKA_MENUA); 
    int idSoinuaBotoia = loadSound(BOTOIEN_SOINUA); 

    /* ------------------- MENUAN GERTATU BEHARREKOAK ----------------------*/
    while (!irten)
    {
        //Aldagaiak deklaratu:
        dirua = 0;
        ebentu = ebentuaJasoGertatuBada();

        /* ------ ESCAPE EGITEKO -------*/
        escape(ebentu);

        /* ------- TROFEOEN KONTADOREA -------*/
        for (int i = 0; i < 6; i++)
        {
            trofeoak[i] = 0;
        }

        /* ------- GAINETIK PASATZEAN GERTATU BEHARREKOA -------*/
        if (ebentu == SAGU_MUGIMENDUA)
        {
            mugimenduMenuBotoiak(0, &mundu.idHasiJolasten_aldaketa, HASIJOLASTEN_ALDAKETA);
            mugimenduMenuBotoiak(1, &mundu.idGida_aldaketa, GIDA_ALDAKETA);
            mugimenduMenuBotoiak(2, &mundu.idIrten_aldaketa, IRTEN_ALDAKETA);
            mugimenduMenuBotoiak(3, &mundu.idKredituak_aldaketa, KREDITUAK_ALDAKETA);
            mugimenduMenuBotoiak(4, &mundu.idEzarpenak_aldaketa, EZARPENAK_ALDAKETA);

            irudiakMarraztu();
            pantailaBerriztu();
        }

        /* ------- KLIK BAT EGITEAN GERTATU BEHARREKOA -------*/
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();

            /* ------- BOTOI BATEAN KLIK EGITEAN, DAGOKION PANTAILA IREKI -------*/
            KlikaEtaSoinuBotoia(idSoinuaBotoia);

        }
    }

    /* ------- SOINU GUZTIAK DESKARGATU -------*/
    soundsUnload();

    return 0;
}


/* ------- PROGRAMA ITXI -------*/
int itxi(void)
{
    sgItxi();
    return 0;
}

/* ------- GAINETIK PASATZEAN GERTATU BEHARREKOA -------*/
void mugimenduMenuBotoiak(int index, int* idAldaketa, int irudiAldaketa)
{
    /* ----------- STRUCT-EI BALIOAK EMAN --------------*/
    KLIKABLEAK botoiak[KOP_BOTOI] =
    {
        {778, 697, 778 + (1142 - 778), 697 + (820 - 697)}, // [0] hasi jolasten
        {827, 845, 827 + (1093 - 827), 845 + (935 - 845)}, // [1] gida
        {827, 960, 827 + (1093 - 827), 960 + (1049 - 960)}, // [2] irten
        {1555, 53, 1555 + (1764 - 1555), 53 + (98 - 53)}, // [3] kredituak
        {1798, 26, 1798 + (1887 - 1798), 26 + (115 - 26)}, // [4] ezarpenak
    };

    if (barruan(botoiak[index].posX, botoiak[index].zabalera, botoiak[index].posY, botoiak[index].altuera))
    {
        if (*idAldaketa == 0)
        {
            *idAldaketa = irudiaKargatu(irudiAldaketa);
        }
        irudiaMugitu(*idAldaketa, botoiak[index].posX, botoiak[index].posY);
    }
    else
    {
        if (*idAldaketa != 0)
        {
            irudiaKendu(*idAldaketa);
            *idAldaketa = 0;
        }
    }
}

/* ------- BOTOI BATEAN KLIK EGITEAN, DAGOKION PANTAILA IREKI -------*/
void KlikaEtaSoinuBotoia(int idSoinuaBotoia)
{
    void (*pantailak[KOP_BOTOI])() = { jolastu, gida, itxi, kredituak, ezarpenak };
    int i = 0;

    /* ----------- STRUCT-EI BALIOAK EMAN --------------*/
    KLIKABLEAK botoiak[KOP_BOTOI] =
    {
        {778, 697, 778 + (1142 - 778), 697 + (820 - 697)}, // [0] hasi jolasten
        {827, 845, 827 + (1093 - 827), 845 + (935 - 845)}, // [1] gida
        {827, 960, 827 + (1093 - 827), 960 + (1049 - 960)}, // [2] irten
        {1555, 53, 1555 + (1764 - 1555), 53 + (98 - 53)}, // [3] kredituak
        {1798, 26, 1798 + (1887 - 1798), 26 + (115 - 26)}, // [4] ezarpenak
    };

    while (i < KOP_BOTOI)
    {
        if (barruan(botoiak[i].posX, botoiak[i].zabalera, botoiak[i].posY, botoiak[i].altuera))
        {
            playSound(idSoinuaBotoia);
            pantailak[i](0);
        }
        i++;
    }
}