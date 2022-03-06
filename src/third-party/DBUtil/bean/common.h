#ifndef COMMON_H
#define COMMON_H

// ---------------------------macro begin-----------------------------
// ***learnt from kaniol: `https://github.com/kaniol-lck/modmanager.git`***
#define PropertyWithAccess(type, methodType, name, methodName)\
    Q_PROPERTY(type name READ get##methodName WRITE set##methodName)\
    AccessMethod(methodType, name, methodName)


#define AccessMethod(methodType, name, methodName)\
    public:\
        void set##methodName(const decltype(QVariant().to##methodType()) &value) {\
            _##name = value;\
        }\
        decltype(QVariant().to##methodType()) get##methodName() const {\
            return _##name;\
        }\
    private:\
// ----------------------------macro end-------------------------------

#endif // COMMON_H
