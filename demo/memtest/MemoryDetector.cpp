//
// Created by hou guoli on 2018/7/10.
//

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cstdlib>
#include <execinfo.h>
#include <thread>

#define PAGE_SHIFT 12
#define PAGE_SIZE   (1UL << PAGE_SHIFT)
#define PAGE_MASK   (~(PAGE_SIZE-1))


#define BUF_LEN 1024

using namespace std;

int buf[BUF_LEN] = {0};
int* p = &buf[512];


class MemoryDetector
{
public:
    typedef void (*segv_handler) (int sig, siginfo_t *si, void *unused);

    static void init(const char *path)
    {
        register_handler(handler);
        fd_ = open(path, O_RDWR|O_CREAT, 777);
    }

    static int protect(void *ptr, int len)
    {
        address_ = reinterpret_cast<uint64_t>(ptr);
        len_ = len;
        uint64_t start_address = (address_ >> PAGE_SHIFT) << PAGE_SHIFT;
        return mprotect(reinterpret_cast<void *>(start_address), PAGE_SIZE, PROT_READ);
    }

    static int umprotect(void *ptr, int len)
    {
        uint64_t addr = reinterpret_cast<uint64_t>(ptr);
        uint64_t start_address = (addr >> PAGE_SHIFT) << PAGE_SHIFT;
        return mprotect(reinterpret_cast<void *>(start_address), PAGE_SIZE, PROT_READ | PROT_WRITE);
    }

    static int umprotect()
    {
        uint64_t start_address = (address_ >> PAGE_SHIFT) << PAGE_SHIFT;
        return mprotect(reinterpret_cast<void *>(start_address), PAGE_SIZE, PROT_READ | PROT_WRITE);
    }

    static void finish()
    {
        close(fd_);
    }

private:
    static void register_handler(segv_handler sh)
    {
        struct sigaction act;
        act.sa_sigaction = sh;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
        if(sigaction(SIGSEGV, &act, NULL) == -1){
            exit(0);
        }
    }

    static void handler(int sig, siginfo_t *si, void *unused)
    {
        uint64_t address = reinterpret_cast<uint64_t>(si->si_addr);
        if (address >= address_ && address < address_ + len_) {
            umprotect(si->si_addr, PAGE_SIZE);
            my_backtrace();
        }
    }

    static void my_backtrace()
    {
        const int N = 100;
        void* array[100];
        int size = backtrace(array, N);
        backtrace_symbols_fd(array, size, fd_);
    }

    static uint64_t address_;
    static int len_;
    static int fd_;
};

uint64_t MemoryDetector::address_;
int MemoryDetector::len_;
int MemoryDetector::fd_;


void func() {
    char* q = reinterpret_cast<char*>(p);
    *q = static_cast<char>(0xFF); //Line 101
}

int main() {
    MemoryDetector::init("memdemo.rst");
    MemoryDetector::protect(p, 4);

    std::thread t(func);
    t.join();
    sleep(5);
    MemoryDetector::finish();

    return 0;
}