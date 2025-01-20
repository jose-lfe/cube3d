#include "../kiki/cub3d.h"

// Fonction pour extraire la prochaine valeur et avancer dans la chaîne
int	extract_next_value(char **str)
{
	int value;
	value = ft_atoi(*str); // Convertit la chaîne actuelle en entier
	// Avance jusqu'à la prochaine virgule ou la fin de la chaîne
	while (**str && **str != ',') {
		(*str)++;
	}
    // Si une virgule est trouvée, passe au caractère suivant
	if (**str == ',') {
		(*str)++;
	}
	printf("%i\n", value); //
    return value;
}

void	ft_extract_rgb(char *id, char *info, t_data *data)
{
	int		r;
	int		g;
	int		b;
	char	*original_info = info;

	r = extract_next_value(&info);
	g = extract_next_value(&info);
	b = extract_next_value(&info);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error\n");
		printf("RGB values must be between 0 and 255.\n");
		free(original_info);
		free(id);
		exit(0); // changer par free all
	}
	if (ft_compare(id, "c") == 1)
		data->c_rgb = (r << 16) | (g << 8) | b;
	if (ft_compare(id, "F") == 1)
		data->f_rgb = (r << 16) | (g << 8) | b;
	free(original_info);
}
