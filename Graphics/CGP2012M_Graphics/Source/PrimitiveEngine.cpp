//#include "PrimitiveEngine.h"
//
//namespace EngineOpenGL
//{
//	PrimitiveEngine::Primitive PrimitiveEngine::ConstructCirclePrimitive()
//	{
//		Primitive circle;
//		return circle;
//	}
//
//	PrimitiveEngine::Primitive PrimitiveEngine::ConstructSquarePrimitive()
//	{
//		Primitive square;
//		//indices
//		square.indices = new GLushort[6];
//		square.indices[0] = 1;
//		square.indices[1] = 0;
//		square.indices[2] = 2;
//		square.indices[3] = 2;
//		square.indices[4] = 3;
//		square.indices[5] = 0;
//
//		//vertices
//		square.vertices = new Model::VertexLayout[4];
//		square.vertices[0] = Model::VertexLayout(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
//		square.vertices[1] = Model::VertexLayout(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
//		square.vertices[2] = Model::VertexLayout(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
//		square.vertices[3] = Model::VertexLayout(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
//
//		//set numbers.
//		square.numVertices = 4;
//		square.numIndices = 2;
//
//		return square;
//	}
//}