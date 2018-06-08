#include <hx/CFFI.h>
#include <graphics/RenderEvent.h>


namespace lime {
	
	
	ValuePointer* RenderEvent::callback = 0;
	ValuePointer* RenderEvent::eventObject = 0;
	
	static int id_type;
	static bool init = false;
	
	
	RenderEvent::RenderEvent () {
		
		type = RENDER;
		
	}
	
	
	void RenderEvent::Dispatch (RenderEvent* event) {
		
		if (RenderEvent::callback) {
			
			if (RenderEvent::eventObject->IsCFFIValue ()) {
				
				if (!init) {
					
					id_type = val_id ("type");
					
				}
				
				value object = (value)RenderEvent::eventObject->Get ();
				
				alloc_field (object, id_type, alloc_int (event->type));
				
			} else {
				
				HL_RenderEvent* eventObject = (HL_RenderEvent*)RenderEvent::eventObject->Get ();
				
				eventObject->type = event->type;
				
			}
			
			RenderEvent::callback->Call ();
			
		}
		
	}
	
	
}