#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./libft/libft.h"

WINDOW	*create_newwin(int heigth, int width, int start_y, int start_x)
{
	WINDOW *local_win;

	local_win = newwin(heigth, width, start_y, start_x);
	box(local_win, 0, 0);
	wborder(local_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wrefresh(local_win);
	return (local_win);
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

int		main()
{
	WINDOW *my_win;
	int start_x, start_y, width, heigth;
	int ch;
	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	heigth = 3;
	width = 10;
	start_y = (LINES - heigth) / 2;
	start_x = (COLS - width) / 2;
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(heigth, width, start_y, start_x);
	while ((ch = getch()) != KEY_F(1))
	{
		switch(ch)
		{
			case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(heigth, width, start_y, --start_x);
				break ;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(heigth, width, start_y, start_x++);
				break ;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(heigth, width, --start_y, start_x);
				break ;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(heigth, width, ++start_y, start_x);
				break ;
		}
	}
	endwin();
	return (0);
}