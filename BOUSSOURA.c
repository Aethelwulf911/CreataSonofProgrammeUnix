/* 	BOUSSOURA 			Mohamed 			Cherif 				181832022492 				Gourpe : 03 					L2 ACAD A 	*/
#include <stdio.h>
#include <stdlib.h>         // exit(0);
#include <signal.h>
#include <unistd.h>
/*------------------------------------ Mode Automatique -----------------------------------------*/
int compteur = 0;           // le compteur sequentiel declarer globale
void handlerA() {      // Manipulation Automatique
    compteur++;             // incrementation le numéro séquentiel
    for(int i = 1 ; i <= 2 ; i++){  // création deux fils
        if(fork() == 0){            // Creation les deux fils
            if(i==1){                // Boucle teste s'il le fils1
                printf("code%d : %d\n",i,getppid()* compteur);      // affichage code1
                kill(getpid()+1,SIGCONT);           // envoye un signale de puis le fils a fils 2*/
            	exit(0);// quitter les deux fils juste apres fait les manipulation pour ne pas faire creer les fils de les deux fils
            }
            else{             // Boucle teste s'il le fils2
                kill(getpid(),SIGSTOP);             // stopper le programme
                printf("code%d : %d\n",i,getpid()* compteur);      // affichage code2
                exit(0);// quitter les deux fils juste apres fait les manipulation pour ne pas faire creer les fils de les deux fils
            }
        }
    }
    alarm(120);    // chaque 120 seconde == 2 min
}
/*------------------------------------ Mode Manuelle -----------------------------------------------*/
int compteur3 = 0 ;     // le compteur pour boucler dans le switch
int compteur1 = 1 ;     // le compteur sequentiel pour calculer les codes
void handlerQ(int sig){             // Manipulation Manuelle
        compteur3++;                // incrementation de compteur3
        switch(compteur3){
            case 1:                     // demande a utilisateur de taper Ctrl+C
                signal(SIGALRM, SIG_DFL);       // desactiver le mode automatique
                alarm(0);
                printf("\n Cliquer  la combinaison Ctrl+C pour continue \n");
                break;
            case 2:                     // case pour faire la manipulation et creation des fils
                for(int i = 1 ; i <= 2 ; i++){  // création deux fils
                    if(fork() == 0){ // creation les fils
                        if(i==1){   // fils1
                            printf("\n code1 : %d\n",getppid()* compteur1);      // affichage code1
                            kill(getpid()+1,SIGCONT);       // envoye un signale a fils2 pour faire le code2
                            exit(0);
                        }
                        else{       //fils 2
                            kill(SIGSTOP,getpid());  // stopper le fils2
                            printf("\n code2 : %d\n",getpid()* compteur1);      // affichage code2
                            kill(getppid(),SIGINT);
                            exit(0);
                        }
                    }
                }
                compteur3 = 0;          // initiaiser le compteur a 0
                compteur1++;            // incrementer le compteur1
                kill(getppid(),SIGINT);  
                break;
        }
}
/*--------------------------------------- Quitter -------------------------------------------------*/
int compteur2 = 0 ;
void Stop(int sig){                // Quitter le programme 
    if (compteur2 == 1)
    {
        fprintf(stdout," Programme de génération des codes arrêté \n");  // Affichage le message
        signal(SIGTSTP,SIG_DFL);    // deroutement SIGTSTP par default
        kill(getpid(),SIGTSTP);     // quitter le programme
    }
    else{
        signal(SIGALRM, SIG_DFL);   // deroutement le SIGALRM ()
        alarm(0);                   // desactiver SIGALRM pour desactiver le mode automatique
        signal(SIGINT, SIG_DFL);       // deroutement le SIGINT (Manuelle)
        compteur2++;
    }
}
void Stop2(int sig){                // Quitter le programme -2
    signal(SIGALRM, SIG_DFL);       // deroutement le SIGALRM (Automatique)
    alarm(0);
    signal(SIGINT, SIG_DFL);       // deroutement le SIGINT (Manuelle)
    printf(" Programme de génération des codes arrêté \n");     // Affichage le message
    signal(SIGTSTP,SIG_DFL);    	// deroutement SIGTSTP par default
    kill(getpid(),SIGQUIT) ;		// quitter le programme 
}
/*------------------------------- Programme principale -----------------------------------------*/
void main() {
    signal(SIGINT,handlerQ);   	// deroutement pour Ctrl-C  (Manuelle)
    signal(SIGTSTP,Stop);    	// deroutement -1 le Ctrl-Z
    //signal(SIGTSTP,Stop2);  	// deroutement -2 le Ctrl-Z
    signal(SIGALRM, handlerA);   // deroutement le SIGALRM (Automatique)
    alarm(120);                  // suspendre pendant 120 seconde == 2 minute
    for(;;)pause();
}