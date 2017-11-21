//
//  PretzelTextureWindow.h
//  BasicSample
//
//
//

#pragma once


#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"

namespace pretzel
{
	class PretzelTextureWindow : public BasePretzel
	{
		friend class ScrollPane;
		
	public:
		PretzelTextureWindow(BasePretzel *parent, std::string labelText, int width, int height, ci::gl::TextureRef tex=nullptr );
		void draw() override;
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) override;
		
		std::string getText() { return mMessage; };
		void setTexture( ci::gl::TextureRef tex );// { mTexture = tex; };
		
	private:
		std::string			mMessage;
		ci::Path2d			mOutlinePath;
		ci::vec2			scrollPaneOffset;
		ci::gl::TextureRef	mTexture;
	};
}
