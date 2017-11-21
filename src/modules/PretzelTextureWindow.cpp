#include "PretzelTextureWindow.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel{
	PretzelTextureWindow::PretzelTextureWindow(BasePretzel *parent, std::string labelText, int width, int height, ci::gl::TextureRef tex )
	: BasePretzel()
	, scrollPaneOffset(0,0)
	, mTexture(tex)
	{
		mMessage = labelText;
		type = WidgetType::TEXTURE;
		mBounds.set(0, 0, 200 + width, 23 + height );
		setTexture( tex );
		parent->registerPretzel(this);
		mGlobal = pretzel::PretzelGlobal::getInstance();
	}
	
	void PretzelTextureWindow::setTexture( ci::gl::TextureRef tex )
	{
		mTexture = tex;
//		if( mTexture ) {
//			mBounds.y2 = mBounds.y2 + tex->getHeight();
//		}
	}

	
	void PretzelTextureWindow::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds)
	{
		BasePretzel::updateBounds(offset, parentBounds);
		
		
		//ci::app::console() << "updateBounds offset-> " << offset << " parentBounds-> " << parentBounds << std::endl;
		
		vec2 textSize = mGlobal->guiFont->measureString(mMessage);
		
//		if( mTexture ) {
//			mBounds.y2 = mBounds.y2 + mTexture->getHeight();
//		}
	
		RectT<float> textRect(0, 0, textSize.x, textSize.y);
		textRect.y2 = mBounds.getHeight();
		textRect.x1 += -5 + 15;
		textRect.x2 += 5 + 15;
		
		mOutlinePath.clear();
		
		/*
		
		mOutlinePath.moveTo(mBounds.getLowerLeft() + vec2(0, -1));
		mOutlinePath.lineTo(textRect.getLowerLeft() + vec2(0, -1));
		mOutlinePath.lineTo(vec2(textRect.getUpperLeft().x, 3));
		mOutlinePath.lineTo(vec2(textRect.getUpperRight().x, 3));
		mOutlinePath.lineTo(textRect.getLowerRight() + vec2(0, -1));
		mOutlinePath.lineTo(mBounds.getLowerRight() + vec2(0, -1));
		 
		 */
		mOutlinePath.moveTo(textRect.getLowerLeft() + vec2(0, -1));
		mOutlinePath.lineTo(vec2(textRect.getUpperLeft().x, 3));
		mOutlinePath.lineTo(vec2(textRect.getUpperRight().x, 3));
		mOutlinePath.lineTo(textRect.getUpperRight() + vec2(0, textSize.y+10 ));
	}
	
	void PretzelTextureWindow::draw()
	{
		vec2 textSize = mGlobal->guiFont->measureString(mMessage);
		RectT<float> textRect(0, 0, textSize.x, textSize.y);
		textRect.y1 = 4;
		textRect.y2 = 23; // mBounds.getHeight()-1;
		textRect.x1 -= 5;
		textRect.x2 += 5;
		
		gl::pushMatrices(); {
			gl::translate(mOffset + scrollPaneOffset);
			
			// draw light background
			gl::color(mGlobal->P_TAB_COLOR);
			PWindow()->drawSolidRect(mBounds);
			
			gl::pushMatrices(); {
				gl::translate(15, 1);
				
				// draw dark background
				gl::color(mGlobal->P_BG_COLOR);
				PWindow()->drawSolidRect(textRect);
				
				// draw text
				mGlobal->renderText(mMessage, mBounds.getUpperLeft() + vec2(0, 4));
				
				
				gl::translate(-5, 1);
				
				if( mTexture ) {
					
					//ci::vec2 textSize = mGlobal->guiFont->measureString(mMessage);
					//ci::app::console() << "textSize " << textSize << std::endl;
					//ci::app::console() << "textRect " << textRect.getHeight() << std::endl;
					ci::gl::ScopedColor col( ci::ColorA(1,1,1,1) );
					ci::gl::draw( mTexture, ci::vec2(0,23 ));
				}
					
				
			}gl::popMatrices();
			
			// draw highlight line
			gl::translate(0, 1);
			//gl::color(mGlobal->P_HIGHLIGHT_COLOR);
			//gl::draw(mOutlinePath);
			
			gl::translate(0, -1);
			gl::color(mGlobal->P_OUTLINE_COLOR);
			gl::draw(mOutlinePath);
			
			
		}gl::popMatrices();
	}
}
