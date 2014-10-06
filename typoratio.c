/*
* This file is part of typoratio.
*
* typoratio is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* typoratio is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with typoratio. If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2014 Chris Foster
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_valid(float value)
{
	if (value == 0.0f)
		return 0;
	if (value < 0.0f)
		return -1;
	return 1;
}


int main(int argc, char **argv)
{
	if (argc == 1 || (argc - 1) % 2 != 0 || argc > 5)
	{
		printf("\
Usage: typoratio [-s fontsize] [-l linelength] [-h lineheight]\n\n\
\
 Calculate typographical ratios:\n\
   Specify one or two of the typographical parameters to calculate the optimal\n\
   value(s) of the remaining parameter(s).\n");
		return EXIT_SUCCESS;
	}
	
	float s = 0.0f;
	float l = 0.0f;
	float h = 0.0f;

	// Extract values from the arguments
	int i;
	for (i = 1; i < argc; i += 2)
	{
		if (strcmp(argv[i], "-s") != 0 &&
			strcmp(argv[i], "-l") != 0 &&
			strcmp(argv[i], "-h") != 0)
		{
			printf("Error: Invalid option.\n");
			return EXIT_FAILURE;
		}

		float value = atof(argv[i + 1]);
		int   valid = is_valid(value);

		if (valid != 1)
		{
			char message[39];
			strcpy(message, "Error: ");
			strcat(message, valid == 0 ? "Invalid " : "Negative ");
			strcat(message, "value for ");
			strcat(message, strcmp(argv[i], "-s") == 0 ? "font size." :
						   (strcmp(argv[i], "-l") == 0 ? "line length." :
														 "line height."));

			printf("%s\n", message);
			return EXIT_FAILURE;
		}

		if (strcmp(argv[i], "-s") == 0 && s == 0.0f)
			s = value;
		else if (strcmp(argv[i], "-l") == 0 && l == 0.0f)
			l = value;
		else if (strcmp(argv[i], "-h") == 0 && h == 0.0f)
			h = value;
		else
		{
			printf("Error: Value redefined.\n");
			return EXIT_FAILURE;
		}
	}

	// Golden ratio
	double const r = 1.61803398875;

	// Calculate the missing values
	if (s != 0.0f && l == 0.0f && h == 0.0f)
	{
		// Calculate l and h
		h = r * s;
		l = h * h;
	}
	else if (s == 0.0f && l != 0.0f && h == 0.0f)
	{
		// Calculate s and h
		h = sqrt(l);
		s = h / r;
	}
	else if (s == 0.0f && l == 0.0f && h != 0.0f)
	{
		s = h / r;
		l = h * h;
	}
	else if (s != 0.0f && l != 0.0f)
	{
		h = (r - 1.0 / (2.0 * r) * (1.0 - l / (r * r * s * s))) * s;
	}
	else if (s != 0.0f && h != 0.0f)
	{
		l = (r * r * s * s) * (1.0 + 2.0 * r * (h / s - r));
	}
	else
	{
		double const r2 = r * r;
		s = (sqrt(h * h * r2 * r2 - 2.0 * l * r2 + l) + h * r2) / (2.0 * r2 * r - r);
	}
	
	printf("Font Size:   %f\nLine Length: %f\nLine Height: %f\n", s, l, h);

	return EXIT_SUCCESS;
}

