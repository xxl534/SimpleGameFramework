#include "sgfCorePCH.h"
#include "sgfColor.h"
#include "sgfMath.h"

namespace sgf
{ 

	Color& Color::FromHSV(float a_fHue, float a_fSaturation, float a_fValue)
	{
		//reference from:https://en.wikipedia.org/wiki/HSL_and_HSV
		float fHue = MathClamp(a_fHue, 0.f, 360.f);
		float fSaturation = MathClamp(a_fSaturation, 0.f, 1.f);
		float fValue = MathClamp(a_fValue, 0.f, 1.f);

		float fC = fValue * fSaturation;
		float fH = fHue / 60.f;
		float fX = fC * (1.f - MathAbs(fmodf(fH, 2.f) - 1.f));
		float fR1, fG1, fB1;
		if (fH < 1.f)
		{
			fR1 = fC;
			fG1 = fX;
			fB1 = 0.f;
		}
		else if (fH < 2.f)
		{
			fR1 = fX;
			fG1 = fC;
			fB1 = 0.f;
		}
		else if (fH < 3.f)
		{
			fR1 = 0.f;
			fG1 = fC;
			fB1 = fX;
		}
		else if (fH < 4.f)
		{
			fR1 = 0.f;
			fG1 = fX;
			fB1 = fC;
		}
		else if (fH < 5.f)
		{
			fR1 = fX;
			fG1 = 0.f;
			fB1 = fC;
		}
		else
		{
			fR1 = fC;
			fG1 = 0.f;
			fB1 = fX;
		}
		float fM = fValue - fC;

		r = fR1 + fM;
		g = fG1 + fM;
		b = fB1 + fM;

		return *this;
	}
}