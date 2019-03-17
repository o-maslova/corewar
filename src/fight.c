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
		make_frame(VIS->main_win, COLOR_PAIR(FRAME));
		make_frame(VIS->info_win, COLOR_PAIR(FRAME));
		that_color = VIS->paint_arena[i].is_st ? COLOR_PAIR(VIS->paint_arena[i].color)
		| A_BOLD | A_UNDERLINE : COLOR_PAIR(VIS->paint_arena[i].color);
		wattron(VIS->main_win, that_color);
		wprintw(VIS->main_win, "%.2x", a->arena[i]);
		wattroff(VIS->main_win, that_color);
		waddch(VIS->main_win, ' ');
		if (VIS->paint_arena[i].is_st > 0)
			VIS->paint_arena[i].is_st--;
		if (VIS->paint_arena[i].i_live > 0)
			VIS->paint_arena[i].i_live--;
	}
	wrefresh(VIS->main_win);
}

void	print_cycle(t_core *a, t_carriage *c, int first_step)
{
	static int	v_time;
	int		o;

	if (v_time == 0)
		VIS->start = clock();
	a->carrs_num = 0;
	c = a->carrs;
	a->n_cycles = !first_step ? a->n_cycles + 1 : a->n_cycles;
	while(c)
	{
		o = carret(c, a, a->arena);
		c = c->next;
		a->carrs_num++;
	}
	if (a->dump && a->n_cycles == a->dump)
	{
		put_colors(a);
		print_arena(a);
		VIS->if_run = false;
	}
	else if (!a->dump || a->n_cycles > a->dump)
	{
		put_colors(a);
		print_arena(a);
	}
	if (v_time == 0)
		VIS->end = clock();
	v_time++;
}

void	check_cyc_per_sec(t_core *a, char ch)
{
	if (ch == MINUS_BIG)
		VIS->c_per_s -= BIG_STEP;
	if (ch == PLUS_BIG)
		VIS->c_per_s += BIG_STEP;
	if (ch == MINUS_SMALL)
		VIS->c_per_s -= SMALL_STEP;
	if (ch == PLUS_SMALL)
		VIS->c_per_s += SMALL_STEP;
	if (VIS->c_per_s < 0)
		VIS->c_per_s = 0;
	if (VIS->c_per_s > 1000)
		VIS->c_per_s = 1000;
}

void	fight(t_core *a, t_carriage *c)
{
	int		ch;

	system("clear");
	initialize(a);
	print_cycle(a, c, 1);
	a->visual_flag = 1;
	VIS->if_run = 0;
	while (a->cycle_to_die > 0 && a->carrs)
	{
		ch = getch();
		check_cyc_per_sec(a, ch);
		if (ch == RUN)
			VIS->if_run = !VIS->if_run;
		else if (ch == ONE_CYCLE_PASS)
		{
			print_cycle(a, c, 0);
			// a->n_cycles++;
			VIS->if_run = false;
		}
		if (VIS->if_run)
		{
			print_cycle(a, c, 0);
			// a->n_cycles++;
		}
		print_info_frame(a);
	}
	dprintf(g_fd, "WINNER - PLAYER №%i\n", a->last_say_live);
}