#pragma once

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <list>
#include <memory>
#include <string>

namespace sylar {


	class LogEvent{
	public:
		using ptr=std::shared_ptr<LogEvent>; 
		LogEvent();
	private:
		const char* m_file{nullptr};
		int32_t m_line{0};
		uint32_t m_elapse{0};			//程序启动到现在毫秒数
		uint32_t m_threadId{0};
		uint32_t m_fiberId{0};			//协程id
		uint64_t m_time{0};
		std::string m_content;
	};

	class LogLevel{
	public:
		enum Level{
				DEBUG{0},
				INFO,
				WARN,
				ERROR,
				FATAL
			};
	};


	//日志
	class Logger{
	public:
		using ptr=std::shared_ptr<Logger>;
	
		Logger(const std::string& name){};

		void log(LogLevel::Level level,LogEvent::ptr event);
		void debug(LogEvent::ptr event);
		void info(LogEvent::ptr event);
		void warn(LogEvent::ptr event);
		void fatal(LogEvent::ptr event);
		void error(LogEvent::ptr event);

		void addAppender(LogAppender::ptr appender);
		void delAppender(LogAppender::ptr appender);
		LogLevel::Level getLevel(){return m_level;}
		void setLevel(LogLevel:Level val){m_level=val;}
	private:
		std::string m_name;
		LogLevel::Level m_level;
		std::list<LogAppender::ptr> m_appenders;		//输出位置列表

	};


	//日志输出
	class LogAppender{
	public:
		using ptr=std::shared_ptr<LogAppender>;
		virtual ~LogAppender();

		virtual void log(LogLevel::Level level,LogEvent::ptr event)=0;

		void setFormatter(LogFormatter::ptr val){
			m_formatter=val;
		}
		LogFormatter::ptr getFormatter()const{
			return m_formatter;
		}
	protected:
		LogLevel::Level m_level;
		LogFormatter::ptr m_formatter;
	};


	class LogFormatter{

	};

	class StdoutLogAppender : public LogAppender{
	public:
		using ptr=std::shared_ptr<StdoutLogAppender>;
		void log(LogLevel::Level level, LogEvent::ptr event)override;
	};


	class FileLogAppender:public LogAppender{
	public:
		using  ptr= std::shared_ptr<FileLogAppender>;
		FileLogAppender(const std::string& filename);
		void log(LogLevel::Level level,LogEvent::ptr event)override;

		bool reopen();
	private:
		std::string m_filename;
		std::ofstream m_filestream;

	};


}
