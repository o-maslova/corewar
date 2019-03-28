#include "corelib.h"

static void			delete(t_core *a)
{
	free(VIS);
	delwin(VIS->main_win);
	delwin(VIS->stat_win);
	delwin(VIS->info_win);
	endwin();
	system("clear");
	exit(0);
}

static void		end_of_game(t_core *a, int ch)
{
	if (ch == EXIT)
		delete(a);
	ft_memset(VIS->rnbw, -1, (sizeof(short) * MAINW_ROWS / 2 + 1));
	print_cycle(a, 1, 0);
	print_side_frame(a);
	ch = wgetch(VIS->main_win);
	if (ch == RUN)
	{
		rainbow(a, VIS->p_colors[a->last_say_live - 1]);
		print_arena(a, FRAME);
		print_side_frame(a);
	}
	if ((ch = wgetch(VIS->main_win)))
		delete(a);
}

void			print_arena(t_core *a, int frame)
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
		that_color = ELEM(i).st ? COLOR_PAIR(ELEM(i).color)
		| A_BOLD | A_UNDERLINE : COLOR_PAIR(ELEM(i).color);
		wattron(VIS->main_win, that_color);
		wprintw(VIS->main_win, "%.2x", a->arena[i]);
		wattroff(VIS->main_win, that_color);
		waddch(VIS->main_win, ' ');
	}
	wrefresh(VIS->main_win);
}

void			print_cycle(t_core *a, int first_step, int ch)
{
	pass_cycle(a);
	a->n_cycles = a->n_cycles + first_step;
	if (ch == ONE_CYCLE_PASS)
	{
		VIS->if_run = true;
		print_side_frame(a);
	}
	print_arena(a, FRAME);
	put_colors(a);
}

void			visual_fight(t_core *a)
{
	int		ch;

	system("clear");
	initialize(a);
	print_cycle(a, 0, 0);
	a->visual_flag = 1;
	VIS->if_run = 0;
	while ((ch = getch()) != EXIT && a->cycle_to_die > 0)
	{
		if (ch == RUN)
			VIS->if_run = !VIS->if_run;
		else if (ch == ONE_CYCLE_PASS)
		{
			print_cycle(a, 1, ch);
			VIS->if_run = false;
		}
		if (VIS->if_run && clock() >= SHOW_REGULATOR)
		{
			VIS->vremya = clock();
			print_cycle(a, 1, ch);
		}
		check_cyc_per_sec(a, ch);
		print_side_frame(a);
	}
	end_of_game(a, ch);
}