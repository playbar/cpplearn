//
//memory_trace.hpp 动态内存使用跟踪工具，对内存的动态分配，释放进行跟踪
//
#ifndef _utils_memory_trace_
#define _utils_memory_trace_

#include <cstdio>
#include <cstring>
#include <functional>
#include <string>
#include <chrono>
#include <mutex>
#include <map>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif


//动态内存跟踪内容如下：
//1.是否存在内存泄漏
//2.是否存在double free
//3.是否交叉释放（如用new申请的内存，确实用free释放）
//4.内存地址是否有效
namespace utils
{
	//内存申请方式
	enum AllocWay
	{
		ALLOC_BY_MALLOC = 0,//通过C函数申请的内存
		ALLOC_BY_NEW, //通过new操作符申请的内存
		ALLOC_BY_NEW_ARRAY, //通过new[]操作符申请的内存
		
	};

	//内存事件
	enum MemoryEvent
	{
		MEMORY_EVENT_ALLOC = 0, //内存申请事件
		MEMORY_EVENT_FREE, //内存释放事件，成功释放
		MEMORY_EVENT_LEAK, //内存泄漏
		MEMORY_EVENT_INVALID, //无效内存
		MEMORY_EVENT_DOUBLE, //多次释放
		MEMORY_EVENT_ILLEGAL, //不正确的释放方式，例如使用malloc申请，使用delete释放
		MEMORY_EVENT_REUSE, //内存释放后，再次申请内存，返回相同的地址

	};

	//内存信息
	struct MemoryInfo
	{
		//内存申请信息，这些信息在构造函数中初始化
		const void *address; //内存地址
		const size_t size; //内存大小
		const AllocWay alloc_way; //内存申请方式
		const std::string alloc_file; //内存申请发生的文件
		const int alloc_line; //内存申请发生的行
		const std::chrono::steady_clock::time_point timestamp; //内存申请发生的时间

		//内存释放信息，这些信息在内存首次释放时填写
		AllocWay free_way; //内存释放方式
		std::string free_file; //内存释放发生的文件
		int free_line; //内存释放发生的行

		//扩展信息，多次释放时使用，如果内存被多次释放，该信息会被填写
		AllocWay free_way_ex; //内存释放方式
		std::string free_file_ex; //内存释放发生的文件
		int free_line_ex; //内存释放发生的行
		

		MemoryInfo(const void *_address, size_t _size, const AllocWay _way, const char *_file, int _line)
			: address(_address)
			, size(_size)
			, alloc_way(_way)
			, alloc_file(_file)
			, alloc_line(_line)
			, timestamp(std::chrono::steady_clock::now())
			, free_way(ALLOC_BY_MALLOC)
			, free_file("")
			, free_line(-1)
			, free_way_ex(ALLOC_BY_MALLOC)
			, free_file_ex("")
			, free_line_ex(-1)
		{}
	};

	//默认内存跟踪信息回调，该类会把信息输出到标准错误，并写入到memory_trace.txt
	class DefaultMemoryTraceHandle final
	{
	public:
		static DefaultMemoryTraceHandle &GetInstance(void) { static DefaultMemoryTraceHandle _instance; return _instance; }

		~DefaultMemoryTraceHandle(void)
		{
			if (m_TraceFile != nullptr) {
				fclose(m_TraceFile);
				m_TraceFile = nullptr;
			}
		}

		/*
			@func OnMemoryEvent
			@brief 内存回调信息处理函数
			@param[in] event 内存事件，参看MemoryEvent定义
			@param[in] MemoryInfo 内存信息，参看MemoryInfo定义
			@return 无
		*/
		void OnMemoryEvent(MemoryEvent event, const MemoryInfo &info)
		{
			auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - info.timestamp).count();
			static const char *alloc_way_name[] = { "malloc", "new", "new []" };
			const char *prefix = "[MEMORY TRACE]";
			static const size_t MAX_LOG_SIZE = 4096;
			char log[MAX_LOG_SIZE];

			switch (event) {
			case MEMORY_EVENT_ALLOC: //内存申请事件
				snprintf(log, MAX_LOG_SIZE, \
					"%s ALLOC 0x%p { + %s %d }", \
					prefix, info.address, info.alloc_file.c_str(), info.alloc_line);
				break;
			case MEMORY_EVENT_FREE: //正常释放
				snprintf(log, MAX_LOG_SIZE, \
					"%s FREE 0x%p { - %s %d %lld } { + %s %d }", \
					prefix, info.address, info.free_file.c_str(), info.free_line, (long long)diff, \
					info.alloc_file.c_str(), info.alloc_line);
				break;
			case MEMORY_EVENT_LEAK: //内存泄漏
				snprintf(log, MAX_LOG_SIZE, \
					"%s LEAK 0x%p %zu { + %s %d }", \
					prefix, info.address, info.size, info.alloc_file.c_str(), info.alloc_line);
				break;
			case MEMORY_EVENT_INVALID: //无效内存
				snprintf(log, MAX_LOG_SIZE, \
					"%s INVALID 0x%p { - %s %d }", \
					prefix, info.address, info.free_file.c_str(), info.free_line);
				break;
			case MEMORY_EVENT_DOUBLE: //多次释放
				snprintf(log, MAX_LOG_SIZE, \
					"%s DOUBLE 0x%p { = %s %d } { - %s %d } { + %s %d }", \
					prefix, info.address, info.free_file_ex.c_str(), info.free_line_ex, \
					info.free_file.c_str(), info.free_line, \
					info.alloc_file.c_str(), info.alloc_line);
				break;
			case MEMORY_EVENT_ILLEGAL: //不正确的释放方式，例如使用malloc申请，使用delete释放
				snprintf(log, MAX_LOG_SIZE, \
					"%s ILLEGAL 0x%p { - %s %d %s } { + %s %d %s }", \
					prefix, info.address, info.free_file.c_str(), info.free_line, alloc_way_name[info.free_way], \
					info.alloc_file.c_str(), info.alloc_line, alloc_way_name[info.alloc_way]);
				break;
			case MEMORY_EVENT_REUSE:
				snprintf(log, MAX_LOG_SIZE, \
					"%s REUSE 0x%p { - %s %d } { + %s %d }", \
					prefix, info.address, info.free_file.c_str(), info.free_line, \
					info.alloc_file.c_str(), info.alloc_line);
				break;
			default:
				break;
			}
#if defined(_WIN32) || defined(_WIN64)
			if (event == MEMORY_EVENT_ALLOC || event == MEMORY_EVENT_FREE || event == MEMORY_EVENT_REUSE) {
				SetConsoleTextAttribute(::GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_GREEN);
				fprintf(stderr, "%s\n", log);
				SetConsoleTextAttribute(::GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(::GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED);
				fprintf(stderr, "%s\n", log);
				SetConsoleTextAttribute(::GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY);
			}
#else
			if (event == MEMORY_EVENT_ALLOC || event == MEMORY_EVENT_FREE || event == MEMORY_EVENT_REUSE)
				fprintf(stderr, "\033[1;32m%s\033[0m\n", log);
			else
				fprintf(stderr, "\033[1;31m%s\033[0m\n", log);
#endif
			fwrite(log, 1, strlen(log), m_TraceFile);
			fwrite("\n", 1, 1, m_TraceFile);
		}

		DefaultMemoryTraceHandle(const DefaultMemoryTraceHandle &) = delete;
		DefaultMemoryTraceHandle(DefaultMemoryTraceHandle &&) = delete;
		DefaultMemoryTraceHandle &operator=(const DefaultMemoryTraceHandle &) = delete;
		bool operator==(const DefaultMemoryTraceHandle &) const = delete;

	protected:
		DefaultMemoryTraceHandle(void)
		{
			m_TraceFile = fopen("./memory_trace.txt", "w");
			if (m_TraceFile == nullptr) {
				printf("failed to open ./memory_trace.txt\n");
				abort();
			}
		}

		FILE *m_TraceFile; //跟踪日志文件句柄

	};

	//内存信息跟踪
	class MemoryTrace final
	{
	public:
		virtual ~MemoryTrace(void) { LeakCheck(); }

		static MemoryTrace &GetInstance(void) 
		{ 
			//规定对象创建顺序，使事件句柄对象先于跟踪对象，生命周期大于跟踪对象
			DefaultMemoryTraceHandle::GetInstance();
			static MemoryTrace _instance; 
			return _instance; 
		}

		/*
			@func SetMemoryTraceProcFunc
			@brief 设置内存跟踪信息回调函数，仅仅打印内存跟踪信息，不可以对内存进行释放
			@param[in] func 内存跟踪信息回调函数，函数原型void (MemoryEvent, const MemoryInfo &)
			@return 无
		*/
		void SetMemoryTraceProcFunc(std::function<void(MemoryEvent, const MemoryInfo &)> func) { m_MemoryTraceProcFunc = func; }

		/*
			@func Alloc
			@brief 内存申请跟踪，将申请的内存信息添加到内存信息列表
			@param[in] _address 申请内存返回的地址
			@param[in] _size 内存大小
			@param[in] _way 内存申请方式，参看AllocWay定义
			@param[in] _file 内存申请发生的文件
			@param[in] _line 内存申请发生的行
			@return 无
		*/
		void Alloc(void *_address, size_t _size, const AllocWay _way, const char *_file, int _line)
		{
			MemoryInfo info(_address, _size, _way, _file, _line);
			std::lock_guard<std::mutex> lk(m_MemoryInfoMutex);
			auto iterator = m_MemoryInfoMap.find(_address);
			if (iterator != m_MemoryInfoMap.end()) { //内存被释放后，再次申请内存，返回了同样的地址
				m_MemoryTraceProcFunc(MEMORY_EVENT_REUSE, iterator->second);
				m_MemoryInfoMap.erase(iterator);
			}
			m_MemoryInfoMap.insert(std::make_pair(_address, info));
			m_MemoryTraceProcFunc(MEMORY_EVENT_ALLOC, info);
		}

		/*
			@func Free
			@brief 内存释放跟踪，用释放的内存信息和内存信息列表中的内存信息做对比，看是否存在异常情况
			@param[in] _address 待释放内存的地址
			@param[in] _way 释放内存的方式，参看AllocWay定义
			@param[in] _file 内存释放发生的文件
			@param[in] _line 内存释放发生的行
			@return 如果存在异常情况，返回false；不存在异常，返回true
		*/
		bool Free(void *_address, const AllocWay _way, const char *_file, int _line)
		{
			std::lock_guard<std::mutex> lk(m_MemoryInfoMutex);
			auto memory_info_iterator = m_MemoryInfoMap.find(_address);
			//该内存地址不在内存信息列表之中，为无效的内存
			if (memory_info_iterator == m_MemoryInfoMap.end()) {
				MemoryInfo info(_address, 0, _way, _file, _line);
				info.free_way = _way;
				info.free_file = _file;
				info.free_line = _line;
				m_MemoryTraceProcFunc(MEMORY_EVENT_INVALID, info);
				return false;
			}

			MemoryInfo info = memory_info_iterator->second;
			//如果内存信息的释放文件不为空，表明内存已经释放过
			if (!memory_info_iterator->second.free_file.empty()) {
				info.free_way_ex = _way;
				info.free_file_ex = _file;
				info.free_line_ex = _line;
				m_MemoryTraceProcFunc(MEMORY_EVENT_DOUBLE, info);
				return false;
			}

			//申请方式与释放方式不同，交叉释放
			if (memory_info_iterator->second.alloc_way != _way) {
				info.free_way = _way;
				info.free_file = _file;
				info.free_line = _line;
				m_MemoryTraceProcFunc(MEMORY_EVENT_ILLEGAL, info);
				return false;
			}
			
			//正常释放，修改内存信息
			memory_info_iterator->second.free_way = _way;
			memory_info_iterator->second.free_file = _file;
			memory_info_iterator->second.free_line = _line;
			m_MemoryTraceProcFunc(MEMORY_EVENT_FREE, memory_info_iterator->second);
			
			return true;
		}

		/*
			@func LeakCheck
			@brief 内存泄漏检测
			@param 无
			@return 无
			@note 析构函数调用了LeakCheck，因此程序退出时会自动进行内存泄漏检测，但用户也可以在自己需要的时候（如
				  多模块情况下，释放某个模块时）调用LeckCheck进行内存泄漏检测
		*/
		void LeakCheck(void)
		{
			//对于还没有释放的内存，其free_file为空
			std::lock_guard<std::mutex> lk(m_MemoryInfoMutex);
			auto memory_info_iterator = m_MemoryInfoMap.begin();
			for (; memory_info_iterator != m_MemoryInfoMap.end(); ++memory_info_iterator) {
				if (memory_info_iterator->second.free_file.empty()) {
					m_MemoryTraceProcFunc(MEMORY_EVENT_LEAK, memory_info_iterator->second);
				}
			}
		}

		MemoryTrace(const MemoryTrace &) = delete;
		MemoryTrace(MemoryTrace &&) = delete;
		MemoryTrace &operator=(const MemoryTrace &) = delete;
		bool operator==(const MemoryTrace &) const = delete;

	protected:
		MemoryTrace(void)
			: m_MemoryInfoMutex()
			, m_MemoryInfoMap()
			, m_MemoryTraceProcFunc()
		{
			m_MemoryTraceProcFunc = [&](MemoryEvent event, const MemoryInfo &info)->void { DefaultMemoryTraceHandle::GetInstance().OnMemoryEvent(event, info); };
		}

		std::mutex m_MemoryInfoMutex; //多线程安全
		std::map<void *, MemoryInfo> m_MemoryInfoMap; //以内存地址为键，内存信息为值，进行内存信息检索
		std::function<void(MemoryEvent, const MemoryInfo &)> m_MemoryTraceProcFunc; //内存跟踪信息回调函数
	
	};

	//重载malloc函数
	void *malloc(size_t size, const char *_file, int _line)
	{
		void *ptr = ::malloc(size);
		if (ptr != nullptr)
			MemoryTrace::GetInstance().Alloc(ptr, size, ALLOC_BY_MALLOC, _file, _line);

		return ptr;
	}

	//重载realloc函数
	void *realloc(void *ptr, size_t size, const char *_file, int _line)
	{
		//无效的内存地址，不能realloc
		if (!MemoryTrace::GetInstance().Free(ptr, ALLOC_BY_MALLOC, _file, _line)) 
			return nullptr;

		ptr = ::realloc(ptr, size);
		if (ptr != nullptr)
			MemoryTrace::GetInstance().Alloc(ptr, size, ALLOC_BY_MALLOC, _file, _line);

		return ptr;
	}

	//重载free函数
	void free(void *ptr, const char *_file, int _line)
	{
		if (MemoryTrace::GetInstance().Free(ptr, ALLOC_BY_MALLOC, _file, _line))
			::free(ptr);
	}

}

//定义_MEMORY_TRACE，则会进行内存跟踪，否则不进行内存跟踪
#ifdef _MEMORY_TRACE

//重载new操作符
inline void *operator new(size_t size, const char *_file, int _line)
{
	void *ptr = ::malloc(size);
	if (ptr != nullptr)
		utils::MemoryTrace::GetInstance().Alloc(ptr, size, utils::ALLOC_BY_NEW, _file, _line);

	return ptr;
}

//重载delete操作符
inline void operator delete(void *ptr, const char *_file, int _line)
{
	if (utils::MemoryTrace::GetInstance().Free(ptr, utils::ALLOC_BY_NEW, _file, _line))
		::free(ptr);
}

//重载new[]操作符
inline void *operator new[](size_t size, const char *_file, int _line)
{
	void *ptr = ::malloc(size);
	if (ptr != nullptr)
		utils::MemoryTrace::GetInstance().Alloc(ptr, size, utils::ALLOC_BY_NEW_ARRAY, _file, _line);

	return ptr;
}

//重载delete[]操作符
inline void operator delete[](void *ptr, const char *_file, int _line)
{
	if (utils::MemoryTrace::GetInstance().Free(ptr, utils::ALLOC_BY_NEW_ARRAY, _file, _line))
		::free(ptr);
}

//定义内存操作符相关宏
#define new new(__FILE__, __LINE__)
#define delete(ptr) operator delete(ptr, __FILE__, __LINE__)
#define delete_array(ptr) operator delete[](ptr, __FILE__, __LINE__)

//定义molloc相关宏
#define malloc(size) utils::malloc((size), __FILE__, __LINE__)
#define realloc(ptr, size) utils::realloc(ptr, (size), __FILE__, __LINE__)
#define free(ptr) utils::free(ptr, __FILE__, __LINE__)

#else

//定义内存操作符相关宏
#define new new
#define delete(ptr) delete(ptr)
#define delete_array(ptr) delete[](ptr)

//定义molloc相关宏
#define malloc(size) malloc((size))
#define realloc(ptr, size) realloc(ptr, (size))
#define free(ptr) free(ptr)


#endif


#endif