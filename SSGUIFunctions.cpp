#include "SSGUIFunctions.h"
#include <windows.h>
#include <math.h>

s32 getFreeElementID(s32 needed, IGUIEnvironment *env)
{
	if (needed < 1) needed = 1;
	if (env->getRootGUIElement()->getElementFromId(needed, true))
	{
		char *buffer = new char[64];
		itoa(needed, buffer, 10);
		double x = pow(10, (double)strlen(buffer));
		delete[] buffer;
		while(env->getRootGUIElement()->getElementFromId(needed, true)) needed += (s32)x;
	}
	return needed;
}

s32 getFreeChildElementID(IGUIElement *parent, IGUIEnvironment *env)
{
	s32 parentID = parent->getID();
	if (parentID >= 0)
	{
		parentID = getFreeElementID(parentID, env);
		parent->setID(parentID);
	}

	int x = parentID * 1000 + 1;
	while (env->getRootGUIElement()->getElementFromId(x, true)) x++;
	return x;
}

s32 createSprite(IGUISpriteBank *sprites, ITexture *texture, const array<rect<s32>> &rectangles, u32 frameTime, bool reverse)
{
	if (sprites && texture)
	{
		u32 textureIndex;
		SGUISprite sprite;
		sprite.frameTime = frameTime;
		for (u32 n = 0; n < sprites->getTextureCount(); n++)
		{
			if (texture == sprites->getTexture(n))
			{
				textureIndex = n;
				break;
			}
		}
		if (sprites->getTexture(textureIndex) != texture)
		{
			sprites->addTexture(texture);
			textureIndex = sprites->getTextureCount() - 1;
		}

		u32 firstRect = sprites->getPositions().size();

		if (rectangles.size() == 0)
		{
			sprites->getPositions().push_back(rect<s32>(0, 0, texture->getSize().Width, texture->getSize().Height));
			SGUISpriteFrame frame;
			frame.rectNumber = firstRect;
			frame.textureNumber = textureIndex;
			sprite.Frames.push_back(frame);
		}
		else
		{
			for (u32 n = 0; n < rectangles.size(); n++)
			{
				sprites->getPositions().push_back(rectangles[n]);
			}

			for (u32 n = 0; n < rectangles.size(); n++)
			{
				SGUISpriteFrame frame;
				frame.rectNumber = firstRect + n;
				frame.textureNumber = textureIndex;

				sprite.Frames.push_back(frame);
			}
			if (reverse)
			{
				for (s32 n = rectangles.size() - 1; n > -1; n--)
				{
					SGUISpriteFrame frame;
					frame.rectNumber = firstRect + n;
					frame.textureNumber = textureIndex;

					sprite.Frames.push_back(frame);
				}
			}
		}

		u32 spriteIndex = sprites->getSprites().size();
		sprites->getSprites().push_back(sprite);

		return spriteIndex;
	}
	else return -1;
}

void drawIGUIElementRect(IGUIEnvironment *environment, IGUIElement *element)
{
	IVideoDriver *driver = environment->getVideoDriver();

	position2d<s32> startLine;
	position2d<s32> endLine;

	rect<s32> r = element->getAbsolutePosition();

	startLine = r.UpperLeftCorner;
	endLine = position2d<s32>(r.LowerRightCorner.X, r.UpperLeftCorner.Y);
	driver->draw2DLine(startLine, endLine, SColor(255,255,0,0));

	startLine = endLine;
	endLine = position2d<s32>(r.LowerRightCorner.X, r.LowerRightCorner.Y);
	driver->draw2DLine(startLine, endLine, SColor(255,255,0,0));

	startLine = endLine;
	endLine = position2d<s32>(r.UpperLeftCorner.X, r.LowerRightCorner.Y);
	driver->draw2DLine(startLine, endLine, SColor(255,255,0,0));

	startLine = endLine;
	endLine = position2d<s32>(r.UpperLeftCorner.X, r.UpperLeftCorner.Y);
	driver->draw2DLine(startLine, endLine, SColor(255,255,0,0));
}