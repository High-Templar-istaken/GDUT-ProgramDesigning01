#ifndef _MYCHECK_KEYOPERATION
#define _MYCHECK_KEYOPERATION

/***************************************************************
  *  @brief     ͨ��ID����truekey��ѯ�� 
  *  @param     PROW inrow:����һ���� char *target:��ѯʲô��ͷ 
  *  @note      �� 
  *  @Sample usage:     ��ѯ��������ָ���NULL 
 **************************************************************/
PKEY QueryKeyHeader(PROW inrow, char *target);


/***************************************************************
  *  @brief     ����place�ŵ�tobenew��**��** 
  *  @param     ��ָ�� place, tobenew   
  *  @note      �� 
  *  @Sample usage:     ����place�ŵ�tobenew��**��** 
 **************************************************************/
PKEY InsertKey_BackOf(PKEY place, PKEY tobe, PROW inrow);


/***************************************************************
  *  @brief     ɾ����
  *  @param     PHEADER delɾ���ļ�
  *  @note      �� 
  *  @Sample usage:     ��������ɾ����
 **************************************************************/
void DeleteKey(PKEY del, PROW inrow);

#endif
