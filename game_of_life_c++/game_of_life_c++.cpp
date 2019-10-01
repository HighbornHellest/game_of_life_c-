// game_of_life_c++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>  
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <atomic>
#include <iostream>       // std::cout
#include <thread> 

#define DEATH 32
#define LIFE 111


int v_current_gen[144];
int v_next_gen[144];

int nbour(int a[], int b)
{
	int nb = 0;


	if (a[b - 11] == 111)
	{
		++nb;
	}
	if (a[b - 10] == 111)
	{
		++nb;
	}
	if (a[b - 9] == 111)
	{
		++nb;
	};
	if (a[b - 1] == 111)
	{
		++nb;
	}
	if (a[b + 1] == 111)
	{
		++nb;
	}
	if (a[b + 9] == 111)
	{
		++nb;
	}
	if (a[b + 10] == 111)
	{
		++nb;
	}
	if (a[b + 11] == 111)
	{
		++nb;
	}


	return nb;

}

void genout(int a[])
{
	for (int i = 0; i < 144; ++i)
	{
		if (i == 0)
		{
			std::cout << (char)a[i] << " ";
			
		}
		else
		{
			if (i % 12 == 0 )
			{
				std::cout << '\n' << (char)a[i] << " " ;
				
			}
			else
			std::cout << (char)a[i] << " ";
			
		}

	}
	std::cout << "\n\n\n\n";
	
}

void convert(int a[])
{
	for (int i = 0; i < 144; ++i)
	{

		if (a[i] == 0)
		{
			a[i] = 111;
		}
		else
		{
			a[i] = 39;
		}

		if (i % 12 == 0 || i<=11 || i>=132 || i%12 == 11)
		{
			a[i] = 88;
		}

	}
	
}

void next_gen(int a[], int b[])
{
	for (int i = 0; i < 144; ++i)
	{
		//konverter
		if (i % 12 == 0 || i <= 11 || i >= 132 || i % 12 == 11)
		{
			b[i] = 88;
		}
		//nextgen
		else
		{
			int v_nbour = nbour(a, i);
			//ne memória szemét legyen benne
			b[i] = 39;
			//ha kevesebb mint 2 szomszéd illetve több mint 3, halál
			if (v_nbour < 2 || v_nbour > 3)
			{
				b[i] = 39;
			}
			//népesedés
			if (v_nbour == 3)
			{
				if (a[i] != 111)
				{
					b[i] = 111;
				}
			}
			//túlél ha 2 v 3 szomszéd
			if (v_nbour == 3 || v_nbour==2)
			{
				if(a[i] == 111)
				{
				b[i] == 111;
				}
			}
		}
	}	
};

void first_gen(int a[])
{
	//first_gen
	
	std::cout << "add meg a kezdo tablat, 100 db szam, \"111\" vagy \"32\"\n";

	for (int i = 0; i < 5; ++i)
	{
		scanf_s("%d", &a[i]);
	}

	printf("beolvasas megtortent!\nuser input was: ");
	for (int i = 0; i < 144; ++i)
	{
		if (i % 10 == 0)
			printf("");
		printf("%c",a[i]);
	}
};
void random_first_gen(int a[])
{
	

	for (int i = 0; i < 100; ++i)
	{
		
		
		a[i] = (int)rand() % 2;
		
	}
	convert(a);
};


void next_to_current(int a[], int b[])
{
	for (int i = 0; i < 144; ++i)
	{
		b[i] = a[i];
	}
}

char loop_variable_for_loop = 0;
void loop() {
	while (loop_variable_for_loop ==0)
	{
		next_gen(v_current_gen, v_next_gen);
		next_to_current(v_next_gen, v_current_gen);
		genout(v_current_gen);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		// your loop body here
	}
}



int main()
{
	srand(time(NULL));
	 random_first_gen(v_current_gen);
	 genout(v_current_gen);
	// std::cout << "\n HERE WE GO \n";
	 std::thread gameloop(loop);
	

	 loop_variable_for_loop = std::getchar();
	 
	 gameloop.join();
	 

	
    return 0;
}

