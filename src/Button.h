#pragma once
#ifndef BUTTON_H_
#define BUTTON_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <functional>

const SDL_Color SDL_COLOR_GREEN = {0,255,0,255};
const SDL_Color SDL_COLOR_RED = {255,0,0,255};
const SDL_Color SDL_COLOR_BLUE = {0,0,255,255};
const SDL_Color SDL_COLOR_BLACK = {0,0,0,255};
const SDL_Color SDL_COLOR_WHITE = {255,255,255,255};

class Button{
private:
    SDL_Renderer* m_Renderer;
    TTF_Font* m_Font;
    SDL_Rect m_Rect;
    SDL_Color m_Color;
    SDL_Color m_DefaultColor;
    std::string m_Label;
    std::function<void()> m_OnClick;
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect rect, SDL_Color color,const std::string& label, std::function<void()> onClick):
    m_Renderer(renderer), m_Font(font), m_Rect(rect), m_Color(color), m_DefaultColor(color), m_Label(label), m_OnClick(onClick) {}
    void Render() const;
    void HandleEvent(SDL_Event &e);
    void SetColor(SDL_Color color);
};
#endif