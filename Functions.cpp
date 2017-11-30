#include "Functions.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
// Sortowanie zwariowane
bool Posortowane(int rozmiar, double t[])
{
	int i;

	for (i = 0; i < rozmiar - 1; i++)
	{
		if (t[i] > t[i + 1])
		{
			return false;
		}
	}
	return true;
}

void Tasuj(int rozmiar, double t[])
{
	int i;
	int i1;
	int i2;

	for (i = 1; i <= 3 * rozmiar; i++)
	{
		i1 = rand() % rozmiar;
		i2 = rand() % rozmiar;
		std::swap(t[i1], t[i2]);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void wypisz(int size, double t[], std::string wypisz)
{
	std::ofstream txt;
	txt.open(wypisz, std::ios::app);

	for (int i = 0; i < size; i++)
	{
		std::cout << t[i] << " ";
		txt << t[i] << " ";
	}
	std::cout << std::endl;
	txt << std::endl;
	txt.close();

}

void wstawianie(int size, double t[])
{
	double x;
	int i;
	for (int j = size - 2; j >= 0; j--)
	{
		x = t[j];
		i = j + 1;
		while ((i < size) && (x > t[i]))
		{
			t[i - 1] = t[i];
			i++;
		}
		t[i - 1] = x;
	}
}

void wybor(int size, double t[])
{
	int i;
	int j;
	int min;

	for (j = 0; j < size - 1; j++)
	{
		min = j;
		for (i = j + 1; i < size; i++)
		{
			if (t[min] > t[i])
			{
				min = i;
			}
			std::swap(t[min], t[j]);
		}
	}
}

int poprawnosc(std::string c)
{
	int j, i;
	j = c.length();

	for (i = 0; i < j; i++)
	{
		if (c[i] >= 58)
		{
			return 1;
		}
		else
		{
			if (c[i] != 32)
			{
				if (c[i] != '\n')
				{
					if (c[i] < 45)
					{
						return 1;
					}
				}
			}
			if (i > 0)
			{
				if (c[i] == ' ')
				{
					if (c[i] == c[i - 1])
					{
						return 1;
					}
				}
			}
			else
			{
				if (c[i] == ' ')
				{
					return 1;
				}
			}
		}
		return 0;
	}
	

}

void glowna(char sorttype, std::string wczytaj, std::string lel)
{
	std::ifstream plik;
	plik.open(wczytaj);

	std::string zmienna;
	const char *c;
	int size;
	int i = 0;
	int j = 0;
	int k = 0;
	int z = 0;
	int n=0;
	int wiersz = 0;
	int po_przecinku = 0;
	int dodatnia_ujemna = 1;
	int wystepuje_przecinek = 0;
	double tab_glowna[50] = { 0 };
	double tab_pomocnicza[50] = { 0 };

	if (!plik.good())							//sprawdzenie poprawności pliku (czy jest, czy nie)
		std::cout << "błąd";

	while (getline(plik, zmienna))
	{
		wiersz++;
		int a=0;
		a = poprawnosc(zmienna);
		if (a)
		{
			n++;
			continue;
		}

		c = zmienna.c_str();
		size = zmienna.length();

		while (i < size)
		{

			if (c[i] == '-')
			{
				dodatnia_ujemna = -1;
				i++;
			}

			if (c[i] != ' ' && c[i]!='/')
			{
				if (c[i] != '.')
				{
					tab_pomocnicza[j] = c[i] - '0';
					i++;
					j++;

					if (wystepuje_przecinek>0)
					{
						po_przecinku--;
					}
				}
				else
				{
					wystepuje_przecinek = i;
					i++;
				}

			}
			else
			{
				i--;
				j--;

				while (j >= 0)
				{
					if (po_przecinku<0)
					{
						tab_glowna[k] = dodatnia_ujemna*tab_pomocnicza[j] * pow(10, po_przecinku) + tab_glowna[k];
						j--;
						po_przecinku++;
					}
					else
					{
						tab_glowna[k] = dodatnia_ujemna*tab_pomocnicza[j] * pow(10, z) + tab_glowna[k];
						j--;
						z++;
					}
				}


				if (c[i] == '/')
					break;

				k++;
				j = 0;
				i = i + 2;
				z = 0;
				po_przecinku = 0;
				dodatnia_ujemna = 1;
				wystepuje_przecinek = 0;

			}

		}
		//=============================================================================================
		switch (sorttype)
		{
		case('a'):
		{
			wstawianie(k, tab_glowna);
			wypisz(k, tab_glowna, lel);
			break;
		}
		case('b'):
		{
			wybor(k, tab_glowna);
			wypisz(k, tab_glowna, lel);
			break;
		}
		case('c'):
		{
			Posortowane(k, tab_glowna);
			Tasuj(k, tab_glowna);
			while (!Posortowane(k, tab_glowna))
			{
				Tasuj(k, tab_glowna);
			}
			wypisz(k, tab_glowna, lel);
			break;
		}
		default:
		{
			break;
		}
		}

		for (k; k >= 0; k--)
		{
			tab_glowna[k] = 0;
			tab_pomocnicza[k] = 0;
		}
		//=============================================================================================

		i = 0;
		j = 0;
		k = 0;
	}
	plik.close();

	std::ofstream plik1;
	plik1.open(lel, std::ios::app);
	std::cout << "Blednych wierszy: " << n << std::endl;
	std::cout << "Ilość wierszy: " << wiersz << std::endl;
	plik1 << "Blednych wierszy: " << n << std::endl;
	plik1<< "Ilosc wierszy: " << wiersz << std::endl;
	plik.close();
}


