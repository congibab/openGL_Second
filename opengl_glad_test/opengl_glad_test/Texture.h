#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <stb_image.h>

class Texture
{
public:
	Texture(char const *filename);
	unsigned int getTexture() { return texture; };
private:
	unsigned int texture;
};

