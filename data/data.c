/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnyamets <lnyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:42:04 by lnyamets          #+#    #+#             */
/*   Updated: 2023/10/19 14:44:04 by lnyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	data_open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0);
	return (fd);
}

void	data_read_file(t_file *p_file)
{
	int		read_count;
	int		prev_read_count;

	p_file->file_str = NULL;
	prev_read_count = 0;
	p_file->first_line = 0;
	p_file->row = 0;
	p_file->col = 0;
	read_count = 1;
	while (read_count != 0)
	{
		ft_memset(p_file->buf, 0, BUFSIZE);
		read_count = read(p_file->fd, p_file->buf, BUFSIZE);
		if (read_count != 0)
		{
			p_file->file_str = ft_concat(p_file, prev_read_count, read_count);
			if (p_file->file_str == NULL)
				return ;
			prev_read_count += read_count;
			p_file->row = count_row(p_file->buf, p_file->row);
			if (p_file->col == 0 || p_file->first_line != -1)
				p_file->first_line = count_col(p_file->buf, &(p_file->col));
		}
	}
	return ;
}

void	data_store_file_in_matrix(t_file *p_file, t_matrix *p_matrix)
{
	p_matrix->row = p_file->row;
	p_matrix->col = p_file->col;
	allocate_matrix(p_matrix);
	if (p_matrix->matrix == NULL)
	{
		report_exit_program(ALLOCATED_ERROR);
		return ;
	}
	if (init_matrix_with_file(p_matrix, p_file->file_str) != 1)
	{
		report_exit_program(DATA_STRUCT_INIT_ERROR);
		p_matrix->matrix = NULL;
		return ;
	}
}

int	init_matrix_with_file(t_matrix *p_matrix, char *str)
{
	t_init_m		init;
	t_point_color	point;

	init_t_init(&init);
	init_s_point_color(&point, 0, 1);
	while (*str != '\0')
	{
		str = data_process_token(&init, p_matrix, str, &point);
		if (str == NULL)
			return (RETURN_CODE_ZERO);
	}
	return (RETURN_CODE_ONE);
}

int	put_str_to_int(t_init_m init_m, t_point_color *z_color)
{
	char			*current;
	char			*token;

	current = (char *)malloc(1 + init_m.end - init_m.start);
	ft_strncpy(current, init_m.start, init_m.end - init_m.start);
	current[init_m.end - init_m.start] = '\0';
	token = ft_strtok(current, ",");
	if (token != NULL)
		z_color->z = ft_atoi(token);
	else
	{
		free(current);
		return (RETURN_CODE_ZERO);
	}
	token = ft_strtok(NULL, ",");
	if (token != NULL)
		data_extract_rgb(ft_strtol(token, NULL, 16), &(z_color->color.red),
			&(z_color->color.green), &(z_color->color.blue));
	else
		init_s_point_color(z_color, 255, 0);
	free(current);
	return (RETURN_CODE_ONE);
}
