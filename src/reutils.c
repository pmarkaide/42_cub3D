/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:38:43 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/06 07:48:12 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// void print_map(t_macro *macro)
// {
//     int i = 0;
//     while (macro->map[i] != NULL)
//     {
//         int j = 0;
//         while (macro->map[i][j])
//         {
//             if (j == macro->start_x && i == macro->start_y)
//                 printf("%c", macro->orientation);
//             else
//                 printf("%c", macro->map[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
// }

// //Parseador temporal: BORRAR
// char** parse_map(const char* filename, int* rows, int* cols) {
//     FILE* file = fopen(filename, "r");
//     if (!file) {
//         perror("Failed to open file");
//         return NULL;
//     }

//     // Determine the number of rows and columns
//     char buffer[256];
//     *rows = 0;
//     *cols = 0;
//     while (fgets(buffer, sizeof(buffer), file)) {
//         if (*cols == 0) {
//             *cols = strlen(buffer) - 1; // Exclude newline character
//         }
//         (*rows)++;
//     }

//     // Allocate memory for the map
//     char** map = (char**)malloc((*rows + 1) * sizeof(char*));
//     if (!map) {
//         perror("Failed to allocate memory");
//         fclose(file);
//         return NULL;
//     }

//     // Read the file again to fill the map
//     rewind(file);
//     for (int i = 0; i < *rows; i++) {
//         map[i] = (char*)malloc((*cols + 1) * sizeof(char)); // +1 for null terminator
//         if (!map[i]) {
//             perror("Failed to allocate memory");
//             fclose(file);
//             return NULL;
//         }
//         fgets(map[i], *cols + 2, file); // +2 to include newline and null terminator
//         map[i][*cols] = '\0'; // Remove newline character
//     }
// 	map[*rows] = NULL;
//     fclose(file);
//     return map;
// }
