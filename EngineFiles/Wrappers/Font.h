#ifndef AMU_FONT_WRAPPER_H
#define AMU_FONT_WRAPPER_H
#include <string>

struct _TTF_Font;

namespace amu
{

	/**
	 * Simple RAII wrapper for a _TTF_Font
	 */
	class Font final
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(std::string_view const& fullPath, unsigned int size);
		~Font();

		Font(Font const&) = delete;
		Font(Font&&) = delete;
		Font& operator= (Font const&) = delete;
		Font & operator= (Font &&) = delete;
	private:
		_TTF_Font* m_FontPtr = nullptr;
	};

}

#endif //AMU_FONT_WRAPPER_H