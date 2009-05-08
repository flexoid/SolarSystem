#include "SSGUIElementFactory.h"

SSGUIElementFactory::SSGUIElementFactory(IGUIEnvironment *environment)
: Environment(environment)
{
}

SSGUIElementFactory::~SSGUIElementFactory()
{
}

IGUIElement* SSGUIElementFactory::addGUIElement(const c8* typeName, IGUIElement* parent)
{
	core::stringc elementType(typeName);
	IGUIElement* ret = 0;

	if (parent == 0)
	{
		parent = Environment->getRootGUIElement();
	}

	if (elementType == core::stringc(SSGUIElementTypeNames[ESSGUI_BUTTON]))
		ret = new SSGUIButton(Environment, parent, -1);
	if (elementType == core::stringc(SSGUIElementTypeNames[ESSGUI_SCROLLBAR]))
		ret = new SSGUIScrollBar(false, Environment, parent, -1);
	if (elementType == core::stringc(SSGUIElementTypeNames[ESSGUI_MENUBAR]))
		ret = new SSGUIMenuBar(0, Environment, parent, -1);
	if (elementType == core::stringc(SSGUIElementTypeNames[ESSGUI_SIDENAVIGATEBAR]))
		ret = new SSGUISideNavigateBar(0, Environment, parent, -1);
	if (elementType == core::stringc(SSGUIElementTypeNames[ESSGUI_SIDEINFOBAR]))
		ret = new SSGUISideInfoBar(Environment, parent);

	if (ret)
		ret->drop();

	return ret;
}

s32 SSGUIElementFactory::getCreatableGUIElementTypeCount() const
{
	return ESSGUI_COUNT;
}

const c8* SSGUIElementFactory::getCreateableGUIElementTypeName(s32 idx) const
{
	if (idx >= 0 && idx < ESSGUI_COUNT)
		return SSGUIElementTypeNames[idx];

	return 0;
}

IGUIEnvironment* SSGUIElementFactory::getGUIEnvironment()
{
	return Environment;
}