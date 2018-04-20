#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <string>
#include <cstdio>
#include<sstream>

class Matrix
{
    private:
        int stopien_macierzy;
        double wyznacznik_macierzy;
        double **macierz;       //dynamiczna tablica dwuwymiarowa (NxN)
        double suma_komorek;
        std::string nazwa_macierzy;

    public:
        Matrix(const int wymiar, const std::string);       //konstruktor
        Matrix(const Matrix& kopiowana_macierz);      //konstruktor kopiujacy, do tworzenia obiektow
        Matrix& operator=(const Matrix& kopiowana_macierz);     //operator przypisania
        ~Matrix();      //destrukotr

        friend std::ostream & operator <<(std::ostream & out, Matrix & macierz_wyj);        //drukowanie macierzy (przeciazenie operatora << )

        ///dodawnie macierzy (przeciazenie operatora + += )
        Matrix operator+(const Matrix& macierz_pom);
        Matrix& operator+=(const Matrix& macierz_pom);

        ///odejmowanie macierzy (przeciazenie operatora - -= )
        Matrix operator-(const Matrix& macierz_pom);
        Matrix& operator-=(const Matrix& macierz_pom);

        ///mnozenie macierzy (przeciazenie operatora * *= )
        Matrix operator*(const Matrix& macierz_pom);
        Matrix& operator*=(const Matrix& macierz_pom);

        ///porownanie macierzy (przeciazenie operatora < )
        int operator<(Matrix& macierz_pom);

        ///porownanie macierzy (przeciazenie operatora == )
        int operator==(Matrix& macierz_pom);

        ///porownanie macierzy (przeciazenie operatora != )
        int operator!=(Matrix& macierz_pom);


        ///porownanie macierzy (przeciazenie operatora > )
        int operator>(Matrix& macierz_pom);

        ///sumowanie komorek
        double sumuj_komorki();

        ///wyswietlanie sumy komorek
        double drukuj_sume();

        ///oblicznie wyznacznika macierzy
        int wyznacznik();

        int ustawWartosci();
};

#endif // MATRIX_H


