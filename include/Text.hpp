#ifndef TEXT_HPP
#define TEXT_HPP

#define INCLUDE_SDL_TTF

#include "SDL_include.h"
#include "Component.hpp"

using namespace std;

class Text : public Component {
  public:
    enum TextStyle { SOLID, SHADED, BLENDED };
  
  private:
    TTF_Font *font;
    SDL_Texture *texture;

    string text;
    TextStyle style;
    string fontFile;
    int fontSize;
    SDL_Color color;

    void RemakeTexture();
  
  public:
    Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
    ~Text();

    void Update(float dt);
    void Render();
    void Start() {};
    bool Is(string type);

    void SetText(string text);
    void SetStyle(TextStyle style);
    void SetFontFile(string fontFile);
    void SetFontSize(int fontSize);
    void SetColor(SDL_Color color);
};

#endif
