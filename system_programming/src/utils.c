/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 26 / 03 / 2025
 * Last update: 26 / 03 / 2025
 *****************************************/
 
#include "utils.h"

char *msg[] = 
{
	"fork failed\n", "fgets failed\n", "strtok failed\n",
	"execvp failed\n", "Too many arguments\n",
	"Empty line is not allowed\n", "SIGINT terminated the proccess\n",
	"SIGTERM terminated the proccess\n", "Arguments not met\n"
};
 
 
void ExitIfBad(int is_good, const char *msg)
{
	if (FALSE == is_good) 
	{
		perror(msg);
		puts(msg);
		exit(1);
	}
}



