#include<iostream>
#include"head.h"
using namespace std;

int main()
{
	Admin();
	getchar();
	return 0;
}

void Menu()
{
	system("cls");
	cout<<"---------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<"                             MySQL模拟"<<endl;
	cout<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
}

int userChoice()
{
	int choice;
	cout<<"普通用户注册请按 1"<<endl;
	cout<<"普通用户登陆请按 2："<<endl;
	cout<<"管理员登陆请按   3："<<endl;
    cin>>choice;

	return choice;
}

void Admin()
{
	while(1)
	{
		Menu();
		int level;
		level = userChoice();
		index_list root=NULL;
		string check;
		bool b = false;
		switch(level)
		{
		    case 1:Rigister();
			     break;
		    case 2:
			     check = userLoad();
		         if(!check.empty())
		         {
					 cout<<"用户登陆成功！   按任意键确定"<<endl;
			         getchar();
					 getchar();
					 userOper(check,root);
			     }
			     else
			     {
				     cout<<"用户名或密码不正确！    按任意键确定"<<endl<<endl;
					 getchar();
					 getchar();
			     }
			     break;
		    case 3:
		         b = adminLoad();
		         if(b)
		         {
					 cout<<"管理员登陆成功！   按任意键确定"<<endl;
			         getchar();
					 getchar();
		             adminOper(root);
		         }
		         else
		         {
			         cout<<"管理员用户名或密码错误！  按任意键确定"<<endl;
					 getchar();
					 getchar();
		         }
				 break;
		    default:
		         cout<<"输入错误！ 按任意键确定"<<endl;
				 getchar();
		}
	}
}


string userLoad()
{
	system("cls");
	cout<<"---------------------------------------------"<<endl;
	cout<<"                用户登陆                     "<<endl;
	cout<<"---------------------------------------------"<<endl;
	
	cout<<"请输入用户名："<<endl;
	string userName;
	cin>>userName;
	cout<<"请输入密码："<<endl;
	string password;
	while (1)
	{
		char ch = getch();
		if (ch =='\r')
			break;
		password += ch;
		cout<<"*";
	}
    cout<<endl;
	string check;
	ifstream in("password.dat");
	if(in)
	{
		while(!in.eof())
		{
			string user,pass;
			in>>user>>pass;
			if(userName == user && password == pass)
			{
				check = userName;
			}
		}
		in.close();
		return check;
	}
}

void userOper(string userName,index_list root)
{
	system("cls");
	Menu();
	while(1)
	{
	    input_list input=NULL;
	    Read(input);
		string oper = input->str;
		if(oper == "exit")
			break;
		bool check = CheckAuth(userName,oper);
		if(check)
		{
			choise(root,input);
		}
	    else
		{		
			cout<<"所在用户组无此权限！"<<endl;
	    }
	}    
}

bool CheckAuth(string userName,string oper)
{
	bool check = false;
	ifstream in(userName.c_str());
	string tmp;
	if(in)
	{
		while(!in.eof())
		{
			in>>tmp;
			if(tmp == oper)
			{
				check = true;
				break;
			}
		}
	}
	return check;
}


bool adminLoad()
{
	system("cls");
	cout<<"---------------------------------------------"<<endl;
	cout<<"               管理员登陆                     "<<endl;
	cout<<"---------------------------------------------"<<endl;

	cout<<"请输入管理员用户名："<<endl;
	string userName;
	cin>>userName;
	cout<<"请输入管理员密码："<<endl;
	string password;
	while (1)
	{
		char ch = getch();
		if (ch =='\r')
			break;
		password += ch;
		cout<<"*";
	}
	//cin>>password;
    cout<<endl;
	bool check = false;
	ifstream in("adminpassword.dat");
	if(in)
	{
		while(!in.eof())
		{
			string user,pass;
			in>>user>>pass;
			if(userName == user && password == pass)
			{
				check = true;
			}
		}
		in.close();
		return check;
	}
}


void adminOper(index_list root)
{
	system("cls");
	Menu();
	while(1)
	{	
		input_list input=NULL;
	    Read(input);
		if(input->str == "exit")
			break;
	    choise(root, input);
			
    }  
}

void Rigister()
{
	system("cls");
	cout<<"---------------------------------------------"<<endl;
	cout<<"                用户注册                     "<<endl;
	cout<<"---------------------------------------------"<<endl;

	string userName;
    while(1)
	{
		cout<<"请输入用户名："<<endl;
		
		cin>>userName;
		bool b = findUser(userName);
		if(b)
		{
			cout<<"该用户名已存在！"<<endl;
			continue;
		}

	cout<<"请输入密码(长度不小于6位)："<<endl;
	string password;
	//cin>>password;
	while (1)
	{
		char ch = getch();
		if (ch =='\r')
			break;
		password += ch;
		cout<<"*";
	}
	cout<<endl;
	if(password.length() < 6)
	{
		cout<<"密码长度必须大于6位！"<<endl<<endl;
		continue;
	}
	cout<<"请再次输入密码："<<endl;
	string secpassword;
	while (1)
	{
		char ch = getch();
		if (ch =='\r')
			break;
		secpassword += ch;
		cout<<"*";
	}
	cout<<endl;
	if(password != secpassword)
	{
		cout<<"两次输入密码不一致！"<<endl<<endl;
		continue;
	}
	ofstream out("password.dat",ios_base::app);
	out<<userName<<"\t"<<password<<endl;
	out.close();
	break;
	}
	cout<<"注册成功！  按任意键确定"<<endl<<endl;
	getchar();
	getchar();
}

bool findUser(string newUser)
{
	ifstream in("password.dat");
	string tmpUser,tmpssword;
	bool check = false;
	if(in)
	{
		while(!in.eof())
		{
			in>>tmpUser>>tmpssword;
			if(tmpUser == newUser)
			{
				check = true;
			}
		}
	}
	in.close();
	return check;
}

void Grand(input_list ins)
{
	input_list Cursor = ins->next;
	string userName = Cursor->str;

	Cursor = Cursor->next;
	ofstream out(userName.c_str(),ios_base::app);
	while(Cursor)
	{
		out<<Cursor->str;
		Cursor = Cursor->next;
	}
	out.close();
	cout<<"对"<<userName<<"设置权限成功！"<<endl;
}

void DelGrand(input_list ins)
{
	input_list Cursor = ins->next;
	string userName = Cursor->str;

	Cursor = Cursor->next;
	string deloper = Cursor->str;
	
	input_list head = new input_node;
    head->next = NULL;
	ifstream in(userName.c_str());
	if(in)
	{
		while(!in.eof())
		{
		string oper;
		in>>oper;
		if(oper == deloper)
			continue;
		input_list tmp = new input_node;
		tmp->str = oper;
		tmp->next = head->next;
		head->next = tmp;
		}
	}
	in.close();
	ofstream out(userName.c_str());
	if(out)
	{
		while(head->next)
		{
			head = head->next;
			out<<head->str;
		}
	}
	cout<<"对"<<userName<<"收回权限成功"<<endl;
}

void Read(input_list &head)//读取指令
{
	input_list cursor = NULL;
	input_list rear;
	cout<<"请输入指令："<<endl;

	string s;
	cin>>s;
	while(s!="$")
	{
		cursor = new input_node;
		cursor->str = s;
		cursor->next = NULL;
		if(!head)
		{
			 head = cursor;
			 rear = head;
		}
		else
		{
			rear->next = cursor;
			rear = rear->next;
		}
		cin>>s;
	} 
}
void choise(index_list &root, input_list head)
{
	string order = head->str;

	if(order =="creat") 
	{
		if(head->next->str == "table")
		{
			//cout<<"指令正确"<<endl;
			input_list formname = head->next->next;

			string form_attri = FindDic(formname->str);
			if(!form_attri.empty())//在数据字典中查找名为list_name的表是否已经存在
			{
				cout<<formname->str<<"表已经存在"<<endl;
				return;
			}
			//cout<<"准备建立名为："<<form->str<<"的表"<<endl;
			attri_list form = Creat(formname);
			WritDic(formname);//写入数据字典
			WritIndex(root,form);
			cout<<"建表成功"<<endl<<endl;
		}
		else if(head->next->str == "index")
		{
			BuiltAttIndex(root,head);
		}
		else
		{
			cout<<order<<" "<<head->next->str<<"指令错误"<<endl;
			return;
		}
	}
	else if(order == "insert")
	    Insert(root,head);
	else if(order =="delete")
		Delete(root,head);
	else if(order == "drop")
		Drop(root,head);
	else if(order =="alter")
		Alter(root,head);
	else if(order =="update")
        Update(root,head);
	else if(order == "select")
		Select(root,head);
	else if(order == "grand")
		Grand(head);
	else if(order == "delgrand")
		DelGrand(head);
	else
	{
		cout<<"输入错误"<<endl<<endl;
	}
	return;
}

void WritIndex(index_list &root,attri_list head)//将在内存中新建立的表写入到索引链表中
{
	index_list tmp = new index;
	tmp->dir_form = head;
	tmp->next = NULL;
	if(!root)
		root = tmp;
	else
	{
		index_list cursor = root;
		while(cursor->next)
		{
			cursor =cursor->next;
		}
		cursor->next = tmp;
	}
}

attri_list GetIndex(index_list &root,string formName)//在索引中查找名为formName 的表 返回指向表的指针
{
	//cout<<"查找表："<<formName<<endl;
	index_list cursor = root;
	attri_list form_head = NULL;
	while(cursor)
	{
		
		string name = cursor->dir_form->name;//索引所指向的表名
		if(name == formName)
		{	//cout<<"已找到表："<<cursor->dir_form->name<<endl;
			form_head = cursor->dir_form;
			break;
		}
		cursor = cursor->next;
	}
    
	
	if(!cursor)
	{
		string formAtt = FindDic(formName);
		
		if(formAtt.empty())
		{
			cout<<formName<<"表不存在"<<endl<<endl;
		}
		else
		{
			input_list builtForm = Tear(formAtt);
		    form_head = Creat(builtForm);
		    input_list data = ReadDB(formName);
		    if(data)//表中有数据 将数据载入到内存
		       Add(form_head,data);
		    WritIndex(root,form_head);
		}
	}

	return form_head;
}

void WritDic(input_list head)//将表属性信息写入数据字典
{
	string dic;
	while(head)
	{
		string temp = head->str;
		dic.append(temp);
	    dic.append(" ");

		head = head->next;
	}
	//dic.append(head->str);
    
	//加查找如数据字典中有则重写，入无则追加
	ofstream out("dictionary.txt",ios_base::app);
	out<<dic<<endl;
	out.close();
}

attri_list Creat(input_list instruct_cur)//建立表
{
	//cout<<"进入建立名为："<<instruct_cur->str<<"的表"<<endl;
	attri_list head = new attribute;//表头结点
	
	head->name = instruct_cur->str;//表名
	head->down=NULL;
	head->next=NULL;

    attri_list rear = head;
	instruct_cur = instruct_cur->next;

    attri_list attriTmp = NULL;
	while(instruct_cur)
	{
		if(!instruct_cur->str.empty()){
		//cout<<"建立属性节点"<<endl;
		attriTmp = new attribute;
		attriTmp->down = NULL;
		attriTmp->next = NULL;


		attriTmp->name = instruct_cur->str;  //属性名称
		//cout<<"属性名称："<<attriTmp->name<<endl;
        
		instruct_cur = instruct_cur->next;
		attriTmp->type = instruct_cur->str;  //属性类型
		//cout<<"属性类型："<<attriTmp->type<<endl;
        
		instruct_cur = instruct_cur->next;
		attriTmp->length = instruct_cur->str;  //属性类型长度
		//cout<<"属性长度："<<attriTmp->length<<endl;
		
		instruct_cur = instruct_cur->next;
        rear->next = attriTmp;
		rear = attriTmp;
        }
		else
		{
			break;
		}
	}
	return head;
}

void Insert(index_list &root, input_list instruct)//添加元组
{
	
    string list_name;//存表名

    input_list instruct_cur = instruct; //定义一个指向指令链表的游标
	
	string fir_word = instruct_cur->str;//指令的第一个关键字 insert
	//cout<<instruct_cur->str<<endl;

	instruct_cur = instruct_cur->next;
	string sec_word = instruct_cur->str;//第二个关键字 into
    //cout<<instruct_cur->str<<endl;

	if(sec_word != "into")//判断指令合法
	{
		cout<<fir_word<<"  "<<sec_word<<"指令错误！"<<endl;
		return;
	}
	instruct_cur = instruct_cur->next;//第三个关键字

	list_name = instruct_cur->str;//取出插入的表名
    
	attri_list form_head = GetIndex(root,list_name);
    if(!form_head)
	{
		string list_attri =FindDic(list_name);//从数据字典中将名为list_name的表的属性取出 

		if(list_attri.empty())
		{
			cout<<"不存在名为： "<<list_name<<" 的表"<<endl;
		    return;
		}
	    //cout<<list_attri<<endl;
        input_list rebuilt_list = Tear(list_attri);//将字符串拆开成链表
	    form_head = Creat(rebuilt_list);//重新建立起名为list_name的表
	    input_list oriData = ReadDB(list_name);
		if(oriData)
		   Add(form_head,oriData);
	    WritIndex(root,form_head);
	}
	else
	{
		//cout<<"表"<<form_head->name<<"已经导入内存"<<endl;
	}
	instruct_cur = instruct_cur->next;
	if(Match(form_head,instruct_cur))
	{
		Add(form_head,instruct_cur);//将数据信息添加到表中
	    WritDB(list_name,form_head->down);
		cout<<"数据添加成功"<<endl<<endl;
	}
}

bool Add(attri_list form_head,input_list instruct)//将数据导入内存中的链表
{
	input_list ins = instruct;

	//cout<<"添加数据"<<endl;	
	while(instruct)
	{
		//cout<<instruct->str<<endl;
		if(instruct->str == "values")
		{
			instruct = instruct->next;
			continue;
		}
	    node_list line_head = new attribute_node;//新建一元组 头结点
		node_list line_cursor = line_head;
		line_head->next = NULL;
		line_head->down = NULL;

		if(form_head->down == NULL)
		{
				attri_list attri_cursor = form_head;
				attri_cursor->down = line_cursor;
				attri_cursor = attri_cursor->next;
				
				while(attri_cursor)
				{
				    node_list tmp = new attribute_node;
					if(instruct->str.empty())
						return false;
					tmp->vale.ch_type = instruct->str.c_str();
					//cout<<tmp->vale.ch_type<<" ";
					instruct = instruct->next;

					tmp->next = NULL;
					tmp->down = NULL;

					line_cursor->next = tmp;
					line_cursor = tmp;

					attri_cursor->down = tmp;
					attri_cursor = attri_cursor->next;
				}
		}
		else
		{
				node_list line = form_head->down;
				while(line->down)
				{
					line = line->down;
				}
				
				line->down = line_cursor;
				line = line->next;
				while(line)
				{
				    node_list tmp = new attribute_node;
					tmp->vale.ch_type = instruct->str.c_str();//注意改类型
					instruct = instruct->next;
					tmp->next = NULL;
					tmp->down = NULL;

					line_cursor->next = tmp;
					line->down = tmp;

					line_cursor = line_cursor->next;
					line = line->next;
				}
		}//end else	
	}//while(instruct)
	//cout<<"数据添加成功"<<endl;
    return true;
}

void WritDB(string form_name,node_list head)//向表文件中写入数据
{
	//cout<<"输出数据"<<endl;
	form_name+=".txt";
	ofstream out(form_name.c_str());
    
	int a = 0;
	string data;
	while(head)
	{
		a+=1;
		node_list cursor = head->next;
		while(cursor)
		{
			//cout<<cursor->vale.ch_type;
			out<<cursor->vale.ch_type<<" ";
		    
			cursor = cursor->next;
		}
		head = head->down;
		out<<endl;
	}
	out.close();
}

void Delete(index_list &root, input_list instruct)//删除满足条件的元组
{
	    //cout<<"进入删除函数"<<endl;
	                               //取指令第二个关键字
		input_list SecKey = instruct->next;
		if(SecKey->str != "from")
		{
			cout<<"指令 delete "<<SecKey->str<<"错误"<<endl<<endl;
			return;
		}

		input_list ThrKey = SecKey->next;//取第三个关键字 即 表名
        
		input_list FourKey = ThrKey->next;
		if(FourKey->str !="where")//取第四个关键字
		{
		    cout<<FourKey->str<<"错误"<<endl;//bug
			return;
		}
		
		string formName = ThrKey->str;
		attri_list form_head = GetIndex(root,formName);//在索引中查找表是否已经载入内存
        if(!form_head)
		{
			return;
		}
			//cout<<formName<<"表已经导入内存！"<<endl;
		input_list FivKey = FourKey->next;//指向第五个关键字 即条件属性

		attri_list attCur = form_head;
		while(attCur)
		{
			if(attCur->name == FivKey->str)
			{
				//cout<<"已找到表"<<form_head->name<<"的"<<FivKey->str<<"属性"<<endl;
				break;
			}
			attCur = attCur->next;
		}

		input_list SevKey = FivKey->next->next;//属性值
		if(!attCur)
		{
			cout<<form_head->name<<"表不存在"<<FivKey->str<<"属性"<<endl<<endl;
			return;
		}
		else
		{   
			bool tuple = false;//是否存在满足条件的元组
			node_list tmp;
			while(attCur->down->vale.ch_type == SevKey->str)
			{
				tuple = true;
				attri_list Cursor = form_head;
				tmp = form_head->down;
				while(Cursor)//将属性down指针 指向更下一层
				{
					Cursor->down = tmp->down;
					tmp->down = NULL;
					tmp = tmp->next;
					Cursor = Cursor->next;
				}
			}

			node_list line = form_head->down;//行游标
			node_list data= attCur->down;//属性行游标
			while(data->down)
			{
				if(data->down->vale.ch_type == SevKey->str)
				{
                    tuple = true;
					node_list linCur = line;
					tmp = line->down;
					while(tmp)
					{
						linCur->down = tmp->down;
					    tmp->down = NULL;
						tmp = tmp->next;
						linCur = linCur->next;
					}
				}
				else
				{
					data = data->down;
					line = line->down;
				}
			}
			if(!tuple)
			{
				cout<<form_head->name<<"表无"<<attCur->name<<"属性为："<<SevKey->str<<"的元组"<<endl;
				return;
			}
			
			if(form_head->down)
				WritDB(formName,form_head->down);
			cout<<"数据删除成功"<<endl<<endl;
		}
}

void Update(index_list &root, input_list ins)
{
	input_list insCur = ins->next;
	string sec = insCur->str;
    attri_list form_head = GetIndex(root,sec);
	if(!form_head)
	{
		cout<<sec<<"表不存在"<<endl;
		return;
	}

	insCur = insCur->next;
	string thr = insCur->str;
	if(thr != "set")
	{
		cout<<thr<<"指令错误"<<endl;
		return;
	}

	insCur = insCur->next;
	string attChaName = insCur->str;
	attri_list change_ptr = form_head;
	while(change_ptr)
	{
		if(change_ptr->name == attChaName)
			break;
		change_ptr = change_ptr->next;
	}
    if(!change_ptr)
	{
		cout<<form_head->name<<"表不存在属性"<<attChaName<<endl;
		return;
	}
    insCur = insCur->next;
	string five = insCur->str;//
	if(five != "=")
	{
		cout<<five<<"错误"<<endl;
		return;
	}
	insCur = insCur->next;
	string attChaVal = insCur->str;//第六个关键字 要改变属性的新值
	insCur = insCur->next;
	string seven = insCur->str;//where
	if(seven!="where")
	{
		cout<<seven<<"错误"<<endl;
		return;
	}

	insCur = insCur->next;
	string attCond = insCur->str;//条件属性
	insCur = insCur->next;
	string nine = insCur->str;
    if(nine != "=")
	{
		cout<<nine<<"错误"<<endl;
		return;
	}
	insCur = insCur->next;
	string attCondVal = insCur->str;//条件属性的值
	attri_list condition_ptr = form_head;//指向条件属性的指针
	while(condition_ptr)
	{
		if(condition_ptr->name == attCond)
		{
			break;
		}
		condition_ptr = condition_ptr->next;
	}
	if(!condition_ptr)
	{
		cout<<form_head->name<<"表不存在属性"<<attChaName<<endl;
		return;
	}
	node_list conDat_ptr = condition_ptr->down;
	node_list chaDat_ptr = change_ptr->down;
	while(conDat_ptr)
	{
		if(conDat_ptr->vale.ch_type == attCondVal)
	    {
			chaDat_ptr->vale.ch_type = attChaVal.c_str();
	     }
		conDat_ptr = conDat_ptr->down;
		chaDat_ptr = chaDat_ptr->down;
	}

	WritDB(sec,form_head->down);//回写到表文件中
	cout<<"数据更新成功"<<endl<<endl;
}

void Drop(index_list &root, input_list instruct)//删除表
{
	input_list sec = instruct->next;
	if(sec->str != "table")
	{
		cout<<instruct->str<<" "<<sec->str<<"指令错误"<<endl;
		return;
	}
	input_list thr = sec->next;
	string formName = FindDic(thr->str);
	if(formName.empty())
	{
		cout<<"表"<<formName<<"不存在"<<endl;
		return;
	}
	input_list dic = ReadDic();
	input_list front = dic;
	input_list cursor = dic->next;
	if(front->str == formName)
	{
		dic = dic->next;
		front->next = NULL;
		delete front;
	}
	else
	{
		while(cursor)
	    {
		    if(cursor->str == formName)
			   break;
			front = front->next;
		    cursor = cursor->next;
	    }
		front = front->next;
		cursor->next = NULL;
		delete cursor;
	}
    
    index_list dexCur = root;
	if(root)
	{
		if(dexCur->dir_form->name == thr->str)//在索引链表中查找 要删除的表 找到删除  
	    {
			//cout<<thr->str<<endl;
		    root = root->next;
		    dexCur->next = NULL;
	    }
	    else
	    {
		    index_list front = dexCur;
		    dexCur = dexCur->next;
		    while(dexCur)
		    {
			    if(dexCur->dir_form->name == thr->str)//在索引链表中查找 要删除的表 找到删除  
				{
					break;
				}
			    front =front->next;
			    dexCur =dexCur->next;
		     }
		     if(dexCur)
		     {
			     front = front->next;
			     dexCur->next = NULL;
		      }
		}//end else
	}//end if(root)
    ReWritDic(dic);
	thr->str+=".txt";
	remove(thr->str.c_str());
	cout<<"表删除成功"<<endl<<endl;
}
input_list ReadDic()//将数据字典中所有数据读出
{
	//cout<<"进入数据字典"<<endl;
	input_list head = NULL;
	input_list cursor = NULL;
	ifstream in("dictionary.txt");
	if(in)
	{
		while(!in.eof())
		{
			string tmpStr;
			getline(in,tmpStr);
			//cout<<tmpStr<<endl;
			if(tmpStr.empty()||tmpStr==" "||tmpStr == "\n")
				continue;
	    	input_list tmpNode = new input_node;
		    tmpNode->str = tmpStr;
	    	tmpNode->next = NULL;
			if(!head)
				head = tmpNode;
		    else
			    cursor->next = tmpNode;
		    cursor = tmpNode;
		}
		//cout<<"读取结束"<<endl;
	 }
	else
		head = NULL;
	in.close();
	return head;
}

void ReWritDic(input_list ins)//重写数据字典
{
	ofstream out("dictionary.txt");
	while(ins)
	{
		out<<ins->str<<" "<<endl;
		ins = ins->next;
	}
	out.close();
}

string FindDic(string name)//在数据字典中查找表名为name的属性信息
{
	//cout<<"在数据字典中查找"<<name<<endl;
	string list_name;

	ifstream in("dictionary.txt");
	while(!in.eof())
	{
		string temp;
		getline(in,temp);
		if(!temp.empty()&&temp != " "&&temp != "\n")
		{
			int i = 0;
		    while(temp[i]!=' ')
			{
			    i++;
			}
		    list_name = temp.substr(0,i);
		    if(list_name == name)
			{
				//cout<<"在数据字典中找到"<<list_name<<endl;
				in.close();
			    return temp; 
			}
		}
	}
	
	in.close();
	return "";
	
}

input_list Tear(string attri)//将字符串拆分成 input_list 链表
{
	//cout<<"拆分属性字符串"<<endl;
	input_list head = NULL;
	input_list cursor;

	int length = attri.length();
	for(int i = 0, j = 0; i < length; i++)
	{
		string temp;
		if(attri[i] == ' '|| i == '\\n')
		{
			temp = attri.substr(j,i-j);
			j=i+1;

			input_list val = new input_node;
			val->str = temp;
			//cout<<val->str<<endl;
			val->next = NULL;

			if(!head)
			{
				head = cursor = val;
			}
			else
			{
				cursor ->next = val;
				cursor = val;
			}
		}
	}
	return head;
}

input_list ReadDB(string name)//从表文件中读取数据
{
	//cout<<"开始从数据文件读取数据"<<endl;
	input_list head = NULL;
	input_list cursor = NULL;

	name+=".txt";
	ifstream in(name.c_str());
	if(in)
	{
	while(!in.eof())
	{
		string read;
		in>>read;
		if(read.empty()||read==" "||read == "\n")
			continue;
		input_list tmp = new input_node;
		
		tmp->str = read;
		tmp->next = NULL;

		if(!head)
			head = tmp;
		else
		{
			cursor->next = tmp;
		}
		cursor = tmp;
	}

	in.close();
	//cout<<"读取成功！"<<endl;
	if(head->str == " "||head->str=="\n")
		head = NULL;
	}
	else
		head = NULL;
	return head;
}

void Alter(index_list &root, input_list ins)//增删属性
{
	//cout<<"进入增删属性函数："<<endl;
	input_list sec = ins->next;
	if(sec->str != "table")
	{
		cout<<"指令"<<ins->str<<" "<<sec->str<<"错误"<<endl<<endl;
		return;
	}

	input_list thr = sec->next;//表名 
	attri_list form_head = GetIndex(root, thr->str);
	string formAtt = FindDic(thr->str);
	if(!form_head)
	{
		return;
	}

	input_list four = thr->next;//操作选择
	if(four->str == "add")
	{
		AlterAdd(form_head,four);
	}
	else if(four->str == "drop")
	{
		AlterDrop(form_head,four);
	}
	else
	{
		cout<<"指令错误"<<endl<<endl;
	}

	string newFormAtt = thr->str;//先+表名
	//cout<<newFormAtt<<endl;
	attri_list cursor = form_head->next;
	while(cursor)//将更新过属性的表的属性信息取出
	{
		newFormAtt.append(" ");
		newFormAtt.append(cursor->name);
		newFormAtt.append(" ");
		newFormAtt.append(cursor->type);
		newFormAtt.append(" ");
		newFormAtt.append(cursor->length);

		cursor = cursor->next;
	}

	input_list form = ReadDic();//从数据字典中将所有表信息读出
	input_list formCur = form;
	while(formCur)
	{
		if(formCur->str == formAtt)//找到更新属性的表
		{
			break;
		}
		formCur = formCur->next;
	}
	formCur->str = newFormAtt;//更新表属性信息

	ReWritDic(form);//将所有表写回数据字典文件

	if(form_head->down)//如果表中有数据 则将数据写回到数据文件
	   WritDB(thr->str,form_head->down);

}

void AlterAdd(attri_list form_head,input_list ins)//添加属性函数
{
	input_list insCur = ins->next;//要添加的属性名称
	attri_list attCur = form_head;
	while(attCur->next)
	{
		attCur =attCur->next;
	}
	attri_list tmp = new attribute;
	tmp->name = insCur->str;
	
	insCur = insCur->next;
	tmp->type = insCur->str;

	insCur = insCur->next;
	tmp->length = insCur->str;

	tmp->next = NULL;
	tmp->down = NULL;

	attCur->next = tmp;
	if(form_head->down)
	{
		node_list nodCur = attCur->down;
		attCur = attCur->next;
	
	    insCur = insCur->next;//属性的默认值
		
	    node_list nodtmp = new attribute_node;//属性的下一排
	    nodtmp->next = NULL;
	    nodtmp->down = NULL;
		nodtmp->vale.ch_type = insCur->str.c_str();
		/*
		if(attCur->type == "char")
	        nodtmp->vale.ch_type = insCur->str.c_str();
	    else if(attCur->type == "double")
		    nodtmp->vale.dob_type = atof(insCur->str.c_str());//将输入的字符串转换成double
	    else
		    nodtmp->vale.int_type = atoi(insCur->str.c_str());//字符串转成int
	   */

		attCur->down = nodtmp;     
	    nodCur->next = nodtmp;
   
		
		while(nodCur->down)
	   {
	    	node_list tmp = new attribute_node;
		    tmp->next = NULL;
		    tmp->down = NULL;

			tmp->vale.ch_type = insCur->str.c_str();

			/*if(attCur->type == "char")
			    tmp->vale.ch_type = insCur->str.c_str();
		    else if(attCur->type == "double")
			    tmp->vale.dob_type = atof(insCur->str.c_str());//将输入的字符串转换成double
		    else
			    tmp->vale.int_type = atoi(insCur->str.c_str());
         */
		
		    nodCur->next->down = tmp;
		    nodCur->down->next = tmp;
		    nodCur =nodCur->down;
		}//while
	}
	cout<<"属性添加成功"<<endl;
}


void AlterDrop(attri_list form_head,input_list ins)//删除属性函数
{
	input_list insCur = ins->next;//要删除的属性名称

	attri_list attCur = form_head->next;
	attri_list attFront = form_head;
	while(attCur)
	{
		if(attCur->name == insCur->str)
			break;
		attCur = attCur->next;
		attFront = attFront->next;
	}
	attFront->next = attCur->next;
	attCur->next = NULL;

	node_list nodCur = attCur->down;
	node_list nodFront = attFront->down;
	while(nodCur)
	{
		nodFront->next = nodCur->next;
		nodCur->next = NULL;

		nodCur = nodCur->down;
		nodFront = nodFront->down;
	}
    

	nodFront = attCur->down;
	attCur->down = NULL;
	delete attCur;
	while(nodFront)
	{
		nodCur = nodFront->down;
		nodFront->down = NULL;
		delete nodFront;
		nodFront = nodCur;
	}

	cout<<"属性删除成功"<<endl;
}

bool Match(attri_list form_head, input_list ins)//匹配输入的数据是否符合类型 长度要求
{
	
	input_list insCur = ins;
	while(insCur)
	{
		if(insCur->str == "values")
		{
			insCur = insCur->next;
		}
		else
		{
			cout<<"关键字错误"<<endl;
			return false;
		}
		attri_list attCur = form_head->next;
		while(attCur)
		{
			if(attCur->type == "char")
			{
				int attlenth = atoi(attCur->length.c_str());
				int datlenth = insCur->str.length();
				if(datlenth > attlenth )
				{
					cout<<insCur->str<<" 数据超出长度限制"<<endl;
					return false;
				}
			}
			else if(attCur->type == "int")
			{
				int i = 0;
				string tmp = insCur->str;
				int length = tmp.length();
				while(i < length)
				{
					if(tmp[i]<'0'||tmp[i]>'9')
					{
						cout<<tmp<<" 类型错误"<<endl;
						return false;
					}
					i++;
				}
			}
			else//判断double
			{
				int i = 0; 
				string tmp = insCur->str;
		  		bool point = false;
				while(i<tmp.length())
				{
					if(tmp[i]<'0'||tmp[i]>'9')
					{
						if(!point&&tmp[i]=='.')
							point = true;
						else
						{
							cout<<tmp<<"类型错误"<<endl;
						    return false;
						}
					}
					i++;
				}//end while(i<tmp.lenth())
			}// end else
			attCur = attCur->next;
			insCur = insCur->next;
		}//while(attCur)
	
	}//while(insCur)
	return true;
}
void Select(index_list &root,input_list ins)//选择查询函数
{
	//cout<<"void Select(index_list &root,input_list ins)//选择查询函数"<<endl<<endl;
	//调用词法分析函数
	attri_list Result = Grammer(root,ins);
	if(Result)
	  Display(Result);
	cout<<"查询结束"<<endl<<endl;
}

input_list GetKeyAtt(input_list& ins)//把需要查找的属性摘出
{
	//cout<<"input_list GetKeyAtt(input_list& ins)//把需要查找的属性摘出"<<endl<<endl;
	input_list insCur = ins;
	input_list KeyAtt = insCur;
	while(insCur->next->str!="from")//将查询的属性摘出来
	{
		insCur = insCur->next;
	}
	input_list rear = insCur;
	ins = insCur->next;
	rear->next = NULL;

	return KeyAtt;
}

attri_list Grammer(index_list &root, input_list &ins)//语法分析
{
	//cout<<"attri_list Grammer(index_list &root, input_list ins)"<<endl<<endl;
	input_list insCur = ins->next;
	input_list KeyAtt = GetKeyAtt(insCur);//要查找的属性集合

	insCur = insCur->next;//指向表名

	index_list form_head = LinkForm(root,insCur);
	//处理条件生成查询用临时表 满足所有条件
	if(!form_head)
	{
		return NULL;
	}
	attri_list query_form = NULL;
	attri_list result_form = NULL;
	
	if(!insCur)//全关系选择 或者 单关系投影
	{
		if(KeyAtt->str == "*")//全关系输出整张表
			result_form = form_head->dir_form;
		else//投影
		{
			result_form = GetResult(form_head,KeyAtt);
			//result_form = CreatResult(form_head->dir_form,KeyAtt);
		}
	}
	else//选择
	{
		insCur = insCur->next;//作为查询条件的属性
		/*if(insCur->next->str == "in")
		{
			insCur = insCur->next;//in
			insCur = insCur->next;//select
			attri_list Form = Grammer(root,insCur);////////////////////////////////多表查询
		    insCur = FormToInput(Form);
		}*/
		GetTmpForm(form_head,insCur);
		if(KeyAtt->str == "*")//选择操作
			result_form = form_head->dir_form;
		else//选择 投影
			result_form = GetResult(form_head,KeyAtt);
			//result_form = CreatResult(form_head->dir_form, KeyAtt);
	}
	return result_form;
}

attri_list GetResult(index_list form_head,input_list key)//没有在索引链表中的 即不需要的属性将被删除 得到最终的结果表
{
	index_list index_head = resIndex(form_head,key);
	attri_list attCur = form_head->dir_form;
	while(attCur->next)
	{
		index_list indexCur = index_head;
		while(indexCur)
		{
			if(attCur->next == indexCur->dir_form)
			{
				break;
			}
			indexCur = indexCur->next;
		}
		if(!indexCur)
		{
			DelAtt(attCur);
		}
		else
		{
			attCur = attCur->next;
		}
	}
	return form_head->dir_form;
}

index_list resIndex(index_list form_head,input_list key)//的到指向满足选择条件的属性的索引的链表
{
	index_list index_head = NULL;
	index_list index_rear = NULL;
	while(key)
	{
		string condName = key->str;
		string formName,attName;
		bool isCompAtt = analyCondAtt(condName,formName,attName);
		attri_list tmpAtt_ptr = NULL;
		if(isCompAtt)
		{
			tmpAtt_ptr = findAtt(form_head,formName,attName);
		}
		else
		{
			tmpAtt_ptr = findAtt(form_head,attName);
		}
		if(tmpAtt_ptr)
		{
			index_list tmpIndex = new index;
			tmpIndex->dir_form = tmpAtt_ptr;
			tmpIndex->next = NULL;
			if(!index_head)
			{
				index_head = tmpIndex;
			}
			else
			{
				index_rear->next = tmpIndex;
			}
			index_rear = tmpIndex;
		}
		key = key->next;
	}
	return index_head;
}

/*
attri_list CreatResult(attri_list query_form,input_list KeyAtt)
{
	cout<<"attri_list CreatResult(attri_list query_form,input_list KeyAtt)"<<endl<<endl;

	attri_list attCur = query_form;
	while(attCur->next)
	{
		attri_list mark = attCur->next;
		input_list keyCur = KeyAtt;
		while(keyCur)
		{
			if(keyCur->str == mark->name)
			{
				cout<<mark->name<<"属性满足"<<endl;
				break;
			}
			keyCur = keyCur->next;
		}
		if(!keyCur)
		{
			DelAtt(attCur);
		}
		else
		{
			attCur = attCur->next;
		}
	}
	return query_form;
}
*/
void DelAtt(attri_list &frontAtt)//删除不需要的属性
{
	cout<<"void DelAtt(attri_list frontAtt)"<<endl<<endl;
	cout<<"删除属性名称"<<frontAtt->next->name<<endl;
	attri_list markAtt = frontAtt->next;
	node_list frontData = frontAtt->down;
	node_list markData = markAtt->down;
    attri_list delHead = markAtt;
	frontAtt->next = markAtt->next;
	markAtt->next = NULL;
	while(frontData)
	{
		frontData->next = markData->next;
		markData->next = NULL;
		//cout<<markData->vale.ch_type<<endl;
		frontData = frontData->down;
		markData = markData->down;
	}

	//cout<<"成功删除属性"<<markAtt->name<<endl;
	
	//FreeData(delHead);
}

void FreeData(attri_list &Head)
{
	//cout<<"void FreeData(attri_list &Head)"<<endl<<endl;
	node_list Data = Head->down;
	Head->down = NULL;
	delete(Head);
	while(Data)
	{
		node_list Next = Data->down;
		Data->down = NULL;

		delete(Data);
		Data = Next;
	}
}


void GetTmpForm(index_list form_head,input_list &ins)//生成元组满足条件的临时表
{
	//cout<<"attri_list GetTmpForm(attri_list form_head,input_list &ins)"<<endl<<endl;
	input_list mark = GetMarkList(form_head,ins);
	node_list datCur = form_head->dir_form->down;//表的第一行数据
	
	while(mark)//用标记链表 来标记临时表的数据元组的头
	{
		datCur->vale.ch_type = mark->str.c_str();
		
		mark = mark->next;
		datCur = datCur->down;
	}
	delTuple(form_head->dir_form);//将头没有被标记选择的元组删除
}
input_list GetMarkList(index_list form_head,input_list &ins)//得到一次查找的最终标记链表
{
	//cout<<"input_list GetMarkList(index_list form_head,input_list &ins)"<<endl;
	attri_list CondAtt = CreatCondAtt(ins);//查找的条件属性
	input_list mark = initMarkList(form_head->dir_form);
	
	AndQuery(form_head,CondAtt,mark);
   
	ins = ins->next;//NULL 或者 and 或者 or
	
	while(ins)//将所有条件遍历完 即查完
	{	
		string logic = ins->str;
		ins = ins->next;
		if(logic == "and")
		{	
			CondAtt = CreatCondAtt(ins);
			ins = ins->next;
			AndQuery(form_head,CondAtt,mark);
		}
		else
		{
			input_list next = GetMarkList(form_head,ins);
			mergeMarkList(mark,next);
		}
	}
	return mark;
}
void mergeMarkList(input_list first,input_list second)//将or操作得到的两个标记链表合并
{
	//cout<<"void mergeMarkList(input_list first,input_list second)"<<endl;
	while(first)
	{
		if(first->str == "nomark" && second->str == "mark")
		{
			first->str = "mark";
		}
		first = first->next;
		second = second->next;
	}
}
input_list initMarkList(attri_list form)//生成初始的标记被选择的元组的链表
{
	//cout<<"input_list initMarkList(attri_list form)"<<endl;
	node_list datCur = form->down;
	input_list mark = NULL;
	input_list rear = NULL;
	while(datCur)
	{
		input_list tmp = new input_node;
		tmp->str = "mark";
		tmp->next = NULL;
		if(!mark)
		{
			mark = tmp;
		}
		else
		{
			rear->next = tmp;
		}
		rear = tmp;
		datCur = datCur->down;
	}
	return mark;
}
attri_list CreatCondAtt(input_list &ins)//将每个条件属性 的名称 操作符= > < 和值 放在一个变量内 方便操作
{
	//cout<<"attri_list CreatCondAtt(input_list &ins)"<<endl<<endl;
	attri_list CondAtt = new attribute;
	CondAtt->name = ins->str;
	ins = ins->next;
	CondAtt->type = ins->str;
	ins = ins->next;
	CondAtt->length = ins->str;
	CondAtt->next = NULL;
	CondAtt->down = NULL;

	return CondAtt;
}
void AndQuery(index_list form_head,attri_list CondAtt,input_list mark)//在临时生成的表上 进行 and 连接
{
	//cout<<"void AndQuery(index_list form_head,attri_list CondAtt)"<<endl<<endl;
	attri_list attCur = NULL;
	string formName,attName;
	bool isCondValue = analyCondAtt(CondAtt->name,formName,attName);//分析student.sno = course.sno 中的student.sno
	if(isCondValue)
	{
	    attCur = findAtt(form_head,formName,attName);//在临时表上找到 需要做and连接的属性
	}
	else
	{
		attCur = findAtt(form_head,attName);
	}

	attri_list query_form = form_head->dir_form;
	
	isCondValue = analyCondAtt(CondAtt->length,formName,attName);//分析student.sno = course.sno 中得course.sno
	attri_list sec_att = NULL;
	if(isCondValue)
	{
		sec_att = findAtt(form_head,formName,attName);//在临时表上找到 需要做and连接的属性
	}

		if(CondAtt->type == ">")
	    {
			LessThan(query_form,attCur,CondAtt->length,mark);
		}
	    else if(CondAtt->type == "<")
	    {
		    MoreThan(query_form,attCur,CondAtt->length,mark);
	    }
	    else
	    {		
			if(isCondValue)
				andEqual(query_form,attCur,sec_att,mark);//比较两个条件的值来选择元组
		    else
			   andEqual(query_form,attCur,CondAtt->length,mark);//将一个条件的值和一个输入值比较来选择元组
     	}
}


attri_list findAtt(index_list form_head, string formName, string attName)
{
	//cout<<"attri_list findAtt(index_list form_head, string formName, string attName)"<<endl<<"查找"<<formName<<" "<<attName<<endl;
	attri_list attCur = NULL;
	index_list indCur = form_head->next;
	while(indCur)
	{
		if(indCur->formName == formName)
		{
			attCur = indCur->dir_form;
			break;
		}
		indCur = indCur->next;
	}
	while(attCur)
	{
		if(attCur->name == attName)
		{
			break;
		}
		attCur = attCur->next;
	}
	return attCur;
}
attri_list findAtt(index_list form_head, string attName)
{
	attri_list attCur = form_head->dir_form->next;
	while(attCur)
	{
		if(attCur->name == attName)
		{
			break;
		}
		attCur = attCur->next;
	}
	return attCur;
}
void delTuple(attri_list query_form)//删除没有被选择的元组
{
	//cout<<"void delTuple(attri_list form_head)//删除没有被选择的元组"<<endl<<endl;
	node_list markHead = query_form->down;
	
	while(markHead)
	{
		string value = markHead->vale.ch_type;
		if(value == "nomark")
	    {   
		   cout<<markHead->vale.ch_type<<endl;
			attri_list Cursor = query_form;
			while(Cursor)
	        {
	            Cursor->down = markHead->down;
		        markHead->down = NULL;
 		        Cursor = Cursor->next;
	            markHead = markHead->next;
			}
		}
		else
		{
			break;
		}
		markHead = query_form->down;
	}
	node_list front = markHead;
	
	while(front)
	{
		markHead = front->down;
		while(markHead)
		{
			string value = markHead->vale.ch_type;
		    if(value == "nomark")
	        {
			    cout<<markHead->next->vale.ch_type<<endl;
			    node_list datCur = front;
		        while(datCur)
		        {
			        datCur->down = markHead->down;
			        markHead->down = NULL;
				    datCur = datCur->next;
			        markHead = markHead->next;
			    }
			}
			else
			{
				break;
			}
		    markHead = front->down;
		}
		front = front->down;
	}
	cout<<"删除结束"<<endl;
}

void LessThan(attri_list query_form, attri_list attCur, string value, input_list mark)//从表中删除某属性值小于等于value的元组
{
	//cout<<"void LessThan(attri_list form_head,attri_list &attCur,string value)//从表中删除某属性值小于等于value的元组"<<endl<<endl;
	node_list datCur = attCur->down;
	//node_list markHead = query_form->down;

	while(datCur)
	{
		double cond = atof(datCur->vale.ch_type);
		double key = atof(value.c_str());
		if(mark->str=="mark" && cond <= key)// 不满足该条件的值的元组
		{
			mark->str ="nomark";
		}
		mark = mark->next;
	    datCur = datCur->down;
	}
}

void MoreThan(attri_list query_form,attri_list attCur,string value,input_list mark)//从表中删除某属性值小于等于value的元组
{
	//cout<<"void delMoreThan(attri_list form_head,attri_list &attCur,string value)//从表中删除某属性值小于等于value的元组"<<endl<<endl;
	node_list datCur = attCur->down;
	//node_list markHead = query_form->down;
	while(datCur)
	{
		if(mark->str == "mark"&& datCur->vale.ch_type >= value)
		{
			mark->str = "nomark";
			//markHead->vale.ch_type = "nomark";
		}
		datCur = datCur->down;
		mark = mark->next;
		//markHead = markHead->down;
	}
}

void andEqual(attri_list query_form,attri_list attCur,string value,input_list mark)//从表中删除某属性值小于等于value的元组
{
	//cout<<"void andEqual(attri_list form_head,attri_list &attCur,string value)//从表中删除某属性值小于等于value的元组"<<endl<<endl;
	node_list datCur = attCur->down;
	//node_list markHead = query_form->down;
	while(datCur)
	{
		if(mark->str == "mark" && datCur->vale.ch_type != value)
		{
			mark->str = "nomark";
			//markHead->vale.ch_type = "nomark";
		}
		datCur = datCur->down;
		mark = mark->next;
		//markHead = markHead->down;
	}
}

void andEqual(attri_list query_form,attri_list fir_att,attri_list sec_att, input_list mark)
{
	//cout<<"void andEqual(attri_list query_form,attri_list fir_att,attri_list sec_att)"<<endl<<endl;
	node_list fir_dat = fir_att->down;
	node_list sec_dat = sec_att->down;
	//node_list markHead = query_form->down;

	while(fir_dat)
	{
		string fir_value = fir_dat->vale.ch_type;
		string sec_value = sec_dat->vale.ch_type;
		if(mark->str == "mark" &&  fir_value != sec_value)
		{
			mark->str = "nomark";
			//markHead->vale.ch_type = "nomark";
		}
		fir_dat =fir_dat->down;
		sec_dat = sec_dat->down;
		mark = mark->next;
		//markHead = markHead->down;
	}
}

bool analyCondAtt(string cond,string &formName,string &attName)//查看条件 如果包涵student.sno形式则分别取出
{
	int i = 0, j = 0;
	bool result = false;
	while(cond[i])
	{
		if(cond[i]=='.')
		{
			formName = cond.substr(0,i);
			j = i+1;
			result = true;
		}
		i++;
	}
	attName = cond.substr(j,i);
	return result;
}

void MarkUp(attri_list form_head,attri_list CondAtt,attri_list query_form)//从原始表中找出满足条件属性 的元组
{
	//cout<<"void MarkUp(attri_list form_head,attri_list CondAtt,attri_list query_form)"<<endl<<endl;
	attri_list attCur = form_head->next;
	node_list headCur = form_head->down;
	while(attCur)
	{
		if(attCur->name == CondAtt->name)
			break;
		attCur = attCur->next;
	}

	node_list dataCur = attCur->down;
		while(dataCur)
		{
			bool b = false;
			if(CondAtt->type == ">")
			{
				if(dataCur->vale.ch_type > CondAtt->length)
				{
					b = true;
				}
			}
			else if(CondAtt->type == "<")
			{	
				if(dataCur->vale.ch_type < CondAtt->length)
				{
					b = true;
				}
			}
			else
			{
				if(dataCur->vale.ch_type == CondAtt->length)//条件属性值
				{
					b = true;
				}
			}
			if(b)
			{
				CopyData(query_form,headCur);//将满足条件属性值得元组 加入到查询结果表中
			}
			dataCur = dataCur->down;
		    headCur = headCur->down;
		}
}
void CopyData(attri_list form_head,node_list data)
{
	//cout<<"void CopyData(attri_list form_head,node_list data)"<<endl<<endl;
	attri_list attCur = form_head;//表头
	
	node_list datCur = data->next;
	
	node_list newHead = new attribute_node;
	newHead->vale.ch_type = "mark";//初始化每个元组均标记为“mark”
	newHead->next = NULL;
	newHead->down = NULL;
	
	node_list newRear = newHead;

	newHead->down = attCur->down;
	attCur->down = newHead;
	attCur = attCur->next;
    
	while(datCur)
	{
		node_list tmp = new attribute_node;
		tmp->vale.ch_type = datCur->vale.ch_type;
		tmp->next = NULL;
		tmp->down = NULL;

		newRear->next = tmp;
		newRear = tmp;
		tmp->down = attCur->down;
		attCur->down = tmp;

		datCur = datCur->next;
		attCur = attCur->next;
	}
}
attri_list CopyAtt(attri_list old_form)//copy 生成表属性
{
	//cout<<"attri_list CopyAtt(attri_list old_form)//copy 生成表属性"<<endl<<endl;
	//cout<<endl;
	attri_list oldCur = old_form->next;
	
	attri_list new_form = new attribute;
	new_form->name = old_form->name;//新表头
	new_form->down = NULL;
	new_form->next = NULL;
	attri_list newCur = new_form;
	while(oldCur)
	{
		attri_list tmp = new attribute;
		tmp->name = oldCur->name;
		tmp->type = oldCur->type;
		tmp->length = oldCur->length;
		tmp->down = NULL;
		tmp->next = NULL;

		newCur->next = tmp;
		newCur = tmp;

		oldCur = oldCur->next;
	}

	return new_form;
}

bool AnalySel(input_list ins)//select指令的词法分析
{
	return true;
}

void Display(attri_list formHead)//显示特定的数据
{
	//cout<<"void Display(attri_list formHead)//显示特定的数据"<<endl<<endl;
	attri_list attCur = formHead->next;
	node_list dataHead = formHead->down;
	while(attCur)
	{
		cout<<attCur->name<<"  ";
		attCur = attCur->next;
	}
	cout<<endl;
    while(dataHead)
	{
		node_list datCur = dataHead->next;
		while(datCur)
		{
			cout<<datCur->vale.ch_type<<"  ";
			datCur = datCur->next;
		}
		cout<<endl;
		dataHead = dataHead->down;
	}
	//cout<<"输出结束"<<endl;
}

attri_list LinkData(attri_list first, attri_list second)
{
	node_list firCur = first->down;
	while(firCur)
	{
		node_list seCur = second->down;
		while(seCur)
		{
			bool b = Judge(firCur,seCur);
			if(b)
				break;
			seCur = seCur->down;
		}
		if(!seCur)
		{
			CopyData(second,firCur);
		}
		firCur = firCur->down;
	}

	return second;
}

bool Judge(node_list first, node_list second)
{
	string s1,s2;
	while(first->next)
	{
		first = first->next;
		second = second->next;
		s1.append(first->vale.ch_type);
		s2.append(second->vale.ch_type);
	}

	if(s1 == s2)
		return true;
	else
		return false;
}

input_list FormToInput(attri_list form_head)//将一个表 拆成input链表
{
	input_list ins_head = NULL;
	input_list insCur = NULL;
	attri_list attCur = form_head->next;
	string attName = attCur->name;
	string oper = "=";
	string logic = "or";
	
	node_list dataCur = attCur->down;
	while(dataCur)
	{
		input_list tmp = new input_node;
        insCur = tmp;
		tmp->str = logic;
		
		tmp->next = new input_node;
		tmp = tmp->next;
		tmp->str = attName;

		tmp->next = new input_node;
		tmp = tmp->next;
		tmp->str = oper;

		tmp->next = new input_node;
		tmp = tmp->next;
		tmp->str = dataCur->vale.ch_type;
		tmp->next = NULL;
		
		addInput(ins_head,insCur);
		dataCur = dataCur->down;
	}
    
    insCur = ins_head;
	ins_head = ins_head->next;
	insCur->next = NULL;
	delete insCur;
	return ins_head;
}

void addInput(input_list &head,input_list tmp)//将一个input结点添加到一个input_list 链表中
{
	
	if(!head)
	{
		head = tmp;
	}
	else
	{
		input_list cursor = head;
		while(cursor->next)
	    {
		    cursor = cursor->next;
	    }
	    cursor->next = tmp;
	}
}

index_list LinkForm(index_list &root, input_list &ins)//连接表
{
	index_list form_head = new index;//建一个索引节点指向一个表，可以在表连接后依然方便找到以前的表头，方便条件为student.sno类似操作
	form_head->dir_form = NULL;
	form_head->next = NULL;
	index_list form_rear = form_head;

	while(ins && ins->str != "where")//将其他表全部取出 同第一个表连接
	{
		string formName = ins->str;
        attri_list query_form = GetIndex(root,formName);
		if(!query_form)
	    {
		    return NULL;
	    }
		query_form = CopyForm(query_form);//生成初始临时表，以此为基础来和其他表连接
		index_list tmp_index = new index;
		tmp_index->formName = formName;
		tmp_index->next = NULL;
		form_rear->next = tmp_index;
		if(!form_head->dir_form)
		{   
			form_head->dir_form = query_form;
			tmp_index->dir_form = query_form->next;
		}
		else
		{
			form_head->dir_form = LinkTwoForm(form_head->dir_form,query_form,tmp_index);//将两个表连接起来
		}
		form_rear->next = tmp_index;
		form_rear = tmp_index;
		ins = ins->next;
	}

	return form_head;
}

attri_list CopyForm(attri_list old_form)//拷贝一个表
{
	attri_list new_form = CopyAtt(old_form);
	node_list secData_cur = old_form->down;//指向第二个表的数据头，全部拷贝到临时表中；
	while(secData_cur)
	{
		CopyData(new_form,secData_cur);
		secData_cur = secData_cur->down;
	}
    
	return new_form;
}

attri_list LinkTwoForm(attri_list first,attri_list second,index_list tmp_index)
{
	second = CopyForm(second);
	//attri_list fir_tmp = CopyAtt(first);//拷贝第一个表的属性
	//attri_list sec_tmp = CopyAtt(second);//拷贝第二个表的属性
    attri_list fir_att = first;
	while(fir_att->next)
	{
		fir_att = fir_att->next;
	}
	fir_att->next = second->next;//将两个表拷贝来的属性连接起来 构成新表的属性
	tmp_index->dir_form = second->next;//该表的索引指向该表
	
	node_list firData_rear = fir_att->down;//第一个表的最后一列数据
	node_list firData_head = first->down;//第一个表的第一列数据
	node_list secData_head = second->down->next;
	
	second->next = NULL;
	node_list cur = second->down;
	while(cur)
	{
		cur->next = NULL;
		cur = cur->down;
	}////////////////////////////释放second表头的一列空间

	fir_att = first;
	while(fir_att)//将属性和数据分离
	{
		fir_att->down = NULL;
		fir_att = fir_att->next;
	}
	string statue = "mark";
	while(firData_rear)//将第二个表的临时表的所有数据和第一个表连接起来 合成一个表
	{
		node_list secData_cur = secData_head;//第二个表的第一列数据
		while(secData_cur)
		{
			firData_rear->next = secData_cur;
			CopyData(first,firData_head);
			
			secData_cur = secData_cur->down;
		}
		firData_rear->next = NULL;
		
		firData_head = firData_head->down;
		firData_rear = firData_rear->down;	
	}
     
	return first;
}

void BuiltAttIndex(index_list root,input_list ins)
{
	input_list insCur = ins->next->next;
	string indexName = insCur->str;//取出索引名称
	attIndex_list head = new attIndex;
	head->key = indexName;
	head->data_ptr = NULL;
	head->next = NULL;
    attIndex_list rear = head;
    insCur = insCur->next;
	
	insCur = insCur->next;
	string formName = insCur->str;//取出表名
    attri_list form_ptr = GetIndex(root,formName);//找到表头
	
	insCur = insCur->next;
	string attName = insCur->str;//取出属性名
    attri_list att_ptr = findAtt(form_ptr,attName);//找到属性

	node_list data_ptr = att_ptr->down;
	while(data_ptr)//遍历属性的每个元组，建立起索引链表
	{
		attIndex_list temp = new attIndex;
		temp->key = data_ptr->vale.ch_type;
		temp->data_ptr = data_ptr;
		temp->next = NULL;

		rear->next = temp;
		rear = temp;

		data_ptr =data_ptr->down;
	}

}

attri_list findAtt(attri_list form,string attName)//通过表指针 找到需要找的属性位置
{
	attri_list attCur = form->next;
	while(attCur)
	{
		if(attCur->name == attName)
		{
			break;
		}
		attCur = attCur->next;
	}
	return attCur;
}

void SortIndex(attIndex_list head, string order)//对属性索引进行排序
{
	attIndex_list Cursor = head->next;
	while(Cursor)
	{
		attIndex_list tmp = Cursor;
		attIndex_list follow = Cursor->next;
		while(follow)
		{
			if(order == "asc")
			{
			    if(tmp->key > follow->key)
			    {
				    tmp = follow;
			    }
			}
			else//order = desc
			{
				if(tmp->key < follow->key)
			    {
				    tmp = follow;
			    }
			}
			follow = follow->next;
		}
		if(tmp != Cursor)
		{
			swap(tmp,Cursor);
		}
		Cursor = Cursor->next;
	}
}

void SwapIndex(attIndex_list fir, attIndex_list sec)//交换两个属性指针的值
{
	attIndex_list tmp = new attIndex;
	tmp->data_ptr = fir->data_ptr;
	tmp->key = fir->key;
	tmp->next = NULL;

	fir->data_ptr = sec->data_ptr;
	fir->key = sec->key;

	sec->data_ptr = tmp->data_ptr;
	sec->key = tmp->key;
}

//primary key s#