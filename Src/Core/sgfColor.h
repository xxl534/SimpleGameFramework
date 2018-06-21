#pragma once
/********************************************************************
	created:	2018/06/21
	created:	21:6:2018   20:18
	filename: 	E:\SimpleGameFramework\Src\Core\sgfColor.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfColor
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
namespace sgf
{
#pragma pack( push,1)
	struct ColorByte4
	{
		union
		{
			struct  
			{
				uint8 r, g, b, a;
			};
			uint32 col;
		};

		ColorByte4()
			:col(0xFFFFFFFF)
		{

		}

		ColorByte4(uint32 a_col)
			:col(a_col)
		{

		}

		ColorByte4(uint8 a_r, uint8 a_g, uint8 a_b, uint8 a_a)
			:r(a_r)
			, g(a_g)
			, b(a_b)
			, a(a_a)
		{

		}

		explicit ColorByte4( float a_r, float a_g, float a_b, float a_a )
			:r(a_r < 0 ? 0 : (a_r > 1 ? 255 : (uint8)(a_r * 255)))
			, g(a_g < 0 ? 0 : (a_g > 1 ? 255 : (uint8)(a_g * 255)))
			, b(a_b < 0 ? 0 : (a_b > 1 ? 255 : (uint8)(a_b * 255)))
			, a(a_a < 0 ? 0 : (a_a > 1 ? 255 : (uint8)(a_a * 255)))
		{

		}


		bool operator==(const ColorByte4& a_rhs)
		{
			return col == a_rhs.col;
		}

		bool operator!=(const ColorByte4& a_rhs)
		{
			return col != a_rhs.col;
		}

		ColorByte4& operator*=(float a_f)
		{
			r *= a_f;
			g *= a_f;
			b *= a_f;
			a *= a_f;
			return *this;
		}

		ColorByte4 operator*(float a_f) const
		{
			ColorByte4 ret(*this);
			ret *= a_f;
			return ret;
		}

		ColorByte4& operator+=(const ColorByte4& a_rhs)
		{
			r += a_rhs.r;
			g += a_rhs.g;
			b += a_rhs.b;
			a += a_rhs.a;
			return *this;
		}

		ColorByte4 operator+(const ColorByte4& a_rhs) const
		{
			ColorByte4 ret(*this);
			ret += a_rhs;
			return ret;
		}

		ColorByte4& operator-=(const ColorByte4& a_rhs)
		{
			r -= a_rhs.r;
			g -= a_rhs.g;
			b -= a_rhs.b;
			a -= a_rhs.a;
			return *this;
		}

		ColorByte4 operator-(const ColorByte4& a_rhs) const
		{
			ColorByte4 ret(*this);
			ret -= a_rhs;
			return ret;
		}

		ColorByte4 operator/(float a_f) const
		{
			ColorByte4 ret(*this);
			ret *=  1 / a_f;
			return ret;
		}
	};

#define RECP255 0.0039215686274509803921568627451
	struct Color
	{
		union
		{
			struct
			{
				float r, g, b, a;
			};
			float f[4];
		};

		const static float ms_fRecip;
		Color()
			:r(1)
			, g(1)
			, b(1)
			, a(1)
		{

		}

		Color(const ColorByte4& col)
			:r(col.r*RECP255)
			, g(col.g*RECP255)
			, b(col.b*RECP255)
			, a(col.a*RECP255)
		{

		}

		Color(float a_r, float a_g, float a_b, float a_a)
			:r(a_r)
			, g(a_g)
			, b(a_b)
			, a(a_a)
		{

		}

		explicit Color(uint8 a_r, uint8 a_g, uint8 a_b, uint8 a_a)
			:r(a_r *RECP255)
			, g(a_g*RECP255)
			, b(a_b*RECP255)
			, a(a_a*RECP255)
		{

		}

		inline Color& operator*=(float a_f)
		{
			r *= a_f;
			g *= a_f;
			b *= a_f;
			a *= a_f;
			return *this;
		}

		inline Color operator*(float a_f) const
		{
			return Color(r*a_f, g*a_f, b*a_f, a*a_f);
		}

		inline Color& operator*=(const Color& a_col)
		{
			r *= a_col.r;
			g *= a_col.g;
			b *= a_col.b;
			a *= a_col.a;
			return *this;
		}

		inline Color operator*(const Color& a_col) const
		{
			return Color(r*a_col.r, g*a_col.g, b*a_col.b, a*a_col.a);
		}

		inline Color operator/(float a_f) const
		{
			return this->operator*(1 / a_f);
		}

		inline Color& operator/=(float a_f)
		{
			return this->operator*=(1 / a_f);
		}

		inline Color& operator/=(const Color& a_col)
		{
			r /= a_col.r;
			g /= a_col.g;
			b /= a_col.b;
			a /= a_col.a;
			return *this;
		}

		inline Color operator+(const Color& a_col)
		{
			return Color(r + a_col.r, g + a_col.g, b + a_col.b, a + a_col.a);
		}

		inline Color& operator+=(const Color& a_col)
		{
			r += a_col.r;
			g += a_col.g;
			b += a_col.b;
			a += a_col.a;
			return *this;
		}

		inline Color operator-(const Color& a_col)
		{
			return Color(r - a_col.r, g - a_col.g, b - a_col.b, a - a_col.a);
		}

		inline Color& operator-=(const Color& a_col)
		{
			r -= a_col.r;
			g -= a_col.g;
			b -= a_col.b;
			a -= a_col.a;
			return *this;
		}

		inline Color& operator=(const Color& a_col)
		{
			r = a_col.r;
			g = a_col.g;
			b = a_col.b;
			a = a_col.a;
			return *this;
		}

		inline bool operator==(const Color& a_col) const
		{
			return (r == a_col.r) && (g == a_col.g) && (b == a_col.b) && (a == a_col.a);
		}

		inline bool operator!=(const Color& a_col) const
		{
			return (r != a_col.r) || (g != a_col.g) || (b != a_col.b) || (a != a_col.a);
		}

		inline ColorByte4 ToColorByte4() const
		{
			return ColorByte4(r, g, b, a);
		}

		Color&			FromHSV(float a_fHue, float a_fSaturation, float a_fValue);
	};
#pragma pack(pop)
}