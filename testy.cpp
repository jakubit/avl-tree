#include <iostream>
#include <string>
#include "testy.h"
#include "matrix.h"
#include "avl.h"


void dawajTestujemy()
{
    int opcja=0;

    while(1)
    {

        std::cout<<"[1] Test intow \n[2] Test stringow \n[3] Test macierzy \n[4] Zakoncz \nWybor: ";
        std::cin>>opcja;
        switch(opcja)
        {
            case 1: testIntow(); break;
            case 2: testStringow(); break;
            case 3: testMacierzy(); break;
            case 4: exit(1); break;
        }
    }
}

void testIntow()
{
    avlTree<int> drzewo;

    drzewo.insertValue(5);
    drzewo.insertValue(3);
    drzewo.insertValue(7);
    drzewo.insertValue(11);
    //drzewo.insertValue(8);
    //drzewo.insertValue(10);
    //drzewo.insertValue(2);

    avlTree<int> drzewo2;
/*
    drzewo2.insertValue(5);
    drzewo2.insertValue(3);
    drzewo2.insertValue(7);
    drzewo2.insertValue(11);
    drzewo2.insertValue(8);
    drzewo2.insertValue(12);
    drzewo2.insertValue(2);
*/

    drzewo2.insertValue(5);
    drzewo2.insertValue(2);
    drzewo2.insertValue(7);
    drzewo2.insertValue(11);

    avlTree<int> drzewo3 = (drzewo + drzewo2);
    avlTree<int> drzewo4 = (drzewo - drzewo2);
    avlTree<int> drzewo5(drzewo);

    int opcja=0;
    int element=0;

    while(1)
    {
        std::cout<<"[0] Wyswietlanie drzewa \n";
        std::cout<<"[1] Dodawanie elementu \n";
        std::cout<<"[2] Usuwanie elementu \n";
        std::cout<<"[3] Pobranie elementu \n";
        std::cout<<"[4] Dodawanie drzew\n";
        std::cout<<"[5] Odejmowanie drzew \n";
        std::cout<<"[6] Kopiowanie obiektu \n";
        std::cout<<"[7] Wielkosc drzewa \n";
        std::cout<<"[8] Porownanie drzew \n";
        std::cout<<"[9] Sprawdzenie wartosci \n";
        std::cout<<"[10] Iterator \n";
        std::cout<<"[12] Wroc do menu glownego \n";

        std::cin>>opcja;

        switch(opcja)
        {
            case 0: drzewo.display(); std::cout<<std::endl; break;
            case 1: std::cin>>element; drzewo.insertValue(element); break;
            case 2: std::cin>>element; drzewo.removeValue(element); break;
            case 3: std::cin>>element;
                    if(drzewo.checkValue(element))
                        std::cout<<"Twoj element: "<<drzewo.getValue(element)<<std::endl;
                    else std::cout<<"Nie ma takiej wartosci"<<std::endl;
                    break;
            case 4: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"---------------------------suma----------------------------\n";
                    drzewo3.display();
                    std::cout<<std::endl;
                    break;
            case 5: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"--------------------------roznica--------------------------\n";
                    drzewo4.display();
                    std::cout<<std::endl;
                    break;
            case 6: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo5.display();
                    std::cout<<std::endl;
                    break;
            case 7: std::cout<<"Wielkosc: "<<drzewo.height()<<std::endl; break;
            case 8: std::cout<<std::endl<<"---------------------------drzewo--------------------------\n";
                    drzewo.display();
                    std::cout<<std::endl<<"--------------------------drzewo2--------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"drzewo == drzewo2?\t"<<(drzewo == drzewo2)<<std::endl;
                    std::cout<<"drzewo != drzewo5?\t"<<(drzewo != drzewo5)<<std::endl;
                    break;
            case 9: std::cin>>element; std::cout<<"Czy "<<element<<" nalezy do drzewa? "<<drzewo.checkValue(element)<<std::endl; break;
            case 10: std::cout<<"Zawartosc dostepna w najnowszym DLC!!! Kup teraz za jedyne 9,99$!!!"<<std::endl; break;
            case 11: break;
        }

        if(opcja==11) break;
    }
}

void testStringow()
{
    avlTree<std::string> drzewo;

    drzewo.insertValue("a");
    drzewo.insertValue("r");
    drzewo.insertValue("t");
    drzewo.insertValue("elo");
    drzewo.insertValue("q");
    drzewo.insertValue("c");
    drzewo.insertValue("d");

    avlTree<std::string> drzewo2;
    drzewo2.insertValue("r");
    drzewo2.insertValue("w");
    drzewo2.insertValue("+");
    drzewo2.insertValue("no elo");

    avlTree<std::string> drzewo3 = (drzewo + drzewo2);
    avlTree<std::string> drzewo4 = (drzewo - drzewo2);
    avlTree<std::string> drzewo5(drzewo);

    int opcja=0;
    std::string element;

    while(1)
    {
        std::cout<<"[0] Wyswietlanie drzewa \n";
        std::cout<<"[1] Dodawanie elementu \n";
        std::cout<<"[2] Usuwanie elementu \n";
        std::cout<<"[3] Pobranie elementu \n";
        std::cout<<"[4] Dodawanie drzew\n";
        std::cout<<"[5] Odejmowanie drzew \n";
        std::cout<<"[6] Kopiowanie obiektu \n";
        std::cout<<"[7] Wielkosc drzewa \n";
        std::cout<<"[8] Porownanie drzew \n";
        std::cout<<"[9] Sprawdzenie wartosci \n";
        std::cout<<"[10] Iterator \n";
        std::cout<<"[11] Wroc do menu glownego \n";

        std::cin>>opcja;

        switch(opcja)
        {
            case 0: drzewo.display(); std::cout<<std::endl; break;
            case 1: std::cin>>element; drzewo.insertValue(element); break;
            case 2: std::cin>>element; drzewo.removeValue(element); break;
            case 3: std::cin>>element;
                    if(drzewo.checkValue(element))
                        std::cout<<"Twoj element: "<<drzewo.getValue(element)<<std::endl;
                    else std::cout<<"Nie ma takiej wartosci"<<std::endl;
                    break;
            case 4: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"---------------------------suma----------------------------\n";
                    drzewo3.display();
                    std::cout<<std::endl;
                    break;
            case 5: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"--------------------------roznica--------------------------\n";
                    drzewo4.display();
                    std::cout<<std::endl;
                    break;
            case 6: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo5.display();
                    std::cout<<std::endl;
                    break;
            case 7: std::cout<<"Wielkosc: "<<drzewo.height()<<std::endl; break;
            case 8: std::cout<<std::endl<<"---------------------------drzewo--------------------------\n";
                    drzewo.display();
                    std::cout<<std::endl<<"--------------------------drzewo2--------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"drzewo == drzewo2?\t"<<(drzewo == drzewo2)<<std::endl;
                    std::cout<<"drzewo != drzewo5?\t"<<(drzewo != drzewo5)<<std::endl;
                    break;
            case 9: std::cin>>element; std::cout<<"Czy "<<element<<" nalezy do drzewa? "<<drzewo.checkValue(element)<<std::endl; break;
            case 10: std::cout<<"Zawartosc dostepna w najnowszym DLC!!! Kup teraz za jedyne 9,99$!!!"<<std::endl; break;
            case 11: break;
        }

        if(opcja==11) break;
    }
}

void testMacierzy()
{
    Matrix m1(4, "m1");
    Matrix m2(3, "m2");
    Matrix m3(4, "m3");
    Matrix m4(3, "m4");
    Matrix m5(4, "m5");
    Matrix m6(3, "m6");
    Matrix m7(3, "m7");
    Matrix m8(4, "m8");
    Matrix m9(3, "m9");

    avlTree<Matrix> drzewo;

    drzewo.insertValue(m1);
    drzewo.insertValue(m2);
    drzewo.insertValue(m3);
    drzewo.insertValue(m4);
    drzewo.insertValue(m5);

    avlTree<Matrix> drzewo2;
    drzewo2.insertValue(m6);
    drzewo2.insertValue(m7);
    drzewo2.insertValue(m8);
    drzewo2.insertValue(m9);

    avlTree<Matrix> drzewo3 = (drzewo + drzewo2);
    avlTree<Matrix> drzewo4 = (drzewo - drzewo2);
    avlTree<Matrix> drzewo5(drzewo);

    int opcja=0;

    Matrix element(3, "element");

    while(1)
    {
        std::cout<<"[0] Wyswietlanie drzewa \n";
        std::cout<<"[1] Dodawanie elementu\n";
        std::cout<<"[2] Usuwanie elementu \n";
        std::cout<<"[3] Pobranie elementu \n";
        std::cout<<"[4] Dodawanie drzew\n";
        std::cout<<"[5] Odejmowanie drzew \n";
        std::cout<<"[6] Kopiowanie obiektu \n";
        std::cout<<"[7] Wielkosc drzewa \n";
        std::cout<<"[8] Porownanie drzew \n";
        std::cout<<"[9] Sprawdzenie wartosci \n";
        std::cout<<"[10] Iterator \n";
        std::cout<<"[11] Wroc do menu glownego \n";

        std::cin>>opcja;

        switch(opcja)
        {
            case 0: drzewo.display(); std::cout<<std::endl; break;
            case 1: drzewo.insertValue(element); break;
            case 2: drzewo.removeValue(element); break;
            case 3: drzewo.insertValue(drzewo2.getValue(m7)); break;
            case 4: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"---------------------------suma----------------------------\n";
                    drzewo3.display();
                    std::cout<<std::endl;
                    break;
            case 5: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"--------------------------roznica--------------------------\n";
                    drzewo4.display();
                    std::cout<<std::endl;
                    break;
            case 6: drzewo.display();
                    std::cout<<std::endl<<"-----------------------------------------------------------\n";
                    drzewo5.display();
                    std::cout<<std::endl;
                    break;
            case 7: std::cout<<"Wielkosc: "<<drzewo.height()<<std::endl; break;
            case 8: std::cout<<std::endl<<"---------------------------drzewo--------------------------\n";
                    drzewo.display();
                    std::cout<<std::endl<<"--------------------------drzewo2--------------------------\n";
                    drzewo2.display();
                    std::cout<<std::endl<<"drzewo == drzewo2?\t"<<(drzewo == drzewo2)<<std::endl;
                    std::cout<<"drzewo != drzewo5?\t"<<(drzewo != drzewo5)<<std::endl;
                    break;
            case 9: std::cout<<"Czy m1 nalezy do drzewa? "<<drzewo.checkValue(m1)<<std::endl;
                    std::cout<<"Czy m6 nalezy do drzewa? "<<drzewo.checkValue(m6)<<std::endl;
                    break;
            case 10: std::cout<<"Zawartosc dostepna w najnowszym DLC!!! Kup teraz za jedyne 9,99$!!!"<<std::endl; break;
            case 11: break;
        }

        if(opcja==11) break;
    }
}
