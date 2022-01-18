// Algorithm to implement simplified - DES encryption
//#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
string Permutation(vector<int> array, string inp){
    string out = "";
    for(int i=0;i<array.size();i++)
        out += inp[array[i]-1];
    return out;
}
class S_DES{
public:
    string KEY,K1,K2,IPOut,InvIPOut;
    string F1Out;
    string INPUT,OUTPUT;
    void initialize(string key){
        if(key.size()!=10){
            cout<<"\nInValid Key-Length "<<key<<" "<<key.size();
            exit(1);
        }
        KEY = key;
	    Keys_Generation();
	}
    void Keys_Generation(){
        cout<<"Enter P10 permutation array: ";
        vector<int> P10(10,0);
//        for(int i=0;i<10;i++)
//            cin>>P10[i];
		P10.push_back(3);
		P10.push_back(5);
		P10.push_back(2);
		P10.push_back(7);
		P10.push_back(4);
		P10.push_back(10);
		P10.push_back(1);
		P10.push_back(9);
		P10.push_back(8);
		P10.push_back(6);
		
        string P10_output = Permutation(P10,KEY);
        cout<<"P10 output while generating key: "<<P10_output<<endl;
        string P10_left = P10_output.substr(0,5), P10_right = P10_output.substr(5,5);
        string pl = LShift(P10_left,1), pr = LShift(P10_right,1);
        string plpr = pl+pr;
        cout<<"Enter P8 permutation array: ";
        vector<int> P8(10,0);
//        for(int i=0;i<8;i++)
//            cin>>P8[i];
		P8.push_back(6);
		P8.push_back(3);
		P8.push_back(7);
		P8.push_back(4);
		P8.push_back(8);
		P8.push_back(5);
		P8.push_back(10);
		P8.push_back(9);
		
        K1 = Permutation(P8,plpr);
        cout<<"K1: "<<K1<<endl;
	    string pl1=LShift(pl,2), pr1=LShift(pr,2);
        plpr = pl1+pr1;
        K2 = Permutation(P8,plpr);
        cout<<"K2: "<<K2<<endl;
    }

	string LShift(string input,int n){
        string output = input;
        char firstbit;
	    while(n--){
            firstbit = output[0];
            output = output.substr(1,output.size()-1);
            output += firstbit;
        }
        return output;
    }
    void DES_Encryption(){
	    IP();
        string LIP = IPOut.substr(0,4);
        string RIP = IPOut.substr(4,4);
        cout<<"IP output: "<<IPOut<<endl;
        Function_F(LIP,RIP,1);
        cout<<"Fn Output: "<<F1Out<<endl;
        string L1 = F1Out.substr(0,4), R1 = F1Out.substr(4,4);
	    Function_F(R1,L1,2);
        cout<<"Fn Output second time: "<<F1Out<<endl;
        InvIP(F1Out);
        cout<<"Encrypted Cipher-string: "<<InvIPOut<<endl;
	}
    /*Method to perform Initial-Permutation*/
	void IP(){
        vector<int> IP_array(8,0);
        cout<<"Enter initial Permutation array: ";
//        for(int i=0;i<8;i++)
//            cin>>IP_array[i];
		IP_array.push_back(2);
		IP_array.push_back(3);
		IP_array.push_back(6);
		IP_array.push_back(1);
		IP_array.push_back(4);
		IP_array.push_back(8);
		IP_array.push_back(5);
		IP_array.push_back(7);
		
        IPOut = Permutation(IP_array,INPUT);
	}
    /*Method to perform Inverse of Initial-Permutation*/
    void InvIP(string input){
    vector<int> InvIPArray(8,0);
    cout<<"Enter Inverse initial Permutation: ";
//    for(int i=0;i<8;i++)
//        cin>>InvIPArray[i];
	InvIPArray.push_back(4);
	InvIPArray.push_back(3);
	InvIPArray.push_back(1);
	InvIPArray.push_back(5);
	InvIPArray.push_back(7);
	InvIPArray.push_back(2);
	InvIPArray.push_back(8);
	InvIPArray.push_back(6);
    InvIPOut = Permutation(InvIPArray,input);
    }
	void Function_F(string linput,string rinput,int key)
	{
        cout<<"Enter E/P array: ";
        vector<int> E_P(8,0);
//        for(int i=0;i<8;i++)
//            cin>>E_P[i];
		E_P.push_back(4);
		E_P.push_back(1);
		E_P.push_back(2);
		E_P.push_back(3);
		E_P.push_back(2);
		E_P.push_back(3);
		E_P.push_back(4);
		E_P.push_back(1);
        string E_POutput = Permutation(E_P,rinput);
        string EXOR_Output;
        if(key == 1)
            EXOR_Output = EX_OR(E_POutput,K1);
        else
            EXOR_Output = EX_OR(E_POutput,K2);
        string LEXOR = EXOR_Output.substr(0,4),REXOR = EXOR_Output.substr(4,4);
        string SBOX0_Output=SBOX0(LEXOR);
        string SBOX1_Output=SBOX1(REXOR);
        string SBOX_Output = SBOX0_Output+SBOX1_Output;
        cout<<"Enter P4 Operation array: ";
        vector<int> P4(4,0);
//        for(int i=0;i<4;i++)
//            cin>>P4[i];
		P4.push_back(2);
		P4.push_back(4);
		P4.push_back(3);
		P4.push_back(1);
        string P4_Output = Permutation(P4,SBOX_Output);
        string fk_Output = EX_OR(P4_Output,linput);
        F1Out = fk_Output + rinput;
	}
	string EX_OR(string a,string b){
        string output = "";
        for(int i=0;i<a.size();i++){
            if(a[i] == b[i])
                output += "0";
            else
                output += "1";
        }
        return output;
	}
    string SBOX0(string l)
	{
        cout<<"Enter Input for S0\n";
        vector<int> temp(4,0);
        vector<vector<int> > S0(4,temp);
        for(int i=0;i<4;i++){
            for(int j = 0;j<4;j++)
                cin>>S0[i][j];
        }
        string bits[]={"00","01","10","11"};
	    string lrow = l.substr(0,1)+l.substr(3,1),lcol = l.substr(1,1)+l.substr(2,1);
	    string SO;
        int i,lr,lc,b;
        for(i=0;i<4;i++){
            if(lrow == bits[i])
                lr=i;
            if(lcol == bits[i])
                lc=i;
        }
        b=S0[lr][lc];
        return bits[b];
	}
    string SBOX1(string l)
	{
        cout<<"Enter Input for S1\n";
        vector<int> temp(4,0);
        vector<vector<int> > S0(4,temp);
        for(int i=0;i<4;i++){
            for(int j = 0;j<4;j++)
                cin>>S0[i][j];
        }
        string bits[]={"00","01","10","11"};
	    string lrow = l.substr(0,1)+l.substr(3,1),lcol = l.substr(1,1)+l.substr(2,1);
	    string SO;
        int i,lr,lc,b;
        for(i=0;i<4;i++){
            if(lrow == bits[i])
                lr=i;
            if(lcol == bits[i])
                lc=i;
        }
        b=S0[lr][lc];
        return bits[b];
	}
};
int main()
{
    int i,n=10,choice;
    string key;
    S_DES S;
    while(1){
        cout<<"\nWhat do you want to do..\n1. Encryption\n2. Exit\n\nEnter the choice? ";
        cin>>choice;
        switch(choice){
            case 1:
            cout<<"\nEnter the 10-bits KEY: ";
            cin>>key;
            cout<<"\nNotedown this key, as same key is used for Decryption\n";
            S.initialize(key);
            cout<<"Enter string to encrypt: ";
            cin>>S.INPUT;
            S.DES_Encryption();
    	    break;
            case 2:
            exit(0);
            default:
	        cout<<"\nWrong Choice Enter again\nPress any key to return to Main Menu..";
            break;
        }
    }
    return 0;
}
