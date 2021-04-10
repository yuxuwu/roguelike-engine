#include "Vertices.h"



VertexBuffer::VertexBuffer(ComPtr<ID3D11Device> d3dDevice, VERTEX vertices[], UINT numVertices) {
	// Create Vertex Buffer
	D3D11_BUFFER_DESC bd = {0};
	bd.ByteWidth = sizeof(VERTEX) * numVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA srd = {vertices, 0, 0};

	DEBUG_HR(d3dDevice->CreateBuffer(&bd, &srd, &this->p_buffer));
}

void VertexBuffer::Set(ComPtr<ID3D11DeviceContext> d3dContext) {
	d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d3dContext->IASetVertexBuffers(0, 1, this->p_buffer.GetAddressOf(), &this->stride, &this->offset);
}
