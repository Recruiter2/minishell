#include "../includes/minishell.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int	str_arr_eq(char **a, char **b)
{
	int i = 0;

	if (!a && !b) return 1;
	if (!a || !b) return 0;
	while (a[i] || b[i])
	{
		if (!a[i] || !b[i]) return 0;
		if (strcmp(a[i], b[i]) != 0) return 0;
		i++;
	}
	return 1;
}

void	free_res(char **res)
{
	int i = 0;
	if (!res) return;
	while (res[i])
		free(res[i++]);
	free(res);
}

void	print_res(char **res)
{
	int i = 0;
	if (!res) { printf("res=NULL\n"); return; }
	printf("[");
	while (res[i])
	{
		printf("\"%s\"", res[i]);
		if (res[i + 1]) printf(", ");
		i++;
	}
	printf("]\n");
}