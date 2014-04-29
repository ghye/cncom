/////////////////////////////////////////////////////////////////////////////
// Name:        lboxtest.cpp
// Purpose:     wxListBox sample
// Author:      Vadim Zeitlin
// Id:          $Id: lboxtest.cpp 41547 2006-10-02 05:36:31Z PC $
// Copyright:   (c) 2000 Vadim Zeitlin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers
#ifndef WX_PRECOMP
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

enum
{
	CNCOM_ID_TEXT = wxID_HIGHEST + 1,
	CNCOM_ID_OPEN_CLOSE_BUTTON,
	CNCOM_ID_TEXT_COM_DEV,
	CNCOM_ID_BPS_CHOICE,
	CNCOM_ID_DATALEN_CHOICE,
	CNCOM_ID_CRC_CHOICE,
	CNCOM_ID_STOP_BITS_CHOICE,
};

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

class CncomFrame : public wxFrame
{
public:
	// ctor(s) and dtor
	CncomFrame(const wxString& title);
	virtual ~CncomFrame();

private:
	wxPanel* m_panel;

	//DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(CncomApp)

bool CncomApp::OnInit()
{
	wxFrame *frame = new CncomFrame(_T("wxListBox sample"));
	frame->Show();

	return true;
}

CncomFrame::CncomFrame(const wxString& title)
             : wxFrame(NULL, wxID_ANY, title, wxPoint(100, 100))
{
	m_panel = new wxPanel(this, wxID_ANY);
	
	wxSizer *sizer_top = new wxBoxSizer(wxVERTICAL);
	wxSizer *sizer_up = new wxBoxSizer(wxVERTICAL);
	wxSizer *sizer_down = new wxBoxSizer(wxVERTICAL);
	wxSizer *sizer_down_p1 = new wxBoxSizer(wxVERTICAL);
	wxSizer *sizer_down_p2 = new wxBoxSizer(wxHORIZONTAL);

	wxTextCtrl *textctrl = new wxTextCtrl(m_panel, CNCOM_ID_TEXT, _T("cncom text"),
				wxDefaultPosition, wxSize(800, 400), wxTE_MULTILINE);
	textctrl->SetEditable(false);
	textctrl->AppendText(_T("cncom text string"));

	sizer_up->Add(textctrl, 0, wxLEFT | wxRIGHT, 5);

	wxSizer *sizer_open_close = new wxBoxSizer(wxHORIZONTAL);
	wxButton *btn_open_close = new wxButton(m_panel, CNCOM_ID_OPEN_CLOSE_BUTTON, _T("open"));
	wxTextCtrl *text_com_dev = new wxTextCtrl(m_panel, CNCOM_ID_TEXT_COM_DEV, _T("/dev/ttyUSB0"));
	sizer_open_close->Add(btn_open_close, 0, wxLEFT | wxRIGHT, 5);
	sizer_open_close->Add(text_com_dev, 0, wxLEFT | wxRIGHT, 5);
	sizer_down_p1->Add(sizer_open_close, 0, wxLEFT | wxRIGHT, 5);



	wxFlexGridSizer *sizer_param_set = new wxFlexGridSizer(2, 2, 0, 0);

	wxStaticText *text_bps = new wxStaticText(m_panel, wxID_ANY, _T("Bps"));
	wxStaticText *text_data_len = new wxStaticText(m_panel, wxID_ANY, _T("DataLen"));
	wxStaticText *text_parity = new wxStaticText(m_panel, wxID_ANY, _T("Parity"));
	wxStaticText *text_stop_bits = new wxStaticText(m_panel, wxID_ANY, _T("StopBits"));
	wxArrayString as_bps;
	as_bps.Add(_T("300"));
	as_bps.Add(_T("1200"));
	as_bps.Add(_T("2400"));
	as_bps.Add(_T("4800"));
	as_bps.Add(_T("9600"));
	as_bps.Add(_T("19200"));
	as_bps.Add(_T("38400"));
	as_bps.Add(_T("115200"));
	wxChoice *text_bps_choice = new wxChoice(m_panel, CNCOM_ID_BPS_CHOICE, wxDefaultPosition, wxDefaultSize, as_bps);
	wxArrayString as_data_len;
	as_data_len.Add(_T("8"));
	as_data_len.Add(_T("9"));
	wxChoice *text_data_len_choice = new wxChoice(m_panel, CNCOM_ID_DATALEN_CHOICE, wxDefaultPosition, wxDefaultSize, as_data_len);
	wxArrayString as_parity;
	as_parity.Add(_T("NO"));
	as_parity.Add(_T("ODD"));
	as_parity.Add(_T("EVEN"));
	wxChoice *text_parity_choice = new wxChoice(m_panel, CNCOM_ID_CRC_CHOICE, wxDefaultPosition, wxDefaultSize, as_parity);
	wxArrayString as_stop_bits;
	as_stop_bits.Add(_T("1"));
	as_stop_bits.Add(_T("1.5"));
	as_stop_bits.Add(_T("2"));
	wxChoice *text_stop_bits_choice = new wxChoice(m_panel, CNCOM_ID_STOP_BITS_CHOICE, wxDefaultPosition, wxDefaultSize, as_stop_bits);
	sizer_param_set->Add(text_bps, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	sizer_param_set->Add(text_bps_choice);
	sizer_param_set->Add(text_data_len, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	sizer_param_set->Add(text_data_len_choice);
	sizer_param_set->Add(text_parity, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	sizer_param_set->Add(text_parity_choice);
	sizer_param_set->Add(text_stop_bits, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	sizer_param_set->Add(text_stop_bits_choice);

	sizer_down_p2->Add(sizer_param_set, 0, wxLEFT | wxRIGHT, 5);





	sizer_down->Add(sizer_down_p1, 0, wxLEFT | wxRIGHT, 5);
	sizer_down->Add(sizer_down_p2, 0, wxLEFT | wxRIGHT, 5);

	sizer_top->Add(sizer_up, 0, wxLEFT | wxRIGHT, 5);
	sizer_top->Add(sizer_down, 0, wxLEFT | wxRIGHT, 5);

	m_panel->SetSizer(sizer_top);

	sizer_top->Fit(this);
	sizer_top->SetSizeHints(this);
}

CncomFrame::~CncomFrame()
{
}
