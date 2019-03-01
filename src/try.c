#include <ncurses.h>
#include "libft.h"
#include "op.h"
#include "corelib.h"
#include "visualization.h"

WINDOW	*create_newwin(int heigth, int width, int start_y, int start_x)
{
	WINDOW *win;

	win = newwin(heigth, width, start_y, start_x);
	box(win, 0, 0);
	wborder(win, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR);
	wrefresh(win);
	return (win);
}

void	destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are
		* 1. win: the window on which to operate
		* 2. ls: character to be used for the left side of the window
		* 3. rs: character to be used for the right side of the window
		* 4. ts: character to be used for the top side of the window
		* 5. bs: character to be used for the bottom side of the window
		* 6. tl: character to be used for the top left corner of the window
		* 7. tr: character to be used for the top right corner of the window
		* 8. bl: character to be used for the bottom left corner of the window
		* 9. br: character to be used for the bottom right corner of the window
	*/
	wrefresh(local_win);
	delwin(local_win);
}

void	make_frame(WINDOW *win)
{
	wattron(win, COLOR_PAIR(FRAME));
	wborder(win, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR);
	wattroff(win, COLOR_PAIR(FRAME));
}

void	start_window(WINDOW **win)
{
	int		width, heigth;
	// char *line;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	heigth = 100;
	width = 100;
	// start_y = (LINES - heigth) / 2;
	// start_x = (COLS - width) / 2;
	*win = create_newwin(heigth, width, 0, 0);
}