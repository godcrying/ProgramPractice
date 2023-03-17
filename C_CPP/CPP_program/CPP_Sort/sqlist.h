#ifndef SQLIST_H_INCLUDED
#define SQLIST_H_INCLUDED
#include <iostream>

using namespace std;
/*
*模板的声明和实现需要放在一起，不能分开成两个文件
*/
template <typename ElemType,typename KeyType>
class SqNode;

template <typename ElemType,typename KeyType>
class SqList;

//template <typename ElemType,typename KeyType>
//ostream &operator<<(ostream &out,SqNode<ElemType,KeyType> &node);

//节点模板
template <typename ElemType,typename KeyType>
class SqNode
{
protected:
    ElemType data;
    KeyType key;
public:
    KeyType Get_Key() const {return key;}
    ElemType Get_Node_Data() const {return data;}
    void Set_Key(KeyType newkey) { key=newkey;}
    void Set_Node_Data(ElemType newdata){data=newdata;}
    int Compare_with(SqNode& );
    void Print();

//设置友元类
//friend ostream &operator<<(ostream &out,SqNode<ElemType,KeyType> &node);
//使用上面的友元函数会报错。
friend class SqList<ElemType,KeyType>;
};

template <typename ElemType,typename KeyType>
int SqNode<ElemType,KeyType>::Compare_with(SqNode& node)
{
        if(node.Get_Key() > key)
            return -1;
        if(node.Get_Key() < key)
            return 1;
        else
            return 0;
}
template <typename ElemType,typename KeyType>
void SqNode<ElemType,KeyType>::Print()
{
    printf("%d",data); //模板不需要在定义时导入头文件，比如此处的<stdio.h>，
                       //只需要在使用模板的cpp文件中导入相关头文件就可以了
}

//线性顺序表
template <typename ElemType,typename KeyType>
class SqList
{
protected:
    SqNode<ElemType,KeyType> *nodes;
    int length;
    void QuickSortLocate(int low,int high);
public:
    SqList();
    ~SqList();
    int GetLength(){ return length;};
    const SqNode<ElemType,KeyType>& Get_Node(int index);
    void Swap_Nodes(int nd1,int nd2);
    void QuickSort();
    void Print();
};

//初始化
template <typename ElemType,typename KeyType>
SqList<ElemType,KeyType>::SqList(){
    nodes = new SqNode<ElemType,KeyType>[21];
    length = 20;

        for(int i=1;i<=length;i++)
        {
            nodes[i].key = rand()%20+1;
            nodes[i].data = nodes[i].key;
        }
    //printf("初始化完毕！！");
    cout << "初始化完毕！！" <<endl;
}
//析构
template <typename ElemType,typename KeyType>
SqList<ElemType,KeyType>::~SqList(){
    delete[] nodes;
    printf("析构完毕！！");
}
//打印
template <typename ElemType,typename KeyType>
void SqList<ElemType,KeyType>::Print()
{
    for(int i=1;i<=length;i++)
    {
        cout << nodes[i] << " ";
        //printf(" ");
    }
}

//获取某个元素的引用，考虑到仅使用元素值而不更改元素值
template <typename ElemType,typename KeyType>
//注意，const对象只能调用const方法
const SqNode<ElemType,KeyType>& SqList<ElemType,KeyType>::Get_Node(int index)
{
    return nodes[index];
}

//真正的快排函数
template <typename ElemType,typename KeyType>
void SqList<ElemType,KeyType>::QuickSortLocate(int low,int high)
{
     int tmp_low=low;
        int tmp_high = high;
        while(low<high)
        {
            while(low<high && nodes[high].Compare_with(nodes[low]) >=0 ) high--;
            Swap_Nodes(high,low);
            while(low<high && nodes[low].Compare_with(nodes[high]) < 0) low++;
            Swap_Nodes(high,low);
        }
        if(tmp_low < tmp_high){
        QuickSortLocate(tmp_low,low-1);
        QuickSortLocate(low+1,tmp_high);
        }
}

//快排
template <typename ElemType,typename KeyType>
void SqList<ElemType,KeyType>::QuickSort()
{
    QuickSortLocate(1,length);
}
//交换
template <typename ElemType,typename KeyType>
void SqList<ElemType,KeyType>::Swap_Nodes(int nd1,int nd2)
{
    nodes[0] = nodes[nd1];
    nodes[nd1] = nodes[nd2];
    nodes[nd2] = nodes[0];
}

//重载输出运算符
//注意，此处相当于声明了一个模板函数。只能使用SqNode类的公共成员。
//此模板函数无法声明为其他类的友元函数
template <typename ElemType,typename KeyType>
ostream &operator<<(ostream &out,SqNode<ElemType,KeyType> &node)
{
    out<<node.Get_Node_Data();
    return out;
}

template <typename ElemType,typename KeyType>
ostream &operator<<(ostream &out,SqList<ElemType,KeyType> &sqlist)
{
    for(int i=1;i<=sqlist.GetLength();i++)
    {
        out << sqlist.Get_Node(i).Get_Node_Data() << " ";
        //printf(" ");
    }
    return out;
}

#endif // SQLIST_H_INCLUDED
