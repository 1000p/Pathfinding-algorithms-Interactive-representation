#include "InfoComponent.h"
#include "ResourceInitializer.h"

void InfoComponent::handleEvent()
{
}

inline void InfoComponent::init()
{
	ResourceInitializer& resourceInit = ResourceInitializer::getInstance();

	font = resourceInit.getFont();
	std::vector<std::pair<SDL_Rect, SDL_Texture*>> textures;

	//TODO: load needed resources into a vector render them to 
	// new texture and save the texture as a class member
	
}
