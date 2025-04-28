#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char nom[50];
    int score;
    char temps[50];

}utilisateur;

int main(){
    int rep ,x,y,s,n,res;
    utilisateur user;
    user.score =0;

    /*while(rep!=0){
         if (rep ==1){
            printf("Addition");
            srand(time(NULL));
            x=rand()%111;
            y=rand()%111;
            s=x+y;
            printf("%d +%d=\n",x,y);
            printf("Entrer le résultat\n");
            scanf("%d",res);
            printf("Vous avez entré %d\n ",res);
            if (res==s)
                printf("Bravo");
            else
                printf("Perdu");

         }


         else if (rep==2)
            printf("Soustraction"); //ajouter le menu + scanf ??
         else if (rep==3)
            printf("Multiplication");
         else if (rep==4)
            printf("Tables des multiplications");
                printf("choisir la table de multiplication de 1 à 10 :\n");
                scanf("%d",n);
                while((n>10)&&(n<1)){
                    printf("veuillez entrerun nombre entre 1 et 10:\n");
                    scanf("%d",n);
                }
         else if (rep==5)
            printf("Divisions");
    }
    printf("Merci de votre visite");*/
    printf("entrer votre nom:");
    scanf("%s",&user.nom);
    charger_score(&user);
    do{
             printf("+-----------------------------------+\n");
             printf("|1 : Addition                       |\n");
             printf("|2 : Soustraction                   |\n");
             printf("|3 : Multiplication                 |\n");
             printf("|4 : Tables des multiplications     |\n");
             printf("|5 : Divisions                      |\n");
             printf("|6 : Pariete                        |\n");
             printf("|0 : Sortir du jeu                  |\n");
             printf("+-----------------------------------+\n");
             printf("Quel est votre choix ?\n");

            scanf("%d",&rep);
            switch (rep){
            case 1 :
                printf("Addition\n");
                user.score=addition();
                if (user.score>0)
                    printf("Bravo\n");
                break;
            case 2 :
                printf("Soustraction\n");
                user.score=soustraction();
                if (user.score>0)
                    printf("Bravo\n");
                break;
            case 3 :
                printf("Multiplication\n");
                user.score=multiplication();
                if (user.score>0)
                    printf("Bravo\n");
                break;

            case 4 :
                printf("Tables des multiplications\n");
                printf("choisir un nombre: ");
                scanf("%d",&n);
                printf("la table de multiplication de %d\n",n);
                tab_multi(n);
                user.score=tab_multi_s();
                if (user.score>0)
                    printf("Bravo\n");
                break;

            case 5 :
                printf("Divisions\n");
                user.score=division();
                if (user.score>0)
                    printf("Bravo\n");
                break;
            case 6:
                printf("Parite\n");
                user.score=parite();
                if (user.score>0)
                    printf("Bravo\n");
                break;
            case 0 :printf("Merci de votre visite\n");break;
            default:printf("Repeter \n");break;
            }
    }while(rep!=0);


    // Enregistrement du score
    /// Recuperer heure cournte
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(user.temps, sizeof(user.temps), "%Y-%m-%d %H:%M:%S", tm_info);

    /// Ecriture sur le fichier
    sauvegarder_score(user);

    return 0;
}
void sauvegarder_score(utilisateur user) {
    FILE *fichierLecture, *fichierEcriture;
    char ligne[150];
    char nomLu[50], dateHeureLu[50];
    int scoreLu;
    int trouve = 0;

    fichierLecture = fopen("scores.txt", "r");
    fichierEcriture = fopen("scores_tmp.txt", "w");

    if (fichierLecture != NULL) {
        while (fgets(ligne, sizeof(ligne), fichierLecture)) {
            if (sscanf(ligne, "%[^;];%[^;];%d", nomLu, dateHeureLu, &scoreLu) == 3) {
                if (strcmp(nomLu, user.nom) == 0) {
                    // L'utilisateur existe, on écrit la nouvelle version
                    fprintf(fichierEcriture, "%s;%s;%d\n", user.nom, user.temps, user.score);
                    trouve = 1;
                } else {
                    // Sinon, on copie la ligne telle quelle
                    fprintf(fichierEcriture, "%s", ligne);
                }
            }
        }
        fclose(fichierLecture);
    }

    // Si l'utilisateur n'existait pas, on ajoute à la fin
    if (!trouve) {
        fprintf(fichierEcriture, "%s;%s;%d\n", user.nom, user.temps, user.score);
    }

    fclose(fichierEcriture);

    // Remplacer l'ancien fichier par le nouveau
    remove("scores.txt");
    rename("scores_tmp.txt", "scores.txt");
}


void charger_score(utilisateur* user) {
    FILE *fichier = fopen("scores.txt", "r");
    char ligne[150];
    char nomLu[50], dateHeureLu[50];
    int scoreLu;
    int trouve = 0;

    if (fichier != NULL) {
        while (fgets(ligne, sizeof(ligne), fichier)) {
            // Lecture sous forme Nom;Date;Score
            if (sscanf(ligne, " %[^;]; %[^;]; %d", nomLu, dateHeureLu, &scoreLu) == 3) {
                if (strcmp(nomLu, user->nom) == 0) {
                    printf("Bienvenue %s ! Dernier score enregistre le %s : %d points\n", nomLu, dateHeureLu, scoreLu);
                    trouve = 1;
                }
            }
        }
        fclose(fichier);
    }

    if (!trouve) {
        printf("Bienvenue %s ! Aucun score trouve, vous commencez a 0.\n", user->nom);
    }
}


int addition(){
    int x,y,res,s,essais=0;
    srand(time(NULL));
    x=rand()%111;
    y=rand()%111;
    s=x+y;
    while (essais < 3) {
        printf("%d + %d = ?\n", x, y);
        scanf("%d", &res);
        essais++;
        if (res == s) {
            return (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
        } else {
            printf("Incorrect. Essai %d/3\n", essais);
        }
    }
    printf("Perdu ! La bonne reponse etait : %d\n", s);
    return 0;
}
int multiplication(){
    int x,y,res,p,essais=0;
    srand(time(NULL));
    x=rand()%10+1;
    y=rand()%10+1;
    p=x*y;
    while (essais < 3) {
        printf("%d * %d = ?\n", x, y);
        scanf("%d", &res);
        essais++;
        if (res == p) {
            return (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
        } else {
            printf("Incorrect. Essai %d/3\n", essais);
        }
    }
    printf("Perdu ! La bonne reponse etait : %d\n", p);
    return 0;
}
int soustraction(){
    int x,y,res,d,essais=0;
    srand(time(NULL));
    x=rand()%111;
    y=rand()%111;
    if (x < y) {
        int temp = x;
        x = y;
        y = temp;
    }

    d = x - y;

    while (essais < 3) {
        printf("%d - %d = ?\n", x, y);
        scanf("%d", &res);
        essais++;
        if (res == d) {
            return (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
        } else {
            printf("Incorrect. Essai %d/3\n", essais);
        }
    }
    printf("Perdu ! La bonne reponse etait : %d\n", d);
    return 0;
}

int tab_multi(int n){
    int i;
    for(i=1;i<=10;i++){
        printf("%d*%d=%d\n",n,i,n*i);
    }
    return 0;
}

int tab_multi_s(int n){
    int rep, essais, total_points = 0;
    for (int i = 1; i <= 10; i++) {
        essais = 0;
        while (essais < 3) {
            printf("%d * %d = ?\n", n, i);
            scanf("%d", &rep);
            essais++;
            if (rep == n * i) {
                total_points += (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
                break;
            } else {
                printf("Incorrect. Essai %d/3\n", essais);
            }
        }
        if (essais == 3) {
            printf("Perdu ! La bonne reponse etait : %d\n", n * i);
        }
    }
    return total_points;
}

int division(){
    int x, y, d, r, res, div, essais = 0;
    srand(time(NULL));
    x = rand() % 10 + 1;
    y = rand() % 10 + 1;

    if (x < y) {
        int temp = x;
        x = y;
        y = temp;
    }

    d = x / y;
    r = x % y;

    while (essais < 3) {
        printf("Saisir la division entiere de %d / %d :\n", x, y);
        scanf("%d", &div);
        printf("Entrer le reste de la division :\n");
        scanf("%d", &res);
        essais++;
        if (res == r && div == d) {
            return (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
        } else {
            printf("Incorrect. Essai %d/3\n", essais);
        }
    }
    printf("Perdu ! La bonne reponse etait : quotient = %d, reste = %d\n", d, r);
    return 0;
}
int parite(){
    int x, essais = 0;
    char rep[10];
    srand(time(NULL));
    x = rand() % 10 + 1;

    while (essais < 3) {
        printf("%d est-il paire ou impaire ?\n", x);
        scanf("%s", rep);
        essais++;
        if (((x % 2 == 0) && strcmp(rep, "paire") == 0) || ((x % 2 != 0) && strcmp(rep, "impaire") == 0)) {
            return (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
        } else {
            printf("Incorrect. Essai %d/3\n", essais);
        }
    }
    printf("Perdu ! La bonne reponse etait : %s\n", (x % 2 == 0) ? "paire" : "impaire");
    return 0;
}





