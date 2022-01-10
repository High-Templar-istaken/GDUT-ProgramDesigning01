#ifndef _MYCHECK_ROWEROPERATION
#define _MYCHECK_ROWEROPERATION

/***************************************************************
  *  @brief     ��ʾ������ 
  *  @param     �� 
  *  @note      �� 
  *  @Sample usage:     ��ʾ�����У�����showcodeȫ�����þ�����������ģʽ 
 **************************************************************/
void ReleaseShowAllRow();


/***************************************************************
  *  @brief     DEBUGģʽ��ʾ�����е�������Ϣ 
  *  @param     �� 
  *  @note      �� 
  *  @Sample usage:     DEBUGģʽ��ʾ�����е�������Ϣ������showcodeȫ�����þ�����������ģʽ 
 **************************************************************/
void DEBUGShowAllRow();


/***************************************************************
  *  @brief     ��ȡ������ 
  *  @param     FILE* ָ��   
  *  @note      ����պö�ȡ������һ�п�ʼ����FILE*ָ�� 
  *  @Sample usage:    ��ȡ������
 **************************************************************/
void ReadAllRow(FILE*);


/***************************************************************
  *  @brief     ����place�ŵ�tobenew��**ǰ��** 
  *  @param     ��ָ�� place, tobenew   
  *  @note      �� 
  *  @Sample usage:     ����place�ŵ�tobenew��**ǰ��** 
 **************************************************************/
PROW InsertRow_FrontOf(PROW place, PROW tobenew);


/***************************************************************
  *  @brief     ����place�ŵ�tobenew��**��** 
  *  @param     ��ָ�� place, tobenew   
  *  @note      �� 
  *  @Sample usage:     ����place�ŵ�tobenew��**��** 
 **************************************************************/
PROW InsertRow_BackOf(PROW place, PROW tobenew);


/***************************************************************
  *  @brief     ͨ��True Key��ѯ��
  *  @param     int trueke 
  *  @note      �� 
  *  @Sample usage:     ��ѯ�У�����ָ���NULL 
 **************************************************************/
PROW QueryRowTrueKey(int truekey);


/***************************************************************
  *  @brief     ���в��ֽ����з� 
  *  @param      char *line��ǰ�е��ַ��� , PROW ��ǰ�� 
  *  @note      �ڲ����� 
  *  @Sample usage:    ����һ���н����з֣��ж��ٸ�����ж��ٸ�������key 
 **************************************************************/
void RowDevide(char *source, PROW inrow);


/***************************************************************
  *  @brief     ɾ����
  *  @param     ��ָ�� delɾ���ı�ͷ, bool truedelete��ɾ���  
  *  @note      �� 
  *  @Sample usage:     ��������ɾ���У����� truedeleteѡ���Ƿ�free(�����ƶ���) 
 **************************************************************/
void DeleteRow(PROW del, bool truedelete);

#endif
