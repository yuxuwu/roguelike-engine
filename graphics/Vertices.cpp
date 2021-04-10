#include "Vertices.h"

void VerticesSpec::Set(const ComPtr<ID3D11DeviceContext>& d3dContext) {
	d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d3dContext->IASetInputLayout(this->p_input_layout.Get());
}

void VertexBuffer::Set(ComPtr<ID3D11DeviceContext> d3dContext) {
	d3dContext->IASetVertexBuffers(0, 1, this->p_buffer.GetAddressOf(), &this->stride, &this->offset);
}
