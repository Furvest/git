#pragma once
#include <memory>

// пока тут ничего нет, когда нибудь я точно разобью имплементацию на отдельные компоненты

namespace Engine {	//forward decls
	namespace Render {
		class IRendererBase;
	};
	namespace Input {
		class IInputManagerBase;
	};
};
namespace Engine {
	class Core {
		void Init() {};
		void Update(){};
		void Render(){};
		std::unique_ptr<Render::RendererBase*> render;
		std::unique_ptr<Input::InputManagerBase*> input;
	};
	namespace Render {
		class RendererBase {
			virtual void Init(Core* core) = 0;
			virtual void CreateWindow() = 0;
			virtual void Update() = 0;
			Core* core;
		};	//render
	};
	namespace Input {
		class InputManagerBase {
			virtual void Init(Core* core) = 0;
			Core* core;
		};
	};
}