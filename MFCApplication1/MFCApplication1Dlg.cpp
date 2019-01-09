
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool CMFCApplication1Dlg::no_tones = false;
bool CMFCApplication1Dlg::ring_on = PJ_FALSE;
int CMFCApplication1Dlg::ring_cnt = 0;
int CMFCApplication1Dlg::ring_slot = PJSUA_INVALID_ID;
pjsua_call_id CMFCApplication1Dlg::call_in = PJSUA_INVALID_ID;
pjsua_call_id CMFCApplication1Dlg::current_call = PJSUA_INVALID_ID;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication1Dlg �Ի���



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

//��Ϣ����
BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()//��Ӧ����ָ��
	ON_WM_PAINT()	//��ͼ��Ϣ
	ON_WM_QUERYDRAGICON()	//��Ӧ�û��϶���С������ʱ��ù��
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
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//MessageBox(_T("open!"));
	initSip();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

/*
* Handler registration status has changed.
*/
static void on_reg_state(pjsua_acc_id acc_id)
{
	PJ_UNUSED_ARG(acc_id);

	// Log already written.
}

void CMFCApplication1Dlg::initSip() {
	status = pjsua_create();
	pj_pool_t *tmp_pool;
	tmp_pool = pjsua_pool_create("tmp-pjsua", 1000, 1000);

	if (status != PJ_SUCCESS) error_exit("Error in pjsua_create()", status);

	/* If argument is specified, it's got to be a valid SIP URL */
	status = pjsua_verify_url("sip:" SEVER_USER "@" SIP_DOMAIN);
	if (status != PJ_SUCCESS) error_exit("Invalid URL in argv", status);

	/* Init pjsua */
	{
		pjsua_config_default(&cfg);
		cfg.cb.on_incoming_call = &on_incoming_call;
		cfg.cb.on_call_media_state = &on_call_media_state;
		cfg.cb.on_call_state = &on_call_state;
		cfg.cb.on_reg_state = &on_reg_state;

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

	/* Register to SIP server by creating SIP account. ����������sip:user@ip�ģ���Ҫע��
	{
		pjsua_acc_config_default(&acc_cfg);
		acc_cfg.id = pj_str("sip:" SIP_USER "@" LOCAL_DOMAIN);
		acc_cfg.reg_uri = pj_str("sip:" LOCAL_DOMAIN);
		acc_cfg.cred_count = 1;
		acc_cfg.cred_info[0].realm = pj_str(LOCAL_DOMAIN);
		acc_cfg.cred_info[0].scheme = pj_str("digest");
		acc_cfg.cred_info[0].username = pj_str(SIP_USER);
		acc_cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
		acc_cfg.cred_info[0].data = pj_str(SIP_PASSWD);
		//Add a local account. A local account is used to identify local endpoint
		//  instead of a specific user, and for this reason, a transport ID is needed to obtain the local address information.
		status = pjsua_acc_add(&acc_cfg, PJ_TRUE, &acc_id);  //acc_id �ǵ��ú󱻷����
		if (status != PJ_SUCCESS) error_exit("Error adding account", status);
	}*/

	/* Add UDP transport unless it's disabled. ������ֱ�Ӳ��� sip:localhost�ģ�����ע�������*/
	{
		pjsip_transport_type_e type = PJSIP_TRANSPORT_UDP;
		/* Add local account */
		pjsua_acc_add_local(transport_id, PJ_TRUE, &acc_id);
		/* Adjust local account config based on pjsua app config */
		{
			pjsua_acc_config acc_cfg;
			pjsua_acc_get_config(acc_id, tmp_pool, &acc_cfg);

			//app_config_init_video(&acc_cfg);
			//acc_cfg.rtp_cfg = app_config.rtp_cfg;
			pjsua_acc_modify(acc_id, &acc_cfg);
		}

		//pjsua_acc_set_transport(aid, transport_id);
		pjsua_acc_set_online_status(current_acc, PJ_TRUE);
	}

	/* make call to the URL. */
	{
		
	}
}pj_str_t uri = pj_str("sip:12345@10.105.242.72");
		//status = pjsua_call_make_call(acc_id, &uri, 0, NULL, NULL, NULL);
		//if (status != PJ_SUCCESS) error_exit("Error making call", status);

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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("1"));
}

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("2"));
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("3"));
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("4"));
}


void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("5"));
}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("6"));
}


void CMFCApplication1Dlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("7"));
}


void CMFCApplication1Dlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("8"));
}


void CMFCApplication1Dlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("9"));
}

void CMFCApplication1Dlg::OnBnClickedButton0()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("0"));
}

void CMFCApplication1Dlg::OnBnClickedButtonansip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("sip:"));
}


void CMFCApplication1Dlg::OnBnClickedButtonansat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("@"));
}

void CMFCApplication1Dlg::OnBnClickedButtonshurp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("#"));
}

void CMFCApplication1Dlg::OnBnClickedButtonansadot()
{
	OnBnClickInp(_T("."));
}

void CMFCApplication1Dlg::OnBnClickedButtonstar()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickInp(_T("*"));
}

void CMFCApplication1Dlg::OnBnClickInp(CString inp)
{
	UpdateData(true);//�޸�Edit��ʾ��֮ǰ��Ҫ������һ��
	m_str = m_str + inp;
	UpdateData(false);
}

void CMFCApplication1Dlg::OnBnClickedButtonandel()
{
	// ɾ������ɾȥ��������һ��
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
	// ����/�ܾ�:  �����ǰ��ͨ������Ҷϣ��������
	if (current_call == PJSUA_INVALID_ID) {
		//������
		if (call_in == PJSUA_INVALID_ID) {
			MessageBox(_T("Nothing answer"));
		}
		else {
			pjsua_call_answer(call_in, 200, NULL, NULL);
			current_call = call_in;
			cancel_announce = false;
		}
	}
	else { //���ܾ�
		if (cancel_announce == false) {
			MessageBox(_T("�ٵ��һ�ιҶϣ���ɹҶ�"));
			cancel_announce = true;
		}
		else {
			pjsua_msg_data msg_data_;
			pjsua_call_hangup(current_call,0,NULL,&msg_data_);
			current_call = PJSUA_INVALID_ID;
		}
	}
	
}


void CMFCApplication1Dlg::OnBnClickedButtonancall()
{
	// ���ż�
	if (current_call != PJSUA_INVALID_ID) {
		MessageBox(_T("����ͨ���У���ҶϺ��ٲ�"));
	}
	else {
		pj_str_t uri = pj_str(m_str.GetBuffer(0));
		pjsua_call_setting call_opt;
		pjsua_call_setting_default(&call_opt);
		call_opt.aud_cnt = 1;
		call_opt.vid_cnt = 0;

		status = pjsua_call_make_call(acc_id, &uri, &call_opt, NULL, NULL, NULL);
		if (status != PJ_SUCCESS) error_exit("Error making call", status);
	}
}


void CMFCApplication1Dlg::OnBnClickedButtondtmf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (current_call == PJSUA_INVALID_ID) {
		MessageBox(_T("No current call"));
	}
	else{
		pj_str_t dtmf_msg = pj_str(m_str.GetBuffer(0));
		pj_status_t status = pjsua_call_dial_dtmf(current_call, &dtmf_msg);
		if (status != PJ_SUCCESS) {
			MessageBox(_T("Unable to send DTMF"));
		}
		else {
			MessageBox(_T("DTMF ��Ϣ���ͳɹ���"));
		}
	}
}
