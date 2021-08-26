#include <stdio.h>
#include <string.h>
#include <string>

class CGirl // 定义超女类
{
public:
    std::string m_name; // 姓名
    int m_age;          // 年龄
    int m_height;       // 身高，单位：厘米cm
    std::string m_sc;   // 身材，火辣；普通；飞机场。
    std::string m_yz;   // 颜值，漂亮；一般；歪瓜裂枣。

    int Show() // 显示超女基本信息的成员函数体
    {
        printf("姓名：%s，年龄：%d，身高：%d，身材：%s，颜值：%s\n", m_name.c_str(), m_age, m_height, m_sc.c_str(), m_yz.c_str());
    }
};

class CKCon : public CGirl // 定义王妃类，从超女类继承
{
public:
    std::string m_ch;     // 称号
    std::string m_palace; // 居住的宫殿
    int m_sal;            // 奉禄

    int Show() // 显示王妃的称号、宫殿和奉禄
    {
        printf("姓名：%s，称号：%s，栖：%s，奉禄：%d两银子。\n", m_name.c_str(), m_ch.c_str(), m_palace.c_str(), m_sal);
    }
};

int main()
{
    CKCon KCon; // 实例化一个KCon对象

    KCon.m_name = "杨玉环";
    KCon.m_age = 28;
    KCon.m_height = 168;
    KCon.m_sc = "火辣";
    KCon.m_yz = "漂亮";
    KCon.m_ch = "杨贵妃";
    KCon.m_palace = "华清宫";
    KCon.m_sal = 10000;

    KCon.Show(); // 如果子类中没有Show函数，就会调用父类的Show函数。
}