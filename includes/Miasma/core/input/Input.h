#ifndef _INPUT_H_
#define _INPUT_H_
#include <memory>
#include <string>

namespace Miasma::Input
{
	class Input
	{
	public:

		Input();
		~Input();

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static Input& GetInstance();

		// Input methods
		void GetKey(int keyCode);
		void GetKeyDown(int keyCode);
		void GetKeyUp(int keyCode);


	private: 
		static std::unique_ptr<Input> mInstance;
	};

#endif
}