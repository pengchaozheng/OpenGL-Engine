#pragma once

// User-defined Headers
#include "Managers\engine_manager.h"
#include "Rendering\Models\skybox.h"
#include "Rendering\Models\earth.h"

int main(int argc, char **argv)
{
	// Initialize the Engine Manager
	Managers::EngineManager* engine = new Managers::EngineManager();
	engine->Init();

	// Setup camera's initial position
	engine->GetCameraManager()->SetPosition(glm::vec3(0, 0, 3));

	// Setup Earth's Vertex and Fragment Shaders
	engine->GetShaderManager()->CreateProgram("earth_shader", "Shaders\\earth_vertex_shader.glsl", "Shaders\\earth_fragment_shader.glsl");
	engine->GetShaderManager()->CreateProgram("skybox_shader", "Shaders\\skybox_vertex_shader.glsl", "Shaders\\skybox_fragment_shader.glsl");

	// Create the skybox and set its shader program
	Rendering::Models::Skybox* skybox = new Rendering::Models::Skybox();

	// Set the Skybox's Program
	skybox->SetProgram(engine->GetShaderManager()->GetShader("skybox_shader"));

	// Load Cube-Map for Skybox
	std::vector<std::string> faces = {
		"Textures\\SkyboxPositiveX.png",
		"Textures\\SkyboxNegativeX.png",
		"Textures\\SkyboxPositiveY.png",
		"Textures\\SkyboxNegativeY.png",
		"Textures\\SkyboxPositiveZ.png",
		"Textures\\SkyboxNegativeZ.png"
	};
	unsigned int skybox_texture_id = engine->GetTextureLoader()->LoadCubeMapTexture(faces);
	skybox->SetTexture("skybox_texture", skybox_texture_id);
	skybox->Create();

	// Create the Earth and set its shader program
	Rendering::Models::Earth* earth = new Rendering::Models::Earth();

	// Set the Earth's Program
	earth->SetProgram(engine->GetShaderManager()->GetShader("earth_shader"));
	
	// Setup Earth's Texture
	unsigned int earth_texture_id = engine->GetTextureLoader()->LoadDDSTexture("Textures\\Earth.dds");
	earth->SetTexture("earth", earth_texture_id);

	// Create a icosphere of radius 1 with 32 slices and 32 stacks
	earth->Create(1, 32, 32);

	// Add cube to Engine's Model Manager
	engine->GetModelManager()->AddModel3D("skybox", skybox);
	engine->GetModelManager()->AddModel3D("earth", earth);

	// Run the Engine
	engine->Run();

	// Delete the Engine Object when rendering loop is finished
	delete engine;
	return 0;
}