#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./libft/libft.h"

// int main ()
//{
//	// initscr();
//	// printw("Hello world!");
//	// refresh();
//	// getch();
//	// // raw();
//	// endwin();

//	char mesg[] = "Enter a string: ";
//	char str[80];
//	int row, col;

//	initscr();
//	getmaxyx(stdscr, row, col);
//	mvprintw(row / 2, (col - strlen(mesg))/2, "%s", mesg);
//	getstr(str);
//	mvprintw(LINES - 2, 0, "You entered: %s", str);
//	// printw("Try resizing your window (if possible) and then run this program again");
//	// refresh();
//	getch();
//	endwin();

//	return (0);
//}

// int main(int argc, char **argv)
// {
// 	int row, col;
// 	int fd;
// 	int i, len;
// 	int x, y;
// 	char *line;

// 	argc = 0;
// 	fd = open(argv[1], O_RDONLY);
// 	initscr();
// 	getmaxyx(stdscr, row, col);
// 	while (get_next_line(fd, &line) > 0)
// 	{
// 		getyx(stdscr, y, x);
// 		if (y == (row - 1))
// 		{
// 			printw("<-Press Any Key->");
// 			getch();
// 			clear();
// 			move(0, 0);
// 		}
// 		len = ft_strlen(line);
// 		i = 0;
// 		while (i < len)
// 		{
// 			if (line[i] == '/' && line[i + 1] == '*')
// 			{
// 				attron(A_BOLD);
// 				getyx(stdscr, y, x);
// 				move(y, x - 1);
// 				printw("%c%c", line[i], line[i + 1]);
// 			}
// 			else
// 				printw("%c", line[i]);
// 			if (line[i] == '/' && line[i + 1] == '*')
// 				attroff(A_BOLD);
// 			refresh();
// 			i++;
// 		}
// 		printw("%c", '\n');
// 		refresh();
// 		free(line);
// 	}
// 	endwin();
// 	return (0);
// }

// int main()
// {
// 	initscr();
// 	start_color();

// 	init_pair(1, COLOR_CYAN, COLOR_BLACK);
// 	printw("A Big string sha la la ");
// 	mvchgat(0, 0, -1, A_BLINK | A_DIM, 1, NULL);
// 	/*
//  		* First two parameters specify the position at which to start
//  		* Third parameter number of characters to update. −1 means till
//  		* end of line
//  		* Forth parameter is the normal attribute you wanted to give
//  		* to the charcter
//  		* Fifth is the color index. It is the index given during init_pair()
//  		* use 0 if you didn't want color
//  		* Sixth one is always NULL
//  	*/
// 	refresh();
// 	getch();
// 	endwin();
// 	return (0);
// }
