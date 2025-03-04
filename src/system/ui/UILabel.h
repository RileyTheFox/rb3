#ifndef UI_UILABEL_H
#define UI_UILABEL_H

#include "milo_types.h"
#include "rndobj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Font.h"
#include "rndobj/Text.h"
#include "ui/UIComponent.h"
#include "ui/UIColor.h"
#include "utl/MemMgr.h"

class UILabelDir : public RndDir /*, public UIFontImporter*/ {
public:
    UILabelDir();
    OBJ_CLASSNAME(UILabelDir);

    NEW_OVERLOAD
    DELETE_OVERLOAD

    int HighlightMeshGroup() const;

    NEW_OBJ(UILabelDir)
};

class UILabel : public UIComponent {
public:
    UILabel();
    virtual ~UILabel();
    OBJ_CLASSNAME(UILabel);
    OBJ_SET_TYPE(UILabel);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual void Draw();
    virtual void DrawShowing();
    virtual int CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);

    virtual void Highlight();

    virtual void Poll();
    virtual int CanHaveFocus();
    virtual void CopyMembers(const UIComponent*, Hmx::Object::CopyType);
    virtual void Update();
    virtual void SetCreditsText() {MILO_ASSERT(false, 78);}
    virtual void SetDisplayText();

    NEW_OVERLOAD
    DELETE_OVERLOAD

    void Terminate();
    void LabelUpdate(bool, bool);
    void AdjustHeight(bool);
    void SetFloat(const char*, float);
    void CenterWithLabel(UILabel*, bool, float);

    DataNode OnSetTokenFmt(const DataArray*);
    DataNode OnSetInt(const DataArray*);
    DataNode OnGetMaterialVariations(const DataArray*);
    DataNode OnGetAltMaterialVariations(const DataArray*);

    UILabelDir* mLabelDir;
    RndText* mText; // TrackWidget* in bank 5
    class String hi;
    ObjPtr<RndFont, class ObjectDir> mFont;
    const char* a;
    const char* b;
    class String c;
    float f;

    class String mPath;
    float h;
    ObjPtr<UIColor, class ObjectDir> mColor;
    ObjPtr<UIColor, class ObjectDir> mColor2;
    int x[0x14];

    NEW_OBJ(UILabel)
    static void Init();
    static bool sDeferUpdate;
};

#endif // UI_UILABEL_H
