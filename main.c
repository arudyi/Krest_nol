#include "game.h"

/*int ft_exit_error(void)
{
    printf("usage:\n");
    printf("./exe x y\n");
    return (0);
}*/

void ft_map_to_screen(t_elem *s_game)
{
    int i;
    int j;

    i = 0;
    printf("  ");
    while (++i <= s_game->width)
        printf("%d ", i);
    printf("X\n");
    i = -1;
    while (++i < s_game->width)
    {
        j = -1;
        printf("%d ", i + 1);
        while (++j < s_game->height)
            printf("%c ", s_game->map[i][j]);
        printf("\n");
    }
    printf("Y\n");
}

int  ft_get_map(t_elem *s_game, int i, int j)
{
    s_game->map = (char**)malloc(sizeof(char *) * s_game->width);
    while (++i < s_game->width)
    {
        j = -1;
        s_game->map[i] = (char*)malloc(sizeof(char) * s_game->height);
        s_game->map[i][s_game->height] = '\0';
        while (++j < s_game->height)
            s_game->map[i][j] = '.';
    }
    return (0);
}

int ft_get_y_pos_player(t_elem *s_game)
{
    int coor;
    char tmp_coor[9];

    printf("please make a move choosing Y from 1 to %d or press 3 to exit\n", s_game->height);
    fgets(tmp_coor, sizeof(tmp_coor), stdin);
    coor = ft_validate_input(s_game, tmp_coor, -1);
    if (coor <= 0 || coor > s_game->height)
        ft_get_y_pos_player(s_game);
    //else if (coor == 3)
      //  exit(1);
    else
    {
        if (s_game->krest->player_or_bot == 1)
            s_game->krest->y = coor - 1;
        else
            s_game->nol->y = coor - 1;
    }
    return (0);
}

int ft_validate_input(t_elem *s_game, char *tmp_coor, int i)
{
    int nbr;

    nbr = 0;
    while (tmp_coor[++i] != '\n')
    {
        if (48 <= tmp_coor[i] && tmp_coor[i] <= 57)
            nbr = nbr * 10 + (tmp_coor[i] - '0');
        else
            return (-1);
    }
    if (nbr <= 0 || nbr > s_game->width)
        return (-1);
    return (nbr);
}

int ft_get_x_pos_player(t_elem *s_game)
{
    int coor;
    char tmp_coor[9];

    printf("please make a move choosing X from 1 to %d or press 3 to exit\n", s_game->width);
    fgets(tmp_coor, sizeof(tmp_coor), stdin);
    coor = ft_validate_input(s_game, tmp_coor, -1);
    if (coor <= 0 || coor > s_game->width)
        ft_get_x_pos_player(s_game);
    //else if (coor == 3)
      //  exit(1);
    else
    {
        if (s_game->krest->player_or_bot == 1)
            s_game->krest->x = coor - 1;
        else
            s_game->nol->x = coor - 1;
    }
    return (0);
}

int ft_validate_sym(char *sym, int i)
{
    int nbr;

    nbr = 0;
    while (sym[++i] != '\n')
    {
        if (48 <= sym[i] && sym[i] <= 57)
            nbr = nbr * 10 + (sym[i] - '0');
        else
            return (-1);
    }
    if (nbr <= 0 || nbr > 3)
        return (-1);
    return (nbr);
}

int ft_get_info_player(t_elem *s_game)
{
    char sym[3];
    int tmp_sym;

    ft_map_to_screen(s_game);
    printf("please 1 to choose X or 2 to choose O or press 3 to exit\n");
    fgets(sym, sizeof(sym), stdin);
    tmp_sym = ft_validate_sym(sym, -1);
    if (tmp_sym <= 0 || tmp_sym > 3)
        ft_get_info_player(s_game);
    else if (tmp_sym == 3)
        exit(1);
    else
    {
        if (tmp_sym == 1)
        {
            s_game->nol->player_or_bot = 0;
            s_game->krest->player_or_bot = 1;
            //ft_get_pos_player1(s_game);
            ft_get_x_pos_player(s_game);
            ft_get_y_pos_player(s_game);
            s_game->map[s_game->krest->y][s_game->krest->x] = 'X';
        }
        else
        {
            s_game->nol->player_or_bot = 1;
            s_game->krest->player_or_bot = 0;
            //ft_get_pos_player2(s_game);
            ft_get_x_pos_player(s_game);
            ft_get_y_pos_player(s_game);
            s_game->map[s_game->nol->y][s_game->nol->x] = 'O';
        }
    }
    //printf("sym = %d\n", sym);
    return (0);
}

void ft_get_info_bot(t_elem *s_game)
{
    short int sym;

    sym = 0 + rand() % 2;
    if (sym == 1) // X
    {
        s_game->krest->x = 1 + rand() % s_game->width;
        s_game->krest->y = 1 + rand() % s_game->height;
        //printf("s_game->nol->x = %d, s_game->nol->y = %d\n", s_game->krest->x, s_game->krest->y);
        s_game->map[s_game->krest->y - 1][s_game->krest->x - 1] = s_game->krest->sym;
        s_game->krest->player_or_bot = 0; // 0 = bot
        s_game->nol->player_or_bot = 1; // 1 = player
    }
    else // O
    {
        s_game->nol->x = 1 + rand() % s_game->width;
        s_game->nol->y = 1 + rand() % s_game->height;
        //printf("s_game->nol->x = %d, s_game->nol->y = %d\n", s_game->nol->x, s_game->nol->y);
        s_game->map[s_game->nol->y - 1][s_game->nol->x - 1] = s_game->nol->sym;
        s_game->krest->player_or_bot = 1;
        s_game->nol->player_or_bot = 0;
    }
}

void ft_first_move(t_elem *s_game)
{
    s_game->krest->sym = 'X';
    s_game->nol->sym = 'O';
    //s_game->who_first = 0 + rand() % 2;
    s_game->logic->who_first = 1;
    if (s_game->logic->who_first == 1) // bot
        ft_get_info_bot(s_game);
    else // player
        ft_get_info_player(s_game);
    ft_map_to_screen(s_game);
}

int ft_get_pos_player(t_elem *s_game)
{
    ft_get_x_pos_player(s_game);
    ft_get_y_pos_player(s_game);
    if (s_game->nol->player_or_bot == 1)
    {
        if (s_game->map[s_game->nol->y][s_game->nol->x] != '.')
        {
            printf("Wrong position !\n");
            ft_get_pos_player(s_game);
        }
        else
            s_game->map[s_game->nol->y][s_game->nol->x] = s_game->nol->sym;
    }
    else
    {
        if (s_game->map[s_game->krest->y][s_game->krest->x] != '.')
        {
            printf("Wrong position !\n");
            ft_get_pos_player(s_game);
        }
        else
            s_game->map[s_game->krest->y][s_game->krest->x] = s_game->krest->sym;
    }
    return (0);
}

int ft_move_player(t_elem *s_game)
{
    ft_get_pos_player(s_game);
    ft_map_to_screen(s_game);
    ft_check_if_win(s_game, -1, -1);
    return (0);
}

int ft_check_gor(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win)/////////////////////////////////////////// j++
            j++;
        if (nbr_win == s_game->nbr_win)
        {
            if (s_game->logic->sym_now == 'X')
                s_game->krest->win = 1;
            else
                s_game->nol->win = 1;
            return (0);
        }
        if (j >= s_game->height)
            return (0); 
        ft_check_gor(s_game, i, j, nbr_win);
    }
    return (0);
}

int ft_check_ver(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win)/////////////////////i++
            i++;
        if (nbr_win == s_game->nbr_win)
        { 
            if (s_game->logic->sym_now == 'X')
                s_game->krest->win = 1;
            else
                s_game->nol->win = 1;
            return (0);
        }
        if (i >= s_game->width)
            return (0);
        ft_check_ver(s_game, i, j, nbr_win);
    }
    return (0);
}

int ft_check_dia_right(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win) /// /i++; j++;
        {
            i++;
            j++;
        }
        if (nbr_win == s_game->nbr_win)
        {
            if (s_game->logic->sym_now == 'X')
                s_game->krest->win = 1;
            else
                s_game->nol->win = 1;
            return (0);
        }
        if (j >= s_game->height || i >= s_game->width)
            return (0);
        ft_check_dia_right(s_game, i, j, nbr_win);
    }
    return (0);
}

int ft_check_dia_left(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win)/////////////i++ j--
        {
            i++;
            j--;
        }
        if (nbr_win == s_game->nbr_win)
        {
            if (s_game->logic->sym_now == 'X')
                s_game->krest->win = 1;
            else
                s_game->nol->win = 1;
            return (0);
        }
        if (j <= -1 || i >= s_game->width)
            return (0);
        ft_check_dia_left(s_game, i, j, nbr_win);
    }
    return (0);
}

int ft_check_every_pos(t_elem *s_game, int i, int j)
{
    ft_check_gor(s_game, i, j, 0);
    ft_check_ver(s_game, i, j, 0);
    ft_check_dia_right(s_game, i, j, 0);
    ft_check_dia_left(s_game, i, j, 0);
    //printf("hi there\n");
    if (s_game->krest->win == 1 || s_game->nol->win == 1)
    {
        (s_game->krest->win == 0) ? printf("nol is winner !\n") : printf("krest is winner !\n");
        exit(1);
    }
    else if (s_game->empty_cell == 1)
    {
        printf("\ndraw :(\n");
        exit(1);
    } 
    return (0);
}

int ft_check_if_win(t_elem *s_game, int i, int j)
{
    while (++i < s_game->width)
    {
        j = -1;
        while (++j < s_game->height)
        {
            if (s_game->map[i][j] != '.')
            {
                s_game->logic->sym_now = s_game->map[i][j];
                ft_check_every_pos(s_game, i, j);
            }
        }
    }
    return (0);
}

void ft_exit_bot_win(t_elem *s_game)
{
    //printf("s_game->krest->must_go_x = %d, s_game->krest->must_go_y = %d\n", s_game->krest->must_go_x, s_game->krest->must_go_y);
    //printf("s_game->nol->must_go_x = %d, s_game->nol->must_go_y = %d\n", s_game->nol->must_go_x, s_game->nol->must_go_y);
    //printf("s_game->krest->sym = %c, s_game->nol->sym = %c\n", s_game->krest->sym, s_game->nol->sym);
    if (s_game->krest->player_or_bot == 0)
        s_game->map[s_game->krest->must_go_x][s_game->krest->must_go_y] = s_game->krest->sym; // x y
    if (s_game->nol->player_or_bot == 0)
        s_game->map[s_game->nol->must_go_x][s_game->nol->must_go_y] = s_game->nol->sym; // x y
    ft_map_to_screen(s_game);
    (s_game->krest->win == 0) ? printf("nol is winner !\n") : printf("krest is winner !\n");
    exit(1);
}

int ft_check_bot_win_gor(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win - 1)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win - 1)
            j++;
        if (j >= s_game->height) // height - 1
            return (0);
        ft_check_bot_win_gor(s_game, i, j, nbr_win);
    }
    else if (nbr_win == s_game->nbr_win - 1)
    {
        if (s_game->krest->player_or_bot == 0)
        {
            if (j == s_game->height - 1)
            {
                if (s_game->map[i][j - nbr_win] == '.')
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i;
                    s_game->krest->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((j + 1) < s_game->width && s_game->map[i][j + 1] == '.') // (j + 1) < s_game->width &&
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i;
                    s_game->krest->must_go_y = j + 1;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((j - nbr_win) >= 0 && s_game->map[i][j - nbr_win] == '.') // (j - nbr_win) >= 0 && 
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i;
                    s_game->krest->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
        else if (s_game->nol->player_or_bot == 0)
        {
            if (j == s_game->height - 1)
            {
                if (s_game->map[i][j - nbr_win] == '.')
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i;
                    s_game->nol->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((j + 1) < s_game->width && s_game->map[i][j + 1] == '.') // (j + 1) < s_game->width &&
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i;
                    s_game->nol->must_go_y = j + 1;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((j - nbr_win) >= 0 && s_game->map[i][j - nbr_win] == '.') // (j - nbr_win) >= 0 && 
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i;
                    s_game->nol->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
    }
    return (0);
}

int ft_check_bot_win_ver(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win - 1)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win - 1)
            i++;
        if (i >= s_game->height)
            return (0);
        ft_check_bot_win_ver(s_game, i, j, nbr_win);
    }
    else if (nbr_win == s_game->nbr_win - 1)
    {
        //printf("i = %d, j = %d\n", i, j);
        if (s_game->krest->player_or_bot == 0)
        {
            if (i == s_game->width - 1)
            {
                if (s_game->map[i - nbr_win][j] == '.')
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i - nbr_win;
                    s_game->krest->must_go_y = j;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((i + 1) < s_game->height && s_game->map[i + 1][j] == '.') // (i + 1) < s_game->height &&
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i + 1;
                    s_game->krest->must_go_y = j;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((i - nbr_win) >= 0 && s_game->map[i - nbr_win][j] == '.') // (i - nbr_win) >= 0 &&
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i - nbr_win;
                    s_game->krest->must_go_y = j;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
        else if (s_game->nol->player_or_bot == 0)
        {
            if (i == s_game->width - 1)
            {
                if (s_game->map[i  - nbr_win][j] == '.')
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i - nbr_win;
                    s_game->nol->must_go_y = j;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((i + 1) < s_game->height && s_game->map[i + 1][j] == '.')
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i + 1;
                    s_game->nol->must_go_y = j;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((i - nbr_win) >= 0 && s_game->map[i - nbr_win][j] == '.')
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i  - nbr_win;
                    s_game->nol->must_go_y = j;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
        return (0);
    }
    return (0);
}

int ft_check_bot_win_dia_right(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win - 1)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win - 1)
        {
            i++;
            j++;
        }
        if (i >= s_game->height || j >= s_game->height)
            return (0);
        ft_check_bot_win_dia_right(s_game, i, j, nbr_win);
    }
    else if (nbr_win == s_game->nbr_win - 1)
    {
        if (s_game->krest->player_or_bot == 0)
        {
            if (i == s_game->width - 1 || j == s_game->width - 1)
            {
                if ((i - nbr_win) >= 0 && (j - nbr_win) >= 0 && s_game->map[i  - nbr_win][j - nbr_win] == '.') // (i - nbr_win) >= 0 && (j - nbr_win) >= 0 &&
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i - nbr_win;
                    s_game->krest->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((i + 1) < s_game->width && (j + 1) < s_game->width && s_game->map[i + 1][j + 1] == '.') // (i + 1) < s_game->width && (j + 1) < s_game->width &&
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i + 1;
                    s_game->krest->must_go_y = j + 1;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((i - nbr_win) >= 0 && (j - nbr_win) >= 0 && s_game->map[i - nbr_win][j - nbr_win] == '.') // (i - nbr_win) >= 0 && (j - nbr_win) >= 0 &&
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i - nbr_win;
                    s_game->krest->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
        else if (s_game->nol->player_or_bot == 0)
        {
            if (i == s_game->width - 1 || j == s_game->width - 1)
            {
                if ((i - nbr_win) >= 0 && (j - nbr_win) >= 0 && s_game->map[i  - nbr_win][j - nbr_win] == '.') // (i - nbr_win) >= 0 && (j - nbr_win) >= 0 &&
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i - nbr_win;
                    s_game->nol->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((i + 1) < s_game->width && (j + 1) < s_game->width &&s_game->map[i + 1][j + 1] == '.') // (i + 1) < s_game->width && (j + 1) < s_game->width &&
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i + 1;
                    s_game->nol->must_go_y = j + 1;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((i - nbr_win) >= 0 && (j - nbr_win) >= 0 && s_game->map[i - nbr_win][j - nbr_win] == '.') // (i - nbr_win) >= 0 && (j - nbr_win) >= 0 &&
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i - nbr_win;
                    s_game->nol->must_go_y = j - nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
    }
    return (0);
}

int ft_check_bot_win_dia_left(t_elem *s_game, int i, int j, int nbr_win)
{
    if (s_game->map[i][j] == s_game->logic->sym_now && nbr_win != s_game->nbr_win - 1)
    {
        nbr_win++;
        if (nbr_win != s_game->nbr_win - 1)
        {
            i++;
            j--;
        }
        if (j <= -1 || i >= s_game->width)
            return (0);
        ft_check_bot_win_dia_left(s_game, i, j, nbr_win);
    }
    else if (nbr_win == s_game->nbr_win - 1)
    {
        if (s_game->krest->player_or_bot == 0)
        {
            if (i == s_game->width - 1 || j == 0)
            {
                if ((i - nbr_win) >= 0 && (j + nbr_win) < s_game->width && s_game->map[i - nbr_win][j + nbr_win] == '.') // if (s_game->map[i + nbr_win][j + nbr_win] == '.') //
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i - nbr_win;
                    s_game->krest->must_go_y = j + nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((i + 1) < s_game->width && (j - 1) >= 0 && s_game->map[i + 1][j - 1] == '.') // (i + 1) < s_game->width && (j - 1) >= 0 &&
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i + 1;
                    s_game->krest->must_go_y = j - 1;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((i - nbr_win) >= 0 && (j + nbr_win) < s_game->width && s_game->map[i - nbr_win][j + nbr_win] == '.') //// if (s_game->map[i + nbr_win][j + nbr_win] == '.') //
                {
                    s_game->logic->move = 1;
                    s_game->krest->must_go_x = i - nbr_win;
                    s_game->krest->must_go_y = j + nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->krest->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
        else if (s_game->nol->player_or_bot == 0)
        {
            if (i == s_game->width - 1 || j == 0)
            {
                if ((i - nbr_win) >= 0 && (j + nbr_win) < s_game->width && s_game->map[i - nbr_win][j + nbr_win] == '.') // (i - nbr_win) >= 0 && (j + nbr_win) < s_game->width &&
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i - nbr_win;
                    s_game->nol->must_go_y = j + nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
            else
            {
                if ((i + 1) < s_game->width && (j - 1) >= 0 &&s_game->map[i + 1][j - 1] == '.') // (i + 1) < s_game->width && (j - 1) >= 0 &&
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i + 1;
                    s_game->nol->must_go_y = j - 1;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
                else if ((i - nbr_win) >= 0 && (j + nbr_win) < s_game->width && s_game->map[i - nbr_win][j + nbr_win] == '.') // (i - nbr_win) >= 0 && (j + nbr_win) < s_game->width &&
                {
                    s_game->logic->move = 1;
                    s_game->nol->must_go_x = i - nbr_win;
                    s_game->nol->must_go_y = j + nbr_win;
                    if (s_game->logic->bot_search_pla_pos == 0)
                    {
                        s_game->nol->win = 1;
                        ft_exit_bot_win(s_game);
                    }
                }
            }
        }
    }
    return (0);
}

int ft_check_bot_win(t_elem *s_game, int i, int j)
{
    ft_check_bot_win_gor(s_game, i, j, 0);
    ft_check_bot_win_ver(s_game, i, j, 0);
    ft_check_bot_win_dia_right(s_game, i, j, 0);
    ft_check_bot_win_dia_left(s_game, i, j, 0);
    return (0);
}

int ft_bot_can_win(t_elem *s_game, int i, int j)
{
    s_game->logic->sym_now = (s_game->krest->player_or_bot == 0) ? s_game->krest->sym : s_game->nol->sym;
    while (++i < s_game->width)
    {
        j = -1;
        while (++j < s_game->height)
        {
            if (s_game->map[i][j] == s_game->logic->sym_now) //s_game->map[i][j] != '.' && 
                ft_check_bot_win(s_game, i, j);
        }
    }
    return (0);
}

int ft_check_bot_player_cant_win(t_elem *s_game, int i, int j)
{
    //printf("HI\n");
    if (s_game->logic->move == 0)
        ft_check_bot_win_gor(s_game, i, j, 0);
    //printf("HI\n");
    if (s_game->logic->move == 0)
        ft_check_bot_win_ver(s_game, i, j, 0);
    //printf("HI\n");
    if (s_game->logic->move == 0)
        ft_check_bot_win_dia_right(s_game, i, j, 0);
    if (s_game->logic->move == 0)
        ft_check_bot_win_dia_left(s_game, i, j, 0);
    return (0);
}

int ft_bot_player_cant_win(t_elem *s_game, int i, int j)
{
    s_game->logic->sym_now = (s_game->krest->player_or_bot == 1) ? s_game->krest->sym : s_game->nol->sym;
    while (++i < s_game->width)
    {
        j = -1;
        while (++j < s_game->height)
        {
            if (s_game->map[i][j] == s_game->logic->sym_now)
                ft_check_bot_player_cant_win(s_game, i, j);
            if (s_game->logic->move == 1)
            {
                if (s_game->krest->player_or_bot == 0)
                    s_game->map[s_game->krest->must_go_x][s_game->krest->must_go_y] = s_game->krest->sym;
                else
                    s_game->map[s_game->nol->must_go_x][s_game->nol->must_go_y] = s_game->nol->sym;
                break ;
            }
        }
        if (s_game->logic->move == 1)
            break ;
    }
    return (0);
}

void ft_check_if_win_smaller(t_elem *s_game, int max, int i, int j, short int gor_ver_dia)
{
    if (max != s_game->nbr_win - 1)
    {
        if (s_game->logic->sym_now == s_game->krest->sym)
        {
            if (max < s_game->krest->max_to_win)
            {
                s_game->krest->max_gor_ver_dia = gor_ver_dia;
                s_game->krest->max_to_win = max;
                s_game->krest->max_x = i;
                s_game->krest->max_y = j;
            }
        }
        else
        {
            if (max < s_game->nol->max_to_win)
            {
                s_game->nol->max_gor_ver_dia = gor_ver_dia;
                s_game->nol->max_to_win = max;
                s_game->nol->max_x = i;
                s_game->nol->max_y = j;
            }
        }
    }
}

int find_gor(t_elem *s_game, int i, int j)
{
    short int searching_right;
    short int searching_left;
    short int k;
    short int max;
    short int is_space;

    is_space = 0;
    max = s_game->nbr_win - 1;
    k = 0;
    searching_right = 1;
    searching_left = 1;
    while (searching_right == 1 || searching_left == 1)
    {
        k++;
        if ((j + k) >= s_game->width)
            searching_right = 0;
        if ((j - k) < 0)
            searching_left = 0;
        if (searching_right == 1)
        {
            if (s_game->map[i][j + k] == s_game->logic->sym_now)
                max--;
            if (s_game->map[i][j + k] == ' ')
            {
                if ((j + k + 1) < s_game->width && s_game->map[i][j + k] == ' ' && s_game->map[i][j + k + 1] == s_game->logic->sym_now && is_space++ == 0)
                    max--;
                else
                    searching_right = 0;
            }
            if (s_game->map[i][j + k] != s_game->logic->sym_now && s_game->map[i][j + k] != ' ')
                searching_right = 0;
        }
        if (searching_left == 1)
        {
            if (s_game->map[i][j - k] == s_game->logic->sym_now)
                max--;
            if (s_game->map[i][j - k] == ' ')
            {
                if ((j - k - 1) >= 0 && s_game->map[i][j - k] == ' ' && s_game->map[i][j - k - 1] == s_game->logic->sym_now && is_space++ == 0)
                    max--;
                else
                    searching_right = 0;
            }
            if (s_game->map[i][j - k] != s_game->logic->sym_now && s_game->map[i][j - k] != ' ')
                searching_right = 0;
        }
        ft_check_if_win_smaller(s_game, max, i, j, 0);
    }
    return (0);
}

int find_ver(t_elem *s_game, int i, int j)
{
    short int searching_right;
    short int searching_left;
    short int k;
    short int max;
    short int is_space;

    is_space = 0;
    max = s_game->nbr_win - 1;
    k = 0;
    searching_right = 1;
    searching_left = 1;
    while (searching_right == 1 || searching_left == 1)
    {
        k++;
        if ((i + k) >= s_game->width)
            searching_right = 0;
        if ((i - k) < 0)
            searching_left = 0;
        if (searching_right == 1)
        {
            if (s_game->map[i + k][j] == s_game->logic->sym_now)
                max--;
            if (s_game->map[i + k][j] == ' ')
            {
                if ((i + k + 1) < s_game->width && s_game->map[i + k][j] == ' ' && s_game->map[i + k + 1][j] == s_game->logic->sym_now && is_space++ == 0)
                    max--;
                else
                    searching_right = 0;
            }
            if (s_game->map[i + k][j] != s_game->logic->sym_now && s_game->map[i + k][j] != ' ')
                searching_right = 0;
        }
        if (searching_left == 1)
        {
            if (s_game->map[i - k][j] == s_game->logic->sym_now)
                max--;
            if (s_game->map[i - k][j] == ' ')
            {
                if ((i - k - 1) >= 0 && s_game->map[i - k][j] == ' ' && s_game->map[i - k - 1][j] == s_game->logic->sym_now && is_space++ == 0)
                    max--;
                else
                    searching_right = 0;
            }
            if (s_game->map[i - k][j] != s_game->logic->sym_now && s_game->map[i - k][j] != ' ')
                searching_right = 0;
        }
        ft_check_if_win_smaller(s_game, max, i, j, 1);
    }
    return (0);
}

int find_dia_right(t_elem *s_game, int i, int j)
{
    return (0);
}

int find_gor_left(t_elem *s_game, int i, int j)
{
    return (0);
}

int ft_find_max(t_elem *s_game, int i, int j)
{
    find_gor(s_game, i, j);
    find_ver(s_game, i, j);
    find_dia_right(s_game, i, j);
    find_gor_left(s_game, i, j);
    return (0);
}

int ft_find_max_to_win_player_bot(t_elem *s_game, int i, int j)
{
    // find_max_to_win_player;
    s_game->krest->max_to_win = 3;
    s_game->nol->max_to_win = 3;
    s_game->logic->sym_now = (s_game->krest->player_or_bot == 1) ? s_game->krest->sym : s_game->nol->sym;
    while (++i < s_game->width)
    {
        j = -1;
        while (++j < s_game->height)
        {
            if (s_game->map[i][j] == s_game->logic->sym_now)
                ft_find_max(s_game, i, j);
        }
    }
    //find_max_to_win_bot;
    s_game->logic->sym_now = (s_game->krest->player_or_bot == 0) ? s_game->krest->sym : s_game->nol->sym;
    i = -1;
    while (++i < s_game->width)
    {
        j = -1;
        while (++j < s_game->height)
        {
            if (s_game->map[i][j] == s_game->logic->sym_now)
                ft_find_max(s_game, i, j);
        }
    }
    printf("s_game->krest->max_to_win = %d, s_game->nol->max_to_win = %d\n", s_game->krest->max_to_win, s_game->nol->max_to_win);
    return (0);
}

int ft_bot_find_player_best_put(t_elem *s_game)
{
    ft_find_max_to_win_player_bot(s_game, -1, -1);
    return (0);
}

int ft_if_exist_empty_cells(t_elem *s_game, int i, int j, int gor_ver_dia)
{
    short int nbr_empty_cells;
    short int searching_left;
    short int searching_right;
    short int k;

    k = 0;
    searching_left = 1;
    searching_right = 1;
    nbr_empty_cells = 0;
    if (gor_ver_dia == 0)
    {
        while (searching_left == 1 || searching_right == 1)
        {
            k++;
            if ((j + k) >= s_game->width)
                searching_right = 0;
            if ((j - k) < 0)
                searching_left = 0;
            if (searching_right == 1)
            {
                if (s_game->map[i][j + k] == '.')
                    nbr_empty_cells++;
                else
                    searching_right = 0;
            }
            if (searching_left == 1)
            {
                if (s_game->map[i][j - k] == '.')
                    nbr_empty_cells++;
                else
                    searching_left = 0;
            }
            if (nbr_empty_cells >= s_game->nbr_win - 1)
                break ;
        }
        if (nbr_empty_cells >= s_game->nbr_win - 1)
            return (1);
        else
            return (0);
    }
    else if (gor_ver_dia == 1)
    {
        while (searching_left == 1 || searching_right == 1)
        {
            k++;
            if ((i + k) >= s_game->width)
                searching_right = 0;
            if ((i - k) < 0)
                searching_left = 0;
            if (searching_right == 1)
            {
                if (s_game->map[i + k][j] == '.')
                    nbr_empty_cells++;
                else
                    searching_right = 0;
            }
            if (searching_left == 1)
            {
                if (s_game->map[i - k][j] == '.')
                    nbr_empty_cells++;
                else
                    searching_left = 0;
            }
            if (nbr_empty_cells >= s_game->nbr_win - 1)
                break ;
        }
        if (nbr_empty_cells >= s_game->nbr_win - 1)
            return (1);
        else
            return (0);
    }
    else if (gor_ver_dia == 2)
    {
        while (searching_left == 1 || searching_right == 1)
        {
            k++;
            if ((i - k) < 0 || (j + k) >= s_game->width)
                searching_right = 0;
            if ((i + k) >= s_game->width || (j - k) < 0)
                searching_left = 0;
            if (searching_right == 1)
            {
                if (s_game->map[i - k][j + k] == '.')
                    nbr_empty_cells++;
                else
                    searching_right = 0;
            }
            if (searching_left == 1)
            {
                if (s_game->map[i + k][j - k] == '.')
                    nbr_empty_cells++;
                else
                    searching_left = 0;
            }
            if (nbr_empty_cells >= s_game->nbr_win - 1)
                break ;
        }
        if (nbr_empty_cells >= s_game->nbr_win - 1)
            return (1);
        else
            return (0);
    }
    else if (gor_ver_dia == 3)
    {
        while (searching_left == 1 || searching_right == 1)
        {
            k++;
            if ((i + k) >= s_game->width || (j + k) >= s_game->width)
                searching_right = 0;
            if ((i - k) < 0 || (j - k) < 0)
                searching_left = 0;
            if (searching_right == 1)
            {
                if (s_game->map[i + k][j + k] == '.')
                    nbr_empty_cells++;
                else
                    searching_right = 0;
            }
            if (searching_left == 1)
            {
                if (s_game->map[i - k][j - k] == '.')
                    nbr_empty_cells++;
                else
                    searching_left = 0;
            }
            if (nbr_empty_cells >= s_game->nbr_win - 1)
                break ;
        }
        if (nbr_empty_cells >= s_game->nbr_win - 1)
            return (1);
        else
            return (0);
    }
    return (0);
}

int ft_bot_find_best_pos(t_elem *s_game, int i, int j)
{
    if ((j + 1) < s_game->width && s_game->map[i][j + 1] == '.' && ft_if_exist_empty_cells(s_game, i, j, 0) == 1)
    {
        s_game->map[i][j + 1] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    if ((j - 1) >= 0 && s_game->map[i][j - 1] == '.' && s_game->logic->move == 0 && ft_if_exist_empty_cells(s_game, i, j, 0) == 1)
    {
        s_game->map[i][j - 1] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    if ((i + 1) < s_game->width && s_game->map[i + 1][j] == '.' && s_game->logic->move == 0 && ft_if_exist_empty_cells(s_game, i, j, 1) == 1)
    {
        s_game->map[i + 1][j] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    if ((i - 1) >= 0 && s_game->map[i - 1][j] == '.' && s_game->logic->move == 0 && ft_if_exist_empty_cells(s_game, i, j, 1) == 1)
    {
        s_game->map[i - 1][j] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    if ((i - 1) >= 0 && (j + 1) < s_game->width && s_game->logic->move == 0 && s_game->map[i - 1][j + 1] == '.' && ft_if_exist_empty_cells(s_game, i, j, 2) == 1)
    {
        s_game->map[i - 1][j + 1] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    if ((i - 1) >= 0 && (j - 1) >= 0 && s_game->logic->move == 0 && s_game->map[i - 1][j - 1] == '.' && ft_if_exist_empty_cells(s_game, i, j, 3) == 1)
    {
        s_game->map[i - 1][j - 1] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    if ((i + 1) < s_game->width && (j - 1) >= 0 && s_game->logic->move == 0 && s_game->map[i + 1][j - 1] == '.' && ft_if_exist_empty_cells(s_game, i, j, 2) == 1)
    {
        s_game->map[i + 1][j - 1] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    if ((i + 1) < s_game->width && (j + 1) < s_game->width && s_game->logic->move == 0 && s_game->map[i + 1][j + 1] == '.' && ft_if_exist_empty_cells(s_game, i, j, 3) == 1)
    {
        s_game->map[i + 1][j + 1] = s_game->logic->sym_now;
        s_game->logic->move = 1;
    }
    return (0);
}

int ft_bot_last_move(t_elem *s_game, int i, int j)
{
    s_game->logic->sym_now = (s_game->krest->player_or_bot == 0) ? s_game->krest->sym : s_game->nol->sym ;
    while (++i < s_game->width)
    {
        j = -1;
        while (++j < s_game->height)
        {
            if (s_game->map[i][j] == s_game->logic->sym_now)
                ft_bot_find_best_pos(s_game, i, j);
            if (s_game->logic->move == 1)
                break ;
        }
        if (s_game->logic->move == 1)
            break ;
    }
    if (s_game->logic->move == 0)
    {
        i = -1;
        while (++i < s_game->width)
        {
            j = -1;
            while (++j < s_game->height)
            {
                if (s_game->map[i][j] == s_game->logic->sym_now)
                {
                    if ((j + 1) < s_game->width && s_game->map[i][j + 1] == '.')
                    {
                        s_game->map[i][j + 1] = s_game->logic->sym_now;
                        s_game->logic->move = 1;
                    }
                    else if ((j - 1) >= 0 && s_game->map[i][j - 1] == '.' && s_game->logic->move == 0)
                    {
                        s_game->map[i][j - 1] = s_game->logic->sym_now;
                        s_game->logic->move = 1;
                    }
                    else if ((i + 1) < s_game->width && s_game->map[i + 1][j] == '.' && s_game->logic->move == 0)
                    {
                        s_game->map[i + 1][j] = s_game->logic->sym_now;
                        s_game->logic->move = 1;
                    }
                    else if ((i - 1) >= 0 && s_game->map[i - 1][j] == '.' && s_game->logic->move == 0)
                    {
                        s_game->map[i - 1][j] = s_game->logic->sym_now;
                        s_game->logic->move = 1;
                    }
                }
                if (s_game->logic->move == 1)
                    break ;
            }
            if (s_game->logic->move == 1)
                break ;
        }
    }
    return (0);
}

int ft_get_pos_bot(t_elem *s_game)
{
    s_game->logic->move = 0;
    s_game->logic->bot_search_pla_pos = 0;
    ft_bot_can_win(s_game, -1, -1);
    s_game->logic->move = 0;
    s_game->logic->bot_search_pla_pos = 1;
    ft_bot_player_cant_win(s_game, -1, -1);
    if (s_game->logic->move == 0)
        ft_bot_find_player_best_put(s_game);
    if (s_game->logic->move == 0)
        ft_bot_last_move(s_game, -1, -1);
    return (0);
}

int ft_move_bot(t_elem *s_game)
{
    ft_get_pos_bot(s_game);
    ft_map_to_screen(s_game);
    ft_check_if_win(s_game, -1, -1);
    return (0);
}

int ft_start_game(t_elem *s_game)
{
    ft_first_move(s_game);
    s_game->run_game = 1;
    while (s_game->run_game)
    {
        if (s_game->logic->who_first == 1)
        {
            ft_move_player(s_game);
            ft_move_bot(s_game);
        }
        else
        {
           ft_move_bot(s_game);
           ft_move_player(s_game);
        }
    }
    return (0);
}

int main(void)
{
    srand(time(NULL));
    t_elem *s_game;

    if (!(s_game = (t_elem*)malloc(sizeof(t_elem))))
        exit(0);
    if (!(s_game->krest = (t_krest*)malloc(sizeof(t_krest))))
        exit(0);
    if (!(s_game->nol = (t_nol*)malloc(sizeof(t_nol))))
        exit(0);
    if (!(s_game->logic = (t_logic_game *)malloc(sizeof(t_logic_game))))
        exit(0);
    /*if (ac != 3)
        return (ft_exit_error());*/
    s_game->width = 8;
    s_game->height = 8;
    s_game->nbr_win = 4;
    s_game->krest->win = 0;
    s_game->nol->win = 0;
    s_game->empty_cell = 0;
    //    who_first = 1 = bot // who_first = 0 = (player or bot1)
    //printf("s_game->who_first = %d\n", s_game->who_first);
    ft_get_map(s_game, -1, -1);
    ft_start_game(s_game);
    return (0);
}