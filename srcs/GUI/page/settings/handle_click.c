// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   handle_click.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/04/20 15:59:19 by lle-duc           #+#    #+#             */
// /*   Updated: 2026/04/20 18:15:53 by lle-duc          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static int is_mouse_pos_inside_button(SDL_Rect mouseCoords, SDL_Rect buttonCoords)
{
    if (mouseCoords.x < buttonCoords.x || mouseCoords.x > buttonCoords.x  + buttonCoords.w)
        return 0;
    if (mouseCoords.y < buttonCoords.y || mouseCoords.y > buttonCoords.y  + buttonCoords.h)
        return 0;
    return 1;
}

static int grab_fov(t_game *game, t_settings_menu *menu, SDL_MouseButtonEvent *MouseDatas)
{
    SDL_Rect mouseCoords = {MouseDatas->x - (1920 - 1044) / 2, MouseDatas->y - 136, 0, 0};
    SDL_Rect sliderCoords = {menu->slider_grab.x, menu->slider_grab.y, menu->slider_grab.w/6, menu->slider_grab.h/6};
    to_responsive(game->window, &mouseCoords);
    to_responsive(game->window, &sliderCoords);
    if (!is_mouse_pos_inside_button(mouseCoords, sliderCoords))
        return (0);
    ft_printf("Yes im here and %d and %d\n", MouseDatas->state, SDL_PRESSED);
    if (MouseDatas->state == SDL_PRESSED)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            ft_printf("Yes im inside while\n");
                
            if (event.type != SDL_PRESSED)
                continue;
            if (event.motion.state == SDL_RELEASED)
                return (1);
            menu->scroll_grab.x += event.motion.xrel;
            ft_printf("New pos = %d\n", menu->scroll_grab.x);
            if (menu->scroll_grab.x < (game->window->w * 200) / 1920)
                menu->scroll_grab.x = 200;
            else if (menu->scroll_grab.x > (game->window->w * 680) / 1920)
                menu->scroll_grab.x = 680;
            draw_settings_menu(game);
        }
    }
    return (1);
}

void handle_click(t_game *game, t_settings_menu *menu, SDL_MouseButtonEvent *MouseDatas)
{
    if (grab_fov(game, menu, MouseDatas))
        return;
}