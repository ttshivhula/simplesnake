/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <ttshivhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:45:10 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/05/07 15:25:53 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "snake.h"

int     boadX = 26;
int     boadY = 26;
int     playerX;
int     playerY;
int     foodX;
int     foodY;
int     bossX;
int     bossY;
int     score = 0;
int     tail = 0;
int     tailX[1000];
int     tailY[1000];
char    command;
int     gameover = 0;
int     mode = 1;
int     level;
int     bossShow = 0;
int     dis;

void    spawnFood(int call)
{
    srand((unsigned)time(0) + call);
    foodX = rand() % boadX;
    if (foodX == 0 || foodX == (boadX - 1))
        spawnFood(++call);
    foodY = rand() % (boadY - 2);
    for (int i = 0; i < boadY; i++)
    {
        for (int j =0; j < boadX; j++)
        {
            if(foodX == tailX[j] && foodY == tailY[i])
                spawnFood(++call);
        }
    }
}

void    spawnBoss(int call)
{
    srand((unsigned)time(0) + call);
    bossX = rand() % boadX;
    if (bossX == 0 || bossX == (boadX - 1))
        spawnBoss(++call);
    bossY = rand() % (boadY - 2);
    for (int i = 0; i < boadY; i++)
    {
        for (int j = 0; j < boadX; j++)
        {
            if (bossY == tailY[i] && bossX == tailX[j])
                spawnBoss(++call);
        }
    }
}

void    input(void)
{
    char temp;
    if (ft_kbhit())
    {
        temp = ft_getch();
        if ((temp == 's' || temp == 'S')&& command != 'w')
            command = 's';
        else if ((temp == 'w' || temp == 'W') && command != 's')
            command = 'w';
        else if ((temp == 'd' || temp == 'D') && command != 'a')
            command = 'd';
        else if ((temp == 'a' || temp == 'A') && command != 'd')
            command = 'a';
    }
}

void    snakeLogic(void)
{
    /*Handle snake tail*/
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = playerX;
    tailY[0] = playerY;
    int prev2X, prev2Y;
    for (int x = 1; x < tail; x++)
    {
        prev2X = tailX[x];
        prev2Y = tailY[x];
        tailX[x] = prevX;
        tailY[x] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    /*Handle inputs*/
    if (command == 'w')
        playerY--;
    else if (command == 's')
        playerY++;
    else if (command == 'd')
        playerX++;
    else if (command == 'a')
        playerX--;
    /*Make sure player doesnt get out of the board, or die when board is hit*/
    if (mode == 1) 
    {
        if (playerY > boadY - 3)
            playerY = 0;
        else if (playerY < 0)
            playerY = boadY - 3;
        else if (playerX > boadX - 2)
            playerX = 1;
        else if (playerX < 1)
            playerX = boadX - 2;
    }
    else
    {
        if (playerY > boadY - 3)
            gameover = 1;
        else if (playerY < 0)
            gameover = 1;
        else if (playerX > boadX - 2)
            gameover = 1;
        else if (playerX < 1)
            gameover = 1;
    }
    /*Die when snake collids with it self*/
    for (int i = 0; i < tail; i++)
    {
        if (tailX[i] == playerX && tailY[i] == playerY)
            gameover = 1;
    }
    /*What happens when snake eats food */
    if (playerX == foodX && playerY == foodY)
    {
        spawnFood(6);
        tail++;
        if (level == 1)
            score+=2;
        else if (level == 2)
            score+=3;
        else if (level == 3)
            score+=4;
        else if (level == 4)
            score+=5;
        else if (level == 5)
            score+=7;
        else if (level == 6)
            score+=8;
        else if (level == 7)
            score+=10;
        /*Handle boss */
        bossShow++;
        if (bossShow == 5)
        {
            spawnBoss(11);
            bossShow = 0;
            dis = 25;
        }
    }
    if (playerX == bossX && playerY == bossY)
    {
        score = score + (level * 3 * dis);
        dis = 1;
    }
    dis--;
    if (dis == 0)
    {
        bossX = boadX + boadX;
        bossY = boadY + boadY;
    }
}

void    init(void)
{   
    spawnFood(7);
    playerX = boadX / 2;
    playerY = (boadY - 2) / 2;
}

void    display(void)
{
    system("clear");
    printf(" # - GAME MODE %d - #\n", mode);
    for (int i = 0; i < boadX; i++)
        printf("# ");
    printf("\n");
    for (int j = 0; j < boadY - 2; j++)
    {
        for (int k = 0; k < boadX; k++)
        {
            if (k == 0)
                printf("# ");
            else if (k == boadX - 1)
                printf("# ");
            else if (k == playerX && j == playerY)
                printf("@ ");
            else if (k == bossX && j == bossY)
                printf("B ");
            else if (k == foodX && j == foodY)
                printf("F ");
            else
                {
                    int printed = 0;
                    for (int x = 0; x < tail; x++)
                    {
                        if (tailX[x] == k && tailY[x] == j)
                        {
                            printf("o ");
                            printed = 1;
                        }
                    }
                    if (printed == 0)
                        printf("  ");
                }
        }
        printf("\n");
    }
    for (int i = 0; i < boadX; i++)
        printf("# ");
    printf("\n");
    if (dis < 0)
        dis = 0;
    printf("SCORE: %d LEVEL: %d\n", score, level);
    for (int i = 0; i < dis; i++)
    {
        printf("+");
        if (i == dis - 1)
            printf("\n");
    }
}

int     main(void)
{  
    system("clear");
    printf("SNAKE v0.0.1\n\nINSTRUCTIONS\n\nUse W A S D to move around\n\nGame contains 2 modes\nMode 1: Pass-through Walls\nMode 2: Death Walls\n\nDeveloped by Tshilidzi Tshivhula\n\n");
    printf("Choose mode (1 and 2):");
    scanf("%d", &mode);
    printf("Choose level (1 - 7):");
    scanf("%d", &level);
    if (level <= 0 || level > 7)
    {
        system("clear");
        printf("Something went wrong.\n");
        return (1);
    }
    init();
    while (gameover == 0)
    {   
        display();
        input();
        snakeLogic();
        if (level == 1)
            usleep(700000);
        else if (level == 2)
            usleep(600000);
        else if (level == 3)
            usleep(500000);
        else if (level == 4)
            usleep(400000);
        else if (level == 5)
            usleep(300000);
        else if (level == 6)
            usleep(200000);
        else if (level == 7)
            usleep(100000);
    }
    printf("GAME OVER: you scored %d points.\n", score);
    return (0);
}
