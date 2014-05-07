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

#include "menu.h"
#include "mythread.h"

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

wxString g_string_open = wxString(_T("open"));
wxString g_string_close = wxString(_T("close"));

IMPLEMENT_APP(CncomApp)

BEGIN_EVENT_TABLE(CncomFrame, wxFrame)
	EVT_BUTTON(CNCOM_ID_OPEN_CLOSE_BUTTON, CncomFrame::doOpenCloseCom)
	EVT_CLOSE(CncomFrame::OnClose)
END_EVENT_TABLE()


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
	wxButton *btn_open_close = new wxButton(m_panel, CNCOM_ID_OPEN_CLOSE_BUTTON, g_string_open);
	m_OpenCloseCom = btn_open_close;
	wxTextCtrl *text_com_dev = new wxTextCtrl(m_panel, CNCOM_ID_TEXT_COM_DEV, _T("/dev/ttyUSB0"));
	m_ComPath = text_com_dev;
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
	m_ChoiceBps = text_bps_choice;
	wxArrayString as_data_len;
	as_data_len.Add(_T("8"));
	as_data_len.Add(_T("9"));
	wxChoice *text_data_len_choice = new wxChoice(m_panel, CNCOM_ID_DATALEN_CHOICE, wxDefaultPosition, wxDefaultSize, as_data_len);
	m_ChoiceDataLen = text_data_len_choice;
	wxArrayString as_parity;
	as_parity.Add(_T("NO"));
	as_parity.Add(_T("ODD"));
	as_parity.Add(_T("EVEN"));
	wxChoice *text_parity_choice = new wxChoice(m_panel, CNCOM_ID_CRC_CHOICE, wxDefaultPosition, wxDefaultSize, as_parity);
	m_ChoiceParity = text_parity_choice;
	wxArrayString as_stop_bits;
	as_stop_bits.Add(_T("1"));
	as_stop_bits.Add(_T("1.5"));
	as_stop_bits.Add(_T("2"));
	wxChoice *text_stop_bits_choice = new wxChoice(m_panel, CNCOM_ID_STOP_BITS_CHOICE, wxDefaultPosition, wxDefaultSize, as_stop_bits);
	m_ChoiceStopBits = text_stop_bits_choice;
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


	/* create and run thread */
	m_thread_exit = 0;
	wxPrintf(_T("thread 1\n"));
	m_thread = doCreateThread();
	wxPrintf(_T("thread 2\n"));
	if (m_thread != NULL) {
		wxPrintf(_T("thread 3\n"));
		m_thread->Run();
	}
	wxPrintf(_T("thread runing now\n"));
}

CncomFrame::~CncomFrame()
{
}

void CncomFrame::OnClose(wxCloseEvent& event)
{
	if (m_thread != NULL) {
		m_thread_exit = 1;
		while (m_thread_exit == 1)
			wxThread::Sleep(1);
		//delete m_thread;
		m_thread = NULL;
	}

	wxPrintf(_T("frame closed\n"));

	event.Skip();	/* must do that */
}

void CncomFrame::doOpenCloseCom(wxCommandEvent& event)
{
	wxString str = m_OpenCloseCom->GetLabel();
	wxString path = m_ComPath->GetLineText(0);
	wxPrintf(_T("Do %s\r\n"), str.c_str());
	wxPrintf(_T("Path %s\r\n"), path.c_str());
	if (str == g_string_open)
		m_OpenCloseCom->SetLabel(g_string_close);
	else
		m_OpenCloseCom->SetLabel(g_string_open);

	wxPrintf(_T("bps %s\r\n"), (m_ChoiceBps->GetString(m_ChoiceBps->GetSelection())).c_str());
	wxPrintf(_T("datalen %s\r\n"), (m_ChoiceDataLen->GetString(m_ChoiceDataLen->GetSelection())).c_str());
	wxPrintf(_T("parity %s\r\n"), (m_ChoiceParity->GetString(m_ChoiceParity->GetSelection())).c_str());
	wxPrintf(_T("stopbits %s\r\n"), (m_ChoiceStopBits->GetString(m_ChoiceStopBits->GetSelection())).c_str());
}

CncomThread *CncomFrame::doCreateThread()
{
	CncomThread *thread = new CncomThread(this);
	if (thread->Create() != wxTHREAD_NO_ERROR) {
		wxPrintf(_T("thread create error\n"));
		delete thread;
		thread = NULL;
	}

	return thread;
}
