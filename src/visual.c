#include <curses.h>
#include "libft.h"
#include "op.h"
#include "corelib.h"
#include "visualization.h"

static void				print_info2(t_core *a, int row)
{
	int			i;
	t_player	*tmp;

	i = 0;
	tmp = a->players;
	while (tmp)
	{
		mvwprintw(VIS->info_win, (row += 2), 4, "Player -%d : ", tmp->number);
		wattron(VIS->info_win, COLOR_PAIR(VIS->clr[tmp->number - 1].st_clr));
		wprintw(VIS->info_win, "%.*s", tmp->prog_name);
		wattroff(VIS->info_win, COLOR_PAIR(VIS->clr[tmp->number - 1].st_clr));
		mvwprintw(VIS->info_win, ++row, 6, "Last live :\t\t\t%-*d",
		CLEAR_LINE, a->n[i]);
		mvwprintw(VIS->info_win, ++row, 6, "Lives in current period :\t\t%-*d",
		CLEAR_LINE, a->live_in_p[i++]);
		tmp = tmp->next;
	}
	mvwprintw(VIS->info_win, (row += 2), 4, "CYCLE_TO_DIE :\t%-*d",
	CLEAR_LINE, a->cycle_to_die);
	mvwprintw(VIS->info_win, (row += 2), 4, "CYCLE_DELTA :\t%-*d",
	CLEAR_LINE, CYCLE_DELTA);
	mvwprintw(VIS->info_win, (row += 2), 4, "NBR_LIVE :\t\t%-*d",
	CLEAR_LINE, NBR_LIVE);
	mvwprintw(VIS->info_win, (row += 2), 4, "MAX_CHECKS :\t%-*d",
	CLEAR_LINE, MAX_CHECKS);
}

void	print_arr(t_core *a)
{
	int i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
			dprintf(g_fd, "\n");
		else
		{
			dprintf(g_fd, "%d  ", VIS->paint_arena[i].default_clr);
		}
	}
}

void	print_info_frame(t_core *a)
{
	static int	tmp;
	int		row;
	int		i;

	row = START_ROW;
	i = -1;
	wattron(VIS->info_win, A_BOLD);
	// wattron(VIS->info_win, COLOR_PAIR(COLOR_WHITE));
	mvwprintw(VIS->info_win, HEIGTH - 4, 4,
	"%-*s", CLEAR_LINE, (VIS->if_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(VIS->info_win, row, 4, "Cycles/second limit :\t%-*d", CLEAR_LINE, VIS->c_per_s);
	mvwprintw(VIS->info_win, (row += 3), 4, "Cycle :\t\t%-*d",
	CLEAR_LINE, (a->n_cycles));
	// if (a->n_cycles - 1 == 3947 && tmp == 0)
	// {
	// 	print_arr(a);
	// 	tmp++;
	// }
	mvwprintw(VIS->info_win, (row += 2), 4, "Processes :\t\t%-*d",
	CLEAR_LINE, a->carrs_num);
	// wattroff(VIS->info_win, COLOR_PAIR(COLOR_WHITE) | A_BOLD);
	print_info2(a, row);
	// wattroff(VIS->info_win, COLOR_PAIR(COLOR_WHITE));
	wrefresh(VIS->info_win);
}

void	make_frame(WINDOW *win, int color)
{
	wattron(win, color | A_BOLD);
	wborder(win, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR);
	wattroff(win, color | A_BOLD);
}

void	put_player_colors(t_core *a)
{
	int			i;
	int			step;
	t_player	*tmp;

	i = 0;
	tmp = a->players;
	step = 0;
	while (i < MEM_SIZE)
	{
		while (tmp && i < tmp->length + step)
			VIS->paint_arena[i++].default_clr = VIS->clr[tmp->number - 1].st_clr;
		if (tmp)
		{
			step += PLAYER_FIELD;
			tmp = tmp->next;
		}
		if (!tmp && a->num_pl % 2 != 0)
			step++;
		while (i < step)
			VIS->paint_arena[i++].default_clr = VIS->clr[COLOR_NUM - 1].st_clr;
	}
}

t_carriage		*search_carriage(t_core *a, int pos)
{
	t_carriage	*tmp;

	tmp = a->carrs;
	while (tmp)
	{
		if (tmp->pos == pos)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		put_colors(t_core *a)
{
	int			i;
	int			diff;
	int			pl;
	t_carriage	*tmp;

	i = -1;
	diff = 1;
	while (++i < MEM_SIZE)
	{
		if (i >= diff * PLAYER_FIELD)
			diff++;
		if (VIS->paint_arena[i].not_in_field != 0)
			VIS->paint_arena[i].not_in_field--;
		if (VIS->paint_arena[i].not_in_field == 0)
		{
			VIS->paint_arena[i].color = VIS->paint_arena[i].default_clr;
			dprintf(g_fd, "not int field %d\n", VIS->paint_arena[i].not_in_field);
		}
		tmp = search_carriage(a, i);
		if (VIS->paint_arena[i].i_live > 0 && VIS->paint_arena[i].not_in_field == 0)
		{
			if (a->n_cycles == 11222)
			{
				print_arr(a);
				dprintf(g_fd, "default: %d, color: %d\n", VIS->paint_arena[i].default_clr, VIS->paint_arena[i].color);
			}
			VIS->paint_arena[i].color = VIS->paint_arena[i].default_clr + 1;
		}
		else if (tmp)
		{
			if (VIS->paint_arena[i].default_clr == VIS->clr[COLOR_NUM - 1].st_clr)
				VIS->paint_arena[i].color = VIS->clr[COLOR_NUM - 1].c_clr;
			else
				VIS->paint_arena[i].color = VIS->paint_arena[i].default_clr - 1;
		}
		
	}
}

void	create_col_pairs(t_core *a)
{
	t_color		*tmp;
	int			indx;
	int			clr_indx;
	int			num_of_pair;
	short		p_colors[COLOR_NUM * 2] = {
		COLOR_LRED, COLOR_BLACK,
		COLOR_PURPLE, COLOR_BLACK,
		COLOR_GREEN, COLOR_BLACK,
		COLOR_BIRUSA, COLOR_BLACK,
		8, COLOR_BLACK
	};
	indx = -1;
	clr_indx = 0;
	num_of_pair = 0;
	tmp = VIS->clr;
	while (++indx < COLOR_NUM)
	{
		num_of_pair += 10;
		tmp[indx].c_clr = num_of_pair++;
		init_pair(tmp[indx].c_clr, p_colors[clr_indx + 1], p_colors[clr_indx]);
		tmp[indx].st_clr = num_of_pair++;
		init_pair(tmp[indx].st_clr, p_colors[clr_indx], p_colors[clr_indx + 1]);
		tmp[indx].live_clr = num_of_pair;
		init_pair(tmp[indx].live_clr, COLOR_WHITE, p_colors[clr_indx]);
		clr_indx += 2;
	}
}

void	initialize(t_core *a)
{
	// dprintf(g_fd, "CHECK HERE22\n");
	VIS = (t_win *)ft_memalloc(sizeof(t_win));
	VIS->if_run = false;
	VIS->vremya = clock();
	VIS->c_per_s = ST_CYC_PER_SEC;
	// dprintf(g_fd, "clock = %lu\nclock_2 = %d", VIS->vremya, tmp);
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	// use_default_colors(); //делает фон по цвету терминала
	// dprintf(g_fd, "change color %d\n", can_change_color());
	start_color();
	init_pair(FRAME, COLOR_OHRA, COLOR_OHRA);
	VIS->main_win = newwin(HEIGTH, MAIN_WDTH, 0, 0);
	make_frame(VIS->main_win, COLOR_PAIR(FRAME));
	VIS->info_win = newwin(HEIGTH, INFO_WDTH, 0, MAIN_WDTH - 1);
	make_frame(VIS->info_win, COLOR_PAIR(FRAME));
	create_col_pairs(a);
	put_player_colors(a);
	put_colors(a);
	refresh();
}
