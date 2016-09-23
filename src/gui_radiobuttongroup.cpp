#include "gui_radiobuttongroup.h"

using namespace irr;
using namespace gui;

namespace
{
	// some struct so we can order the buttons into lines
	struct ButtonLine
	{
		ButtonLine() : Width(0) {}
		s32 Width;
		core::array<s32> SizeIndices;
	};
};

	CGUIRadioButtonGroup::CGUIRadioButtonGroup(IGUIEnvironment* environment, IGUIElement* parent)
	: IGUIElement((EGUI_ELEMENT_TYPE)0, environment, parent, -1, irr::core::rect<irr::s32>(0,0,100,100))
	, MinTextPadding(5)
	, ButtonGap(4)
	, Background(false)
	, MinNumberOfLines(0)
	, Layout(ERBGL_MULTILINE_FULLTEXT)
	, Selected(NULL)
	, AutoActivate(true)
	  , IsAutoActivateEvent(false)
{
	if (environment && Environment->getSkin())
	{
		Background = true;
		BGColor = environment->getSkin()->getColor(gui::EGDC_3D_FACE);
	}
}

CGUIRadioButtonGroup::~CGUIRadioButtonGroup()
{
	removeAll();
}

IGUIButton* CGUIRadioButtonGroup::add(const wchar_t* caption, s32 id)
{
	IGUIButton* button = Environment->addButton(core::rect<s32>(0,0,1,1), this, id, caption);
	if ( !button )
		return NULL;

	if ( insert(Buttons.size(), button) >= 0 )
		return button;

	button->drop();
	return NULL;
}

s32 CGUIRadioButtonGroup::add(IGUIButton* button)
{
	return insert( Buttons.size(), button );
}

IGUIButton* CGUIRadioButtonGroup::insert(u32 index, const wchar_t* caption, s32 id)
{
	IGUIButton* button = Environment->addButton(core::rect<s32>(0,0,1,1), this, id, caption);
	if ( !button )
		return NULL;

	if ( insert(index, button) >= 0 )
		return button;

	button->drop();
	return NULL;
}

// this one does the work
s32 CGUIRadioButtonGroup::insert(u32 index, IGUIButton* button)
{
	if ( !button )
		return -1;

	button->setIsPushButton(true);
	addChild(button);
	button->setSubElement(true);

	if ( index < Buttons.size() )
	{
		button->grab();
		Buttons.insert(button, index);
	}
	else
	{
		button->grab();
		Buttons.push_back(button);
		index = Buttons.size()-1;

		if( AutoActivate && Buttons.size() == 1 )
		{
			activateButton(index, true, true);
		}
	}

	updateLayout();

	return (s32)index;
}

IGUIButton* CGUIRadioButtonGroup::get(u32 index) const
{
	if ( index < Buttons.size() )
		return Buttons[index];
	return NULL;
}

bool CGUIRadioButtonGroup::remove(u32 index)
{
	if ( index < Buttons.size() )
	{
		if ( AutoActivate && Buttons[index]->isPressed() )
		{
			if ( index > 0 )
			{
				activateButton(index-1, true, true);
			}
			else if ( index < Buttons.size()-1 )
			{
				activateButton(index+1, true, true);
			}
		}

		removeChild(Buttons[index]);
		Buttons[index]->drop();
		Buttons.erase(index);
		updateLayout();
		return true;
	}
	return false;
}

void CGUIRadioButtonGroup::removeAll()
{
	for ( u32 i=0; i < Buttons.size(); ++i )
	{
		removeChild(Buttons[i]);
		Buttons[i]->drop();

	}
	Buttons.clear();
}

u32 CGUIRadioButtonGroup::count() const
{
	return Buttons.size();
}

s32 CGUIRadioButtonGroup::getSelected() const
{
	if ( Selected )
	{
		for ( u32 i=0; i < Buttons.size(); ++i )
		{
			if ( Buttons[i] == Selected )
				return (s32)i;
		}
	}
	return -1;
}

void CGUIRadioButtonGroup::setSelected(s32 index)
{
	activateButton(index, false, false);
}

void CGUIRadioButtonGroup::activateButton(s32 index, bool sendEvent, bool isAutoActivated)
{
	IGUIButton* oldSelected = Selected;

	if ( (u32)index >= Buttons.size() )
		return;

	Selected = NULL;
	// We do this even if it's the same than the old one. If someone calls it for the old he
	// probably has some reason for it.
	for ( u32 i=0; i < Buttons.size(); ++i )
	{
		if ( (s32)i!=index)
		{
			Buttons[i]->setPressed(false);
			//		Buttons[i]->enableOverrideTextColor(false); // TODO patch not yet in Irrlicht
		}
		else
		{
			Buttons[i]->setPressed(true);
			//	    Buttons[i]->enableOverrideTextColor(true);  // TODO patch not yet in Irrlicht
			//	    Buttons[i]->setOverrideTextColor(); // TODO patch not yet in Irrlicht
			Selected = Buttons[i];
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
				e.GUIEvent.Element = index > 0 ? Buttons[index] : NULL;
				e.GUIEvent.EventType = (EGUI_EVENT_TYPE)EGET_CHECKBOX_CHANGED;
				Parent->OnEvent(e);
			}
		}
	}
}

void CGUIRadioButtonGroup::updateLayout()
{
	switch ( Layout )
	{
		case ERBGL_MANUAL:
			// user will do it
			break;
		case ERBGL_MULTILINE_FULLTEXT:
			layoutMultilineFulltext();
			break;
	}
}

void CGUIRadioButtonGroup::layoutMultilineFulltext()
{
	// Every button will have the width to contain at least it's full text
	// If one line is not enough the buttons will be distributed on several lines
	// Buttons are distributed as evenly as possible on multiple lines
	// All space is filled (so buttons can be larger than needed for their text)

	if (!Buttons.size() )
		return;

	// lets find out what sizes the buttons should have
	//	s32 maxButtonWidth = 0;
	s32 maxButtonHeight = 0;
	core::array<s32> buttonSizes(Buttons.size());
	for ( u32 i=0; i < Buttons.size(); ++i )
	{
		// TODO patch not yet in Irrlicht
		//	    IGUIFont * font = Buttons[i]->getCurrentFont();
		//	    if ( font )
		//	    {
		//		core::dimension2d<s32> dim = font->getDimension(Buttons[i]->getText());
		//		buttonSizes.push_back( dim.Width + 2*MinTextPadding );
		//		if ( buttonSizes[i] > maxButtonWidth )
		//		    maxButtonWidth = buttonSizes[i];
		//		if ( dim.Height > maxButtonHeight )
		//		    maxButtonHeight = dim.Height;
		//	    }
	}

	// push at least one button in each line, but wrap lines when too many buttons are in one line
	core::array<ButtonLine> lines;
	lines.push_back(ButtonLine());
	lines.getLast().Width = ButtonGap;
	for ( u32 i=0; i < buttonSizes.size(); ++i )
	{
		s32 addSize = buttonSizes[i] + ButtonGap;

		if ( lines.getLast().SizeIndices.size() > 0 // at least one button for each line
				&& lines.getLast().Width + addSize > RelativeRect.getWidth() // too large for the line
		   )
		{
			lines.push_back(ButtonLine());
			lines.getLast().Width = ButtonGap;
		}
		lines.getLast().SizeIndices.push_back(i);
		lines.getLast().Width += addSize;
	}

	while ( lines.size() < MinNumberOfLines )
	{
		lines.push_back(ButtonLine());
		lines.getLast().Width = ButtonGap;
	}

	// As long as moving a button down to the next line
	// leads to two shorter lines, do so.
	bool tryMove=true;
	while ( tryMove )
	{
		tryMove = false;
		for ( u32 l=0; l < lines.size()-1; ++l )
		{
			if ( lines[l].SizeIndices.size() > 1	// at least one button
					&& lines[l].Width > lines[l+1].Width )	// and the line is larget than the next
			{
				// try if it would improve the layout (two shorter lines) if we
				// move the last button one line down
				s32 changedSize = buttonSizes[ lines[l].SizeIndices.getLast() ] + ButtonGap;
				if ( lines[l+1].Width + changedSize < lines[l].Width )
				{
					// do so
					lines[l+1].Width += changedSize;
					lines[l+1].SizeIndices.insert( lines[l].SizeIndices.getLast() );
					lines[l].SizeIndices.erase( lines[l].SizeIndices.size()-1 );
					lines[l].Width -= changedSize;

					tryMove = true;
				}
			}
		}
	}

	s32 buttonHeight = maxButtonHeight; // all buttons have the same height
	s32 buttonHeightNeeded = (ButtonGap + maxButtonHeight)*lines.size()+ButtonGap;
	s32 extraHeight = (RelativeRect.getHeight() - buttonHeightNeeded) / lines.size();
	if ( extraHeight > 0 )
	{
		// we can make the buttons a little heigher
		buttonHeight += extraHeight;
	}

	// Ok now we have sorted the buttons per line and know the minimum sizes which we will need.
	// We won't reduce buttons sizes - if the element is too small some buttons will be clipped
	// Now do place 'em.
	core::rect<s32> rect;
	rect.UpperLeftCorner.Y = ButtonGap;
	u32 buttonIdx = 0;
	for ( u32 l=0; l < lines.size(); ++l )
	{
		rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + buttonHeight;
		if ( lines[l].SizeIndices.size() )
		{
			s32 extraWidth = (RelativeRect.getWidth() - lines[l].Width);
			if ( extraWidth < 0 )
				extraWidth = 0;
			rect.UpperLeftCorner.X = ButtonGap + (extraWidth % lines[l].SizeIndices.size())/2 ; // left border + center it if the extraWidth can't be divided equally among the buttons.
			extraWidth /= lines[l].SizeIndices.size();
			for ( u32 i=0; i < lines[l].SizeIndices.size(); ++i )
			{
				rect.LowerRightCorner.X = rect.UpperLeftCorner.X + buttonSizes[buttonIdx]+extraWidth;
				Buttons[buttonIdx]->setRelativePosition(rect);
				++buttonIdx;
				rect.UpperLeftCorner.X = rect.LowerRightCorner.X+ ButtonGap;
			}
		}
		rect.UpperLeftCorner.Y = rect.LowerRightCorner.Y + ButtonGap;
	}
}

void CGUIRadioButtonGroup::setLayout(EGUI_RadioButtonGroupLayout layout)
{
	Layout = layout;
}

void CGUIRadioButtonGroup::setMinNumberLines(u32 minLines)
{
	MinNumberOfLines = minLines;
}

EGUI_RadioButtonGroupLayout CGUIRadioButtonGroup::getLayout() const
{
	return Layout;
}

void CGUIRadioButtonGroup::updateAbsolutePosition()
{
	IGUIElement::updateAbsolutePosition();
	updateLayout();
}

bool CGUIRadioButtonGroup::OnEvent(const SEvent &event)
{
	if ( !IsEnabled )
		return IGUIElement::OnEvent(event);

	switch(event.EventType)
	{
		case EET_GUI_EVENT:
			// TODO patch not yet in Irrlicht
			//	    if (event.GUIEvent.EventType == EGET_PUSHBUTTON_STATE_CHANGED)
			//	    {
			//		if ( Selected == event.GUIEvent.Caller )
			//		{
			//		    // keep your head down buddy
			//		    Selected->setPressed(true);
			//		    return true;
			//		}
			//		else
			//		{
			//		    // check if it's one of our buttons
			//		    for ( u32 i=0; i < Buttons.size(); ++i )
			//		    {
			//			if ( event.GUIEvent.Caller == Buttons[i] )
			//			{
			//			    // new selected
			//			    activateButton(i, true, false);
			//			    break;
			//			}
			//		    }
			//		}
			//	    }
			break;

		default:
			break;
	}

	return IGUIElement::OnEvent(event);
}

void CGUIRadioButtonGroup::autoActivate(bool autoActivate)
{
	AutoActivate = false;
}

bool CGUIRadioButtonGroup::isAutoActivateEvent() const
{
	return IsAutoActivateEvent;
}

void CGUIRadioButtonGroup::setBackgroundColor(video::SColor color, bool drawBackground)
{
	BGColor = color;
	Background = drawBackground;
}

void CGUIRadioButtonGroup::setDrawBackground(bool draw)
{
	Background = draw;
}

void CGUIRadioButtonGroup::draw()
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


void CGUIRadioButtonGroup::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	IGUIElement::serializeAttributes(out,options);

	out->addInt("MinTextPadding", MinTextPadding );
	out->addInt("ButtonGap", ButtonGap );
	out->addBool("Background", Background);
	out->addColor("BGColor", BGColor);
	out->addInt("MinNumberOfLines", MinNumberOfLines);
	out->addEnum("Layout", Layout, GUIRadioButtonGroupLayoutNames);
	out->addBool("AutoActivate", AutoActivate);
	out->addBool("IsAutoActivateEvent", IsAutoActivateEvent);

	//for ( u32 i=0, s=0; i < Buttons.size(); ++i )
	//{
	//  if ( Buttons[i]->isSubElement() )
	//	{
	//	core::stringc label;
	//	    label = "button"; label += s;
	//	++s;
	//	    // I found no way to do that with irrlicht.
	//	// Either I need access to the xml writer here or IAttributes needs
	//	    // something like out->addNode.
	//  }
	//}
	// core::array<IGUIButton*> Buttons;
}

void CGUIRadioButtonGroup::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	Selected = NULL;
	removeAll();

	IGUIElement::deserializeAttributes(in,options);

	MinTextPadding = in->getAttributeAsInt("MinTextPadding");
	ButtonGap = in->getAttributeAsInt("ButtonGap");
	Background = in->getAttributeAsBool("Background");
	BGColor = in->getAttributeAsColor("BGColor");
	MinNumberOfLines = in->getAttributeAsInt("MinNumberOfLines");
	Layout = (EGUI_RadioButtonGroupLayout)in->getAttributeAsEnumeration("Layout", GUIRadioButtonGroupLayoutNames);
	AutoActivate = in->getAttributeAsBool("AutoActivate");
	IsAutoActivateEvent = in->getAttributeAsBool("IsAutoActivateEvent");
	// core::array<IGUIButton*> Buttons;
}
