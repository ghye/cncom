#ifndef __MENU_H__
#define __MENU_H__

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

#include "deftype.h"

class CncomThread;

class CncomApp : public wxApp
{
public:
	// override base class virtuals
	// ----------------------------

	// this one is called on application startup and is a good place for the app
	// initialization (doing it here and not in the ctor allows to have an error
	// return: if OnInit() returns false, the application terminates)
	virtual bool OnInit();

};

//wxDECLARE_APP(CncomApp);

class CncomFrame : public wxFrame
{
public:
	// ctor(s) and dtor
	CncomFrame(const wxString& title);
	virtual ~CncomFrame();

	void OnTimer(wxTimerEvent& event);

public:
	char m_thread_exit;
	wxMutex		*m_mutex;
	wxCondition	*m_cond;

protected:
	void OnClose(wxCloseEvent& event);

private:
	void doOpenCloseCom(wxCommandEvent& event);
	void OnHexCheckBox(wxCommandEvent& event);
	CncomThread *doCreateThread();
	void doToHex(wxArrayUchar& aUchar, int head, int tail, wxTextCtrl *textctrl);
	void doToCharacter(wxArrayUchar& aUchar, int head, int tail, wxTextCtrl *textctrl);

	wxPanel		*m_panel;
	wxTextCtrl 	*m_textctrl;
	wxButton	*m_OpenCloseCom;
	wxCheckBox 	*m_hex_choice;
	wxTextCtrl	*m_ComPath;
	wxChoice	*m_ChoiceBps;
	wxChoice	*m_ChoiceDataLen;
	wxChoice	*m_ChoiceParity;
	wxChoice	*m_ChoiceStopBits;

	CncomThread	*m_thread;
	wxArrayUchar	m_buf;

	wxTimer m_timer;

	DECLARE_EVENT_TABLE()
};

#endif
