#include <iostream>
#include <conio.h> //getch - pobieranie klawisza z klawiatury
#include <cstdlib> // system ("cls) - oczyszczanie ekranu
#include <time.h> // srand
#include <windows.h> // funckja wait i procedura idzdoxy

using namespace std;

int szerokosc, wysokosc, szybkosc;
int gora, dol, lewo, prawo;
int wspolzednaXweza, wspolzednaYweza;
int wspolzednaXjedzenia, wspolzednaYjedzenia;
int klawisz;
int dlugosc=3, historiaWspolzednejX[10000], historiaWspolzednejY[10000];
int ile=0;
char kierunek='p'; //p=prawo l-lewo g-gora d-dol
char pole[35][35];
char waz=219, jed=177, pd=188, pg=187, lg=201, ld=200, lpoz=205, lpion=186;


//procedura przenosząca kursor
void idzdoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X=x;
    dwPos.Y=y;

    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}


/// procedura sprawdzajaca poprawnosc rozmiaru planszy
int check_plansza (int r)
{
 cout << "plansza miaga miec rozmiar w zakresie 5-35" <<endl;
 cout << "POPRAW SWOJ WYBOR (masz ostatnia szanse)" <<endl;
 cin >> r;
  if (r<5 || r>35) r=15;

}



int main()
{
    SetConsoleTitle("SNAKE - wezus  ::made by Daniel");
    /// wprowadzanie rozmiaru planszy
    cout << "Wybierz szerokosc planszy od 5 do 35" << endl;
    cin >> szerokosc;
    if (szerokosc<5 || szerokosc>35) check_plansza(szerokosc);

    cout << "Wybierz wysokosc planszy od 5 do 35" << endl;
    cin >> wysokosc;
    if (wysokosc<5 || wysokosc>35) check_plansza(wysokosc);

    /// okreslanie szybkosci gry
    cout << "Wybierz szybkosc gry z zakresu 1-15" << endl;
    cin >> szybkosc;
    if (szybkosc <1 || szybkosc>15) szybkosc=10;


    /// definiowanie klawiszy kontroli
    cout << "Nacisnij klawisze kontroli"<<endl;
    cout << "GORA"<<endl;
    gora=getch();
    if (gora==224)gora+=getch();
    if (gora==0)gora-=getch();

    cout << "DOL"<<endl;
    dol=getch();
    if (dol==224)dol+=getch();
    if (dol==0)dol-=getch();

    cout << "LEWO"<<endl;
    lewo=getch();
    if (lewo==224)lewo+=getch();
    if (lewo==0)lewo-=getch();

    cout << "PRAWO"<<endl;
    prawo=getch();
    if (prawo==224)prawo+=getch();
    if (prawo==0)prawo-=getch();

    for (int i=0; i<wysokosc; i++)
    {
        for(int j=0; j<szerokosc; j++)
        {
            pole[j][i]='p';
        }
    }
    srand(time(NULL));
    ///losowanie pola dla weza
    wspolzednaXweza=rand()%szerokosc;
    wspolzednaYweza=rand()%wysokosc;
    pole[wspolzednaXweza][wspolzednaYweza]='w';

    /// losowanie pola dla jedzenia
    do{
    wspolzednaXjedzenia=rand()%szerokosc;
    wspolzednaYjedzenia=rand()%wysokosc;
    }while(pole[wspolzednaXjedzenia][wspolzednaYjedzenia]!='p');

    pole[wspolzednaXjedzenia][wspolzednaYjedzenia]='j';

    system("cls"); //oczyszczenie ekranu przed rozpoczêciem rozgrywki

    /// rysowanie planszy
        cout<<lg;
        for (int i=0; i<szerokosc; i++) //gorna ramka
        {
            cout <<lpoz<<lpoz;
        }
        cout<<pg;

        for (int i=0; i<wysokosc; i++) //lewa ramka
        {
            cout<<endl<<lpion;
            for (int j=0; j<szerokosc; j++)
            {
            if (pole[j][i]=='p') cout <<"  ";
            if (pole[j][i]=='w') cout <<waz<<waz;
            if (pole[j][i]=='j') cout <<jed<<jed;
            }
                cout << lpion; //prawa ramka
    }
    cout <<endl;
        //dolna ramka
        cout<<ld;
        for  (int i=0; i<szerokosc; i++)
        {
            cout << lpoz<<lpoz;
        }
        cout<<pd;

    //start gry
    for(;;)
    {
        ile++; //ilosc ruchow
        ///pamiec polozenia weza
        historiaWspolzednejX[ile]=wspolzednaXweza;
        historiaWspolzednejY[ile]=wspolzednaYweza;

        //kasowanie ogona
        pole[historiaWspolzednejX[ile-dlugosc]][historiaWspolzednejY[ile-dlugosc]]='p';

        idzdoxy(0,0); // powrot do poczatku




        Sleep(1000/szybkosc);

        if(kbhit()) //if zostanie nacisniety klawisz
        {
            klawisz=getch();
            if (klawisz==224)klawisz+=getch();
            if (klawisz==0)klawisz-+getch();

            if (klawisz==gora && (kierunek=='l' || kierunek=='p')) kierunek='g';
            if (klawisz==dol && (kierunek=='l' || kierunek=='p')) kierunek='d';
            if (klawisz==lewo && (kierunek=='g' || kierunek=='d')) kierunek ='l';
            if (klawisz==prawo && (kierunek=='g' || kierunek=='d'))
                kierunek ='p';
        }


        //zmiana kierunku weza
        if(kierunek=='d') wspolzednaYweza++;
        if(kierunek=='g') wspolzednaYweza--;
        if(kierunek=='l') wspolzednaXweza--;
        if(kierunek=='p') wspolzednaXweza++;






        // przechodzenie przez sciany
        if (wspolzednaXweza==szerokosc) wspolzednaXweza=0;
        if (wspolzednaXweza==-1) wspolzednaXweza=szerokosc-1;
        if (wspolzednaYweza==wysokosc) wspolzednaYweza=0;
        if (wspolzednaYweza==-1) wspolzednaYweza=wysokosc-1;

        //wąż wpada w siebie
        if(pole[wspolzednaXweza][wspolzednaYweza]=='w')
        {
            idzdoxy(0,wysokosc+2);
            cout<<endl<<"\aKONIEC GRY     dlugosc = "<<dlugosc+1;
            break;
        }


        // waz zjada jedzenie
        if(pole[wspolzednaXweza][wspolzednaYweza]=='j')
        {
            dlugosc++;
             /// losowanie pola dla jedzenia po zjedzeniu poprzedniego
                do{
                    wspolzednaXjedzenia=rand()%szerokosc;
                    wspolzednaYjedzenia=rand()%wysokosc;
                }while(pole[wspolzednaXjedzenia][wspolzednaYjedzenia]!='p');

                pole[wspolzednaXjedzenia][wspolzednaYjedzenia]='j';
                idzdoxy(wspolzednaXjedzenia*2+1,wspolzednaYjedzenia+1);
                cout<<jed<<jed;
                }
                else{
                pole[historiaWspolzednejX[ile-dlugosc]][historiaWspolzednejY[ile-dlugosc]]='p';
                idzdoxy(historiaWspolzednejX[ile-dlugosc]*2+1,historiaWspolzednejY[ile-dlugosc]+1);
                cout<<"  ";
                }

        pole[wspolzednaXweza][wspolzednaYweza]='w';
        idzdoxy(wspolzednaXweza*2+1,wspolzednaYweza+1);
        cout<<waz<<waz;




 } //koniec petli for(::)


 getch();

    return 0;
}
