#include "TextImage.h"

#include <SDL2/SDL_image.h>
#include <ostream>

#include "Logger.h"

bool TextImage::theRunTtfInitOnce = true;
std::map<std::string, TTF_Font*> TextImage::theFonts;

TextImage::TextImage(std::string text, SDL_Color color, SDL_Renderer* renderer):
   ImageInfo(renderer),
   theColor(color),
   theText(text)
{
   if (theRunTtfInitOnce)
   {
      // Initialize the library
      if (TTF_Init() == -1)
      {
         LOG_FATAL() << "Error enabling TTF support:" << TTF_GetError();
      }
      theRunTtfInitOnce = false;
   }

   // Since no font is specified, a font is required to be loaded already, use the first one
   if (theFonts.empty())
   {
      LOG_FATAL() << "TextImage constructor for default font called, but no fonts are loaded";
      return;
   }

   theCurFont = theFonts.begin()->second;

   // Create surface with the text, and then create a texture with it
   SDL_Surface* surface = TTF_RenderText_Solid(theCurFont, text.c_str(), theColor);
   ProcessSurface(surface);

   LOG_DEBUG() << "Loaded texture with text (" << text << ") and size is (" << theSize << ")";
}

TextImage::TextImage(std::string text, SDL_Color color, std::string font, int pt, SDL_Renderer* renderer):
   ImageInfo(renderer),
   theColor(color),
   theText(text)
{
   if (theRunTtfInitOnce)
   {
      // Initialize the library
      if (TTF_Init() == -1)
      {
         LOG_FATAL() << "Error enabling TTF support:" << TTF_GetError();
      }
      theRunTtfInitOnce = false;
   }


   theCurFont = GetFont(font, pt);
   if (theCurFont == nullptr)
   {
      // Fatal error already logged by LoadFont
      return;
   }

   // Create surface with the text, and then create a texture with it
   SDL_Surface* surface = TTF_RenderText_Solid(theCurFont, text.c_str(), theColor);
   ProcessSurface(surface);

   LOG_DEBUG() << "Loaded texture with text (" << text << ") and size is (" << theSize << ")";
}

void TextImage::SetText(std::string text)
{
   if (text == theText)
   {
      // Called SetText with the same text already displayed, do nothing
      return;
   }

   if (theTexture != nullptr)
   {
      SDL_DestroyTexture(theTexture);
   }

   // Create surface with the text, and then create a texture with it

   SDL_Surface* surface = TTF_RenderText_Solid(theCurFont, text.c_str(), theColor);
   ProcessSurface(surface);
}

void TextImage::ProcessSurface(SDL_Surface* s)
{
   if (s == nullptr)
   {
      LOG_FATAL() << "Process surface passed null surface";
      return;
   }

   theSize[0] = s->w;
   theSize[1] = s->h;

   theSrc.w = s->w;
   theSrc.h = s->h;
   theSrc.x = 0;
   theSrc.y = 0;

   theTexture = SDL_CreateTextureFromSurface(theRenderer, s);

   if (theTexture == nullptr)
   {
      LOG_FATAL() << "Error converting surface to texture in ProcessSurface:" << SDL_GetError();
      return;
   }

   SDL_FreeSurface(s);
}


bool TextImage::LoadFont(std::string font, int pt)
{
   if (theRunTtfInitOnce)
   {
      // Initialize the library
      if (TTF_Init() == -1)
      {
         LOG_FATAL() << "Error enabling TTF support:" << TTF_GetError();
      }
      theRunTtfInitOnce = false;
   }

   std::ostringstream oss;
   oss << font << "!" << pt;

   std::map<std::string, TTF_Font*>::iterator it = theFonts.find(oss.str());
   if (it == theFonts.end())
   {
      // We didn't have that font cached
      TTF_Font* f = TTF_OpenFont(font.c_str(), pt);
      if (f == nullptr)
      {
         LOG_WARNING() << "Error loading font (" << font << "," << pt << "):" << TTF_GetError();
         return false;
      }

      LOG_DEBUG() << "Font (" << font << "," << pt << ") added to font cache";
      theFonts[oss.str()] = f;
      return true;
   }
   else
   {
      LOG_DEBUG() << "Font (" << font << "," << pt << ") found in font cache";
      return true;
   }
}

void TextImage::UnloadAllFonts()
{
   if (theRunTtfInitOnce)
   {
      // Nothing was ever loadedulils
      return;
   }

   for(auto&& curFont : theFonts)
   {
      LOG_DEBUG() << "Unloading font" << curFont.first;
      TTF_CloseFont(curFont.second);
   }

   theFonts.clear();
   theRunTtfInitOnce = true;
}

TTF_Font* TextImage::GetFont(std::string font, int pt)
{
   std::ostringstream oss;
   oss << font << "!" << pt;

   std::map<std::string, TTF_Font*>::iterator it = theFonts.find(oss.str());
   if (it == theFonts.end())
   {
      // We didn't have that font cached
      TTF_Font* f = TTF_OpenFont(font.c_str(), pt);
      if (f == nullptr)
      {
         LOG_FATAL() << "Error loading font (" << font << "," << pt << "):" << TTF_GetError();
         return nullptr;
      }

      LOG_DEBUG() << "Font (" << font << "," << pt << ") added to font cache";
      theFonts[oss.str()] = f;
      return f;
   }
   else
   {
      LOG_DEBUG() << "Font (" << font << "," << pt << ") found in font cache";
      return it->second;
   }
}
