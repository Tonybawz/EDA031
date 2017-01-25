#include <ctime>  // time and localtime
#include "date.h"

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d) : year(y), month(m), day(d){

}

std::istream& operator>>(std::istream& is, Date& d){


	is >> d.year;
	is >> d.month;
	d.month *= -1;
	is >> d.day;
	d.day *= -1;

	if (d.getMonth() > 12 || d.getDay() > Date::daysPerMonth[d.getMonth()]){
		is.setstate(std::ios_base::failbit);
		return is;
	}
	return is;
	}


std::ostream& operator<<(std::ostream& os, const Date& d){
 os << d.getYear() << '-' << d.getMonth() << '-' << d.getDay() << std::endl;
 return os;
}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

void Date::next() {
	++day;
	if (day > daysPerMonth[month-1]){
		day = 1;
		++month;
		if (month > 12){
			++year;
			month = 1;
		}
	}

}
