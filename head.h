#include<string>
#include <conio.h>
#include<windows.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
union type//attribute  //属性类型
{
	const char *ch_type;
	int int_type;
	double dob_type;
};

typedef struct attribute_node//数据节点
{
	type vale;
	struct attribute_node * next;
	struct attribute_node * down;
}attribute_node, *node_list;

typedef struct attribute//属性节点
{
	string name;
	string type;
	string length;
	struct attribute * next;
	struct attribute_node * down;
}attribute, *attri_list;

typedef struct input_node//指令节点
{
	string str;
	struct input_node *next; 
}input_node, *input_list;

typedef struct index//表索引
{
	string formName;
	attri_list dir_form;
	struct index * next;
}index, *index_list;

typedef struct attIndex
{
	string key;
	node_list data_ptr;
	attIndex * next;
}attIndex,*attIndex_list;


bool Load();
void Read(input_list &head);
void choise(index_list &root, input_list head);
attri_list Creat(input_list instruct);
void Insert(index_list &root, input_list instruct);
bool Add(attri_list form_head,input_list instruct);
void Select(input_list instruct);
void Delete(index_list &root, input_list instruct);
void Drop(index_list &root, input_list instruct);
string FindDic(string name);
void WritDic(input_list head);
input_list Tear(string attri);
void WritDB(string lise_name,node_list head);
input_list ReadDB(string name);
void WritIndex(index_list &root,attri_list head);
attri_list GetIndex(index_list &root,string formName);
input_list ReadDic();
void ReWritDic(input_list ins);

void Alter(index_list &root, input_list ins);
void AlterAdd(attri_list form_head,input_list ins);
void AlterDrop(attri_list form_head,input_list ins);

void Update(index_list &root, input_list ins);
bool Match(attri_list form_head, input_list ins);

void Select(index_list &root,input_list ins);//选择查询函数
input_list GetKeyAtt(input_list& ins);
attri_list Grammer(index_list &root, input_list &ins);
//attri_list CreatResult(attri_list query_form,input_list KeyAtt);
void DelAtt(attri_list &frontAtt);
void FreeData(attri_list &Head);
void GetTmpForm(index_list form_head,input_list &ins);
attri_list CreatCondAtt(input_list &ins);//将每个条件属性 的名称 操作符= > < 和值 放在一个变量内 方便操作
void CopyData(attri_list form_head,node_list data);
attri_list CopyAtt(attri_list old_form);//copy 生成
bool AnalySel(input_list ins);//select指令的词法分析
void Display(attri_list formHead);//显示特定的数据
bool Judge(node_list first, node_list second);
attri_list LinkData(attri_list first, attri_list second);
input_list FormToInput(attri_list form_head);//将一个表 拆成input链表
void addInput(input_list &head,input_list tmp);//将一个input结点添加到一个input_list 链表中

void andEqual(attri_list form_head,attri_list attCur,string value,input_list mark);//从表中标记某属性值不等于value的元组为“nomark”
void andEqual(attri_list query_form,attri_list fir_att,attri_list sec_att,input_list mark);

void MoreThan(attri_list query_form,attri_list attCur,string value,input_list mark);//从表中删除某属性值小于等于value的元组
void LessThan(attri_list query_form,attri_list attCur,string value,input_list mark);//从表中删除某属性值小于等于value的元组
void delTuple(attri_list form);//删除不是第一行的元组


attri_list LinkTwoForm(attri_list first,attri_list second,index_list tmp_index);
attri_list CopyForm(attri_list old_form);//拷贝一个表
index_list LinkForm(index_list &root, input_list &ins);//连接表
attri_list findAtt(index_list form_head, string formName, string attName);
attri_list findAtt(index_list form, string attName);

void delTuple(attri_list query_form);//删除没有被选择的元组
void AndQuery(index_list form_head,attri_list CondAtt,input_list mark);//在临时生成的表上 进行 and 或者 or 连接
void judgeLogic(string logic, string &oldLab, string &newLab);
bool analyCondAtt(string cond,string &formName,string &attName);//查看条件 如果包涵student.sno形式则分别取出

input_list GetMarkList(index_list form_head,input_list &ins);
input_list initMarkList(attri_list form);
void mergeMarkList(input_list first,input_list second);

attri_list GetResult(index_list form_head,input_list key);
index_list resIndex(index_list form_head,input_list key);

//登陆注册
void Admin();
int userChoice();
string userLoad();
void userOper(string userName,index_list root);
bool adminLoad();
void adminOper(index_list root);
bool findUser(string newUser);
void Rigister();
void Grand(input_list ins);
bool CheckAuth(string userName,string oper);
void Grand(input_list ins);
void DelGrand(input_list ins);

//属性索引
void SwapIndex(attIndex_list fir, attIndex_list sec);//交换两个属性指针的值
void SortIndex(attIndex_list head);//对属性索引进行排序
attri_list findAtt(attri_list form,string attName);//通过表指针 找到需要找的属性位置
void BuiltAttIndex(index_list root,input_list ins);