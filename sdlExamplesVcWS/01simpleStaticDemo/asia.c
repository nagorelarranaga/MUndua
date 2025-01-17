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

#define KOP_KARBONODIOXIDOA 13
void escape(ebentua);
int musikaJarri(int erreproduzitu, int MUSIKA);
int dialogoapantailaratu(IRUDIA);
void cursorra(int marraztu, const char* argazkia, int posX, int posY);
int barruan(int posX, int zabalera, int posY, int altuera);
void atzekoplanoaJarri(int argazki);
void atzerajoan(int pantaila, int n, int dirualdaketa);
void trofeoaren_selloa(int kontadorea, int nKont, int n, int trofeoarenIDa);

KLIKABLEAK atzera;
POSIZIOA pos;
dirua, erreproduzitu;
trofeoak[];

int asia(void)
{
    //FALTAN COSAS
    int i, idlortu[KOP_KARBONODIOXIDOA], ebentu = 0, irten = 0, karbonodioxidokop = 0, dirualdaketa=0;

    KONTINENTEAK asia = 
    {
           {KARBONODIOXIDOA, OXIGENOA, 0},
           ASIA_TROFEOA,
    };

    KLIKABLEAK molekulak[KOP_KARBONODIOXIDOA] =
    {
        {246, 228, 246 + (357 - 246), 228 + (320 - 228)},  //[0] karbono1
        {655, 269, 655 + (766 - 655), 269 + (361 - 269)}, //[1] karbono2
        {1247, 219, 1247 + (1358 - 1247), 219 + (311 - 219)}, //[2] karbono3
        {1535, 120, 1535 + (1646 - 1535), 120 + (192 - 120)}, //[3] karbono4
        {1685, 252, 1685 + (1796 - 1685), 252 + (363 - 252)}, //[4] karbono5
        {452, 575, 452 + (563 - 452), 575 + (686 - 575)}, //[5] karbono6
        {635, 591, 635 + (746 - 635), 591 + (683 - 591)}, //[6] karbono7
        {462, 744, 462 + (573 - 462), 744 + (836 - 744)}, //[7] karbono8
        {67, 533, 67 + (179 - 67), 533 + (639 - 533)}, //[8] oxigeno1
        {1042, 542, 1042 + (1154 - 1042), 542 + (648 - 542)}, //[9] oxigeno2
        {1457, 561, 1457 + (1564 - 1457), 561 + (667 - 561)}, //[10] oxigeno3
        {1720, 830, 1720 + (1832 - 1720), 830 + (936 - 830)}, //[11] oxigeno4
        {1000, 100, 1000 + (1112 - 1000), 100 + (206 - 100)}, //[12] oxigeno5
    };

    JOKOKO_ELEMENTUAK molekulak_berria[KOP_KARBONODIOXIDOA] =
    { 
        {0, KARBONODIOXIDOA, molekulak[0]},
        {0, KARBONODIOXIDOA, molekulak[1]},
        {0, KARBONODIOXIDOA, molekulak[2]},
        {0, KARBONODIOXIDOA, molekulak[3]},
        {0, KARBONODIOXIDOA, molekulak[4]},
        {0, KARBONODIOXIDOA, molekulak[5]},
        {0, KARBONODIOXIDOA, molekulak[6]},
        {0, KARBONODIOXIDOA, molekulak[7]},
        {0, OXIGENOA, molekulak[8]},
        {0, OXIGENOA, molekulak[9]},
        {0, OXIGENOA, molekulak[10]},
        {0, OXIGENOA, molekulak[11]},
        {0, OXIGENOA, molekulak[12]},
    };

    /* ------------- ATZEKO PLANOA/FONDOA ETA HAZIAK --------------*/
    atzekoplanoaJarri(ASIA);

    //musika
    musikaJarri(erreproduzitu, MUSIKA_ASIA);

    //dialogoa
    dialogoapantailaratu(ASIA_DIALOGOA);

    for (i = 0; i < KOP_KARBONODIOXIDOA; i++) 
    {
        idlortu[i] = irudiaKargatu(molekulak_berria[i].irudiarenHelbidea);
        irudiaMugitu(idlortu[i], molekulak_berria[i].posizioa.posX, molekulak_berria[i].posizioa.posY);
    }

    irudiakMarraztu();
    pantailaBerriztu();

    //pantaila honetan gauden bitartean egin beharrekoa
    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();
        escape(ebentu);

        if (ebentu == SAGU_BOTOIA_EZKERRA) //klik egitean
        {
            pos = saguarenPosizioa();

            //atzera
            atzerajoan(1, 4, dirualdaketa);

            int i;
            for (i = 0; i <= KOP_KARBONODIOXIDOA - 5; i++) 
            {
                if ((barruan(molekulak[i].posX, molekulak[i].zabalera, molekulak[i].posY, molekulak[i].altuera) && (!molekulak_berria[i].estado)) && (idlortu[i] != asia.idElementu[1])) {

                    int oxigenobihurtu = irudiaKargatu(asia.idElementu[1]);
                    irudiaMugitu(oxigenobihurtu, molekulak_berria[i].posizioa.posX, molekulak_berria[i].posizioa.posY);
                    irudiaKendu(idlortu[i]);
                    molekulak_berria[i].estado = 1;
                    karbonodioxidokop += 1;
                    dirua += 20;
                    dirualdaketa += 20;
                }
            }
            //azken elementuari ez afektatzeko
            irudiakMarraztu();
            pantailaBerriztu();

            //trofeoa pantailaratzeko
            trofeoaren_selloa(karbonodioxidokop, KOP_KARBONODIOXIDOA - 5, 4, asia.idTrofeoa);

        }
        diruaPantailaratu(dirua);
        pantailaBerriztu();
        soundsUnload();
    }
    return 0;
}