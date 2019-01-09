
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include <pj/log.h>

#include <pj/types.h>

#include <pjlib.h>

#include <pjlib-util.h>

#include <pjnath.h>

#include <pjsip.h>

#include <pjsip_ua.h>

#include <pjsip_simple.h>

#include <pjsua-lib/pjsua.h>

#include <pjmedia.h>

#include <pjmedia-codec.h>


#pragma comment(lib,"ws2_32.lib")

#pragma comment(lib,"wsock32.lib")

#pragma comment(lib,"ole32.lib")

#pragma comment(lib,"dsound.lib")

#define THIS_FILE	"APP"

#define SIP_DOMAIN	"10.105.242.72"
#define SEVER_USER  "12345"
#define SIP_USER	"12345"

#define SIP_PASSWD	""
#define LOCAL_DOMAIN "10.210.54.173"
#define current_acc	pjsua_acc_get_default()
#define PJSUA_INVALID_ID -1

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	void OnBnClickInp(CString inp);
	CString m_str;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();


	//不知道是什么的定义
	bool cancel_announce = false;
	static bool no_tones;
	static bool ring_on;
	static int ring_cnt;
	static int ring_slot;
	static pjsua_call_id call_in;
	static pjsua_call_id current_call;

	//sip定义
	pjsua_acc_id acc_id;
	pjsua_config cfg;
	pjsua_logging_config log_cfg;
	pj_status_t status;
	pjsua_transport_config tran_cfg;
	pjsua_acc_config acc_cfg;
	pjsua_transport_id transport_id = -1;
	void initSip();
	void error_exit(const char *title, pj_status_t status);
	static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,
		pjsip_rx_data *rdata)
	{
		pjsua_call_info call_info;
		PJ_UNUSED_ARG(acc_id);
		PJ_UNUSED_ARG(rdata);

		pjsua_call_get_info(call_id, &call_info);

		//if (current_call == PJSUA_INVALID_ID)
		//	current_call = call_id;
		/* Start ringback */
		ring_start(call_id);

		PJ_LOG(3, (THIS_FILE, "Incoming call for account %d!\n"
		  "Media count: %d audio & %d video\n"
		  "From: %s\n"
		  "To: %s\n",
			acc_id,
			call_info.rem_aud_cnt,
			call_info.rem_vid_cnt,
			call_info.remote_info.ptr,
			call_info.local_info.ptr));

		CString msg;
		msg.Format(_T("Incoming call for account %d!\n"
		  "Media count: %d audio & %d video\n"
		  "From: %s\n"
			"To: %s\n"),
			acc_id,
			call_info.rem_aud_cnt,
			call_info.rem_vid_cnt,
			call_info.remote_info.ptr,
			call_info.local_info.ptr);
		AfxMessageBox(msg);
		call_in = call_id;
	}

	/* Callback called by the library when call's state has changed */
	static void on_call_state(pjsua_call_id call_id, pjsip_event *e)
	{
		pjsua_call_info call_info;

		PJ_UNUSED_ARG(e);

		pjsua_call_get_info(call_id, &call_info);

		if (call_info.state == PJSIP_INV_STATE_DISCONNECTED) {

			/* Stop all ringback for this call */
			//ring_stop(call_id);

			PJ_LOG(3, (THIS_FILE, "Call %d is DISCONNECTED [reason=%d (%s)]",
				call_id,
				call_info.last_status,
				call_info.last_status_text.ptr));

			if (call_id == current_call) {
				CString msg = "对方已挂断";
				AfxMessageBox(msg);
			}
		}
		if (call_info.state == PJSIP_INV_STATE_CONFIRMED)
		{
			CString msg = "对方已接通";
			current_call = call_id;
			AfxMessageBox(msg);
		}

	}

	static void ring_start(pjsua_call_id call_id)
	{
		if (no_tones)
			return;

		//if (call_data[call_id].ring_on)
		if (ring_on)
			return;

		ring_on = PJ_TRUE;

		if (++ring_cnt == 1 &&
			ring_slot != PJSUA_INVALID_ID)
		{
			pjsua_conf_connect(ring_slot, 0);
		}
	}
	afx_msg void OnBnClickedButtonans();
	afx_msg void OnBnClickedButtonansip();
	afx_msg void OnBnClickedButtonansat();
	afx_msg void OnBnClickedButtonandel();
	afx_msg void OnBnClickedButtonshurp();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonstar();
	afx_msg void OnBnClickedButtonancall();
	afx_msg void OnBnClickedButtonansadot();
	afx_msg void OnBnClickedButtonans2();
	afx_msg void OnBnClickedButtondtmf();
};