//
// Created by Yu on 4/9/2021.
//

#ifndef ROGUELIKE_ENGINE_RENDERINGTARGET_H
#define ROGUELIKE_ENGINE_RENDERINGTARGET_H

#include "../pch.h"
#include "Shader.h"
#include "Vertices.h"

struct RenderingTarget {
	void Set(const ComPtr<ID3D11DeviceContext>&);

	VertexShader vertex_shader;
	PixelShader pixel_shader;
	VertexBuffer vertex_buffer;
};


#endif //ROGUELIKE_ENGINE_RENDERINGTARGET_H
