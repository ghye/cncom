#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__

// for compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers
#ifndef WX_PRECOMP
	#include <wx/app.h>
	#include <wx/thread.h>
	#include "wx/wx.h"
	#include "wx/app.h"
	#include "wx/frame.h"
	#include "wx/dcclient.h"

	#include "wx/button.h"
	#include "wx/checkbox.h"
	#include "wx/checklst.h"
	#include "wx/listbox.h"
	#include "wx/radiobox.h"
	#include "wx/radiobut.h"
	#include "wx/statbox.h"
	#include "wx/stattext.h"
	#include "wx/textctrl.h"
	#include "wx/choice.h"
#endif

#include "wx/sizer.h"

#ifdef __WXUNIVERSAL__
    #include "wx/univ/theme.h"
#endif // __WXUNIVERSAL__

class CncomFrame;

class CncomThread : public wxThread
{
public:
	CncomThread(CncomFrame *frame);
	~CncomThread();

	virtual void *Entry();
	virtual void OnExit();

private:
	CncomFrame *m_frame;

};

#endif
