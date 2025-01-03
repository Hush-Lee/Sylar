#include "log.hpp"
namespace sylar{
	Logger::Logger(std::string &name):m_name(name){}

	void Logger::addAppender(LogAppender::ptr appender){
		m_appenders.push_back(appender);
	}

	void Logger::delAppender(LogAppender::ptr appender){
		for(auto it:m_appenders){
			if(*it ==appender){
				m_appenders.erase(it);
				break;
			}
		}
	}
	void Logger::log(LogLevel::Level level,LogEvent::ptr event){
		if(level>=m_level){
			for(auto &i: m_appenders){
				i->log(level,event);
			}
		}
	}

	void Logger::debug(LogEvent::ptr event){
		debug(LogLevel::DEBUG,event);
	}
	void Logger::info(LogEvent::ptr event){
		debug(LogLevel::INFO,event);
	}
	void Logger::warn(LogEvent::ptr event){
		debug(LogLevel::WARN,event);
	}
	void Logger::error(LogEvent::ptr event){
		debug(LogLevel::ERROR,event);
	}
	void Logger::fatal(LogEvent::ptr event){
		debug(LogLevel::FATAL,event);
	}


	FileLogAppender::FileLogAppender(const std::string& filename):m_filename(filename){

	}
	
	void FileLogAppender::log(LogLevel::Level level,LogEvent::ptr event){
		if(level >= m_level){
			m_filestream << m_formatter.format(event);
		}
	}

	bool FileLogAppender::reopen(){
		if(m_filestream){
			m_filestream.close();
		}
		m_filestream.open(m_filename);
		return !!m_filestream;
	}
	void StdoutLogAppender::log(LogLevel::Level level,LogEvent::ptr event){
		if(m_level>= m_level){
			std::cout<<m_formatter.format(event);
		}
	}
}

