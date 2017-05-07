/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <ttshivhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:40:56 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/05/07 09:46:04 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_H
# define SNAKE_H

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int     ft_getch(void);
int     ft_kbhit(void);
void    spawnFood(int call);
void    spawnBoss(int call);
void    display(void);
void    snakeLogic(void);
void    input(void);

#endif
