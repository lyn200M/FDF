#include "manager.h"

int	manager_start_processing(char argv[])
{
	void *p_connection_id;
	void	*p_window_id;
	t_size	window_size;
	t_size	*p_window_size;
	t_window_config	window_config;
	t_window_config	*p_window_config;
	char *window_title;

	window_title = "fdf_1";
	p_window_size = &window_size;
	p_window_size->x = 1920;
	p_window_size->y = 1080;
	p_connection_id = engine_init_connection();
	report_connection_x_server(p_connection_id);
	p_window_config = init_window_config(p_connection_id, p_window_size, window_title);
	p_window_id = engine_create_window(p_window_config);
	report_create_window(p_window_id);

	void	*img;
	char	c = 48;
	char 	*p_c = &c;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = 0;
	green = 0;
	blue = 0;

	t_color	color = {0, 0, 0}, *p_color = &color;
	//int	colori = red << 16 | green << 8 | blue;
	//printf("color value is : %d %#x\n", color, color);
	//t_pixel pixel = {p_connection_id, p_window_id, 720, 720, color};
	//t_pixel *p_pixel = &pixel;
	t_param	parm = {p_connection_id, p_window_id, img, p_window_size->x, p_window_size->y, p_c, p_color};
	t_param	*param = &parm;
	//mlx_expose_hook(p_window_id, engine_expose_win, (void *)param);                                                    
	//mlx_key_hook(p_window_id, engine_key_event, param);
	mlx_mouse_hook(p_window_id, engine_mouse_event, param);
	//engine_check_endian();
	//engine_display_pixel(p_pixel);
	mlx_loop(p_connection_id);
        return (0);
	
}                                                                                 

t_window_config	*init_window_config(void *p_connection_id, t_size *p_window_size, char *window_title)
{
	t_window_config	*p_window_config;
	t_window_config	window_config;

	p_window_config = &window_config;
	p_window_config->p_connection_id = p_connection_id;
	p_window_config->title = window_title;
	p_window_config->p_window_size = p_window_size;
	return (p_window_config);
}