// Pack_Picture1.h: interface for the Pack_Picture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACK_PICTURE1_H__A38E312E_17B2_4374_AC9D_F4C01A0C57C5__INCLUDED_)
#define AFX_PACK_PICTURE1_H__A38E312E_17B2_4374_AC9D_F4C01A0C57C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Pack_Picture  
{
public:
	void OnPackMap(int left, int top, int bottom, int right);
	Pack_Picture();
	virtual ~Pack_Picture();

private:
	bool Tofile(HBITMAP hbitmap, LPSTR lpfilename);
	HBITMAP Copybitmap(LPRECT lprect);
};

#endif // !defined(AFX_PACK_PICTURE1_H__A38E312E_17B2_4374_AC9D_F4C01A0C57C5__INCLUDED_)
