#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
using namespace std;

const int maxsize=100;//设置链表数组的最多个数
int Goodnum=0;//用于设置输入的商品数
int Adminnum=0;//用于设置输入的管理员人数
int buyernum=0;//用于设置输入的普通用户人数

//管理员结构体。。。。。。。。。。。。。。。。。。。。。。。。。。。
typedef struct Admin* apointer;//结点指针类型
struct Admin{
	string Admin_ID;//帐号
	string Admin_name;//姓名
	string Admin_mima;//密码
	apointer next;
};
typedef apointer alklist;//单链表类型，即头指针类型

//管理员函数模块
//初始化，建表
alklist Admin_initlist(){
	apointer head;
	head=new Admin;
	head->next=NULL;
	return head;
}

//存储管理员信息至文件
void Admin_save(alklist &head){
	apointer p;
	ofstream ofile("C:\\管理员信息.txt",ios::out);
	ofile<<"管理员人数："<<"  "<<Adminnum<<endl;//文本第一行显示共有多少管理员
	p=head->next;
	while(p!=NULL) {
		ofile<<p->Admin_ID<<"\t"<<p->Admin_name<<"\t"<<p->Admin_mima<<endl;
		p=p->next;
	}
	cout<<"管理员信息保存成功"<<endl;
	ofile.close();
}

//管理员登录验证
int Admin_ender(alklist &head,string ID,string mima){
	apointer p;
	p=head;
	while(p!=NULL) {
		if(p->Admin_ID==ID&&p->Admin_mima==mima) return 1;
		else p=p->next;
	}
	cout<<"管理员帐号不存在!"<<endl;
	return 0;
}

 //注册-管理员
void Admin_creat(alklist &head){
	apointer s,p;
	string ID,name,mima;
	int sign=1,flat=1;
	while(sign!=0){
		flat=1;
		cout<<"请输入管理员帐号"<<endl;
		cin>>ID;
		p=head->next;
		while(p!=NULL){
			if(p->Admin_ID==ID) flat=0;
			p=p->next;
		}
		if(flat==0) {
			cout<<"管理员帐号已存在，请重新输入"<<endl;
			continue;
		}
		cout<<"请输入管理员密码"<<endl;
		cin>>mima;
		cout<<"请输入管理员姓名"<<endl;
		cin>>name;
		s=new Admin;
		s->Admin_ID=ID;
		s->Admin_name=name;
		s->Admin_mima=mima;
		s->next=head->next;//使用头插法建表
		head->next=s;
		Adminnum++;//输入一个管理员信息，Adminnum自加1
		Admin_save(head);
		cout<<"是否继续注册？<继续>请按1  <结束>请按0"<<endl;
		cin>>sign;//while循环判断条件，所以不需要用if
	}
}

//删除管理员
void Admin_delete(alklist &head){
	apointer p,q;
	p=head;
	int sign=1,flat = 0;
	string ID;
	while(sign!=0){
	cout<<"请输入要删除的管理员帐号：";
	cin>>ID;
	while(p->next!=NULL&&flat==0){
		if(p->next->Admin_ID==ID){
			q=p->next;
			p->next=q->next;
			delete q;
			Adminnum--;
			flat=1;
			cout<<"删除成功"<<endl;
		}
		else p=p->next;
	}
	if(flat==0) cout<<"管理员不存在!"<<endl;
	Admin_save(head);
	cout<<"是否继续删除？<继续>请按1  <结束>请按0"<<endl;
		cin>>sign;//while循环判断条件，所以不需要用if
	}

}

//获取管理员信息，导入链表
alklist Admin_get(alklist &head){
	apointer s,p;//s用于存储管理员信息，p用于head的连接
	string numname;
	string ID,name,mima;
	head->next=NULL;
	p=head;
	ifstream ifile("C:\\管理员信息.txt",ios::in);
	if(!ifile){
		cerr<<"管理员信息查询出错"<<endl;return 0;
	}
	ifile>>numname;
	ifile>>Adminnum;//从文件中提取管理员个数，用于for循环
	for(int i=1;i<=Adminnum;i++){
		ifile>>ID;
		ifile>>name;
		ifile>>mima;
		s=new Admin;
		s->Admin_ID=ID;
		s->Admin_name=name;
		s->Admin_mima=mima;
		s->next=p->next;
		p->next=s;
	}
	head=p;
	ifile.close();
	return head;
}
//。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。




//普通用户结构。。。。。。。。。。。。。。。。。。。。。。。。。。
typedef struct custom* cpointer;//结点指针类型
struct custom{
	string custom_ID;//帐号
	string custom_name;//姓名
	string custom_mima;//密码
	double money;//账户余额
	cpointer next;
};
typedef cpointer clklist;//单链表类型，即头指针类型

//普通用户函数模块。。。。。。
//初始化，建表
clklist custom_initlist(){
	cpointer head;
	head=new custom;
	head->next=NULL;
	return head;
}

//存储用户信息至文件
void custom_save(clklist &head){
	cpointer p;
	ofstream ofile("C:\\普通用户信息.txt",ios::out);
	ofile<<"普通用户人数："<<"  "<<buyernum<<endl;//文本第一行显示共有多少普通用户
	p=head->next;
	while(p!=NULL) {
		ofile<<p->custom_ID<<"\t"<<p->custom_name<<"\t"<<p->custom_mima<<"\t"<<p->money<<endl;
		p=p->next;
	}
	cout<<"用户信息保存成功"<<endl;
	ofile.close();

}

//用户注册
void custom_creat(clklist &head){
	cpointer s,p;
	string ID,name,mima;
	int sign=1,flat=1;
	while(sign!=0){
		flat=1;
		cout<<"请输入用户帐号"<<endl;
		cin>>ID;
		p=head->next;
		while(p!=NULL){
			if(p->custom_ID==ID) flat=0;
			p=p->next;
		}
		if(flat==0) {
			cout<<"用户帐号已存在，请重新输入"<<endl;
			continue;
		}
		cout<<"请输入用户密码"<<endl;
		cin>>mima;
		cout<<"请输入用户姓名"<<endl;
		cin>>name;
		s=new custom;
		s->custom_ID=ID;
		s->custom_name=name;
		s->custom_mima=mima;
		s->money=0;
		s->next=head->next;//使用头插法建表
		head->next=s;
		buyernum++;//输入一个用户信息，buyernum自加1
		custom_save(head);
		cout<<"是否继续注册？<继续>请按1  <结束>请按0"<<endl;
		cin>>sign;//while循环判断条件，所以不需要用if
	}
}

//普通用户登录验证
int custom_ender(clklist &head,string ID,string mima){
	cpointer p;
	p=head;
	while(p!=NULL) {
		if(p->custom_ID==ID&&p->custom_mima==mima) return 1;
		else p=p->next;
	}
	cout<<"用户帐号不存在!"<<endl;
	return 0;
	
}

//用户定位
cpointer custom_locate(clklist &head,string ID){
	cpointer p,q;
	p=head;
	int flat = 0;
	while(p->next!=NULL&&flat==0){
		if(p->next->custom_ID==ID){
			q=p->next;
			return q;
		}
		else p=p->next;
	}
	//if(flat==0) cout<<"用户不存在!"<<endl;
}

//获取普通用户信息，导入链表
clklist custom_get(clklist &buyer){
	cpointer s,p;//s用于存储用户信息，p用于buyer的连接
	string numname;
	string ID,name,mima;
	double money;
	buyer->next=NULL;
	p=buyer;
	ifstream ifile("C:\\普通用户信息.txt",ios::in);
	if(!ifile){
		cerr<<"用户信息查询出错"<<endl;return 0;
	}
	ifile>>numname;
	ifile>>buyernum;//从文件中提取用户个数，用于for循环
	for(int i=1;i<=buyernum;i++){
		ifile>>ID;
		ifile>>name;
		ifile>>mima;
		ifile>>money;
		s=new custom;
		s->custom_ID=ID;
		s->custom_name=name;
		s->custom_mima=mima;
		s->money=money;
		s->next=p->next;
		p->next=s;
	}
	buyer=p;
	ifile.close();
	return buyer;
}

//修改用户密码
void custom_change(clklist &head,string ID){
	cpointer p;
	p=head;
	int sign=1;
	string mima;
	while(sign!=0){
	while(p!=NULL) {
		if(p->custom_ID==ID) {
			cout<<"请输入新密码：";
			cin>>p->custom_mima;
			cout<<"密码修改成功~~"<<endl;
			break;
		}
		else p=p->next;
	}
	custom_save(head);
	cout<<"是否继续该模块？<继续>请按1  <结束>请按0"<<endl;
		cin>>sign;//while循环判断条件，所以不需要用if
	}
}

//删除普通用户
void custom_delete(clklist &head){
	cpointer p,q;
	p=head;
	int sign=1,flat = 0;
	string ID;
	while(sign!=0){
	cout<<"请输入要删除的用户帐号：";
	cin>>ID;
	while(p->next!=NULL&&flat==0){
		if(p->next->custom_ID==ID){
			q=p->next;
			p->next=q->next;
			delete q;
			buyernum--;
			flat=1;
			cout<<"删除成功"<<endl;
		}
		else p=p->next;
	}
	if(flat==0) cout<<"用户不存在!"<<endl;
	custom_save(head);
	cout<<"是否继续删除？<继续>请按1  <结束>请按0"<<endl;
		cin>>sign;//while循环判断条件，所以不需要用if
	}
}

//余额充值
void custom_addmoney(clklist &head,string ID){
	cpointer p;
	int sign=1;
	p=custom_locate(head,ID);
	string acard,card1="asd500",card2="asd1000";
	while(sign!=0){
	cout<<"请输入您获得的充值卡卡号:";
	cin>>acard;//acard是用户获得的充值卡
	if(acard!=card1&&acard!=card2) cout<<"充值卡无效"<<endl;
	if(acard==card1)
	{
		p->money+=500;
		cout<<"充值成功！"<<endl;
		cout<<"账户余额："<<p->money<<endl;

	};
	if(acard==card2)
	{
		p->money+=1000;
		cout<<"充值成功！"<<endl;
		cout<<"账户余额："<<p->money<<endl;

	};	
	custom_save(head);//充值成功
	cout<<"是否继续充值？<继续>请按1  <结束>请按0"<<endl;
		cin>>sign;//while循环判断条件，所以不需要用if
	}
}
//。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。



//商品结构。。。。。。。。。。。。。。。。。。。。。。。。。。。。
struct Goods{
	string Good_name;//商品名称
	string Good_ID;//商品编号
	double piece;//商品价格
	int last;//库存数量
};
typedef struct{
	Goods Good[maxsize];
	int n;
}sqlist;

//商品函数模块
//商品信息验证
//编号验证
int Good_ender1(sqlist &Goods,string ID){//对比相同返回1
	for(int i=0;i<Goodnum;i++){
		if(Goods.Good[i].Good_ID==ID) return 1;
	}
	return 0;
}

//名称验证
int Good_ender2(sqlist &Goods,string name){//对比相同返回1
	for(int i=0;i<Goodnum;i++){
		if(Goods.Good[i].Good_name==name) return 1;
	}
	return 0;
}

//定位商品在链表中的位置
//编号定位
int Good_locate1(sqlist &Goods,string ID){
	int i=0;
	while(i<Goodnum&&Goods.Good[i].Good_ID!=ID) i++;
	if(i<Goodnum) return i;//成功定位到位置
	else return 0;//i超出范围
}

//名称定位
int Good_locate2(sqlist &Goods,string name){
	int i=0;
	while(i<Goodnum&&Goods.Good[i].Good_name!=name) i++;
	if(i<Goodnum) return i;//成功定位到位置
	else return 0;//i超出范围
}

//获取商品信息，导入链表
void Good_get(sqlist &Goods){
	ifstream ifile("C:\\商品信息.txt",ios::in);
	if(!ifile) {cout<<"文件打开失败！"<<endl;return;}
	string IDtitle,nametitle,piecetitle,lasttitle;//用于显示（货品编码 货品名字 单价 存货量）标题
	string ID,name,title;//title用于显示编号标题
	double piece;
	int last,sum;//sum用于显示商品种类
	ifile>>title;//输出“商品种类共有”
	ifile>>sum;//输出商品种类
	Goodnum=sum;
	ifile>>IDtitle>>nametitle>>piecetitle>>lasttitle;//输出编号，名称，单价，库存
	for(int i=0;i<sum;i++){
		ifile>>ID>>name>>piece>>last;
		Goods.Good[i].Good_ID=ID;
		Goods.Good[i].Good_name=name;
		Goods.Good[i].piece=piece;
		Goods.Good[i].last=last;
	}
	cout<<"成功读取了 "<<sum<<" 种商品"<<endl;
	ifile.close();
}


//商品信息保存
void Good_save(sqlist &Goods){
	ofstream ofile("C:\\商品信息.txt",ios::out);
	ofile<<"商品种类："<<"\t\t"<<Goodnum<<endl;//文本第一行显示共有多少种商品
	ofile<<"商品编号"<<"\t\t"<<"商品名称"<<"\t\t"<<"商品单价"<<"\t\t"<<"商品库存"<<endl;
	for(int i=0;i<Goodnum;i++) {
		ofile<<Goods.Good[i].Good_ID<<"\t\t"<<Goods.Good[i].Good_name<<"\t\t"<<Goods.Good[i].piece<<"\t\t"<<Goods.Good[i].last<<endl;
	}
	cout<<"商品信息保存成功"<<endl;
	ofile.close();
}

//商品录入(新商品录入+旧商品添加)
void Good_add(sqlist &Goods){
	string ID,name;
	double piece;
	int last,sign,flat=1;//last为商品库存，sign用于判断选择
	fstream ifile("C:\\商品信息.txt",ios::in);
	for(;flat!=0;) {
		cout<<"请输入商品编号:";
		cin>>ID;
		if(Good_ender1(Goods,ID)==0) {
			cout<<"请输入商品名称:";
			cin>>name;
			if(Good_ender2(Goods,name)==0) {
				cout<<"请输入商品单价:";
				cin>>piece;
				cout<<"请输入商品数量:";
				cin>>last;
				Goods.Good[Goodnum].Good_ID=ID;
				Goods.Good[Goodnum].Good_name=name;
				Goods.Good[Goodnum].piece=piece;
				Goods.Good[Goodnum].last=last;
				Goodnum++;//添加完信息就自加1
				Good_save(Goods);//添加完就保存至商品信息.txt
				cout<<"是否继续录入？<继续>请按1  <结束>请按0"<<endl;
				cin>>sign;
				if(sign==0) break;
			}
			else {cout<<"商品名称已存在！<重新输入>请按1  <结束>请按0"<<endl;
			cin>>flat;}
		}
		else {cout<<"商品编号已存在！<重新输入>请按1  <结束>请按0"<<endl;
		cin>>flat;}
	}
}

//商品修改
void Good_change(sqlist &Goods){
	string ID,name;
	int sign;//sign用于定位要修改商品的位置
	int a,flat=1;//a用于switch
	for(;flat!=0;){
	cout<<"<输入要修改的商品编号>请按1   <输入要修改的商品名称>请按2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"选择有误，请重新输入"<<endl;continue;}
	switch(a){
	case 1:
		{
		cout<<"请输入商品编号：";
		cin>>ID;
		if(Good_ender1(Goods,ID)==1) {
			sign=Good_locate1(Goods,ID);
			cout<<"商品编号:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"商品名称:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"商品单价:"<<Goods.Good[sign].piece<<endl;
			cout<<"商品库存:"<<Goods.Good[sign].last<<endl;
			cout<<"请输入修改后的信息："<<endl;
			cout<<"商品编号:";
			cin>>Goods.Good[sign].Good_ID;
			cout<<"商品名称:";
			cin>>Goods.Good[sign].Good_name;
			cout<<"商品单价:";
			cin>>Goods.Good[sign].piece;
			cout<<"商品库存:";
			cin>>Goods.Good[sign].last;
			Good_save(Goods);//保存信息
			cout<<"修改成功"<<endl;
		}
		else cout<<"商品不存在!"<<endl;
		break;
		}
	case 2:
		{
		cout<<"请输入商品名称：";
		cin>>name;
		if(Good_ender2(Goods,name)==1) {
			sign=Good_locate2(Goods,name);
			cout<<"商品编号:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"商品名称:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"商品单价:"<<Goods.Good[sign].piece<<endl;
			cout<<"商品库存:"<<Goods.Good[sign].last<<endl;
			cout<<"请输入修改后的信息："<<endl;
			cout<<"商品编号:";
			cin>>Goods.Good[sign].Good_ID;
			cout<<"商品名称:";
			cin>>Goods.Good[sign].Good_name;
			cout<<"商品单价:";
			cin>>Goods.Good[sign].piece;
			cout<<"商品库存:";
			cin>>Goods.Good[sign].last;
			Good_save(Goods);//保存信息
			cout<<"修改成功"<<endl;
		}
		else cout<<"商品不存在!"<<endl;
		break;
		}
	}//switch的
	cout<<"<继续修改>请按1  <退出>请按0"<<endl;
	cin>>flat;
	}//for循环的
}

//商品查询
void Good_inquire(sqlist &Goods){
	string ID,name;
	int a,sign,flat=1;
	for(;flat!=0;){
	cout<<"<按商品编号查询>请按1   <按商品名称查询>请按2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"选择有误，请重新输入"<<endl;continue;}
	switch(a){
	case 1:
		{
			cout<<"请输入商品编号：";
			cin>>ID;
			if(Good_ender1(Goods,ID)==1) {
			sign=Good_locate1(Goods,ID);
			cout<<"商品编号:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"商品名称:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"商品单价:"<<Goods.Good[sign].piece<<endl;
			cout<<"商品库存:"<<Goods.Good[sign].last<<endl;
			}
			else cout<<"商品不存在!"<<endl;
			break;
		}
	case 2:
		{
			cout<<"请输入商品名称：";
			cin>>name;
			if(Good_ender2(Goods,name)==1) {
			sign=Good_locate2(Goods,name);
			cout<<"商品编号:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"商品名称:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"商品单价:"<<Goods.Good[sign].piece<<endl;
			cout<<"商品库存:"<<Goods.Good[sign].last<<endl;
			}
			else cout<<"商品不存在!"<<endl;
			break;
		}
	}//switch的
	cout<<"是否继续查询？<继续>请按1  <结束>请按0"<<endl;
	cin>>flat;
	if(flat==0) break;
	}//for循环的
}

//商品删除
void Good_delete(sqlist &Goods){
	int a,sign,flat=1;
	string ID,name;
	for(;flat!=0;){
	cout<<"<输入要删除的商品编号>请按1   <输入要删除的商品名称>请按2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"选择有误，请重新输入"<<endl;continue;}
	switch(a){
	case 1:
		{
			cout<<"请输入要删除的商品编号:";
			cin>>ID;
			if(Good_ender1(Goods,ID)==1){
			sign=Good_locate1(Goods,ID);
			for(int i=sign;i<Goodnum;i++){
				Goods.Good[i]=Goods.Good[i+1];
			}
			Goodnum--;
			Good_save(Goods);
			cout<<"删除成功！"<<endl;
			}
			else cout<<"商品不存在!"<<endl;
			break;
		}
	case 2:
		{
			cout<<"请输入要删除的商品名称:";
			cin>>name;
			if(Good_ender2(Goods,name)==1){
			sign=Good_locate2(Goods,name);
			for(int i=sign;i<Goodnum;i++){
				Goods.Good[i]=Goods.Good[i+1];
			}
			Goodnum--;
			Good_save(Goods);
			cout<<"删除成功！"<<endl;
			}
			else cout<<"商品不存在!"<<endl;
			break;
		}
	}//switch的
	cout<<"是否继续删除？<继续>请按1  <结束>请按0"<<endl;
	cin>>sign;
	if(sign==0) break;
	}//for循环的
}

//商品排序
void Good_range(sqlist Go){
	Goods p;
	p.piece=0;
	p.last=0;
	int a,flag=0,flat=1;
	for(;flat!=0;){
	cout<<"<按商品编号排序>请按1  <按商品单价排序>请按2  <按库存数量排序>请按3  <退出>请按0"<<endl;
	cin>>a;
	if(a!=0&&a!=1&&a!=2&&a!=3) {cout<<"选择有误，请重新输入"<<endl;continue;}
	switch(a){
	case 1:
		{
			for(int i=0;i<Goodnum;i++){
				for(int j=Goodnum;j>=i+1;j--){
					if(Go.Good[j].Good_ID<Go.Good[j-1].Good_ID){//比较编号大小，小的在前面，大的在后面
						flag=1;
						p=Go.Good[j];
						Go.Good[j]=Go.Good[j-1];
						Go.Good[j-1]=p;
					}
				}//jfor的
				if(!flag) break;
			}//ifor的
			cout<<"商品编号"<<setw(10)<<"商品名称"<<setw(10)<<"商品单价"<<setw(10)<<"商品库存"<<endl;
			for(int i=1;i<=Goodnum;i++){
				cout<<Go.Good[i].Good_ID<<setw(13)<<Go.Good[i].Good_name<<setw(8)<<Go.Good[i].piece<<setw(10)<<Go.Good[i].last<<endl;			
			}
			break;
		}
	case 2:
		{
			for(int i=0;i<Goodnum;i++){
				for(int j=Goodnum;j>=i+1;j--){
					if(Go.Good[j].piece<Go.Good[j-1].piece){//比较单价大小，小的在前面，大的在后面
						flag=1;
						p=Go.Good[j];
						Go.Good[j]=Go.Good[j-1];
						Go.Good[j-1]=p;
					}
				}//jfor的
				if(!flag) break;
			}//ifor的
			cout<<"商品编号"<<setw(10)<<"商品名称"<<setw(10)<<"商品单价"<<setw(10)<<"商品库存"<<endl;
			for(int i=1;i<=Goodnum;i++){
				cout<<Go.Good[i].Good_ID<<setw(13)<<Go.Good[i].Good_name<<setw(8)<<Go.Good[i].piece<<setw(10)<<Go.Good[i].last<<endl;			
			}
			break;
		}
	case 3:
		{
			for(int i=0;i<Goodnum;i++){
				for(int j=Goodnum;j>=i+1;j--){
					if(Go.Good[j].last<Go.Good[j-1].last){//比较编号大小，小的在前面，大的在后面
						flag=1;
						p=Go.Good[j];
						Go.Good[j]=Go.Good[j-1];
						Go.Good[j-1]=p;
					}
				}//jfor的
				if(!flag) break;
			}//ifor的
			cout<<"商品编号"<<setw(10)<<"商品名称"<<setw(10)<<"商品单价"<<setw(10)<<"商品库存"<<endl;
			for(int i=1;i<=Goodnum;i++){
				cout<<Go.Good[i].Good_ID<<setw(13)<<Go.Good[i].Good_name<<setw(8)<<Go.Good[i].piece<<setw(10)<<Go.Good[i].last<<endl;			
			}
			break;
		}//case3的
	case 0:return;
	}//switch的
	}//最外层for的
}

//购买商品
void Good_buy(sqlist &Goods,clklist &head,string cID){//cID为用户帐号
	string ID,name;
	int a,shu,sign,flat=1;
	cpointer p;
	p=custom_locate(head,cID);
	for(;flat!=0;){
	cout<<"<输入商品编号购买>请按1   <输入商品名称购买>请按2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"输入有误，请重新输入"<<endl;continue;}
	switch (a)
	{
	case 1:
		{
			cout<<"请输入商品编号：";
			cin>>ID;
			if(Good_ender1(Goods,ID)==1)
			{
				sign=Good_locate1(Goods,ID);
				cout<<"请输入购买数量：";
				cin>>shu;
				if(shu<=Goods.Good[sign].last){
					if(p->money<Goods.Good[sign].piece*shu) 
					{cout<<"余额不足，请充值！"<<endl;
					cout<<"是否前往充值？<充值>请按1  <否>请按0"<<endl;
					cin>>flat;
					if(flat==0) break;
					if(flat==1) return;}
					Goods.Good[sign].last=Goods.Good[sign].last-shu;
					cout<<"购买成功"<<endl;
					p->money=p->money-Goods.Good[sign].piece*shu;//账户余额减少，扣费成功
					custom_save(head);
					cout<<"账户余额："<<p->money<<endl;
					Good_save(Goods);
				}
				else cout<<"库存不足！"<<endl;
			}
			else cout<<"找不到相应商品，购买失败"<<endl;
			break;
		}
	case 2:
		{
			cout<<"请输入商品名称：";
			cin>>name;
			if(Good_ender2(Goods,name)==1)
			{
				sign=Good_locate2(Goods,name);
				cout<<"请输入购买数量：";
				cin>>shu;
				if(shu<=Goods.Good[sign].last){
					if(p->money<Goods.Good[sign].piece*shu) 
					{cout<<"余额不足，请充值！"<<endl;
					cout<<"是否前往充值？<充值>请按1  <否>请按0"<<endl;
					cin>>flat;
					if(flat==0) break;
					if(flat==1) return;}
					Goods.Good[sign].last=Goods.Good[sign].last-shu;
					cout<<"购买成功"<<endl;
					p->money=p->money-Goods.Good[sign].piece*shu;//账户余额减少，扣费成功
					custom_save(head);
					cout<<"账户余额："<<p->money<<endl;
					Good_save(Goods);
				}
				else cout<<"库存不足！"<<endl;
			}
			else cout<<"找不到相应商品，购买失败"<<endl;
			break;
		}
	}//switch的
	cout<<"是否继续购物？<继续>请按1  <结束>请按0"<<endl;
	cin>>flat;
	if(flat==0) break;
	}//for的
}

//输出商品的所有库存信息
void Good_all(sqlist &Goods){
	int flat=1;
	for(;flat!=0;){
	cout<<"商品编号"<<setw(10)<<"商品名称"<<setw(10)<<"商品单价"<<setw(10)<<"商品库存"<<endl;
	for(int i=0;i<Goodnum;i++){
		cout<<Goods.Good[i].Good_ID<<setw(13)<<Goods.Good[i].Good_name<<setw(8)<<Goods.Good[i].piece<<setw(10)<<Goods.Good[i].last<<endl;			
			}
	cout<<"是否继续该模块？<继续>请按1  <结束>请按0"<<endl;
	cin>>flat;
	if(flat==0) break;}
}
//。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。




//超级管理员界面
void superman(alklist &head){
	int a=1,sign=1,choice;
	string ID,mima;
	while(sign!=0){
	cout<<"请输入帐号："<<endl;
	cin>>ID;
	cout<<"请输入密码"<<endl;
	cin>>mima;
	if(ID!="asd"||mima!="123") 
	{cout<<"输入有误，是否重新登录？"<<endl;
	cout<<"<继续>请按1  <结束>请按0"<<endl;
	cin>>sign;
	if(sign==0) {system("cls");return;}
	else continue;
	}
	while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         欢迎您，尊敬的超级管理员                          ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t \t \t      [1]添加管理员 \t\t\t             ||\n";
	cout<<"|| \t \t \t      [2]删除管理员 \t\t\t             ||\n";
	cout<<"|| \t \t \t      [0]  退出  \t\t\t             ||\n";
	cout<<"===============================================================================\n";
	cout<<"请输入操作选项: ";
	cin >> choice ;
	if(choice!=0&&choice!=1&&choice!=2) {cout<<"输入有误，请重新输入";continue;}
    switch ( choice )
	{
	case 1:Admin_creat(head);system("cls"); break;
	case 2:Admin_delete(head);system("cls"); break;
	case 0:return;
	}//switch
	cout<<"是否继续执行超级管理员权限？<继续>请按1  <结束>请按0"<<endl;
	cin>>a;
	if(a==0) return;
	}//里层while的a
	}//最外层while的sign
}

//管理者功能界面
void Admin_show(alklist &head,clklist &buyer,sqlist &Goods)
{
	int a=1,choice;//a用于循环，choice用于功能选择
	string ID,mima;
	cout<<"请输入管理员帐号：";
	cin>>ID;
	cout<<"请输入管理员密码:";
	cin>>mima;
	apointer p;
	p=head;
	if(Admin_ender(head,ID,mima)==1) {
		while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         欢迎您，尊敬的管理者                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t [1]商品录入 \t [2]商品修改 \t[3]商品查询\t        ||\n";
	cout<<"|| \t [4]商品删除 \t [5]商品排序 \t[6]商品库存\t        ||\n";
	cout<<"|| \t [7]删除普通用户 \t [0]退出 \t\t        ||\n";
	cout<<"===============================================================================\n";
	cout<<"请输入操作选项: ";
	cin >> choice ;
    switch ( choice )
	{
	case 1:Good_add(Goods);system("cls"); break;        case 2:Good_change(Goods);system("cls"); break;
	case 3:Good_inquire(Goods);system("cls"); break;    case 4:Good_delete(Goods);system("cls"); break;
	case 5:Good_range(Goods);system("cls"); break;      case 6:Good_all(Goods);system("cls"); break;
	case 7:custom_delete(buyer);system("cls"); break;      case 0:system("cls"); return;
	}//switch的
		}//while的
	}//if的
	else cout<<"管理员帐号不存在!"<<endl;
	
}

//普通用户功能界面
void custom_showall(clklist &head,sqlist &Goods){
	int a=1,choice,sign=1;//a用于循环，choice用于功能选择
	string ID,mima;
	while(sign!=0){
	cout<<"请输入帐号："<<endl;
	cin>>ID;
	cout<<"请输入密码"<<endl;
	cin>>mima;
	/*cpointer p;
	p=head;*/
	if(custom_ender(head,ID,mima)==1) {
		while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         欢迎您，尊敬的用户                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t [1]商品查询 \t [2]商品排序 \t[3]商品库存\t        ||\n";
	cout<<"|| \t [4]商品购买 \t [5]修改密码 \t[6]充值    [0]退出        ||\n";
	cout<<"===============================================================================\n";
	cout<<"请输入操作选项: ";
	cin >> choice ;
    switch ( choice )
	{
	case 1:Good_inquire(Goods);system("cls"); break;    case 2:Good_range(Goods);system("cls"); break;
	case 3:Good_all(Goods);system("cls"); break;        case 4:Good_buy(Goods,head,ID);system("cls"); break;
	case 5:custom_change(head,ID);system("cls"); break; case 6:custom_addmoney(head,ID);system("cls"); break;
	case 0:system("cls"); return;
	}//switch的
		}//while的
	}//if的
	else 
	{
	cout<<"是否重新输入？<继续>请按1  <结束>请按0"<<endl;
		cin>>sign;//while循环判断条件，所以不需要用if
	}
	}
}

//普通用户选择（登录||注册）
void custom_show(clklist &head,sqlist &Goods)
{
	int a=1,choice;
	while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         欢迎您，尊敬的用户                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t \t \t [1]用户登录 \t\t\t        ||\n";
	cout<<"|| \t \t \t [2]新用户注册 \t\t\t        ||\n";
	cout<<"|| \t \t \t [0]返回 \t\t\t        ||\n";
	cout<<"===============================================================================\n";
	cout<<"请选择您的身份: ";
	cin >> choice ;
	if(choice!=0&&choice!=1&&choice!=2) {cout<<"输入有误，请重新输入";continue;}
    switch ( choice )
	{
	case 1:custom_showall(head,Goods);system("cls"); break;
	case 2:custom_creat(head);system("cls"); break;
	case 0:return;
	}//switch
	cout<<"是否继续用户模块？<继续>请按1  <结束>请按0"<<endl;
	cin>>a;
	if(a==0) break;
	}
}

//main()函数主界面
void show()//
{
	int a=1;//用于循环次数
	Admin *Ad;//定义一个管理员
	Ad=Admin_initlist();//初始化，新建一个链表

	custom *buyer;//定义一个普通用户
	buyer=custom_initlist();

	sqlist Goods;//定义一个商品链表

	int choice;
	while(a!=0){
	Admin_get(Ad);//获取管理员文件中的信息，导入Ad链表中
	custom_get(buyer);//获取普通用户文件中的信息，导入buyer链表中
	Good_get(Goods);//从文件中获取商品信息
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         欢迎使用超市管理系统                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t [1]超级管理员  \t[2]管理员 \t [3]顾客 \t [0]退出        ||\n";
	cout<<"===============================================================================\n";
	cout<<"请选择您的身份: ";
	cin >> choice ;
    switch ( choice )
	{
	case 1:superman(Ad); break;//超级管理员功能界面
	case 2:Admin_show(Ad,buyer,Goods); break;        
	case 3:custom_show(buyer,Goods); break;
	case 0:system("cls");return;
	default:cout<<"输入有误，请重新输入"<<endl;system("cls");
	}
	}
}


//主函数
int main()
{
	show();
	return 0;
}
