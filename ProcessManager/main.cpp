#include <iostream>
#include "manage.h"

int mainUI() {
    int num;
    cout << endl << "******************************************";
    cout << endl << "               进程演示系统";
    cout << endl << "     1.创建新的进程        2.查看运行进程";
    cout << endl << "     3.换出某个进程        4.杀死运行进程";
    cout << endl << "     5.激活某个进程        6.退出系统";
    cout << endl << "******************************************";
    cout << endl << "请选择(1 ~ 6):";
    cin >> num;
    return num;
}

int main() {
    system("cls");
    uint32_t pid_tp;
    auto mgr = Manage::getInstance();
    while (true) {
        int n = mainUI();
        switch (n) {
            case 1: {
                cout << "请输入新进程 pid:";
                cin >> pid_tp;
                auto res = mgr->create(pid_tp, []() -> PCB {
                    PCB _tp{};
                    cout << "请输入新进程优先级:";
                    cin >> _tp.PRIORITY;
                    cout << "请输入新进程大小:";
                    cin >> _tp.SIZE;
                    cout << "请输入新进程内容:";
                    cin >> _tp.INFO;
                    return _tp;
                });
                if (not res.first) {
                    cout << res.second << endl;
                }
                break;
            }
            case 2: {
                auto ls = mgr->run();
                for (auto i: ls) {
                    cout << endl
                         << "\t进程编号 = " << i->PID
                         << "\t优先级 = " << i->PRIORITY
                         << "\t进程大小 = " << i->SIZE
                         << "\t进程状态 = " << to_string(i->STATUS)
                         << "\t进程信息 = " << i->INFO;
                }
                if (ls.empty())
                    cout << endl << " 当前没有运行进程" << endl;
                cout << endl;
                break;
            }
            case 3: {
                cout << endl << " 输入换出的 ID 值:";
                cin >> pid_tp;
                auto res = mgr->suspend(pid_tp);
                if (not res.first)
                    cout << res.second << endl;
                break;
            }
            case 4: {
                cout << endl << " 输入杀死进程的 ID 值:";
                cin >> pid_tp;
                auto res = mgr->kill(pid_tp);
                if (not res.first)
                    cout << res.second << endl;
                break;
            }
            case 5: {
                cout << endl << " 输入:";
                cin >> pid_tp;
                auto res = mgr->activate(pid_tp);
                if (not res.first) {
                    cout << res.second << endl;
                }
                break;
            }
            case 6: {
                exit(EXIT_SUCCESS);
            }
            default:cout << "选错啦" << endl;
        }
        cout << endl << "即将清屏" << endl;
        system("pause");
        system("cls");
    }
}
