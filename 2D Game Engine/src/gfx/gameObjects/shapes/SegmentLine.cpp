#include "SegmentLine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

SegmentLine::SegmentLine( const Position& p1, const Position& p2, const Colour& colour, unsigned short type )
	:
	Renderable( p1, p2, colour, type )
{
	std::vector<GLfloat> vertices =
	{
		this->p1.x, this->p1.y, this->p1.z,
		this->p2.x, this->p2.y, this->p2.z
	};

	std::vector<GLfloat> colours =
	{
		this->colour.r, this->colour.g, this->colour.b, this->colour.a,
		this->colour.r, this->colour.g, this->colour.b, this->colour.a
	};

	vertVBO = VertexBuffer( vertices, vertices.size( ), 3 );
	colourVBO = VertexBuffer( colours, colours.size( ), 4 );

	VAO.BindBuffer( vertVBO, ShaderLocation::POSITION, 0, 0 );
	VAO.BindBuffer( colourVBO, ShaderLocation::COLOUR, 0, 0 );

	verticesCount = vertices.size( ) / vertVBO.GetComponentCount( );
}

void SegmentLine::Render( Shader & shader )
{
	VAO.Bind( );

	Renderable::RenderVertices( );
}

void SegmentLine::SetLineWidth( float lineWidth )
{
	this->lineWidth = lineWidth;

	glLineWidth( this->lineWidth );
}

void SegmentLine::SetPoint( const Position & p, int number )
{
	if( number == VertexNum::P1 )
		p1 = p;
	else if( number == VertexNum::P2 )
		p2 = p;
	else
		throw std::out_of_range{ "Chosen vertex does not exist!\n" };

	std::vector<GLfloat> vertices =
	{
		this->p1.x, this->p1.y, this->p1.z,
		this->p2.x, this->p2.y, this->p2.z
	};

	vertVBO = VertexBuffer( vertices, vertices.size( ), 3 );
	VAO.BindBuffer( vertVBO, ShaderLocation::POSITION, 0, 0 );
}

void SegmentLine::SetPoints( const Position & p1, const Position & p2 )
{
	this->p1 = p1;
	this->p2 = p2;

	std::vector<GLfloat> vertices =
	{
		this->p1.x, this->p1.y, this->p1.z,
		this->p2.x, this->p2.y, this->p2.z
	};

	vertVBO = VertexBuffer( vertices, vertices.size( ), 3 );
	VAO.BindBuffer( vertVBO, ShaderLocation::POSITION, 0, 0 );
}

void SegmentLine::SetColour( const Colour & colour )
{
	this->colour = colour;

	std::vector<GLfloat> colours =
	{
		this->colour.r, this->colour.g, this->colour.b, this->colour.a,
		this->colour.r, this->colour.g, this->colour.b, this->colour.a
	};

	colourVBO = VertexBuffer( colours, colours.size( ), 4 );
	VAO.BindBuffer( colourVBO, ShaderLocation::COLOUR, 0, 0 );
}
