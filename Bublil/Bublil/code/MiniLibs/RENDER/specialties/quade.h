#pragma once

#include"RENDER/loading/obj_loader.h"

#include<vector>

const int NUM_BUFFER = 3;//Positions, texCoords, indices.

class Quade
{
public:
	IndexedModel model;
	Quade()
	{
		m_drawCount = 4;
		model.positions = { {-1, -1, 0}, {-1, 1, 0}, {1, 1, 0}, {1, -1, 0} };
		model.indices = { 0, 1, 2,     0, 2, 3 };
		model.texCoords = { {0, 1}, {0, 0}, {1, 0}, {1, 1} };

		glGenVertexArrays(1, &m_vertexArrayObject);
		glBindVertexArray(m_vertexArrayObject);

		glGenBuffers(NUM_BUFFER, m_vertexArrayBuffers);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
		glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[1]);
		glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}
	~Quade() { glDeleteVertexArrays(1, &m_vertexArrayObject); }

	void Draw()
	{
		glBindVertexArray(m_vertexArrayObject);

		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
private:
	
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFER];
	unsigned int m_drawCount;
};
