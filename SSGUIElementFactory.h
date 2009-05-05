#ifndef __SS__GUI_FACTORY_H_INCLUDED__
#define __SS__GUI_FACTORY_H_INCLUDED__

#include <irrlicht.h>

#include "SSGUIButton.h"
#include "SSGUIScrollBar.h"
#include "SSGUIMenuBar.h"
#include "SSGUISideNavigateBar.h"
#include "SSGUISideInfoBar.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum SSGUI_ELEMENT_TYPES
{
	ESSGUI_BUTTON = 0,
	ESSGUI_SCROLLBAR,
	ESSGUI_MENUBAR,
	ESSGUI_SIDENAVIGATEBAR,
	ESSGUI_SIDEINFOBAR,

	ESSGUI_COUNT
};

const c8* const SSGUIElementTypeNames[] =
{
	"button",
	"scrollbar",
	"menubar",
	"sidenavigatebar",
	"sideinfobar",

	0
};

class SSGUIElementFactory : public IGUIElementFactory
{
public:
	explicit SSGUIElementFactory(IGUIEnvironment *environment);

	virtual IGUIElement* addGUIElement(const c8* typeName, IGUIElement* parent = 0);
	virtual s32 getCreatableGUIElementTypeCount() const;
	virtual const c8* getCreateableGUIElementTypeName(s32 idx) const;

	//not used:
	virtual const c8* getCreateableGUIElementTypeName(EGUI_ELEMENT_TYPE type) const {return 0;} ;
	virtual EGUI_ELEMENT_TYPE getCreateableGUIElementType(s32 idx) const { return EGUIET_ELEMENT;};
	virtual IGUIElement* addGUIElement(EGUI_ELEMENT_TYPE type, IGUIElement* parent=0) {return 0;};

	~SSGUIElementFactory();
private:
	IGUIEnvironment *Environment;
};

#endif