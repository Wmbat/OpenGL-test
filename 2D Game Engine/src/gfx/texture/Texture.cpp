#include "Texture.h"

#include <stdexcept>

#include <SOIL/SOIL.h>

Texture::Texture( const std::string& filepath )
{
	glGenTextures( 1, &textureID );

	Bind();

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	auto data = SOIL_load_image( filepath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA );

	if( data )
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );
	}
	else
		throw std::runtime_error( "Failed to load texture.\n" );

	SOIL_free_image_data( data );

	Unbind();
}

void Texture::Bind()
{
	glBindTexture( GL_TEXTURE_2D, textureID );
}

void Texture::Unbind()
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}