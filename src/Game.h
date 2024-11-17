#ifndef GAME_H_
#define GAME_H_
#include "header.h"
#include "Button.h"

class Game{
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    TTF_Font* m_Font;
    bool m_IsRunning;
    std::vector<Button> m_Buttons;
    SDL_Event m_Event;
    void m_HandleEvents();
    void m_Update();
    void m_Render();
public:
    void Init();
    void Clean();
    void Run();
};

#endif