#ifndef MIASMAMAPLOADER_H_
#define MIASMAMAPLOADER_H_
#include <string>

namespace Miasma::Utility
{
	class MiasmaMapLoader
	{
	public: 
		MiasmaMapLoader();
		~MiasmaMapLoader();

		void LoadMap(const std::string& mapFilename);

	private:

	};
}
#endif