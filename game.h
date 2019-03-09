#ifndef GAME_H
# define GAME_H
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
typedef struct		s_krest
{
    short int       player_or_bot;// 1 = player // 0 = bot
    char            sym;
	short int       x;
    short int       y;
    short int       win;
    short int       must_go_x;
    short int       must_go_y;
    short int       max_to_win;
    short int       max_x;
    short int       max_y;
    short int       max_gor_ver_dia;
}					t_krest;

typedef struct		s_nol
{
    short int       player_or_bot;
    char            sym;
	short int       x;
    short int       y;
    short int       win;
    short int       must_go_x;
    short int       must_go_y;
    short int       max_to_win;
    short int       max_x;
    short int       max_y;
    short int       max_gor_ver_dia;
}					t_nol;

typedef struct		s_logic
{
    short int       bot_search_pla_pos;
    short int       move;
    char            sym_now;
    short int       who_first;
    short int       bot_mode;
    short int       pve_or_eve;
}					t_logic_game;

typedef struct		s_elem
{
    short int       empty_cell;
    short int       nbr_win;
    char            **map;
    short int       height;
    short int       width;
    short int       run_game;
	t_krest *krest;
    t_nol   *nol;
    t_logic_game *logic;
}					t_elem;

int ft_validate_input(t_elem *s_game, char *tmp_coor, int i);
int ft_move_player(t_elem *s_game);
int ft_move_bot(t_elem *s_game);
int ft_check_if_win(t_elem *s_game, int i, int j);
int ft_bot_can_win(t_elem *s_game, int i, int j);
int ft_check_bot_win(t_elem *s_game, int i, int j);
int ft_check_bot_player_cant_win(t_elem *s_game, int i, int j);
int    ft_check_bot_win_gor(t_elem *s_game, int i, int j, int nbr_win);
int    ft_check_bot_win_ver(t_elem *s_game, int i, int j, int nbr_win);
int    ft_check_bot_win_dia(t_elem *s_game, int i, int j, int nbr_win);
int ft_bot_find_player_best_put(t_elem *s_game);
int ft_bot_last_move(t_elem *s_game, int i, int j);
int ft_bot_interrupt_player(t_elem *s_game);
int ft_bot_interrupt_gor(t_elem *s_game, int i, int j);
int ft_bot_interrupt_ver(t_elem *s_game, int i, int j);
int ft_bot_interrupt_dia_right(t_elem *s_game, int i, int j);
int ft_bot_interrupt_dia_left(t_elem *s_game, int i, int j);
void ft_player_interrupt(t_elem *s_game);
#endif