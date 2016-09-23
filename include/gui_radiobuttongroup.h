#ifndef _GUI_RADIOBUTTONGROUP_H
#define _GUI_RADIOBUTTONGROUP_H

#include <irrlicht.h>
#include <IGUIElementFactory.h>

namespace irr
{
	namespace gui
	{

		// automatic layout
		enum EGUI_RadioButtonGroupLayout
		{
			//! element won't do the layout for you
			ERBGL_MANUAL,

			//! The default layout:
			//! Every button will have the width to contain at least it's full text
			//! If one line is not enough the buttons will be distributed on several lines
			//! Buttons are distributed as evenly as possible on multiple lines
			//! All space is filled (so buttons can be larger than needed for their text)
			ERBGL_MULTILINE_FULLTEXT,
		};

		//! Names for gui element types
		const c8* const GUIRadioButtonGroupLayoutNames[] =
		{
			"manual",
			"multiline_fulltext",
			0,
		};


		//! Groups radiobuttons
		//! Can send MEGET_RADIOBUTTONGROUP_CHANGED gui events
		//! TAKE CARE: The added buttons will not be serialized at all.
		//!            Neither as normal child elements nor in any other way.
		//!            So adding buttons must be hardcoded.
		//!            Sorry for that, but it's rather hard to do that clean with the current serialization system.
		// TODO: This does not matter for now, but serialization could maybe work in some way. Some thoughts:
		// - it would probably be possible to work with element-names instead of pointers, but that would be slow
		// - Maybe the elements should *not* be added as sub-elements. The connection as radio-button could not be saved
		//   that way, but at least the normal serialization would still work. I don't know anymore if I had a real reason to use
		//   subelements or if I just did it that way because I thought of them as subelements.
		// - a last solution could maybe be made by adding some PostSerialization functionality to irrlicht
		class CGUIRadioButtonGroup : public IGUIElement
		{
			public:
				CGUIRadioButtonGroup(IGUIEnvironment* environment, IGUIElement* parent);
				virtual ~CGUIRadioButtonGroup();

				//! add a new button at the end.
				//! \param caption: the button text
				//! \param id: the button identifier
				//! Returns the added button
				virtual IGUIButton* add(const wchar_t* caption, s32 id=-1);

				//! add an existing button at the end
				//! \param button: A button which you created somewhere else.
				//! Returns the index or -1 for failure
				virtual s32 add(IGUIButton* button);

				//! insert a new button
				//! \param index: The place where it will be inserted.
				//!	          This is only important for the layout, not for the drawing order.
				//!	              Note that the index of this button can change when other elements are inserted or removed before it.
				//! \param caption: The button text
				//! \param id: A number which you can use to identify the button.
				//! returns the inserted button
				virtual IGUIButton* insert(u32 index, const wchar_t* caption, s32 id=-1);

				//! insert an existing button
				//! \param button: A button which you created somewhere else.
				//! Returns the index or -1 for failure
				virtual s32 insert(u32 index, IGUIButton* button);

				//! return the button at the given index
				virtual IGUIButton* get(u32 index) const;

				//! remove button with the given index
				//! return true if it was removed and false if the index did not exist
				virtual bool remove(u32 index);

				//! remove all buttons
				virtual void removeAll();

				//! return the number of buttons
				virtual u32 count() const;

				//! Returns the index of the selected button.
				//! will return -1 if no button is selected
				virtual s32 getSelected() const;

				//! Set the currently active selected button.
				//! Note that this will not trigger an MEGET_RADIOBUTTONGROUP_CHANGED event
				virtual void setSelected(s32 index);

				//! Force an update of the layout with the currently active layout type.
				//! Usually the element cares about this itself, so you will mostly need to call
				//! this when you change the layout and some buttons already do exist.
				virtual void updateLayout();

				//! Set a certain layout type which the element will use when for example buttons are added/removed
				//! You need to manually call updateLayout() afterwards to see an effect.
				//! default layout is ERBGL_MULTILINE_FULLTEXT
				virtual void setLayout(EGUI_RadioButtonGroupLayout layout);

				//! Tell the multiline layouts that a certain minimal numer of lines is necessary
				virtual void setMinNumberLines(u32 minLines);

				//! get the currently used layout
				virtual EGUI_RadioButtonGroupLayout getLayout() const;

				//! Activate the first added button or activate another button (when possible) if the active was removed.
				virtual void autoActivate(bool autoActivate);

				//! The last event was caused by an autoActivation
				//! Such events can be suppressed by calling autoActivate(false)
				virtual bool isAutoActivateEvent() const;

				//! Sets another color for the background
				virtual void setBackgroundColor(video::SColor color, bool drawBackground=true);

				//! Sets whether to draw the background
				virtual void setDrawBackground(bool draw);


				virtual const c8* getTypeName() const	{ return "radiobuttongroup"; }
				virtual void updateAbsolutePosition();
				virtual bool OnEvent(const SEvent &event);
				virtual void draw();

			protected:
				virtual void activateButton(s32 index, bool sendEvent, bool autoActivated=false);
				void layoutMultilineFulltext();

				virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
				virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

				s32 MinTextPadding; // min. padding space around buttontext on each side
				s32 ButtonGap;	// gap between two buttons and between buttons are borders

				bool Background;
				video::SColor BGColor;

				u32 MinNumberOfLines;
				EGUI_RadioButtonGroupLayout Layout;
				IGUIButton* Selected;
				bool AutoActivate;
				bool IsAutoActivateEvent;
				core::array<IGUIButton*> Buttons;
		};

	} // namespace gui
} // namespace irr

#endif // _GUI_RADIOBUTTONGROUP_H
