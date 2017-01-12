#include"variables.h"
#include"functions.h"

int main()
{
	while (1) {
		for (int m = 0; m < 40; m++)
			for (int n = 0; n < 20; n++)
				field[m][n] = 0;
		for (int m = 0; m < 20; m++)
			position[m] = 0;
		point = 0;
		maxpoint = 0;
		passed = 0;
		begin = time(NULL);
		titledim(60, HEIGHT);
		srand(clock());
		position[6] = position[7] = 'c';
		while (1) {
			passed = time(NULL) - begin;
			findmax();
			if (kbhit())
			{
				int ch;
				ch = getch();
				if (ch == 224 || ch == 0)
					ch = getch();
				switch (ch) {
				case RIGHT:
					if (position[17] == 'c')
						break;
					for (int j = 17; j >= 0; j--)
						position[j + 2] = position[j];
					position[0] = position[1] = 0;
					break;
				case LEFT:
					if (position[3] == 'c')
						break;
					for (int j = 2; j <= 19; j++)
						position[j - 2] = position[j];
					position[19] = position[18] = 0;
					break;
				case ENTER:
					getch();
					break;
				}
			}
			downshift();
			clearscreen();
			print();
			if (flag)
				hurdle();
			timeflag();
			Sleep(timeconst);
			if (check()) {
				getchar();
				if (exit())
					return 0;
				break;
			}
			point++;
			i++;
			
		}
	}
	return 0;
}