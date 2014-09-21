#ifndef MMX_LOGGER_HPP
#define MMX_LOGGER_HPP 1

#include <fstream>
#include <string>
#include <stdexcept>
#include <mutex>

#include "config.hpp"
#include "date.hpp"
#include "time.hpp"

namespace mmx {

	enum class logging_policy {
		DEBUG,
		WARNING,
		ERROR,
	};

	/**
	 *
	 */
	class logger {
	public:
		logger(const std::string& filename)
			: _filename(filename)
			, _format("[%D %T] '%F:%L' %P %M")
			, _mode(std::ios::out | std::ios::app)
		{
		}

		logger(const logger& ) MMX_CLASS_DELETE;
		logger& operator = (const logger& ) MMX_CLASS_DELETE;

		/** 
		 * %D, %d | date (YYYY-MM-DD)
		 * %T, %t | time (HH:MM:SS)
		 * %M, %m | message
		 * %P, %p | policy
		 * %L, %l | line
		 * %F, %f | file
		 *
		 * TODO: with (sub)strings? ie: %date, %time, %msg, %type
		 */
		void format(const std::string& fmt) {
			if (fmt.empty()) {
				throw std::invalid_argument("logger: no format specified");
			}

			const char* ptr = fmt.c_str();
			while (*ptr++) {
				if (*ptr == '%') {
					switch (*(++ptr)) {
						case 'D': case 'd': break;
						case 'T': case 't': break;
						case 'M': case 'm': break;
						case 'P': case 'p': break;
						case 'L': case 'l': break;
						case 'F': case 'f': break;
						default:
							throw std::invalid_argument(std::string("logger: invalid format specifier '") + *ptr + "'");
					}
				}
			}
			_format = fmt;
		}

		std::string format() const { return _format; }

		void remove_mode(std::ios_base::openmode mode) { _mode &= ~mode; }
		void add_mode(std::ios_base::openmode mode) { _mode |= mode; }
		std::ios_base::openmode mode() const { return _mode; }
		
		void rename(const std::string& filename) { _filename = filename; }
		std::string name() const { return _filename; }

		void print(logging_policy policy, const std::string& src, int line, const std::string& msg) {
			_mutex.lock();

			std::ofstream file(_filename.c_str(), _mode);
			
			if (!file.is_open()) {
				throw std::runtime_error("logger: unable to open '" + _filename + "'");
			}

			const char* ptr = _format.c_str();

			while (*ptr++) {
				if (*ptr == '%') {
					switch (*(++ptr)) {
						case 'D': case 'd': file << mmx::date::to_string(); break;
						case 'T': case 't': file << mmx::time::to_string(); break;
						case 'P': case 'p':
							switch (policy) {
								case logging_policy::DEBUG:   file << "<DEBUG>"; break;
								case logging_policy::WARNING: file << "<WARNING>"; break;
								case logging_policy::ERROR:   file << "<ERROR>"; break;
								default: ;
							}
							break;
						case 'M': case 'm': file << msg; break;
						case 'L': case 'l': file << line; break;
						case 'F': case 'f': file << src; break;
						default: ;
					}
				} else {
					file << *ptr;
				}
			}
			file << std::endl;

			file.flush();

			_mutex.unlock();
		}
		
	private:
		std::mutex               _mutex;
		std::string              _filename;
		std::string              _format;
		std::ios_base::openmode  _mode;
	};

	mmx::logger log("trace.log");

}         // ~namespace mmx

// undef this to disable logging
#define MMX_DEBUG 1

#if defined( MMX_DEBUG )
	#define DLOG(msg) mmx::log.print(mmx::logging_policy::DEBUG, __FILE__, __LINE__, (msg))
	#define WLOG(msg) mmx::log.print(mmx::logging_policy::WARNING, __FILE__, __LINE__, (msg))
	#define ELOG(msg) mmx::log.print(mmx::logging_policy::ERROR, __FILE__, __LINE__, (msg))
#else
	#define DLOG(...)
	#define WLOG(...)
	#define ELOG(...)
#endif    // MMX_DEBUG

#endif    // MMX_LOGGER_HPP

