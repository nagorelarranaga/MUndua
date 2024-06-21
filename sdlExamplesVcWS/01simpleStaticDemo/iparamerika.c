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


/* --------------------------- IPAR AMERIKAN GERTATU BEHARREKOAK -----------------------------------*/
int iparamerika(agertu)
{
    /* ------------- ALDAGAIAK DEKLARATU ---------------*/
    int ebentu = 0, irten = 0, galderakop = 0, erantzuna = 0, eginda = 0, dirualdaketa = 0, irudiaKargatuta = 0,
        galderaErantzuta = 0, galdera_aktiboa, botoia, tick, erantzun_zuzena, j = 0; //ixa1, ixa2;


    /* ----------- STRUCT-EI BALIOAK EMAN --------------*/
    KONTINENTEAK iparamerika = {

          {GALDERA1, GALDERA2, GALDERA3},
          IPARAMERIKA_TROFEOA,
    };

    int erantzunak_argazkiak[3] = { ERANTZUNA1, ERANTZUNA2, ERANTZUNA3 };

    KLIKABLEAK erantzun_zuzenak[3] = {

        {665, 447, 1255, 621}, // [0] 1.Galderaren erantzun zuzena
        {665, 658, 1255, 835}, // [1] 2.Galderaren erantzun zuzena
        {665, 864, 1255, 1042}, // [2] 3.Galderaren erantzun zuzena
    };

    KLIKABLEAK erantzun_okerrak[6] = {

        {665, 658, 1255, 835}, // [0] 1.Galderaren erantzun okerra
        {745, 873, 1255, 1042}, // [1] 1.Galderaren erantzun okerra

        {665, 447, 1255, 621}, // [2] 2.Galderaren erantzun zuzena
        {745, 873, 1255, 1042}, // [3] 2.Galderaren erantzun zuzena

        {665, 447, 1255, 621}, // [4] 3.Galderaren erantzun zuzena
        {665, 658, 1255, 835}, // [5] 3.Galderaren erantzun zuzena
    };

    /*KLIKABLEAK tickak[3] = {

        {1283, 473, 1411, 473},
        {1283, 685, 1411, 808},
        {1283, 897, 1411, 1010},
    };

    KLIKABLEAK ixak[6] = {

        {1283, 685, 1411, 808},
        {1283, 897, 1411, 1010},

        {1283, 473, 1411, 473},
        {1283, 897, 1411, 1010},

        {1283, 473, 1411, 473},
        {1283, 685, 1411, 808},

    };*/

    KLIKABLEAK hurrengoa_botoia = { 1629, 969, 1629 + (1862 - 1629), 969 + (1041 - 969) };


    /* ------------- ATZEKO PLANOA/FONDOA --------------*/
    atzekoplanoaJarri(IPARAMERIKA);


    irudiakMarraztu();
    pantailaBerriztu();


    /* ------------------- MUSIKA  --------------------*/
    musikaJarri(erreproduzitu, MUSIKA_IPARAMERIKA);


    /* ------------------ DIALOGOAK -------------------*/
    dialogoapantailaratu(IPARAMERIKA_DIALOGOA);



    /* ------------- BUKLE BAT, EBENTUAK KONTUAN IZANDA --------------*/
    while (!irten)
    {

        if (!irudiaKargatuta && galderakop < 3) {

            galdera_aktiboa = irudiaKargatu(iparamerika.idElementu[galderakop]);
            irudiaMugitu(galdera_aktiboa, 0, 0);
            irudiaKargatuta = 1;

            irudiakMarraztu();
            pantailaBerriztu();
        }

        ebentu = ebentuaJasoGertatuBada();

        /* ------ ESCAPE EGITEKO -------*/
        escape(ebentu);


        /* ------- KLIK BAT EGITEAN GERTATU BEHARREKOA -------*/
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();

            /* ------ AURREKO PANTAILARA JOATEKO -------*/
            atzerajoan(1, 0, dirualdaketa, 1);


            /* -------- HURRENGOA BOTOIAREN SOINUA --------*/
            int idSoinuaBotoia = loadSound(BOTOIEN_SOINUA);
            int idErantzun_okerra = loadSound(ERANTZUN_OKERRA);
            int idErantzun_zuzena = loadSound(ERANTZUN_ZUZENA);

            /* ------------ GALDERAK PASATZEKO -------------*/
            int i = 0;
            while (i < 3) {

                //ERANTZUN ZUZENA KLIKATUTA?
                if ((barruan(erantzun_zuzenak[galderakop].posX, erantzun_zuzenak[galderakop].zabalera, erantzun_zuzenak[galderakop].posY, erantzun_zuzenak[galderakop].altuera) || barruan(erantzun_okerrak[j].posX, erantzun_okerrak[j].zabalera, erantzun_okerrak[j].posY, erantzun_okerrak[j].altuera) || barruan(erantzun_okerrak[j + 1].posX, erantzun_okerrak[j + 1].zabalera, erantzun_okerrak[j + 1].posY, erantzun_okerrak[j + 1].altuera)) && !galderaErantzuta) {

                    /*if (galderakop < 3 && (barruan(erantzun_okerrak[j].posX, erantzun_okerrak[j].zabalera, erantzun_okerrak[j].posY, erantzun_okerrak[j].altuera) || (barruan(erantzun_okerrak[j + 1].posX, erantzun_okerrak[j + 1].zabalera, erantzun_okerrak[j + 1].posY, erantzun_okerrak[j + 1].altuera)))) {
                        printf("entra primer if");
                        playSound(idErantzun_okerra);
                        SDL_Delay(150);
                    }
                    else if (galderakop < 3 && barruan(erantzun_zuzenak[galderakop].posX, erantzun_zuzenak[galderakop].zabalera, erantzun_zuzenak[galderakop].posY, erantzun_zuzenak[galderakop].altuera)) {
                        printf("entra segundo if");
                        playSound(idErantzun_zuzena);
                        SDL_Delay(150);
                    }*/

                    if (galderakop < 3) {   

                        j += 2;
                        botoia = irudiaKargatu(HURRENGOA_BOTOIA);
                        irudiaMugitu(botoia, hurrengoa_botoia.posX, hurrengoa_botoia.posY);
                        erantzun_zuzena = irudiaKargatu(erantzunak_argazkiak[galderakop]);
                        irudiaMugitu(erantzun_zuzena, 1283, 473);
                    }

                    


                    /*tick = irudiaKargatu(TICK);
                    irudiaMugitu(tick, tickak[galderakop].posX, tickak[galderakop].posY);

                    ixa1 = irudiaKargatu(IXA);
                    irudiaMugitu(ixa1, ixak[galderakop].posX, ixak[galderakop].posY);
                    ixa2 = irudiaKargatu(IXA);
                    irudiaMugitu(ixa2, ixak[galderakop + 1].posX, ixak[galderakop + 1].posY);*/

                    galderaErantzuta = 1;
                    galderakop++;

                }
                /*else if (barruan(erantzun_okerrak[galderakop].posX, erantzun_okerrak[galderakop].zabalera, erantzun_okerrak[galderakop].posY, erantzun_okerrak[galderakop].altuera) && !galderaErantzuta) {

                    ixa = irudiaKargatu(IXA);
                    irudiaMugitu(ixa, ixak[galderakop].posX, ixak[galderakop].posY);

                }*/

                //HURRENGOA BOTOIA KLIKATUTA?
                if (galderaErantzuta && barruan(hurrengoa_botoia.posX, hurrengoa_botoia.zabalera, hurrengoa_botoia.posY, hurrengoa_botoia.altuera) && galderakop !=4) {

                    playSound(idSoinuaBotoia);
                    SDL_Delay(100);

                    /*irudiaKendu(tick);
                    irudiaKendu(ixa1);
                    irudiaKendu(ixa2);*/

                    irudiaKendu(erantzun_zuzena);
                    irudiaKendu(galdera_aktiboa);
                    irudiaKendu(botoia);

                    irudiaKargatuta = 0;
                    galderaErantzuta = 0;
                    

                    dirua += 200;
                    dirualdaketa += 200;
    
                }
                
                i++;
               
            }
            
            //AZKEN ELEMENTUARI DELAY-A AFEKTATU EZ DEZAN
            irudiakMarraztu();
            pantailaBerriztu();


            /* ------- TROFEOA PANTAILARATU -------*/
            trofeoaren_selloa(galderakop, 4, 0, iparamerika.idTrofeoa);
        }

        /* ------- DIRUA PANTAILARATU -------*/
        diruaPantailaratu(dirua);
        pantailaBerriztu();

        /* ------- SOINU GUZTIAK DESKARGATU -------*/
        soundsUnload();
    }
    return 0;
}
