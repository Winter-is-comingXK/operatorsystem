#include <set>
#include "PCB.h"
#include <iostream>
#include <functional>

using namespace std;

typedef pair<bool, string> OPTRESULT;

//进程管理
class Manage : set<PCB> {
private:
    string PROCESS_IS_SUSPEND = "进程已挂起";
    string PROCESS_EXIST = "进程已存在";
    string PROCESS_NOT_EXIST = "进程不存在";
    string PROCESS_ACTIVATE = "进程已激活";
    uint32_t processNum = 0;
    uint32_t suspendNum = 0;
    uint32_t flag = 0;

    Manage() = default;

    static Manage *static_manage;
public:
    static Manage *getInstance();

    //创建进程
    OPTRESULT create(uint32_t _pid, PCB(*fun)());

    //获取正在运行的进程
    set<const PCB *> run();

    //挂起
    OPTRESULT suspend(uint32_t _pid);

    //杀死进程
    OPTRESULT kill(uint32_t _pid);

    //激活进程
    OPTRESULT activate(uint32_t _pid);

    //判断进程是否存在
    bool exist(uint32_t pid);

    //获取进程指针
    PCB *get(uint32_t _pid);

};

