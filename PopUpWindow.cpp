#include "PopUpWindow.h"

#include "ResourceInitializer.h"

#include "SDL_image.h"

PopUpWindow::PopUpWindow(MainWindow* owner, Uint32 windowFlags) :
    owner(owner)
{
    int mouseX, mouseY;
    SDL_GetGlobalMouseState(&mouseX, &mouseY);
    window = SDL_CreateWindow("Choose algorithm", mouseX, mouseY,
        114, 30, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
        | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    ResourceInitializer& resourceInit = ResourceInitializer::getInstance();
    //Font in with which we will render text
    TTF_Font* font = resourceInit.getFont();
    SDL_Color textColor{ 0,0,0 };

    //Add components
    SDL_Surface* text = TTF_RenderText_Blended(font, "A STAR", textColor);
    SDL_Texture* textT = SDL_CreateTextureFromSurface(renderer, text);
    SDL_FreeSurface(text);

    SDL_Rect dst{ 0,0,114,30 };
    SDL_Rect textDst{ 0,0,90,20 };
    textDst.x = dst.x + ((dst.w - textDst.w) / 2);
    textDst.y = dst.y + ((dst.h - textDst.h) / 2);

    SDL_Texture* button = IMG_LoadTexture(renderer, "Source/yellow_button.png");
    components.emplace_back(new ButtonComponent(std::make_pair(dst, button), std::make_pair(textDst, textT),
        ButtonType::A_STAR_ALGORITHM, owner, renderer));

    render();

}

void PopUpWindow::handleEvent(SDL_Event* evt)
{
    for (auto comp : components)
    {
        comp->handleEvent(evt);
    }

}

void PopUpWindow::render()
{
    SDL_RenderClear(renderer);
    for (auto comp : components)
    {
        comp->render(renderer, NULL);
    }
    SDL_RenderPresent(renderer);
}

void PopUpWindow::close()
{
    SDL_SetWindowGrab(window, SDL_FALSE);
    for (auto comp : components)
    {
        comp->destroy();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
