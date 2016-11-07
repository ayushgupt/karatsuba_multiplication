#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

vector<int> add_two_vectors(vector<int> a,vector<int> b) ;
vector<int> string_to_vector(string str);
string int2str(int num);
string vector_to_string(vector<int> v);
vector<int> add_two_vectors(vector<int> a,vector<int> b);
vector<int> multiply_two_vectors(vector<int> a,vector<int> b);
string multiply_two_strings(string a, string b);
vector<int> subtract_big_small_vectors(vector<int> a,vector<int> b);
vector<int> remove_initial_zeros(vector<int> a);
string subtract_big_small_strings(string a, string b);
vector<int> karatsuba_two_vectors(vector<int> a,vector<int> b);

void readinput();
void print_input();

int initial_length;
string num1;
string num2;

string int2str(int num)
{
	ostringstream ss;
	ss << num;
	return(ss.str());
}

vector<int> string_to_vector(string str)
{
	vector<int> result(int(str.length()),0);
	for(int i=0;i<int(str.length());i++)
	{
		if(str.at(i)=='1')
		{
			result[i]=1;
		}
	}
	return result;
}

string vector_to_string(vector<int> v)
{
	string str;
	for(int i=0;i<int(v.size());i++)
	{
		if(v[i]==1)
		{
			str+="1";
		}
		else
		{
			str+="0";
		}
	}
	return str;
}

string add_two_strings(string a, string b)
{
	string str=vector_to_string(add_two_vectors((string_to_vector(a)),(string_to_vector(b))));
	return str;
}

string karatsuba_two_strings(string a, string b)
{
	string str=vector_to_string( remove_initial_zeros ( karatsuba_two_vectors ((string_to_vector(a)),(string_to_vector(b)))   )   );
	return str;
}

string multiply_two_strings(string a, string b)
{
	string str= vector_to_string(     remove_initial_zeros (  multiply_two_vectors((string_to_vector(a)),(string_to_vector(b)))      )      );
	return str;
}

string subtract_big_small_strings(string a, string b)
{
	string str=vector_to_string(subtract_big_small_vectors((string_to_vector(a)),(string_to_vector(b))));
	return str;
}

vector<int> multiply_two_vectors(vector<int> a,vector<int> b)
{
	// cout<<"Normal Multiply Starts here"<<endl;
	// cout<<"a is "<<vector_to_string(a)<<endl;
	// cout<<"b is "<<vector_to_string(b)<<endl;
	a=remove_initial_zeros(a);
	b=remove_initial_zeros(b);
	int size_a=int(a.size());
	int size_b=int(b.size());
	vector<int> small_mult;
	vector<int> big_mult;
	if(size_a>=size_b)
	{
		big_mult=a;
		small_mult=b;
	}
	else
	{
		big_mult=b;
		small_mult=a;
	}
	reverse(small_mult.begin(),small_mult.end());
	vector<int> answer(5,0);
	for(int i=0;i<int(small_mult.size());i++)
	{
		if(small_mult[i]!=0)
		{
			vector<int> temp_mult(big_mult);
			for(int j=0;j<i;j++)
			{
				temp_mult.push_back(0);
			}
			answer = add_two_vectors(answer,temp_mult);
		}
	}
	// cout<<"Normal Multiply Ends here with answer"<<vector_to_string(answer)<<endl;
	return answer;
}

vector<int> add_two_vectors(vector<int> a,vector<int> b) 
{
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	int size_a=int(a.size());
	int size_b=int(b.size());
	int greater_len=0;
	int smaller_len=0;
	int carry=0;
	int curr_ans=0;
	vector<int> sum_vect;
	vector<int> bigger_operand;
	if(size_a>=size_b)
	{
		bigger_operand=a;
		greater_len=size_a;
		smaller_len=size_b;
	}
	else
	{
		bigger_operand=b;
		greater_len=size_b;
		smaller_len=size_a;
	}
	for(int i=0;i<size_a && i<size_b;i++)
	{
		curr_ans=carry+a[i]+b[i];
		if(curr_ans==3)
		{
			curr_ans=1;
			carry=1;
		}
		else if(curr_ans==2)
		{
			carry=1;
			curr_ans=0;
		}
		else if(curr_ans==1)
		{
			carry=0;
			curr_ans=1;
		}
		else
		{
			curr_ans=0;
			carry=0;
		}
		sum_vect.push_back(curr_ans);
	}

	for(int i=smaller_len;i<greater_len;i++)
	{
		curr_ans=carry+bigger_operand[i];
		if(curr_ans==3)
		{
			curr_ans=1;
			carry=1;
		}
		else if(curr_ans==2)
		{
			carry=1;
			curr_ans=0;
		}
		else if(curr_ans==1)
		{
			carry=0;
			curr_ans=1;
		}
		else
		{
			curr_ans=0;
			carry=0;
		}
		sum_vect.push_back(curr_ans);
	}
	if(carry==1)
	{
		sum_vect.push_back(1);
	}
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	reverse(sum_vect.begin(),sum_vect.end());
	return sum_vect;
} 

void readinput()
{
	ifstream infile;
	infile.open("input.txt");
	infile>>initial_length;
	infile>>num1;
	infile>>num2;
	infile.close();
}

bool are_equal(vector<int> a,vector<int> b)
{
	a=remove_initial_zeros(a);
	b=remove_initial_zeros(b);
	if(int(a.size())!=int(b.size()))
	{
		return false;
	}
	else
	{
		for(int i=0;i<int(a.size());i++)
		{
			if(a[i]!=b[i])
			{
				return false;
			}
		}
	}
	return true;
}


void print_input()
{
	ofstream outfile;
	outfile.open("hw3.out");
	outfile<<initial_length<<endl;
	outfile<<num1<<endl;
	outfile<<num2<<endl;
	outfile<<"Addn of these 2 things are "<<add_two_strings(num1,num2)<<endl;
	outfile<<"Both types of multiplication of these vectors are "<<endl;
	vector<int> normal(remove_initial_zeros(multiply_two_vectors(string_to_vector(num1),string_to_vector(num2))));
	vector<int> karatsuba(remove_initial_zeros(karatsuba_two_vectors(string_to_vector(num1),string_to_vector(num2))));
	outfile<<vector_to_string(normal)<<endl;
	outfile<<vector_to_string(karatsuba)<<endl;
	if(are_equal(normal,karatsuba))
	{
		outfile<<"They are Equal.!!"<<endl;
	}
	else
	{
		outfile<<"Something is wrong!!!!!"<<endl;
	}
	
	outfile.close();
	// cout<<initial_length<<endl;
	// cout<<num1<<endl;
	// cout<<num2<<endl;
	// cout<<"Addn of these 2 things are "<<add_two_strings(num1,num2)<<endl;
	// cout<<"Both types of multiplication of these vectors are "<<endl;
	// cout<<karatsuba_two_strings(num1,num2)<<endl;
	// cout<<multiply_two_strings(num1,num2)<<endl;
}

vector<int> remove_initial_zeros(vector<int> a)
{
	reverse(a.begin(),a.end());
	while(a[(int(a.size()))-1]==0 && int(a.size())>1)
	{
		a.pop_back();
	}
	reverse(a.begin(),a.end());
	return a;
}

vector<int> subtract_big_small_vectors(vector<int> a,vector<int> b)
{
	// cout<<"Subtraction starts here"<<endl;
	// cout<<"first term is "<<vector_to_string(a)<<endl;
	// cout<<"second term is "<<vector_to_string(b)<<endl;
	a=remove_initial_zeros(a);
	b=remove_initial_zeros(b);
	reverse(b.begin(),b.end());
	// make b size equal to a
	for(int i=int(b.size());i<(int(a.size()));i++)
	{
		b.push_back(0);
	}
	reverse(b.begin(),b.end());
	// cout<<"After making their length equal"<<endl;
	// cout<<"first term is "<<vector_to_string(a)<<endl;
	// cout<<"second term is "<<vector_to_string(b)<<endl;
	vector<int> b_complement(b);
	for(int i=0;i<int(b_complement.size());i++)
	{
		if(b_complement[i]==0)
		{
			b_complement[i]=1;
		}
		else
		{
			b_complement[i]=0;
		}
	}
	// cout<<"b_complement is "<<vector_to_string(b_complement)<<endl;
	vector<int> sub_result (add_two_vectors(a,b_complement));
	vector<int> temp_add(1,1);
	sub_result=add_two_vectors(sub_result,temp_add);
	// cout<<"Result of additions is "<<vector_to_string(sub_result)<<endl;
	reverse(sub_result.begin(),sub_result.end());
	int num_remove=int(sub_result.size())-int(a.size());
	for(int i=0;i<num_remove;i++)
	{
		sub_result.pop_back();
	}
	reverse(sub_result.begin(),sub_result.end());
	// cout<<"sub_result after removing the extra digit of addition is "<<vector_to_string(sub_result)<<endl;
	// cout<<"subtraction Result is "<<vector_to_string(sub_result)<<endl;
	// cout<<"subtraction ends here"<<endl;
	return sub_result;
}

vector<int> karatsuba_two_vectors(vector<int> a,vector<int> b)
{

	// cout<<"karatsuba starts here"<<endl;
	// cout<<"a vector is "<<vector_to_string(a)<<endl;
	// cout<<"b vector is "<<vector_to_string(b)<<endl;
	int size_a=int(a.size());
	int size_b=int(b.size());
	if(size_a==1 || size_b==1)
	{
		// cout<<"karatsuba ends early here as either of them had one bit!"<<endl;
		// cout<<"karatsuba result is "<<vector_to_string(multiply_two_vectors(a,b))<<endl;		
		return multiply_two_vectors(a,b);
	}
	// cout<<"2"<<endl;
	if(size_a!=size_b)
	{
		if(size_a>size_b)
		{
			int num_zero=(size_a-size_b);
			reverse(b.begin(),b.end());
			for(int i=0;i<num_zero;i++)
			{
				b.push_back(0);
			}
			reverse(b.begin(),b.end());
		}
		else
		{
			int num_zero=(size_b-size_a);
			reverse(a.begin(),a.end());
			for(int i=0;i<num_zero;i++)
			{
				a.push_back(0);
			}
			reverse(a.begin(),a.end());
		}
	}
	// cout<<"After making size equal"<<endl;
	// cout<<"a vector is "<<vector_to_string(a)<<endl;
	// cout<<"b vector is "<<vector_to_string(b)<<endl;
	size_a=int(a.size());
	size_b=int(b.size());
	int low_number=size_a/2;
	int high_number=size_a - low_number;
	vector<int> a_lower;
	vector<int> a_higher;	
	vector<int> b_lower;
	vector<int> b_higher;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	// cout<<"4"<<endl;
	for(int i=0;i<int(a.size());i++)
	{
		if(i<low_number)
		{
			a_lower.push_back(a[i]);
		}
		else
		{
			a_higher.push_back(a[i]);
		}
	}
	// cout<<"5"<<endl;
	for(int i=0;i<int(b.size());i++)
	{
		if(i<low_number)
		{
			b_lower.push_back(b[i]);
		}
		else
		{
			b_higher.push_back(b[i]);
		}
	}
	// cout<<"6"<<endl;
	reverse(a_lower.begin(),a_lower.end());
	reverse(a_higher.begin(),a_higher.end());
	reverse(b_lower.begin(),b_lower.end());
	reverse(b_higher.begin(),b_higher.end());
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());

	// cout<<"a_lower vector is "<<vector_to_string(a_lower)<<endl;
	// cout<<"a_higher vector is "<<vector_to_string(a_higher)<<endl;
	// cout<<"b_lower vector is "<<vector_to_string(b_lower)<<endl;
	// cout<<"b_higher vector is "<<vector_to_string(b_higher)<<endl;

	vector<int> p(karatsuba_two_vectors(a_higher,b_higher));
	vector<int> q(karatsuba_two_vectors(a_lower,b_lower));
	vector<int> r( karatsuba_two_vectors(add_two_vectors(a_lower,a_higher),add_two_vectors(b_lower,b_higher)) );
	// cout<<"7"<<endl;
	vector<int> first_term(p);
	// cout<<"first_term before shift is "<<vector_to_string(first_term)<<endl;
	// cout<<"first_term after reverse is "<<vector_to_string(first_term)<<endl;
	for(int i=0;i<2*low_number;i++)
	{
		first_term.push_back(0);
	}
	// cout<<"first_term after shift is "<<vector_to_string(first_term)<<endl;

	vector<int> second_term(subtract_big_small_vectors(r,p));
	// cout<<"11"<<endl;
	// cout<<"p is "<<vector_to_string(p)<<endl;
	// cout<<"q is "<<vector_to_string(q)<<endl;
	// cout<<"r is "<<vector_to_string(r)<<endl;
	// cout<<"second_term after one sub is "<<vector_to_string(second_term)<<endl;
	second_term=subtract_big_small_vectors(second_term,q);
	// cout<<"second_term after two sub is "<<vector_to_string(second_term)<<endl;
	// cout<<"12"<<endl;
	for(int i=0;i<low_number;i++)
	{
		second_term.push_back(0);
	}
	// cout<<"second_term after shift is "<<vector_to_string(second_term)<<endl;
	first_term=add_two_vectors(first_term,second_term);
	first_term=add_two_vectors(first_term,q);
	// cout<<"karatsuba ends here"<<endl;
	// cout<<"a was "<<vector_to_string(a)<<endl;
	// cout<<"b was "<<vector_to_string(b)<<endl;
	// cout<<"Result is "<<vector_to_string(first_term)<<endl;
	return first_term;
}


void data_for_graphs()
{
	ofstream outfile;
	outfile.open("hw3.out");
	for(int i=0;i<17;i++)
	{
		vector<int> v((pow(2,i)),1);
		clock_t karat_begin = clock();
		vector<int> karatsuba_result(karatsuba_two_vectors(v,v));
		clock_t karat_end = clock();
		double karat_elapsed_secs = double(karat_end - karat_begin) / CLOCKS_PER_SEC;

		clock_t long_mul_begin = clock();
		vector<int> long_mul_result(multiply_two_vectors(v,v));
		clock_t long_mul_end = clock();
		double long_mul_elapsed_secs = double(long_mul_end - long_mul_begin) / CLOCKS_PER_SEC;

		cout<<"For test case "<<i<<endl;
		cout<<"karatsuba result is "<<vector_to_string(karatsuba_result)<<endl;
		cout<<"normal multiply result is "<<vector_to_string(long_mul_result)<<endl;
		if(are_equal(karatsuba_result,long_mul_result))
		{
			cout<<"They are equal!! Awesome!"<<endl;
		}
		else
		{
			cout<<"The Fuck, they are unequal"<<endl;
		}
		cout<<"Normal Multiply time was "<<long_mul_elapsed_secs<<endl;
		cout<<"Karatsuba multiplication time was "<<karat_elapsed_secs<<endl;
		cout<<endl<<endl<<endl;

		
		outfile<<"For test case "<<i<<endl;
		outfile<<"karatsuba result is "<<vector_to_string(karatsuba_result)<<endl;
		outfile<<"normal multiply result is "<<vector_to_string(long_mul_result)<<endl;
		if(are_equal(karatsuba_result,long_mul_result))
		{
			outfile<<"They are equal!! Awesome!"<<endl;
		}
		else
		{
			outfile<<"The Fuck, they are unequal"<<endl;
		}
		outfile<<"Normal Multiply time was "<<long_mul_elapsed_secs<<endl;
		outfile<<"Karatsuba multiplication time was "<<karat_elapsed_secs<<endl;
		outfile<<endl<<endl<<endl;
	}
	outfile.close();
}


int main()
{
	readinput();
	ofstream outfile;
	outfile.open("output.txt");
	outfile<< multiply_two_strings(num1,num2);
	outfile.close();	
	// print_input();
	// data_for_graphs();
	return 0;
}
