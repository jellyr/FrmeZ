#pragma once

typedef void* (__cdecl* tCreateInterface)(const char* name, int* pReturnCode);

class RecvProp;

class RecvTable
{
public:
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	const char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

class RecvProp
{
public:
	const char* m_pVarName;
	void* m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int	m_nElements;
	const char* m_pParentArrayPropName;
};

class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class IBaseClientDLL
{
public:
	virtual void fn0() = 0;
	virtual void fn1() = 0;
	virtual void fn2() = 0;
	virtual void fn3() = 0;
	virtual void fn4() = 0;
	virtual void fn5() = 0;
	virtual void fn6() = 0;
	virtual void fn7() = 0;
	virtual ClientClass* GetAllClasses() = 0;
};

void* GetInterface(const char* dllname, const char* interfacename);
intptr_t GetNetVarOffset(const char* tableName, const char* netvarName, ClientClass* clientClass, int offset = 0);