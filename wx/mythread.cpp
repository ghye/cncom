#include <wx/utils.h>

#include "mythread.h"
#include "menu.h"

//DECLARE_APP(CncomApp);

CncomThread::CncomThread(CncomFrame *frame) : wxThread()
{
	wxPrintf(wxT("struct CncomThread\n"));
	m_frame = frame;
	head = 0;
	tail = 0;
}

CncomThread::~CncomThread()
{
	wxPrintf(wxT("destruct CncomThread\n"));
}

void *CncomThread::Entry()
{
	unsigned char v = 0xfe;

	while (m_frame->m_thread_exit == 0) {
		wxPrintf(wxT("write:\n"));
		AddBuf(v);
		wxPrintf(wxT("%d\n"), v);
		v++;
		/*AddBuf(v);
		wxPrintf(wxT("%d \n"), v);
		v++;*/
		
		wxThread::Sleep(2000);
		//wxMicroSleep(2000000);
	}

	return NULL;
}

void CncomThread::OnExit()
{
	m_frame->m_thread_exit = 0;
	wxMutexLocker lock(*m_frame->m_mutex);
	m_frame->m_cond->Broadcast();
}

void CncomThread::AddBuf(unsigned char v)
{
	m_buf[tail] = v;
	tail++;
	if (tail >= BUF_LEN_THREAD)
		tail = 0;
}

int CncomThread::GetBuf(unsigned char **p)
{
	int len;
	int lhead, ltail;

	lhead = head;
	ltail = tail;

	if (ltail >= lhead) {
		len = ltail - lhead;
	} else {
		len = BUF_LEN_THREAD - lhead;
	}
	head = lhead + len;
	if (head >= BUF_LEN_THREAD)
		head = 0;
	*p = m_buf + lhead;

	return len;
}
