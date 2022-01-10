#ifndef _MYCHECK_ROWEROPERATION
#define _MYCHECK_ROWEROPERATION

/***************************************************************
  *  @brief     显示所有行 
  *  @param     无 
  *  @note      无 
  *  @Sample usage:     显示所有行，根据showcode全局配置决定采用哪种模式 
 **************************************************************/
void ReleaseShowAllRow();


/***************************************************************
  *  @brief     DEBUG模式显示所有行的所有信息 
  *  @param     无 
  *  @note      无 
  *  @Sample usage:     DEBUG模式显示所有行的所有信息，根据showcode全局配置决定采用哪种模式 
 **************************************************************/
void DEBUGShowAllRow();


/***************************************************************
  *  @brief     读取所有行 
  *  @param     FILE* 指针   
  *  @note      必须刚好读取到行那一行开始传入FILE*指针 
  *  @Sample usage:    读取所有行
 **************************************************************/
void ReadAllRow(FILE*);


/***************************************************************
  *  @brief     将行place放到tobenew的**前方** 
  *  @param     行指针 place, tobenew   
  *  @note      无 
  *  @Sample usage:     将行place放到tobenew的**前方** 
 **************************************************************/
PROW InsertRow_FrontOf(PROW place, PROW tobenew);


/***************************************************************
  *  @brief     将行place放到tobenew的**后方** 
  *  @param     行指针 place, tobenew   
  *  @note      无 
  *  @Sample usage:     将行place放到tobenew的**后方** 
 **************************************************************/
PROW InsertRow_BackOf(PROW place, PROW tobenew);


/***************************************************************
  *  @brief     通过True Key查询行
  *  @param     int trueke 
  *  @note      无 
  *  @Sample usage:     查询行，返回指针或NULL 
 **************************************************************/
PROW QueryRowTrueKey(int truekey);


/***************************************************************
  *  @brief     对行部分进行切分 
  *  @param      char *line当前行的字符串 , PROW 当前行 
  *  @note      内部调用 
  *  @Sample usage:    对下一个行进行切分，有多少个块就有多少个附属的key 
 **************************************************************/
void RowDevide(char *source, PROW inrow);


/***************************************************************
  *  @brief     删除行
  *  @param     行指针 del删除的表头, bool truedelete真删与否  
  *  @note      无 
  *  @Sample usage:     从链表上删除行，根据 truedelete选择是否free(用于移动行) 
 **************************************************************/
void DeleteRow(PROW del, bool truedelete);

#endif
