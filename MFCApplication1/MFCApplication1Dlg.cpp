
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* Ringtones		    US	       UK  */
#define RINGBACK_FREQ1	    440	    /* 400 */
#define RINGBACK_FREQ2	    480	    /* 450 */
#define RINGBACK_ON	    2000    /* 400 */
#define RINGBACK_OFF	    4000    /* 200 */
#define RINGBACK_CNT	    1	    /* 2   */
#define RINGBACK_INTERVAL   4000    /* 2000 */

#define RING_FREQ1	    800
#define RING_FREQ2	    640
#define RING_ON		    200
#define RING_OFF	    100
#define RING_CNT	    3
#define RING_INTERVAL	    3000

bool CMFCApplication1Dlg::no_tones = false;
bool CMFCApplication1Dlg::ring_on = PJ_FALSE;
int CMFCApplication1Dlg::ring_cnt = 0;
bool CMFCApplication1Dlg::ringback_on = PJ_FALSE;
int CMFCApplication1Dlg::ringback_cnt = 0;
pjsua_call_id CMFCApplication1Dlg::call_in = PJSUA_INVALID_ID;
pjsua_call_id CMFCApplication1Dlg::current_call = PJSUA_INVALID_ID;
pjsua_call_id CMFCApplication1Dlg::ringback_slot = PJSUA_INVALID_ID;
pjsua_call_id CMFCApplication1Dlg::ring_slot = PJSUA_INVALID_ID;
CString CMFCApplication1Dlg::stage_msg = "点击下方按键或者直接键盘输入sip uri，点呼叫";
CString CMFCApplication1Dlg::static_msg = "点击下方按键或者直接键盘输入sip uri，点呼叫";



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_str);
}

//消息定义
BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()//响应控制指令
	ON_WM_PAINT()	//绘图消息
	ON_WM_TIMER() //
	ON_WM_QUERYDRAGICON()	//响应用户拖动最小化窗口时获得光标
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication1Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication1Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTONANS, &CMFCApplication1Dlg::OnBnClickedButtonans)
	ON_BN_CLICKED(IDC_BUTTONANSIP, &CMFCApplication1Dlg::OnBnClickedButtonansip)
	ON_BN_CLICKED(IDC_BUTTONANSAT, &CMFCApplication1Dlg::OnBnClickedButtonansat)
	ON_BN_CLICKED(IDC_BUTTONANDEL, &CMFCApplication1Dlg::OnBnClickedButtonandel)
	ON_BN_CLICKED(IDC_BUTTONSHURP, &CMFCApplication1Dlg::OnBnClickedButtonshurp)
	ON_BN_CLICKED(IDC_BUTTON0, &CMFCApplication1Dlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTONSTAR, &CMFCApplication1Dlg::OnBnClickedButtonstar)
	ON_BN_CLICKED(IDC_BUTTONANCALL, &CMFCApplication1Dlg::OnBnClickedButtonancall)
	ON_BN_CLICKED(IDC_BUTTONANSADOT, &CMFCApplication1Dlg::OnBnClickedButtonansadot)
	ON_BN_CLICKED(IDC_BUTTONDTMF, &CMFCApplication1Dlg::OnBnClickedButtondtmf)
	ON_BN_CLICKED(IDC_BUTTONREJCET, &CMFCApplication1Dlg::OnBnClickedButtonrejcet)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	HBITMAP hBitmapCollection;
	hBitmapCollection = (HBITMAP)::LoadImage(NULL, "res/callout.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	((CButton *)GetDlgItem(IDC_BUTTONANCALL))->SetBitmap(hBitmapCollection);
	hBitmapCollection = (HBITMAP)::LoadImage(NULL, "res/ansin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	((CButton *)GetDlgItem(IDC_BUTTONANS))->SetBitmap(hBitmapCollection);
	hBitmapCollection = (HBITMAP)::LoadImage(NULL, "res/reject.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	((CButton *)GetDlgItem(IDC_BUTTONREJCET))->SetBitmap(hBitmapCollection);

	SetTimer(1, 1000, NULL);
	// TODO: 在此添加额外的初始化代码
	//MessageBox(_T("open!"));
	initSip();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

/* Display error and exit application */

void CMFCApplication1Dlg :: error_exit(const char *title, pj_status_t status)
{
	CString errMsg(title);
	MessageBox(errMsg);
	pjsua_perror(THIS_FILE, title, status);
	//pjsua_destroy();
	//exit(1);
}

void CMFCApplication1Dlg::OnTimer(UINT nIDEvent) {
	{
		//检查文字
		CString showing;
		GetDlgItem(IDC_STATIC)->GetWindowTextA(showing);
		if(showing != stage_msg)
			SetDlgItemText(IDC_STATIC, stage_msg);
	}
	{
		//检查声音
		if (current_call == PJSUA_INVALID_ID) {
			if (ringback_on) ring_stop(current_call);
		}
		if (call_in == PJSUA_INVALID_ID) {
			if (ring_on) ring_stop(current_call);
		}
	}
}



/* Callback called by the library when call's media state has changed */
static void on_call_media_state(pjsua_call_id call_id)

{
	pjsua_call_info ci;
	pjsua_call_get_info(call_id, &ci);
	if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE) {
		// When media is active, connect call to sound device.
		pjsua_conf_connect(ci.conf_slot, 0);
		pjsua_conf_connect(0, ci.conf_slot);
	}
}

/*处理收到的dtmf消息*/
static void call_on_dtmf_callback(pjsua_call_id call_id, int dtmf) {
	CString msg;
	msg.Format(_T("收到dtmf消息:%d"),dtmf);
	AfxMessageBox(msg);
}

void CMFCApplication1Dlg::initSip() {
	/*创建pjsua实例*/
	status = pjsua_create();
	pj_pool_t *tmp_pool;
	tmp_pool = pjsua_pool_create("tmp-pjsua", 1000, 1000);

	if (status != PJ_SUCCESS) error_exit("Error in pjsua_create()", status);

	/* 初始化pjsua，设置回调函数*/
	{
		pjsua_config_default(&cfg);
		cfg.cb.on_incoming_call = &on_incoming_call;
		cfg.cb.on_call_media_state = &on_call_media_state;
		cfg.cb.on_call_state = &on_call_state;
		cfg.cb.on_dtmf_digit = &call_on_dtmf_callback;

		pjsua_logging_config_default(&log_cfg);
		log_cfg.console_level = 4;
		status = pjsua_init(&cfg, &log_cfg, NULL);
		if (status != PJ_SUCCESS) error_exit("Error in pjsua_init()", status);
	}

	/* Add UDP transport. */
	{
		pjsua_transport_config_default(&tran_cfg);
		tran_cfg.port = 5060;
		status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &tran_cfg, &transport_id);
		if (status != PJ_SUCCESS) error_exit("Error creating transport", status);
	}

	/* Initialization is done, now start pjsua */
	status = pjsua_start();
	if (status != PJ_SUCCESS) error_exit("Error starting pjsua", status);

	/* Add UDP transport unless it's disabled. 这种是直接产生 sip:localhost的，不用注册的样子*/
	{
		pjsip_transport_type_e type = PJSIP_TRANSPORT_UDP;
		/* Add local account */
		pjsua_acc_add_local(transport_id, PJ_TRUE, &acc_id);
		/* Adjust local account config based on pjsua app config */
		{
			pjsua_acc_config acc_cfg;
			pjsua_acc_get_config(acc_id, tmp_pool, &acc_cfg);
			pjsua_acc_modify(acc_id, &acc_cfg);
		}
		pjsua_acc_set_online_status(current_acc, PJ_TRUE);
	}

	/* Create ringback tones */
	{
		unsigned samples_per_frame;
		pjmedia_tone_desc tone[RING_CNT + RINGBACK_CNT];
		pj_str_t name;

		/* Ringback tone (call is ringing) */
		name = pj_str("ringback");
		status = pjmedia_tonegen_create2(tmp_pool, &name,
			8000, 2, 320,  //设置回铃音的采样率、通道数、帧数
			16, PJMEDIA_TONEGEN_LOOP,
			&this->ringback_port);
		if (status != PJ_SUCCESS)
			error_exit("Create tone failed", status);

		pj_bzero(&tone, sizeof(tone));
		for (int i = 0; i<RINGBACK_CNT; ++i) {
			tone[i].freq1 = RINGBACK_FREQ1;
			tone[i].freq2 = RINGBACK_FREQ2;
			tone[i].on_msec = RINGBACK_ON;
			tone[i].off_msec = RINGBACK_OFF;
		}
		tone[RINGBACK_CNT - 1].off_msec = RINGBACK_INTERVAL;
		
		//铃声设置绑定到媒体端口
		pjmedia_tonegen_play(this->ringback_port, RINGBACK_CNT, tone,
			PJMEDIA_TONEGEN_LOOP);
		status = pjsua_conf_add_port(tmp_pool, this->ringback_port,
			&this->ringback_slot);
		if (status != PJ_SUCCESS)
			error_exit("add port failed", status);

		/* Ring (to alert incoming call) */
		name = pj_str("ring");
		status = pjmedia_tonegen_create2(tmp_pool, &name,
			32000,2,640,
			16, PJMEDIA_TONEGEN_LOOP,
			&this->ring_port);
		if (status != PJ_SUCCESS)
			error_exit("Create tone failed2", status);

		for (int i = 0; i<RING_CNT; ++i) {
			tone[i].freq1 = RING_FREQ1;
			tone[i].freq2 = RING_FREQ2;
			tone[i].on_msec = RING_ON;
			tone[i].off_msec = RING_OFF;
		}
		tone[RING_CNT - 1].off_msec = RING_INTERVAL;

		pjmedia_tonegen_play(this->ring_port, RING_CNT,
			tone, PJMEDIA_TONEGEN_LOOP);

		status = pjsua_conf_add_port(tmp_pool, this->ring_port,
			&this->ring_slot);
		if (status != PJ_SUCCESS)
			error_exit("add port failed2", status);

	}
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("1"));
}

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("2"));
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("3"));
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("4"));
}


void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("5"));
}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("6"));
}


void CMFCApplication1Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("7"));
}


void CMFCApplication1Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("8"));
}


void CMFCApplication1Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("9"));
}

void CMFCApplication1Dlg::OnBnClickedButton0()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("0"));
}

void CMFCApplication1Dlg::OnBnClickedButtonansip()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("sip:"));
}


void CMFCApplication1Dlg::OnBnClickedButtonansat()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("@"));
}

void CMFCApplication1Dlg::OnBnClickedButtonshurp()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("#"));
}

void CMFCApplication1Dlg::OnBnClickedButtonansadot()
{
	OnBnClickInp(_T("."));
}

void CMFCApplication1Dlg::OnBnClickedButtonstar()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickInp(_T("*"));
}

void CMFCApplication1Dlg::OnBnClickInp(CString inp)
{
	UpdateData(true);//修改Edit显示数之前需要这样锁一下
	m_str = m_str + inp;
	UpdateData(false);
}

void CMFCApplication1Dlg::OnBnClickedButtonandel()
{
	// 删除键，删去输入的最后一个
	UpdateData(true);
	int m_len = m_str.GetLength();
	if ( m_len == 0)
		return;
	else {
		m_str.Delete(m_len - 1, 1);
	}
	UpdateData(false);
}

void CMFCApplication1Dlg::OnBnClickedButtonans()
{
	// 接听/拒绝:  如果当前没有通话，则接听
	if (current_call == PJSUA_INVALID_ID) {
		//检查接听
		if (call_in == PJSUA_INVALID_ID) {
			MessageBox(_T("Nothing answer"));
		}
		else {
			pjsua_call_answer(call_in, 200, NULL, NULL);
			current_call = call_in;
			cancel_announce = false;
		}
	}
	
}

void CMFCApplication1Dlg::checkinput() {
	CString edit_input;
	GetDlgItem(IDC_EDIT2)->GetWindowTextA(edit_input);
	if (m_str != edit_input)
		m_str = edit_input;
}

void CMFCApplication1Dlg::OnBnClickedButtonancall()
{
	// 拨号键
	if (current_call != PJSUA_INVALID_ID) {
		MessageBox(_T("正在通话中，请挂断后再拨"));
	}
	else if (call_in != PJSUA_INVALID_ID) {
		MessageBox(_T("有未处理的未接电话，请挂断后再拨"));
	}
	else {
		checkinput();//校正输入框
		pj_str_t uri = pj_str(m_str.GetBuffer(0));
		pjsua_call_setting call_opt;
		pjsua_call_setting_default(&call_opt);
		call_opt.aud_cnt = 1;
		call_opt.vid_cnt = 0;

		status = pjsua_call_make_call(acc_id, &uri, &call_opt, NULL, NULL, NULL);
		if (status != PJ_SUCCESS) error_exit("拨号错误，请检查url", status);
	}
}


void CMFCApplication1Dlg::OnBnClickedButtondtmf()
{
	// TODO: 在此添加控件通知处理程序代码
	if (current_call == PJSUA_INVALID_ID) {
		MessageBox(_T("只能在通话过程中发送dtmf信息"));
	}
	else{
		checkinput();//校正输入框
		pj_str_t dtmf_msg = pj_str(m_str.GetBuffer(m_str.GetLength()));
		pj_status_t status = pjsua_call_dial_dtmf(current_call, &dtmf_msg);
		if (status != PJ_SUCCESS) {
			MessageBox(_T("发送DTMF失败(仅支持数字信息)"));
		}
		else {
			stage_msg.Format(_T("发送的消息为%s"), m_str);
			MessageBox(_T("DTMF 信息发送成功！"));
		}
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonrejcet()
{
	// 拒绝:  如果当前有通话，则挂断
	if (current_call != PJSUA_INVALID_ID) {
		//检查挂断
		if (cancel_announce == false) {
			MessageBox(_T("再点击一次挂断，完成挂断"));
			cancel_announce = true;
		}
		else {
			//pjsua_msg_data msg_data_;
			//pjsua_call_hangup(current_call,0,NULL,&msg_data_);
			pjsua_call_hangup_all();
			current_call = PJSUA_INVALID_ID;
			call_in = PJSUA_INVALID_ID;
			stage_msg = "通话已结束，可以重新拨打";
		}
	}
	else if (call_in != PJSUA_INVALID_ID) {
		//检查拒绝
		if (cancel_announce == false) {
			MessageBox(_T("再点击一次挂断，完成挂断"));
			cancel_announce = true;
		}
		else {
			pjsua_call_hangup_all();
			call_in = PJSUA_INVALID_ID;
			stage_msg = "已经拒绝";
		}
	}
}
