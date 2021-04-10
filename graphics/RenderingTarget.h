//
// Created by Yu on 4/9/2021.
//

#ifndef ROGUELIKE_ENGINE_RENDERINGTARGET_H
#define ROGUELIKE_ENGINE_RENDERINGTARGET_H

#include "../pch.h"
#include "Shader.h"
#include "Vertices.h"

struct RenderingTarget {
	VertexShader vertex_shader;
	PixelShader pixel_shader;
	VerticesSpec vertices_spec;
	VertexBuffer vertex_buffer;
	void Set(const ComPtr<ID3D11DeviceContext>&);
};


#endif //ROGUELIKE_ENGINE_RENDERINGTARGET_H
