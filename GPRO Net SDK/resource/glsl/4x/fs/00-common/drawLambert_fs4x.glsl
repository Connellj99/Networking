/*
	Copyright 2011-2021 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	drawLambert_fs4x.glsl
	Output Lambert shading.
*/

#version 450

#define MAX_LIGHTS 1024

in vbVertexData {
	mat4 vTangentBasis_view;
	vec4 vTexcoord_atlas;
};

struct sPointLight
{
	vec4 viewPos, worldPos, color, radiusInfo;
};

uniform ubLight
{
	sPointLight uPointLight[MAX_LIGHTS];
};

uniform int uCount;

uniform vec4 uColor;

uniform sampler2D uTex_dm;

layout (location = 0) out vec4 rtFragColor;
layout (location = 1) out vec4 rtFragNormal;

void calcLambertPoint(out vec4 diffuseColor,
	in vec4 fragPos, in vec4 fragNrm, in vec4 fragColor,
	in vec4 lightPos, in vec4 lightRadiusInfo, in vec4 lightColor);
	

void main()
{
	vec4 diffuseColor = vec4(0.0), dd;
	
	// view-space tangent basis
	vec4 nrm_view = normalize(vTangentBasis_view[2]);
	vec4 pos_view = vTangentBasis_view[3];
	
	int i;
	for (i = 0; i < uCount; ++i)
	{
		
		calcLambertPoint(dd, pos_view, nrm_view, uColor, 
			uPointLight[i].viewPos, uPointLight[i].radiusInfo,
			uPointLight[i].color);
		diffuseColor += dd;
	}

	vec4 sample_dm = texture(uTex_dm, vTexcoord_atlas.xy);
	rtFragColor = sample_dm * diffuseColor;
	rtFragColor.a = sample_dm.a;
	
	// MRT
	rtFragNormal = vec4(nrm_view.xyz * 0.5 + 0.5, 1.0);
}