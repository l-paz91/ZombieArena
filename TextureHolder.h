// -----------------------------------------------------------------------------
#ifndef TextureHolder_H
#define TextureHolder_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include <map>
#include <string>

using namespace sf;

// -----------------------------------------------------------------------------

class TextureHolder
{
public:
	static TextureHolder& getInstance()
	{
		static TextureHolder instance;	// guaranteed to be destroyed properly
		return instance;
	}

	TextureHolder(const TextureHolder&) = delete;
	void operator=(const TextureHolder&) = delete;

	static Texture& getTexture(const std::string& filename)
	{
		std::map<std::string, Texture>& ref = getInstance().mTextures;
		auto it = ref.find(filename);
		if (it != ref.end())
		{
			return it->second;
		}
		else
		{
			Texture& t = ref[filename];
			t.loadFromFile(filename);
			return t;
		}
	}

private:
	TextureHolder() {}

	std::map<std::string, Texture> mTextures;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TextureHolder_H