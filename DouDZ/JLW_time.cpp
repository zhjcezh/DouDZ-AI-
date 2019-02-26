#include <time.h>
#include "JLW_time.h"

#ifdef _WIN32
#if (_MSC_VER >= 1400)         /* Check version */	/* after vs2005 */
#pragma warning(disable: 4996) /* Disable deprecation */	/* _CRT_SECURE_NO_WARNINGS */
#endif /* #if defined(NMEA_WIN) && (_MSC_VER >= 1400) */
#endif // #ifdef _WIN32

// 检测日期是否正确
bool isDateValid(int date);

// 验证是否在有效期内
bool check_UsefulLife(int startDate, int endDate, int vDate);

bool isInPeriodOfValidity( const std::string& dateStr )
{
	int startDate = 0, endDate = 0, vDate = 0;
	std::string date(dateStr);

	if ( dateStr.length() != 20 )
	{
		return false;
	}

	//for ( int i = 0; i < date.length(); ++i )
	//{
	//	date[i] = (date[i] - 'A')/2 + '0';
	//}

	for ( int i = 0; i < 8; ++i )
	{
		startDate = 10*startDate + date[i] - '0';
		endDate = 10*endDate + date[8+i] - '0';
	}
	for ( int i = 16; i < 20; ++i )
	{
		vDate = 10*vDate + date[i] - '0';
	}

	return check_UsefulLife(startDate, endDate, vDate);
}

// 检测日期是否正确
bool isDateValid(int date)
{
	int year = 0, month = 0, day = 0;
	bool flag = false;

	year = date / 10000;
	date %= 10000;

	month = date / 100;
	date %= 100;

	day = date;

	if ( year > 2013 && year < 2100		// 验证年份
		&& month > 0 && month < 13 
		&& day > 0 && day < 32 )
	{
		flag = true;
	}
#ifdef DEBUG
	std::cout<<year<<" "<<month<<" "<<day<<" "<<date<<std::endl;
#endif

	return flag;
}


// 验证是否在有效期内
bool check_UsefulLife(int startDate, int endDate, int vDate)
{
	bool flag = false;
	int rightDate = 0;

	char tmp[10];
	time_t t = time(0);
	strftime( tmp, sizeof(tmp), "%Y%m%d", localtime(&t) );

	for ( int i = 0; i < 8; ++i )
	{
		rightDate = rightDate*10 + tmp[i] - '0';
	}

	do 
	{
		if ( !isDateValid(rightDate) || !isDateValid(startDate) || !isDateValid(endDate) )
		{
			break;
		}

		if ( startDate <= rightDate && rightDate <= endDate )
		{
			flag = true;
		}
	} while ( false );

	return flag;
}