#ifndef _MYCHECK_HEADEROPERATION
#define _MYCHECK_HEADEROPERATION


/***************************************************************
  *  @brief     将表头place放到tobenew的**前方** 
  *  @param     表头指针 place, tobenew   
  *  @note      无 
  *  @Sample usage:     将表头place放到tobenew的**前方** 
 **************************************************************/
PHEADER InsertHeader_FrontOf(PHEADER place, PHEADER tobenew);



/***************************************************************
  *  @brief     将表头place放到tobenew的**后方** 
  *  @param     表头指针 place, tobenew   
  *  @note      无 
  *  @Sample usage:     将表头place放到tobenew的**后方** 
 **************************************************************/
PHEADER InsertHeader_BackOf(PHEADER place, PHEADER tobenew);



/***************************************************************
  *  @brief     展示所有表头 
  *  @param     无   
  *  @note      正常的Release模式，不显示所有参数 
  *  @Sample usage:    展示所有表头 ，不显示所有参数
 **************************************************************/
void ReleaseShowAllHeader();



/***************************************************************
  *  @brief     展示所有表头 
  *  @param     无   
  *  @note      Debug模式，显示所有参数 
  *  @Sample usage:    展示所有表头 ，显示所有参数
 **************************************************************/
void DEBUGShowAllHeader();



/***************************************************************
  *  @brief     读取所有表头 
  *  @param     FILE* 指针   
  *  @note      必须刚好读取到表头那一行开始传入FILE*指针 
  *  @Sample usage:    读取所有表头，包括显示名、ID、默认值 
 **************************************************************/
void ReadAllHeader(FILE*);



/***************************************************************
  *  @brief     对表头部分下一个XX:XX进行切分 
  *  @param      char *line当前行 , int *j当前行第几个字符, char **first(返回用)第一个,
  					char **second(返回用)第二个, char *tmp临时字符串,防止多次malloc占用大量时间 
  *  @note      内部调用 
  *  @Sample usage:    对下一个存储块进行切分，返回第一个块first与第二个块second
 **************************************************************/
void ReadAllHeader_DevideNextHeaderInput(char *line, int *j, char **first, char **second, char *tmp);



/***************************************************************
  *  @brief     通过ID查询表头 
  *  @param     char* ID  
  *  @note      无 
  *  @Sample usage:     查询表头，返回指针或NULL 
 **************************************************************/
PHEADER QueryHeaderID(char *);



/***************************************************************
  *  @brief     删除表头
  *  @param     PHEADER del删除的表头, bool truedelete真删与否  
  *  @note      无 
  *  @Sample usage:     从链表上删除表头，根据 truedelete选择是否free(用于移动表头) 
 **************************************************************/
void DeleteHeader(PHEADER del, bool truedelete);



/***************************************************************
  *  @brief     检查表头名字是否合规
  *  @param     PHEADER 被检查的表头   
  *  @note      无 
  *  @Sample usage:      检查传入的指针中的表头名字是否合规，用于躲避##:##的干扰 
 **************************************************************/
bool CheckHeaderLegitByPointer(PHEADER now);



/***************************************************************
  *  @brief     检查表头名字是否合规
  *  @param     char* 被检查的表头名字 
  *  @note      无 
  *  @Sample usage:      检查传入的表头名字是否合规，用于防止用户失误 
 **************************************************************/
bool CheckHeaderLegitByString(char* now);

#endif
