#ifndef OPERATORSYSTEM_PCB_H
#define OPERATORSYSTEM_PCB_H

#include <cstdint>
#include <string>

enum PCB_STATUS {
    //NOT_EXIST,//本代码不需要
    IN_MEM,
    SUSPEND
};

inline std::string to_string(PCB_STATUS s){
    switch (s) {
        case IN_MEM:return "激活";
        case SUSPEND:return "挂起";
    }
    return "";
}

struct PCB {
    uint32_t PID;//进程编号
    uint32_t PRIORITY;//优先级
    uint32_t SIZE = -1;//进程大小
    PCB_STATUS STATUS = PCB_STATUS::IN_MEM;// 标志进程状态， 0  为不在内存， 1  为在内存， 2  为挂起
    std::string INFO;//进程信息

    bool isSuspend() const {
        return this->STATUS == PCB_STATUS::SUSPEND;
    }

    bool operator<(const PCB &other) const {
        return this->PID < other.PID;
    }

};

#endif //OPERATORSYSTEM_PCB_H
