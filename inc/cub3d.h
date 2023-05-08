
#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
# include "../minilibx_opengl_20191021/mlx.h"
# else
	# include "../minilibx-linux/mlx.h"
# endif

# include <math.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.14159265
# define X 0
# define Y 1
# define EXACT_X 3
# define EXACT_Y 4
# define X1 0
# define Y1 1
# define X2 2
# define Y2 3
# define X3 4
# define Y3 5
# define X4 6
# define Y4 7
# define START_X_WALL 0
# define END_X_WALL 1
# define DX_FOR_WALL 2
# define DEST 0
# define SRC 1
# define START_Y 0
# define COLOR 2
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4
# define M 0
# define B 1
# define WIDTH_WALL 64
# define HEIGHT_WALL 64

# ifdef __APPLE__
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define LINUX 0
# else
	# define W 119
	# define A 97
	# define S 115
	# define D 100
	# define ESC 65307
	# define ARROW_LEFT 65361
	# define ARROW_RIGHT 65363
	# define LINUX 1
# endif

# define DISPLAY_WIDTH 1000
# define DISPLAY_HEIGHT 600
# define LEN_CAM_VEC 1
# define LEN_LEFT_FOV 0.65 // 0,65 und 1 sind 33° -> fov von zusammen 66° gut für first person
# define FACTOR_WALL_HEIGHT 1
# define STEPSIZE 0.3
# define PLAYER_ROTATION_DEG 15
# define DISTANCE_FROM_WALL 0.3

//**				TEXT OUTPUT							**//

# define STR_PROG_NAME "Cub3D:"

# define ERROR_1 "Couldn't open Cub3D file!\n"
# define ERROR_2 "Invalid Cub3D file: Use .cub file extension!\n"

# define CHECK_TEX_1 "Couldn't open path of texture!\n"
# define CHECK_TEX_2 "Invalid path of texture: Use .xpm texture extension!\n"
# define CHECK_TEX_3 "Error: Invalid value for red!\nUse a value between 0 and 255.\n"
# define CHECK_TEX_4 "Error: Invalid value for green!\nUse a value between 0 and 255.\n"
# define CHECK_TEX_5 "Error: Invalid value for blue!\nUse a value between 0 and 255.\n"
# define CHECK_TEX_6 "Invalid map: Only ceiling and floor allowed!\n"
# define CHECK_TEX_7 "Invalid map: There needs to be a ceiling and a floor!\n"

# define CHECK_MAP_1 "Error: Found empty line in map!\n"
# define CHECK_MAP_2 "Invalid map!\n"
# define CHECK_MAP_3 "Invalid character in map!\n"
# define CHECK_MAP_4 "Map should be surrounded by wall (top)!\n"
# define CHECK_MAP_5 "Fix wall on the top!\n"
# define CHECK_MAP_6 "Map should be surrounded by wall (bottom)!\n"
# define CHECK_MAP_7 "Fix wall on the bottom!\n"
# define CHECK_MAP_8 "Map should be surrounded by wall (right)!\n"
# define CHECK_MAP_9 "Fix wall on the right!\n"
# define CHECK_MAP_10 "Map should be surrounded by wall (left)!\n"
# define CHECK_MAP_11 "Fix wall on the left!\n"
# define CHECK_MAP_12 "Too many players!\nOnly one player is allowed in map.\n"
# define CHECK_MAP_13 "There is no player in map!\n"
# define CHECK_MAP_14 "Invalid map: Only four cardinal directions allowed!\n"

# define RAYCAST "Error in cardinal direction!\n"

//*********************************************************//
//**                    STRUCTURES                      **//
//*******************************************************//

typedef struct s_player
{
	double	pos[2];
	double	cam_vec[2];
	double	dpx;
	double	left_fov[2];
}	t_player;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_textures
{
	char		*path_no;
	char		*path_ea;
	char		*path_so;
	char		*path_we;
	char		*red;
	char		*green;
	char		*blue;
	int			red_int;
	int			green_int;
	int			blue_int;
	//int			ceiling_color;
	//int			floor_color;
}				t_textures;

typedef struct s_info
{
	char	*map_path;
	int		row;
	char	**map;
	int		map_i;
	t_textures	txt;
	int		floor;
	int		ceiling;
	int		player_amount;
	int		player_x;
	int		player_y;
	char	player_orientation;

	int			mapsize[2];
	int			**map_int;
	double		*dist_arr;
	int			**dist_info;
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		*north;
	t_img		*east;
	t_img		*south;
	t_img		*west;
	t_img		*img;
	t_player	*p;
}			t_info;

//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

/* ft_rd_map.c */
int			count_nb_row(char *map_path);
char		**save_map(t_info *info);

/* ft_parser.c */

bool		valid_map_extension(t_info *info);
void		skip_empty_lines(t_info *info);
bool		check_valid_map(t_info *info);
bool		amount_player(int	amount_player);
bool		parsing(t_info *info);

/* ft_check_valid_textures.c */

void    ft_save_path_texture(t_info *info, char *map, char x);
bool    check_valid_textures(t_info *info);
bool	ft_texture_extension_helper(char *path_texture);
bool	valid_texture_extension(t_info *info);

/* ft_check_valid_textures_2.c */

void    ft_letter_to_rgb(t_info *info, char *map);
bool    ft_rgb_int_converter(t_info *info);
bool    ft_fc_helper(t_info *info, int i);
bool    check_valid_fc(t_info *info);

/* ft_check_valid_map.c */

bool    valid_lines(t_info *info, int i);
bool    is_allowed_char(t_info *info, char c);
bool    filled_line(t_info *info, int i);
bool    correct_char(t_info *info, int i, int j);
bool	init_player_pos(t_info *info, char c, int i, int j);

/* ft_check_walls.c */

bool		no_zero_top(t_info *info, int i, int j);
bool		no_zero_bottom(t_info *info, int i, int j);
bool		no_zero_right(t_info *info, int i, int j);
bool		no_zero_left(t_info *info, int i, int j);
bool		zero_middle(t_info *info, int i, int j);

/* ft_check_walls_2.c */

bool		horizontal_correct(t_info *info, int i, int j, int var);
bool		vertical_correct(t_info *info, int i, int j, int var);

/* ft_map_converter.c */

int 	**map_converter(t_info *info);
void	convert_player_pos_dir(t_info *info);

//**** ft_draw_textures_2.c ****//

void	fill_background(int	ceiling, int floor, t_img *img);
int		get_color_from_img(t_img *img, double x, double y);
t_img	*get_wall_ptr(int width_pixel, int **dist_info, t_info *info);
double	calc_dx_for_wall(double *start_end_wall, int *corners);
void	draw_one_vertical_line(t_img **img_ptr, double *start_end_wall, \
	int *corners, int act_x);

//**** ft_draw_textures_3.c ****//

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		argb(int alpha, int red, int green, int blue);

//**** ft_draw_textures.c ****//

int		next_tile_on_display_x(int act_x_on_display, t_info *info);
void	calc_end_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info);
void	calc_start_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info);
void	calc_corners_of_wall(int *corners, int width_pixel, \
	double *dist_arr, t_info *info);
void	draw_wall_textures(t_info *info, int width_pixel);

//**** ft_clean_up_2.c ****//

void	clean_up_map_int(t_info *info);
void	clean_up_dist_info(t_info *info);
void	clean_up_dist_arr(t_info *info);
void	clean_up_char_map(t_info *info);
void	clean_up_p(t_info *info);

//**** ft_clean_up_3.c ****//

t_info	*clean_up_info(t_info *info);
void	clean_up_map_path(t_info *info);
t_img	*clean_up_one_texture(t_img *img, t_info *info);
void	clean_up_textures(t_info *info);
void	clean_up_mlx_ptr_win(t_info *info);

//**** ft_clean_up.c ****//

void	clean_up_map_int(t_info *info);
void	clean_up_dist_info(t_info *info);
void	clean_up_char_map(t_info *info);
void	clean_up_textures(t_info *info);
void	clean_up_txt_colors(t_info *info);
int		ft_free_destroy(t_info *info);

# ifdef __APPLE__
void	mlx_loop_end(void *mlx_ptr);
# endif

//**** ft_init_info.c ****//

t_info	*init_info(void);

//**** ft_init.c ****//

int		**init_dist_arr(t_info *info);
void	init_mlx_window_first_screen(t_info *info);
t_info	*init_info_player_images();
void	get_properties_from_mlx_img(void *img_ptr, t_img *img);
void	init_mlx_and_textures(t_info *info);

//**** linear_analysis.c ****//

double	slope(double *one, double *two);
int		func_from_points(double *one, double *two, double *func);
double	y_from_x(double x, double *func);
double	x_from_y(double y, double *func);
double	len_between_two_points(double x1, double y1, double x2, double y2);

//**** move_2.c ****//

void	move_backward(t_info *info);
void	move_left(t_info *info);
void	move_right(t_info *info);
void	rotate_left(t_info *info);
void	rotate_right(t_info *info);

//**** move.c ****//

double	betrag(double value);
void	move_x(double *move_vec, t_info *info);
void	move_y(double *move_vec, t_info *info);
void	move(double *move_vec, t_info *info);
void	move_forward(t_info *info);

//**** raycast_scan.c ****//

void	field_of_view(double *cam_vec, double *left_fov);
double	calc_diff_fov(double *left_fov);
void	calc_left_px_vec(double *left_px_vec, t_player *p);
void	calc_px_vec(double *px_vec, double *left_px_vec, t_player *p, int i);
void	raycast_scan_in_fov(t_info *info, t_player *p);

//**** raycast_scan.c ****//

int	cardinal_direction_of_tile(int col, int row, double *pos);
void	write_next_grid_pt_to_hit_coordinates(int *hit_coordinates, \
	double *dest);
double	calc_len(double *dest, double *position);

//**** raycast.c ****//

int		next_int_value_in_dir(double pos, double dir);
void	next_grid_point(double *dest, double *pos, double *dir, double *func);
int		find_correct_box(double pos, double dir);
int		hit(double *pos, double *dir, t_info *info, int *hit_coordinates);
double	raycast(double *position, double *cast_dir, \
	t_info *info, int *hit_coordinates);

//**** test_utils.c ****//

void	print_dist_arr_info(t_info *info);
void	print_2d_arr(int **array, int row, int col);
void	draw_wallshadows(double *dist_arr, t_img *img);

//**** vec_ops_2.c ****//

void	pvec(double *vec);
void	cpy_vec(double *dest, double *src);
void	subtract_vec(double *dest, double *src);
double	dot_prod_vec(double *one, double *two);
double	calc_angle_vec(double *one, double *two);

//**** vec_ops.c ****//

double	len_vec(double *vec);
void	norm_vec(double *vec);
void	rot_vec(double *vec, double rot);
void	mult_vec(double *vec, double factor);
void	add_vec(double *dest, double *src);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//**** ft_message.c ****//

void	message(char *str);

#endif