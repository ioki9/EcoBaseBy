#pragma once

#include <wx/wx.h>
#include <wx/imagpng.h>
#include <wx/gdicmn.h>
#include "cMain.h"
#include "DBMain.h"


class cApp : public wxApp
{
public:
	cApp();
	~cApp();

private:
	cMain* m_frame1 = nullptr;

public:
	virtual bool OnInit();
};

