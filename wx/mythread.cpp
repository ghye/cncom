#include <wx/utils.h>

#include "mythread.h"
#include "menu.h"

//DECLARE_APP(CncomApp);

CncomThread::CncomThread(CncomFrame *frame) : wxThread()
{
	wxPrintf(_T("struct CncomThread\n"));
	m_frame = frame;
}

CncomThread::~CncomThread()
{
	wxPrintf(_T("destruct CncomThread\n"));
}

void *CncomThread::Entry()
{
	//while (!wxGetApp().m_thread_exit) {
	while (m_frame->m_thread_exit == 0) {
		wxPrintf(_T("thread\n"));
		wxThread::Sleep(2000);
		//wxMicroSleep(2000000);
	}
}

void CncomThread::OnExit()
{
	m_frame->m_thread_exit = 0;
	wxMutexLocker lock(*m_frame->m_mutex);
	m_frame->m_cond->Broadcast();
}
