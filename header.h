#ifndef _MYCHECK_HEADEROPERATION
#define _MYCHECK_HEADEROPERATION


/***************************************************************
  *  @brief     ����ͷplace�ŵ�tobenew��**ǰ��** 
  *  @param     ��ͷָ�� place, tobenew   
  *  @note      �� 
  *  @Sample usage:     ����ͷplace�ŵ�tobenew��**ǰ��** 
 **************************************************************/
PHEADER InsertHeader_FrontOf(PHEADER place, PHEADER tobenew);



/***************************************************************
  *  @brief     ����ͷplace�ŵ�tobenew��**��** 
  *  @param     ��ͷָ�� place, tobenew   
  *  @note      �� 
  *  @Sample usage:     ����ͷplace�ŵ�tobenew��**��** 
 **************************************************************/
PHEADER InsertHeader_BackOf(PHEADER place, PHEADER tobenew);



/***************************************************************
  *  @brief     չʾ���б�ͷ 
  *  @param     ��   
  *  @note      ������Releaseģʽ������ʾ���в��� 
  *  @Sample usage:    չʾ���б�ͷ ������ʾ���в���
 **************************************************************/
void ReleaseShowAllHeader();



/***************************************************************
  *  @brief     չʾ���б�ͷ 
  *  @param     ��   
  *  @note      Debugģʽ����ʾ���в��� 
  *  @Sample usage:    չʾ���б�ͷ ����ʾ���в���
 **************************************************************/
void DEBUGShowAllHeader();



/***************************************************************
  *  @brief     ��ȡ���б�ͷ 
  *  @param     FILE* ָ��   
  *  @note      ����պö�ȡ����ͷ��һ�п�ʼ����FILE*ָ�� 
  *  @Sample usage:    ��ȡ���б�ͷ��������ʾ����ID��Ĭ��ֵ 
 **************************************************************/
void ReadAllHeader(FILE*);



/***************************************************************
  *  @brief     �Ա�ͷ������һ��XX:XX�����з� 
  *  @param      char *line��ǰ�� , int *j��ǰ�еڼ����ַ�, char **first(������)��һ��,
  					char **second(������)�ڶ���, char *tmp��ʱ�ַ���,��ֹ���mallocռ�ô���ʱ�� 
  *  @note      �ڲ����� 
  *  @Sample usage:    ����һ���洢������з֣����ص�һ����first��ڶ�����second
 **************************************************************/
void ReadAllHeader_DevideNextHeaderInput(char *line, int *j, char **first, char **second, char *tmp);



/***************************************************************
  *  @brief     ͨ��ID��ѯ��ͷ 
  *  @param     char* ID  
  *  @note      �� 
  *  @Sample usage:     ��ѯ��ͷ������ָ���NULL 
 **************************************************************/
PHEADER QueryHeaderID(char *);



/***************************************************************
  *  @brief     ɾ����ͷ
  *  @param     PHEADER delɾ���ı�ͷ, bool truedelete��ɾ���  
  *  @note      �� 
  *  @Sample usage:     ��������ɾ����ͷ������ truedeleteѡ���Ƿ�free(�����ƶ���ͷ) 
 **************************************************************/
void DeleteHeader(PHEADER del, bool truedelete);



/***************************************************************
  *  @brief     ����ͷ�����Ƿ�Ϲ�
  *  @param     PHEADER �����ı�ͷ   
  *  @note      �� 
  *  @Sample usage:      ��鴫���ָ���еı�ͷ�����Ƿ�Ϲ棬���ڶ��##:##�ĸ��� 
 **************************************************************/
bool CheckHeaderLegitByPointer(PHEADER now);



/***************************************************************
  *  @brief     ����ͷ�����Ƿ�Ϲ�
  *  @param     char* �����ı�ͷ���� 
  *  @note      �� 
  *  @Sample usage:      ��鴫��ı�ͷ�����Ƿ�Ϲ棬���ڷ�ֹ�û�ʧ�� 
 **************************************************************/
bool CheckHeaderLegitByString(char* now);

#endif
