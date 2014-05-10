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

#include <wx/timer.h>

enum
{
	CNCOM_ID_TEXT = wxID_HIGHEST + 1,
	CNCOM_ID_OPEN_CLOSE_BUTTON,
	CNCOM_ID_HEX_CHOICE,
	CNCOM_ID_TEXT_COM_DEV,
	CNCOM_ID_BPS_CHOICE,
	CNCOM_ID_DATALEN_CHOICE,
	CNCOM_ID_CRC_CHOICE,
	CNCOM_ID_STOP_BITS_CHOICE,


	CNCOM_ID_TIMER,
};

wxString g_string_open = wxString(_T("open"));
wxString g_string_close = wxString(_T("close"));

IMPLEMENT_APP(CncomApp)

BEGIN_EVENT_TABLE(CncomFrame, wxFrame)
	EVT_BUTTON(CNCOM_ID_OPEN_CLOSE_BUTTON, CncomFrame::doOpenCloseCom)
	EVT_CHECKBOX(CNCOM_ID_HEX_CHOICE, CncomFrame::OnHexCheckBox)
	EVT_CLOSE(CncomFrame::OnClose)
	EVT_TIMER(CNCOM_ID_TIMER, CncomFrame::OnTimer)
END_EVENT_TABLE()


bool CncomApp::OnInit()
{
	wxFrame *frame = new CncomFrame(_T("wxListBox sample"));
	frame->Show();

	return true;
}

CncomFrame::CncomFrame(const wxString& title)
             : wxFrame(NULL, wxID_ANY, title, wxPoint(100, 100)), m_timer(this, CNCOM_ID_TIMER)
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
	textctrl->Clear();
	m_textctrl = textctrl;

	sizer_up->Add(textctrl, 0, wxLEFT | wxRIGHT, 5);

	wxSizer *sizer_open_close = new wxBoxSizer(wxHORIZONTAL);
	wxButton *btn_open_close = new wxButton(m_panel, CNCOM_ID_OPEN_CLOSE_BUTTON, g_string_open);
	m_OpenCloseCom = btn_open_close;
	wxTextCtrl *text_com_dev = new wxTextCtrl(m_panel, CNCOM_ID_TEXT_COM_DEV, _T("/dev/ttyUSB0"));
	m_ComPath = text_com_dev;
	m_hex_choice = new wxCheckBox(m_panel, CNCOM_ID_HEX_CHOICE,
		_T("Hex"), wxDefaultPosition, wxDefaultSize);
	sizer_open_close->Add(btn_open_close, 0, wxLEFT | wxRIGHT, 5);
	sizer_open_close->Add(text_com_dev, 0, wxLEFT | wxRIGHT, 5);
	sizer_open_close->Add(m_hex_choice, 0, wxLEFT | wxRIGHT, 5);

	sizer_down_p1->Add(sizer_open_close, 0, wxLEFT | wxRIGHT, 5);



	wxGridSizer *sizer_param_set = new wxGridSizer(5, 2, 0, 0);

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
	as_bps.Add(_T("128000"));
	as_bps.Add(_T("256000"));
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

#if wxUSE_STATUSBAR
	CreateStatusBar(2);
#endif

	m_panel->SetSizer(sizer_top);

	sizer_top->Fit(this);
	sizer_top->SetSizeHints(this);

	/* create and run thread */
	m_thread_exit = 0;
	m_mutex = new wxMutex();
	m_cond = new wxCondition(*m_mutex);
	m_mutex->Lock();
	wxPrintf(_T("thread 1\n"));
	m_thread = doCreateThread();
	wxPrintf(_T("thread 2\n"));
	if (m_thread != NULL) {
		wxPrintf(_T("thread 3\n"));
		m_thread->Run();
	}
	wxPrintf(_T("thread runing now\n"));

	m_timer.Start(10);
}

CncomFrame::~CncomFrame()
{
}

void CncomFrame::OnTimer(wxTimerEvent& event)
{
	int len, i;
	int head;
	unsigned char *p;

	len = m_thread->GetBuf(&p);
	if (len > 0) {
		head = m_buf.GetCount();
		for (i = 0; i < len; i++)
			m_buf.Add(p[i]);
		len = m_buf.GetCount();
		if (m_hex_choice->IsChecked())
			doToHex(m_buf, head, len, m_textctrl);
		else
			doToCharacter(m_buf, head, len, m_textctrl);

#if wxUSE_STATUSBAR
		UpdateStatusRead(len);
		UpdateStatusTransmit(len - head);
#endif
	}
}

void CncomFrame::OnClose(wxCloseEvent& event)
{
	m_timer.Stop();

	if (m_thread != NULL) {
		m_thread_exit = 1;
		while (m_thread_exit == 1) {
			m_cond->Wait();
		}
		m_mutex->Unlock();
		delete m_cond;
		delete m_mutex;
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

void CncomFrame::OnHexCheckBox(wxCommandEvent& event)
{
	if (event.IsChecked()) {
		wxPrintf(_T("Hex checked\n"));
		m_textctrl->Clear();
		doToHex(m_buf, 0, m_buf.GetCount(), m_textctrl);
	} else {
		wxPrintf(_T("Hex unchecked\n"));
		m_textctrl->Clear();
		doToCharacter(m_buf, 0, m_buf.GetCount(), m_textctrl);
	}

	event.Skip();
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


void CncomFrame::doToHex(wxArrayUchar& aUchar, int head, int tail, wxTextCtrl *textctrl)
{
	int i;
	char buf[3];

	for (i = head; i < tail; i++) {
		sprintf(buf, "%.2X ", aUchar.Item(i));
		textctrl->AppendText(wxString::FromUTF8(buf));
	}
}

void CncomFrame::doToCharacter(wxArrayUchar& aUchar, int head, int tail, wxTextCtrl *textctrl)
{
	int i;
	char buf[3];

	for (i = head; i < tail; i++) {
		sprintf(buf, "%c", aUchar.Item(i));
		textctrl->AppendText(wxString::FromUTF8(buf));
	}
}

#if wxUSE_STATUSBAR
void CncomFrame::UpdateStatusRead(int v)
{
	wxString msg;
	msg.Printf(wxT("R: %d"), v);
	SetStatusText(msg, 1);
}

void CncomFrame::UpdateStatusTransmit(int v)
{
	wxString msg;
	msg.Printf(wxT("T: %d"), v);
	SetStatusText(msg, 0);
}
#endif
