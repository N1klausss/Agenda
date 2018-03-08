#include "Date.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>
Date::Date()
{
	m_year=0;
	m_month=0;
	m_day=0;
	m_hour=0;
	m_minute=0;
}
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
{
	m_year=t_year;
	m_month=t_month;
	m_day=t_day;
	m_hour=t_hour;
	m_minute=t_minute;
}
Date::Date(std::string dateString)
{
	m_year=(dateString[0]-48)*1000+(dateString[1]-48)*100+(dateString[2]-48)*10+dateString[3]-48;
	m_month=(dateString[5]-48)*10+(dateString[6]-48);
	m_day=(dateString[8]-48)*10+(dateString[9]-48);
	m_hour=(dateString[11]-48)*10+(dateString[11]-48);
	m_minute=(dateString[14]-48)*10+(dateString[15]-48);
}
int Date::getYear(void) const
{
	return m_year;
}
void Date::setYear(const int t_year)
{
	m_year=t_year;
}
int Date::getMonth(void) const
{
	return m_month;
}
void Date::setMonth(const int t_month)
{
	m_month=t_month;
}
int Date::getDay(void) const
{
	return m_day;
}
void Date::setDay(const int t_day)
{
	m_day=t_day;
}
int Date::getHour(void) const
{
	return m_hour;
}
void Date::setHour(const int t_hour)
{
	m_hour=t_hour;
}
int Date::getMinute(void) const
{
	return m_minute;
}
void Date::setMinute(const int t_minute)
{
	m_minute=t_minute;
}
bool Date::isValid(const Date t_date)
{
	if(t_date.m_month==1 || t_date.m_month==3 || t_date.m_month==5 || t_date.m_month==7 ||
			t_date.m_month==8 || t_date.m_month==10 || t_date.m_month==12)
		{
			if(t_date.m_day > 31){
				return false;
			}else{
				return true;
			}
		}
	if(t_date.m_month==2){
		if(t_date.m_year%400==0 || (t_date.m_year%4==0 && t_date.m_year%100!=0)){
			if(t_date.m_day > 29){
				return false;
			}else{
				return true;
			}
		}else{
			if(t_date.m_day > 28){
				return false;
			}else{
				return true;
			}			
		}
	}
	if(t_date.m_month==4 || t_date.m_month==6 || t_date.m_month==9 ||t_date.m_month==11){
			if(t_date.m_day > 30){
				return false;
			}else{
				return true;
			}
	}
}
Date Date::stringToDate(const std::string t_dateString)
{
	if(t_dateString[4]!='-' || t_dateString[7]!='-' || t_dateString[10]!='/' || t_dateString[13]!=':')
	{
		Date d(0,0,0,0,0);
		return d;
	}else{
		int y,m,d,h,m1;
		y=(t_dateString[0]-48)*1000+(t_dateString[1]-48)*100+(t_dateString[2]-48)*10+t_dateString[3]-48;
		m=(t_dateString[5]-48)*10+(t_dateString[6]-48);
		d=(t_dateString[8]-48)*10+(t_dateString[9]-48);
		h=(t_dateString[11]-48)*10+(t_dateString[11]-48);
		m1=(t_dateString[14]-48)*10+(t_dateString[15]-48);
		Date d1(y,m,d,h,m1);
		return d1;
	}
}
std::string Date::dateToString(Date t_date)
{   if(!Date::isValid(t_date))
	{
		return "0000-00-00/00:00";
	}
	std::stringstream s; 
	std::string s1;
	s << std::setfill('0') << std::setw(4) << t_date.m_year << '-' << std::setfill('0') << std::setw(2) << t_date.m_month << '-'
	<< std::setfill('0') << std::setw(2) << t_date.m_day << '/' << std::setfill('0') << std::setw(2) << t_date.m_hour << ':' <<
	std::setfill('0') << std::setw(2) << t_date.m_minute;
	s >> s1;
	return s1;
}
Date &Date::operator=(const Date &t_date)
{
	m_year=t_date.m_year;
	m_month=t_date.m_month;
	m_day=t_date.m_day;
	m_hour=t_date.m_hour;
	m_minute=t_date.m_minute;
	return *this;
}
bool Date::operator==(const Date &t_date) const
{
	if(	m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour==t_date.m_hour && m_minute==t_date.m_minute){
		return true;
	}else{
		return false;
	}
}
bool Date::operator>(const Date &t_date) const
{
	if(m_year>t_date.m_year){
		return true;
	}else if(m_year<t_date.m_year){
		return false;
	}else{
		if(m_month>t_date.m_month){
			return true;
		}else if(m_month<t_date.m_month){
			return false;
		}else{
			if(m_day>t_date.m_day){
				return true;
			}else if(m_day<t_date.m_day){
				return false;
			}else{
				if(m_hour>t_date.m_hour){
					return true;
				}else if(m_hour<t_date.m_hour){
					return false;
				}else{
					if(m_minute>t_date.m_minute){
						return true;
					}else {
						return false;
					}	
				}			
			}
		}
	}
}
bool Date::operator<(const Date &t_date) const
{
	if(m_year<t_date.m_year){
		return true;
	}else if(m_year>t_date.m_year){
		return false;
	}else{
		if(m_month<t_date.m_month){
			return true;
		}else if(m_month>t_date.m_month){
			return false;
		}else{
			if(m_day<t_date.m_day){
				return true;
			}else if(m_day>t_date.m_day){
				return false;
			}else{
				if(m_hour<t_date.m_hour){
					return true;
				}else if(m_hour>t_date.m_hour){
					return false;
				}else{
					if(m_minute<t_date.m_minute){
						return true;
					}else {
						return false;
					}	
				}			
			}
		}
	}
}
bool Date::operator>=(const Date &t_date) const
{
	if(m_year>t_date.m_year){
		return true;
	}else if(m_year<t_date.m_year){
		return false;
	}else{
		if(m_month>t_date.m_month){
			return true;
		}else if(m_month<t_date.m_month){
			return false;
		}else{
			if(m_day>t_date.m_day){
				return true;
			}else if(m_day<t_date.m_day){
				return false;
			}else{
				if(m_hour>t_date.m_hour){
					return true;
				}else if(m_hour<t_date.m_hour){
					return false;
				}else{
					if(m_minute>t_date.m_minute || m_minute==t_date.m_minute){
						return true;
					}else {
						return false;
					}	
				}			
			}
		}
	}
}
bool Date::operator<=(const Date &t_date) const
{
	if(m_year<t_date.m_year){
		return true;
	}else if(m_year>t_date.m_year){
		return false;
	}else{
		if(m_month<t_date.m_month){
			return true;
		}else if(m_month>t_date.m_month){
			return false;
		}else{
			if(m_day<t_date.m_day){
				return true;
			}else if(m_day>t_date.m_day){
				return false;
			}else{
				if(m_hour<t_date.m_hour){
					return true;
				}else if(m_hour>t_date.m_hour){
					return false;
				}else{
					if(m_minute<t_date.m_minute || m_minute==t_date.m_minute){
						return true;
					}else {
						return false;
					}	
				}			
			}
		}
	}
}
