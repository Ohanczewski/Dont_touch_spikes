#include "Animation.h"

Animation::Animation() 
{

}

Animation::Animation(sf::Texture& texture, sf::Vector2u imageCount_, float switchTime_)
{
	imageCount = imageCount_;
	switchTime = switchTime_;
	totalTime = 0.f;
	currentImage.x = 0;
	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

Animation::~Animation() 
{

}

void Animation::update(int row, float dt) 
{
	currentImage.y = row;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}