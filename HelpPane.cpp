
// HelpPane.cpp
//
// references:
// https://strontic.github.io/xcyclopedia/library/clsid_8cec58ae-07a1-11d9-b15e-000d56bfe6ee.html
//
#include <iostream>
#include <unknwn.h>
#include <rpcndr.h>

MIDL_INTERFACE("8CEC592C-07A1-11D9-B15E-000D56BFE6EE")
IHxHelpPaneServer : public IUnknown{
public:

	virtual     HRESULT STDMETHODCALLTYPE DisplayTask(__RPC__in BSTR bstrUrl);
	virtual 	HRESULT STDMETHODCALLTYPE DisplayContents(__RPC__in BSTR bstrUrl);
	virtual 	HRESULT STDMETHODCALLTYPE DisplaySearchResults(__RPC__in BSTR bstrSearchQuery);
	virtual 	HRESULT STDMETHODCALLTYPE Execute(__RPC__in LPWSTR pcUrl);
};

int main()
{

	IHxHelpPaneServer* IPaneServer;
	GUID ClassHxHelpPaneServerc;
	CoInitialize(0);
	IIDFromString(L"{8CEC58AE-07A1-11D9-B15E-000D56BFE6EE}", &ClassHxHelpPaneServerc);
	HRESULT hr = CoCreateInstance(ClassHxHelpPaneServerc, NULL, CLSCTX_ALL, __uuidof(IHxHelpPaneServer), (void**)&IPaneServer);
	if (SUCCEEDED(hr))
	{
		hr = IPaneServer->Execute((LPWSTR)L"file:///c:\\windows\\system32\\calc.exe");
		if (SUCCEEDED(hr))
		{
			std::cout << "done" << std::endl;
			return 0;
		}
	}
	std::cout << "failed! error="<<GetLastError()<< std::endl;
}
