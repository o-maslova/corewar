#include "corelib.h"

void	print_arena(t_core *a)
{
	int		i;
	int		row;
	int		that_color;

	i = -1;
	row = START_ROW - 1;
	while (++i < MEM_SIZE)
	{
		if ((i % MAINW_ROWS) == 0)
			wmove(VIS->main_win, ++row, 4);
		make_frame(VIS->info_win, COLOR_PAIR(FRAME));
		make_frame(VIS->main_win, COLOR_PAIR(FRAME));
		that_color = ELEM(i).st ? COLOR_PAIR(ELEM(i).color)
		| A_BOLD | A_UNDERLINE : COLOR_PAIR(ELEM(i).color);
		wattron(VIS->main_win, that_color);
		wprintw(VIS->main_win, "%.2x", a->arena[i]);
		wattroff(VIS->main_win, that_color);
		waddch(VIS->main_win, ' ');
	}
	wrefresh(VIS->main_win);
}

void	print_cycle(t_core *a, t_carriage *c, int first_step, int ch)
{
	int			o;
	int			count;
	static int	step;

	a->carrs_num = 0;
	c = a->carrs;
	a->n_cycles = a->n_cycles + first_step;
	while (c)
	{
		o = carret(c, a, a->arena);
		c = c->next;
		a->carrs_num++;
	}
	check_cycles(a);
	if (++step == FOR_VISUAL || first_step == 0 || ch == ONE_CYCLE_PASS)
	{
		print_arena(a);
		step = 0;
	}
	print_info_frame(a);
	put_colors(a);
}

bool	check_cyc_per_sec(t_core *a, char ch)
{
	int tmp;

	tmp = VIS->c_per_s;
	if (ch == MINUS_BIG)
		VIS->c_per_s -= BIG_STEP;
	if (ch == PLUS_BIG)
		VIS->c_per_s += BIG_STEP;
	if (ch == MINUS_SMALL)
		VIS->c_per_s -= SMALL_STEP;
	if (ch == PLUS_SMALL)
		VIS->c_per_s += SMALL_STEP;
	(VIS->c_per_s < 1) && (VIS->c_per_s = 1);
	(VIS->c_per_s > 1000) && (VIS->c_per_s = 1000);
	if (tmp != VIS->c_per_s)
		return (false);
	return (true);
}

void	end_of_game(t_core *a, int ch)
{
	print_arena(a);
	print_info_frame(a);
	ch = wgetch(VIS->main_win);
	if (ch == RUN)
	{
		dprintf(g_fd, "color = %d\n", VIS->p_colors[a->last_say_live - 1]);
		rainbow(a, VIS->p_colors[a->last_say_live - 1]);
		print_arena(a);
	}
	// make_rainbow(a);
	if ((ch = wgetch(VIS->main_win)))
	{
		delwin(VIS->main_win);
		delwin(VIS->info_win);
		endwin();
		system("clear");
		exit(0);
	}
}

void	fight(t_core *a, t_carriage *c)
{
	int		ch;

	system("clear");
	initialize(a);
	print_cycle(a, c, 0, 0);
	print_info_frame(a);
	a->visual_flag = 1;
	VIS->if_run = 0;
	while ((ch = getch()))
	{
		if (a->cycle_to_die > 0 && a->carrs)
		{
			if (!check_cyc_per_sec(a, ch))
				print_info_frame(a);
			// wrefresh(VIS->raduga);
			if (ch == RUN)
				VIS->if_run = !VIS->if_run;
			else if (ch == ONE_CYCLE_PASS)
			{
				// print_info_frame(a);
				print_cycle(a, c, 1, ch);
				VIS->if_run = false;
			}
			if (VIS->if_run)
			{
				// dprintf(g_fd, "sec: %d	clock = %lu\nclock_2 = %lu\n\n", VIS->c_per_s, clock(), SHOW_REGULATOR);
				print_cycle(a, c, 1, ch);
				VIS->vremya = clock();
				// if (a->n_cycles == a->dump)
				// 	VIS->if_run = false;
				// a->n_cycles++;
			}
		}
		else
			end_of_game(a, ch);
	}
}