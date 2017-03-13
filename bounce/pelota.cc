#include <FL/Fl.h>
#include <FL/Fl_Widget.h>
#include <FL/Fl_draw.H> 
#include <FL/Fl_Double_Window.H>

#include <octave/oct.h>
#include <octave/parse.h> 

class Draw : public ::Fl_Widget
{
public:
  Draw(octave_function * fcn,int x, int y, int w, int h, const char *label)
    : fcn(fcn), Fl_Widget(x, y, w, h, label), x(x), y(y), h(h), w(w), px(w/2),py(h/2), t(0)
  {
    Fl::add_timeout(0.10, Timer_CB, (void*)this);
    A = h/2;
    omega = 0.5;
  }
  
  virtual void draw()
  {
    fl_color(0,0,0);	
    fl_rectf (x,y,w,h);
    fl_color(255,0,0);	
    fl_pie	(px-25, py-25, 50, 50, 0, 360);
  }
  
  static void Timer_CB(void *userdata) 
  {
    Draw *o = (Draw*)userdata;
    
    o->t += 0.10;
    o->py = o->h - abs(feval( o->fcn, octave_value(o-> omega * o->t))(0).double_value() * o->A) - 25;
    o->redraw();
    Fl::repeat_timeout(0.10, Timer_CB, userdata);
  }
    
  int x,y,h,w, px,py;
  double t, A, omega;
  octave_function *fcn;
};

DEFUN_DLD (pelota, args, nargout,
           "pelota [y(t)]")
{
  if( args.length() < 1 )
    print_usage ();
  else if (args(0).is_function_handle () || args(0).is_inline_function ())
  {
    Fl_Double_Window window(600, 600, "Pelota");  
    Draw draw(args(0).function_value (), 0, 0, 600, 600, "");
    window.show();
    Fl::run();
  }
    
  return octave_value_list ();
}
