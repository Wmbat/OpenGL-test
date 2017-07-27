#pragma once

#include <glm/glm.hpp>

#include "../buffers/VertexArray.h"
#include "../../shader/Shader.h"

#include "../structs/Structs.h"

class Renderable
{
public:
	Renderable() = default;

	Renderable( const Position& position, const GLf_Size& size, unsigned short type = 0 )
		: position( position ), size( size ), currentType( type ) {	}

	Renderable( const Position& position, const GLf_Size& size, const Colour& colour, unsigned short type = 0 )
		: position( position ), size( size ), colour( colour ), currentType( type ) {	}

	Renderable( const Position& p1, const Position& p2, const Colour& colour, unsigned short type = 1 )
		: p1( p1 ), p2( p2 ), colour( colour ), currentType( type ) {	}

	Renderable( const Position& p1, const Position& p2, const Position& p3, const Colour& colour, unsigned short type = 0 )
		: p1( p1 ), p2( p2 ), p3( p3 ), colour( colour ), currentType( type ) {	}

	virtual ~Renderable() = default;

	virtual void Render( Shader& shader ) = 0;

	const glm::vec3 GetPosition( ) const { return static_cast<glm::vec3>( position ); }

	Renderable& operator=( Renderable&& renderable ) = default;

	void SetType( int type ) { currentType = type; }

protected:
	void RenderIndices( )
	{
		IBO.Bind();

		if( currentType == ShapeType::FILLED )
		{
			glDrawElements( GL_TRIANGLES, IBO.GetCount( ), GL_UNSIGNED_INT, nullptr );
		}
		else if( currentType == ShapeType::LINE )
		{
			glDrawElements( GL_LINE_LOOP, IBO.GetCount( ), GL_UNSIGNED_INT, nullptr );
		}

		IBO.Unbind();
	}

	void RenderVertices( )
	{
		if( currentType == ShapeType::FILLED )
		{
			glDrawArrays( GL_TRIANGLES, 0, verticesCount );
		}
		else if( currentType == ShapeType::LINE )
		{
			glDrawArrays( GL_LINE_LOOP, 0, verticesCount );
		}
	}

protected:
	Position position;
	Colour colour;
	GLf_Size size;

	Position p1;
	Position p2;
	Position p3;

	GLuint verticesCount;

	unsigned short currentType;
	float lineWidth;

	VertexBuffer vertVBO;
	VertexBuffer colourVBO;
	IndexBuffer IBO;
	VertexArray VAO;

protected:
	enum ShaderLocation
	{
		POSITION		= 0,
		COLOUR			= 1,
		TEXTURE_COORD	= 2
	}; 

public:
	enum ShapeType
	{
		FILLED = 0,
		LINE = 1
	};
};