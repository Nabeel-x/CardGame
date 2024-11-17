#include "Game.h"


void Game::Init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if(TTF_Init() < 0){
        std::cerr << "TTF initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    m_Window = SDL_CreateWindow(
        "CardGame",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );
    m_Renderer = SDL_CreateRenderer(
        m_Window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    m_Font = TTF_OpenFont("assets/fonts/arial.ttf",16);
    if(!m_Window || !m_Renderer){
        std::cerr << "SDL Initialization failed" << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    if(!m_Font){
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    m_IsRunning = true;
    m_Buttons.emplace_back(Button(m_Renderer,m_Font,SDL_Rect{200,200,100,30},SDL_COLOR_BLACK,"Start Server",[](){
        std::cout << "Server Button Clicked" << std::endl;
    }));
    m_Buttons.emplace_back(Button(m_Renderer,m_Font,SDL_Rect{200,250,100,30},SDL_COLOR_RED,"Exit",[this](){
        std::cout << "Exit Button Clicked" << std::endl;
        m_IsRunning = false;
    }));
    m_Buttons.emplace_back(Button(m_Renderer,m_Font,SDL_Rect{200,300,100,30},SDL_COLOR_BLACK,"Join Client",[](){
        std::cout << "Client Button Clicked" << std::endl;
    }));
    m_Buttons.emplace_back(Button(m_Renderer,m_Font,SDL_Rect{200,350,100,30},SDL_COLOR_BLUE,"Hawk Tuah",[](){
        std::cout << "Hawk Tuah!!!" << std::endl;
    }));
}



void Game::m_HandleEvents(){
    while(SDL_PollEvent(&m_Event)){
        if(m_Event.type == SDL_QUIT){
            m_IsRunning = false;
        }
        for(auto& button: m_Buttons){
            button.HandleEvent(m_Event);
        }
    }

}

void Game::m_Update(){
    return;
}

void Game::m_Render(){
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);
    for(const auto& button : m_Buttons){
        button.Render();
    }
    SDL_RenderPresent(m_Renderer);
}

void Game::Run(){
    while(m_IsRunning){
        m_HandleEvents();
        m_Update();
        m_Render();
    }
}

void Game::Clean(){
    TTF_CloseFont(m_Font);
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    TTF_Quit();
    SDL_Quit();
}
