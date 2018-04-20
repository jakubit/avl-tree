#include "matrix.h"
#include <iostream>
#include <cmath>
#include <cstdlib>


/// DEFINICJE METOD KLASY MATRIX Z PLIKU FUNKCJE.H

///konstruktor
Matrix::Matrix(const int wymiar, const std::string nazwa)
{
    //tablica na wskazniki
    macierz=new double*[wymiar];

    //generowanie poszczegolych wymiarow
    for(int i=0; i<wymiar; i++)
        macierz[i]=new double [wymiar];

    //ustawienie wymiaru macierzy
    this->stopien_macierzy=wymiar;

    for(int i=0; i<wymiar; i++)
        for(int j=0; j<wymiar; j++) macierz[i][j]=0;

    //ustawienie wyznacznika na 1
    this->wyznacznik_macierzy=1;

    this->suma_komorek = 0;

    this->ustawWartosci();
    this->sumuj_komorki();

    this->nazwa_macierzy=nazwa;

    //komunikat o stworzeniu macierzy
    //std::cout<<"Konstruktor stworzyl macierz kwadratowa o stopniu: "<<wymiar<<std::endl;
}

///konstruktor kopiujacy, do tworzenia obiektow
Matrix::Matrix(const Matrix& kopiowana_macierz)
{
    //skopiowanie wymiaru
    stopien_macierzy=kopiowana_macierz.stopien_macierzy;

    //tablica na wskazniki
    macierz=new double*[stopien_macierzy];

    //generowanie poszczegolych wymiarow
    for(int i=0; i<stopien_macierzy; i++)
    {
        macierz[i]=new double [stopien_macierzy];
    }

    //kopiowanie wartosci
    for(int i=0; i<stopien_macierzy; i++)
    {
        for(int j=0; j<stopien_macierzy; j++) macierz[i][j]=kopiowana_macierz.macierz[i][j];
    }

    suma_komorek=kopiowana_macierz.suma_komorek;
    nazwa_macierzy=kopiowana_macierz.nazwa_macierzy;

    //komunikat o stworzeniu macierzy
    //std::cout<<"Konstruktor kopiujacy stworzyl macierz kwadratowa o stopniu: "<<kopiowana_macierz.stopien_macierzy<<std::endl;
}

///operator przypisania =
Matrix& Matrix::operator=(const Matrix& kopiowana_macierz)
{
    if(&kopiowana_macierz==this) return *this;

    /// zwalnianie pamieci dla this
    //usuwanie poszczegolnych kolumn wiersza pierwszego
    for(int i=0; i<stopien_macierzy; i++)
    {
        delete[] *(macierz+i);
    }

    //usuniecie wskaznika na macierz, czyli usuniecie pierwszego wiersza
    delete[] this->macierz;

    //skopiowanie stopnia
    stopien_macierzy=kopiowana_macierz.stopien_macierzy;

    //tablica na wskazniki
    macierz=new double*[stopien_macierzy];

    //generowanie poszczegolych wymiarow
    for(int i=0; i<stopien_macierzy; i++)
    {
        macierz[i]=new double [stopien_macierzy];
    }

    //kopiowanie wartosci
    for(int i=0; i<stopien_macierzy; i++)
    {
        for(int j=0; j<stopien_macierzy; j++) macierz[i][j]=kopiowana_macierz.macierz[i][j];
    }

    //komunikat o stworzeniu i przypisaniu macierzy
    //std::cout<<"Operator przypisania przypisal wartosci"<<std::endl;

    return *this;
}

///dodawnie macierzy, operator +
Matrix Matrix::operator+(const Matrix& macierz_pom)
{
    //Storzenie macierzy pomocniczej na wynik dodawania
    Matrix suma(this->stopien_macierzy, "suma");

    //Sumowanie
    for(int i=0; i<this->stopien_macierzy; i++)
    {
        for(int j=0; j<this->stopien_macierzy; j++)
        {
            suma.macierz[i][j]=this->macierz[i][j]+macierz_pom.macierz[i][j];
        }
    }

    //komunikat o dodaniu macierzy
    //std::cout<<"Operator + dodal macierze"<<std::endl;

    return suma;
}

///operator +=
Matrix& Matrix::operator+=(const Matrix& macierz_pom)
{
    //dodawanie elementow macierzy
    for(int i=0; i<stopien_macierzy; i++)
    {
        for(int j=0; j<stopien_macierzy; j++)
            macierz[i][j]+=macierz_pom.macierz[i][j];
    }

    //komunikat o dodaniu macierzy
    //std::cout<<"Operator += dodal macierze"<<std::endl;

    return *this;
}

///odejmowanie macierzy, operator -
Matrix Matrix::operator-(const Matrix& macierz_pom)
{
    //Macierz pomocnicza, na wynik odejmowania
    Matrix roznica(this->stopien_macierzy, "roznica");

    //Odejmowanie
    for(int i=0; i<this->stopien_macierzy; i++)
    {
        for(int j=0; j<this->stopien_macierzy; j++)
        {
            roznica.macierz[i][j]=this->macierz[i][j]-macierz_pom.macierz[i][j];
        }
    }

    //komunikat o odjeciu macierzy
    //std::cout<<"Operator - odjal macierze"<<std::endl;

    return roznica;
}

///operator -=
Matrix& Matrix::operator-=(const Matrix& macierz_pom)
{
    //Odejmowanie
    for(int i=0; i<stopien_macierzy; i++)
    {
        for(int j=0; j<stopien_macierzy; j++)
            macierz[i][j]-=macierz_pom.macierz[i][j];
    }

    //komunikat o odjeciu macierzy
   //std::cout<<"Operator -= odjal macierze"<<std::endl;

    return *this;
}

///mnozenie macierzy, operator *
Matrix Matrix::operator*(const Matrix& macierz_pom)
{
    //Zabezpieczenie przed mnozeniem macierzy o roznych stopniach, zwraca macierz lewostronna
    if(this->stopien_macierzy!=macierz_pom.stopien_macierzy) return *this;

    //Macierz pomocnicza, na wynik mnozenia
    Matrix iloczyn(this->stopien_macierzy, "iloczyn"); ///'iloczyn' jest obiektem statycznym, wiec konstruktor i destruktor sa wywolywane automatycznie

    //Mnozenie elementow
    for(int i=0; i<this->stopien_macierzy; i++)
    {
        for(int j=0; j<this->stopien_macierzy; j++)
        {
            for(int k=0; k<this->stopien_macierzy; k++)
            {
                iloczyn.macierz[i][j]+=this->macierz[i][k]*macierz_pom.macierz[k][j];
            }
        }
    }

    //komunikat o pomnozeniu macierzy
    //std::cout<<"Operator * pomnozyl macierze"<<std::endl;

    return iloczyn;
}

///operator *=
Matrix& Matrix::operator*=(const Matrix& macierz_pom)
{
    //Zabezpieczenie przed mnozeniem macierzy o roznych stopniach, zwraca macierz lewostronna
    if(this->stopien_macierzy!=macierz_pom.stopien_macierzy) return *this;

    //lokalna kopia macierzy wejsciowej
    Matrix pom2(*this);

    // zerowa macierz pomocnicza, na wynik mnozenia
    Matrix pom3(this->stopien_macierzy, "pom3");

    /* pom2 oraz pom3 to obiekty statyczne, wiec konstrukor oraz destruktor sa wywolywane automatycznie */

    for(int i=0; i<this->stopien_macierzy; i++)
    {
        for(int j=0; j<this->stopien_macierzy; j++)
        {
            for(int k=0; k<this->stopien_macierzy; k++)
            {
                pom3.macierz[i][j]+=pom2.macierz[i][k]*macierz_pom.macierz[k][j]; ///mnozenie macierzy
            }
            this->macierz[i][j]=pom3.macierz[i][j];///przekazanie wartosci iloczynu do macierzy wejsciowej
        }
    }

    //komunikat o pomnozeniu macierzy
    //std::cout<<"Operator *= pomnozyl macierze"<<std::endl;

    return *this;
}

///Sumowanie komorek
double Matrix::sumuj_komorki()
{
    for(int i=0; i<this->stopien_macierzy; i++)
    {
        for(int j=0; j<this->stopien_macierzy; j++) this->suma_komorek+=this->macierz[i][j];
    }

    return suma_komorek;
}

///Wyswietlanie sumy komorek
double Matrix::drukuj_sume()
{
    std::cout<<this->suma_komorek;
}

///Operator <
int Matrix::operator<(Matrix& macierz_pom)
{

    //std::cout<<"suma m1: "<<this->suma_komorek<<std::endl<<"suma m2: "<<macierz_pom.suma_komorek<<std::endl;


    if(this->suma_komorek < macierz_pom.suma_komorek) return 1;
    else return 0;

    //std::cout<<"suma m1: "<<this->suma_komorek;

    //std::cout<<"suma m1: "<<this->suma_komorek<<std::endl<<"suma m2: "<<macierz_pom.suma_komorek;
}

///porownanie macierzy (przeciazenie operatora == )
int Matrix::operator==(Matrix& macierz_pom)
{
    //std::cout<<"suma m1: "<<this->suma_komorek<<std::endl<<"suma m2: "<<macierz_pom.suma_komorek<<std::endl;

    if(this->suma_komorek == macierz_pom.suma_komorek) return 1;
    else return 0;
}

///porownanie macierzy (przeciazenie operatora != )
int Matrix::operator!=(Matrix& macierz_pom)
{
    if(this->suma_komorek != macierz_pom.suma_komorek) return 1;
    else return 0;
}

///porownanie macierzy (przeciazenie operatora > )
int Matrix::operator>(Matrix& macierz_pom)
{
    if(this->suma_komorek > macierz_pom.suma_komorek) return 1;
    else return 0;
}

///Oblicznie wyznacznika metoda Gaussa
int Matrix::wyznacznik()
{
    int i,j,k;
    float d;

    //Lokalna kopia macierzy, ktorej wyznacznik liczymy
    Matrix pom(*this);

    const double eps = 1e-5; //przyblizenie zera

    //Przeksztalcanie macierzy na macierz trojkatna gorna
    for(j=0; j<pom.stopien_macierzy; j++)
    {
        for(i=0; i<pom.stopien_macierzy; i++)
        {
            if(i>j)
            {
                d=pom.macierz[i][j]/pom.macierz[j][j];
                for(k=0; k<pom.stopien_macierzy; k++)
                {
                    pom.macierz[i][k]=pom.macierz[i][k]-d*pom.macierz[j][k];
                    if((pom.macierz[i][k]<eps)&&(pom.macierz[i][k]>-eps)) pom.macierz[i][k]=0; ///gdy wartosc komorki macierzy jest bardzo mala, tzn z przedzialu (-eps; eps) to szacuje ja jako zero
                }                                                                  ///inaczej nie utworzylaby sie macierz trojkatna gorna...
            }
        }
    }

    double wyzn=1;
    //Wyznacznik macierzy trojkatnej gornej to iloczyn elementow na glownej przekatnej
    for(i=0; i<pom.stopien_macierzy; i++)
        wyzn*=pom.macierz[i][i];

    this->wyznacznik_macierzy=wyzn;

    //std::cout<<std::endl<<"elo, wyznacznik: "<<this->wyznacznik_macierzy<<std::endl;
    //std::cout<<this->wyznacznik_macierzy;

    return wyzn;
}

///destrukotr
Matrix::~Matrix()
{
    //usuwanie poszczegolnych kolumn wiersza pierwszego
    for(int i=0; i<stopien_macierzy; i++)
    {
        delete[] *(macierz+i);
    }

    //usuniecie wskaznika na macierz, czyli usuniecie pierwszego wiersza
    delete[] this->macierz;

    //std::cout<<"Usunieto macierz!"<<std::endl;
}

///drukowanie macierzy (przeciazenie operatora << )
std::ostream& operator<<(std::ostream & out, Matrix & macierz_wyj)
{
    //std::cout<<"Drukowanie macierzy, przeciazenie operatora <<"<<std::endl;
/*
    for(int i=0; i<macierz_wyj.stopien_macierzy; i++)
    {
        for(int j=0; j<macierz_wyj.stopien_macierzy; j++) out<<macierz_wyj.macierz[i][j]<<"\t";
        out<<std::endl;
    }
*/
    std::cout<<macierz_wyj.nazwa_macierzy<<"("<<macierz_wyj.suma_komorek<<")"<<std::endl;
    return out;
}

///Ustawienie losowych wartosci macierzy
int Matrix::ustawWartosci()
{
    //int wartosc=std::rand();
    //srand(time(0));

    for(int i=0; i<stopien_macierzy; i++)
    {
        for(int j=0; j<stopien_macierzy; j++)
        {

            this->macierz[i][j]=std::rand()%10;
        }
    }
    return 0;
}


