#include <wx/utils.h>

#include "menu.h"

class CncomThread : public wxThread
{
public:
	CncomThread(CncomFrame *frame);
	~CncomThread();

	virtual void *Entry();
	//virtual void OnExit();

private:
	CncomFrame *m_frame;

}

CncomThread::CncomThread(CncomThread *frame) : wxThread()
{
	m_frame = frame;
}

CncomThread::~CncomThread()
{
	wxPrintf(_T("destruct CncomThread\r\n"));
}

void *CncomThread::Entry()
{
	while (!wxGetApp().m_thread_exit) {
		wxPrintf(_T("thread\r\n"));
		wxThread::Sleep(1000);
		//wxMicroSleep();
	}
}
