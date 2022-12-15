#ifndef __ATP_COMMON_H__
#define __ATP_COMMON_H__

#include <sys/socket.h>
#include <sys/time.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "platform.h"


#define CONFIG_FEATURE_COPYBUF_KB 4
#define ENABLE_FEATURE_COPYBUF_KB 1

#define ATP_STRING_LEN_512                  516   //Ԥ��4���ֽڣ������������4�ֽڶ���
#define ATP_STRING_LEN_256                  260   //Ԥ��4���ֽڣ������������4�ֽڶ���
#define ATP_STRING_LEN_128                  132   //Ԥ��4���ֽڣ������������4�ֽڶ���
#define ATP_STRING_LEN_64                   68    //Ԥ��4���ֽڣ������������4�ֽڶ���
#define ATP_STRING_LEN_32                   36    //Ԥ��4���ֽڣ������������4�ֽڶ���
#define ATP_STRING_LEN_16                   20    //Ԥ��4���ֽڣ������������4�ֽڶ���



#if ENABLE_FEATURE_ATP_WGET_ZIP || ENABLE_FEATURE_ATP_FTP_ZIP || ENABLE_FEATURE_ATP_TFTP_ZIP || ENABLE_FEATURE_ATP_MCAST_ZIP
typedef void * gzFile;

extern gzFile gzopen(const char *path, const char *mode);
extern int gzwrite(gzFile file, const void *buf, unsigned int len);
extern int gzclose(gzFile file);

#endif

/* ftpget ftpput tftp wget���乤�ߵķ����� */
#define ATP_TRANS_OK                (0)
#define ATP_TRANS_TIMEOUT           (0xF1)
#define ATP_TRANS_FILE_ERR          (0xF2)
#define ATP_TRANS_SYS_ERR           (0xF3)
#define ATP_TRANS_AUTH_ERR          (0xF4)

/*modified by w00190448@20110907 for DTS2011082904337 .START*/
#define ATP_TRANS_SPACE_FULL_ERR          (0xF5)
/*modified by w00190448@20110907 for DTS2011082904337 .END*/

/* ftpget ftpput tftp wget���乤�ߵ�������ѡ�� */
#define TRANS_TOOL_OPT_DOWNLOAD	    1
#define TRANS_TOOL_OPT_UPLOAD	    2
#define TRANS_TOOL_OPT_VERBOSE	    4
#define TRANS_TOOL_OPT_USER	        8
#define TRANS_TOOL_OPT_PASSWORD	    16
#define TRANS_TOOL_OPT_LOCALPATH	32
#define TRANS_TOOL_OPT_REMOTEPATH	64
#define TRANS_TOOL_OPT_REMOTEPORT	128
#define TRANS_TOOL_OPT_BINDIP       256
#define TRANS_TOOL_OPT_REMOTEIP     512
// 1024,2048,4096
#define TRANS_TOOL_OPT_ZIP	        8192

#ifdef ENABLE_FEATURE_IPV6
#define ATP_IPV4_IP     0
#define ATP_IPV6_IP     1
#define ATP_LEN_64      64
#endif

/*Diagbostic record files*/
#if defined(SUPPORT_ATP_TR143_DOWNLOAD_TCP) ||defined(SUPPORT_ATP_TR143_DOWNLOAD)
#define TR143_DOWNDIAG_RESULT_FILE "/var/DownloadDiagState"
#define TR143_DOWNDIAG_PID_FILE    "/var/DownloadDiagPid"
#endif
#if defined(SUPPORT_ATP_TR143_UPLOAD_TCP) || defined(SUPPORT_ATP_TR143_UPLOAD)
#define TR143_UPDIAG_RESULT_FILE "/var/UploadDiagState"
#define TR143_UPDIAG_PID_FILE    "/var/UploadDiagPid"
#endif

#if ENABLE_GETOPT_LONG
/* ftp wget��tftp���乤�ߵ��������÷�˵�� */
extern const char bb_transtool_long_options[];
#endif

typedef struct  tagtr143_diag_state_t{
/* None, Requested, Completed, Error_InitConnectionFailed, Error_NoResponse,Error_TransferFailed,Error_PasswordRequestFailed, Error_LoginFailed,Error_NoTransferMode,Error_NoPASV,Error_NoCWD,Error_NoSTOR,Error_NoTransferComplete */
  char szState[ATP_STRING_LEN_32];
  //int ulTextFileLength;
  char  szRomTime[ATP_STRING_LEN_64];             /* in ms */
  char  szBomTime[ATP_STRING_LEN_64];
  char  szEomTime[ATP_STRING_LEN_64];
  unsigned int    ulTextBytesReceived;
  unsigned int    ulTotalBytesReceived;
  unsigned int    ulTotalBytesSent;
  char   szTcpOpenRequestTime[ATP_STRING_LEN_64];
  char   szTcpOpenResponseTime[ATP_STRING_LEN_64];
  char   szIfName[32];
  unsigned int      ulTransDir;
} tr143_diag_state_t;

#if 1
// ʹ��ȫ���ڴ棬���ӽ�ʡ�ڴ�
struct atp_trans_globals {
	int g_lTransEnd;            // �������λ��
	int g_lMaxTrans;            // �����ļ�����С
    const char *g_pcLocalIP;    // ���ذ�IP
    const char *g_pcTransBegin; // ���俪ʼ��ַ
    const char *g_pcTransEnd;   // ���������ַ

    int         bCompress;

    unsigned int g_ulTotalLen;
    int mcast_seq_num;
    int mcast_len;
    unsigned char *mcast_buf;

    int         timout_cnt;
};

#define HANDY (*(struct atp_trans_globals*)&bb_common_bufsiz1)

#define g_pcLocalIP     (HANDY.g_pcLocalIP    )
#define g_pcTransBegin  (HANDY.g_pcTransBegin )
#define g_pcTransEnd    (HANDY.g_pcTransEnd   )
#define g_lTransEnd     (HANDY.g_lTransEnd    )
#define g_lMaxTrans     (HANDY.g_lMaxTrans    )

#define g_ulTotalLen    (HANDY.g_ulTotalLen   )
#define g_lMcastSeqNum  (HANDY.mcast_seq_num  )
#define g_lMcastLen     (HANDY.mcast_len      )
#define g_pucMcastBuf   (HANDY.mcast_buf      )
#define g_bCompress     (HANDY.bCompress      )

#define g_TimeoutCnt    (HANDY.timout_cnt     )

#else

extern const char *g_pcLocalIP;
extern const char *g_pcTransBegin;
extern int g_lTransEnd;
extern int g_lMaxTrans;
#endif

int xbind_connect(const len_and_sockaddr *lsa, const char *ip);

#if ENABLE_FEATURE_ATP_WGET_ZIP || ENABLE_FEATURE_ATP_FTP_ZIP || ENABLE_FEATURE_ATP_MCAST_ZIP
void atp_zip_write(gzFile fd, const void *buf, size_t count);
#define atp_write atp_zip_write

#if 1
/*
DTS2011082704676 2011-11-02 for by j00196195
��Ҫ�����ļ�·������Ϊ�ļ�����Ѿ�ʧЧ
*/
int atp_copy_to_zipfile(int src_fd, gzFile dst_file, int filesize, char* dst_path);
#else
int atp_copy_to_zipfile(int src_fd, gzFile dst_file, int filesize);
#endif
#else
#define atp_write xwrite
#endif

/*Start of MNT 2008-10-13 14:36 for ���䳬ʱ��� by z65940*/
#define ATP_CONNECT_TIMEOUT_D   (20)    // 20�����ӳ�ʱ
#define ATP_PACK_TIMEOUT_D      (30)    // 30��û���յ�������ʱ

/* 20120904 Modify by weiqingchuan 61642 for Compiling Warning */
void atp_setup_alarm(void);
#if 1
/*
DTS2011082704676 2011-11-02 for by j00196195
��Ҫ�����ļ�·������Ϊ�ļ�����Ѿ�ʧЧ
*/
off_t atp_copy_fd_with_timeout(int src_fd, int dst_fd, off_t size, char* dst_path);
#else
off_t atp_copy_fd_with_timeout(int src_fd, int dst_fd, off_t size);
#endif
/*End of MNT 2008-10-13 14:36 for by z65940*/
#ifdef ENABLE_FEATURE_IPV6
int ATP_TransHostname2IP(char * hostname,char* buffer,int len,int * pIPflag);
#endif

#if defined(SUPPORT_ATP_TR143_DOWNLOAD_TCP) ||defined(SUPPORT_ATP_TR143_DOWNLOAD)
void SetDownDiagState(tr143_diag_state_t *pstDiagState, char * pcState, bool bFlag);
//#define SetDownDiagState(x) SetUpDiagStateEx((x))
#else
#define SetDownDiagState(x,y,z)
#endif

#if defined(SUPPORT_ATP_TR143_UPLOAD_TCP) || defined(SUPPORT_ATP_TR143_UPLOAD)
void SetUpDiagState(tr143_diag_state_t *pstDiagState, char * pcState, bool bFlag);
int diag_copy_fd_with_timeout( int dst_fd, int size);
//#define SetUpDiagState(x) SetUpDiagStateEx((x))
#else
#define SetUpDiagState(x,y,z)
#endif

#if defined(SUPPORT_ATP_TR143_DOWNLOAD_TCP) ||defined(SUPPORT_ATP_TR143_DOWNLOAD) || defined(SUPPORT_ATP_TR143_UPLOAD_TCP) || defined(SUPPORT_ATP_TR143_UPLOAD)
 int GetCurDateTime(char *pcBuf, int ulBufLen);
void ATP_UTIL_GetIfcStatInfo(char *pszIfcName, ATP_UTIL_INTERFACE_STAT_ST *pstState);
void SetDiagState(tr143_diag_state_t *pstDiagState, char * pcState, bool bFlag);
//#define SetDiagState(x) SetDiagStateEx((x), (y),(z))
#else
#define SetDiagState(x,y,z)
#endif
#endif
