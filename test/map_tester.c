#include "../include/cub3D.h"

void test_map(char *file)
{
	t_macro macro;

	ft_bzero(&macro, sizeof(t_macro));
	validate_map_file(file, &macro);
	ft_printf(1, "Map %s is valid\n", file);
	free_and_exit(&macro);
}

int main(void)
{
	test_map("maps/valid_subject.cub");
	test_map("maps/invalid_missing_no_texture.cub");
	test_map("maps/invalid_duplicated_elements.cub");
	test_map("maps/invalid_incorrect_map_characters.cub");
	test_map("maps/invalid_map_not_surrounded_by_walls.cub");

	return (0);
}
