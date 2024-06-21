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
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define KOP_PANELA_ERROTAK 9
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


/* --------------------------- EUROPAN GERTATU BEHARREKOAK -----------------------------------*/
int europa(void)
{
    /* ------------- ALDAGAIAK DEKLARATU ---------------*/
    int i, idlortu[KOP_PANELA_ERROTAK], ebentu = 0, irten = 0, errota_panel_kop = 0, dirualdaketa = 0;


    /* ----------- STRUCT-EI BALIOAK EMAN --------------*/
    KONTINENTEAK europa = 
    {
        {EGUZKIPANELA, HAIZEERROTA, 0},
        EUROPA_TROFEOA,
    };
    KLIKABLEAK panelak_errotak[KOP_PANELA_ERROTAK] =
    {
        {206, 420, 206 + (404 - 206), 420 + (765 - 420)}, //[0] Haizeerrota1
        {515, 314, 515 + (715 - 515), 314 + (660 - 314)}, //[1] Haizeerrota2
        {860, 251, 860 + (1078 - 860), 251 + (593 - 251)}, //[2] Haizeerrota3
        {1211, 314, 1211 + (1411 - 1211), 314 + (657 - 314)}, //[3] Haizeerrota4
        {1529, 420, 1529 + (1729 - 1529), 420 + (765 - 420)}, //[4] Haizeerrota45
        {306, 795, 306 + (671 - 306), 795 + (981 - 795)}, //[5] Eguzkipanela1
        {674, 669, 674 + (1028 - 674), 669 + (845 - 669)}, //[6] Eguzkipanela2
        {1055, 711, 1055 + (1415 - 1055), 711 + (888 - 711)}, //[7] Eguzkipanela3
        {1432, 834, 1432 + (1786 - 1432), 834 + (1008 - 834)}, //[7] Eguzkipanela4
    };

    JOKOKO_ELEMENTUAK panelak_errotak_berria[KOP_PANELA_ERROTAK] =
    {
        {0, HAIZEERROTA, panelak_errotak[0]},
        {0, HAIZEERROTA, panelak_errotak[1]},
        {0, HAIZEERROTA, panelak_errotak[2]},
        {0, HAIZEERROTA, panelak_errotak[3]},
        {0, HAIZEERROTA, panelak_errotak[4]},
        {0, EGUZKIPANELA, panelak_errotak[5]},
        {0, EGUZKIPANELA, panelak_errotak[6]},
        {0, EGUZKIPANELA, panelak_errotak[7]},
        {0, EGUZKIPANELA, panelak_errotak[8]},
    };

    /* ------------- ATZEKO PLANOA/FONDOA ETA HAZIAK --------------*/
    atzekoplanoaJarri(EUROPA);

    irudiakMarraztu();
    pantailaBerriztu();


    /* ------------------- MUSIKA  --------------------*/
    musikaJarri(erreproduzitu, MUSIKA_EUROPA);



    /* ------------------ DIALOGOAK -------------------*/
    dialogoapantailaratu(EUROPA_DIALOGOA);



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
            atzerajoan(1, 2, dirualdaketa);


            /* ------------ HAIZE ERROTAK ETA EGUZKI PANELAK JARTZEKO -------------*/
            for (int i = 0; i < KOP_PANELA_ERROTAK; i++) 
            {
                if (barruan(panelak_errotak[i].posX, panelak_errotak[i].zabalera, panelak_errotak[i].posY, panelak_errotak[i].altuera) && (!panelak_errotak_berria[i].estado)) 
                {
                    idlortu[i] = irudiaKargatu(panelak_errotak_berria[i].irudiarenHelbidea);
                    irudiaMugitu(idlortu[i], panelak_errotak_berria[i].posizioa.posX, panelak_errotak_berria[i].posizioa.posY);
                    panelak_errotak_berria[i].estado = 1;
                    errota_panel_kop += 1;
                    dirua -= 150;
                    dirualdaketa -= 150;
                }
            }

            //AZKEN ELEMENTUARI DELAY-A AFEKTATU EZ DEZAN
            irudiakMarraztu();
            pantailaBerriztu();


            /* ------- TROFEOA PANTAILARATU -------*/
            trofeoaren_selloa(errota_panel_kop, KOP_PANELA_ERROTAK, 2, europa.idTrofeoa);
        }

        /* ------- DIRUA PANTAILARATU -------*/
        diruaPantailaratu(dirua);
        pantailaBerriztu();

        /* ------- SOINU GUZTIAK DESKARGATU -------*/
        soundsUnload();
    }

    return 0;
}
