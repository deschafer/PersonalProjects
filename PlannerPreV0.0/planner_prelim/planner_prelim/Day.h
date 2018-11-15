#pragma once

// CDay command target

class CDay //: public CObject
{
public:
	virtual ~CDay(void);

	CDay(int m_DayNumber);
	CDay(const int DayNumber, CPoint TopLeft, CPoint BottomRight);
	CDay(void) {};


	unsigned GetNumber() { return m_DayNumber; }
	void Initilize(int m_DayNumber);


	CRect m_Cell;			// Holds the dimensions of this object

protected:
	unsigned m_DayNumber;	// Part of this day object's date
	
};


