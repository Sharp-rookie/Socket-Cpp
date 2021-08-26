#include <stdio.h>
#include <string.h>
#include <stdarg.h>

class CFile
{
private: //私有成員
    FILE *m_fp;
    bool m_bEnBuffer;

public:                    //公有成員、属性
    CFile();               //构造函数
    CFile(bool bEnBuffer); //重构的构造函数
    ~CFile();              //析构函数

    void EnBuffer(bool bEnBuffer = true); //启/禁用缓冲区

    bool Open(const char *filename, const char *openmode); //打开文件

    void Fprintf(const char *fmt, ...); //向文件写入数据

    bool Fgets(char *strBuffer, const int ReadSize); //读取文件一行

    void Close(); //关闭文件指针
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("请输入待打开的文件名。\n");
        return -1;
    }

    CFile File;

    if (File.Open(argv[1], "r") == false)
    {
        printf("File.Open(%s) failed.\n", argv[1]);
        return -1;
    }

    char strLine[301];

    while (true)
    {
        if (File.Fgets(strLine, 300) == false)
            break;
        printf("%s", strLine);
    }
}

CFile::CFile()
{
    m_fp = 0;
    m_bEnBuffer = true;
}

CFile::CFile(bool bEnBuffer)
{
    m_fp = 0;
    m_bEnBuffer = bEnBuffer;
}

void CFile::Close()
{
    if (m_fp != 0)
        fclose(m_fp);
    m_fp = 0;
}

CFile::~CFile()
{
    Close();
}

void CFile::EnBuffer(bool bEnBuffer)
{
    m_bEnBuffer = bEnBuffer;
}

bool CFile::Open(const char *filename, const char *openmode)
{
    Close();

    if ((m_fp = fopen(filename, openmode)) == 0)
        return false;
    else
        return true;
}

void CFile::Fprintf(const char *fmt, ...)
{
    if (m_fp == 0)
        return;

    va_list arg;
    va_start(arg, fmt);
    vfprintf(m_fp, fmt, arg);
    va_end(arg);

    if (m_bEnBuffer == false)
        fflush(m_fp);
}

bool CFile::Fgets(char *strBuffer, const int ReadSize)
{
    if (m_fp == 0)
        return false;

    memset(strBuffer, 0, ReadSize);

    if (fgets(strBuffer, ReadSize, m_fp) == 0)
        return false;
    else
        return true;
}