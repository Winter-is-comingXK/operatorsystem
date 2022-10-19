#include "manage.h"

Manage *Manage::static_manage = nullptr;

bool Manage::exist(uint32_t pid) {
    return this->contains(PCB{.PID= pid});
}

OPTRESULT Manage::create(uint32_t _pid, PCB (*fun)()) {
    bool success = false;
    string mes;
    if (exist(_pid)) {
        success = false, mes = PROCESS_EXIST;
    }
    else {
        PCB p = fun();
        p.PID = _pid;
        this->emplace(p);
    }
    return {success, mes};
}

set<const PCB *> Manage::run() {
    set<const PCB *> r;
    for (const PCB &i: *this) {
        r.emplace(&i);
    }
    return r;
}

OPTRESULT Manage::suspend(uint32_t _pid) {
    bool b;
    string s;
    if (exist(_pid)) {
        auto i = this->get(_pid);
        switch (i->STATUS) {
            case PCB_STATUS::IN_MEM: {
                i->STATUS = PCB_STATUS::SUSPEND, b = true;
                break;
            }
            case PCB_STATUS::SUSPEND: {
                b = false, s = PROCESS_IS_SUSPEND;
                break;
            }
        }
    }
    else b = false, s = PROCESS_NOT_EXIST;
    return {b, s};
}

PCB *Manage::get(uint32_t _pid) {
    auto i = this->find(PCB{.PID=_pid});

    return i == this->end() ? nullptr : (PCB *) &(*i);
}

OPTRESULT Manage::kill(uint32_t _pid) {
    bool b;
    string s;
    if (exist(_pid)) {
        if (get(_pid)->isSuspend()) b = false, s = PROCESS_IS_SUSPEND;
        else this->erase(*get(_pid)), b = true;
    }
    else b = false, s = PROCESS_NOT_EXIST;

    return {b, s};
}

OPTRESULT Manage::activate(uint32_t _pid) {
    bool b;
    string s;
    if (exist(_pid)) {
        auto i = get(_pid);
        if (i->isSuspend())
            i->STATUS = PCB_STATUS::IN_MEM,
                    b = true;
        else
            i->STATUS = PCB_STATUS::SUSPEND,
            b = false,
            s = PROCESS_ACTIVATE;
    }
    else {
        b = false, s = PROCESS_NOT_EXIST;
    }
    return {b, s};
}

Manage *Manage::getInstance() {
    if (Manage::static_manage == nullptr) {
        Manage::static_manage = new Manage();
    }
    return Manage::static_manage;
}

