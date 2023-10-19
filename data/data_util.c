/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnyamets <lnyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:15:08 by lnyamets          #+#    #+#             */
/*   Updated: 2023/10/19 14:35:38 by lnyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

char	*data_process_token(t_init_m *init, t_matrix *p_matrix,
	char *str, t_point_color *point)
{
	str = util_skip_whitespace(str);
	if (*str != '\0')
		init->start = str;
	str = util_skip_to_next_token(str);
	if (*str == 32 || *str == '\0' || *str == '\n')
	{
		init->end = str;
		if (init->row < p_matrix->row && init->col < p_matrix->col)
		{
			init_s_point_color(point, 0, 1);
			if (put_str_to_int(*init, point))
				(p_matrix->matrix)[init->row][init->col] = *point;
		}
		else if (init->row == p_matrix->row && init->col == 0)
			return (NULL);
		if (*str == 32)
			init->col++;
		str = util_skip_whitespace(str);
		if (*str == '\n')
			util_increment(init, &str);
	}
	return (str);
}

void	data_extract_rgb(int rgbValue, int *red, int *green, int *blue)
{
	*red = (rgbValue >> 16) & 255;
	*green = (rgbValue >> 8) & 255;
	*blue = rgbValue & 255;
}
