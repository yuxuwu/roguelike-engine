#ifndef ROGUELIKE_ENGINE_VERTICES_H
#define ROGUELIKE_ENGINE_VERTICES_H

#include "../pch.h"

struct Vertex {
	FLOAT X, Y, Z;
	FLOAT Color[3];
};

struct VerticesSpec {
	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	ComPtr<ID3D11InputLayout> p_input_layout;
	void Set(const ComPtr<ID3D11DeviceContext>&);
};

struct VertexBuffer {
	ComPtr<ID3D11Buffer> p_buffer;
	UINT stride = sizeof(Vertex);
	UINT offset;
	void Set(ComPtr<ID3D11DeviceContext>);
};



#endif //ROGUELIKE_ENGINE_VERTICES_H
