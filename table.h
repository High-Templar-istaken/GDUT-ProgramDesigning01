#ifndef _MYCHECK_TABLEOPERATION
#define _MYCHECK_TABLEOPERATION

/***************************************************************
  *  @brief     初始化配置文件 
  *  @param     无 
  *  @note      无 
  *  @Sample usage:    用默认信息初始化配置文件 
 **************************************************************/
void initconfig();


/***************************************************************
  *  @brief     读取表格 
  *  @param     char* 文件名 
  *  @note      无 
  *  @Sample usage:    打包readheader与readrow 
 **************************************************************/
void ReadTable(char*);


/***************************************************************
  *  @brief     打印表格 
  *  @param     char* 文件名 
  *  @note      无 
  *  @Sample usage:    打包Printheader与Printrow 
 **************************************************************/
void ReleasePrintTable();


/***************************************************************
  *  @brief     DEBUG模式打印表格 
  *  @param     char* 文件名 
  *  @note      无 
  *  @Sample usage:    打包DEBUGPrintheader与DEBUGPrintrow 
 **************************************************************/
void DebugPrintTable();


/***************************************************************
  *  @brief     写表格
  *  @param     char* 文件名 
  *  @note      无 
  *  @Sample usage:    打包Writeheader与Writerow 
 **************************************************************/
void WriteTable(char*);

#endif
