#ifndef _MYCHECK_KEYOPERATION
#define _MYCHECK_KEYOPERATION

/***************************************************************
  *  @brief     通过ID与行truekey查询键 
  *  @param     PROW inrow:在哪一行中 char *target:查询什么表头 
  *  @note      无 
  *  @Sample usage:     查询键，返回指针或NULL 
 **************************************************************/
PKEY QueryKeyHeader(PROW inrow, char *target);


/***************************************************************
  *  @brief     将键place放到tobenew的**后方** 
  *  @param     键指针 place, tobenew   
  *  @note      无 
  *  @Sample usage:     将键place放到tobenew的**后方** 
 **************************************************************/
PKEY InsertKey_BackOf(PKEY place, PKEY tobe, PROW inrow);


/***************************************************************
  *  @brief     删除键
  *  @param     PHEADER del删除的键
  *  @note      无 
  *  @Sample usage:     从链表上删除键
 **************************************************************/
void DeleteKey(PKEY del, PROW inrow);

#endif
