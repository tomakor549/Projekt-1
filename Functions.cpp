#include "stdafx.h"
#include "Functions.h"

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
	int i, i1, i2;

	for (i = 1; i <= 3 * rozmiar; i++)
	{
		i1 = rand() % rozmiar; i2 = rand() % rozmiar;
		std::swap(t[i1], t[i2]);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void wypisz(int size, double t[]/*, std::string wypisz*/)
{
	std::ofstream txt;
	txt.open(/*wypisz*/ "wypisz.txt", std::ios::app);

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

bool poprawnosc(std::string c, bool a)
{
	int j, i;
	j = c.length();

	for (i = 0; i < j; i++)
	{
		if (c[i] >= 58)
		{
			std::cout << "blad w wierszu pliku" << std::endl;
			a = false;
			return a;
		}
		else
		{
			if (c[i] != 32)
			{
				if (c[i] != '\n')
				{
					if (c[i] < 45)
					{
						std::cout << "blad w wierszu pliku" << std::endl;
						a = false;
						return a;
					}
				}
			}
			if (i > 0)
			{
				if (c[i] == ' ')
				{
					if (c[i] == c[i] - 1)
					{
						std::cout << "blad w wierszu pliku" << std::endl;
						a = false;
						return a;
					}
				}
			}
			else
			{
				if (c[i] == ' ')
				{
					std::cout << "wiersz nie moze zaczynac sie od spacji :'(" << std::endl;
					a = false;
					return a;
				}
			}
		}
	}
	

}

void glowna(char sorttype, std::string wczytaj, std::string wypisz)
{
	std::ifstream plik;
	plik.open("wczytaj" odczytaj.txt");

	std::string zmienna;
	const char *c;
	int size;
	int i = 0;
	int j = 0;
	int k = 0;
	int z = 0;
	int po_przecinku = 0;
	int dodatnia_ujemna = 1;
	int wystepuje_przecinek = 0;
	double tab_glowna[50] = { 0 };
	double tab_pomocnicza[50] = { 0 };

	if (!plik.good())							//sprawdzenie poprawności pliku (czy jest, czy nie)
		std::cout << "błąd";

	while (getline(plik, zmienna))
	{
		bool a=true;
		a = poprawnosc(zmienna, a);
		if (!a)
			continue;

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
			wypisz(k, tab_glowna/*, wypisz*/);
			break;
		}
		case('b'):
		{
			wybor(k, tab_glowna);
			wypisz(k, tab_glowna/*, wypisz*/);
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
			wypisz(k, tab_glowna/*, wypisz*/);
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
}


