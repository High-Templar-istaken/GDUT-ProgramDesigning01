#ifndef _MYCHECK_TABLEOPERATION
#define _MYCHECK_TABLEOPERATION

/***************************************************************
  *  @brief     ��ʼ�������ļ� 
  *  @param     �� 
  *  @note      �� 
  *  @Sample usage:    ��Ĭ����Ϣ��ʼ�������ļ� 
 **************************************************************/
void initconfig();


/***************************************************************
  *  @brief     ��ȡ��� 
  *  @param     char* �ļ��� 
  *  @note      �� 
  *  @Sample usage:    ���readheader��readrow 
 **************************************************************/
void ReadTable(char*);


/***************************************************************
  *  @brief     ��ӡ��� 
  *  @param     char* �ļ��� 
  *  @note      �� 
  *  @Sample usage:    ���Printheader��Printrow 
 **************************************************************/
void ReleasePrintTable();


/***************************************************************
  *  @brief     DEBUGģʽ��ӡ��� 
  *  @param     char* �ļ��� 
  *  @note      �� 
  *  @Sample usage:    ���DEBUGPrintheader��DEBUGPrintrow 
 **************************************************************/
void DebugPrintTable();


/***************************************************************
  *  @brief     д���
  *  @param     char* �ļ��� 
  *  @note      �� 
  *  @Sample usage:    ���Writeheader��Writerow 
 **************************************************************/
void WriteTable(char*);

#endif
