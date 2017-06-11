#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
using namespace std;

const int maxsize=100;//�������������������
int Goodnum=0;//���������������Ʒ��
int Adminnum=0;//������������Ĺ���Ա����
int buyernum=0;//���������������ͨ�û�����

//����Ա�ṹ�塣����������������������������������������������������
typedef struct Admin* apointer;//���ָ������
struct Admin{
	string Admin_ID;//�ʺ�
	string Admin_name;//����
	string Admin_mima;//����
	apointer next;
};
typedef apointer alklist;//���������ͣ���ͷָ������

//����Ա����ģ��
//��ʼ��������
alklist Admin_initlist(){
	apointer head;
	head=new Admin;
	head->next=NULL;
	return head;
}

//�洢����Ա��Ϣ���ļ�
void Admin_save(alklist &head){
	apointer p;
	ofstream ofile("C:\\����Ա��Ϣ.txt",ios::out);
	ofile<<"����Ա������"<<"  "<<Adminnum<<endl;//�ı���һ����ʾ���ж��ٹ���Ա
	p=head->next;
	while(p!=NULL) {
		ofile<<p->Admin_ID<<"\t"<<p->Admin_name<<"\t"<<p->Admin_mima<<endl;
		p=p->next;
	}
	cout<<"����Ա��Ϣ����ɹ�"<<endl;
	ofile.close();
}

//����Ա��¼��֤
int Admin_ender(alklist &head,string ID,string mima){
	apointer p;
	p=head;
	while(p!=NULL) {
		if(p->Admin_ID==ID&&p->Admin_mima==mima) return 1;
		else p=p->next;
	}
	cout<<"����Ա�ʺŲ�����!"<<endl;
	return 0;
}

 //ע��-����Ա
void Admin_creat(alklist &head){
	apointer s,p;
	string ID,name,mima;
	int sign=1,flat=1;
	while(sign!=0){
		flat=1;
		cout<<"���������Ա�ʺ�"<<endl;
		cin>>ID;
		p=head->next;
		while(p!=NULL){
			if(p->Admin_ID==ID) flat=0;
			p=p->next;
		}
		if(flat==0) {
			cout<<"����Ա�ʺ��Ѵ��ڣ�����������"<<endl;
			continue;
		}
		cout<<"���������Ա����"<<endl;
		cin>>mima;
		cout<<"���������Ա����"<<endl;
		cin>>name;
		s=new Admin;
		s->Admin_ID=ID;
		s->Admin_name=name;
		s->Admin_mima=mima;
		s->next=head->next;//ʹ��ͷ�巨����
		head->next=s;
		Adminnum++;//����һ������Ա��Ϣ��Adminnum�Լ�1
		Admin_save(head);
		cout<<"�Ƿ����ע�᣿<����>�밴1  <����>�밴0"<<endl;
		cin>>sign;//whileѭ���ж����������Բ���Ҫ��if
	}
}

//ɾ������Ա
void Admin_delete(alklist &head){
	apointer p,q;
	p=head;
	int sign=1,flat = 0;
	string ID;
	while(sign!=0){
	cout<<"������Ҫɾ���Ĺ���Ա�ʺţ�";
	cin>>ID;
	while(p->next!=NULL&&flat==0){
		if(p->next->Admin_ID==ID){
			q=p->next;
			p->next=q->next;
			delete q;
			Adminnum--;
			flat=1;
			cout<<"ɾ���ɹ�"<<endl;
		}
		else p=p->next;
	}
	if(flat==0) cout<<"����Ա������!"<<endl;
	Admin_save(head);
	cout<<"�Ƿ����ɾ����<����>�밴1  <����>�밴0"<<endl;
		cin>>sign;//whileѭ���ж����������Բ���Ҫ��if
	}

}

//��ȡ����Ա��Ϣ����������
alklist Admin_get(alklist &head){
	apointer s,p;//s���ڴ洢����Ա��Ϣ��p����head������
	string numname;
	string ID,name,mima;
	head->next=NULL;
	p=head;
	ifstream ifile("C:\\����Ա��Ϣ.txt",ios::in);
	if(!ifile){
		cerr<<"����Ա��Ϣ��ѯ����"<<endl;return 0;
	}
	ifile>>numname;
	ifile>>Adminnum;//���ļ�����ȡ����Ա����������forѭ��
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
//��������������������������������������������������������������������




//��ͨ�û��ṹ����������������������������������������������������
typedef struct custom* cpointer;//���ָ������
struct custom{
	string custom_ID;//�ʺ�
	string custom_name;//����
	string custom_mima;//����
	double money;//�˻����
	cpointer next;
};
typedef cpointer clklist;//���������ͣ���ͷָ������

//��ͨ�û�����ģ�顣����������
//��ʼ��������
clklist custom_initlist(){
	cpointer head;
	head=new custom;
	head->next=NULL;
	return head;
}

//�洢�û���Ϣ���ļ�
void custom_save(clklist &head){
	cpointer p;
	ofstream ofile("C:\\��ͨ�û���Ϣ.txt",ios::out);
	ofile<<"��ͨ�û�������"<<"  "<<buyernum<<endl;//�ı���һ����ʾ���ж�����ͨ�û�
	p=head->next;
	while(p!=NULL) {
		ofile<<p->custom_ID<<"\t"<<p->custom_name<<"\t"<<p->custom_mima<<"\t"<<p->money<<endl;
		p=p->next;
	}
	cout<<"�û���Ϣ����ɹ�"<<endl;
	ofile.close();

}

//�û�ע��
void custom_creat(clklist &head){
	cpointer s,p;
	string ID,name,mima;
	int sign=1,flat=1;
	while(sign!=0){
		flat=1;
		cout<<"�������û��ʺ�"<<endl;
		cin>>ID;
		p=head->next;
		while(p!=NULL){
			if(p->custom_ID==ID) flat=0;
			p=p->next;
		}
		if(flat==0) {
			cout<<"�û��ʺ��Ѵ��ڣ�����������"<<endl;
			continue;
		}
		cout<<"�������û�����"<<endl;
		cin>>mima;
		cout<<"�������û�����"<<endl;
		cin>>name;
		s=new custom;
		s->custom_ID=ID;
		s->custom_name=name;
		s->custom_mima=mima;
		s->money=0;
		s->next=head->next;//ʹ��ͷ�巨����
		head->next=s;
		buyernum++;//����һ���û���Ϣ��buyernum�Լ�1
		custom_save(head);
		cout<<"�Ƿ����ע�᣿<����>�밴1  <����>�밴0"<<endl;
		cin>>sign;//whileѭ���ж����������Բ���Ҫ��if
	}
}

//��ͨ�û���¼��֤
int custom_ender(clklist &head,string ID,string mima){
	cpointer p;
	p=head;
	while(p!=NULL) {
		if(p->custom_ID==ID&&p->custom_mima==mima) return 1;
		else p=p->next;
	}
	cout<<"�û��ʺŲ�����!"<<endl;
	return 0;
	
}

//�û���λ
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
	//if(flat==0) cout<<"�û�������!"<<endl;
}

//��ȡ��ͨ�û���Ϣ����������
clklist custom_get(clklist &buyer){
	cpointer s,p;//s���ڴ洢�û���Ϣ��p����buyer������
	string numname;
	string ID,name,mima;
	double money;
	buyer->next=NULL;
	p=buyer;
	ifstream ifile("C:\\��ͨ�û���Ϣ.txt",ios::in);
	if(!ifile){
		cerr<<"�û���Ϣ��ѯ����"<<endl;return 0;
	}
	ifile>>numname;
	ifile>>buyernum;//���ļ�����ȡ�û�����������forѭ��
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

//�޸��û�����
void custom_change(clklist &head,string ID){
	cpointer p;
	p=head;
	int sign=1;
	string mima;
	while(sign!=0){
	while(p!=NULL) {
		if(p->custom_ID==ID) {
			cout<<"�����������룺";
			cin>>p->custom_mima;
			cout<<"�����޸ĳɹ�~~"<<endl;
			break;
		}
		else p=p->next;
	}
	custom_save(head);
	cout<<"�Ƿ������ģ�飿<����>�밴1  <����>�밴0"<<endl;
		cin>>sign;//whileѭ���ж����������Բ���Ҫ��if
	}
}

//ɾ����ͨ�û�
void custom_delete(clklist &head){
	cpointer p,q;
	p=head;
	int sign=1,flat = 0;
	string ID;
	while(sign!=0){
	cout<<"������Ҫɾ�����û��ʺţ�";
	cin>>ID;
	while(p->next!=NULL&&flat==0){
		if(p->next->custom_ID==ID){
			q=p->next;
			p->next=q->next;
			delete q;
			buyernum--;
			flat=1;
			cout<<"ɾ���ɹ�"<<endl;
		}
		else p=p->next;
	}
	if(flat==0) cout<<"�û�������!"<<endl;
	custom_save(head);
	cout<<"�Ƿ����ɾ����<����>�밴1  <����>�밴0"<<endl;
		cin>>sign;//whileѭ���ж����������Բ���Ҫ��if
	}
}

//����ֵ
void custom_addmoney(clklist &head,string ID){
	cpointer p;
	int sign=1;
	p=custom_locate(head,ID);
	string acard,card1="asd500",card2="asd1000";
	while(sign!=0){
	cout<<"����������õĳ�ֵ������:";
	cin>>acard;//acard���û���õĳ�ֵ��
	if(acard!=card1&&acard!=card2) cout<<"��ֵ����Ч"<<endl;
	if(acard==card1)
	{
		p->money+=500;
		cout<<"��ֵ�ɹ���"<<endl;
		cout<<"�˻���"<<p->money<<endl;

	};
	if(acard==card2)
	{
		p->money+=1000;
		cout<<"��ֵ�ɹ���"<<endl;
		cout<<"�˻���"<<p->money<<endl;

	};	
	custom_save(head);//��ֵ�ɹ�
	cout<<"�Ƿ������ֵ��<����>�밴1  <����>�밴0"<<endl;
		cin>>sign;//whileѭ���ж����������Բ���Ҫ��if
	}
}
//����������������������������������������������������������������



//��Ʒ�ṹ��������������������������������������������������������
struct Goods{
	string Good_name;//��Ʒ����
	string Good_ID;//��Ʒ���
	double piece;//��Ʒ�۸�
	int last;//�������
};
typedef struct{
	Goods Good[maxsize];
	int n;
}sqlist;

//��Ʒ����ģ��
//��Ʒ��Ϣ��֤
//�����֤
int Good_ender1(sqlist &Goods,string ID){//�Ա���ͬ����1
	for(int i=0;i<Goodnum;i++){
		if(Goods.Good[i].Good_ID==ID) return 1;
	}
	return 0;
}

//������֤
int Good_ender2(sqlist &Goods,string name){//�Ա���ͬ����1
	for(int i=0;i<Goodnum;i++){
		if(Goods.Good[i].Good_name==name) return 1;
	}
	return 0;
}

//��λ��Ʒ�������е�λ��
//��Ŷ�λ
int Good_locate1(sqlist &Goods,string ID){
	int i=0;
	while(i<Goodnum&&Goods.Good[i].Good_ID!=ID) i++;
	if(i<Goodnum) return i;//�ɹ���λ��λ��
	else return 0;//i������Χ
}

//���ƶ�λ
int Good_locate2(sqlist &Goods,string name){
	int i=0;
	while(i<Goodnum&&Goods.Good[i].Good_name!=name) i++;
	if(i<Goodnum) return i;//�ɹ���λ��λ��
	else return 0;//i������Χ
}

//��ȡ��Ʒ��Ϣ����������
void Good_get(sqlist &Goods){
	ifstream ifile("C:\\��Ʒ��Ϣ.txt",ios::in);
	if(!ifile) {cout<<"�ļ���ʧ�ܣ�"<<endl;return;}
	string IDtitle,nametitle,piecetitle,lasttitle;//������ʾ����Ʒ���� ��Ʒ���� ���� �����������
	string ID,name,title;//title������ʾ��ű���
	double piece;
	int last,sum;//sum������ʾ��Ʒ����
	ifile>>title;//�������Ʒ���๲�С�
	ifile>>sum;//�����Ʒ����
	Goodnum=sum;
	ifile>>IDtitle>>nametitle>>piecetitle>>lasttitle;//�����ţ����ƣ����ۣ����
	for(int i=0;i<sum;i++){
		ifile>>ID>>name>>piece>>last;
		Goods.Good[i].Good_ID=ID;
		Goods.Good[i].Good_name=name;
		Goods.Good[i].piece=piece;
		Goods.Good[i].last=last;
	}
	cout<<"�ɹ���ȡ�� "<<sum<<" ����Ʒ"<<endl;
	ifile.close();
}


//��Ʒ��Ϣ����
void Good_save(sqlist &Goods){
	ofstream ofile("C:\\��Ʒ��Ϣ.txt",ios::out);
	ofile<<"��Ʒ���ࣺ"<<"\t\t"<<Goodnum<<endl;//�ı���һ����ʾ���ж�������Ʒ
	ofile<<"��Ʒ���"<<"\t\t"<<"��Ʒ����"<<"\t\t"<<"��Ʒ����"<<"\t\t"<<"��Ʒ���"<<endl;
	for(int i=0;i<Goodnum;i++) {
		ofile<<Goods.Good[i].Good_ID<<"\t\t"<<Goods.Good[i].Good_name<<"\t\t"<<Goods.Good[i].piece<<"\t\t"<<Goods.Good[i].last<<endl;
	}
	cout<<"��Ʒ��Ϣ����ɹ�"<<endl;
	ofile.close();
}

//��Ʒ¼��(����Ʒ¼��+����Ʒ���)
void Good_add(sqlist &Goods){
	string ID,name;
	double piece;
	int last,sign,flat=1;//lastΪ��Ʒ��棬sign�����ж�ѡ��
	fstream ifile("C:\\��Ʒ��Ϣ.txt",ios::in);
	for(;flat!=0;) {
		cout<<"��������Ʒ���:";
		cin>>ID;
		if(Good_ender1(Goods,ID)==0) {
			cout<<"��������Ʒ����:";
			cin>>name;
			if(Good_ender2(Goods,name)==0) {
				cout<<"��������Ʒ����:";
				cin>>piece;
				cout<<"��������Ʒ����:";
				cin>>last;
				Goods.Good[Goodnum].Good_ID=ID;
				Goods.Good[Goodnum].Good_name=name;
				Goods.Good[Goodnum].piece=piece;
				Goods.Good[Goodnum].last=last;
				Goodnum++;//�������Ϣ���Լ�1
				Good_save(Goods);//�����ͱ�������Ʒ��Ϣ.txt
				cout<<"�Ƿ����¼�룿<����>�밴1  <����>�밴0"<<endl;
				cin>>sign;
				if(sign==0) break;
			}
			else {cout<<"��Ʒ�����Ѵ��ڣ�<��������>�밴1  <����>�밴0"<<endl;
			cin>>flat;}
		}
		else {cout<<"��Ʒ����Ѵ��ڣ�<��������>�밴1  <����>�밴0"<<endl;
		cin>>flat;}
	}
}

//��Ʒ�޸�
void Good_change(sqlist &Goods){
	string ID,name;
	int sign;//sign���ڶ�λҪ�޸���Ʒ��λ��
	int a,flat=1;//a����switch
	for(;flat!=0;){
	cout<<"<����Ҫ�޸ĵ���Ʒ���>�밴1   <����Ҫ�޸ĵ���Ʒ����>�밴2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"ѡ����������������"<<endl;continue;}
	switch(a){
	case 1:
		{
		cout<<"��������Ʒ��ţ�";
		cin>>ID;
		if(Good_ender1(Goods,ID)==1) {
			sign=Good_locate1(Goods,ID);
			cout<<"��Ʒ���:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].piece<<endl;
			cout<<"��Ʒ���:"<<Goods.Good[sign].last<<endl;
			cout<<"�������޸ĺ����Ϣ��"<<endl;
			cout<<"��Ʒ���:";
			cin>>Goods.Good[sign].Good_ID;
			cout<<"��Ʒ����:";
			cin>>Goods.Good[sign].Good_name;
			cout<<"��Ʒ����:";
			cin>>Goods.Good[sign].piece;
			cout<<"��Ʒ���:";
			cin>>Goods.Good[sign].last;
			Good_save(Goods);//������Ϣ
			cout<<"�޸ĳɹ�"<<endl;
		}
		else cout<<"��Ʒ������!"<<endl;
		break;
		}
	case 2:
		{
		cout<<"��������Ʒ���ƣ�";
		cin>>name;
		if(Good_ender2(Goods,name)==1) {
			sign=Good_locate2(Goods,name);
			cout<<"��Ʒ���:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].piece<<endl;
			cout<<"��Ʒ���:"<<Goods.Good[sign].last<<endl;
			cout<<"�������޸ĺ����Ϣ��"<<endl;
			cout<<"��Ʒ���:";
			cin>>Goods.Good[sign].Good_ID;
			cout<<"��Ʒ����:";
			cin>>Goods.Good[sign].Good_name;
			cout<<"��Ʒ����:";
			cin>>Goods.Good[sign].piece;
			cout<<"��Ʒ���:";
			cin>>Goods.Good[sign].last;
			Good_save(Goods);//������Ϣ
			cout<<"�޸ĳɹ�"<<endl;
		}
		else cout<<"��Ʒ������!"<<endl;
		break;
		}
	}//switch��
	cout<<"<�����޸�>�밴1  <�˳�>�밴0"<<endl;
	cin>>flat;
	}//forѭ����
}

//��Ʒ��ѯ
void Good_inquire(sqlist &Goods){
	string ID,name;
	int a,sign,flat=1;
	for(;flat!=0;){
	cout<<"<����Ʒ��Ų�ѯ>�밴1   <����Ʒ���Ʋ�ѯ>�밴2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"ѡ����������������"<<endl;continue;}
	switch(a){
	case 1:
		{
			cout<<"��������Ʒ��ţ�";
			cin>>ID;
			if(Good_ender1(Goods,ID)==1) {
			sign=Good_locate1(Goods,ID);
			cout<<"��Ʒ���:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].piece<<endl;
			cout<<"��Ʒ���:"<<Goods.Good[sign].last<<endl;
			}
			else cout<<"��Ʒ������!"<<endl;
			break;
		}
	case 2:
		{
			cout<<"��������Ʒ���ƣ�";
			cin>>name;
			if(Good_ender2(Goods,name)==1) {
			sign=Good_locate2(Goods,name);
			cout<<"��Ʒ���:"<<Goods.Good[sign].Good_ID<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].Good_name<<endl;
			cout<<"��Ʒ����:"<<Goods.Good[sign].piece<<endl;
			cout<<"��Ʒ���:"<<Goods.Good[sign].last<<endl;
			}
			else cout<<"��Ʒ������!"<<endl;
			break;
		}
	}//switch��
	cout<<"�Ƿ������ѯ��<����>�밴1  <����>�밴0"<<endl;
	cin>>flat;
	if(flat==0) break;
	}//forѭ����
}

//��Ʒɾ��
void Good_delete(sqlist &Goods){
	int a,sign,flat=1;
	string ID,name;
	for(;flat!=0;){
	cout<<"<����Ҫɾ������Ʒ���>�밴1   <����Ҫɾ������Ʒ����>�밴2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"ѡ����������������"<<endl;continue;}
	switch(a){
	case 1:
		{
			cout<<"������Ҫɾ������Ʒ���:";
			cin>>ID;
			if(Good_ender1(Goods,ID)==1){
			sign=Good_locate1(Goods,ID);
			for(int i=sign;i<Goodnum;i++){
				Goods.Good[i]=Goods.Good[i+1];
			}
			Goodnum--;
			Good_save(Goods);
			cout<<"ɾ���ɹ���"<<endl;
			}
			else cout<<"��Ʒ������!"<<endl;
			break;
		}
	case 2:
		{
			cout<<"������Ҫɾ������Ʒ����:";
			cin>>name;
			if(Good_ender2(Goods,name)==1){
			sign=Good_locate2(Goods,name);
			for(int i=sign;i<Goodnum;i++){
				Goods.Good[i]=Goods.Good[i+1];
			}
			Goodnum--;
			Good_save(Goods);
			cout<<"ɾ���ɹ���"<<endl;
			}
			else cout<<"��Ʒ������!"<<endl;
			break;
		}
	}//switch��
	cout<<"�Ƿ����ɾ����<����>�밴1  <����>�밴0"<<endl;
	cin>>sign;
	if(sign==0) break;
	}//forѭ����
}

//��Ʒ����
void Good_range(sqlist Go){
	Goods p;
	p.piece=0;
	p.last=0;
	int a,flag=0,flat=1;
	for(;flat!=0;){
	cout<<"<����Ʒ�������>�밴1  <����Ʒ��������>�밴2  <�������������>�밴3  <�˳�>�밴0"<<endl;
	cin>>a;
	if(a!=0&&a!=1&&a!=2&&a!=3) {cout<<"ѡ����������������"<<endl;continue;}
	switch(a){
	case 1:
		{
			for(int i=0;i<Goodnum;i++){
				for(int j=Goodnum;j>=i+1;j--){
					if(Go.Good[j].Good_ID<Go.Good[j-1].Good_ID){//�Ƚϱ�Ŵ�С��С����ǰ�棬����ں���
						flag=1;
						p=Go.Good[j];
						Go.Good[j]=Go.Good[j-1];
						Go.Good[j-1]=p;
					}
				}//jfor��
				if(!flag) break;
			}//ifor��
			cout<<"��Ʒ���"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ���"<<endl;
			for(int i=1;i<=Goodnum;i++){
				cout<<Go.Good[i].Good_ID<<setw(13)<<Go.Good[i].Good_name<<setw(8)<<Go.Good[i].piece<<setw(10)<<Go.Good[i].last<<endl;			
			}
			break;
		}
	case 2:
		{
			for(int i=0;i<Goodnum;i++){
				for(int j=Goodnum;j>=i+1;j--){
					if(Go.Good[j].piece<Go.Good[j-1].piece){//�Ƚϵ��۴�С��С����ǰ�棬����ں���
						flag=1;
						p=Go.Good[j];
						Go.Good[j]=Go.Good[j-1];
						Go.Good[j-1]=p;
					}
				}//jfor��
				if(!flag) break;
			}//ifor��
			cout<<"��Ʒ���"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ���"<<endl;
			for(int i=1;i<=Goodnum;i++){
				cout<<Go.Good[i].Good_ID<<setw(13)<<Go.Good[i].Good_name<<setw(8)<<Go.Good[i].piece<<setw(10)<<Go.Good[i].last<<endl;			
			}
			break;
		}
	case 3:
		{
			for(int i=0;i<Goodnum;i++){
				for(int j=Goodnum;j>=i+1;j--){
					if(Go.Good[j].last<Go.Good[j-1].last){//�Ƚϱ�Ŵ�С��С����ǰ�棬����ں���
						flag=1;
						p=Go.Good[j];
						Go.Good[j]=Go.Good[j-1];
						Go.Good[j-1]=p;
					}
				}//jfor��
				if(!flag) break;
			}//ifor��
			cout<<"��Ʒ���"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ���"<<endl;
			for(int i=1;i<=Goodnum;i++){
				cout<<Go.Good[i].Good_ID<<setw(13)<<Go.Good[i].Good_name<<setw(8)<<Go.Good[i].piece<<setw(10)<<Go.Good[i].last<<endl;			
			}
			break;
		}//case3��
	case 0:return;
	}//switch��
	}//�����for��
}

//������Ʒ
void Good_buy(sqlist &Goods,clklist &head,string cID){//cIDΪ�û��ʺ�
	string ID,name;
	int a,shu,sign,flat=1;
	cpointer p;
	p=custom_locate(head,cID);
	for(;flat!=0;){
	cout<<"<������Ʒ��Ź���>�밴1   <������Ʒ���ƹ���>�밴2"<<endl;
	cin>>a;
	if(a!=1&&a!=2) {cout<<"������������������"<<endl;continue;}
	switch (a)
	{
	case 1:
		{
			cout<<"��������Ʒ��ţ�";
			cin>>ID;
			if(Good_ender1(Goods,ID)==1)
			{
				sign=Good_locate1(Goods,ID);
				cout<<"�����빺��������";
				cin>>shu;
				if(shu<=Goods.Good[sign].last){
					if(p->money<Goods.Good[sign].piece*shu) 
					{cout<<"���㣬���ֵ��"<<endl;
					cout<<"�Ƿ�ǰ����ֵ��<��ֵ>�밴1  <��>�밴0"<<endl;
					cin>>flat;
					if(flat==0) break;
					if(flat==1) return;}
					Goods.Good[sign].last=Goods.Good[sign].last-shu;
					cout<<"����ɹ�"<<endl;
					p->money=p->money-Goods.Good[sign].piece*shu;//�˻������٣��۷ѳɹ�
					custom_save(head);
					cout<<"�˻���"<<p->money<<endl;
					Good_save(Goods);
				}
				else cout<<"��治�㣡"<<endl;
			}
			else cout<<"�Ҳ�����Ӧ��Ʒ������ʧ��"<<endl;
			break;
		}
	case 2:
		{
			cout<<"��������Ʒ���ƣ�";
			cin>>name;
			if(Good_ender2(Goods,name)==1)
			{
				sign=Good_locate2(Goods,name);
				cout<<"�����빺��������";
				cin>>shu;
				if(shu<=Goods.Good[sign].last){
					if(p->money<Goods.Good[sign].piece*shu) 
					{cout<<"���㣬���ֵ��"<<endl;
					cout<<"�Ƿ�ǰ����ֵ��<��ֵ>�밴1  <��>�밴0"<<endl;
					cin>>flat;
					if(flat==0) break;
					if(flat==1) return;}
					Goods.Good[sign].last=Goods.Good[sign].last-shu;
					cout<<"����ɹ�"<<endl;
					p->money=p->money-Goods.Good[sign].piece*shu;//�˻������٣��۷ѳɹ�
					custom_save(head);
					cout<<"�˻���"<<p->money<<endl;
					Good_save(Goods);
				}
				else cout<<"��治�㣡"<<endl;
			}
			else cout<<"�Ҳ�����Ӧ��Ʒ������ʧ��"<<endl;
			break;
		}
	}//switch��
	cout<<"�Ƿ�������<����>�밴1  <����>�밴0"<<endl;
	cin>>flat;
	if(flat==0) break;
	}//for��
}

//�����Ʒ�����п����Ϣ
void Good_all(sqlist &Goods){
	int flat=1;
	for(;flat!=0;){
	cout<<"��Ʒ���"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ����"<<setw(10)<<"��Ʒ���"<<endl;
	for(int i=0;i<Goodnum;i++){
		cout<<Goods.Good[i].Good_ID<<setw(13)<<Goods.Good[i].Good_name<<setw(8)<<Goods.Good[i].piece<<setw(10)<<Goods.Good[i].last<<endl;			
			}
	cout<<"�Ƿ������ģ�飿<����>�밴1  <����>�밴0"<<endl;
	cin>>flat;
	if(flat==0) break;}
}
//��������������������������������������������������������������




//��������Ա����
void superman(alklist &head){
	int a=1,sign=1,choice;
	string ID,mima;
	while(sign!=0){
	cout<<"�������ʺţ�"<<endl;
	cin>>ID;
	cout<<"����������"<<endl;
	cin>>mima;
	if(ID!="asd"||mima!="123") 
	{cout<<"���������Ƿ����µ�¼��"<<endl;
	cout<<"<����>�밴1  <����>�밴0"<<endl;
	cin>>sign;
	if(sign==0) {system("cls");return;}
	else continue;
	}
	while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         ��ӭ�����𾴵ĳ�������Ա                          ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t \t \t      [1]��ӹ���Ա \t\t\t             ||\n";
	cout<<"|| \t \t \t      [2]ɾ������Ա \t\t\t             ||\n";
	cout<<"|| \t \t \t      [0]  �˳�  \t\t\t             ||\n";
	cout<<"===============================================================================\n";
	cout<<"���������ѡ��: ";
	cin >> choice ;
	if(choice!=0&&choice!=1&&choice!=2) {cout<<"������������������";continue;}
    switch ( choice )
	{
	case 1:Admin_creat(head);system("cls"); break;
	case 2:Admin_delete(head);system("cls"); break;
	case 0:return;
	}//switch
	cout<<"�Ƿ����ִ�г�������ԱȨ�ޣ�<����>�밴1  <����>�밴0"<<endl;
	cin>>a;
	if(a==0) return;
	}//���while��a
	}//�����while��sign
}

//�����߹��ܽ���
void Admin_show(alklist &head,clklist &buyer,sqlist &Goods)
{
	int a=1,choice;//a����ѭ����choice���ڹ���ѡ��
	string ID,mima;
	cout<<"���������Ա�ʺţ�";
	cin>>ID;
	cout<<"���������Ա����:";
	cin>>mima;
	apointer p;
	p=head;
	if(Admin_ender(head,ID,mima)==1) {
		while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         ��ӭ�����𾴵Ĺ�����                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t [1]��Ʒ¼�� \t [2]��Ʒ�޸� \t[3]��Ʒ��ѯ\t        ||\n";
	cout<<"|| \t [4]��Ʒɾ�� \t [5]��Ʒ���� \t[6]��Ʒ���\t        ||\n";
	cout<<"|| \t [7]ɾ����ͨ�û� \t [0]�˳� \t\t        ||\n";
	cout<<"===============================================================================\n";
	cout<<"���������ѡ��: ";
	cin >> choice ;
    switch ( choice )
	{
	case 1:Good_add(Goods);system("cls"); break;        case 2:Good_change(Goods);system("cls"); break;
	case 3:Good_inquire(Goods);system("cls"); break;    case 4:Good_delete(Goods);system("cls"); break;
	case 5:Good_range(Goods);system("cls"); break;      case 6:Good_all(Goods);system("cls"); break;
	case 7:custom_delete(buyer);system("cls"); break;      case 0:system("cls"); return;
	}//switch��
		}//while��
	}//if��
	else cout<<"����Ա�ʺŲ�����!"<<endl;
	
}

//��ͨ�û����ܽ���
void custom_showall(clklist &head,sqlist &Goods){
	int a=1,choice,sign=1;//a����ѭ����choice���ڹ���ѡ��
	string ID,mima;
	while(sign!=0){
	cout<<"�������ʺţ�"<<endl;
	cin>>ID;
	cout<<"����������"<<endl;
	cin>>mima;
	/*cpointer p;
	p=head;*/
	if(custom_ender(head,ID,mima)==1) {
		while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         ��ӭ�����𾴵��û�                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t [1]��Ʒ��ѯ \t [2]��Ʒ���� \t[3]��Ʒ���\t        ||\n";
	cout<<"|| \t [4]��Ʒ���� \t [5]�޸����� \t[6]��ֵ    [0]�˳�        ||\n";
	cout<<"===============================================================================\n";
	cout<<"���������ѡ��: ";
	cin >> choice ;
    switch ( choice )
	{
	case 1:Good_inquire(Goods);system("cls"); break;    case 2:Good_range(Goods);system("cls"); break;
	case 3:Good_all(Goods);system("cls"); break;        case 4:Good_buy(Goods,head,ID);system("cls"); break;
	case 5:custom_change(head,ID);system("cls"); break; case 6:custom_addmoney(head,ID);system("cls"); break;
	case 0:system("cls"); return;
	}//switch��
		}//while��
	}//if��
	else 
	{
	cout<<"�Ƿ��������룿<����>�밴1  <����>�밴0"<<endl;
		cin>>sign;//whileѭ���ж����������Բ���Ҫ��if
	}
	}
}

//��ͨ�û�ѡ�񣨵�¼||ע�ᣩ
void custom_show(clklist &head,sqlist &Goods)
{
	int a=1,choice;
	while(a!=0){
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         ��ӭ�����𾴵��û�                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t \t \t [1]�û���¼ \t\t\t        ||\n";
	cout<<"|| \t \t \t [2]���û�ע�� \t\t\t        ||\n";
	cout<<"|| \t \t \t [0]���� \t\t\t        ||\n";
	cout<<"===============================================================================\n";
	cout<<"��ѡ���������: ";
	cin >> choice ;
	if(choice!=0&&choice!=1&&choice!=2) {cout<<"������������������";continue;}
    switch ( choice )
	{
	case 1:custom_showall(head,Goods);system("cls"); break;
	case 2:custom_creat(head);system("cls"); break;
	case 0:return;
	}//switch
	cout<<"�Ƿ�����û�ģ�飿<����>�밴1  <����>�밴0"<<endl;
	cin>>a;
	if(a==0) break;
	}
}

//main()����������
void show()//
{
	int a=1;//����ѭ������
	Admin *Ad;//����һ������Ա
	Ad=Admin_initlist();//��ʼ�����½�һ������

	custom *buyer;//����һ����ͨ�û�
	buyer=custom_initlist();

	sqlist Goods;//����һ����Ʒ����

	int choice;
	while(a!=0){
	Admin_get(Ad);//��ȡ����Ա�ļ��е���Ϣ������Ad������
	custom_get(buyer);//��ȡ��ͨ�û��ļ��е���Ϣ������buyer������
	Good_get(Goods);//���ļ��л�ȡ��Ʒ��Ϣ
	system("cls");
	cout<<"===============================================================================\n";
	cout<<"||                         ��ӭʹ�ó��й���ϵͳ                              ||\n";
	cout<<"===============================================================================\n";
	cout<<"||                                                                           ||\n";
	cout<<"|| \t [1]��������Ա  \t[2]����Ա \t [3]�˿� \t [0]�˳�        ||\n";
	cout<<"===============================================================================\n";
	cout<<"��ѡ���������: ";
	cin >> choice ;
    switch ( choice )
	{
	case 1:superman(Ad); break;//��������Ա���ܽ���
	case 2:Admin_show(Ad,buyer,Goods); break;        
	case 3:custom_show(buyer,Goods); break;
	case 0:system("cls");return;
	default:cout<<"������������������"<<endl;system("cls");
	}
	}
}


//������
int main()
{
	show();
	return 0;
}
