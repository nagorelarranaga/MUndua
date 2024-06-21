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

#define KOP_SUAK 4
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


/* --------------------------- HEGO AMERIKAN GERTATU BEHARREKOAK -----------------------------------*/
int hegoamerika(void)
{
    /* ------------- ALDAGAIAK DEKLARATU ---------------*/
    int i, idlortu[KOP_SUAK], ebentu = 0, irten = 0, suakop = 0, dirualdaketa = 0;


    /* ----------- STRUCT-EI BALIOAK EMAN --------------*/
    KONTINENTEAK hegoamerika =
    {
        {SUA2, SUA3, SUA4},
        HEGOAMERIKA_TROFEOA,
    };

    KLIKABLEAK suak[KOP_SUAK] =
    {
        {775, 700, 775 + (979 - 775), 700 + (981 - 700)}, //[0] sua1
        {380, 562, 380 + (584 - 380), 562 + (843 - 562)}, //[1] sua2
        {1600, 650, 1600 + (1811 - 1600), 650 + (896 - 650)}, //[2] sua3 (dcha)
        {565, 582, 565 + (848 - 565), 582 + (719 - 582)}, //[3] sua4 (largo)
    };

    JOKOKO_ELEMENTUAK suak_berria[KOP_SUAK] =
    {
        {0, SUA2, suak[0]},
        {0, SUA2, suak[1]},
        {0, SUA3, suak[2]},
        {0, SUA4, suak[3]},
    };


    /* ------------- ATZEKO PLANOA/FONDOA ETA SUAK --------------*/
    atzekoplanoaJarri(HEGOAMERIKA);

    //SUAK
    for (i = 0; i < KOP_SUAK; i++)
    {
        idlortu[i] = irudiaKargatu(suak_berria[i].irudiarenHelbidea);
        irudiaMugitu(idlortu[i], suak_berria[i].posizioa.posX, suak_berria[i].posizioa.posY);
    }

    irudiakMarraztu();
    pantailaBerriztu();


    /* ------------------- MUSIKA  --------------------*/
    musikaJarri(erreproduzitu, MUSIKA_HEGOAMERIKA);


    /* ------------------ DIALOGOAK -------------------*/
    dialogoapantailaratu(HEGOAMERIKA_DIALOGOA);


    /* ------------- ARRATOIAREN KURTSORRA --------------*/
    cursorra(1, EXTINTOREA, 102, 36);



    /* ------------- BUKLE BAT, EBENTUAK KONTUAN IZANDA --------------*/
    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();

        /* ------ ESCAPE EGITEKO -------*/
        escape(ebentu);
      

        /* ------- KLIK BAT EGITEAN GERTATU BEHARREKOA -------*/
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();

            /* ------ AURREKO PANTAILARA JOATEKO -------*/
            atzerajoan(1, 1, dirualdaketa);


            /* --------- EXTINTOREAREN SOINUA ----------*/
            int idSoinuaExtintorea = loadSound(EXTINTOREA_SOINUA);


            /* ------------ SUAK KENTZEKO -------------*/
            int i = 0;
            while (i < KOP_SUAK)
            {
                if (barruan(suak[i].posX, suak[i].zabalera, suak[i].posY, suak[i].altuera) && (suak_berria[i].estado <= 3))
                {
                    
                    playSound(idSoinuaExtintorea);
                    SDL_Delay(400);

                    if (suak_berria[i].estado == 3) 
                    {
                        irudiaKendu(idlortu[i]);
                        suakop += 1;
                        dirua += 50;
                        dirualdaketa += 50;
                    }

                    suak_berria[i].estado += 1;
                }
               
                i++;
                
            }

            //AZKEN ELEMENTUARI DELAY-A AFEKTATU EZ DEZAN
            irudiakMarraztu();
            pantailaBerriztu();


            /* ------- TROFEOA PANTAILARATU -------*/
            trofeoaren_selloa(suakop, KOP_SUAK, 1, hegoamerika.idTrofeoa);
        }

        /* ------- DIRUA PANTAILARATU -------*/
        diruaPantailaratu(dirua);
        pantailaBerriztu();

        /* ------- SOINU GUZTIAK DESKARGATU -------*/
        soundsUnload();
    }

    return 0;
}