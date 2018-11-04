
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

#define SIP_USER	"12345"

#define SIP_PASSWD	""
#define LOCAL_DOMAIN "10.210.54.173"

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


	//sip定义
	pjsua_acc_id acc_id;
	pjsua_config cfg;
	pjsua_logging_config log_cfg;
	pj_status_t status;
	pjsua_transport_config tran_cfg;
	pjsua_acc_config acc_cfg;
	void initSip();
	void error_exit(const char *title, pj_status_t status);
};
