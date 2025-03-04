#include "rndobj/MotionBlur.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(RndMotionBlur);

RndMotionBlur::RndMotionBlur() : mDrawList(this, kObjListNoNull) {

}

BEGIN_COPYS(RndMotionBlur)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    GET_COPY(RndMotionBlur)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mDrawList)
    END_COPY_CHECKED
END_COPYS

SAVE_OBJ(RndMotionBlur, 0x2B)

void RndMotionBlur::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mDrawList;
}

BEGIN_HANDLERS(RndMotionBlur)
    HANDLE(allowed_drawable, OnAllowedDrawable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x83)
END_HANDLERS

BEGIN_PROPSYNCS(RndMotionBlur)
    SYNC_PROP(draw_list, mDrawList)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
