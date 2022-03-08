#pragma once
#include <glm/glm.hpp>
namespace Geometry {
	struct Vertex {
	public:
		//Default Constructor
		Vertex() :pos(glm::vec3(0.f)), texCoord(glm::vec3(0.f)),
			vertexColor(glm::vec4(0.f, 0.f, 0.f, 1.f)), id(0) {}

		//Verbose Constructor
		Vertex(const glm::vec3& Position, const glm::vec2& TexCoord, const glm::vec4& VertexColor, unsigned int ID)
			:pos(Position), texCoord(TexCoord), vertexColor(VertexColor), id(ID) {}

		//One Value Constructors
		explicit Vertex(const glm::vec3& Position) : pos(Position), texCoord(glm::vec3(0.f)),
			vertexColor(glm::vec4(0.f, 0.f, 0.f, 1.f)), id(0) {}

		explicit Vertex(const glm::vec2& TexCoord) : pos(glm::vec3(0.f)), texCoord(TexCoord),
			vertexColor(glm::vec4(0.f, 0.f, 0.f, 1.f)), id(0) {}

		explicit Vertex(const glm::vec4& Color) : pos(glm::vec3(0.f)), texCoord(glm::vec3(0.f)),
			vertexColor(Color), id(0) {}

		//by components constructors
		Vertex(float X, float Y, float Z, float S, float T, float R, float G, float B, float Alpha,
			unsigned int ID)
			:x(X), y(Y), z(Z), s(S), t(T), r(R), g(G), b(B), alpha(Alpha), id(ID) {}

		Vertex(float X, float Y, float Z, float S, float T)
			:x(X), y(Y), z(Z), s(S), t(T), vertexColor(glm::vec4(0.f)), id(0) {}

		Vertex(float X, float Y, float Z, float S, float T, unsigned int ID)
			:x(X), y(Y), z(Z), s(S), t(T), vertexColor(glm::vec4(0.f)), id(ID) {}

		Vertex(float X, float Y, float Z)
			:x(X), y(Y), z(Z), texCoord(glm::vec2(0.f)), vertexColor(glm::vec4(0.f)), id(0) {}

		Vertex(float X, float Y, float Z, unsigned int ID)
			:x(X), y(Y), z(Z), texCoord(glm::vec2(0.f)), vertexColor(glm::vec4(0.f)), id(ID) {}

		Vertex(float X, float Y, float Z, float R, float G, float B, float Alpha)
			:x(X), y(y), z(Z), r(R), g(G), b(B), alpha(Alpha), texCoord(glm::vec3(0.f)), id(0) {}

		Vertex(float X, float Y, float Z, float R, float G, float B, float Alpha, unsigned int ID)
			:x(X), y(y), z(Z), r(R), g(G), b(B), alpha(Alpha), texCoord(glm::vec3(0.f)), id(ID) {}

		//Overloaded Operators
		const float* GetVertexRef() const {
			return &pos.x;
		}

		const float* operator&() const {
			return &pos.x;
		}

		//Utility Functions
		static unsigned int GetSize(){
			return sizeof(float) * 3 + sizeof(float) * 2 + sizeof(float) * 4 + sizeof(unsigned int);
		}
	public:
		union
		{
			glm::vec3 pos;
			struct {
				float x, y, z;
			};
			struct {
				glm::vec2 pos2D;
				float z;
			};
			float _pos[3];
		};
		union {
			glm::vec2 texCoord;
			struct {
				float s, t;
			};
			float _texCoord[2];
		};

		union {
			glm::vec4 vertexColor;
			struct {
				float r, g, b, alpha;
			};
			struct {
				glm::vec3 RGB; float alpha;
			};
			float _vertexColor[4];
		};

		unsigned int id;
	};
}


