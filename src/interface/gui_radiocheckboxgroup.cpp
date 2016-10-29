#include "interface/gui_radiocheckboxgroup.h"

using namespace irr;
using namespace gui;


CGUIRadioCheckBoxGroup::CGUIRadioCheckBoxGroup(IGUIEnvironment* environment, IGUIElement* parent)
	: IGUIElement((EGUI_ELEMENT_TYPE)0, environment, parent, -1, irr::core::rect<irr::s32>(0,0,100,100))
	, Background(false)
	, Selected(NULL)
	, AutoActivate(true)
	  , IsAutoActivateEvent(false)
{
	if (environment && Environment->getSkin())
	{
		BGColor = environment->getSkin()->getColor(gui::EGDC_3D_FACE);
	}
}

CGUIRadioCheckBoxGroup::~CGUIRadioCheckBoxGroup()
{
	removeAll();
}

s32 CGUIRadioCheckBoxGroup::add(IGUICheckBox* cb)
{
	return insert( CheckBoxes.size(), cb);
}

// this one does the work
s32 CGUIRadioCheckBoxGroup::insert(u32 index, IGUICheckBox* cb)
{
	if ( !cb )
		return -1;

	addChild(cb);
	cb->setSubElement(true);

	if ( index < CheckBoxes.size() )
	{
		cb->grab();
		CheckBoxes.insert(cb, index);
	}
	else
	{
		cb->grab();
		CheckBoxes.push_back(cb);
		index = CheckBoxes.size()-1;

		if( AutoActivate && CheckBoxes.size() == 1 )
		{
			activateCheckBox(index, true, true);
		}
	}

	return (s32)index;
}

IGUICheckBox* CGUIRadioCheckBoxGroup::get(u32 index) const
{
	if ( index < CheckBoxes.size() )
		return CheckBoxes[index];
	return NULL;
}

//! return the index for the checkbox or -1 for not found
s32 CGUIRadioCheckBoxGroup::getIndex(IGUICheckBox* cb) const
{
	for ( u32 i=0; i < CheckBoxes.size(); ++i )
	{
		if ( CheckBoxes[i] == cb )
			return (s32)i;
	}

	return -1;
}


bool CGUIRadioCheckBoxGroup::remove(u32 index)
{
	if ( index < CheckBoxes.size() )
	{
		if ( AutoActivate && CheckBoxes[index]->isChecked() )
		{
			if ( index > 0 )
			{
				activateCheckBox(index-1, true, true);
			}
			else if ( index < CheckBoxes.size()-1 )
			{
				activateCheckBox(index+1, true, true);
			}
		}

		removeChild(CheckBoxes[index]);
		CheckBoxes[index]->drop();
		CheckBoxes.erase(index);
		return true;
	}
	return false;
}

void CGUIRadioCheckBoxGroup::removeAll()
{
	for ( u32 i=0; i < CheckBoxes.size(); ++i )
	{
		removeChild(CheckBoxes[i]);
		CheckBoxes[i]->drop();

	}
	CheckBoxes.clear();
}

u32 CGUIRadioCheckBoxGroup::count() const
{
	return CheckBoxes.size();
}

s32 CGUIRadioCheckBoxGroup::getSelected() const
{
	if ( Selected )
	{
		for ( u32 i=0; i < CheckBoxes.size(); ++i )
		{
			if ( CheckBoxes[i] == Selected )
				return (s32)i;
		}
	}
	return -1;
}

void CGUIRadioCheckBoxGroup::setSelected(s32 index)
{
	activateCheckBox(index, false, false);
}

void CGUIRadioCheckBoxGroup::activateCheckBox(s32 index, bool sendEvent, bool isAutoActivated)
{
	IGUICheckBox* oldSelected = Selected;

	if ( (u32)index >= CheckBoxes.size() )
		return;

	Selected = NULL;
	// We do this even if it's the same than the old one. If someone calls it for the old he
	// probably has some reason for it.
	for ( u32 i=0; i < CheckBoxes.size(); ++i )
	{
		if ( (s32)i!=index)
		{
			CheckBoxes[i]->setChecked(false);
		}
		else
		{
			CheckBoxes[i]->setChecked(true);
			Selected = CheckBoxes[i];
		}
	}

	if ( sendEvent )
	{
		IsAutoActivateEvent = isAutoActivated;
		if ( oldSelected != Selected )	// it's only a change event
		{
			if (Parent)
			{
				SEvent e;
				e.EventType = EET_GUI_EVENT;
				e.GUIEvent.Caller = this;
				e.GUIEvent.Element = index > 0 ? CheckBoxes[index] : NULL;
				e.GUIEvent.EventType = (EGUI_EVENT_TYPE)EGET_CHECKBOX_CHANGED;
				Parent->OnEvent(e);
			}
		}
	}
}

bool CGUIRadioCheckBoxGroup::OnEvent(const SEvent &event)
{
	if ( !IsEnabled )
		return IGUIElement::OnEvent(event);

	switch(event.EventType)
	{
		case EET_GUI_EVENT:
			if (event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
			{
				if ( Selected == event.GUIEvent.Caller )
				{
					// keep your head down buddy
					Selected->setChecked(true);
					return true;
				}
				else
				{
					// check if it's one of our checkboxes
					for ( u32 i=0; i < CheckBoxes.size(); ++i )
					{
						if ( event.GUIEvent.Caller == CheckBoxes[i] )
						{
							// new selected
							activateCheckBox(i, true, false);
							break;
						}
					}
				}
			}
			break;

		default:
			break;
	}

	return IGUIElement::OnEvent(event);
}

void CGUIRadioCheckBoxGroup::autoActivate(bool autoActivate)
{
	AutoActivate = autoActivate;
}

bool CGUIRadioCheckBoxGroup::isAutoActivateEvent() const
{
	return IsAutoActivateEvent;
}

void CGUIRadioCheckBoxGroup::setBackgroundColor(video::SColor color, bool drawBackground)
{
	BGColor = color;
	Background = drawBackground;
}

void CGUIRadioCheckBoxGroup::setDrawBackground(bool draw)
{
	Background = draw;
}

void CGUIRadioCheckBoxGroup::draw()
{
	if (!IsVisible)
		return;

	irr::video::IVideoDriver* driver = Environment->getVideoDriver();

	// draw background
	if (Background)
	{
		driver->draw2DRectangle(BGColor, AbsoluteRect, &AbsoluteClippingRect);
	}

	IGUIElement::draw();
}


void CGUIRadioCheckBoxGroup::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	IGUIElement::serializeAttributes(out,options);

	out->addBool("Background", Background);
	out->addColor("BGColor", BGColor);
	out->addBool("AutoActivate", AutoActivate);
	out->addBool("IsAutoActivateEvent", IsAutoActivateEvent);
}

void CGUIRadioCheckBoxGroup::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	Selected = NULL;
	removeAll();

	IGUIElement::deserializeAttributes(in,options);

	Background = in->getAttributeAsBool("Background");
	BGColor = in->getAttributeAsColor("BGColor");
	AutoActivate = in->getAttributeAsBool("AutoActivate");
	IsAutoActivateEvent = in->getAttributeAsBool("IsAutoActivateEvent");
}
