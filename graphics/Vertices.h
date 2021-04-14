#ifndef ROGUELIKE_ENGINE_VERTICES_H
#define ROGUELIKE_ENGINE_VERTICES_H

#include "../pch.h"

struct VERTEX {
	FLOAT X, Y, Z;
	FLOAT Color[3];
};


struct VertexBuffer {
	VertexBuffer(ComPtr<ID3D11Device>, VERTEX[], UINT);
	void Set(ComPtr<ID3D11DeviceContext>);

	ComPtr<ID3D11Buffer> p_buffer;
	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	/// TODO: Parameterize below once I get the context of these vars
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
};


#endif //ROGUELIKE_ENGINE_VERTICES_H
