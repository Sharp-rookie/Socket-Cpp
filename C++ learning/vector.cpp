#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <string>

using namespace std;

int vector_int()
{
    int height = 0;
    std::vector<int> vheight;

    while (true)
    {
        printf("输入身高（0-结束输入）：");
        scanf("%d", &height);
        if (height == 0)
            break;
        vheight.push_back(height);
    }

    for (int i = 0; i < vheight.size(); i++)
        printf("veight[%d] = %d\n", i, vheight[i]);

    sort(vheight.begin(), vheight.end());

    for (int i = 0; i < vheight.size(); i++)
        printf("vheight[%d] = %d\n", i, vheight[i]);
}

int vector_string()
{
    char strtmp[50];
    std::string name;
    std::vector<std::string> vname;

    while (true)
    {
        printf("请输入超女姓名（0-结束输入）：");
        scanf("%s", strtmp);
        if (strcmp(strtmp, "0") == 0)
            break;
        vname.push_back(strtmp); //string的构造函数支持char[]，表面上看push_back()进去的是char[]，实际上会被转换为string
    }

    for (int ii = 0; ii < vname.size(); ii++)
        printf("vname[%d]=%s\n", ii, vname[ii].c_str());
}

struct st_girl // 超女数据结构
{
    char name[50]; // 姓名
    int age;       // 年龄
};
int vector_struct()
{
    struct st_girl stgirl;
    std::vector<struct st_girl> vgirl;

    strcpy(stgirl.name, "西施");
    stgirl.age = 18;
    vgirl.push_back(stgirl);

    printf("%d\n", vgirl.empty());

    for (int ii = 0; ii < vgirl.size(); ii++)
        printf("vgirl[%d].name=%s,vgirl[%d].age=%d\n", ii, vgirl[ii].name, ii, vgirl[ii].age);

    for (int ii = 0; ii < vgirl.size(); ii++)
    {
        memcpy(&stgirl, &vgirl[ii], sizeof(struct st_girl));
        printf("stgirl.name=%s,stgirl.age=%d\n", stgirl.name, stgirl.age);
    }
}

bool sortbyname(const st_girl &p1, const st_girl &p2)
{
    if (strcmp(p1.name, p2.name) <= 0)
        return true;
    else
        return false;
}
bool sortbyage(const st_girl &p1, const st_girl &p2)
{
    if (p1.age < p2.age)
        return true;
    return false;
}

int main()
{
    struct st_girl stgirl;             // 超女数据结构
    std::vector<struct st_girl> vgirl; // 存放超女结构体的容器

    strcpy(stgirl.name, "西施");
    stgirl.age = 18;
    vgirl.push_back(stgirl);

    strcpy(stgirl.name, "杨玉环");
    stgirl.age = 28;
    vgirl.push_back(stgirl);

    //sort(vgirl.begin(),vgirl.end());   // 如果不指定排序函数，编译将报错.如果vector容器中元素的数据类型不是基本数据类型，sort函数必须指定排序方法函数。
    //sort(vgirl.begin(),vgirl.end(),sortbyname); // 按超女的姓名排序
    sort(vgirl.begin(), vgirl.end(), sortbyage); // 按超女的年龄排序

    for (int ii = 0; ii < vgirl.size(); ii++)
    {
        printf("vgirl[%d].name=%s,vgirl[%d].age=%d\n",
               ii, vgirl[ii].name, ii, vgirl[ii].age);
    }
}