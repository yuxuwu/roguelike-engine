//
// Created by Yu on 4/9/2021.
//

#include "RenderingTarget.h"

void RenderingTarget::Set(const ComPtr<ID3D11DeviceContext>& d3dContext) {
	this->pixel_shader.Set(d3dContext);
	this->vertex_shader.Set(d3dContext);
	this->vertex_buffer.Set(d3dContext);
}
