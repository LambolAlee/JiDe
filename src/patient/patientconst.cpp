#include "patientconst.h"

QMap<int, QString> PatientConst::Sex {
    {0, "Female"},
    {1, "Male"}
};

QMap<int, QString> PatientConst::Ethnicity {
    {0, "Han"},
    {1, "Zhuang"},
    {2, "Manchu"},
    {3, "Hui"},
    {4, "Miao"},
    {5, "Uighur"},
    {6, "Yi"},
    {7, "Tujia"},
    {8, "Mongol"},
    {9, "Tibetan"},
    {10, "Buyi"},
    {11, "Dong"},
    {12, "Yao"},
    {13, "Korean"},
    {14, "Bai"},
    {15, "Hani"},
    {16, "Li"},
    {17, "Kazakh"},
    {18, "Dai"},
    {19, "She"},
    {20, "Lisu"},
    {21, "Gelao"},
    {22, "Lahu"},
    {23, "Dongxiang"},
    {24, "Wa"},
    {25, "Shui"},
    {26, "Naxi"},
    {27, "Qiang"},
    {28, "Du"},
    {29, "Xibe"},
    {30, "Mulam"},
    {31, "Kirghiz"},
    {32, "Daur"},
    {33, "Jingpo"},
    {34, "Salar"},
    {35, "Blang"},
    {36, "Maonan"},
    {37, "Tajik"},
    {38, "Pumi"},
    {39, "Achang"},
    {40, "Nu"},
    {41, "Evenki"},
    {42, "Gin"},
    {43, "Jino"},
    {44, "De'ang"},
    {45, "Uzbek"},
    {46, "Russian"},
    {47, "Yugur"},
    {48, "Bonan"},
    {49, "Menba"},
    {50, "Oroqin"},
    {51, "Drung"},
    {52, "Tatar"},
    {53, "Hezhen"},
    {54, "Lhoba"},
    {55, "Gaoshan"},
    {56, "Foreign"}
};

QString PatientConst::toString(FieldType type, int k)
{
    switch (type) {
    case ToSex:
        return Sex.value(k);
    case ToEthnicity:
        return Ethnicity.value(k);
    }
    return QString();
}

int PatientConst::toIndex(FieldType type, const QString &v)
{
    switch (type) {
    case ToSex:
        return Sex.key(v);
    case ToEthnicity:
        return Ethnicity.key(v);
    }
    return -1;
}
