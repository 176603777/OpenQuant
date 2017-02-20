#pragma once
#include <vector>
#include "ProtoDataStruct.h"


//////////////////////////////////////////////////////////////////////////
//��ȡ��������Э��, PROTO_ID_GET_BASIC_PRICE

struct	BasicPriceReqBody
{
	int nStockMarket;
	std::string strStockCode;
};

struct BasicPriceAckBody
{
	int nHigh;
	int nOpen;
	int nClose;
	int nLastClose;
	int nLow;
	int nCur;
	INT64 nVolume;
	INT64 nTurnover;
	INT64 nLotSize;

	int nStockMarket;
	std::string strStockCode;
	DWORD dwTime;
};

struct	BasicPrice_Req
{
	ProtoHead			head;
	BasicPriceReqBody	body;
};

struct	BasicPrice_Ack
{
	ProtoHead				head;
	BasicPriceAckBody		body;
};


//////////////////////////////////////////////////////////////////////////
//��ȡ������ϢЭ��, PROTO_ID_GET_GEAR_PRICE

struct	GearPriceReqBody
{
	int nGetGearNum;
	int nStockMarket;	
	std::string strStockCode;	
};

struct GearPriceAckItem
{
	int nBuyOrder;
	int nSellOrder;
	int nBuyPrice;
	int nSellPrice;
	INT64 nBuyVolume;
	INT64 nSellVolume;
};

typedef std::vector<GearPriceAckItem>	VT_GEAR_PRICE;

struct GearPriceAckBody 
{
	int nStockMarket;
	std::string strStockCode;
	VT_GEAR_PRICE vtGear;
};

struct	GearPrice_Req
{
	ProtoHead			head;
	GearPriceReqBody	body;
};

struct	GearPrice_Ack
{
	ProtoHead			head;
	GearPriceAckBody	body;
};

//////////////////////////////////////////////////////////////////////////
//��ȡ��ʱ����Э��, PROTO_ID_QT_GET_RT_DATA

struct	RTDataReqBody
{
	int nStockMarket;	
	std::string strStockCode;
};

struct RTDataAckItem
{
	int   nDataStatus; 
	std::wstring strTime; 
	DWORD dwOpenedMins;  //���̵ڶ��ٷ���  

	int   nCurPrice;
	DWORD nLastClosePrice; //��������̼� 

	int   nAvgPrice;

	INT64 ddwTDVolume;
	INT64 ddwTDValue;  
};

typedef std::vector<RTDataAckItem>	VT_RT_DATA;

struct RTDataAckBody 
{
	int nLastTrueDataNum;
	int nStockMarket;
	std::string strStockCode;
	VT_RT_DATA vtRTData;
};

struct RTData_Req
{
	ProtoHead			head;
	RTDataReqBody		body;
};

struct RTData_Ack
{
	ProtoHead			head;
	RTDataAckBody		body;
};

//////////////////////////////////////////////////////////////////////////
//��ȡ��ǰK������Э��

struct	KLDataReqBody
{
	int nRehabType;
	int nKLType;
	int nStockMarket;
	std::string strStockCode;
};

struct KLDataAckItem
{
	int   nDataStatus; 
	std::wstring strTime; 
	int   nOpenPrice; 
	int   nClosePrice; 
	int   nHighestPrice; 
	int   nLowestPrice;  
	int   nPERatio; //��ӯ��(��λС��)
	int   nTurnoverRate;//������(���ɼ�ָ������/��/��K��)
	INT64 ddwTDVol; 
	INT64 ddwTDVal;
};

typedef std::vector<KLDataAckItem>	VT_KL_DATA;

struct KLDataAckBody 
{
	int nRehabType;
	int nKLType;
	int nStockMarket;
	std::string strStockCode;
	VT_KL_DATA vtKLData;
};

struct KLData_Req
{
	ProtoHead			head;
	KLDataReqBody		body;
};

struct KLData_Ack
{
	ProtoHead			head;
	KLDataAckBody		body;
};