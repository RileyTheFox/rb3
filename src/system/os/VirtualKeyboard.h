#ifndef OS_VIRTUALKEYBOARD_H
#define OS_VIRTUALKEYBOARD_H
#include "obj/Object.h"
#include "utl/Str.h"
#include "obj/Msg.h"
#include "os/User.h"
#include <list>

class VirtualKeyboard : public Hmx::Object {
public:
    VirtualKeyboard();
    virtual ~VirtualKeyboard();
    virtual DataNode Handle(DataArray*, bool);
    std::list<void*> mListIdk;
    Hmx::Object* mPobjKeyboardCallback;
    bool mCallbackReady;
    bool mMsgOk;
    class String mCallbackMsg;

    void Init();
    void ClearKeyboardCallback();
    void Poll();
    void Terminate();

    void PlatformPoll();
    void PlatformTerminate();
    DataNode OnShowKeyboardUI(const DataArray*);
    DataNode ShowKeyboardUI(const LocalUser*, int, class String, class String, class String, int, int);
};

BEGIN_MESSAGE(VirtualKeyboardResultMsg, virtual_keyboard_result_msg, int, const char*);
END_MESSAGE;

inline VirtualKeyboardResultMsg::VirtualKeyboardResultMsg(int i, const char* c)
    : Message(Type(), DataNode(i), DataNode(c ? c : gNullStr)) {
}

#endif
