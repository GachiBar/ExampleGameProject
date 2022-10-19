#include <iostream>

#include "../GameplaySystem/Engine.h"
#include "../monowrapper/monopp/mono_jit.h"

// TODO: Add references to monowrapper.lib, add reference to Engine.dll

const char kMonoLibPath[] = "..\\vendor\\mono\\lib\\4.5";
const char kDllPath[] = "GameplayCore.dll";

// TODO: Add reference to GameplayCore.dll in ExampleGameProject and copy GameplayCore.dll in build folder

class StandaloneGameTestApplication final : public Application
{
public:
	StandaloneGameTestApplication(const char* dll_path) 
		: Application(dll_path)
	{}

	mono::mono_object scene{ m_Assembly.get_type("GameplayCore", "Scene").new_instance() };
	mono::mono_object go1{ CreateGameObject(scene) };
	mono::mono_object go2{ CreateGameObject(scene) };

	void OnSetup() override;
};


void StandaloneGameTestApplication::OnSetup()
{
	AddComponent(m_Assembly, go1, "GameplayCore.Components", "TestUpdateComponent");
	AddComponent(m_Assembly, go2, "GameplayCore.Components", "TestFixedUpdateComponent");
	AddComponent(m_Assembly, go1, "GameplayCore.Components", "MeshRenderComponent");
	AddComponent(m_Assembly, go1, "GameplayCore.Components", "TransformComponent");

	engine_->SetScene(&scene);
}
#include "../Editor/Delegates.h"

int main() {
	if (!mono::init_with_mono_assembly_path(kMonoLibPath, "KtripRuntime")) {
		return 1;
	}		

	StandaloneGameTestApplication app(kDllPath);
	return app.Run();
}
