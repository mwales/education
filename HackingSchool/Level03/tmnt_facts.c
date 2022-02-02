#include <stdio.h>

int main(int argc, char** argv)
{
	char* names[4] = { "Leonardo", "Raphael", "Michaelangelo", "Donatello" };
	char* weapons[4] = { "Sword", "Katana", "Nun-chucks", "Bow Staff" };
	char* colors[4] = { "Blue", "Red", "Orange", "Purple" };
	double height[4] = { 4.0 + 9.0 / 12.0,
		             4.0 + 6.0 / 12.0,
			     4.0 + 8.0 / 12.0,
			     5.0 };

	printf("%15s %15s %10s %10s\n", "Names", "Weapons", "Color", "Height");

	for(int i = 0; i < 4; i++)
	{
		printf("%15s %15s %10s %10.2f\n", names[i], weapons[i], colors[i], height[i]);
	}

	return 0;
}

