#pragma once

#ifndef interface
#define interface struct
#endif

 
/************************************************* 
Copyright: FUTU
Author: ysq
Date: 2015-03-18
Description: ����API�ͻص��ӿڶ���
**************************************************/  

/**
*��Ʊ���г����� 
*/ 
enum StockMktType 
{	
	StockMkt_HK = 1,  //�۹� 
	StockMkt_US = 2,  //����
	StockMkt_SH = 3,  //����
	StockMkt_SZ = 4,  //���
	StockMkt_Feature_Old = 5,  //�ɵ��ڻ� code: 999000, 999001 �����ڻ���ʱ������һ��������
	StockMkt_Feature_New = 6,  //���ڻ� code: 999010, 999011 �����ڻ���ʱ���ݻ���죬�봫ͳ�������һ�£�
}; 

enum StockSubErrCode
{
	StockSub_Suc = 0,	//���ĳɹ�
	StockSub_FailUnknown	= 1,	//δ֪��ʧ��
	StockSub_FailMaxSubNum	= 2,	//�����������
	StockSub_FailCodeNoFind = 3,	//����û�ҵ�(Ҳ�п������г����ʹ���)
	StockSub_FailGuidNoFind = 4,	//���GUID����
	StockSub_FailNoImplInf = 5,		//����ӿ�δ���
};

enum QueryDataErrCode
{
	QueryData_Suc = 0,	//��ѯ�ɹ�
	QueryData_FailUnknown	= 1,	//δ֪��ʧ��
	QueryData_FailMaxSubNum	= 2,	//��������ѯ��
	QueryData_FailCodeNoFind = 3,	//����û�ҵ�(Ҳ�п������г����ʹ���)
	QueryData_FailGuidNoFind = 4,	//���GUID����
	QueryData_FailNoImplInf = 5,		//����ӿ�δ���
	QueryData_IsExisted = 6,
};

/**
* ��Ʊ����������Ϣ��
* �۸񾫶���3λС���� �籨��8.888�洢ֵ 88888
*/
typedef struct tagQuotePriceBase
{ 
	DWORD dwOpen;		//���̼�
	DWORD dwLastClose;  //���ռ�
	DWORD dwCur;		//��ǰ��
	DWORD dwHigh;		//��߼�
	DWORD dwLow;		//��ͼ�
	INT64 ddwVolume;	//�ɽ���
	INT64 ddwTrunover;	//�ɽ���
	DWORD dwTime;		//����ʱ��
	DWORD ddwLotSize;	//ÿ������
}Quote_PriceBase, *LPQuote_PriceBase;


/**
* ��Ʊʮ������
* IFTQuoteData::FillOrderQueue �Ľӿڲ���  
*/
typedef struct tagQuoteOrderQueue
{
	DWORD	dwBuyPrice, dwSellPrice;  //��� ����
	INT64	ddwBuyVol, ddwSellVol;    //���� ����
	int		nBuyOrders, nSellOrders;  //��λ 
}Quote_OrderQueue, *LPQuote_OrderQueue;  


/**
* ��ʱ����
*/
typedef struct tagQuoteStockRTData
{
	int   nDataStatus; 
	DWORD dwTime; 
	DWORD dwOpenedMins;  //���̵ڶ��ٷ���  

	int   nCurPrice;
	DWORD nLastClosePrice; //��������̼� 

	int   nAvgPrice;

	INT64 ddwTDVolume;
	INT64 ddwTDValue;  
}Quote_StockRTData, *LPQuote_StockRTData;  

/**
* K������
*/
typedef struct tagQueryStockKLData
{
	int   nDataStatus; 
	DWORD dwTime;

	int   nOpenPrice; 
	int   nClosePrice; 

	int   nHighestPrice; 
	int   nLowestPrice;  

	int   nPERatio; //��ӯ��(��λС��)
	int   nTurnoverRate;//������(���ɼ�ָ������/��/��K��)

	INT64 ddwTDVol; 
	INT64 ddwTDVal;
}Quote_StockKLData, *LPQuote_StockKLData; 

//nKLType:
//1 = 1��K;  
//2 = ��K; 
//3 = ��K;   
//4 = ��K;
//6 = 5��K; 
//7 = 15��K;  
//8 = 30��K;  
//9 = 60��K;
//
//nRehabType:
//0 = ����Ȩ��
//1 = ǰ��Ȩ��
//2 = ��Ȩ��

/**
* ��������ӿ� 
*/
interface IFTQuoteOperation 
{
	//���鶨�ģ����ش�����
	virtual StockSubErrCode Subscribe_PriceBase(const GUID &guidPlugin, LPCWSTR wstrStockCode,  StockMktType eType, bool bSubb) = 0;  
	virtual StockSubErrCode Subscribe_OrderQueue(const GUID &guidPlugin, LPCWSTR wstrStockCode, StockMktType eType, bool bSubb) = 0; 
	virtual StockSubErrCode Subscribe_RTData(const GUID &guidPlugin, LPCWSTR wstrStockCode, StockMktType eType, bool bSubb) = 0; 
	virtual StockSubErrCode Subscribe_KLData(const GUID &guidPlugin, LPCWSTR wstrStockCode, StockMktType eType, bool bSubb, int nKLType) = 0; 
	virtual QueryDataErrCode QueryStockRTData(const GUID &guidPlugin, DWORD* pCookie, LPCWSTR wstrStockCode, StockMktType eType) = 0;
	virtual QueryDataErrCode QueryStockKLData(const GUID &guidPlugin, DWORD* pCookie, LPCWSTR wstrStockCode, StockMktType eType, int nKLType) = 0;
};

/**
* �������ݵĽӿ�
*/
interface IFTQuoteData
{ 
	/**
	* ��ǰ�Ƿ���ʵʱ����
	*/
	virtual bool   IsRealTimeQuotes() = 0; 

	/**
	* stock ��hashֵ, �ص��ӿڷ��� 
	*/ 
	virtual INT64  GetStockHashVal(LPCWSTR pstrStockCode, StockMktType eMkt) = 0; 

	/**
	* ���������� 
	*/ 
	virtual bool   FillPriceBase(INT64 ddwStockHash,  Quote_PriceBase* pInfo) = 0; 

	/**
	* ���ʮ������
	*/ 
	virtual bool   FillOrderQueue(INT64 ddwStockHash, Quote_OrderQueue* parQuote, int nCount) = 0; 

	/**
	* ����ʱ����
	*/ 
	virtual bool   FillRTData(INT64 ddwStockHash, Quote_StockRTData* &pQuoteRT, int& nCount) = 0;

	virtual BOOL   IsRTDataExist(INT64 ddwStockHash) = 0;

	virtual void   DeleteRTDataPointer(Quote_StockRTData* pRTData) = 0; 

	/**
	* ���K������
	*/ 
	virtual BOOL   FillKLData(INT64 ddwStockHash, Quote_StockKLData* &pQuoteKL, int& nCount, int nKLType, int nRehabType) = 0;

	virtual BOOL   IsKLDataExist(INT64 ddwStockHash, int nKLType) = 0;

	virtual void   DeleteKLDataPointer(Quote_StockKLData* pRTData) = 0; 

	/**
	* 
	*/ 
	virtual void   CheckRemoveQuoteRT(INT64 ddwStockID) = 0;

	virtual void   CheckRemoveQuoteKL(INT64 ddwStockID, int nKLType) = 0;

	/**
	* dwTimeת��wstring
	*/ 
	virtual void   TimeStampToStr(INT64 ddwStockHash, DWORD dwTime, wchar_t szTime[64]) = 0;
}; 

/**
* �������ݻص�
*/
interface IQuoteInfoCallback
{ 
	/**
	* ����������Ϣ�仯 
	*/ 
	virtual void  OnChanged_PriceBase(INT64  ddwStockHash) = 0; 

	/**
	* ʮ�����ݱ仯
	*/ 
	virtual void  OnChanged_OrderQueue(INT64 ddwStockHash) = 0; 

	/**
	* ��ʱ���ݱ仯
	*/ 
	virtual void  OnChanged_RTData(INT64 ddwStockHash) = 0; 

		/**
	* ��ʱ���ݱ仯
	*/ 
	virtual void  OnChanged_KLData(INT64 ddwStockHash, int nKLType) = 0; 
};

interface IQuoteKLCallback
{
	/**
	* �����ʱ�ص�
	*/ 
	virtual void OnQueryStockRTData(DWORD dwCookie, int nCSResult) = 0; 

	/**
	* ����K�߻ص�
	*/ 
	virtual void OnQueryStockKLData(DWORD dwCookie, int nCSResult) = 0; 
};

