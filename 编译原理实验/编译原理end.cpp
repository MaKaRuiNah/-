#include<bits/stdc++.h>
using namespace std;

const int max_word = 505;
//�ؼ��� 
const char keyWord[13][20] = {"main","if","else","do","while","for","switch",
"case","int","double","float","long","void"};

//���ʱ� 
struct Word{
	char value[20];//����ֵ 
	int type;//��������
	int line;//�к� 
}w[max_word]; 

//��Ԫʽ
struct si_Yuan{
	string op;//�����
	string s1;
	string s2;
	string res;//��� 
}sy[105];
//�ļ��� 
FILE *fin,*fout;
int line = 1;
char token[12];//��ŵ��� 
int flag = 0;//�ж��Ƿ��ȡ�ַ� 
int flag1 = 0,flag2;//flag1�ж��Ƿ����Ѿ�����miss����; 
int e = 0;//������� 
int sy_num = 0;//��Ԫʽ�ĸ���
string op,s1,ss1,s2,res,res1,res2,op2,op1; 
int op_num = 0,op_num1 = 0;//������ĸ���
int sy_id;//��Ԫʽ����� 

string var[300];//�Ѿ������ı��� 
int var_num = 0;//���������ĸ��� 

int sent_id;//�ж�if,while��� 
string equ[300];//= 
int a,b,c; 
int equ_num = 1; //=���� 
int cnt = 0,token_num = 0;//��ǰ�ַ� 
int row = 1;//��ǰ���� 
char ch;
char ch1; 

int word_num = 0;//���ʵ��ܸ��� 
int word_cnt = 0;
string temp;
char str_int[20];
stack<string>word_stack;//���� 
stack<string>op_stack;
//���� 
void S();
void P();//(){�ֳ���} 
void P1();//�ֳ��� 
void A();//����˵������
void B();//��䲿��
void B1();
int C();//����˵��
void D();//��ʶ����
void D1();
void E();//��ʶ��
void F();//��ĸ 
void G();//���� 
void H();//��� 
void I();//��ֵ��� 
void J();//������� 
void K();//ѭ����� 
int L();//��ϵ����� 
void M();//���ʽ 
void M1();
void N();//�� 
void N1();
int O();//�ӷ������ 
int Q();//�˷������ 
void R();//���� 
void S();//�޷������� 
void T();//�������� 
void W();//������� 
void X();//���� 
void Y();//���1 
void Z();//����
 
//������Ԫʽ 
void siYuan(string op,string s1,string s2,string res)
{	
	sy[sy_num].op =op;
	sy[sy_num].s1=s1;
	sy[sy_num].s2=s2;
	sy[sy_num].res=res;
	sy_num++;
}

void printFour()//�����Ԫʽ 
{
	ofstream out("sy.txt");
    int i;
    for(i=0;i<sy_num;i++)
   	{
   		cout<<i<<":\t("<<sy[i].op<<",\t"<<sy[i].s1<<",\t"<<sy[i].s2<<",\t"<<sy[i].res<<")"<<endl;
   		out<<i<<":\t("<<sy[i].op<<",\t"<<sy[i].s1<<",\t"<<sy[i].s2<<",\t"<<sy[i].res<<")"<<endl;
    }
}
void error(string err)//������λ�������� 
{
        cout<<"��"<<w[word_cnt].line<<"�г���!\t";
		cout<<err<<"\n";
		e++;
}

//�������Ƿ�����
void is_say(string a)
{
	int i;
    for(i=1;i<=var_num;i++)
    {
    	if(a.compare(var[i])==0)
		{
			break;
		}
	}
	if(i>var_num)  
	{
		cout<<"�� "<<w[word_cnt].line<<" �г���\t";
		cout<<w[word_cnt].value<<" û�б����� !"<<endl;
		e++;
	}
}

void init_token(){
	int i;
	for(i = 0;i < 12;i++){
		token[i] = NULL;
	}
}

int judge_token(){
	init_token();
	if(flag == 0){
		ch = getc(fin);
	}
	flag = 1;
	while(ch == ' ' || ch == '\t' || ch == '\n'){
		if(ch == '\n'){
			row++;
		}
		ch=getc(fin);
	}
	token_num = 0;
	if((ch>='a' && ch <= 'z') || (ch >= 'A' &&ch <= 'Z')){
		//����Ϊ��ʶ�����߱����� 
		while((ch>='a' && ch <= 'z') || (ch >= 'A' &&ch <= 'Z') || (ch >= '0' && ch <= '9')){
			token[token_num++] = ch;
			ch = getc(fin);
		}
		token[token_num++] = '\0';
		for(int i = 0;i <13;i++){
			if(strcmp(token,keyWord[i]) == 0){
				//3Ϊ�ؼ��� 
				return 3;
			}
		}
		//2Ϊ��ʶ�� 
		return 2;
	}
	//������ 
	else if(ch >= '0' && ch <= '9'){
		while((ch >= '0'&& ch <= '9') || ch == '.'){
			token[token_num++] = ch;
			ch = getc(fin);
		}
		return 1;
	}
	else{
		token[token_num++] = ch;
		switch(ch){
			case '(': ch = getc(fin); return 16;
			case ')': ch = getc(fin); return 17;
			case '{': ch = getc(fin); return 33;
			case '}': ch = getc(fin); return 34;
			case '+':
				ch = getc(fin);
				if(ch == '+'){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 29;
				}
				else{
					return 18;
				}
			case '-':
				ch = getc(fin);
				if(ch == '-'){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 30;
				}
				else{
					return 19;
				}
			case '*':
				ch = getc(fin);
				if(ch == '/'){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 32;
				}
				else{
					return 20;
				}
			case '/':
				ch = getc(fin);
				if(ch == '*'){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 31;
				}
				else{ 
					return 21;
				}
			//����Ҫ���±��� 
			case '=':
				ch = getc(fin);
				if(ch == '='){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 23;
				}
				else{
					return 22;
				}
			case '>':
				ch = getc(fin);
				if(ch == '='){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 24;
				}
				else{
					return 23;
				}
			case '<':
				ch = getc(fin);
				if(ch == '='){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 26;
				}
				else{
					return 25;
				}
			case ';': ch = getc(fin); return 27;
			case '"': ch = getc(fin); return 28;
			case '!':
				ch = getc(fin);
				if(ch == '='){
					token[token_num++] = ch;
					ch = getc(fin); 
					return 37;
				}
				else{
					return 36;
				}
			case '#': ch = getc(fin); return -2;
			case ',': ch = getc(fin); return 35;
			case EOF: return -1;
			default: ch = getc(fin); return -10;
		}
	}
}

void getWord(){
	int temp;
	while(1){
		temp = judge_token();
		if(temp==-1){
			break;
		}
		switch(temp){
			case -10:
				//cout<<"�� "<<row<<" �г��ִ���."<<endl;
				error("word has a mistake");
				w[word_num].type = -1;
				strcat(w[word_num].value," ");
				word_num++;
				break;
			case -1:
				return;
			default:
				w[word_num].type  = temp;
				w[word_num].line = row;
				strcpy(w[word_num].value,token);
				word_num++;
				//cout<<"<"<<temp<<","<<token<<">"<<endl;
				break;
		}
	}
}
//���� 
void S(){
	if(strcmp("main",w[word_cnt].value)){
		error("miss main");
		word_cnt--;
	}
	word_cnt++;
	if(strcmp("(",w[word_cnt].value)){
		error("miss (");
		word_cnt--;
	}
	word_cnt++;
	if(strcmp(")",w[word_cnt].value)){
		error("miss )");
		word_cnt--;
	}
	word_cnt++;
	if(strcmp("{",w[word_cnt].value)){
		error("miss {");
		word_cnt--;
	}
	word_cnt++;
	P();
	if(strcmp("}",w[word_cnt].value)){
		error("miss }");
		word_cnt--;
	}
	op = "#";
	s1 = "";
	s2 = "";
	res = "";
	siYuan(op,s1,s2,res);
	cout<<"There are "<<e<<" mistakes in total."<<endl;
}
//�ֳ��� 
void P(){
	A();//����˵������
	if(strcmp(";",w[word_cnt].value)){
		error("miss ;");
		word_cnt--;
	}
	word_cnt++;
	B();//��䲿�� 
}
//����˵������ 
void A(){
	if(C()){
		var[++var_num] = w[word_cnt].value;
		D();
	}
	else{
		D();
	}
}
//����˵�� 
int C(){
	if(strcmp(w[word_cnt].value,"int")){
		error("miss int");
		return 0;
	}
	word_cnt++;
	return 1;
}
//��ʶ����
void D(){
	if(w[word_cnt].type != 2){
		error("denoter has a error");
	}
	word_cnt++;
	D1();
}
//�ӱ�ʶ���� 
void D1(){
	if(strcmp(w[word_cnt].value,";") == 0){
		return;
	}
	if(strcmp(w[word_cnt].value,",")){
		error("miss ,");
		word_cnt--;
	}
	word_cnt++;
	var[++var_num] = w[word_cnt].value;
	if(w[word_cnt].type!=2){
		error("denoter has a error");
	}
	word_cnt++;
	D1();
}
//��䲿�� 
void B(){
	H();
	B1();
}
//����䲿�� 
void B1(){
	if(strcmp(w[word_cnt].value,";") == 0){
		word_cnt++;
		H();
		B1();
	}
	else if(strcmp(w[word_cnt].value,"}") == 0){
		return;
	}
	else{
		error("miss ;");
	}
}
//��� 
void H(){
	cout<<"H()"<<endl;
	cout<<w[word_cnt].value<<endl;
	if(w[word_cnt].type == 2){
		op_num = 0;
		is_say(w[word_cnt].value);
		word_stack.push(w[word_cnt].value);
		word_cnt++;
		I();
	}
	else if(strcmp(w[word_cnt].value,"if") == 0){
		op_num = 0;
		J();
	}
	else if(strcmp(w[word_cnt].value,"while") == 0){
		op_num = 0;
		a = sy_num;
		K();
		op = "go";
		s1 = "";
		s2 = "";
		stringstream sss;//int ת string 
		sss<<a;
		sss>>res;
		siYuan(op,s1,s2,res);
		//�޸�while��ת�����
		stringstream sss2;
		sss2<<sy_num;
		sss2>>sy[sent_id].res;
	}
	else{
		error("extra fuhao"); 
	}
}

//��ֵ���
void I(){
	if(strcmp(w[word_cnt].value,"=") == 0){
		word_cnt++;
		//word_stack.push(w[word_cnt].value); 
		M();
		if(e > 0){
			return;
		}
		if(op_stack.size() > 0){
			op = op_stack.top();
			op_stack.pop();
			s2 = word_stack.top();
			word_stack.pop();
			s1 = word_stack.top();
			word_stack.pop();
			res = word_stack.top();
			word_stack.pop();
			siYuan(op,s1,s2,res);
		}
		else{
			s1 = word_stack.top();
			word_stack.pop();
			res = word_stack.top();
			word_stack.pop();
			siYuan("=",s1,"",res);
		}
		
	}
	else{
		error("miss = ");
		word_cnt--; 
	}
} 
//if��� 
void J(){
	cout<<"J()"<<endl;
	if(strcmp(w[word_cnt].value,"if")){
		error("miss if");
		word_cnt--;		
	}
	word_cnt++;
	if(strcmp(w[word_cnt].value,"(")){
		error("miss (");
		word_cnt--;
	}
	word_cnt++; 
	//word_stack.push(w[word_cnt].value);
	X();//���� 
	sent_id = sy_num;
	if(op_stack.size() > 0 && e == 0){
		op = op_stack.top();
		op_stack.pop();
		s2 = word_stack.top();
		word_stack.pop();
		s1 = word_stack.top();
		word_stack.pop();
		siYuan(op,s1,s2,res);
	}
	if(strcmp(w[word_cnt].value,")")){
		error("miss )");
		word_cnt--;
	}
	word_cnt++;
	//��Ԫʽ��Ϊ��
	op = "";
	s1 = "";
	s2 = "";
	res = "";
	Y();//���1
	
	stringstream ss;
	ss<<sy_num+1;
	ss>>sy[sent_id].res;
		
	sent_id = sy_num;
	op = "go";
	s1 = "";
	s2 = "";
	res = "";
	siYuan(op,s1,s2,res);
	if(strcmp(w[word_cnt].value,"else")){
		error("miss else");
		word_cnt--;
	}
	word_cnt++;
	Y();
	stringstream ss2;
	ss2<<sy_num;
	ss2>>sy[sent_id].res;
}

//while���
void K(){
	cout<<"K()"<<endl;
	if(strcmp(w[word_cnt].value,"while")){
		error("miss while");
		word_cnt--;
	}
	word_cnt++;
	if(strcmp(w[word_cnt].value,"(")){
		error("miss (");
		word_cnt--;
	}
	word_cnt++;
	//word_stack.push(w[word_cnt].value);
	X();
	sent_id = sy_num;
	
	if(op_stack.size()>0 && e == 0){
		op = op_stack.top();
		op_stack.pop();
		s2 = word_stack.top();
		word_stack.pop();
		s1 = word_stack.top();
		word_stack.pop();
		siYuan(op,s1,s2,res);
	}
	
	//cout<<w[word_cnt].value<<endl;
	if(strcmp(w[word_cnt].value,")")){
		error("miss )");
		word_cnt--;
	}
	word_cnt++;
	if(strcmp(w[word_cnt].value,"do")){
		error("miss do");
		word_cnt--;
	}
	word_cnt++;
	Y();	
}
 
void X(){
	cout<<"X()"<<endl;
	M();

	if(op_stack.size() > 0 && e == 0){
		op = op_stack.top();
		op_stack.pop(); 
		s2 = word_stack.top();
		word_stack.pop(); 
		s1 = word_stack.top();
		word_stack.pop();
		stringstream ss;
		ss << op_num;
		res = "t"+ss.str();
		word_stack.push(res);
		siYuan(op,s1,s2,res);
	}
	

	if(strcmp(w[word_cnt].value,">") == 0){
		op = "<=";
	}
	else if(strcmp(w[word_cnt].value,">=") == 0){
		op = "<";
	}
	else if(strcmp(w[word_cnt].value,"<") == 0){
		op = ">=";
	}
	else if(strcmp(w[word_cnt].value,"<=") == 0){
		op = ">";
	}
	else if(strcmp(w[word_cnt].value,"==") == 0){
		op = "!=";
	}
	else if(strcmp(w[word_cnt].value,"!=") == 0){
		op = "==";
	}
	//cout<<w.value<<"  "<<w.type<<endl;
	if(!L()){
		error("miss relation operator");
		word_cnt--;
	}
	op_stack.push(op);
	word_cnt++;
	//word_stack.push(w[word_cnt].value);
	//sent_id = sy_num;
	M();
}
//���ʽ 
void M(){
	cout<<"M()"<<endl;
	N();
	M1();
}
//�ӱ��ʽ 
void M1(){
	cout<<"M1()"<<endl;
	cout<<w[word_cnt].value<<endl;
	if(strcmp(w[word_cnt].value,";") == 0 || strcmp(w[word_cnt].value,")") == 0 
	|| L() || strcmp(w[word_cnt].value,"}") == 0 || strcmp(w[word_cnt].value,"else") == 0){
		return;
	}
	else if(!O()){
		error("miss + or -");
		//word_cnt--;
	}
	else{
		op_stack.push(w[word_cnt].value);
		word_cnt++;
		//word_stack.push(w[word_cnt].value);
		op_num++; 
		//getWord();
		//strcpy(b[b_num++].bds,new_w.value);
		N();
		M1();

		if(op_stack.size() > 1 && e == 0){
			op = op_stack.top();
			op_stack.pop();
			s2 = word_stack.top();
			word_stack.pop(); 
			s1 = word_stack.top();
			word_stack.pop();
			stringstream ss;
			ss << op_num;
			res = "t"+ss.str();
			word_stack.push(res);
			siYuan(op,s1,s2,res);
		}
		
	}
}

//�� ,������ݹ� 
void N(){
	cout<<"N()"<<endl;
	Z();
	N1();
}
void N1(){
	cout<<"N1()"<<endl;
	cout<<w[word_cnt].value<<endl;
	//������ż�,��ϵ�����  ;  ) 
	if(strcmp(w[word_cnt].value,";") == 0 || strcmp(w[word_cnt].value,")") == 0 
	|| strcmp(w[word_cnt].value,"}") == 0 || strcmp(w[word_cnt].value,"else") == 0 || L() || O()){
		return;
	}
	else if(!Q()){
		error("miss * or /");
		//�ֺų���ת����� 
		//word_cnt--;
	}
	//word_cnt++;
	else{
		op_num++;
		op_stack.push(w[word_cnt].value);
		word_cnt++;
		//word_stack.push(w[word_cnt].value);
		Z();
		N1();
		
		if(op_stack.size() > 1 && e == 0){
			op = op_stack.top();
			op_stack.pop();
			s2 = word_stack.top();
			word_stack.pop(); 
			s1 = word_stack.top();
			word_stack.pop();
			stringstream ss;
			ss << op_num;
			res = "t"+ss.str();
			word_stack.push(res);
			siYuan(op,s1,s2,res);
		}
		
	}
}
//����
void Z(){
	//cout<<w.value<<"  "<<w.type<<endl;
	//�����ֻ��ʶ�� 
	cout<<"Z()"<<endl;
	if(w[word_cnt].type!=1 && w[word_cnt].type!=2 &&strcmp(w[word_cnt].value,"(")){
		error("expression has a error");
		return;
	}
	//��ʶ��
	if(w[word_cnt].type == 1||w[word_cnt].type == 2){
		if(w[word_cnt].type == 2){
			is_say(w[word_cnt].value);
		}
		word_stack.push(w[word_cnt].value);
		word_cnt++;
		//equ[equ_num++] = w.value;
		return;
	}
	else if(strcmp(w[word_cnt].value,"(") == 0){
		word_cnt++;
		//word_stack.push(w[word_cnt].value);
		M();
		if(e == 0){
			op = op_stack.top();
			op_stack.pop();
			s2 = word_stack.top();
			word_stack.pop(); 
			s1 = word_stack.top();
			word_stack.pop();
			stringstream ss;
			ss << op_num;
			res = "t"+ss.str();
			word_stack.push(res);
			siYuan(op,s1,s2,res);
		}
		
		if(strcmp(w[word_cnt].value,")") == 0){
			word_cnt++;
			return;
		}
		else{
			error("miss )");
		}
	}
	return;
}

//���1 
void Y(){
	cout<<"Y()"<<endl; 
	if(strcmp(w[word_cnt].value,"{") == 0){
		word_cnt++;
		B();
		//cout<<w.value<<endl;
		if(strcmp(w[word_cnt].value,"}")){
			error("miss }");
		}
		word_cnt++;
		return; 
	}
	else{
		H();//���
		return; 
	}
}

//��ϵ�����
int L(){
	if(((w[word_cnt].type > 22 && w[word_cnt].type <= 26) || w[word_cnt].type == 37)){
		return 1;
	}
	return 0;
} 

//�ӷ������ 
int O(){
	if(w[word_cnt].type == 18 || w[word_cnt].type == 19){
		return 1;
	}
	return 0;
}
//�˷������ 
int Q(){
	if(w[word_cnt].type == 20 || w[word_cnt].type == 21){
		return 1;
	}
	return 0;
}

int main(){
	fin = fopen("compiler.txt","r");
	getWord();
	S();
	if(e==0)
	{
		printFour();
	}
	else
	{
		cout<<"\nSorry,can not generate siYuan."<<endl;
	}
	return 0;
}
/*

*/
