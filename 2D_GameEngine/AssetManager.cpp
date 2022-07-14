#include "AssetManager.h"
#include "ECS/Components.h"

//set the 'manager' variable in the .h file to point to the manager
AssetManager::AssetManager(Manager* man) : manager(man) {}

//destructor
AssetManager::~AssetManager() {

}


void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	//automatically create a pointer to a projectile entity and add it to the manager vector
	auto& projectile(manager->addEntity());
	//add the transform component to the entity at current position with size of the image as well as the scale
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	//id for the projectile which adds it to the asset manager
	projectile.addComponent<SpriteComponent>(id, false);
	//add the projectile component to make this a projectile entity
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	//add the projectile to the label of "projectile" to be used with collision detection
	projectile.addComponent<ColliderComponent>("projectile");
	//add the projectile to a group called groupProjectiles to be used with rendering (and collisions I'm sure)
	projectile.addGroup(Game::groupProjectiles);
}


//add texture to a map
void AssetManager::AddTexture(std::string id, const char* path){
	//add a texture with id to the end of the vector (located in .h file)
	textures.emplace(id, TextureManager::LoadTexture(path));

}

//retrieve a texture from a map
SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

//add a font style to the map
void AssetManager::AddFont(std::string id, std::string path, int fontSize){
	//	.str() produces an STL string, and then.c_str() returns a const char* to the guts of the STL string, 
	//	which SDL, a pretty firmly C library, expects.
	//	in this case, path can correspond to a string
	//	https://stackoverflow.com/questions/13096758/how-add-variables-to-string-for-ttf-rendertext-solid
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

//retrieve a font style from the map
TTF_Font* AssetManager::GetFont(std::string id){
	return fonts[id];
}

