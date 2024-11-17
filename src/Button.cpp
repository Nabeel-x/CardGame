#include "Button.h"

void Button::Render() const{
    SDL_SetRenderDrawColor(m_Renderer,m_Color.r,m_Color.g,m_Color.b,m_Color.a);
    SDL_RenderFillRect(m_Renderer,&m_Rect);

    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font,m_Label.c_str(),textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_Renderer,textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture,NULL,NULL,&textWidth,&textHeight);
    SDL_Rect textRect = {
        m_Rect.x + (m_Rect.w - textWidth)/2,
        m_Rect.y + (m_Rect.h - textHeight)/2,
        textWidth, textHeight
    };
    SDL_RenderCopy(m_Renderer,textTexture,NULL,&textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Button::HandleEvent(SDL_Event &e){
    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION){
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX,&mouseY);
        bool isHovered = mouseX > m_Rect.x && mouseX < m_Rect.x + m_Rect.w && mouseY > m_Rect.y && mouseY < m_Rect.y + m_Rect.h;
        if(isHovered){
            if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                if(m_OnClick){
                    m_OnClick();
                }
            }
            m_Color = SDL_COLOR_GREEN;
        }else{
            m_Color = m_DefaultColor;
        }
    }
}

void Button::SetColor(SDL_Color color){
    m_Color = color;
}