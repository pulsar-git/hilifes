#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

//Log4CPP

#include <log4cpp/Category.hh>
#define LOGGER(a) \
	if(!logger)\
	logger = &log4cpp::Category::getInstance(std::string(a));

#define LOGGER_DEBUG \
	if(logger->isDebugEnabled())\
	 *logger << log4cpp::Priority::DEBUG

#define LOGGER_INFO \
	if(logger->isInfoEnabled())\
	 *logger << log4cpp::Priority::INFO 

#define LOGGER_NOTICE \
	if(logger->isNoticeEnabled())\
	 *logger << log4cpp::Priority::NOTICE 

#define LOGGER_WARN \
	if(logger->isWarnEnabled())\
	 *logger << log4cpp::Priority::WARN 

#define LOGGER_ERROR \
	if(logger->isErrorEnabled())\
	 *logger << log4cpp::Priority::ERROR 

#define LOGGER_CRIT \
	if(logger->isCritEnabled())\
	 *logger << log4cpp::Priority::CRIT 

#define LOGGER_ALERT \
	if(logger->isAlertEnabled())\
	 *logger << log4cpp::Priority::ALERT 

#define LOGGER_FATAL \
	if(logger->isFatalEnabled())\
	 *logger << log4cpp::Priority::FATAL 

#define LOGGER_EMERG \
	if(logger->isEmergEnabled())\
	 *logger << log4cpp::Priority::EMERG 


#endif //_LOGGER_H_
