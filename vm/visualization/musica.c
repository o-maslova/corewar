/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musica.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:41:03 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:41:07 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		define_music(t_core *a)
{
	static char *tmp;

	VIS->music.is_start = true;
	tmp = "afplay /./vm/music/";
	VIS->music.m_fight = ft_strjoin(tmp, "epic.mp3 &> /dev/null &");
	VIS->music.magic = ft_strjoin(tmp, "boogie.mp3 &> /dev/null &");
}

void		play_music(t_core *a, int what_now)
{
	if (what_now == MUS_FIGHT)
		system(VIS->music.m_fight);
	else if (what_now == MUS_MAGIC)
	{
		if (VIS->music.is_start)
			system("pkill afplay");
		system(VIS->music.magic);
	}
	else if (what_now == MUS_END)
		system("pkill afplay");
}
