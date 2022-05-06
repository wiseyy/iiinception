#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

class Texture{
public:
	// Constructor and Deconstructor 
	Texture(); 
	~Texture();
	// Helps in creating a texture from a file
	bool loadfromFile(std::string path, SDL_Renderer* gRenderer);
	// Dealocating the texture
	void free();
	// Get Dimensions of the texture
	int getHeight();
	int getWidth();
	// Get the Texture 
	SDL_Texture* getTexture();
	// Edit the private attributes 
	void setDimensions(int w, int h);
	void setTexture(SDL_Texture* tex); 
	// render the texture
	void render(int x, int y, SDL_Renderer* gRenderer);
private:
	int height;
	int width;
	SDL_Texture* texture; 
};

// Initializing using a Constructor
Texture::Texture(){
	texture = NULL;
	width = 0;
	height = 0;
}

// Deallocating using a Deconstructor
Texture::~Texture(){
	free();
}

bool Texture::loadfromFile( std::string path , SDL_Renderer* gRenderer){
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL ){
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

//Free texture if it exists. Also set the dimensions to zero 
void Texture::free(){
	if(texture != NULL){
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	width = 0;
	height = 0;
}

// Get Dimensions of the texture
int Texture::getHeight(){
	return height;
}
int Texture::getWidth(){
	return width;
}

// Get the texture in the Texture object
SDL_Texture* Texture::getTexture(){
	return texture; 
}
// Setting the dimensions for a texture
void Texture::setDimensions(int w, int h){
	height = h;
	width = w ;
}
// Setting private attribute texture
void Texture::setTexture(SDL_Texture* tex){
	texture = tex;
}
// Render the texture
// void Texture::render(int x,int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	// //Set rendering space and render to screen
	// SDL_Rect renderQuad = {x, y, width, height};

	// //Set clip rendering dimensions
	// if(clip != NULL)
	// {
	// 	renderQuad.w = clip->w;
	// 	renderQuad.h = clip->h;
	// }

// 	//Render to screen
// 	SDL_RenderCopyEx( gRenderer, texture, clip, &renderQuad, angle, center, flip );
// }

void Texture::render(int x, int y, SDL_Renderer* gRenderer){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, width, height};
	// 	//Render to screen
	SDL_RenderCopy( gRenderer, texture, NULL, &renderQuad);
}