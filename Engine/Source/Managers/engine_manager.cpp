// User-defined Headers
#include "engine_manager.h"

// Default Constructor
Managers::EngineManager::EngineManager() {}

// Initialize Window, Context, FrameBufferInfo, OpenGL & all Managers
bool Managers::EngineManager::Init() {
	// Setup window information
	Core::WindowInfo window(std::string("Engine"), 400, 200, 800, 600, true);

	// Setup OpenGL context information
	Core::ContextInfo context(4, 5, true);

	// Setup FrameBuffer information
	Core::FrameBufferInfo framebuffer_info(true, true, true, true);

	// Initialize GLUT
	Core::Init::InitGLUT::Init(window, context, framebuffer_info);

	// Setup Scene Manager
	scene_manager_ = new Managers::SceneManager();
	Core::Init::InitGLUT::SetListener(scene_manager_);

	// Setup Shader Manager
	shader_manager_ = new Managers::ShaderManager();
	shader_manager_->CreateProgram("colorShader", "Shaders\\vertex_shader.glsl", "Shaders\\fragment_shader.glsl");

	// Add shader manager and create model manager
	if (scene_manager_ && shader_manager_) {
		scene_manager_->SetShaderManager(shader_manager_);

		// Create the Scene's Model Manager
		model_manager_ = new Managers::ModelManager();
		scene_manager_->SetModelManager(model_manager_);

		// Create the Scene's Camera Manager
		camera_manager_ = new Managers::CameraManager();
		scene_manager_->SetCameraManager(camera_manager_);
		glutKeyboardFunc(Managers::CameraManager::KeyPressCallback);
		glutKeyboardUpFunc(Managers::CameraManager::KeyReleaseCallback);
		glutMouseFunc(Managers::CameraManager::MousePressCallback);
		glutMotionFunc(Managers::CameraManager::MouseMoveCallback);
		glutSpecialFunc(Managers::CameraManager::SpecialKeyPressCallback);
		glutSpecialUpFunc(Managers::CameraManager::SpecialKeyReleaseCallback);
	}
	else
		return false;

	return true;
}

// Main Engine Loop
void Managers::EngineManager::Run() {
	Core::Init::InitGLUT::Run();
}

// Return Scene Manager
Managers::SceneManager* Managers::EngineManager::GetSceneManager() const {
	return scene_manager_;
}

// Return Shader Manager
Managers::ShaderManager* Managers::EngineManager::GetShaderManager() const {
	return shader_manager_;
}

// Return Model Manager
Managers::ModelManager* Managers::EngineManager::GetModelManager() const {
	return model_manager_;
}

// Return Camera Manager
Managers::CameraManager* Managers::EngineManager::GetCameraManager() const {
	return camera_manager_;
}

// Cleanup managers
Managers::EngineManager::~EngineManager() {
	// Delete Scene Manager
	if (scene_manager_)
		delete scene_manager_;
}