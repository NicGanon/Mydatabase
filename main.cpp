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
	cout<<"                             MySQLģ��"<<endl;
	cout<<endl;
	cout<<"---------------------------------------------------------------------"<<endl;
}

int userChoice()
{
	int choice;
	cout<<"��ͨ�û�ע���밴 1"<<endl;
	cout<<"��ͨ�û���½�밴 2��"<<endl;
	cout<<"����Ա��½�밴   3��"<<endl;
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
					 cout<<"�û���½�ɹ���   �������ȷ��"<<endl;
			         getchar();
					 getchar();
					 userOper(check,root);
			     }
			     else
			     {
				     cout<<"�û��������벻��ȷ��    �������ȷ��"<<endl<<endl;
					 getchar();
					 getchar();
			     }
			     break;
		    case 3:
		         b = adminLoad();
		         if(b)
		         {
					 cout<<"����Ա��½�ɹ���   �������ȷ��"<<endl;
			         getchar();
					 getchar();
		             adminOper(root);
		         }
		         else
		         {
			         cout<<"����Ա�û������������  �������ȷ��"<<endl;
					 getchar();
					 getchar();
		         }
				 break;
		    default:
		         cout<<"������� �������ȷ��"<<endl;
				 getchar();
		}
	}
}


string userLoad()
{
	system("cls");
	cout<<"---------------------------------------------"<<endl;
	cout<<"                �û���½                     "<<endl;
	cout<<"---------------------------------------------"<<endl;
	
	cout<<"�������û�����"<<endl;
	string userName;
	cin>>userName;
	cout<<"���������룺"<<endl;
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
			cout<<"�����û����޴�Ȩ�ޣ�"<<endl;
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
	cout<<"               ����Ա��½                     "<<endl;
	cout<<"---------------------------------------------"<<endl;

	cout<<"���������Ա�û�����"<<endl;
	string userName;
	cin>>userName;
	cout<<"���������Ա���룺"<<endl;
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
	cout<<"                �û�ע��                     "<<endl;
	cout<<"---------------------------------------------"<<endl;

	string userName;
    while(1)
	{
		cout<<"�������û�����"<<endl;
		
		cin>>userName;
		bool b = findUser(userName);
		if(b)
		{
			cout<<"���û����Ѵ��ڣ�"<<endl;
			continue;
		}

	cout<<"����������(���Ȳ�С��6λ)��"<<endl;
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
		cout<<"���볤�ȱ������6λ��"<<endl<<endl;
		continue;
	}
	cout<<"���ٴ��������룺"<<endl;
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
		cout<<"�����������벻һ�£�"<<endl<<endl;
		continue;
	}
	ofstream out("password.dat",ios_base::app);
	out<<userName<<"\t"<<password<<endl;
	out.close();
	break;
	}
	cout<<"ע��ɹ���  �������ȷ��"<<endl<<endl;
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
	cout<<"��"<<userName<<"����Ȩ�޳ɹ���"<<endl;
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
	cout<<"��"<<userName<<"�ջ�Ȩ�޳ɹ�"<<endl;
}

void Read(input_list &head)//��ȡָ��
{
	input_list cursor = NULL;
	input_list rear;
	cout<<"������ָ�"<<endl;

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
			//cout<<"ָ����ȷ"<<endl;
			input_list formname = head->next->next;

			string form_attri = FindDic(formname->str);
			if(!form_attri.empty())//�������ֵ��в�����Ϊlist_name�ı��Ƿ��Ѿ�����
			{
				cout<<formname->str<<"���Ѿ�����"<<endl;
				return;
			}
			//cout<<"׼��������Ϊ��"<<form->str<<"�ı�"<<endl;
			attri_list form = Creat(formname);
			WritDic(formname);//д�������ֵ�
			WritIndex(root,form);
			cout<<"����ɹ�"<<endl<<endl;
		}
		else if(head->next->str == "index")
		{
			BuiltAttIndex(root,head);
		}
		else
		{
			cout<<order<<" "<<head->next->str<<"ָ�����"<<endl;
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
		cout<<"�������"<<endl<<endl;
	}
	return;
}

void WritIndex(index_list &root,attri_list head)//�����ڴ����½����ı�д�뵽����������
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

attri_list GetIndex(index_list &root,string formName)//�������в�����ΪformName �ı� ����ָ����ָ��
{
	//cout<<"���ұ�"<<formName<<endl;
	index_list cursor = root;
	attri_list form_head = NULL;
	while(cursor)
	{
		
		string name = cursor->dir_form->name;//������ָ��ı���
		if(name == formName)
		{	//cout<<"���ҵ���"<<cursor->dir_form->name<<endl;
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
			cout<<formName<<"������"<<endl<<endl;
		}
		else
		{
			input_list builtForm = Tear(formAtt);
		    form_head = Creat(builtForm);
		    input_list data = ReadDB(formName);
		    if(data)//���������� ���������뵽�ڴ�
		       Add(form_head,data);
		    WritIndex(root,form_head);
		}
	}

	return form_head;
}

void WritDic(input_list head)//����������Ϣд�������ֵ�
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
    
	//�Ӳ����������ֵ���������д��������׷��
	ofstream out("dictionary.txt",ios_base::app);
	out<<dic<<endl;
	out.close();
}

attri_list Creat(input_list instruct_cur)//������
{
	//cout<<"���뽨����Ϊ��"<<instruct_cur->str<<"�ı�"<<endl;
	attri_list head = new attribute;//��ͷ���
	
	head->name = instruct_cur->str;//����
	head->down=NULL;
	head->next=NULL;

    attri_list rear = head;
	instruct_cur = instruct_cur->next;

    attri_list attriTmp = NULL;
	while(instruct_cur)
	{
		if(!instruct_cur->str.empty()){
		//cout<<"�������Խڵ�"<<endl;
		attriTmp = new attribute;
		attriTmp->down = NULL;
		attriTmp->next = NULL;


		attriTmp->name = instruct_cur->str;  //��������
		//cout<<"�������ƣ�"<<attriTmp->name<<endl;
        
		instruct_cur = instruct_cur->next;
		attriTmp->type = instruct_cur->str;  //��������
		//cout<<"�������ͣ�"<<attriTmp->type<<endl;
        
		instruct_cur = instruct_cur->next;
		attriTmp->length = instruct_cur->str;  //�������ͳ���
		//cout<<"���Գ��ȣ�"<<attriTmp->length<<endl;
		
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

void Insert(index_list &root, input_list instruct)//���Ԫ��
{
	
    string list_name;//�����

    input_list instruct_cur = instruct; //����һ��ָ��ָ��������α�
	
	string fir_word = instruct_cur->str;//ָ��ĵ�һ���ؼ��� insert
	//cout<<instruct_cur->str<<endl;

	instruct_cur = instruct_cur->next;
	string sec_word = instruct_cur->str;//�ڶ����ؼ��� into
    //cout<<instruct_cur->str<<endl;

	if(sec_word != "into")//�ж�ָ��Ϸ�
	{
		cout<<fir_word<<"  "<<sec_word<<"ָ�����"<<endl;
		return;
	}
	instruct_cur = instruct_cur->next;//�������ؼ���

	list_name = instruct_cur->str;//ȡ������ı���
    
	attri_list form_head = GetIndex(root,list_name);
    if(!form_head)
	{
		string list_attri =FindDic(list_name);//�������ֵ��н���Ϊlist_name�ı������ȡ�� 

		if(list_attri.empty())
		{
			cout<<"��������Ϊ�� "<<list_name<<" �ı�"<<endl;
		    return;
		}
	    //cout<<list_attri<<endl;
        input_list rebuilt_list = Tear(list_attri);//���ַ����𿪳�����
	    form_head = Creat(rebuilt_list);//���½�������Ϊlist_name�ı�
	    input_list oriData = ReadDB(list_name);
		if(oriData)
		   Add(form_head,oriData);
	    WritIndex(root,form_head);
	}
	else
	{
		//cout<<"��"<<form_head->name<<"�Ѿ������ڴ�"<<endl;
	}
	instruct_cur = instruct_cur->next;
	if(Match(form_head,instruct_cur))
	{
		Add(form_head,instruct_cur);//��������Ϣ��ӵ�����
	    WritDB(list_name,form_head->down);
		cout<<"������ӳɹ�"<<endl<<endl;
	}
}

bool Add(attri_list form_head,input_list instruct)//�����ݵ����ڴ��е�����
{
	input_list ins = instruct;

	//cout<<"�������"<<endl;	
	while(instruct)
	{
		//cout<<instruct->str<<endl;
		if(instruct->str == "values")
		{
			instruct = instruct->next;
			continue;
		}
	    node_list line_head = new attribute_node;//�½�һԪ�� ͷ���
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
					tmp->vale.ch_type = instruct->str.c_str();//ע�������
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
	//cout<<"������ӳɹ�"<<endl;
    return true;
}

void WritDB(string form_name,node_list head)//����ļ���д������
{
	//cout<<"�������"<<endl;
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

void Delete(index_list &root, input_list instruct)//ɾ������������Ԫ��
{
	    //cout<<"����ɾ������"<<endl;
	                               //ȡָ��ڶ����ؼ���
		input_list SecKey = instruct->next;
		if(SecKey->str != "from")
		{
			cout<<"ָ�� delete "<<SecKey->str<<"����"<<endl<<endl;
			return;
		}

		input_list ThrKey = SecKey->next;//ȡ�������ؼ��� �� ����
        
		input_list FourKey = ThrKey->next;
		if(FourKey->str !="where")//ȡ���ĸ��ؼ���
		{
		    cout<<FourKey->str<<"����"<<endl;//bug
			return;
		}
		
		string formName = ThrKey->str;
		attri_list form_head = GetIndex(root,formName);//�������в��ұ��Ƿ��Ѿ������ڴ�
        if(!form_head)
		{
			return;
		}
			//cout<<formName<<"���Ѿ������ڴ棡"<<endl;
		input_list FivKey = FourKey->next;//ָ�������ؼ��� ����������

		attri_list attCur = form_head;
		while(attCur)
		{
			if(attCur->name == FivKey->str)
			{
				//cout<<"���ҵ���"<<form_head->name<<"��"<<FivKey->str<<"����"<<endl;
				break;
			}
			attCur = attCur->next;
		}

		input_list SevKey = FivKey->next->next;//����ֵ
		if(!attCur)
		{
			cout<<form_head->name<<"������"<<FivKey->str<<"����"<<endl<<endl;
			return;
		}
		else
		{   
			bool tuple = false;//�Ƿ��������������Ԫ��
			node_list tmp;
			while(attCur->down->vale.ch_type == SevKey->str)
			{
				tuple = true;
				attri_list Cursor = form_head;
				tmp = form_head->down;
				while(Cursor)//������downָ�� ָ�����һ��
				{
					Cursor->down = tmp->down;
					tmp->down = NULL;
					tmp = tmp->next;
					Cursor = Cursor->next;
				}
			}

			node_list line = form_head->down;//���α�
			node_list data= attCur->down;//�������α�
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
				cout<<form_head->name<<"����"<<attCur->name<<"����Ϊ��"<<SevKey->str<<"��Ԫ��"<<endl;
				return;
			}
			
			if(form_head->down)
				WritDB(formName,form_head->down);
			cout<<"����ɾ���ɹ�"<<endl<<endl;
		}
}

void Update(index_list &root, input_list ins)
{
	input_list insCur = ins->next;
	string sec = insCur->str;
    attri_list form_head = GetIndex(root,sec);
	if(!form_head)
	{
		cout<<sec<<"������"<<endl;
		return;
	}

	insCur = insCur->next;
	string thr = insCur->str;
	if(thr != "set")
	{
		cout<<thr<<"ָ�����"<<endl;
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
		cout<<form_head->name<<"����������"<<attChaName<<endl;
		return;
	}
    insCur = insCur->next;
	string five = insCur->str;//
	if(five != "=")
	{
		cout<<five<<"����"<<endl;
		return;
	}
	insCur = insCur->next;
	string attChaVal = insCur->str;//�������ؼ��� Ҫ�ı����Ե���ֵ
	insCur = insCur->next;
	string seven = insCur->str;//where
	if(seven!="where")
	{
		cout<<seven<<"����"<<endl;
		return;
	}

	insCur = insCur->next;
	string attCond = insCur->str;//��������
	insCur = insCur->next;
	string nine = insCur->str;
    if(nine != "=")
	{
		cout<<nine<<"����"<<endl;
		return;
	}
	insCur = insCur->next;
	string attCondVal = insCur->str;//�������Ե�ֵ
	attri_list condition_ptr = form_head;//ָ���������Ե�ָ��
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
		cout<<form_head->name<<"����������"<<attChaName<<endl;
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

	WritDB(sec,form_head->down);//��д�����ļ���
	cout<<"���ݸ��³ɹ�"<<endl<<endl;
}

void Drop(index_list &root, input_list instruct)//ɾ����
{
	input_list sec = instruct->next;
	if(sec->str != "table")
	{
		cout<<instruct->str<<" "<<sec->str<<"ָ�����"<<endl;
		return;
	}
	input_list thr = sec->next;
	string formName = FindDic(thr->str);
	if(formName.empty())
	{
		cout<<"��"<<formName<<"������"<<endl;
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
		if(dexCur->dir_form->name == thr->str)//�����������в��� Ҫɾ���ı� �ҵ�ɾ��  
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
			    if(dexCur->dir_form->name == thr->str)//�����������в��� Ҫɾ���ı� �ҵ�ɾ��  
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
	cout<<"��ɾ���ɹ�"<<endl<<endl;
}
input_list ReadDic()//�������ֵ����������ݶ���
{
	//cout<<"���������ֵ�"<<endl;
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
		//cout<<"��ȡ����"<<endl;
	 }
	else
		head = NULL;
	in.close();
	return head;
}

void ReWritDic(input_list ins)//��д�����ֵ�
{
	ofstream out("dictionary.txt");
	while(ins)
	{
		out<<ins->str<<" "<<endl;
		ins = ins->next;
	}
	out.close();
}

string FindDic(string name)//�������ֵ��в��ұ���Ϊname��������Ϣ
{
	//cout<<"�������ֵ��в���"<<name<<endl;
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
				//cout<<"�������ֵ����ҵ�"<<list_name<<endl;
				in.close();
			    return temp; 
			}
		}
	}
	
	in.close();
	return "";
	
}

input_list Tear(string attri)//���ַ�����ֳ� input_list ����
{
	//cout<<"��������ַ���"<<endl;
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

input_list ReadDB(string name)//�ӱ��ļ��ж�ȡ����
{
	//cout<<"��ʼ�������ļ���ȡ����"<<endl;
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
	//cout<<"��ȡ�ɹ���"<<endl;
	if(head->str == " "||head->str=="\n")
		head = NULL;
	}
	else
		head = NULL;
	return head;
}

void Alter(index_list &root, input_list ins)//��ɾ����
{
	//cout<<"������ɾ���Ժ�����"<<endl;
	input_list sec = ins->next;
	if(sec->str != "table")
	{
		cout<<"ָ��"<<ins->str<<" "<<sec->str<<"����"<<endl<<endl;
		return;
	}

	input_list thr = sec->next;//���� 
	attri_list form_head = GetIndex(root, thr->str);
	string formAtt = FindDic(thr->str);
	if(!form_head)
	{
		return;
	}

	input_list four = thr->next;//����ѡ��
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
		cout<<"ָ�����"<<endl<<endl;
	}

	string newFormAtt = thr->str;//��+����
	//cout<<newFormAtt<<endl;
	attri_list cursor = form_head->next;
	while(cursor)//�����¹����Եı��������Ϣȡ��
	{
		newFormAtt.append(" ");
		newFormAtt.append(cursor->name);
		newFormAtt.append(" ");
		newFormAtt.append(cursor->type);
		newFormAtt.append(" ");
		newFormAtt.append(cursor->length);

		cursor = cursor->next;
	}

	input_list form = ReadDic();//�������ֵ��н����б���Ϣ����
	input_list formCur = form;
	while(formCur)
	{
		if(formCur->str == formAtt)//�ҵ��������Եı�
		{
			break;
		}
		formCur = formCur->next;
	}
	formCur->str = newFormAtt;//���±�������Ϣ

	ReWritDic(form);//�����б�д�������ֵ��ļ�

	if(form_head->down)//������������� ������д�ص������ļ�
	   WritDB(thr->str,form_head->down);

}

void AlterAdd(attri_list form_head,input_list ins)//������Ժ���
{
	input_list insCur = ins->next;//Ҫ��ӵ���������
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
	
	    insCur = insCur->next;//���Ե�Ĭ��ֵ
		
	    node_list nodtmp = new attribute_node;//���Ե���һ��
	    nodtmp->next = NULL;
	    nodtmp->down = NULL;
		nodtmp->vale.ch_type = insCur->str.c_str();
		/*
		if(attCur->type == "char")
	        nodtmp->vale.ch_type = insCur->str.c_str();
	    else if(attCur->type == "double")
		    nodtmp->vale.dob_type = atof(insCur->str.c_str());//��������ַ���ת����double
	    else
		    nodtmp->vale.int_type = atoi(insCur->str.c_str());//�ַ���ת��int
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
			    tmp->vale.dob_type = atof(insCur->str.c_str());//��������ַ���ת����double
		    else
			    tmp->vale.int_type = atoi(insCur->str.c_str());
         */
		
		    nodCur->next->down = tmp;
		    nodCur->down->next = tmp;
		    nodCur =nodCur->down;
		}//while
	}
	cout<<"������ӳɹ�"<<endl;
}


void AlterDrop(attri_list form_head,input_list ins)//ɾ�����Ժ���
{
	input_list insCur = ins->next;//Ҫɾ������������

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

	cout<<"����ɾ���ɹ�"<<endl;
}

bool Match(attri_list form_head, input_list ins)//ƥ������������Ƿ�������� ����Ҫ��
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
			cout<<"�ؼ��ִ���"<<endl;
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
					cout<<insCur->str<<" ���ݳ�����������"<<endl;
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
						cout<<tmp<<" ���ʹ���"<<endl;
						return false;
					}
					i++;
				}
			}
			else//�ж�double
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
							cout<<tmp<<"���ʹ���"<<endl;
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
void Select(index_list &root,input_list ins)//ѡ���ѯ����
{
	//cout<<"void Select(index_list &root,input_list ins)//ѡ���ѯ����"<<endl<<endl;
	//���ôʷ���������
	attri_list Result = Grammer(root,ins);
	if(Result)
	  Display(Result);
	cout<<"��ѯ����"<<endl<<endl;
}

input_list GetKeyAtt(input_list& ins)//����Ҫ���ҵ�����ժ��
{
	//cout<<"input_list GetKeyAtt(input_list& ins)//����Ҫ���ҵ�����ժ��"<<endl<<endl;
	input_list insCur = ins;
	input_list KeyAtt = insCur;
	while(insCur->next->str!="from")//����ѯ������ժ����
	{
		insCur = insCur->next;
	}
	input_list rear = insCur;
	ins = insCur->next;
	rear->next = NULL;

	return KeyAtt;
}

attri_list Grammer(index_list &root, input_list &ins)//�﷨����
{
	//cout<<"attri_list Grammer(index_list &root, input_list ins)"<<endl<<endl;
	input_list insCur = ins->next;
	input_list KeyAtt = GetKeyAtt(insCur);//Ҫ���ҵ����Լ���

	insCur = insCur->next;//ָ�����

	index_list form_head = LinkForm(root,insCur);
	//�����������ɲ�ѯ����ʱ�� ������������
	if(!form_head)
	{
		return NULL;
	}
	attri_list query_form = NULL;
	attri_list result_form = NULL;
	
	if(!insCur)//ȫ��ϵѡ�� ���� ����ϵͶӰ
	{
		if(KeyAtt->str == "*")//ȫ��ϵ������ű�
			result_form = form_head->dir_form;
		else//ͶӰ
		{
			result_form = GetResult(form_head,KeyAtt);
			//result_form = CreatResult(form_head->dir_form,KeyAtt);
		}
	}
	else//ѡ��
	{
		insCur = insCur->next;//��Ϊ��ѯ����������
		/*if(insCur->next->str == "in")
		{
			insCur = insCur->next;//in
			insCur = insCur->next;//select
			attri_list Form = Grammer(root,insCur);////////////////////////////////����ѯ
		    insCur = FormToInput(Form);
		}*/
		GetTmpForm(form_head,insCur);
		if(KeyAtt->str == "*")//ѡ�����
			result_form = form_head->dir_form;
		else//ѡ�� ͶӰ
			result_form = GetResult(form_head,KeyAtt);
			//result_form = CreatResult(form_head->dir_form, KeyAtt);
	}
	return result_form;
}

attri_list GetResult(index_list form_head,input_list key)//û�������������е� ������Ҫ�����Խ���ɾ�� �õ����յĽ����
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

index_list resIndex(index_list form_head,input_list key)//�ĵ�ָ������ѡ�����������Ե�����������
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
				cout<<mark->name<<"��������"<<endl;
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
void DelAtt(attri_list &frontAtt)//ɾ������Ҫ������
{
	cout<<"void DelAtt(attri_list frontAtt)"<<endl<<endl;
	cout<<"ɾ����������"<<frontAtt->next->name<<endl;
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

	//cout<<"�ɹ�ɾ������"<<markAtt->name<<endl;
	
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


void GetTmpForm(index_list form_head,input_list &ins)//����Ԫ��������������ʱ��
{
	//cout<<"attri_list GetTmpForm(attri_list form_head,input_list &ins)"<<endl<<endl;
	input_list mark = GetMarkList(form_head,ins);
	node_list datCur = form_head->dir_form->down;//��ĵ�һ������
	
	while(mark)//�ñ������ �������ʱ�������Ԫ���ͷ
	{
		datCur->vale.ch_type = mark->str.c_str();
		
		mark = mark->next;
		datCur = datCur->down;
	}
	delTuple(form_head->dir_form);//��ͷû�б����ѡ���Ԫ��ɾ��
}
input_list GetMarkList(index_list form_head,input_list &ins)//�õ�һ�β��ҵ����ձ������
{
	//cout<<"input_list GetMarkList(index_list form_head,input_list &ins)"<<endl;
	attri_list CondAtt = CreatCondAtt(ins);//���ҵ���������
	input_list mark = initMarkList(form_head->dir_form);
	
	AndQuery(form_head,CondAtt,mark);
   
	ins = ins->next;//NULL ���� and ���� or
	
	while(ins)//���������������� ������
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
void mergeMarkList(input_list first,input_list second)//��or�����õ��������������ϲ�
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
input_list initMarkList(attri_list form)//���ɳ�ʼ�ı�Ǳ�ѡ���Ԫ�������
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
attri_list CreatCondAtt(input_list &ins)//��ÿ���������� ������ ������= > < ��ֵ ����һ�������� �������
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
void AndQuery(index_list form_head,attri_list CondAtt,input_list mark)//����ʱ���ɵı��� ���� and ����
{
	//cout<<"void AndQuery(index_list form_head,attri_list CondAtt)"<<endl<<endl;
	attri_list attCur = NULL;
	string formName,attName;
	bool isCondValue = analyCondAtt(CondAtt->name,formName,attName);//����student.sno = course.sno �е�student.sno
	if(isCondValue)
	{
	    attCur = findAtt(form_head,formName,attName);//����ʱ�����ҵ� ��Ҫ��and���ӵ�����
	}
	else
	{
		attCur = findAtt(form_head,attName);
	}

	attri_list query_form = form_head->dir_form;
	
	isCondValue = analyCondAtt(CondAtt->length,formName,attName);//����student.sno = course.sno �е�course.sno
	attri_list sec_att = NULL;
	if(isCondValue)
	{
		sec_att = findAtt(form_head,formName,attName);//����ʱ�����ҵ� ��Ҫ��and���ӵ�����
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
				andEqual(query_form,attCur,sec_att,mark);//�Ƚ�����������ֵ��ѡ��Ԫ��
		    else
			   andEqual(query_form,attCur,CondAtt->length,mark);//��һ��������ֵ��һ������ֵ�Ƚ���ѡ��Ԫ��
     	}
}


attri_list findAtt(index_list form_head, string formName, string attName)
{
	//cout<<"attri_list findAtt(index_list form_head, string formName, string attName)"<<endl<<"����"<<formName<<" "<<attName<<endl;
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
void delTuple(attri_list query_form)//ɾ��û�б�ѡ���Ԫ��
{
	//cout<<"void delTuple(attri_list form_head)//ɾ��û�б�ѡ���Ԫ��"<<endl<<endl;
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
	cout<<"ɾ������"<<endl;
}

void LessThan(attri_list query_form, attri_list attCur, string value, input_list mark)//�ӱ���ɾ��ĳ����ֵС�ڵ���value��Ԫ��
{
	//cout<<"void LessThan(attri_list form_head,attri_list &attCur,string value)//�ӱ���ɾ��ĳ����ֵС�ڵ���value��Ԫ��"<<endl<<endl;
	node_list datCur = attCur->down;
	//node_list markHead = query_form->down;

	while(datCur)
	{
		double cond = atof(datCur->vale.ch_type);
		double key = atof(value.c_str());
		if(mark->str=="mark" && cond <= key)// �������������ֵ��Ԫ��
		{
			mark->str ="nomark";
		}
		mark = mark->next;
	    datCur = datCur->down;
	}
}

void MoreThan(attri_list query_form,attri_list attCur,string value,input_list mark)//�ӱ���ɾ��ĳ����ֵС�ڵ���value��Ԫ��
{
	//cout<<"void delMoreThan(attri_list form_head,attri_list &attCur,string value)//�ӱ���ɾ��ĳ����ֵС�ڵ���value��Ԫ��"<<endl<<endl;
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

void andEqual(attri_list query_form,attri_list attCur,string value,input_list mark)//�ӱ���ɾ��ĳ����ֵС�ڵ���value��Ԫ��
{
	//cout<<"void andEqual(attri_list form_head,attri_list &attCur,string value)//�ӱ���ɾ��ĳ����ֵС�ڵ���value��Ԫ��"<<endl<<endl;
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

bool analyCondAtt(string cond,string &formName,string &attName)//�鿴���� �������student.sno��ʽ��ֱ�ȡ��
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

void MarkUp(attri_list form_head,attri_list CondAtt,attri_list query_form)//��ԭʼ�����ҳ������������� ��Ԫ��
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
				if(dataCur->vale.ch_type == CondAtt->length)//��������ֵ
				{
					b = true;
				}
			}
			if(b)
			{
				CopyData(query_form,headCur);//��������������ֵ��Ԫ�� ���뵽��ѯ�������
			}
			dataCur = dataCur->down;
		    headCur = headCur->down;
		}
}
void CopyData(attri_list form_head,node_list data)
{
	//cout<<"void CopyData(attri_list form_head,node_list data)"<<endl<<endl;
	attri_list attCur = form_head;//��ͷ
	
	node_list datCur = data->next;
	
	node_list newHead = new attribute_node;
	newHead->vale.ch_type = "mark";//��ʼ��ÿ��Ԫ������Ϊ��mark��
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
attri_list CopyAtt(attri_list old_form)//copy ���ɱ�����
{
	//cout<<"attri_list CopyAtt(attri_list old_form)//copy ���ɱ�����"<<endl<<endl;
	//cout<<endl;
	attri_list oldCur = old_form->next;
	
	attri_list new_form = new attribute;
	new_form->name = old_form->name;//�±�ͷ
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

bool AnalySel(input_list ins)//selectָ��Ĵʷ�����
{
	return true;
}

void Display(attri_list formHead)//��ʾ�ض�������
{
	//cout<<"void Display(attri_list formHead)//��ʾ�ض�������"<<endl<<endl;
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
	//cout<<"�������"<<endl;
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

input_list FormToInput(attri_list form_head)//��һ���� ���input����
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

void addInput(input_list &head,input_list tmp)//��һ��input�����ӵ�һ��input_list ������
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

index_list LinkForm(index_list &root, input_list &ins)//���ӱ�
{
	index_list form_head = new index;//��һ�������ڵ�ָ��һ���������ڱ����Ӻ���Ȼ�����ҵ���ǰ�ı�ͷ����������Ϊstudent.sno���Ʋ���
	form_head->dir_form = NULL;
	form_head->next = NULL;
	index_list form_rear = form_head;

	while(ins && ins->str != "where")//��������ȫ��ȡ�� ͬ��һ��������
	{
		string formName = ins->str;
        attri_list query_form = GetIndex(root,formName);
		if(!query_form)
	    {
		    return NULL;
	    }
		query_form = CopyForm(query_form);//���ɳ�ʼ��ʱ���Դ�Ϊ������������������
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
			form_head->dir_form = LinkTwoForm(form_head->dir_form,query_form,tmp_index);//����������������
		}
		form_rear->next = tmp_index;
		form_rear = tmp_index;
		ins = ins->next;
	}

	return form_head;
}

attri_list CopyForm(attri_list old_form)//����һ����
{
	attri_list new_form = CopyAtt(old_form);
	node_list secData_cur = old_form->down;//ָ��ڶ����������ͷ��ȫ����������ʱ���У�
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
	//attri_list fir_tmp = CopyAtt(first);//������һ���������
	//attri_list sec_tmp = CopyAtt(second);//�����ڶ����������
    attri_list fir_att = first;
	while(fir_att->next)
	{
		fir_att = fir_att->next;
	}
	fir_att->next = second->next;//�������������������������� �����±������
	tmp_index->dir_form = second->next;//�ñ������ָ��ñ�
	
	node_list firData_rear = fir_att->down;//��һ��������һ������
	node_list firData_head = first->down;//��һ����ĵ�һ������
	node_list secData_head = second->down->next;
	
	second->next = NULL;
	node_list cur = second->down;
	while(cur)
	{
		cur->next = NULL;
		cur = cur->down;
	}////////////////////////////�ͷ�second��ͷ��һ�пռ�

	fir_att = first;
	while(fir_att)//�����Ժ����ݷ���
	{
		fir_att->down = NULL;
		fir_att = fir_att->next;
	}
	string statue = "mark";
	while(firData_rear)//���ڶ��������ʱ����������ݺ͵�һ������������ �ϳ�һ����
	{
		node_list secData_cur = secData_head;//�ڶ�����ĵ�һ������
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
	string indexName = insCur->str;//ȡ����������
	attIndex_list head = new attIndex;
	head->key = indexName;
	head->data_ptr = NULL;
	head->next = NULL;
    attIndex_list rear = head;
    insCur = insCur->next;
	
	insCur = insCur->next;
	string formName = insCur->str;//ȡ������
    attri_list form_ptr = GetIndex(root,formName);//�ҵ���ͷ
	
	insCur = insCur->next;
	string attName = insCur->str;//ȡ��������
    attri_list att_ptr = findAtt(form_ptr,attName);//�ҵ�����

	node_list data_ptr = att_ptr->down;
	while(data_ptr)//�������Ե�ÿ��Ԫ�飬��������������
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

attri_list findAtt(attri_list form,string attName)//ͨ����ָ�� �ҵ���Ҫ�ҵ�����λ��
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

void SortIndex(attIndex_list head, string order)//������������������
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

void SwapIndex(attIndex_list fir, attIndex_list sec)//������������ָ���ֵ
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