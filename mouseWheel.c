/*
	mouseWheel
	tomohiro nagasaki blurrednote@me.com

*/

#include "ext.h"
#include "ext_obex.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

////////////////////////// object struct
typedef struct _mouseWheel 
{
	t_object ob;
	void *outlet_wheel;
	id evGlobalHander;
	id evLocalHander;
} t_mouseWheel;

///////////////////////// function prototypes
//// standard set
void *mouseWheel_new(t_symbol *s, long argc, t_atom *argv);
void mouseWheel_free(t_mouseWheel *x);
void mouseWheel_assist(t_mouseWheel *x, void *b, long m, long a, char *s);

//////////////////////// global class pointer variable
void *mouseWheel_class;


int C74_EXPORT main(void)
{	
	t_class *c;
	c = class_new("mouseWheel", (method)mouseWheel_new, (method)mouseWheel_free, (long)sizeof(t_mouseWheel), NULL, A_GIMME, 0);
	
    class_addmethod(c, (method)mouseWheel_assist, "assist", A_CANT, 0);
	class_register(CLASS_BOX, c);
	mouseWheel_class = c;
	return 0;
}

void mouseWheel_assist(t_mouseWheel *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		
	} 
	else {	// outlet
		switch (a) {
			case 0:
				sprintf(s, "local mousewheel event");
				break;
			default:
				break;
		}
				
	}
}

void mouseWheel_free(t_mouseWheel *x)
{
	[NSEvent removeMonitor:x->evLocalHander];
	
	if (x->evGlobalHander) {
		[NSEvent removeMonitor:x->evGlobalHander];		
	}
	
}

void *mouseWheel_new(t_symbol *s, long argc, t_atom *argv)
{
	t_mouseWheel *x = NULL;
    
	if ((x = (t_mouseWheel *)object_alloc(mouseWheel_class))) {
		
		// I don't need any inlet but i couldn't find code about deleting default inlet...
		
		
		// create outlet
		x->outlet_wheel = floatout(x);
		
		// NSEvent monitor
		
		/*
		 global monitor
		 at your own risk.
		 
		x->evGlobalHander = [NSEvent addGlobalMonitorForEventsMatchingMask:NSScrollWheelMask
																   handler:^(NSEvent *ev){
																	   CGFloat y = [ev scrollingDeltaY];
																	   outlet_float(x->outlet_wheel, y);
																   }];
		 */
		
		x->evLocalHander = [NSEvent addLocalMonitorForEventsMatchingMask:NSScrollWheelMask
																 handler:^NSEvent *(NSEvent *ev) {
																	 CGFloat y = [ev scrollingDeltaY];
																	 outlet_float(x->outlet_wheel, y);
																	 return ev;
																 }];
	}
	return (x);
}
