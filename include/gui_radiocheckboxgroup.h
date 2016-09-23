#ifndef _GUI_RADIOCHECKBOXGROUP_H
#define _GUI_RADIOCHECKBOXGROUP_H

#include <irrlicht.h>
#include <IGUIElementFactory.h>

namespace irr
{
	namespace gui
	{
		//! Groups checkboxes
		//! Can send MEGET_RADIOCHECKBOXGROUP_CHANGED gui events
		//! TAKE CARE: The added checkboxes will not be serialized at all.
		//!            Neither as normal child elements nor in any other way.
		//!            So adding checkboxes must be hardcoded.
		//!            Sorry for that, but it's rather hard to do that clean with the current serialization system.
		// TODO: This does not matter for now, but serialization could maybe work in some way. Some thoughts:
		// - it would probably be possible to work with element-names instead of pointers, but that would be slow
		// - Maybe the elements should *not* be added as sub-elements. The connection as radio-button could not be saved
		//   that way, but at least the normal serialization would still work. I don't know anymore if I had a real reason to use
		//   subelements or if I just did it that way because I thought of them as subelements.
		// - a last solution could maybe be made by adding some PostSerialization functionality to irrlicht

		class CGUIRadioCheckBoxGroup : public IGUIElement
		{
			public:
				CGUIRadioCheckBoxGroup(IGUIEnvironment* environment, IGUIElement* parent);
				virtual ~CGUIRadioCheckBoxGroup();

				//! add an existing checkbox at the end
				//! \param cb: A checkbox which you created somewhere else.
				//! Returns the index or -1 for failure
				virtual s32 add(IGUICheckBox* cb);

				//! insert an existing checkbox
				//! \param cb: A checkbox which you created somewhere else.
				//! Returns the index or -1 for failure
				virtual s32 insert(u32 index, IGUICheckBox* cb);

				//! return the checkbox at the given index
				virtual IGUICheckBox* get(u32 index) const;

				//! return the index for the checkbox or -1 for not found
				virtual s32 getIndex(IGUICheckBox* cb) const;

				//! remove checkbox with the given index
				//! return true if it was removed and false if the index did not exist
				virtual bool remove(u32 index);

				//! remove all checkboxes
				virtual void removeAll();

				//! return the number of checkboxes
				virtual u32 count() const;

				//! Returns the index of the selected checkbox.
				//! will return -1 if no checkbox is selected
				virtual s32 getSelected() const;

				//! Set the currently active selected checkbox.
				//! Note that this will not trigger an MEGET_RADIOCHECKBOXGROUP_CHANGED event
				virtual void setSelected(s32 index);

				//! Activate the first added checkbox or activate another checkbox (when possible) if the active was removed.
				virtual void autoActivate(bool autoActivate);

				//! The last event was caused by an autoActivation
				//! Such events can be suppressed by calling autoActivate(false)
				virtual bool isAutoActivateEvent() const;

				//! Sets another color for the background
				virtual void setBackgroundColor(video::SColor color, bool drawBackground=true);

				//! Sets whether to draw the background
				virtual void setDrawBackground(bool draw);


				virtual const c8* getTypeName() const   { return "radiocheckboxgroup"; }
				virtual bool OnEvent(const SEvent &event);
				virtual void draw();

			protected:
				virtual void activateCheckBox(s32 index, bool sendEvent, bool autoActivated=false);

				virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
				virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

				bool Background;
				video::SColor BGColor;
				IGUICheckBox* Selected;
				bool AutoActivate;
				bool IsAutoActivateEvent;
				core::array<IGUICheckBox*> CheckBoxes;
		};

	} // namespace gui
} // namespace irr


#endif // _GUI_RADIOCHECKBOXGROUP_H
